#ifndef METALINKSOURCE_HPP
#define METALINKSOURCE_HPP

#include <wx/wx.h>

class MetalinkSource
{
public:
    MetalinkSource(wxString uri = wxT(""));
    wxString get_uri();
    void set_uri(wxString uri);
private:
    wxString uri_;
};

#endif
