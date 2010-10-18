#include "SourceDialog.hpp"

SourceDialog::SourceDialog(wxString title, MetalinkSource source)
    : wxDialog(0, wxID_ANY, title), source_(source)
{
    // Init variables
    uri_ = source.get_uri();
    // Create widgets
    wxStaticText* label1 = new wxStaticText(this, wxID_ANY, wxT("URI:"));
    wxTextCtrl* text1 = new wxTextCtrl(this, wxID_ANY, wxT(""), wxDefaultPosition,
        wxDefaultSize, 0, wxTextValidator(wxFILTER_NONE, &uri_));
    // Create FlexGridSizer
    wxFlexGridSizer* gridSizer = new wxFlexGridSizer(2, 5, 5);
    gridSizer->AddGrowableCol(1);
    gridSizer->Add(label1, 0, wxALIGN_CENTER_VERTICAL | wxALIGN_RIGHT);
    gridSizer->Add(text1, 1, wxEXPAND);
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
    SetSize(wxSize(400, -1));
    text1->SetFocus();
}

MetalinkSource SourceDialog::get_source()
{
    MetalinkSource source = source_;
    source.set_uri(uri_);
    return source;
}
