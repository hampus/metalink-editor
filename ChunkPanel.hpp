#ifndef CHUNKPANEL_HPP
#define CHUNKPANEL_HPP

#include "MetalinkEditor.hpp"
#include <wx/wx.h>

class ChunkPanel : public wxPanel
{
public:
    ChunkPanel(wxWindow* parent, MetalinkEditor& editor);
    void update();
    void on_delete(wxCommandEvent& event);
private:
    void create_widgets();
    wxStaticText* label1_;
    wxButton* btn_delete_;
    MetalinkEditor& editor_;
    DECLARE_EVENT_TABLE()
};

#endif
