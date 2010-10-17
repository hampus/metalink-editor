#ifndef METALINKFILE_HPP
#define METALINKFILE_HPP

#include <wx/wx.h>
#include <vector>

struct MetalinkSource
{
    MetalinkSource(wxString uri) : uri(uri) {}
    wxString uri;
};

struct MetalinkFile
{
    MetalinkFile(wxString filename);
    std::vector<MetalinkSource> sources;
    wxString filename;
};

#endif
