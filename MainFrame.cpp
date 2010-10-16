#include "MainFrame.hpp"
#include "LicenseFrame.hpp"
#include "util.hpp"
#include "common.hpp"
#include <wx/filename.h>
#include <wx/aboutdlg.h>
#include <iostream>

BEGIN_EVENT_TABLE(MainFrame, wxFrame)
    EVT_MENU(ID_Quit, MainFrame::on_quit)
    EVT_MENU(ID_About, MainFrame::on_about)
    EVT_MENU(ID_License, MainFrame::on_license)
END_EVENT_TABLE()

MainFrame::MainFrame()
    : wxFrame((wxFrame *)0, -1, wxT(""), wxDefaultPosition, wxDefaultSize)
{
    create_menu();
    create_widgets();
    // Set properties
    SetTitle(wxT("Metalink Editor"));
    SetSize(wxSize(420, 412));
}

void MainFrame::create_menu()
{
    wxMenuBar* main_menubar = new wxMenuBar();
    wxMenu* menu_file = new wxMenu();
    menu_file->Append(wxID_ANY, wxT("New"), wxEmptyString, wxITEM_NORMAL);
    menu_file->AppendSeparator();
    menu_file->Append(ID_Quit, wxT("Exit"), wxEmptyString, wxITEM_NORMAL);
    main_menubar->Append(menu_file, wxT("File"));
    wxMenu* menu_metalink = new wxMenu();
    menu_metalink->Append(wxID_ANY, wxT("Add file..."), wxEmptyString, wxITEM_NORMAL);
    menu_metalink->Append(wxID_ANY, wxT("Remove file..."), wxEmptyString, wxITEM_NORMAL);
    main_menubar->Append(menu_metalink, wxT("Metalink"));
    wxMenu* menu_help = new wxMenu();
    menu_help->Append(ID_License, wxT("License"), wxEmptyString, wxITEM_NORMAL);
    menu_help->Append(ID_About, wxT("About"), wxEmptyString, wxITEM_NORMAL);
    main_menubar->Append(menu_help, wxT("Help"));
    SetMenuBar(main_menubar);
}

void MainFrame::create_widgets()
{
    // Create widgets
    file_choice_ = new wxChoice(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0, NULL, 0);
    notebook_ = new wxNotebook(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0);
    if(editor_.is_empty()) {
        wxPanel* notebook_page1 = new wxPanel(notebook_, wxID_ANY);
        wxStaticText* label1 = new wxStaticText(notebook_page1, wxID_ANY, wxT("Welcome to Metalink Editor 2\n\nThis is an empty metalink. Get started by either opening\nan existing metalink or adding a file to this one. You can\nadd a file from the metalink menu."), wxDefaultPosition, wxDefaultSize, wxST_NO_AUTORESIZE);
        notebook_->AddPage(notebook_page1, wxT("Start"));
        // Layout
        wxBoxSizer* sizer2 = new wxBoxSizer(wxVERTICAL);
        sizer2->Add(label1, 1, wxALL|wxEXPAND, 10);
        notebook_page1->SetSizer(sizer2);
    } else {
        wxPanel* notebook_page2 = new wxPanel(notebook_, wxID_ANY);
        notebook_->AddPage(notebook_page2, wxT("Sources"));
    }
    // Layout
    wxBoxSizer* sizer1 = new wxBoxSizer(wxVERTICAL);
    sizer1->Add(file_choice_, 0, wxEXPAND, 0);
    sizer1->Add(notebook_, 1, wxEXPAND, 0);
    SetSizerAndFit(sizer1);
    Layout();
}

void MainFrame::on_quit(wxCommandEvent& WXUNUSED(event))
{
    Close(true);
}

void MainFrame::on_about(wxCommandEvent& WXUNUSED(event))
{
    wxAboutDialogInfo info;
    info.SetName(_T("Metalink Editor"));
    info.SetVersion(_T("2.0dev"));
    info.SetDescription(_T("This is a preview of Metalink Editor 2.0"));
    info.AddDeveloper(_T("Hampus Wessman <hampus.wessman@gmail.com>"));
    wxAboutBox(info);
}

void MainFrame::on_license(wxCommandEvent& WXUNUSED(event))
{
    LicenseFrame* frame = new LicenseFrame();
    frame->Show(true);
}

void MainFrame::on_add_file(wxCommandEvent& WXUNUSED(event))
{
    wxString filename = wxGetTextFromUser(
        wxT("Please enter a file name:"),
        wxT("Add empty file to metalink")
    );
    if(filename == wxT("")) return;
    // TODO
}

void MainFrame::on_del_file(wxCommandEvent& WXUNUSED(event))
{
    int answer = wxMessageBox(
        wxT("Remove currently selected file from metalink?"),
        wxT("Remove file"),
        wxOK | wxCANCEL | wxICON_EXCLAMATION
    );
    if(answer == wxCANCEL) return;
    // TODO
}

void MainFrame::on_file_select(wxCommandEvent& event)
{
    // TODO
}

void MainFrame::on_new(wxCommandEvent& WXUNUSED(event))
{
    // TODO
}

void MainFrame::update()
{
    // TODO
}
