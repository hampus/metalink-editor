#include "LicenseFrame.hpp"
#include "util.hpp"
#include <wx/html/htmlwin.h>

LicenseFrame::LicenseFrame()
    : wxFrame((wxFrame *)0, -1, wxT(""), wxDefaultPosition, wxDefaultSize)
{
    // License file
    wxStandardPaths stdpaths = get_stdpaths();
    wxFileName file(stdpaths.GetDataDir(), wxT("LICENSE.txt"));
    // Create HTML widget
    wxHtmlWindow* htmlwin = new wxHtmlWindow(this);
    htmlwin->LoadFile(file);
    // Layout
    wxBoxSizer* sizer1 = new wxBoxSizer(wxVERTICAL);
    sizer1->Add(htmlwin, 1, wxEXPAND, 0);
    SetSizerAndFit(sizer1);
    Layout();
    // Set properties
    SetTitle(wxT("Metalink Editor License"));
    SetSize(wxSize(650, 450));
}
