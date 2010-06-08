#ifndef METALINK_HPP
#define METALINK_HPP

#include <wx/wx.h>
#include <vector>

struct MetalinkFile
{
    wxString name;
};

struct Metalink
{
    std::vector<MetalinkFile> files;
};

#endif
