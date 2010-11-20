#ifndef HASHPANEL_HPP
#define HASHPANEL_HPP

#include "MetalinkEditor.hpp"
#include <wx/wx.h>

class HashPanel : public wxPanel
{
public:
    HashPanel(wxWindow* parent, MetalinkEditor& editor);
    void update();
    void on_resize(wxSizeEvent& event);
    void on_col_resize(wxListEvent& event);
private:
    void create_widgets();
    void update_layout();
    wxListCtrl* list_;
    MetalinkEditor& editor_;
    DECLARE_EVENT_TABLE()
};

#endif
