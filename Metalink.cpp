#include "Metalink.hpp"
#include "Metalink4Reader.hpp"
#include "Metalink3Reader.hpp"

int Metalink::num_files() const
{
    return files_.size();
}

bool Metalink::is_empty() const
{
    return files_.empty();
}

void Metalink::add_file(const MetalinkFile& file)
{
    files_.push_back(file);
}

void Metalink::remove_file(int index)
{
    if(index >= files_.size()) return;
    files_.erase(files_.begin() + index);
}

void Metalink::set_file(int index, const MetalinkFile& file)
{
    files_.at(index) = file;
}

const MetalinkFile& Metalink::get_file(int index) const
{
    return files_.at(index);
}

const std::vector<MetalinkFile>& Metalink::get_files() const
{
    return files_;
}

void Metalink::clear()
{
    files_.clear();
}

Metalink Metalink::load(const wxString& filename)
{
    Metalink ml;
    bool loaded = load_metalink4(filename, &ml);
    if(!loaded) {
        loaded = load_metalink3(filename, &ml);
    }
    if(!loaded) {
        throw MetalinkLoadError("Unrecognized file format!");
    }
    return ml;
}

bool Metalink::load_metalink4(const wxString& filename, Metalink* metalink)
{
    Metalink4Reader reader;
    reader.load(filename);
    *metalink = reader.get_metalink();
    return reader.is_recognized();
}

bool Metalink::load_metalink3(const wxString& filename, Metalink* metalink)
{
    Metalink3Reader reader;
    reader.load(filename);
    *metalink = reader.get_metalink();
    return reader.is_recognized();
}
