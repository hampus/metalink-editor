#include "Metalink4Reader.hpp"
#include <expat.h>
#include <fstream>
#include <iostream>

using namespace std;

void StartElementHandler(void* userData, const char* name, const char** attrs);
void EndElementHandler(void* userData, const char* name);
void CharacterDataHandler(void* userData, const char* s, int len);

class XmlParser
{
public:
    XmlParser(Metalink4Reader& reader)
        : reader_(reader)
    {
        parser_ = XML_ParserCreateNS(0, '\t');
        XML_SetUserData(parser_, static_cast<void*>(this));
        XML_SetStartElementHandler(parser_, StartElementHandler);
        XML_SetEndElementHandler(parser_, EndElementHandler);
        XML_SetCharacterDataHandler(parser_, CharacterDataHandler);
        error_msg_ = "Failed to parse XML.";
    }

    ~XmlParser() {
        XML_ParserFree(parser_);
    }

    void parse(wxString filename) {
        ifstream in(filename.mb_str(wxConvFile), ofstream::in | ofstream::binary);
        if(in.fail()) throw MetalinkLoadError();
        char buf[4096];
        XML_Status result;
        while (in.good()) {
            in.read(buf, sizeof(buf));
            int bytes = in.gcount();
            result =  XML_Parse(parser_, buf, bytes, false);
            if(result != XML_STATUS_OK) throw MetalinkLoadError(error_msg_);
        }
        if(!in.eof()) throw MetalinkLoadError();
        in.close();
        result =  XML_Parse(parser_, buf, 0, true);
    }

    void start_element(wxString name, std::map<std::string, wxString> attrs) {
        reader_.start_element(name, attrs);
    }

    void end_element(wxString name) {
        reader_.end_element(name);
    }

    void char_data(wxString data) {
        reader_.char_data(data);
    }

    XML_Parser get_parser() {
        return parser_;
    }

    void set_error_msg(const char* msg) {
        error_msg_ = msg;
    }
private:
    XML_Parser parser_;
    Metalink4Reader& reader_;
    const char* error_msg_;
};

void StartElementHandler(void* userData, const char* name, const char** attrs)
{
    XmlParser* parser = static_cast<XmlParser*>(userData);
    try {
        map<string, wxString> attr_map;
        while(*attrs) {
            attr_map[string(*attrs)] = wxString(*(attrs+1), wxConvUTF8);
            attrs += 2;
        }
        parser->start_element(wxString(name, wxConvUTF8), attr_map);
    } catch(MetalinkLoadError& e) {
        parser->set_error_msg(e.what());
        XML_StopParser(parser->get_parser(), false);
    }
}

void EndElementHandler(void* userData, const char* name)
{
    XmlParser* parser = static_cast<XmlParser*>(userData);
    try {
        parser->end_element(wxString(name, wxConvUTF8));
    } catch(MetalinkLoadError& e) {
        parser->set_error_msg(e.what());
        XML_StopParser(parser->get_parser(), false);
    }
}

void CharacterDataHandler(void* userData, const char* s, int len)
{
    XmlParser* parser = static_cast<XmlParser*>(userData);
    try {
        parser->char_data(wxString(s, wxConvUTF8, len));
    } catch(MetalinkLoadError& e) {
        parser->set_error_msg(e.what());
        XML_StopParser(parser->get_parser(), false);
    }
}

Metalink4Reader::Metalink4Reader(MetalinkEditor& editor)
    : editor_(editor)
{
}

void Metalink4Reader::load(wxString filename)
{
    editor_.clear();
    state_ = STATE_NONE;
    XmlParser parser(*this);
    parser.parse(filename);
}

void Metalink4Reader::start_element(wxString name, std::map<std::string, wxString> attrs)
{
    if(!remove_namespace(name)) return;
    switch(state_) {
        case STATE_NONE:
            if(name == wxT("metalink")) {
                state_ = STATE_METALINK;
            }
        break;
        case STATE_METALINK:
            if(name == wxT("file")) {
                if(attrs.count("name") != 1) {
                    throw MetalinkLoadError("Missing 'name' attribute on file element.");
                }
                file_ = MetalinkFile(attrs["name"]);
                state_ = STATE_FILE;
            }
        break;
        case STATE_FILE:
            if(name == wxT("url")) {
                source_ = MetalinkSource();
                if(attrs.count("location") == 1) {
                    source_.set_location(attrs["location"]);
                }
                if(attrs.count("priority") == 1) {
                    source_.set_priority(attrs["priority"]);
                }
                state_ = STATE_URL;
            }
        break;
    }
    data_.clear();
}

void Metalink4Reader::end_element(wxString name)
{
    if(!remove_namespace(name)) return;
    switch(state_) {
        case STATE_METALINK:
            if(name == wxT("metalink")) {
                state_ = STATE_NONE;
            }
        break;
        case STATE_FILE:
            if(name == wxT("file")) {
                editor_.add_file(file_);
                state_ = STATE_METALINK;
            }
        break;
        case STATE_URL:
            if(name == wxT("url")) {
                source_.set_uri(data_);
                file_.add_source(source_);
                state_ = STATE_FILE;
            }
        break;
    }
}

void Metalink4Reader::char_data(wxString data)
{
    data_.append(data);
}

bool Metalink4Reader::remove_namespace(wxString& name)
{
    wxString ns = wxT("urn:ietf:params:xml:ns:metalink\t");
    if(name.compare(0, ns.length(), ns) == 0) {
        name.erase(0, ns.length());
        return true;
    }
    return false;
}
