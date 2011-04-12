#include "HashPanel.hpp"
#include "HashDialog.hpp"
#include "common.hpp"

BEGIN_EVENT_TABLE(HashPanel, wxPanel)
    EVT_SIZE(HashPanel::on_resize)
    EVT_LIST_COL_BEGIN_DRAG(ID_HashList, HashPanel::on_col_resize)
    EVT_BUTTON(ID_HashAdd, HashPanel::on_add)
    EVT_BUTTON(ID_HashEdit, HashPanel::on_edit)
    EVT_BUTTON(ID_HashDel, HashPanel::on_del)
    EVT_LIST_ITEM_ACTIVATED(ID_HashList, HashPanel::on_activate)
    EVT_LIST_KEY_DOWN(ID_HashList, HashPanel::on_key)
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
    list_ = new wxListCtrl(this, ID_HashList, wxDefaultPosition, wxDefaultSize,
                           wxLC_REPORT | wxLC_VRULES | wxLC_HRULES);
    list_->InsertColumn(0, wxT("Type"));
    list_->InsertColumn(1, wxT("Value"));
    // Buttons
    wxButton* btn_add = new wxButton(this, ID_HashAdd, wxT("Add"));
    wxButton* btn_edit = new wxButton(this, ID_HashEdit, wxT("Edit"));
    wxButton* btn_delete = new wxButton(this, ID_HashDel, wxT("Delete"));
    // Layout
    wxBoxSizer* sizer2 = new wxBoxSizer(wxHORIZONTAL);
    sizer2->AddStretchSpacer();
    sizer2->Add(btn_add);
    sizer2->Add(btn_edit);
    sizer2->Add(btn_delete);
    wxBoxSizer* sizer1 = new wxBoxSizer(wxVERTICAL);
    sizer1->Add(list_, 1, wxEXPAND, 0);
    sizer1->Add(sizer2, 0, wxEXPAND, 0);
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

void HashPanel::on_activate(wxListEvent& event)
{
    edit();
}

void HashPanel::on_key(wxListEvent& event)
{
    if(event.GetKeyCode() == WXK_DELETE) delete_hashes();
}

void HashPanel::on_add(wxCommandEvent& event)
{
    HashDialog dlg(wxT("Add hash"), MetalinkHash(wxT("")));
    if(dlg.ShowModal() == wxID_OK) {
        MetalinkHash hash = dlg.get_hash();
        MetalinkFile file = editor_.get_file();
        file.add_file_hash(hash);
        editor_.set_file(file);
    }
}

void HashPanel::on_edit(wxCommandEvent& event)
{
    edit();
}

void HashPanel::on_del(wxCommandEvent& event)
{
    delete_hashes();
}

void HashPanel::delete_hashes()
{
    long index = -1;
    long deleted = 0;
    MetalinkFile file = editor_.get_file();
    while(true) {
        index = list_->GetNextItem(index, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
        if(index == -1) break;
        file.del_file_hash(index - deleted);
        deleted++;
    }
    editor_.set_file(file);
}

long HashPanel::get_selected()
{
    return list_->GetNextItem(-1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
}

void HashPanel::edit()
{
    long selected = get_selected();
    if(selected == -1) return;
    MetalinkFile file = editor_.get_file();
    HashDialog dlg(wxT("Edit hash"), file.get_file_hash(selected));
    if(dlg.ShowModal() == wxID_OK) {
        MetalinkHash hash = dlg.get_hash();
        file.set_file_hash(selected, hash);
        editor_.set_file(file);
    }
}
