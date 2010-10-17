#ifndef SOURCEPANEL_HPP
#define SOURCEPANEL_HPP

#include "MetalinkEditor.hpp"
#include <wx/wx.h>
#include <wx/listctrl.h>

class SourcePanel : public wxPanel
{
public:
    SourcePanel(wxWindow* parent, MetalinkEditor& editor);
    void update();
    void on_resize(wxSizeEvent& event);
    void on_col_resize(wxListEvent& event);
    void on_add(wxCommandEvent& event);
    void on_edit(wxCommandEvent& event);
    void on_del(wxCommandEvent& event);
private:
    void create_widgets();
    wxListCtrl* list_;
    MetalinkEditor& editor_;
    DECLARE_EVENT_TABLE()
};

#endif
