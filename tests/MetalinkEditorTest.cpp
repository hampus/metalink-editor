#include <cppunit/extensions/HelperMacros.h>
#include "../MetalinkEditor.hpp"
#include "config.h"
#include <wx/filename.h>
#include <iostream>

class MetalinkEditorTest : public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE(MetalinkEditorTest);
    CPPUNIT_TEST(testAddFiles);
    CPPUNIT_TEST(testClear);
    CPPUNIT_TEST(testLoad4);
    CPPUNIT_TEST(testSave4);
    CPPUNIT_TEST(testLoad3);
    CPPUNIT_TEST(testSave3);
    CPPUNIT_TEST(testLoadInvalid4);
    CPPUNIT_TEST(testLoadInvalid3);
    CPPUNIT_TEST(testLoadTorrent4);
    CPPUNIT_TEST(testLoadTorrent3);
    CPPUNIT_TEST(testSaveTorrent4);
    CPPUNIT_TEST(testSaveTorrent3);
    CPPUNIT_TEST_SUITE_END();
public:
    void testAddFiles();
    void testClear();
    void testLoad4();
    void testSave4();
    void testLoad3();
    void testSave3();
    void testLoadInvalid4();
    void testLoadInvalid3();
    void testLoadTorrent4();
    void testLoadTorrent3();
    void testSaveTorrent4();
    void testSaveTorrent3();
};

CPPUNIT_TEST_SUITE_REGISTRATION(MetalinkEditorTest);

wxString get_testfile(const wxString& filename)
{
    wxFileName file(wxT(SOURCE_DIR), filename);
    file.AppendDir(wxT("tests"));
    return file.GetFullPath();
}

wxString get_tmpfile(const wxString& filename)
{
    wxFileName file(wxT(BINARY_DIR), filename);
    return file.GetFullPath();
}

std::string read_file(const wxString& filename)
{
    std::ifstream in(filename.mb_str(wxConvFile),
                     std::ifstream::in | std::ifstream::binary);
    std::string data;
    char buf[4096];
    while(in.good()) {
        in.read(buf, sizeof(buf));
        data.append(buf, in.gcount());
    }
    return data;
}

MetalinkEditor create_test1()
{
    MetalinkEditor editor;
    MetalinkSource src(wxT("http://example.com/"));
    MetalinkFile file1(wxT("test1"));
    MetalinkFile file2(wxT("test2"));
    file1.add_source(src);
    file2.add_source(src);
    editor.add_file(file1);
    editor.add_file(file2);
    return editor;
}

MetalinkEditor create_test2()
{
    MetalinkEditor editor;
    MetalinkSource src(wxT("http://torrent.com/test.torrent"));
    src.set_location(wxT("us"));
    src.set_priority(wxT("23"));
    src.set_torrent(true);
    MetalinkFile file1(wxT("test55"));
    file1.add_source(src);
    editor.add_file(file1);
    return editor;
}

void MetalinkEditorTest::testAddFiles()
{
    MetalinkEditor editor;
    CPPUNIT_ASSERT_EQUAL(0, editor.num_files());
    CPPUNIT_ASSERT(editor.is_empty());
    editor.add_file(wxT("test1"));
    CPPUNIT_ASSERT_EQUAL(1, editor.num_files());
    CPPUNIT_ASSERT(!editor.is_empty());
    editor.add_file(wxT("test2"));
    CPPUNIT_ASSERT_EQUAL(2, editor.num_files());
    CPPUNIT_ASSERT(!editor.is_empty());
}

void MetalinkEditorTest::testClear()
{
    // Setup
    MetalinkEditor editor;
    editor.add_file(wxT("test3"));
    editor.set_filename(wxT("test364"));
    // Exercise
    editor.clear();
    // Verify
    CPPUNIT_ASSERT(editor.is_empty());
    CPPUNIT_ASSERT(editor.get_filename().empty());
}

void MetalinkEditorTest::testLoad4()
{
    // Setup
    wxString filename = get_testfile(wxT("test1.meta4"));
    MetalinkEditor editor;
    // Exercise
    editor.open(filename);
    // Verify
    CPPUNIT_ASSERT_EQUAL(2, editor.num_files());
    CPPUNIT_ASSERT(editor.get_filename() == filename);
    CPPUNIT_ASSERT(editor.get_filename(0) == wxT("test1"));
    CPPUNIT_ASSERT(editor.get_filename(1) == wxT("test2"));
}

void MetalinkEditorTest::testSave4()
{
    // Setup
    wxString savefile = get_tmpfile(wxT("tmp.meta4"));
    wxString test1file = get_testfile(wxT("test1.meta4"));
    MetalinkEditor editor = create_test1();
    // Exercise
    editor.set_filename(savefile);
    editor.save();
    // Verify
    std::string saved = read_file(savefile);
    std::string test1 = read_file(test1file);
    CPPUNIT_ASSERT(saved == test1);
}

void MetalinkEditorTest::testLoad3()
{
    // Setup
    wxString filename = get_testfile(wxT("test1.metalink"));
    MetalinkEditor editor;
    // Exercise
    editor.open(filename);
    // Verify
    CPPUNIT_ASSERT_EQUAL(2, editor.num_files());
    CPPUNIT_ASSERT(editor.get_filename() == filename);
    CPPUNIT_ASSERT(editor.get_filename(0) == wxT("test1"));
    CPPUNIT_ASSERT(editor.get_filename(1) == wxT("test2"));
}

void MetalinkEditorTest::testSave3()
{
    // Setup
    wxString savefile = get_tmpfile(wxT("tmp.metalink"));
    wxString test1file = get_testfile(wxT("test1.metalink"));
    MetalinkEditor editor = create_test1();
    // Exercise
    editor.set_filename(savefile);
    editor.save();
    // Verify
    std::string saved = read_file(savefile);
    std::string test1 = read_file(test1file);
    CPPUNIT_ASSERT(saved == test1);
}

void MetalinkEditorTest::testLoadInvalid4()
{
    wxString filename = get_testfile(wxT("invalid.meta4"));
    MetalinkEditor editor;
    CPPUNIT_ASSERT_THROW(editor.open(filename), MetalinkLoadError);
}

void MetalinkEditorTest::testLoadInvalid3()
{
    wxString filename = get_testfile(wxT("invalid.metalink"));
    MetalinkEditor editor;
    CPPUNIT_ASSERT_THROW(editor.open(filename), MetalinkLoadError);
}

void MetalinkEditorTest::testLoadTorrent4()
{
    // Setup
    wxString filename = get_testfile(wxT("test2.meta4"));
    MetalinkEditor editor;
    // Exercise
    editor.open(filename);
    // Verify
    CPPUNIT_ASSERT_EQUAL(1, editor.num_files());
    MetalinkFile file = editor.get_file();
    CPPUNIT_ASSERT(file.get_filename() == wxT("test55"));
    CPPUNIT_ASSERT(file.get_sources().size() == 1);
    MetalinkSource src = file.get_sources().at(0);
    CPPUNIT_ASSERT(src.get_uri() == wxT("http://torrent.com/test.torrent"));
    CPPUNIT_ASSERT(src.get_priority() == 23);
    CPPUNIT_ASSERT(src.get_location().empty());
    CPPUNIT_ASSERT(src.is_torrent());
}

void MetalinkEditorTest::testLoadTorrent3()
{
    // Setup
    wxString filename = get_testfile(wxT("test2.metalink"));
    MetalinkEditor editor;
    // Exercise
    editor.open(filename);
    // Verify
    CPPUNIT_ASSERT_EQUAL(1, editor.num_files());
    MetalinkFile file = editor.get_file();
    CPPUNIT_ASSERT(file.get_filename() == wxT("test55"));
    CPPUNIT_ASSERT(file.get_sources().size() == 1);
    MetalinkSource src = file.get_sources().at(0);
    CPPUNIT_ASSERT(src.get_uri() == wxT("http://torrent.com/test.torrent"));
    CPPUNIT_ASSERT(src.get_priority() == 23);
    CPPUNIT_ASSERT(src.get_location().empty());
    CPPUNIT_ASSERT(src.is_torrent());
}

void MetalinkEditorTest::testSaveTorrent4()
{
    // Setup
    wxString savefile = get_tmpfile(wxT("tmp.meta4"));
    wxString test2file = get_testfile(wxT("test2.meta4"));
    MetalinkEditor editor = create_test2();
    // Exercise
    editor.set_filename(savefile);
    editor.save();
    // Verify
    std::string saved = read_file(savefile);
    std::string test2 = read_file(test2file);
    CPPUNIT_ASSERT(saved == test2);
}

void MetalinkEditorTest::testSaveTorrent3()
{
    // Setup
    wxString savefile = get_tmpfile(wxT("tmp.metalink"));
    wxString test2file = get_testfile(wxT("test2.metalink"));
    MetalinkEditor editor = create_test2();
    // Exercise
    editor.set_filename(savefile);
    editor.save();
    // Verify
    std::string saved = read_file(savefile);
    std::string test2 = read_file(test2file);
    CPPUNIT_ASSERT(saved == test2);
}
