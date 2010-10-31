#ifndef METALINKWRITER_HPP
#define METALINKWRITER_HPP

#include <wx/wx.h>
#include <fstream>

class MetalinkWriter
{
public:
    virtual ~MetalinkWriter();
    void save(const wxString& filename);
protected:
    virtual void write_metalink()=0;
    void write_text(const wxString& data, bool indent=true);
    wxString get_generator();
    void start(const wxString& element);
    void close_start();
    void end(const wxString& element, const wxString& value);
    void end(const wxString& element);
    void add_element(const wxString& element, const wxString& value);
    void add_attr(const wxString& name, const wxString& value);
private:
    std::ofstream out_;
    int indent_;
};

#endif
