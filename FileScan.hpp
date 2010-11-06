#ifndef FILESCAN_HPP
#define FILESCAN_HPP

#include "MetalinkEditorProgressListener.hpp"
#include "HashContext.hpp"
#include <wx/wx.h>
#include <vector>
#include <tr1/memory>

// This class reads specified file and collects data such as file size
// and hash.
//
// To calculate hash value for entire file, you can add HashContext of
// desired hash function using FileScan::add_file_hash_ctx().  To
// calculate piece hash, you can set HashContext of desired hash
// function using using FileScan::set_piece_hash_ctx().  You can set
// multiple HashContext for entire file hash.  But you can only set
// one HashContext for piece hash. This is reasonable because normally
// piece hash is available for one hash function.
//
// To scan file, call FileScan::scan().  After FileScan::scan(), you
// can get collected data using various getter functions.  For file
// hashes, FileScan does not provide getter function directly.  You
// can get hash calling HashContext::hex_digest() against HashContext
// you added earlier.  For piece hash, you can get them using
// FileScan::get_piece_hashes().
class FileScan {
public:
    FileScan();
    void set_filename(const wxString& filename);
    void add_file_hash_ctx(const std::tr1::shared_ptr<HashContext>& ctx);
    void set_piece_hash_ctx(const std::tr1::shared_ptr<HashContext>& ctx);
    void set_piece_length(size_t length);
    // Setting listener. The caller must be responsible for deleting
    // listener.
    void set_listener(MetalinkEditorProgressListener* listener);
    const std::vector<wxString>& get_piece_hashes() const;
    off_t get_length() const;
    void scan();
private:
    wxString filename_;
    // file length. This is calculated after opening file filename_
    off_t length_;
    std::vector<std::tr1::shared_ptr<HashContext> > file_hash_ctxs_;
    std::tr1::shared_ptr<HashContext> piece_hash_ctx_;
    // length of piece for piece hash calculation
    size_t piece_length_;
    // MetalinkEditorProgressListener::udpate(...) is repeatedly called
    // while scanning file. This is used to show user progress bar.
    MetalinkEditorProgressListener* listener_;
    // Calculated piece hashes. This is an array of human readable hex
    // digest.
    std::vector<wxString> piece_hashes_;
};

class FileScanError: public std::exception
{
public:
    FileScanError(const wxString& msg) : msg_(msg) {}
    ~FileScanError() throw() {}
    virtual const char* what() const throw()
    {
        return msg_.mb_str(wxConvUTF8);
    }
    const wxString& getMessage() const
    {
        return msg_;
    }
private:
    wxString msg_;
};

#endif
