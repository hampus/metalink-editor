#include "StartPanel.hpp"
#include <wx/stdpaths.h>
#include <wx/html/htmlwin.h>

StartPanel::StartPanel(wxWindow* parent)
    : wxPanel(parent)
{
    // HTML file
    const wxStandardPaths& stdpaths(wxStandardPaths::Get());
    wxFileName file(stdpaths.GetDataDir(), wxT("start.htm"));
    // Create HTML widget
    wxHtmlWindow* htmlwin = new wxHtmlWindow(this);
    htmlwin->LoadFile(file);
    // Layout
    wxBoxSizer* sizer1 = new wxBoxSizer(wxVERTICAL);
    sizer1->Add(htmlwin, 1, wxEXPAND, 0);
    SetSizerAndFit(sizer1);
    Layout();
}
