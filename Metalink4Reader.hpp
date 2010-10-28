#ifndef METALINK4READER_HPP
#define METALINK4READER_HPP

#include "MetalinkEditor.hpp"
#include "XmlContentHandler.hpp"
#include <wx/wx.h>
#include <string>
#include <map>

class Metalink4Reader : public XmlContentHandler
{
public:
    Metalink4Reader(MetalinkEditor& editor);
    bool load(wxString filename);
    void start_element(wxString name, std::map<std::string, wxString> attrs);
    void end_element(wxString name);
    void char_data(wxString data);
private:
    bool remove_namespace(wxString& name);
    MetalinkEditor& editor_;
    MetalinkFile file_;
    MetalinkSource source_;
    wxString data_;
    bool correctversion_;
    enum State {
        STATE_NONE,
        STATE_METALINK,
        STATE_FILE,
        STATE_URL
    } state_;
};

#endif
