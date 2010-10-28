#include "Metalink3Reader.hpp"
#include "XmlParser.hpp"

Metalink3Reader::Metalink3Reader(MetalinkEditor& editor)
    : editor_(editor)
{
}

bool Metalink3Reader::load(wxString filename)
{
    editor_.clear();
    state_ = STATE_NONE;
    correctversion_ = false;
    XmlParser parser(*this);
    parser.parse(filename);
    return correctversion_;
}

void Metalink3Reader::start_element(wxString name, std::map<std::string,
                                    wxString> attrs)
{
    if(!remove_namespace(name)) return;
    switch(state_) {
        case STATE_NONE:
            if(name == wxT("metalink") && attrs["version"] == wxT("3.0")) {
                correctversion_ = true;
                state_ = STATE_METALINK;
            }
        break;
        case STATE_METALINK:
            if(name == wxT("file")) {
                if(attrs.count("name") != 1) {
                    throw MetalinkLoadError("Missing 'name' attribute on file "
                                            "element.");
                }
                file_ = MetalinkFile(attrs["name"]);
                state_ = STATE_FILE;
            }
        break;
        case STATE_FILE:
            if(name == wxT("resources")) {
                state_ = STATE_RESOURCES;
            }
        break;
        case STATE_RESOURCES:
            if(name == wxT("url")) {
                source_ = MetalinkSource();
                if(attrs.count("location") == 1) {
                    source_.set_location(attrs["location"]);
                }
                if(attrs.count("preference") == 1) {
                    source_.set_priority(attrs["preference"]);
                }
                state_ = STATE_URL;
            }
        break;
    }
    data_.clear();
}

void Metalink3Reader::end_element(wxString name)
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
        case STATE_RESOURCES:
            if(name == wxT("resources")) {
                state_ = STATE_FILE;
            }
        break;
        case STATE_URL:
            if(name == wxT("url")) {
                source_.set_uri(data_);
                file_.add_source(source_);
                state_ = STATE_RESOURCES;
            }
        break;
    }
}

void Metalink3Reader::char_data(wxString data)
{
    data_.append(data);
}

bool Metalink3Reader::remove_namespace(wxString& name)
{
    wxString ns = wxT("http://www.metalinker.org/\t");
    if(name.compare(0, ns.length(), ns) == 0) {
        name.erase(0, ns.length());
        return true;
    }
    return false;
}
