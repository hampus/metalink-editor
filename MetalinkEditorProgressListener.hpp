#ifndef METALINKEDITORPROGRESSLISTENER_HPP
#define METALINKEDITORPROGRESSLISTENER_HPP

#include <wx/wx.h>

// Lister that can update progress information
class MetalinkEditorProgressListener
{
public:
    virtual void update(int value, const wxString& newmsg = wxT(""),
                        bool* skip = NULL)=0;
};

#endif
