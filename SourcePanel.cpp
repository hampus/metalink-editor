#include "SourcePanel.hpp"
#include "SourceDialog.hpp"
#include "common.hpp"

BEGIN_EVENT_TABLE(SourcePanel, wxPanel)
    EVT_SIZE(SourcePanel::on_resize)
    EVT_LIST_COL_BEGIN_DRAG(ID_URIList, SourcePanel::on_col_resize)
    EVT_BUTTON(ID_URIAdd, SourcePanel::on_add)
    EVT_BUTTON(ID_URIEdit, SourcePanel::on_edit)
    EVT_BUTTON(ID_URIDel, SourcePanel::on_del)
    EVT_LIST_ITEM_ACTIVATED(ID_URIList, SourcePanel::on_activate)
    EVT_LIST_KEY_DOWN(ID_URIList, SourcePanel::on_key)
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
    wxButton* btn_add = new wxButton(this, ID_URIAdd, wxT("Add"));
    wxButton* btn_edit = new wxButton(this, ID_URIEdit, wxT("Edit"));
    wxButton* btn_delete = new wxButton(this, ID_URIDel, wxT("Delete"));
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

long SourcePanel::get_selected()
{
    return list_->GetNextItem(-1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
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

void SourcePanel::on_activate(wxListEvent& event)
{
    edit();
}

void SourcePanel::on_key(wxListEvent& event)
{
    if(event.GetKeyCode() == WXK_DELETE) delete_sources();
}

void SourcePanel::on_add(wxCommandEvent& event)
{
    SourceDialog dlg(wxT("Add source"), MetalinkSource());
    if(dlg.ShowModal() == wxID_OK) {
        MetalinkSource source = dlg.get_source();
        MetalinkFile file = editor_.get_file();
        file.add_source(source);
        editor_.set_file(file);
    }
}

void SourcePanel::on_edit(wxCommandEvent& event)
{
    edit();
}

void SourcePanel::on_del(wxCommandEvent& event)
{
    delete_sources();
}

void SourcePanel::delete_sources()
{
    long index = -1;
    long deleted = 0;
    MetalinkFile file = editor_.get_file();
    while(true) {
        index = list_->GetNextItem(index, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
        if(index == -1) break;
        file.del_source(index - deleted);
        deleted++;
    }
    editor_.set_file(file);
}

void SourcePanel::edit()
{
    long selected = get_selected();
    if(selected == -1) return;
    MetalinkFile file = editor_.get_file();
    SourceDialog dlg(wxT("Edit source"), file.get_source(selected));
    if(dlg.ShowModal() == wxID_OK) {
        MetalinkSource source = dlg.get_source();
        file.set_source(selected, source);
        editor_.set_file(file);
    }
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
