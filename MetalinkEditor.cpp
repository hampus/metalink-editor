#include "MetalinkEditor.hpp"

MetalinkEditor::MetalinkEditor()
{
    selection_ = 0;
}

bool MetalinkEditor::is_empty() const
{
    return metalink_.is_empty();
}

int MetalinkEditor::num_files() const
{
    return metalink_.num_files();
}

const wxString& MetalinkEditor::get_filename(int file) const
{
    return metalink_.get_file(file).get_filename();
}

void MetalinkEditor::add_file(const wxString& filename)
{
    add_file(MetalinkFile(filename));
}

void MetalinkEditor::add_file(const MetalinkFile& file)
{
    metalink_.add_file(file);
    selection_ = metalink_.num_files() - 1;
    update();
}

void MetalinkEditor::add_listener(MetalinkEditorListener* listener)
{
    listeners_.push_back(listener);
}

void MetalinkEditor::select(int file)
{
    if(file < 0 || file >= metalink_.num_files()) return;
    selection_ = file;
    update();
}

int MetalinkEditor::get_selection() const
{
    return selection_;
}

void MetalinkEditor::remove_file()
{
    // Remove the file
    metalink_.remove_file(selection_);
    // Update
    update();
}

const MetalinkFile& MetalinkEditor::get_file() const
{
    return metalink_.get_file(selection_);
}

const std::vector<MetalinkFile>& MetalinkEditor::get_files() const
{
    return metalink_.get_files();
}

void MetalinkEditor::set_file(const MetalinkFile& file)
{
    metalink_.set_file(selection_, file);
    update();
}

const wxString& MetalinkEditor::get_filename() const
{
    return filename_;
}

const Metalink& MetalinkEditor::get_metalink() const
{
    return metalink_;
}

void MetalinkEditor::set_filename(const wxString& filename)
{
    filename_ = filename;
}

void MetalinkEditor::update()
{
    // Fix selection, if needed.
    if(metalink_.is_empty()) {
        selection_ = 0;
    } else if(selection_ >= metalink_.num_files()) {
        selection_ = metalink_.num_files() - 1;
    }
    // Notify listeners
    for(int i = 0; i < listeners_.size(); i++) {
        listeners_.at(i)->update();
    }
}

void MetalinkEditor::save()
{
    if(filename_.empty()) return;
    metalink_.save(filename_);
}

void MetalinkEditor::open(const wxString& filename)
{
    metalink_ = Metalink::load(filename);
    filename_ = filename;
    selection_ = 0;
    update();
}

void MetalinkEditor::clear()
{
    metalink_.clear();
    filename_.clear();
    selection_ = 0;
    update();
}
