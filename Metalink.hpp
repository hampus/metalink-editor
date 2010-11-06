#ifndef METALINK_HPP
#define METALINK_HPP

#include "MetalinkFile.hpp"
#include <wx/wx.h>
#include <vector>

class Metalink
{
public:
    int num_files() const;
    bool is_empty() const;
    void add_file(const MetalinkFile& file);
    void remove_file(int index);
    void set_file(int index, const MetalinkFile& file);
    const MetalinkFile& get_file(int index) const;
    const std::vector<MetalinkFile>& get_files() const;
    void clear();
private:
    std::vector<MetalinkFile> files_;
};

#endif
