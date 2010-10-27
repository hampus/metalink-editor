#include "XmlParser.hpp"
#include "Metalink4Reader.hpp"
#include <fstream>

namespace {

void StartElementHandler(void* userData, const char* name, const char** attrs)
{
    XmlParser* parser = static_cast<XmlParser*>(userData);
    try {
        std::map<std::string, wxString> attr_map;
        while(*attrs) {
            attr_map[std::string(*attrs)] = wxString(*(attrs+1), wxConvUTF8);
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

}

XmlParser::XmlParser(XmlContentHandler& handler)
    : handler_(handler)
{
    parser_ = XML_ParserCreateNS(0, '\t');
    XML_SetUserData(parser_, static_cast<void*>(this));
    XML_SetStartElementHandler(parser_, StartElementHandler);
    XML_SetEndElementHandler(parser_, EndElementHandler);
    XML_SetCharacterDataHandler(parser_, CharacterDataHandler);
    error_msg_ = "Failed to parse XML.";
}

XmlParser::~XmlParser() {
    XML_ParserFree(parser_);
}

void XmlParser::parse(wxString filename) {
    std::ifstream in(filename.mb_str(wxConvFile),
                     std::ofstream::in | std::ofstream::binary);
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

void XmlParser::start_element(wxString name, std::map<std::string, wxString> attrs) {
    handler_.start_element(name, attrs);
}

void XmlParser::end_element(wxString name) {
    handler_.end_element(name);
}

void XmlParser::char_data(wxString data) {
    handler_.char_data(data);
}

XML_Parser XmlParser::get_parser() {
    return parser_;
}

void XmlParser::set_error_msg(const char* msg) {
    error_msg_ = msg;
}
