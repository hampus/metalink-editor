#include "HashDialog.hpp"
#include <wx/valgen.h>

HashDialog::HashDialog(const wxString& title, const MetalinkHash& hash)
    : wxDialog(0, wxID_ANY, title), hash_(hash)
{
    // Init variables
    type_ = hash.type;
    value_ = hash.value;
    // Create widgets
    wxStaticText* label1 = new wxStaticText(this, wxID_ANY, wxT("Type:"));
    wxTextCtrl* text1 = new wxTextCtrl(this, wxID_ANY, wxT(""), wxDefaultPosition,
        wxDefaultSize, 0, wxTextValidator(wxFILTER_NONE, &type_));
    wxStaticText* label2 = new wxStaticText(this, wxID_ANY, wxT("Value:"));
    wxTextCtrl* text2 = new wxTextCtrl(this, wxID_ANY, wxT(""), wxDefaultPosition,
        wxDefaultSize, 0, wxTextValidator(wxFILTER_NONE, &value_));
    // Create FlexGridSizer
    wxFlexGridSizer* gridSizer = new wxFlexGridSizer(2, 5, 5);
    gridSizer->AddGrowableCol(1);
    gridSizer->Add(label1, 0, wxALIGN_CENTER_VERTICAL | wxALIGN_RIGHT);
    gridSizer->Add(text1, 1, wxEXPAND);
    gridSizer->Add(label2, 0, wxALIGN_CENTER_VERTICAL | wxALIGN_RIGHT);
    gridSizer->Add(text2, 1, wxEXPAND);
    // Create button sizer
    wxSizer* btnSizer = CreateSeparatedButtonSizer(wxOK | wxCANCEL);
    // Create top sizer
    wxBoxSizer* topsizer = new wxBoxSizer(wxVERTICAL);
    topsizer->Add(gridSizer, 0, wxEXPAND | wxALL, 5);
    if(btnSizer) {
        topsizer->Add(btnSizer, 0, wxEXPAND | wxALL, 5);
    }
    SetSizerAndFit(topsizer);
    Layout();
    // Set initial state
    SetSize(wxSize(500, -1));
    text1->SetFocus();
}

MetalinkHash HashDialog::get_hash() const
{
    MetalinkHash hash = hash_;
    hash.type = type_;
    hash.value = value_;
    return hash;
}
