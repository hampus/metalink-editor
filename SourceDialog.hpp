#ifndef SOURCEDIALOG_HPP
#define SOURCEDIALOG_HPP

#include "MetalinkFile.hpp"
#include <wx/wx.h>

class SourceDialog : public wxDialog
{
public:
    SourceDialog(wxString title, MetalinkSource source);
    MetalinkSource get_source();
private:
    wxString uri_;
    wxString location_;
    wxString priority_;
    MetalinkSource source_;
};

#endif
