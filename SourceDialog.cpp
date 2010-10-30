#include "SourceDialog.hpp"
#include <wx/valgen.h>

SourceDialog::SourceDialog(const wxString& title, const MetalinkSource& source)
    : wxDialog(0, wxID_ANY, title), source_(source)
{
    // Init variables
    uri_ = source.get_uri();
    location_ = source.get_location();
    priority_ = source.get_prioritystr();
    torrent_ = source.is_torrent();
    // Create widgets
    wxStaticText* label1 = new wxStaticText(this, wxID_ANY, wxT("URI:"));
    wxTextCtrl* text1 = new wxTextCtrl(this, wxID_ANY, wxT(""), wxDefaultPosition,
        wxDefaultSize, 0, wxTextValidator(wxFILTER_NONE, &uri_));
    wxStaticText* label2 = new wxStaticText(this, wxID_ANY, wxT("Location:"));
    wxTextCtrl* text2 = new wxTextCtrl(this, wxID_ANY, wxT(""), wxDefaultPosition,
        wxDefaultSize, 0, wxTextValidator(wxFILTER_NONE, &location_));
    wxStaticText* label3 = new wxStaticText(this, wxID_ANY, wxT("Priority:"));
    wxTextCtrl* text3 = new wxTextCtrl(this, wxID_ANY, wxT(""), wxDefaultPosition,
        wxDefaultSize, 0, wxTextValidator(wxFILTER_NUMERIC, &priority_));
    wxStaticText* label4 = new wxStaticText(this, wxID_ANY, wxT("Torrent:"));
    wxCheckBox* check1 = new wxCheckBox(this, wxID_ANY, wxT("URI to a torrent that contains the file"), wxDefaultPosition,
        wxDefaultSize, 0, wxGenericValidator(&torrent_));
    // Create FlexGridSizer
    wxFlexGridSizer* gridSizer = new wxFlexGridSizer(2, 5, 5);
    gridSizer->AddGrowableCol(1);
    gridSizer->Add(label1, 0, wxALIGN_CENTER_VERTICAL | wxALIGN_RIGHT);
    gridSizer->Add(text1, 1, wxEXPAND);
    gridSizer->Add(label2, 0, wxALIGN_CENTER_VERTICAL | wxALIGN_RIGHT);
    gridSizer->Add(text2, 1, wxEXPAND);
    gridSizer->Add(label3, 0, wxALIGN_CENTER_VERTICAL | wxALIGN_RIGHT);
    gridSizer->Add(text3, 1, wxEXPAND);
    gridSizer->Add(label4, 0, wxALIGN_CENTER_VERTICAL | wxALIGN_RIGHT);
    gridSizer->Add(check1, 1, wxEXPAND);
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

MetalinkSource SourceDialog::get_source() const
{
    MetalinkSource source = source_;
    source.set_uri(uri_);
    source.set_location(location_);
    source.set_priority(priority_);
    source.set_torrent(torrent_);
    return source;
}
