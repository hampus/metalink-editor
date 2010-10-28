#include "Metalink4Writer.hpp"
#include "config.h"

Metalink4Writer::Metalink4Writer(MetalinkEditor& editor)
    : editor_(editor)
{
}

Metalink4Writer::~Metalink4Writer()
{
}

void Metalink4Writer::save(const wxString& filename)
{
    using std::ofstream;
    out_.open(filename.mb_str(wxConvFile),
              ofstream::out | ofstream::binary | ofstream::trunc);
    indent_ = 0;
    write(wxT("<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"));
    write(wxT("<metalink xmlns=\"urn:ietf:params:xml:ns:metalink\">\n"));
    indent_++;
    wxString generator("MetalinkEditor/" METALINKEDITOR_VERSION, wxConvUTF8);
    add_element(wxT("generator"), generator);
    const std::vector<MetalinkFile>& files = editor_.get_files();
    for(std::vector<MetalinkFile>::const_iterator i = files.begin(),
            eoi = files.end(); i != eoi; ++i) {
        write(*i);
    }
    indent_--;
    write(wxT("</metalink>\n"));
}

void Metalink4Writer::write(const MetalinkFile& file)
{
    start(wxT("file"));
    addattr(wxT("name"), file.get_filename());
    close_start();
    const std::vector<MetalinkSource>& sources = file.get_sources();
    for(std::vector<MetalinkSource>::const_iterator i = sources.begin(),
            eoi = sources.end(); i != eoi; ++i) {
        write(*i);
    }
    end(wxT("file"));
}

void Metalink4Writer::write(const MetalinkSource& source)
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

void Metalink4Writer::write(const wxString& data, bool indent)
{
    if(indent) {
        for(int i = 0; i < indent_; i++) {
            out_ << "    ";
        }
    }
    out_ << data.mb_str(wxConvUTF8);
}

void Metalink4Writer::start(const wxString& element)
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

void Metalink4Writer::end(const wxString& element, const wxString& value)
{
    write(wxT(">"), false);
    write(xml_escape(value), false);
    write(wxT("</"), false);
    write(element, false);
    write(wxT(">\n"), false);
}

void Metalink4Writer::end(const wxString& element)
{
    indent_--;
    write(wxT("</"));
    write(element, false);
    write(wxT(">\n"), false);
}

void Metalink4Writer::add_element(const wxString& element,
                                  const wxString& value)
{
    start(element);
    end(element, value);
}

void Metalink4Writer::addattr(const wxString& name, const wxString& value)
{
    write(wxT(" "), false);
    write(name, false);
    write(wxT("=\""), false);
    write(xml_escape(value), false);
    write(wxT("\""), false);
}
