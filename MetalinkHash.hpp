#ifndef METALINKHASH_HPP
#define METALINKHASH_HPP

struct MetalinkHash {
    MetalinkHash(const wxString& type, const wxString& value) {
        this->type = type;
        this->value = value;
    }
    wxString type;
    wxString value;
};

#endif
