#ifndef GENERALPANEL_HPP
#define GENERALPANEL_HPP

#include "MetalinkEditor.hpp"
#include <wx/wx.h>

class GeneralPanel : public wxScrolledWindow
{
public:
    GeneralPanel(wxWindow* parent, MetalinkEditor& editor);
    void update();
    void on_change(wxCommandEvent& event);
private:
    void create_widgets();
    wxTextCtrl* txt_identity_;
    wxTextCtrl* txt_desc_;
    wxTextCtrl* txt_version_;
    wxTextCtrl* txt_size_;
    MetalinkEditor& editor_;
    bool ignore_updates_;
    DECLARE_EVENT_TABLE()
};

#endif
