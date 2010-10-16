#ifndef METALINKFILE_HPP
#define METALINKFILE_HPP

#include <wx/wx.h>

class MetalinkFile
{
public:
    MetalinkFile(wxString filename);
    wxString get_filename();
private:
    wxString filename_;
};

#endif
