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
    void write_source(const MetalinkSource& source);
    const Metalink& metalink_;
};

#endif
