#include "MainFrame.hpp"
#include <wx/wx.h>
#include <wx/image.h>

class MetalinkEditorApp: public wxApp
{
    virtual bool OnInit();
};

IMPLEMENT_APP(MetalinkEditorApp)

bool MetalinkEditorApp::OnInit()
{
    wxInitAllImageHandlers();
    MainFrame* frame = new MainFrame();
    frame->Show(true);
    SetTopWindow(frame);
    return true;
}
