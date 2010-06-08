#include "MetalinkEditor.hpp"

MetalinkEditor::MetalinkEditor()
{
    _file = 0;
}

void MetalinkEditor::add_listener(MetalinkEditorListener* listener)
{
    _listeners.push_back(listener);
}

void MetalinkEditor::update()
{
    for(int i = 0; i < _listeners.size(); i++) {
        _listeners.at(i)->update();
    }
}

void MetalinkEditor::add_file(wxString name)
{
    // Add file
    MetalinkFile f;
    f.name = name;
    _ml.files.push_back(f);
    // Update selection
    _file = _ml.files.size() - 1;
    // Call listeners
    update();
}

void MetalinkEditor::remove_file()
{
    if(_ml.files.size() == 0) return;
    _ml.files.erase(_ml.files.begin() + _file);
    if(_file > _ml.files.size() - 1) {
        _file = _ml.files.size() - 1;
    }
    update();
}

void MetalinkEditor::reset()
{
    _ml = Metalink();
    _file = 0;
    update();
}

wxArrayString MetalinkEditor::get_filenames()
{
    wxArrayString list;
    for(int i = 0; i < _ml.files.size(); i++) {
        list.Add(_ml.files.at(i).name);
    }
    return list;
}

// Return the index of the currently selected file.
int MetalinkEditor::get_selection()
{
    return _file;
}

// Set a file as the currently selected one.
void MetalinkEditor::set_selection(int i)
{
    _file = i;
    update();
}

int MetalinkEditor::get_file_count()
{
    return _ml.files.size();
}
