#include <cppunit/extensions/HelperMacros.h>
#include "../MetalinkEditor.hpp"

class MetalinkEditorTest : public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE(MetalinkEditorTest);
    CPPUNIT_TEST(testAddFiles);
    CPPUNIT_TEST_SUITE_END();
public:
    void testAddFiles();
};

CPPUNIT_TEST_SUITE_REGISTRATION(MetalinkEditorTest);

void MetalinkEditorTest::testAddFiles()
{
    MetalinkEditor editor;
    CPPUNIT_ASSERT_EQUAL(0, editor.num_files());
    editor.add_file(wxT("test1"));
    CPPUNIT_ASSERT_EQUAL(1, editor.num_files());
    editor.add_file(wxT("test2"));
    CPPUNIT_ASSERT_EQUAL(2, editor.num_files());
}
