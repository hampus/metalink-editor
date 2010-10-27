#ifndef XMLCONTENTHANDLER_HPP
#define XMLCONTENTHANDLER_HPP

#include <wx/wx.h>
#include <string>
#include <map>

class XmlContentHandler
{
public:
    virtual void start_element(wxString name,
                               std::map<std::string, wxString> attrs)=0;
    virtual void end_element(wxString name)=0;
    virtual void char_data(wxString data)=0;
};

#endif
