#include "FileFinder.hpp"

FileFinder* FileFinder::GetSingleton() {
#ifdef GAME
    return *reinterpret_cast<FileFinder**>(0x11F81DC);
#else
    return *reinterpret_cast<FileFinder**>(0xF22AA0);
#endif
}

// GAME - 0xAFE0D0
// GECK - 0x8A1FC0
bool FileFinder::Exist(const char* apFileName, char* apFilePath, uint32_t aiFlags, ARCHIVE_TYPE aeArchiveType) const {
#ifdef GAME
    return ThisCall<bool>(0xAFE0D0, this, apFileName, apFilePath, aiFlags, aeArchiveType);
#else
    return ThisCall<bool>(0x8A1FC0, this, apFileName, apFilePath, aiFlags, aeArchiveType);
#endif
}

// GAME - 0xAFDF20
// GECK - 0x8A1E10
BSFile* FileFinder::GetFile(const char* apFileName, OpenMode aeMode, uint32_t auiSize, ARCHIVE_TYPE aeArchiveType) {
#ifdef GAME
    return CdeclCall<BSFile*>(0xAFDF20, apFileName, aeMode, auiSize, aeArchiveType);
#else
    return CdeclCall<BSFile*>(0x8A1E10, apFileName, aeMode, auiSize, aeArchiveType);
#endif
}

// GAME - 0x456A20
// GECK - 0x479630
bool FileFinder::Locate(const char* apFileName, char* apFilePath, uint32_t auiFlags, ARCHIVE_TYPE aeArchiveType) {
#ifdef GAME
    return CdeclCall<bool>(0x456A20, apFileName, apFilePath, auiFlags, aeArchiveType);
#else
    return CdeclCall<bool>(0x479630, apFileName, apFilePath, auiFlags, aeArchiveType);
#endif
}