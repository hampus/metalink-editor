#ifndef METALINKEDITOR_HPP
#define METALINKEDITOR_HPP

#include "Metalink.hpp"
#include "MetalinkEditorListener.hpp"
#include <wx/wx.h>
#include <vector>

class MetalinkEditor
{
public:
    MetalinkEditor();
    bool is_empty() const;
    int num_files() const;
    void add_file(const wxString& filename);
    void add_file(const MetalinkFile& file);
    void add_listener(MetalinkEditorListener* listener);
    void remove_file();
    void select(int file);
    int get_selection() const;
    const wxString& get_filename(int file) const;
    const MetalinkFile& get_file() const;
    const std::vector<MetalinkFile>& get_files() const;
    void set_file(const MetalinkFile& file);
    const wxString& get_filename() const;
    void set_filename(const wxString& filename);
    void save();
    void open(const wxString& filename);
    void clear();
private:
    void update();
    bool load_metalink4(const wxString& filename);
    bool load_metalink3(const wxString& filename);
    std::vector<MetalinkEditorListener*> listeners_;
    Metalink metalink_;
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
