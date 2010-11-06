#ifndef HASHCONTEXTIMPL_HPP
#define HASHCONTEXTIMPL_HPP

#include <wx/wx.h>
#include <openssl/evp.h>

// HashContextImpl implementation using OpenSSL.
class HashContextImpl {
public:
    typedef const EVP_MD* HashFunc;
    HashContextImpl(const HashFunc& hash_func);
    ~HashContextImpl();
    void reset();
    void update(const void* data, size_t length);
    wxString hex_digest();
    static HashFunc md5();
    static HashFunc sha1();
    static HashFunc sha256();
private:
    HashContextImpl(const HashContextImpl&);
    HashContextImpl& operator=(const HashContextImpl&);
    EVP_MD_CTX ctx_;
    HashFunc hash_func_;
};

#endif
