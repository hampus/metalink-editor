#include "MetalinkSource.hpp"

MetalinkSource::MetalinkSource(const wxString& uri)
    : uri_(uri), priority_(0)
{
}

const wxString& MetalinkSource::get_uri() const
{
    return uri_;
}

const wxString& MetalinkSource::get_location() const
{
    return location_;
}

long MetalinkSource::get_priority() const
{
    return priority_;
}

wxString MetalinkSource::get_prioritystr() const
{
    if(priority_ == 0) return wxString(wxT(""));
    return wxString::Format(wxT("%li"), priority_);
}

void MetalinkSource::set_uri(const wxString& uri)
{
    uri_ = uri;
}

void MetalinkSource::set_location(const wxString& location)
{
    location_ = location;
}

void MetalinkSource::set_priority(const wxString& priority)
{
    if(!priority.ToLong(&priority_)) {
        priority_ = 0;
    }
    if(priority_ < 0) priority_ = 0;
    if(priority_ > 999999) priority_ = 999999;
}
