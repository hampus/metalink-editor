#ifndef XMLPARSER_HPP
#define XMLPARSER_HPP

#include "XmlContentHandler.hpp"
#include <expat.h>
#include <wx/wx.h>
#include <string>
#include <map>

class XmlParser
{
public:
    XmlParser(XmlContentHandler& handler);
    ~XmlParser();
    void parse(wxString filename);
    void start_element(wxString name, std::map<std::string, wxString> attrs);
    void end_element(wxString name);
    void char_data(wxString data);
    XML_Parser get_parser();
    void set_error_msg(const char* msg);
private:
    XML_Parser parser_;
    XmlContentHandler& handler_;
    const char* error_msg_;
};

#endif
