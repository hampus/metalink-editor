#ifndef METALINK3READER_HPP
#define METALINK3READER_HPP

#include "Metalink.hpp"
#include "XmlContentHandler.hpp"
#include <wx/wx.h>
#include <string>
#include <map>

class Metalink3Reader : public XmlContentHandler
{
public:
    Metalink3Reader();
    void load(wxString filename);
    void start_element(wxString name, std::map<std::string, wxString> attrs);
    void end_element(wxString name);
    void char_data(wxString data);
    const Metalink& get_metalink() const;
    bool is_recognized() const;
private:
    bool remove_namespace(wxString& name);
    Metalink metalink_;
    MetalinkFile file_;
    MetalinkSource source_;
    MetalinkHash hash_;
    std::vector<wxString> piece_hashes_;
    long piece_;
    wxString data_;
    bool recognized_;
    enum State {
        STATE_NONE,
        STATE_METALINK,
        STATE_FILE,
        STATE_RESOURCES,
        STATE_URL,
        STATE_PIECES
    } state_;
};

#endif
