#include "FileFinder.hpp"

// GAME - 0x50F6E0
FileFinder* FileFinder::GetSingleton() {
#ifdef GAME
    return *reinterpret_cast<FileFinder**>(0x11F81DC);
#else
    return *reinterpret_cast<FileFinder**>(0xF22AA0);
#endif
}

// GAME - 0xAFDF20
// GECK - 0x8A1E10
BSFile* FileFinder::GetFile(const char* apName, NiFile::OpenMode aeMode, uint32_t auiSize, ARCHIVE_TYPE aeArchiveType) {
#ifdef GAME
    return CdeclCall<BSFile*>(0xAFDF20, apName, aeMode, auiSize, aeArchiveType);
#else
    return CdeclCall<BSFile*>(0x8A1E10, apName, aeMode, auiSize, aeArchiveType);
#endif
}

// GAME - 0x456A20
// GECK - 0x479630
bool FileFinder::Locate(const char* apName, char* apFilePath, uint32_t auiFlags, ARCHIVE_TYPE aeArchiveType) {
    return FileFinder::GetSingleton() && FileFinder::GetSingleton()->Exist(apName, apFilePath, auiFlags, aeArchiveType);
}

// GAME - 0xAFE420
// GECK - 0x8A2310
BSSimpleList<char const*>* FileFinder::BuildFileList(const char* apSearchName, const char* apBaseFilename, ARCHIVE_TYPE aeArchiveType, BSSimpleList<char const*>* apFileList) {
#ifdef GAME
    return CdeclCall<BSSimpleList<char const*>*>(0xAFE420, apSearchName, apBaseFilename, aeArchiveType, apFileList);
#else
    return CdeclCall<BSSimpleList<char const*>*>(0x8A2310, apSearchName, apBaseFilename, aeArchiveType, apFileList);
#endif
}

// GAME - 0xAFE0D0
// GECK - 0x8A1FC0
bool FileFinder::Exist(const char* apName, char* apFilePath, uint32_t auiFlags, ARCHIVE_TYPE aeArchiveType) {
#ifdef GAME
    return ThisCall<bool>(0xAFE0D0, this, apName, apFilePath, auiFlags, aeArchiveType);
#else
    return ThisCall<bool>(0x8A1FC0, this, apName, apFilePath, auiFlags, aeArchiveType);
#endif
}

// GAME - 0xAFE220
// GECK - 0x8A2110
uint32_t FileFinder::LookForFile(const char* apName, uint32_t auiFlags, ARCHIVE_TYPE aeArchiveType) {
#ifdef GAME
    return ThisCall<uint32_t>(0xAFE220, this, apName, auiFlags, aeArchiveType);
#else
    return ThisCall<uint32_t>(0x8A2110, this, apName, auiFlags, aeArchiveType);
#endif
}
