#include "LicenseFrame.hpp"
#include <wx/stdpaths.h>
#include <wx/html/htmlwin.h>

LicenseFrame::LicenseFrame()
    : wxFrame((wxFrame *)0, -1, wxT(""), wxDefaultPosition, wxDefaultSize)
{
    // License file
    const wxStandardPaths& stdpaths(wxStandardPaths::Get());
    wxFileName file(stdpaths.GetDataDir(), wxT("legal.htm"));
    // Create HTML widget
    wxHtmlWindow* htmlwin = new wxHtmlWindow(this);
    htmlwin->LoadFile(file);
    // Set icon
#if defined(__WXMSW__)
    wxIcon icon(wxT("metalink"), wxBITMAP_TYPE_ICO_RESOURCE);
#else
    wxFileName icon_name(stdpaths.GetDataDir(), wxT("metalink.png"));
    wxBitmap bmp(icon_name.GetFullPath(), wxBITMAP_TYPE_ANY);
    wxIcon icon;
    icon.CopyFromBitmap(bmp);
#endif
    SetIcon(icon);
    // Layout
    wxBoxSizer* sizer1 = new wxBoxSizer(wxVERTICAL);
    sizer1->Add(htmlwin, 1, wxEXPAND, 0);
    SetSizerAndFit(sizer1);
    Layout();
    // Set properties
    SetTitle(wxT("Legal information"));
    SetSize(wxSize(675, 500));
}
