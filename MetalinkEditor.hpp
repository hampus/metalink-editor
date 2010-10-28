#ifndef METALINKEDITOR_HPP
#define METALINKEDITOR_HPP

#include "MetalinkFile.hpp"
#include "MetalinkEditorListener.hpp"
#include <wx/wx.h>
#include <vector>

class MetalinkEditor
{
public:
    MetalinkEditor();
    bool is_empty();
    int num_files();
    void add_file(wxString filename);
    void add_file(MetalinkFile file);
    void add_listener(MetalinkEditorListener* listener);
    void remove_file();
    void select(int file);
    int get_selection();
    wxString get_filename(int file);
    MetalinkFile get_file();
    std::vector<MetalinkFile> get_files();
    void set_file(MetalinkFile& file);
    wxString get_filename();
    void set_filename(wxString filename);
    void save();
    void open(wxString filename);
    void clear();
private:
    void update();
    bool load_metalink4(wxString filename);
    bool load_metalink3(wxString filename);
    std::vector<MetalinkFile> files_;
    std::vector<MetalinkEditorListener*> listeners_;
    int selection_;
    wxString filename_;
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
