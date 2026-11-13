#include "Archive.hpp"

bool Archive::IsType(ARCHIVE_TYPE aeArchiveType) const {
	return usArchiveType.Get(aeArchiveType);
}

bool Archive::IsType(ARCHIVE_TYPE_INDEX aeArchiveTypeIndex) const {
	return usArchiveType.GetBit(aeArchiveTypeIndex);
}

bool Archive::GetHasDirectoryStrings() const {
	return ucArchiveFlags.bHasDirectoryStrings;
}

void Archive::SetHasDirectoryStrings(bool abHasDirectoryStrings) {
	ucArchiveFlags.bHasDirectoryStrings = abHasDirectoryStrings;
}

bool Archive::GetHasFileStrings() const {
	return ucArchiveFlags.bHasFileStrings;
}

void Archive::SetHasFileStrings(bool abHasFileStrings) {
	ucArchiveFlags.bHasFileStrings = abHasFileStrings;
}

// GAME - 0xAF9BA0
// GECK - 0x8A8580
const char* Archive::GetFileNameForFileEntry(BSFileEntry* apFileEntry) {
#ifdef GAME
	return ThisCall<const char*>(0xAF9BA0, this, apFileEntry);
#else
	return ThisCall<const char*>(0x8A8580, this, apFileEntry);
#endif
}

// GAME - 0xAF9BF0
// GECK - 0x8A85D0
bool Archive::FindFile(const BSHash& arDirectoryHash, const BSHash& arFileNameHash, uint32_t& arDirectoryID, uint32_t& arFileID, const char* apFileName) {
#ifdef GAME
	return ThisCall<bool>(0xAF9BF0, this, &arDirectoryHash, &arFileNameHash, &arDirectoryID, &arFileID, apFileName);
#else
	return ThisCall<bool>(0x8A85D0, this, &arDirectoryHash, &arFileNameHash, &arDirectoryID, &arFileID, apFileName);
#endif
}

// GAME - 0xAFA550
// GECK - 0x8A8F30
ArchiveFile* Archive::GetFile(uint32_t auiDirectoryIndex, uint32_t auiFileIndex, uint32_t auiBufferSize, const char* apFileName) {
#ifdef GAME
	return ThisCall<ArchiveFile*>(0xAFA550, this, auiDirectoryIndex, auiFileIndex, auiBufferSize, apFileName);
#else
	return ThisCall<ArchiveFile*>(0x8A8F30, this, auiDirectoryIndex, auiFileIndex, auiBufferSize, apFileName);
#endif
}

// GAME - 0xAFA6E0
// GECK - 0x8A90C0
BSFileEntry* Archive::GetFileEntryForFile(const BSHash& arDirectoryHash, const BSHash& arFileNameHash, const char* apFileName) {
#ifdef GAME
	return ThisCall<BSFileEntry*>(0xAFA6E0, this, &arDirectoryHash, &arFileNameHash, apFileName);
#else
	return ThisCall<BSFileEntry*>(0x8A90C0, this, &arDirectoryHash, &arFileNameHash, apFileName);
#endif
}

// GAME - 0xAF94C0
// GECK - 0x8A7EA0
const char* Archive::GetDirectoryString(uint32_t auiDirectoryIndex) {
#ifdef GAME
	return ThisCall<const char*>(0xAF94C0, this, auiDirectoryIndex);
#else
	return ThisCall<const char*>(0x8A7EA0, this, auiDirectoryIndex);
#endif
}

// GAME - 0xAF96D0
// GECK - 0x8A80B0
const char* Archive::GetFileString(uint32_t auiDirectoryIndex, uint32_t auiFileIndex) {
#ifdef GAME
	return ThisCall<const char*>(0xAF96D0, this, auiDirectoryIndex, auiFileIndex);
#else
	return ThisCall<const char*>(0x8A80B0, this, auiDirectoryIndex, auiFileIndex);
#endif
}