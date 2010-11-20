#ifndef METALINK3WRITER_HPP
#define METALINK3WRITER_HPP

#include "MetalinkWriter.hpp"
#include "MetalinkEditor.hpp"
#include <wx/wx.h>

class Metalink3Writer : public MetalinkWriter
{
public:
    Metalink3Writer(const Metalink& metalink);
private:
    virtual void write_metalink();
    void write_file(const MetalinkFile& file);
    void write_verification(const MetalinkFile& file);
    bool has_hashes(const MetalinkFile& file);
    bool has_piece_hashes(const MetalinkFile& file);
    void write_hashes(const MetalinkFile& file);
    void write_piece_hashes(const MetalinkFile& file);
    void write_source(const MetalinkSource& source);
    MetalinkFile convert_hash_types(const MetalinkFile& file);
    const wxString convert_hash_type(const wxString& type);
    const Metalink& metalink_;
};

#endif
