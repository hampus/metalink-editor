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

void MetalinkFile::set_source(long index, MetalinkSource source)
{
    sources_.at(index) = source;
}

void MetalinkFile::del_source(long index)
{
    sources_.erase(sources_.begin() + index);
}

MetalinkSource MetalinkFile::get_source(long index)
{
    return sources_.at(index);
}

std::vector<MetalinkSource> MetalinkFile::get_sources()
{
    return sources_;
}
