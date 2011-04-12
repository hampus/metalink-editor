#include "MetalinkFile.hpp"

MetalinkFile::MetalinkFile(const wxString& filename)
    : filename_(filename),
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

void MetalinkFile::set_identity(const wxString& identity)
{
    identity_ = identity;
}

const wxString& MetalinkFile::get_identity() const
{
    return identity_;
}

void MetalinkFile::set_description(const wxString& description)
{
    desc_ = description;
}

const wxString& MetalinkFile::get_description() const
{
    return desc_;
}

void MetalinkFile::set_version(const wxString& version)
{
    version_ = version;
}

const wxString& MetalinkFile::get_version() const
{
    return version_;
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

void MetalinkFile::set_size(const wxString& size)
{
    size_ = size;
}

void MetalinkFile::set_size(off_t size)
{
    set_size(wxString::Format(wxT("%lld"), size));
}

const wxString& MetalinkFile::get_size() const
{
    return size_;
}

void MetalinkFile::add_file_hash(const wxString& hash_type,
                                 const wxString& value)
{
    add_file_hash(MetalinkHash(hash_type, value));
}

void MetalinkFile::add_file_hash(MetalinkHash hash)
{
    file_hashes_.push_back(hash);
}

const std::vector<MetalinkHash>& MetalinkFile::get_file_hashes() const
{
    return file_hashes_;
}

void MetalinkFile::set_file_hashes(const std::vector<MetalinkHash>& hashes)
{
    file_hashes_ = hashes;
}

void MetalinkFile::set_file_hash(long index, const MetalinkHash& hash)
{
    file_hashes_.at(index) = hash;
}

const MetalinkHash& MetalinkFile::get_file_hash(long index)
{
    return file_hashes_.at(index);
}

void MetalinkFile::del_file_hash(long index)
{
    file_hashes_.erase(file_hashes_.begin() + index);
}

void MetalinkFile::set_piece_hash(const wxString& hash_type,
                                  size_t piece_length,
                                  const std::vector<wxString>& hashes)
{
    piece_hash_type_ = hash_type;
    piece_length_ = piece_length;
    piece_hashes_ = hashes;
}

void MetalinkFile::set_piece_hash(const std::vector<wxString>& hashes)
{
    piece_hashes_ = hashes;
}

void MetalinkFile::set_piece_length(size_t piece_length)
{
    piece_length_ = piece_length;
}

void MetalinkFile::set_piece_length(wxString piece_length)
{
    wxLongLong_t length;
    if(piece_length.ToLongLong(&length)) {
        set_piece_length(length);
    }
}

const wxString& MetalinkFile::get_piece_hash_type() const
{
    return piece_hash_type_;
}

void MetalinkFile::set_piece_hash_type(const wxString& type)
{
    piece_hash_type_ = type;
}

size_t MetalinkFile::get_piece_length() const
{
    return piece_length_;
}

const std::vector<wxString>& MetalinkFile::get_piece_hashes() const
{
    return piece_hashes_;
}
