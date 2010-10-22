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
    void clear();
private:
    void update();
    std::vector<MetalinkFile> files_;
    std::vector<MetalinkEditorListener*> listeners_;
    int selection_;
};

#endif
