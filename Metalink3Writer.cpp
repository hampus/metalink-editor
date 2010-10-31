#include "Metalink3Writer.hpp"
#include "config.h"

Metalink3Writer::Metalink3Writer(const MetalinkEditor& editor)
    : editor_(editor)
{
}

Metalink3Writer::~Metalink3Writer()
{
}

void Metalink3Writer::save(const wxString& filename)
{
    using std::ofstream;
    out_.open(filename.mb_str(wxConvFile),
              ofstream::out | ofstream::binary | ofstream::trunc);
    indent_ = 0;
    wxString generator("MetalinkEditor/" METALINKEDITOR_VERSION, wxConvUTF8);
    write(wxT("<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"));
    start(wxT("metalink"));
    add_attr(wxT("version"), wxT("3.0"));
    add_attr(wxT("generator"), generator);
    add_attr(wxT("xmlns"), wxT("http://www.metalinker.org/"));
    close_start();
    start(wxT("files"));
    close_start();
    const std::vector<MetalinkFile>& files = editor_.get_files();
    for(std::vector<MetalinkFile>::const_iterator i = files.begin(),
            eoi = files.end(); i != eoi; ++i) {
        write(*i);
    }
    end(wxT("files"));
    end(wxT("metalink"));
}

void Metalink3Writer::write(const MetalinkFile& file)
{
    start(wxT("file"));
    add_attr(wxT("name"), file.get_filename());
    close_start();
    start(wxT("resources"));
    close_start();
    const std::vector<MetalinkSource>& sources = file.get_sources();
    for(std::vector<MetalinkSource>::const_iterator i = sources.begin(),
            eoi = sources.end(); i != eoi; ++i) {
        write(*i);
    }
    end(wxT("resources"));
    end(wxT("file"));
}

void Metalink3Writer::write(const MetalinkSource& source)
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

void Metalink3Writer::write(const wxString& data, bool indent)
{
    if(indent) {
        for(int i = 0; i < indent_; i++) {
            out_ << "    ";
        }
    }
    out_ << data.mb_str(wxConvUTF8);
}

void Metalink3Writer::start(const wxString& element)
{
    write(wxT("<"));
    write(element, false);
}

void Metalink3Writer::close_start()
{
    write(wxT(">\n"), false);
    indent_++;
}

namespace {
// Escapes characters not allowed in XML documents and returns new
// escaped string.
wxString xml_escape(const wxString& src)
{
    wxString dest;
    for(wxString::const_iterator i = src.begin(), eoi = src.end();
            i != eoi; ++i) {
        const wxChar ch = *i;
        if(ch == wxT('<')) {
            dest += wxT("&lt;");
        } else if(ch == wxT('>')) {
            dest += wxT("&gt;");
        } else if(ch == wxT('&')) {
            dest += wxT("&amp;");
        } else if(ch == wxT('\'')) {
            dest += wxT("&#39;");
        } else if(ch == wxT('"')) {
            dest += wxT("&quot;");
        } else {
            dest += ch;
        }
    }
    return dest;
}
}

void Metalink3Writer::end(const wxString& element, const wxString& value)
{
    write(wxT(">"), false);
    write(xml_escape(value), false);
    write(wxT("</"), false);
    write(element, false);
    write(wxT(">\n"), false);
}

void Metalink3Writer::end(const wxString& element)
{
    indent_--;
    write(wxT("</"));
    write(element, false);
    write(wxT(">\n"), false);
}

void Metalink3Writer::add_element(const wxString& element,
                                  const wxString& value)
{
    start(element);
    end(element, value);
}

void Metalink3Writer::add_attr(const wxString& name, const wxString& value)
{
    write(wxT(" "), false);
    write(name, false);
    write(wxT("=\""), false);
    write(xml_escape(value), false);
    write(wxT("\""), false);
}
