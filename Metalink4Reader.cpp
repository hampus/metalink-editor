#include "Metalink4Reader.hpp"
#include "XmlParser.hpp"

Metalink4Reader::Metalink4Reader()
    : recognized_(false)
{
}

void Metalink4Reader::load(wxString filename)
{
    metalink_.clear();
    state_ = STATE_NONE;
    recognized_ = false;
    XmlParser parser(*this);
    parser.parse(filename);
    if(state_ != STATE_NONE) {
        throw MetalinkLoadError("Internal error while loading metalink!");
    }
}

const Metalink& Metalink4Reader::get_metalink() const
{
    return metalink_;
}

bool Metalink4Reader::is_recognized() const
{
    return recognized_;
}

void Metalink4Reader::start_element(wxString name, std::map<std::string,
                                    wxString> attrs)
{
    if(!remove_namespace(name)) return;
    switch(state_) {
        case STATE_NONE:
            if(name == wxT("metalink")) {
                recognized_ = true;
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
            } else if(name == wxT("metaurl")) {
                if(attrs["mediatype"] == wxT("torrent")) {
                    source_ = MetalinkSource();
                    source_.set_torrent(true);
                    if(attrs.count("priority") == 1) {
                        source_.set_priority(attrs["priority"]);
                    }
                    state_ = STATE_URL;
                }
            } else if(name == wxT("pieces")) {
                if(attrs.count("length") != 1 || attrs.count("type") != 1) {
                    throw MetalinkLoadError("Missing attribute on pieces "
                                            "element.");
                }
                file_.set_piece_hash_type(attrs["type"]);
                file_.set_piece_length(attrs["length"]);
                piece_hashes_.clear();
                state_ = STATE_PIECES;
            } else if(name == wxT("hash")) {
                if(attrs.count("type") != 1) {
                    throw MetalinkLoadError("Missing 'type' attribute on "
                                            "hash element");
                }
                hash_ = MetalinkHash(attrs["type"]);
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
                metalink_.add_file(file_);
                state_ = STATE_METALINK;
            } else if(name == wxT("identity")) {
                file_.set_identity(data_);
            } else if(name == wxT("description")) {
                file_.set_description(data_);
            } else if(name == wxT("version")) {
                file_.set_version(data_);
            } else if(name == wxT("size")) {
                file_.set_size(data_);
            } else if(name == wxT("hash")) {
                hash_.value = data_;
                file_.add_file_hash(hash_);
            }
        break;
        case STATE_PIECES:
            if(name == wxT("pieces")) {
                file_.set_piece_hash(piece_hashes_);
                state_ = STATE_FILE;
            } else if(name == wxT("hash")) {
                piece_hashes_.push_back(data_);
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
