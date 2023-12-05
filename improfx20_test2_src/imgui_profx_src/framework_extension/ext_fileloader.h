// ext_fileloader. RCSZ 2023_12_3.

#ifndef _EXT_FILELOADER_H
#define _EXT_FILELOADER_H
#include "framework_extension_tools.hpp"

// �������ļ�������.
class FileLoaderBinary {
protected:
    std::vector<uint8_t> read_filedata = {};
    size_t               read_filesize = {};
public:
    FileLoaderBinary(const std::string& filename);

    std::vector<uint8_t> GetDataBinary();
    size_t               GetFileSize();
};

// �ı��ļ�������.
class FileLoaderString {
protected:
    std::string read_filedata = {};
    size_t      read_filesize = {};
public:
    FileLoaderString(const std::string& filename);

    std::string GetDataString();
    size_t      GetFileSize();
};

#endif