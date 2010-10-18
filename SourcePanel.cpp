#include "SourcePanel.hpp"
#include "SourceDialog.hpp"
#include "common.hpp"

BEGIN_EVENT_TABLE(SourcePanel, wxPanel)
    EVT_SIZE(SourcePanel::on_resize)
    EVT_LIST_COL_BEGIN_DRAG(ID_URIList, SourcePanel::on_col_resize)
    EVT_BUTTON(ID_URIAdd, SourcePanel::on_add)
    EVT_BUTTON(ID_URIEdit, SourcePanel::on_edit)
    EVT_BUTTON(ID_URIDel, SourcePanel::on_del)
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

void SourcePanel::on_add(wxCommandEvent& event)
{
    SourceDialog dlg(wxT("Add URI"), MetalinkSource());
    if(dlg.ShowModal() == wxID_OK) {
        MetalinkSource source = dlg.get_source();
        MetalinkFile file = editor_.get_file();
        file.add_source(source);
        editor_.set_file(file);
    }
}

void SourcePanel::on_edit(wxCommandEvent& event)
{
}

void SourcePanel::on_del(wxCommandEvent& event)
{
}

void SourcePanel::update()
{
    list_->DeleteAllItems();
    MetalinkFile file = editor_.get_file();
    std::vector<MetalinkSource> sources = file.get_sources();
    for(int i = 0; i < sources.size(); i++) {
        MetalinkSource& source = sources.at(i);
        list_->InsertItem(i, source.get_uri());
        list_->SetItem(i, 1, source.get_location());
        list_->SetItem(i, 2, source.get_prioritystr());
    }
}
