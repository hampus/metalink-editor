#include "ProgressDialogProgressListener.hpp"

ProgressDialogProgressListener::ProgressDialogProgressListener
(wxProgressDialog* dialog):dialog_(dialog)
{}

void ProgressDialogProgressListener::update(int value, const wxString& newmsg,
                                            bool* skip)
{
    dialog_->Update(value, newmsg, skip);
}
