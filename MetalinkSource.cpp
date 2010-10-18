#include "MetalinkSource.hpp"

MetalinkSource::MetalinkSource(wxString uri)
    : uri_(uri), priority_(0)
{
}

wxString MetalinkSource::get_uri()
{
    return uri_;
}

wxString MetalinkSource::get_location()
{
    return location_;
}

long MetalinkSource::get_priority()
{
    return priority_;
}

wxString MetalinkSource::get_prioritystr()
{
    return wxString::Format(wxT("%li"), priority_);
}

void MetalinkSource::set_uri(wxString uri)
{
    uri_ = uri;
}

void MetalinkSource::set_location(wxString location)
{
    location_ = location;
}

void MetalinkSource::set_priority(wxString priority)
{
    if(!priority.ToLong(&priority_)) {
        priority_ = 0;
    }
    if(priority_ < 0) priority_ = 0;
    if(priority_ > 999999) priority_ = 999999;
}
