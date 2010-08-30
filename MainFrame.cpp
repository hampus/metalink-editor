#include "MainFrame.hpp"
#include "util.hpp"
#include <wx/filename.h>
#include <wx/aboutdlg.h>
#include <iostream>

enum
{
    ID_Quit = 1,
    ID_About,
};

BEGIN_EVENT_TABLE(MainFrame, wxFrame)
    EVT_MENU(ID_Quit, MainFrame::on_quit)
    EVT_MENU(ID_About, MainFrame::on_about)
END_EVENT_TABLE()

wxString get_resource_filename()
{
    wxStandardPaths stdp = get_stdpaths();
    wxFileName filename(stdp.GetDataDir(), wxT("resources.xrc"));
    return filename.GetFullPath();
}

MainFrame::MainFrame()
    : wxFrame((wxFrame *)0, -1, wxT(""), wxDefaultPosition, wxDefaultSize)
{
    create_menu();
    create_widgets();
    set_properties();
    do_layout();
}

void MainFrame::create_widgets()
{
    file_choice = new wxChoice(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0, NULL, 0);
    notebook = new wxNotebook(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0);
    notebook_page_1 = new wxPanel(notebook, wxID_ANY);
    label_1 = new wxStaticText(notebook_page_1, wxID_ANY, wxT("Welcome to Metalink Editor 2\n\nThis is an empty metalink. Get started by either opening an existing metalink\nor adding a file to this one. You can add a file from the metalink menu.\n"), wxDefaultPosition, wxDefaultSize, wxST_NO_AUTORESIZE);
    notebook_page_2 = new wxPanel(notebook, wxID_ANY);
    notebook->AddPage(notebook_page_1, wxT("Welcome"));
    notebook->AddPage(notebook_page_2, wxT("Sources"));
}

void MainFrame::create_menu()
{
    main_menubar = new wxMenuBar();
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
    menu_help->Append(ID_About, wxT("About"), wxEmptyString, wxITEM_NORMAL);
    main_menubar->Append(menu_help, wxT("Help"));
    SetMenuBar(main_menubar);
}

void MainFrame::set_properties()
{
    SetTitle(wxT("Metalink Editor"));
    SetSize(wxSize(420, 412));
}


void MainFrame::do_layout()
{
    wxBoxSizer* sizer_1 = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer* sizer_2 = new wxBoxSizer(wxVERTICAL);
    sizer_1->Add(file_choice, 0, wxEXPAND, 0);
    sizer_2->Add(label_1, 1, wxALL|wxEXPAND, 10);
    notebook_page_1->SetSizer(sizer_2);
    sizer_1->Add(notebook, 1, wxEXPAND, 0);
    SetSizer(sizer_1);
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
