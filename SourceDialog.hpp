#ifndef SOURCEDIALOG_HPP
#define SOURCEDIALOG_HPP

#include "MetalinkFile.hpp"
#include <wx/wx.h>

class SourceDialog : public wxDialog
{
public:
    SourceDialog(const wxString& title, const MetalinkSource& source);
    MetalinkSource get_source() const;
private:
    wxString uri_;
    wxString location_;
    wxString priority_;
    bool torrent_;
    MetalinkSource source_;
};

#endif
