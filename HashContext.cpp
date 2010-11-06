#include "HashContext.hpp"
#include "HashContextImpl.hpp"

void HashContext::reset()
{
    pImpl_->reset();
}

void HashContext::update(const void* data, size_t length)
{
    pImpl_->update(data, length);
}

wxString HashContext::hex_digest()
{
    return pImpl_->hex_digest();
}

std::tr1::shared_ptr<HashContext> HashContext::md5()
{
    std::tr1::shared_ptr<HashContext> ctx(new HashContext());
    ctx->pImpl_ = new HashContextImpl(HashContextImpl::md5());
    return ctx;
}

std::tr1::shared_ptr<HashContext> HashContext::sha1()
{
    std::tr1::shared_ptr<HashContext> ctx(new HashContext());
    ctx->pImpl_ = new HashContextImpl(HashContextImpl::sha1());
    return ctx;
}

std::tr1::shared_ptr<HashContext> HashContext::sha256()
{
    std::tr1::shared_ptr<HashContext> ctx(new HashContext());
    ctx->pImpl_ = new HashContextImpl(HashContextImpl::sha256());
    return ctx;
}

HashContext::HashContext():pImpl_(NULL)
{}

HashContext::~HashContext()
{
    delete pImpl_;
}
