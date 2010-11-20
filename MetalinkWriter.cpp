#include "MetalinkWriter.hpp"
#include "config.h"

MetalinkWriter::~MetalinkWriter()
{
}

void MetalinkWriter::save(const wxString& filename)
{
    using std::ofstream;
    out_.open(filename.mb_str(wxConvFile),
              ofstream::out | ofstream::binary | ofstream::trunc);
    indent_ = 0;
    write_metalink();
}

wxString MetalinkWriter::get_generator()
{
    return wxString("MetalinkEditor/" METALINKEDITOR_VERSION, wxConvUTF8);
}

void MetalinkWriter::write_text(const wxString& data, bool indent)
{
    if(indent) {
        for(int i = 0; i < indent_; i++) {
            out_ << "    ";
        }
    }
    out_ << data.mb_str(wxConvUTF8);
}

void MetalinkWriter::start(const wxString& element)
{
    write_text(wxT("<"));
    write_text(element, false);
}

void MetalinkWriter::close_start()
{
    write_text(wxT(">\n"), false);
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

void MetalinkWriter::end(const wxString& element, const wxString& value)
{
    write_text(wxT(">"), false);
    write_text(xml_escape(value), false);
    write_text(wxT("</"), false);
    write_text(element, false);
    write_text(wxT(">\n"), false);
}

void MetalinkWriter::end(const wxString& element)
{
    indent_--;
    write_text(wxT("</"));
    write_text(element, false);
    write_text(wxT(">\n"), false);
}

void MetalinkWriter::add_element(const wxString& element,
                                  const wxString& value)
{
    if(value.empty()) return;
    start(element);
    end(element, value);
}

void MetalinkWriter::add_attr(const wxString& name, const wxString& value)
{
    write_text(wxT(" "), false);
    write_text(name, false);
    write_text(wxT("=\""), false);
    write_text(xml_escape(value), false);
    write_text(wxT("\""), false);
}
