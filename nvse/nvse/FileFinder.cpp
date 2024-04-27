#include "FileFinder.h"

FileFinder* FileFinder::GetSingleton() {
    return *(FileFinder**)0x11F81DC;
}

// 0xAFDF20
BSFile* FileFinder::GetFile(const char* apName, OpenMode aeMode, int aiSize, ARCHIVE_TYPE aeArchiveType) {
    return CdeclCall<BSFile*>(0xAFDF20, apName, aeMode, aiSize, aeArchiveType);
}

// 0x456A20
bool FileFinder::Locate(const char* apName, const char* apFilePath, UInt32 aiFlags, ARCHIVE_TYPE aiArchiveType) {
    return FileFinder::GetSingleton() && FileFinder::GetSingleton()->Exist(apName, apFilePath, aiFlags, aiArchiveType);
}

// 0xAFE0D0
bool FileFinder::Exist(const char* apName, const char* apFilePath, UInt32 aiFlags, ARCHIVE_TYPE aiArchiveType) {
    return ThisStdCall<bool>(0xAFE0D0, this, apName, apFilePath, aiFlags, aiArchiveType);
}