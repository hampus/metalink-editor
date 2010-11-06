#include <cppunit/extensions/HelperMacros.h>
#include "../HashContext.hpp"

class HashContextTest : public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE(HashContextTest);
    CPPUNIT_TEST(testHexDigest);
    CPPUNIT_TEST_SUITE_END();
public:
    void testHexDigest();
};

CPPUNIT_TEST_SUITE_REGISTRATION(HashContextTest);

void HashContextTest::testHexDigest()
{
    std::tr1::shared_ptr<HashContext> ctx = HashContext::sha1();
    const char* msg = "MetalinkEditor";
    ctx->update(msg, strlen(msg));

    CPPUNIT_ASSERT_EQUAL
        (std::string("ed55d83291bd5d103539cfef17e5f74a482596e1"),
         std::string(ctx->hex_digest().ToAscii()));

    ctx->reset();

    ctx->update(msg, strlen(msg));
    ctx->update(msg, strlen(msg));

    CPPUNIT_ASSERT_EQUAL
        (std::string("bf72e7ebe6b3952099acbbe86cbb5d4d25b7a162"),
         std::string(ctx->hex_digest().ToAscii()));
}
