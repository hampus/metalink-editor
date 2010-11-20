#include "HashPanel.hpp"
#include "common.hpp"

BEGIN_EVENT_TABLE(HashPanel, wxPanel)
    EVT_SIZE(HashPanel::on_resize)
    EVT_LIST_COL_BEGIN_DRAG(ID_HashList, HashPanel::on_col_resize)
END_EVENT_TABLE()

HashPanel::HashPanel(wxWindow* parent, MetalinkEditor& editor)
    : wxPanel(parent), editor_(editor)
{
    create_widgets();
    update();
}

void HashPanel::create_widgets()
{
    // List
    list_ = new wxListCtrl(this, ID_HashList, wxDefaultPosition, wxDefaultSize, wxLC_REPORT | wxLC_VRULES | wxLC_HRULES);
    list_->InsertColumn(0, wxT("Type"));
    list_->InsertColumn(1, wxT("Value"));
    // Layout
    wxBoxSizer* sizer1 = new wxBoxSizer(wxVERTICAL);
    sizer1->Add(list_, 1, wxEXPAND, 0);
    SetSizerAndFit(sizer1);
    Layout();
}

void HashPanel::update()
{
    list_->DeleteAllItems();
    MetalinkFile file = editor_.get_file();
    std::vector<MetalinkHash> hashes = file.get_file_hashes();
    for(int i = 0; i < hashes.size(); i++) {
        MetalinkHash& hash = hashes.at(i);
        list_->InsertItem(i, hash.type);
        list_->SetItem(i, 1, hash.value);
    }
    update_layout();
}

void HashPanel::on_resize(wxSizeEvent& event)
{
    Layout();
    // This is needed to get rid of some visual artifacts (wxGTK).
    update_layout();
}

void HashPanel::update_layout()
{
    list_->SetColumnWidth(0, 80);
    list_->SetColumnWidth(1, wxLIST_AUTOSIZE);
    if(list_->GetColumnWidth(1) < 80) {
        list_->SetColumnWidth(1, 80);
    }
}

void HashPanel::on_col_resize(wxListEvent& event)
{
    event.Veto();
}
