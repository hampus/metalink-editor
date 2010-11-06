#ifndef PROGRESSDIALOGPROGRESSLISTENER_HPP
#define PROGRESSDIALOGPROGRESSLISTENER_HPP

#include "MetalinkEditorProgressListener.hpp"
#include <wx/progdlg.h>

class ProgressDialogProgressListener:public MetalinkEditorProgressListener
{
public:
    ProgressDialogProgressListener(wxProgressDialog* dialog);
    virtual void update(int value, const wxString& newmsg = wxT(""),
                        bool* skip = NULL);
private:
    wxProgressDialog* dialog_;
};

#endif
