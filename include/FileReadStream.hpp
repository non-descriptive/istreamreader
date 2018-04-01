#pragma once
#include <string>
#include <fstream>

#include "IReadStream.hpp"

class FileReadStream: public IReadStream<FileReadStream, std::ifstream>
{
    friend class IReadStream<FileReadStream, std::ifstream>;
public:
    FileReadStream();
    virtual ~FileReadStream() override;

    void open(const std::string& path);
protected:
    const std::ifstream* getStream() const;
    bool is_open() const;
    bool is_eof() const;


private:
    std::string _filepath;
    std::ifstream _stream;
};
