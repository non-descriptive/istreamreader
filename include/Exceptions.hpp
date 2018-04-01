#pragma once

#include <stdexcept>

namespace file_reader_error
{
class empty_path: public std::runtime_error
{
public:
    explicit empty_path(const std::string& path)
        : std::runtime_error("Path is empty: " + path)
    {
    }
};

class cannot_access: public std::runtime_error
{
public:
    explicit cannot_access(const std::string& path)
        : std::runtime_error("Cannot access path: " + path)
    {
    }
};

class already_open: public std::runtime_error
{
public:
    explicit already_open()
        : std::runtime_error("Stream already opened")
    {}
};

} // end stream_read_error
