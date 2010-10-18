#include "MetalinkSource.hpp"

MetalinkSource::MetalinkSource(wxString uri)
    : uri_(uri)
{
}

wxString MetalinkSource::get_uri()
{
    return uri_;
}

void MetalinkSource::set_uri(wxString uri)
{
    uri_ = uri;
}
