#ifndef METALINKSOURCE_HPP
#define METALINKSOURCE_HPP

#include <wx/wx.h>

class MetalinkSource
{
public:
    MetalinkSource(const wxString& uri = wxT(""));
    const wxString& get_uri() const;
    const wxString& get_location() const;
    long get_priority() const;
    wxString get_prioritystr() const;
    void set_uri(const wxString& uri);
    void set_location(const wxString& location);
    void set_priority(const wxString& priority);
private:
    wxString uri_;
    wxString location_;
    long priority_;
};

#endif
