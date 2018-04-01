#include <fstream>
#include "Exceptions.hpp"
#include "FileReadStream.hpp"


FileReadStream::FileReadStream()
{
}

FileReadStream::~FileReadStream()
{
    if (is_open()) {
        _stream.close();
    }
}

void FileReadStream::open(const std::string& path)
{
    if (path.empty())
    {
        throw file_reader_error::empty_path(path);
    }
    if (is_open())
    {
        throw file_reader_error::already_open();
    }
    _stream.open(path, std::ios_base::binary);
    if (not is_open() or not _stream.good())
    {
        throw file_reader_error::cannot_access(path);
    }
    _filepath = path;
}

bool FileReadStream::is_open() const
{
    return _stream.is_open();
}

bool FileReadStream::is_eof() const
{
    return _stream.eof();
}

const std::ifstream* FileReadStream::getStream() const
{
    return  &_stream;
}

