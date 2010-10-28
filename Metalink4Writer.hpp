#ifndef METALINK4WRITER_HPP
#define METALINK4WRITER_HPP

#include "MetalinkEditor.hpp"
#include <wx/wx.h>
#include <fstream>

class Metalink4Writer
{
public:
    Metalink4Writer(MetalinkEditor& editor);
    ~Metalink4Writer();
    void save(const wxString& filename);
private:
    void write(const MetalinkFile& file);
    void write(const MetalinkSource& source);
    void write(const wxString& data, bool indent=true);
    void start(const wxString& element);
    void close_start();
    void end(const wxString& element, const wxString& value);
    void end(const wxString& element);
    void add_element(const wxString& element, const wxString& value);
    void add_attr(const wxString& name, const wxString& value);
    MetalinkEditor& editor_;
    std::ofstream out_;
    int indent_;
};

#endif
