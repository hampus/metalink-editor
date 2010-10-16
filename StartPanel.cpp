#include "StartPanel.hpp"


StartPanel::StartPanel(wxWindow* parent)
    : wxPanel(parent)
{
    wxStaticText* label = new wxStaticText(this, wxID_ANY, wxT("Welcome to Metalink Editor 2\n\nThis is an empty metalink. Get started by either opening\nan existing metalink or adding a file to this one. You can\nadd a file from the metalink menu."), wxDefaultPosition, wxDefaultSize, wxST_NO_AUTORESIZE);
    wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
    sizer->Add(label, 1, wxALL|wxEXPAND, 10);
    SetSizerAndFit(sizer);
}
