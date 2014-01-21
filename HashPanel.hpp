#ifndef HASHPANEL_HPP
#define HASHPANEL_HPP

#include "MetalinkEditor.hpp"
#include <wx/wx.h>
#include <wx/listctrl.h>

class HashPanel : public wxPanel
{
public:
    HashPanel(wxWindow* parent, MetalinkEditor& editor);
    void update();
    void on_resize(wxSizeEvent& event);
    void on_col_resize(wxListEvent& event);
    void on_activate(wxListEvent& event);
    void on_key(wxListEvent& event);
    void on_add(wxCommandEvent& event);
    void on_edit(wxCommandEvent& event);
    void on_del(wxCommandEvent& event);
private:
    void create_widgets();
    void edit();
    void delete_hashes();
    long get_selected();
    void update_layout();
    wxListCtrl* list_;
    MetalinkEditor& editor_;
    DECLARE_EVENT_TABLE()
};

#endif
