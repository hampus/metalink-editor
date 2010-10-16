#ifndef MAINFRAME_HPP
#define MAINFRAME_HPP

#include "MetalinkEditor.hpp"
#include "MetalinkEditorListener.hpp"
#include <wx/wx.h>
#include <wx/image.h>
#include <wx/notebook.h>
#include <wx/choice.h>

class MainFrame: public wxFrame, public MetalinkEditorListener
{
public:
    MainFrame();
    void on_quit(wxCommandEvent& event);
    void on_about(wxCommandEvent& event);
    void on_license(wxCommandEvent& event);
    void on_add_file(wxCommandEvent& event);
    void on_del_file(wxCommandEvent& event);
    void on_file_select(wxCommandEvent& event);
    void on_new(wxCommandEvent& event);
    void update();
private:
    void create_menu();
    void create_widgets();
    void update_start(bool force=false);
    wxChoice* file_choice_;
    wxNotebook* notebook_;
    MetalinkEditor editor_;
    bool start_; // Are we showing the "start page"?
    DECLARE_EVENT_TABLE()
};

#endif
