#ifndef METALINKHASH_HPP
#define METALINKHASH_HPP

struct MetalinkHash {
    MetalinkHash(const wxString& type, const wxString& value = wxT(""))
       : type(type), value(value) { }
    MetalinkHash() { }
    wxString type;
    wxString value;
};

#endif
