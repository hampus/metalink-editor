#include "HashContextImpl.hpp"

HashContextImpl::HashContextImpl(const HashFunc& hash_func):
    hash_func_(hash_func)
{
    EVP_MD_CTX_init(&ctx_);
    reset();
}

HashContextImpl::~HashContextImpl()
{
    EVP_MD_CTX_cleanup(&ctx_);
}

void HashContextImpl::reset()
{
    EVP_DigestInit_ex(&ctx_, hash_func_, NULL);
}

void HashContextImpl::update(const void* data, size_t length)
{
    EVP_DigestUpdate(&ctx_, data, length);
}

wxString HashContextImpl::hex_digest()
{
    unsigned int length = EVP_MD_size(hash_func_);
    unsigned char* data = new unsigned char[length];
    EVP_DigestFinal(&ctx_, data, &length);
    wxString hex_digest;
    for(size_t i = 0; i < length; ++i) {
        wxString temp;
        temp.Printf(wxT("%02x"), data[i]);
        hex_digest += temp;
    }
    delete [] data;
    return hex_digest;
}

HashContextImpl::HashFunc HashContextImpl::md5()
{
    return EVP_md5();
}

HashContextImpl::HashFunc HashContextImpl::sha1()
{
    return EVP_sha1();
}

HashContextImpl::HashFunc HashContextImpl::sha256()
{
    return EVP_sha256();
}
