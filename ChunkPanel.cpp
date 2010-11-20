#include "ChunkPanel.hpp"
#include "common.hpp"

BEGIN_EVENT_TABLE(ChunkPanel, wxPanel)
    EVT_BUTTON(ID_DeleteChunks, ChunkPanel::on_delete)
END_EVENT_TABLE()

ChunkPanel::ChunkPanel(wxWindow* parent, MetalinkEditor& editor)
    : wxPanel(parent), editor_(editor)
{
    create_widgets();
    update();
}

void ChunkPanel::create_widgets()
{
    // Create widgets
    label1_ = new wxStaticText(this, wxID_ANY, wxT(""));
    btn_delete_ = new wxButton(this, ID_DeleteChunks, wxT("Delete chunks"));
    // Layout
    wxBoxSizer* sizer2 = new wxBoxSizer(wxHORIZONTAL);
    sizer2->Add(btn_delete_, 0, 0);
    wxBoxSizer* sizer1 = new wxBoxSizer(wxVERTICAL);
    sizer1->Add(label1_, 0, wxEXPAND | wxALL, 5);
    sizer1->Add(sizer2, 0, wxEXPAND | wxALL, 5);
    SetSizerAndFit(sizer1);
    Layout();
}

void ChunkPanel::update()
{
    MetalinkFile file = editor_.get_file();
    long num = file.get_piece_hashes().size();
    if(num == 0) {
        label1_->SetLabel(wxT("This file has no chunk checksums."));
        btn_delete_->Enable(false);
    } else {
        wxString type = file.get_piece_hash_type();
        wxString msg;
        msg << wxT("This file has ") << num;
        msg << wxT(" chunk checksum");
        if(num > 1) {
            msg << wxT("s");
        }
        msg << wxT(" of type '") << type << wxT("'.");
        label1_->SetLabel(msg);
        btn_delete_->Enable(true);
    }
}

void ChunkPanel::on_delete(wxCommandEvent& WXUNUSED(event))
{
    MetalinkFile file = editor_.get_file();
    file.set_piece_hash(wxT(""), 0, std::vector<wxString>());
    editor_.set_file(file);
}
