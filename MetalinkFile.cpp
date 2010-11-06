#include "MetalinkFile.hpp"

MetalinkFile::MetalinkFile(const wxString& filename)
    : filename_(filename),
      size_(-1),
      piece_length_(0)
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

void MetalinkFile::set_size(off_t size)
{
    size_ = size;
}

off_t MetalinkFile::get_size() const
{
    return size_;
}

void MetalinkFile::add_file_hash(const wxString& hash_type,
                                 const wxString& value)
{
    file_hashes_.push_back(std::make_pair(hash_type, value));
}

const std::vector<std::pair<wxString, wxString> >&
MetalinkFile::get_file_hashes() const
{
    return file_hashes_;
}

void MetalinkFile::set_piece_hash(const wxString& hash_type,
                                  size_t piece_length,
                                  const std::vector<wxString>& hashes)
{
    piece_hash_type_ = hash_type;
    piece_length_ = piece_length;
    piece_hashes_ = hashes;
}

const wxString& MetalinkFile::get_piece_hash_type() const
{
    return piece_hash_type_;
}

size_t MetalinkFile::get_piece_length() const
{
    return piece_length_;
}

const std::vector<wxString>& MetalinkFile::get_piece_hashes() const
{
    return piece_hashes_;
}
