#include "Metalink3Writer.hpp"

Metalink3Writer::Metalink3Writer(const Metalink& metalink)
    : metalink_(metalink)
{
}

void Metalink3Writer::write_metalink()
{
    write_text(wxString(wxT("<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n")), true);
    start(wxT("metalink"));
    add_attr(wxT("version"), wxT("3.0"));
    add_attr(wxT("generator"), get_generator());
    add_attr(wxT("xmlns"), wxT("http://www.metalinker.org/"));
    close_start();
    start(wxT("files"));
    close_start();
    const std::vector<MetalinkFile>& files = metalink_.get_files();
    for(std::vector<MetalinkFile>::const_iterator i = files.begin(),
            eoi = files.end(); i != eoi; ++i) {
        write_file(*i);
    }
    end(wxT("files"));
    end(wxT("metalink"));
}

void Metalink3Writer::write_file(const MetalinkFile& file)
{
    start(wxT("file"));
    add_attr(wxT("name"), file.get_filename());
    close_start();
    add_element(wxT("identity"), file.get_identity());
    add_element(wxT("size"), file.get_size());
    write_verification(file);
    start(wxT("resources"));
    close_start();
    const std::vector<MetalinkSource>& sources = file.get_sources();
    for(std::vector<MetalinkSource>::const_iterator i = sources.begin(),
            eoi = sources.end(); i != eoi; ++i) {
        write_source(*i);
    }
    end(wxT("resources"));
    end(wxT("file"));
}

void Metalink3Writer::write_verification(const MetalinkFile& file)
{
    MetalinkFile file2 = convert_hash_types(file);
    if(has_hashes(file2) || has_piece_hashes(file2)) {
        start(wxT("verification"));
        close_start();
        write_hashes(file2);
        write_piece_hashes(file2);
        end(wxT("verification"));
    }
}

MetalinkFile Metalink3Writer::convert_hash_types(const MetalinkFile& file)
{
    std::vector<std::pair<wxString, wxString> > hashes = file.get_file_hashes();
    for(std::vector<std::pair<wxString, wxString> >::iterator i =
            hashes.begin(), eoi = hashes.end(); i != eoi; ++i) {
        i->first = convert_hash_type(i->first);
    }
    wxString piece_type = convert_hash_type(file.get_piece_hash_type());
    MetalinkFile file2 = file;
    file2.set_file_hashes(hashes);
    file2.set_piece_hash_type(piece_type);
    return file2;
}

const wxString Metalink3Writer::convert_hash_type(const wxString& type)
{
    if(type == wxT("sha-1")){
        return wxT("sha1");
    } else if(type == wxT("sha-224")){
        return wxT("sha224");
    } else if(type == wxT("sha-256")){
        return wxT("sha256");
    } else if(type == wxT("sha-384")){
        return wxT("sha384");
    } else if(type == wxT("sha-256")){
        return wxT("sha256");
    }
    return type;
}

bool Metalink3Writer::has_hashes(const MetalinkFile& file)
{
    return !file.get_file_hashes().empty();
}

bool Metalink3Writer::has_piece_hashes(const MetalinkFile& file)
{
    if(file.get_piece_hashes().empty()) return false;
    if(file.get_piece_hash_type().empty()) return false;
    return true;
}

void Metalink3Writer::write_hashes(const MetalinkFile& file)
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

void Metalink3Writer::write_piece_hashes(const MetalinkFile& file)
{
    if(!has_piece_hashes(file)) return;
    start(wxT("pieces"));
    add_attr(wxT("length"),
             wxString::Format(wxT("%lu"), file.get_piece_length()));
    add_attr(wxT("type"), file.get_piece_hash_type());
    close_start();
    const std::vector<wxString>& hashes = file.get_piece_hashes();
    long index = 0;
    for(std::vector<wxString>::const_iterator i = hashes.begin(),
            eoi = hashes.end(); i != eoi; ++i) {
        start(wxT("hash"));
        add_attr(wxT("piece"), wxString::Format(wxT("%ld"), index));
        end(wxT("hash"), *i);
        index++;
    }
    end(wxT("pieces"));
}

void Metalink3Writer::write_source(const MetalinkSource& source)
{
    if(source.is_torrent()) {
        start(wxT("url"));
        add_attr(wxT("type"), wxT("bittorrent"));
        if(!source.get_prioritystr().empty()) {
            add_attr(wxT("preference"), source.get_prioritystr());
        }
        end(wxT("url"), source.get_uri());
    } else {
        start(wxT("url"));
        if(!source.get_prioritystr().empty()) {
            add_attr(wxT("preference"), source.get_prioritystr());
        }
        if(!source.get_location().empty()) {
            add_attr(wxT("location"), source.get_location());
        }
        end(wxT("url"), source.get_uri());
    }
}
