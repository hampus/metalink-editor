#include "Metalink4Writer.hpp"

Metalink4Writer::Metalink4Writer(const Metalink& metalink)
    : metalink_(metalink)
{
}

void Metalink4Writer::write_metalink()
{
    write_text(wxT("<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"));
    start(wxT("metalink"));
    add_attr(wxT("xmlns"), wxT("urn:ietf:params:xml:ns:metalink"));
    close_start();
    add_element(wxT("generator"), get_generator());
    const std::vector<MetalinkFile>& files = metalink_.get_files();
    for(std::vector<MetalinkFile>::const_iterator i = files.begin(),
            eoi = files.end(); i != eoi; ++i) {
        write_file(*i);
    }
    end(wxT("metalink"));
}

void Metalink4Writer::write_file(const MetalinkFile& file)
{
    start(wxT("file"));
    add_attr(wxT("name"), file.get_filename());
    close_start();
    add_element(wxT("identity"), file.get_identity());
    add_element(wxT("size"), file.get_size());
    write_hashes(file);
    write_piece_hash(file);
    const std::vector<MetalinkSource>& sources = file.get_sources();
    for(std::vector<MetalinkSource>::const_iterator i = sources.begin(),
            eoi = sources.end(); i != eoi; ++i) {
        write_source(*i);
    }
    end(wxT("file"));
}

void Metalink4Writer::write_hashes(const MetalinkFile& file)
{
    const std::vector<std::pair<wxString, wxString> >& hashes =
        file.get_file_hashes();
    for(std::vector<std::pair<wxString, wxString> >::const_iterator i =
            hashes.begin(), eoi = hashes.end(); i != eoi; ++i) {
        start(wxT("hash"));
        add_attr(wxT("type"), (*i).first);
        end(wxT("hash"), (*i).second);
    }
}

void Metalink4Writer::write_piece_hash(const MetalinkFile& file)
{
    if(file.get_piece_hashes().empty()) return;
    if(file.get_piece_hash_type().empty()) return;
    start(wxT("pieces"));
    add_attr(wxT("length"),
             wxString::Format(wxT("%lu"), file.get_piece_length()));
    add_attr(wxT("type"), file.get_piece_hash_type());
    close_start();
    const std::vector<wxString>& hashes = file.get_piece_hashes();
    for(std::vector<wxString>::const_iterator i = hashes.begin(),
            eoi = hashes.end(); i != eoi; ++i) {
        add_element(wxT("hash"), *i);
    }
    end(wxT("pieces"));
}

void Metalink4Writer::write_source(const MetalinkSource& source)
{
    if(source.is_torrent()) {
        start(wxT("metaurl"));
        add_attr(wxT("mediatype"), wxT("torrent"));
        if(!source.get_prioritystr().empty()) {
            add_attr(wxT("priority"), source.get_prioritystr());
        }
        end(wxT("metaurl"), source.get_uri());
    } else {
        start(wxT("url"));
        if(!source.get_prioritystr().empty()) {
            add_attr(wxT("priority"), source.get_prioritystr());
        }
        if(!source.get_location().empty()) {
            add_attr(wxT("location"), source.get_location());
        }
        end(wxT("url"), source.get_uri());
    }
}
