#include "FileScan.hpp"
#include <unistd.h>
#include <cerrno>

#ifndef O_BINARY
# define O_BINARY 0
#endif // O_BINARY

FileScan::FileScan():length_(0),
                     piece_length_(4194304),
                     listener_(NULL)
{}
                     
void FileScan::set_filename(const wxString& filename)
{
    filename_ = filename;
}

void FileScan::add_file_hash_ctx
(const std::tr1::shared_ptr<HashContext>& hash_ctx)
{
    file_hash_ctxs_.push_back(hash_ctx);
}

void FileScan::set_piece_hash_ctx
(const std::tr1::shared_ptr<HashContext>& hash_ctx)
{
    piece_hash_ctx_ = hash_ctx;
}

void FileScan::set_piece_length(size_t length)
{
    piece_length_ = length;
}

void FileScan::set_listener(MetalinkEditorProgressListener* listener)
{
    listener_ = listener;
}

size_t FileScan::get_piece_length() const
{
    return piece_length_;
}

const std::vector<wxString>& FileScan::get_piece_hashes() const
{
    return piece_hashes_;
}

off_t FileScan::get_length() const
{
    return length_;
}

namespace {
class AutoClose {
public:
    AutoClose(int fd):fd_(fd)
    {}
    ~AutoClose()
    {
        while(close(fd_) == -1 && errno == EINTR);
    }
private:
    int fd_;
};
} // namespace

void FileScan::scan()
{
    int fd;
    while((fd = open(filename_.mb_str(wxConvFile), O_BINARY|O_RDONLY)) == -1 &&
          errno == EINTR);
    if(fd == -1) {
        throw FileScanError(wxT("Failed to open file"));
    }
    AutoClose ac(fd);
    off_t length = lseek(fd, 0, SEEK_END);
    if((off_t)-1 == length || lseek(fd, 0, SEEK_SET) == (off_t)-1) {
        throw FileScanError(wxT("Failed to seek file"));
    }
    length_ = length;
    size_t accumulated_piece_length = 0;
    off_t partial = 0;
    static const size_t BUFSIZE = 4096;
    char buf[BUFSIZE];
    while(1) {
        ssize_t read_bytes;
        size_t count = BUFSIZE;
        while((read_bytes = read(fd, buf, count)) == -1 && errno == EINTR);
        if(read_bytes == 0) {
            break;
        }
        if(read_bytes == -1) {
            throw FileScanError(wxT("I/O error"));
        }
        partial += read_bytes;
        for(std::vector<std::tr1::shared_ptr<HashContext> >::const_iterator
                i = file_hash_ctxs_.begin(), eoi = file_hash_ctxs_.end();
            i != eoi;
            ++i) {
            (*i)->update(buf, read_bytes);
        }
        if(piece_hash_ctx_.get()) {
            ssize_t remaining_bytes = piece_length_-accumulated_piece_length;
            size_t update_bytes = std::min(remaining_bytes, read_bytes);
            piece_hash_ctx_->update(buf, update_bytes);
            accumulated_piece_length += update_bytes;
            if(accumulated_piece_length == piece_length_) {
                piece_hashes_.push_back(piece_hash_ctx_->hex_digest());
                accumulated_piece_length = 0;
                piece_hash_ctx_->reset();
                piece_hash_ctx_->update(buf+update_bytes,
                                        read_bytes-update_bytes);
            }
        }
        if(listener_) {
            listener_->update((static_cast<float>(partial))/length_*100);
        }
    }
    if(piece_hash_ctx_.get() && accumulated_piece_length > 0) {
        piece_hashes_.push_back(piece_hash_ctx_->hex_digest());
    }
}
