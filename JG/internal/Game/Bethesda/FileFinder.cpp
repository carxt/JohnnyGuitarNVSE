#include "FileFinder.hpp"

FileFinder* FileFinder::GetSingleton() {
    return *reinterpret_cast<FileFinder**>(0x11F81DC);
}

// GAME - 0xAFE0D0
bool FileFinder::Exist(const char* apFileName, char* apFilePath, uint32_t aiFlags, ARCHIVE_TYPE aeArchiveType) const {
    return ThisCall<bool>(0xAFE0D0, this, apFileName, apFilePath, aiFlags, aeArchiveType);
}

// GAME - 0xAFDF20
BSFile* FileFinder::GetFile(const char* apFileName, OpenMode aeMode, uint32_t auiSize, ARCHIVE_TYPE aeArchiveType) {
    return CdeclCall<BSFile*>(0xAFDF20, apFileName, aeMode, auiSize, aeArchiveType);
}

// GAME - 0x456A20
bool FileFinder::Locate(const char* apFileName, char* apFilePath, uint32_t auiFlags, ARCHIVE_TYPE aeArchiveType) {
    return CdeclCall<bool>(0x456A20, apFileName, apFilePath, auiFlags, aeArchiveType);
}