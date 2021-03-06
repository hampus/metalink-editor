#ifndef METALINK4WRITER_HPP
#define METALINK4WRITER_HPP

#include "MetalinkWriter.hpp"
#include "MetalinkEditor.hpp"
#include <wx/wx.h>

class Metalink4Writer : public MetalinkWriter
{
public:
    Metalink4Writer(const Metalink& metalink);
private:
    void write_metalink();
    void write_file(const MetalinkFile& file);
    void write_hashes(const MetalinkFile& file);
    void write_piece_hash(const MetalinkFile& file);
    void write_source(const MetalinkSource& source);
    const Metalink& metalink_;
};

#endif
