#include "MetalinkFile.hpp"

MetalinkFile::MetalinkFile(wxString filename)
    : filename_(filename)
{
}

wxString MetalinkFile::get_filename()
{
    return filename_;
}

void MetalinkFile::add_source(MetalinkSource source)
{
    sources_.push_back(source);
}

std::vector<MetalinkSource> MetalinkFile::get_sources()
{
    return sources_;
}
