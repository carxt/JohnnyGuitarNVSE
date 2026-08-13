#include "FileFinder.hpp"

FileFinder* FileFinder::GetSingleton() {
#ifdef GAME
    return *reinterpret_cast<FileFinder**>(0x11F81DC);
#else
    return *reinterpret_cast<FileFinder**>(0xF22AA0);
#endif
}

// GAME - 0xAFDF20
// GECK - 0x8A1E10
BSFile* FileFinder::GetFile(const char* apName, OpenMode aeMode, int aiSize, ARCHIVE_TYPE aeArchiveType) {
#ifdef GAME
    return CdeclCall<BSFile*>(0xAFDF20, apName, aeMode, aiSize, aeArchiveType);
#else
    return CdeclCall<BSFile*>(0x8A1E10, apName, aeMode, aiSize, aeArchiveType);
#endif
}

// GAME - 0x456A20
// GECK - 0x479630
bool FileFinder::Locate(const char* apName, const char* apFilePath, uint32_t aiFlags, ARCHIVE_TYPE aiArchiveType) {
    return FileFinder::GetSingleton() && FileFinder::GetSingleton()->Exist(apName, apFilePath, aiFlags, aiArchiveType);
}

// GAME - 0xAFE0D0
// GECK - 0x8A1FC0
bool FileFinder::Exist(const char* apName, const char* apFilePath, uint32_t aiFlags, ARCHIVE_TYPE aiArchiveType) {
#ifdef GAME
    return ThisCall<bool>(0xAFE0D0, this, apName, apFilePath, aiFlags, aiArchiveType);
#else
    return ThisCall<bool>(0x8A1FC0, this, apName, apFilePath, aiFlags, aiArchiveType);
#endif
}