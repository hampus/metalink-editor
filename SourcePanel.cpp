#include "SourcePanel.hpp"
#include "common.hpp"

BEGIN_EVENT_TABLE(SourcePanel, wxPanel)
    EVT_SIZE(SourcePanel::on_resize)
    EVT_LIST_COL_BEGIN_DRAG(ID_URIList, SourcePanel::on_col_resize)
END_EVENT_TABLE()

SourcePanel::SourcePanel(wxWindow* parent, MetalinkEditor& editor)
    : wxPanel(parent), editor_(editor)
{
    create_widgets();
    update();
}

void SourcePanel::create_widgets()
{
    // List
    list_ = new wxListCtrl(this, ID_URIList, wxDefaultPosition, wxDefaultSize, wxLC_REPORT | wxLC_VRULES | wxLC_HRULES);
    list_->InsertColumn(0, wxT("URI"));
    list_->InsertColumn(1, wxT("Location"));
    list_->InsertColumn(2, wxT("Priority"));
    // Buttons
    wxButton* btnAdd = new wxButton(this, ID_URIAdd, wxT("Add"));
    wxButton* btnEdit = new wxButton(this, ID_URIEdit, wxT("Edit"));
    wxButton* btnDelete = new wxButton(this, ID_URIDel, wxT("Delete"));
    // Layout
    wxBoxSizer* sizer2 = new wxBoxSizer(wxHORIZONTAL);
    sizer2->AddStretchSpacer();
    sizer2->Add(btnAdd);
    sizer2->Add(btnEdit);
    sizer2->Add(btnDelete);
    wxBoxSizer* sizer1 = new wxBoxSizer(wxVERTICAL);
    sizer1->Add(list_, 1, wxEXPAND, 0);
    sizer1->Add(sizer2, 0, wxEXPAND, 0);
    SetSizerAndFit(sizer1);
    Layout();
}

void SourcePanel::on_resize(wxSizeEvent& event)
{
    Layout();
    int width= list_->GetSize().GetWidth();
    if(width < 250) width = 250;
    list_->SetColumnWidth(0, width - 80*2);
    list_->SetColumnWidth(1, 80);
    list_->SetColumnWidth(2, 80);
}

void SourcePanel::on_col_resize(wxListEvent& event)
{
    event.Veto();
}

void SourcePanel::update()
{
    list_->DeleteAllItems();
}
