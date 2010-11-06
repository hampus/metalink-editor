#ifndef HASHCONTEXT_HPP
#define HASHCONTEXT_HPP

#include <wx/wx.h>
#include <tr1/memory>

class HashContextImpl;

class HashContext {
public:
    ~HashContext();
    // Resets this object so that it can be reused.
    void reset();
    void update(const void* data, size_t length);
    // Returns printable hex digest. This method can be called only
    // once. You can reuse this object after calling reset().
    wxString hex_digest();
    static std::tr1::shared_ptr<HashContext> md5();
    static std::tr1::shared_ptr<HashContext> sha1();
    static std::tr1::shared_ptr<HashContext> sha256();
private:
    HashContext();
    // We don't allow copying this class.
    HashContext(const HashContext&);
    // We don't allow assignment for this class.
    HashContext& operator=(const HashContext&);  
    HashContextImpl* pImpl_;
};

#endif
