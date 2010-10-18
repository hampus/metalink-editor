#ifndef METALINKSOURCE_HPP
#define METALINKSOURCE_HPP

#include <wx/wx.h>

class MetalinkSource
{
public:
    MetalinkSource(wxString uri = wxT(""));
    wxString get_uri();
    wxString get_location();
    long get_priority();
    wxString get_prioritystr();
    void set_uri(wxString uri);
    void set_location(wxString location);
    void set_priority(wxString priority);
private:
    wxString uri_;
    wxString location_;
    long priority_;
};

#endif
