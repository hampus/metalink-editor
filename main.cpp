#include "MainFrame.hpp"
#include "config.h"
#include <wx/wx.h>
#include <wx/image.h>
#include <wx/stdpaths.h>

class MetalinkEditorApp: public wxApp
{
    bool OnInit();
    wxString GetAppName();
};

IMPLEMENT_APP(MetalinkEditorApp)

bool MetalinkEditorApp::OnInit()
{
#ifdef __UNIX__
    wxStandardPaths::Get().SetInstallPrefix(wxT(CMAKE_INSTALL_PREFIX));
#endif

    wxInitAllImageHandlers();

    MainFrame* frame = new MainFrame();
    frame->Show(true);
    SetTopWindow(frame);

    return true;
}

wxString MetalinkEditorApp::GetAppName()
{
    return wxT("metalinkeditor");
}
