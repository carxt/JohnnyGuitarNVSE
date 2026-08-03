#include "QueuedFileEntry.hpp"

// GAME - 0x45CD60
const char* QueuedFileEntry::GetFileName() const {
    return pFileName;
}

// GAME - 0xC3CEE0
// GECK - 0x9E7630
void QueuedFileEntry::SetFileName(const char* apFileName) {
#ifdef GAME
    ThisCall(0xC3CEE0, this, apFileName);
#else
    ThisCall(0x9E7630, this, apFileName);
#endif
}

// GAME - 0x55B980
BSFileEntry* QueuedFileEntry::GetFileEntry() const {
    return pFileEntry;
}

// GAME - 0xC3CF40
void QueuedFileEntry::SetFileEntry(BSFileEntry* apEntry) {
    pFileEntry = apEntry;
}

// GAME - 0xC3CF60
// GECK - 0x9E76B0
void QueuedFileEntry::LookupFileEntry(ARCHIVE_TYPE_INDEX aeArchiveTypeIndex) {
#ifdef GAME
	ThisCall(0xC3CF60, this, aeArchiveTypeIndex);
#else
	ThisCall(0x9E76B0, this, aeArchiveTypeIndex);
#endif
}

// GAME - 0xC3D090
// GECK - 0x9E77E0
void QueuedFileEntry::GetLookupFileName(ARCHIVE_TYPE_INDEX aeArchiveTypeIndex, char* apBuffer) const {
#ifdef GAME
    ThisCall(0xC3D090, this, aeArchiveTypeIndex, apBuffer);
#else
    ThisCall(0x9E77E0, this, aeArchiveTypeIndex, apBuffer);
#endif
}

// GAME - 0xC3D0E0
// GECK - 0x9E7830
bool QueuedFileEntry::GetDescription(char* apBuffer, size_t auiBufferSize, const char* apTaskName) const {
#ifdef GAME
    return ThisCall<bool>(0xC3D0E0, this, apBuffer, auiBufferSize, apTaskName);
#else
    return ThisCall<bool>(0x9E7830, this, apBuffer, auiBufferSize, apTaskName);
#endif
}

// GAME - 0xC3CFF0
// GECK - 0x9E7740
ArchiveFile* QueuedFileEntry::GetFile(ARCHIVE_TYPE_INDEX aeArchiveTypeIndex, ARCHIVE_TYPE aeArchiveType) {
#ifdef GAME
    return ThisCall<ArchiveFile*>(0xC3CFF0, this, aeArchiveTypeIndex, aeArchiveType);
#else
    return ThisCall<ArchiveFile*>(0x9E7740, this, aeArchiveTypeIndex, aeArchiveType);
#endif
}