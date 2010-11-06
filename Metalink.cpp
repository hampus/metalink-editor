#include "Metalink.hpp"

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
