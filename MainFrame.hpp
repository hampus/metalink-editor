#ifndef MAINFRAME_HPP
#define MAINFRAME_HPP

#include "MetalinkEditorListener.hpp"
#include <wx/wx.h>
#include <wx/image.h>
#include <wx/notebook.h>
#include <wx/choice.h>

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
    void update();
private:
    void create_menu();
    void create_widgets();
    void set_properties();
    void do_layout();
    wxMenuBar* main_menubar;
    wxChoice* file_choice;
    wxStaticText* label_1;
    wxPanel* notebook_page_1;
    wxPanel* notebook_page_2;
    wxNotebook* notebook;
    DECLARE_EVENT_TABLE()
};

#endif
