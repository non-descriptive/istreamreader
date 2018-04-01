#include <cstdio>
#include <string>

#include <sys/types.h>
#include <sys/stat.h>


#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>

#include "FileReadStream.hpp"
#include "Exceptions.hpp"


class FileReadStreamTest : public ::testing::Test {
protected:
    std::string _filename{"frs.test"};
    std::string _non_existent_filename{"non_existent.test"};
    std::string _dir_path{"test-folder"};
    // test object
    FileReadStream frs;
private:
    void createDir(const std::string& path) {
        struct stat info;
        int nError = 0;
        nError = stat(path.c_str(), &info );
        if (info.st_mode & S_IFDIR) {
            return;
        }

#ifdef __linux__
        mode_t nMode = 0o644;
        nError = mkdir(path.c_str(),nMode);
#elif _WIN32
        nError = _mkdir(path.c_str());
#endif
        if (nError != 0)
        {
            std::cerr << "Can't create directory: err[" << nError << "]"  << std::endl;
        }
    }
    void removeDir(const std::string& path) {
        struct stat info;
        int nError = 0;
        nError = stat(path.c_str(), &info );
        if( nError != 0 ) {
            std::cerr << "removeDir: Cannot access path: " << path << std::endl;
        }
        else if (info.st_mode & S_IFDIR) {
#ifdef __linux__
            nError = rmdir(path.c_str(),nMode);
#elif _WIN32
            nError = _rmdir(path.c_str());
#endif
        }
    }
protected:
    virtual void SetUp() override{
        std::ofstream testfile;
        testfile.open(_filename, std::ios_base::binary);
        std::string buf;
        for (size_t i =0; i < 1000000; ++i)
        {
            buf.append(std::to_string(i));
        }
        testfile.write(buf.data(), buf.size());
        testfile.close();
        createDir(_dir_path);
    }

    virtual void TestBody() override {

    }

    virtual void TearDown() override {
        std::remove(_filename.c_str());
        removeDir(_dir_path);
    }
};

TEST_F(FileReadStreamTest, EmptyFileStream)
{
    ASSERT_THROW(frs.open({}), file_reader_error::empty_path);
}
TEST_F(FileReadStreamTest, CantAccessNonExist)
{
    ASSERT_THROW(frs.open(_non_existent_filename), file_reader_error::cannot_access);
}
TEST_F(FileReadStreamTest, CantAceessDir)
{
    ASSERT_THROW(frs.open(_dir_path), file_reader_error::cannot_access);
}

TEST_F(FileReadStreamTest, AlreadyOpen)
{
    frs.open(_filename);
    ASSERT_THROW(frs.open(_filename), file_reader_error::already_open);
}

TEST_F(FileReadStreamTest, Streaming)
{
    frs.open(_filename);
    auto future = frs.get();
    auto stream = future.get();
    ASSERT_TRUE(stream->is_open());


}
