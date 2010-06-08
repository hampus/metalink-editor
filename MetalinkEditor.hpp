#ifndef METALINKEDITOR_HPP
#define METALINKEDITOR_HPP

#include "MetalinkEditorListener.hpp"
#include "metalink.hpp"
#include <wx/wx.h>
#include <vector>

class MetalinkEditor
{
public:
    MetalinkEditor();
    void add_listener(MetalinkEditorListener* listener);
    void add_file(wxString name);
    void remove_file();
    void reset();
    wxArrayString get_filenames();
    int get_selection();
    void set_selection(int i);
    int get_file_count();
private:
    void update();
    Metalink _ml;
    int _file;
    std::vector<MetalinkEditorListener*> _listeners;
};

#endif
