#include "MetalinkFile.hpp"

MetalinkFile::MetalinkFile(wxString filename)
    : filename_(filename)
{
}

wxString MetalinkFile::get_filename()
{
    return filename_;
}
