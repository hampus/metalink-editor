#include "MainFrame.hpp"
#include "util.hpp"
#include <wx/xrc/xmlres.h>
#include <wx/filename.h>
#include <wx/aboutdlg.h>
#include <iostream>

BEGIN_EVENT_TABLE(MainFrame, wxFrame)
    EVT_MENU(XRCID("menu_exit"),  MainFrame::on_quit)
    EVT_MENU(XRCID("menu_about"),  MainFrame::on_about)
    EVT_MENU(XRCID("metalink_add_file"),  MainFrame::on_add_file)
    EVT_MENU(XRCID("metalink_del_file"),  MainFrame::on_del_file)
    EVT_MENU(XRCID("metalink_new"),  MainFrame::on_new)
    EVT_CHOICE(XRCID("file_choice"), MainFrame::on_file_select)
END_EVENT_TABLE()

wxString get_resource_filename()
{
    wxStandardPaths stdp = get_stdpaths();
    wxFileName filename(stdp.GetDataDir(), wxT("resources.xrc"));
    return filename.GetFullPath();
}

MainFrame::MainFrame()
{
    wxXmlResource::Get()->InitAllHandlers();
    wxXmlResource::Get()->Load(get_resource_filename());
    wxXmlResource::Get()->LoadFrame(this, (wxFrame*)0, wxT("main_frame"));
    _notebook = (wxNotebook*)wxWindow::FindWindowByName(wxT("notebook"));
    _choice = (wxChoice*)wxWindow::FindWindowByName(wxT("file_choice"));
    _editor.add_listener(this);
    init_tabs();
    show_welcome_screen();
    SetSize(400, 450);
}

void MainFrame::on_quit(wxCommandEvent& WXUNUSED(event))
{
    Close(true);
}

void MainFrame::on_about(wxCommandEvent& WXUNUSED(event))
{
    wxAboutDialogInfo info;
    info.SetName(_T("Metalink Editor"));
    info.SetVersion(_T("2.0pre0"));
    info.SetDescription(_T("This is a preview of Metalink Editor 2.0"));
    info.AddDeveloper(_T("Hampus Wessman <hampus.wessman@gmail.com>"));
    wxAboutBox(info);
}

void MainFrame::on_add_file(wxCommandEvent& WXUNUSED(event))
{
    wxString filename = wxGetTextFromUser(
        wxT("Please enter a file name:"),
        wxT("Add empty file to metalink")
    );
    if(filename == wxT("")) return;
    _editor.add_file(filename);
}

void MainFrame::on_del_file(wxCommandEvent& WXUNUSED(event))
{
    int answer = wxMessageBox(
        wxT("Remove currently selected file from metalink?"),
        wxT("Remove file"),
        wxOK | wxCANCEL | wxICON_EXCLAMATION
    );
    if(answer == wxCANCEL) return;
    _editor.remove_file();
}

void MainFrame::on_file_select(wxCommandEvent& event)
{
    _editor.set_selection(event.GetSelection());
}

void MainFrame::on_new(wxCommandEvent& WXUNUSED(event))
{
    _editor.reset();
}

void MainFrame::update()
{
    _choice->Clear();
    // Show welcome screen?
    if(_editor.get_file_count() == 0) {
        show_welcome_screen();
        return;
    }
    show_edit_screen();
    // Update file choice
    wxArrayString filenames = _editor.get_filenames();
    _choice->Append(filenames);
    _choice->SetSelection(_editor.get_selection());
}

void MainFrame::show_welcome_screen()
{
    hide_tabs();
    show_tab(0);
}

void MainFrame::show_edit_screen()
{
    hide_tabs();
    for(int i = 1; i < _tabs.size(); i++) {
        show_tab(i);
    }
}

void MainFrame::init_tabs()
{
    int num = (int)_notebook->GetPageCount();
    for(int i = 0; i < num; i++) {
        NotebookTab tab;
        tab.page = _notebook->GetPage(i);
        tab.text = _notebook->GetPageText(i);
        _tabs.push_back(tab);
    }
}

void MainFrame::show_tab(int i)
{
    NotebookTab tab = _tabs.at(i);
    _notebook->AddPage(tab.page, tab.text);
}

void MainFrame::hide_tabs()
{
    while(_notebook->GetPageCount() > 0) { 
        _notebook->RemovePage(0);
    }
}
