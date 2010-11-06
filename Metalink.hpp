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
    void save(const wxString& filename);
    static Metalink load(const wxString& filename);
private:
    static bool load_metalink4(const wxString& filename, Metalink* metalink);
    static bool load_metalink3(const wxString& filename, Metalink* metalink);
    std::vector<MetalinkFile> files_;
};

class MetalinkLoadError: public std::exception
{
public:
    MetalinkLoadError(const char* msg = "Failed to load Metalink.") : msg_(msg) {}
    virtual const char* what() const throw()
    {
        return msg_;
    }
private:
    const char* msg_;
};

#endif
