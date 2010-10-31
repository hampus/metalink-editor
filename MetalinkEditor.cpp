#include "MetalinkEditor.hpp"
#include "Metalink4Writer.hpp"
#include "Metalink3Writer.hpp"
#include "Metalink4Reader.hpp"
#include "Metalink3Reader.hpp"
#include <wx/filename.h>

MetalinkEditor::MetalinkEditor()
{
    selection_ = 0;
}

bool MetalinkEditor::is_empty() const
{
    return files_.empty();
}

int MetalinkEditor::num_files() const
{
    return files_.size();
}

const wxString& MetalinkEditor::get_filename(int file) const
{
    return files_.at(file).get_filename();
}

void MetalinkEditor::add_file(const wxString& filename)
{
    add_file(MetalinkFile(filename));
}

void MetalinkEditor::add_file(const MetalinkFile& file)
{
    files_.push_back(file);
    selection_ = files_.size() - 1;
    update();
}

void MetalinkEditor::add_listener(MetalinkEditorListener* listener)
{
    listeners_.push_back(listener);
}

void MetalinkEditor::select(int file)
{
    if(file < 0 || file >= files_.size()) return;
    selection_ = file;
    update();
}

int MetalinkEditor::get_selection() const
{
    return selection_;
}

void MetalinkEditor::remove_file()
{
    if(files_.empty()) return;
    // Erase file
    files_.erase(files_.begin() + selection_);
    // Fix selection
    if(files_.empty()) {
        selection_ = 0;
    } else {
        if(selection_ >= files_.size()) selection_ = files_.size() - 1;
    }
    // Update
    update();
}

const MetalinkFile& MetalinkEditor::get_file() const
{
    return files_.at(selection_);
}

const std::vector<MetalinkFile>& MetalinkEditor::get_files() const
{
    return files_;
}

void MetalinkEditor::set_file(const MetalinkFile& file)
{
    files_.at(selection_) = file;
    update();
}

const wxString& MetalinkEditor::get_filename() const
{
    return filename_;
}

void MetalinkEditor::set_filename(const wxString& filename)
{
    filename_ = filename;
}

void MetalinkEditor::update()
{
    for(int i = 0; i < listeners_.size(); i++) {
        listeners_.at(i)->update();
    }
}

void MetalinkEditor::save()
{
    if(filename_.empty()) return;
    if(wxFileName(filename_).GetExt() == wxT("metalink")) {
        Metalink3Writer writer(*this);
        writer.save(filename_);
    } else {
        Metalink4Writer writer(*this);
        writer.save(filename_);
    }
}

bool MetalinkEditor::load_metalink4(const wxString& filename)
{
    Metalink4Reader reader(*this);
    return reader.load(filename);
}

bool MetalinkEditor::load_metalink3(const wxString& filename)
{
    Metalink3Reader reader(*this);
    return reader.load(filename);
}

void MetalinkEditor::open(const wxString& filename)
{
    try {
        bool loaded = load_metalink4(filename);
        if(!loaded) {
            loaded = load_metalink3(filename);
        }
        if(!loaded) {
            throw MetalinkLoadError("Unrecognized file format!");
        }
        filename_ = filename;
    } catch(MetalinkLoadError& e) {
        clear();
        throw e;
    }
}

void MetalinkEditor::clear()
{
    files_.clear();
    filename_.clear();
    selection_ = 0;
    update();
}
