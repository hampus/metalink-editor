#ifndef METALINKFILE_HPP
#define METALINKFILE_HPP

#include "MetalinkSource.hpp"
#include "MetalinkHash.hpp"
#include <wx/wx.h>
#include <vector>

class MetalinkFile
{
public:
    MetalinkFile(const wxString& filename = wxT(""));
    const wxString& get_filename() const;
    void set_filename(const wxString& filename);
    const wxString& get_identity() const;
    void set_identity(const wxString& filename);
    const wxString& get_description() const;
    void set_description(const wxString& description);
    const wxString& get_version() const;
    void set_version(const wxString& version);
    void add_source(const MetalinkSource& source);
    void set_source(long index, const MetalinkSource& source);
    void del_source(long index);
    const MetalinkSource& get_source(long index) const;
    const std::vector<MetalinkSource>& get_sources() const;
    void set_size(off_t length);
    void set_size(const wxString& length);
    const wxString& get_size() const;
    void add_file_hash(const wxString& hash_type, const wxString& value);
    const std::vector<MetalinkHash>& get_file_hashes() const;
    void set_file_hashes(const std::vector<MetalinkHash>& hashes);
    void set_piece_hash(const wxString& hash_type,
                        size_t piece_length,
                        const std::vector<wxString>& hashes);
    const wxString& get_piece_hash_type() const;
    void set_piece_hash_type(const wxString& type);
    size_t get_piece_length() const;
    const std::vector<wxString>& get_piece_hashes() const;
private:
    std::vector<MetalinkSource> sources_;
    wxString filename_;
    wxString identity_;
    wxString desc_;
    wxString version_;
    wxString size_;
    std::vector<MetalinkHash> file_hashes_;
    wxString piece_hash_type_;
    size_t piece_length_;
    std::vector<wxString> piece_hashes_;
};

#endif
