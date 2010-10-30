#ifndef METALINKFILE_HPP
#define METALINKFILE_HPP

#include "MetalinkSource.hpp"
#include <wx/wx.h>
#include <vector>

class MetalinkFile
{
public:
    MetalinkFile(const wxString& filename = wxT(""));
    const wxString& get_filename() const;
    void set_filename(const wxString& filename);
    void add_source(const MetalinkSource& source);
    void set_source(long index, const MetalinkSource& source);
    void del_source(long index);
    const MetalinkSource& get_source(long index) const;
    const std::vector<MetalinkSource>& get_sources() const;
private:
    std::vector<MetalinkSource> sources_;
    wxString filename_;
};

#endif
