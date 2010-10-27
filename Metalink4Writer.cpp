#include "Metalink4Writer.hpp"

Metalink4Writer::Metalink4Writer(MetalinkEditor& editor)
    : editor_(editor)
{
}

Metalink4Writer::~Metalink4Writer()
{
    if(out_.is_open()) out_.close();
}

void Metalink4Writer::save(wxString filename)
{
    using std::ofstream;
    out_.open(filename.mb_str(wxConvFile),
              ofstream::out | ofstream::binary | ofstream::trunc);
    indent_ = 0;
    write(wxT("<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"));
    write(wxT("<metalink xmlns=\"urn:ietf:params:xml:ns:metalink\">\n"));
    indent_++;
    std::vector<MetalinkFile> files = editor_.get_files();
    for(int i = 0; i < files.size(); i++) {
        write(files.at(i));
    }
    indent_--;
    write(wxT("</metalink>\n"));
}

void Metalink4Writer::write(MetalinkFile& file)
{
    start(wxT("file"));
    addattr(wxT("name"), file.get_filename());
    close_start();
    std::vector<MetalinkSource> sources = file.get_sources();
    for(int i = 0; i < sources.size(); i++) {
        write(sources.at(i));
    }
    end(wxT("file"));
}

void Metalink4Writer::write(MetalinkSource& source)
{
    start(wxT("url"));
    if(!source.get_location().empty()) {
        addattr(wxT("location"), source.get_location());
    }
    if(!source.get_prioritystr().empty()) {
        addattr(wxT("priority"), source.get_prioritystr());
    }
    end(wxT("url"), source.get_uri());
}

void Metalink4Writer::write(wxString data, bool indent)
{
    if(indent) {
        for(int i = 0; i < indent_; i++) {
            out_ << "    ";
        }
    }
    out_ << data.mb_str(wxConvUTF8);
}

void Metalink4Writer::start(wxString element)
{
    write(wxT("<"));
    write(element, false);
}

void Metalink4Writer::close_start()
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

void Metalink4Writer::end(wxString element, wxString value)
{
    write(wxT(">"), false);
    write(xml_escape(value), false);
    write(wxT("</"), false);
    write(element, false);
    write(wxT(">\n"), false);
}

void Metalink4Writer::end(wxString element)
{
    indent_--;
    write(wxT("</"));
    write(element, false);
    write(wxT(">\n"), false);
}

void Metalink4Writer::addattr(wxString name, wxString value)
{
    write(wxT(" "), false);
    write(name, false);
    write(wxT("=\""), false);
    write(xml_escape(value), false);
    write(wxT("\""), false);
}
