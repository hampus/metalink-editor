#include "MainFrame.hpp"
#include <wx/wx.h>

class MetalinkEditorApp: public wxApp
{
    virtual bool OnInit();
};

IMPLEMENT_APP(MetalinkEditorApp)

bool MetalinkEditorApp::OnInit()
{
    MainFrame *frame = new MainFrame();
    frame->Show(true);
    SetTopWindow(frame);
    return true;
}
