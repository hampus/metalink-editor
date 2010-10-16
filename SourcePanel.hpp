#ifndef SOURCEPANEL_HPP
#define SOURCEPANEL_HPP

#include "MetalinkEditor.hpp"
#include <wx/wx.h>

class SourcePanel : public wxPanel
{
public:
    SourcePanel(wxWindow* parent, MetalinkEditor& editor);
    void update();
private:
    MetalinkEditor& editor_;
};

#endif
