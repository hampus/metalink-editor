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
    wxString get_filename(int file);
    void add_file(wxString filename);
    void add_listener(MetalinkEditorListener* listener);
    void select(int file);
    int get_selection();
    void remove_file();
    void clear();
private:
    void update();
    std::vector<MetalinkFile> files_;
    std::vector<MetalinkEditorListener*> listeners_;
    int selection_;
};

#endif
