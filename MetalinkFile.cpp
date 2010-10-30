#include "MetalinkFile.hpp"

MetalinkFile::MetalinkFile(const wxString& filename)
    : filename_(filename)
{
}

void MetalinkFile::set_filename(const wxString& filename)
{
    filename_ = filename;
}

const wxString& MetalinkFile::get_filename() const
{
    return filename_;
}

void MetalinkFile::add_source(const MetalinkSource& source)
{
    sources_.push_back(source);
}

void MetalinkFile::set_source(long index, const MetalinkSource& source)
{
    sources_.at(index) = source;
}

void MetalinkFile::del_source(long index)
{
    sources_.erase(sources_.begin() + index);
}

const MetalinkSource& MetalinkFile::get_source(long index) const
{
    return sources_.at(index);
}

const std::vector<MetalinkSource>& MetalinkFile::get_sources() const
{
    return sources_;
}
