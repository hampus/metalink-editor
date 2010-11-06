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
