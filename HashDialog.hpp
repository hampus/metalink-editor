#ifndef HASHDIALOG_HPP
#define HASHDIALOG_HPP

#include "MetalinkFile.hpp"
#include <wx/wx.h>

class HashDialog : public wxDialog
{
public:
    HashDialog(const wxString& title, const MetalinkHash& hash);
    MetalinkHash get_hash() const;
private:
    wxString type_;
    wxString value_;
    const MetalinkHash& hash_;
};

#endif
