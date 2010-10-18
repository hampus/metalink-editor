#ifndef METALINKFILE_HPP
#define METALINKFILE_HPP

#include "MetalinkSource.hpp"
#include <wx/wx.h>
#include <vector>

class MetalinkFile
{
public:
    MetalinkFile(wxString filename);
    wxString get_filename();
    void add_source(MetalinkSource source);
    std::vector<MetalinkSource> get_sources();
private:
    std::vector<MetalinkSource> sources_;
    wxString filename_;
};

#endif
