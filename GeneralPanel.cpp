#include "GeneralPanel.hpp"
#include "util.hpp"
#include "common.hpp"

BEGIN_EVENT_TABLE(GeneralPanel, wxScrolledWindow)
    EVT_TEXT(ID_Identity, GeneralPanel::on_change)
    EVT_TEXT(ID_Description, GeneralPanel::on_change)
    EVT_TEXT(ID_Version, GeneralPanel::on_change)
    EVT_TEXT(ID_Size, GeneralPanel::on_change)
END_EVENT_TABLE()

GeneralPanel::GeneralPanel(wxWindow* parent, MetalinkEditor& editor)
    : wxScrolledWindow(parent), editor_(editor), ignore_updates_(false)
{
    create_widgets();
    update();
}

void GeneralPanel::create_widgets()
{
    // Create widgets
    wxStaticText* label1 = new wxStaticText(this, wxID_ANY, wxT("Identity:"));
    txt_identity_ = new wxTextCtrl(this, ID_Identity);
    wxStaticText* label2 = new wxStaticText(this, wxID_ANY,
                                            wxT("Description:"));
    txt_desc_ = new wxTextCtrl(this, ID_Description);
    wxStaticText* label3 = new wxStaticText(this, wxID_ANY, wxT("Version:"));
    txt_version_ = new wxTextCtrl(this, ID_Version);
    wxStaticText* label4 = new wxStaticText(this, wxID_ANY, wxT("File size:"));
    txt_size_ = new wxTextCtrl(this, ID_Size, wxT(""), wxDefaultPosition,
        wxDefaultSize, 0, wxTextValidator(wxFILTER_NUMERIC));
    // Create FlexGridSizer
    wxFlexGridSizer* gridSizer = new wxFlexGridSizer(2, 5, 5);
    gridSizer->AddGrowableCol(1);
    gridSizer->Add(label1, 0, wxALIGN_CENTER_VERTICAL | wxALIGN_RIGHT);
    gridSizer->Add(txt_identity_, 1, wxEXPAND);
    gridSizer->Add(label2, 0, wxALIGN_CENTER_VERTICAL | wxALIGN_RIGHT);
    gridSizer->Add(txt_desc_, 1, wxEXPAND);
    gridSizer->Add(label3, 0, wxALIGN_CENTER_VERTICAL | wxALIGN_RIGHT);
    gridSizer->Add(txt_version_, 1, wxEXPAND);
    gridSizer->Add(label4, 0, wxALIGN_CENTER_VERTICAL | wxALIGN_RIGHT);
    gridSizer->Add(txt_size_, 1, wxEXPAND);
    // Create top sizer
    wxBoxSizer* topsizer = new wxBoxSizer(wxVERTICAL);
    topsizer->Add(gridSizer, 0, wxEXPAND | wxALL, 5);
    SetSizer(topsizer);
    Layout();
    // Set properties
    SetScrollRate(5, 5);
}

void GeneralPanel::update()
{
    if(ignore_updates_) return;
    MetalinkFile file = editor_.get_file();
    txt_identity_->ChangeValue(file.get_identity());
    txt_desc_->ChangeValue(file.get_description());
    txt_version_->ChangeValue(file.get_version());
    txt_size_->ChangeValue(file.get_size());
}

void GeneralPanel::on_change(wxCommandEvent& WXUNUSED(event))
{
    ignore_updates_ = true;
    MetalinkFile file = editor_.get_file();
    file.set_identity(txt_identity_->GetValue());
    file.set_description(txt_desc_->GetValue());
    file.set_version(txt_version_->GetValue());
    file.set_size(txt_size_->GetValue());
    editor_.set_file(file);
    ignore_updates_ = false;
}
