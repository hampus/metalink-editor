#include "Metalink4Reader.hpp"
#include "XmlParser.hpp"

Metalink4Reader::Metalink4Reader(MetalinkEditor& editor)
    : editor_(editor)
{
}

bool Metalink4Reader::load(wxString filename)
{
    editor_.clear();
    state_ = STATE_NONE;
    correctversion_ = false;
    XmlParser parser(*this);
    parser.parse(filename);
    return correctversion_;
}

void Metalink4Reader::start_element(wxString name, std::map<std::string,
                                    wxString> attrs)
{
    if(!remove_namespace(name)) return;
    switch(state_) {
        case STATE_NONE:
            if(name == wxT("metalink")) {
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
            if(name == wxT("metaurl") && attrs["mediatype"] == wxT("torrent")) {
                source_ = MetalinkSource();
                source_.set_torrent(true);
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
            if(name == wxT("url") || name == wxT("metaurl")) {
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
