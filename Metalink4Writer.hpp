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
    void save(wxString filename);
private:
    void write(MetalinkFile& file);
    void write(MetalinkSource& source);
    void write(wxString data, bool indent=true);
    void start(wxString element);
    void close_start();
    void end(wxString element, wxString value);
    void end(wxString element);
    void addattr(wxString name, wxString value);
    MetalinkEditor& editor_;
    std::ofstream out_;
    int indent_;
};

#endif
