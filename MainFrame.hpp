#ifndef MAINFRAME_HPP
#define MAINFRAME_HPP

#include "MetalinkEditor.hpp"
#include "MetalinkEditorListener.hpp"
#include <wx/wx.h>
#include <wx/notebook.h>
#include <wx/choice.h>
#include <vector>

struct NotebookTab {
    wxNotebookPage* page;
    wxString text;
};

class MainFrame: public wxFrame, public MetalinkEditorListener
{
public:
    MainFrame();
    void on_quit(wxCommandEvent& event);
    void on_about(wxCommandEvent& event);
    void on_add_file(wxCommandEvent& event);
    void on_del_file(wxCommandEvent& event);
    void on_file_select(wxCommandEvent& event);
    void on_new(wxCommandEvent& event);
    void show_welcome_screen();
    void show_edit_screen();
    void update();
private:
    void init_tabs();
    void hide_tabs();
    void show_tab(int i);
    MetalinkEditor _editor;
    wxNotebook* _notebook;
    wxChoice* _choice;
    std::vector<NotebookTab> _tabs;
    DECLARE_EVENT_TABLE()
};

#endif
