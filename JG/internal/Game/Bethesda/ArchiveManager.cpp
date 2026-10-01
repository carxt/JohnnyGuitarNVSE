#include "ArchiveManager.hpp"

// GAME - 0xAF4BE0
// GECK - 0x8A35C0
Archive* ArchiveManager::OpenArchive(const char* apArchiveName, uint16_t aiForceArchiveType, bool abInvalidateOtherArchives) {
#ifdef GAME
	return CdeclCall<Archive*>(0xAF4BE0, apArchiveName, aiForceArchiveType, abInvalidateOtherArchives);
#else
	return CdeclCall<Archive*>(0x8A35C0, apArchiveName, aiForceArchiveType, abInvalidateOtherArchives);
#endif
}

// GAME - 0xAF6160
// GECK - 0x8A4B40
Archive* ArchiveManager::GetArchiveForFile(const char* apFileName, ARCHIVE_TYPE aeArchiveType) {
#ifdef GAME
	return CdeclCall<Archive*>(0xAF6160, apFileName, aeArchiveType);
#else
	return CdeclCall<Archive*>(0x8A4B40, apFileName, aeArchiveType);
#endif
}

// GAME - 0xAF6910
// GECK - 0x8A52F0
Archive* ArchiveManager::GetArchiveForFileEntry(BSFileEntry* apFileEntry, ARCHIVE_TYPE aeArchiveType) {
#ifdef GAME
	return CdeclCall<Archive*>(0xAF6910, apFileEntry, aeArchiveType);
#else
	return CdeclCall<Archive*>(0x8A52F0, apFileEntry, aeArchiveType);
#endif
}

// GAME - 0xAF5320
// GECK - 0x8A3D00
Archive* ArchiveManager::GetArchiveByName(const char* apArchiveName) {
#ifdef GAME
	return CdeclCall<Archive*>(0xAF5320, apArchiveName);
#else
	return CdeclCall<Archive*>(0x8A3D00, apArchiveName);
#endif
}

// GAME - 0xAF6320
// GECK - 0x8A4D00
bool ArchiveManager::FindFile(const char* apFileName, ARCHIVE_TYPE aeArchiveType) {
#ifdef GAME
	return CdeclCall<bool>(0xAF6320, apFileName, aeArchiveType);
#else
	return CdeclCall<bool>(0x8A4D00, apFileName, aeArchiveType);
#endif
}

// GAME - 0xAF5FA0
// GECK - 0x8A4980
ArchiveFile* ArchiveManager::GetFile(const char* apFileName, uint32_t aiBufferSize, ARCHIVE_TYPE aeArchiveType) {
#ifdef GAME
	return CdeclCall<ArchiveFile*>(0xAF5FA0, apFileName, aiBufferSize, aeArchiveType);
#else
	return CdeclCall<ArchiveFile*>(0x8A4980, apFileName, aiBufferSize, aeArchiveType);
#endif
}

// GAME - 0xAF6340
// GECK - 0x8A4D20
ArchiveFile* ArchiveManager::GetFileByFileEntry(ARCHIVE_TYPE_INDEX aeArchiveTypeIndex, BSFileEntry* apFileEntry, uint32_t auiBufferSize, const char* apFileName) {
#ifdef GAME
	return CdeclCall<ArchiveFile*>(0xAF6340, aeArchiveTypeIndex, apFileEntry, auiBufferSize, apFileName);
#else
	return CdeclCall<ArchiveFile*>(0x8A4D20, aeArchiveTypeIndex, apFileEntry, auiBufferSize, apFileName);
#endif
}

// GAME - 0xAF6540
// GECK - 0x8A4F20
BSFileEntry* ArchiveManager::GetFileEntryForFileFromAllArchives(ARCHIVE_TYPE_INDEX aeArchiveTypeIndex, const BSHash& arDirectoryHash, const BSHash& arFileHash, const char* apFileName) {
#ifdef GAME
	return CdeclCall<BSFileEntry*>(0xAF6540, aeArchiveTypeIndex, &arDirectoryHash, &arFileHash, apFileName);
#else
	return CdeclCall<BSFileEntry*>(0x8A4F20, aeArchiveTypeIndex, &arDirectoryHash, &arFileHash, apFileName);
#endif
}

// GAME - 0xAF7D80
// GECK - 0x8A6760
ARCHIVE_TYPE ArchiveManager::GetArchiveTypeFromFileName(const char* apFileName) {
#ifdef GAME
    return CdeclCall<ARCHIVE_TYPE>(0xAF7D80, apFileName);
#else
    return CdeclCall<ARCHIVE_TYPE>(0x8A6760, apFileName);
#endif
}

// GAME - 0xAF7DB0
// GECK - 0x8A6790
ARCHIVE_TYPE ArchiveManager::GetArchiveTypeFromFileExtension(const char* apExtension) {
#ifdef GAME
	return CdeclCall<ARCHIVE_TYPE>(0xAF7DB0, apExtension);
#else
	return CdeclCall<ARCHIVE_TYPE>(0x8A6790, apExtension);
#endif
}

// GAME - 0xAF7800
// GECK - 0x8A61E0
bool ArchiveManager::GetFileNameForSmallestFileInDirectory(const char* apDirectory, char* apFileName, ARCHIVE_TYPE aeArchiveType) {
#ifdef GAME
	return CdeclCall<bool>(0xAF7800, apDirectory, apFileName, aeArchiveType);
#else
	return CdeclCall<bool>(0x8A61E0, apDirectory, apFileName, aeArchiveType);
#endif
}

// GAME - 0xAF7400
// GECK - 0x8A5DE0
bool ArchiveManager::GetRandomFileNameForDirectory(const char* apDirectory, char* apFileName, ARCHIVE_TYPE aeArchiveType) {
#ifdef GAME
	return CdeclCall<bool>(0xAF7400, apDirectory, apFileName, aeArchiveType);
#else
	return CdeclCall<bool>(0x8A5DE0, apDirectory, apFileName, aeArchiveType);
#endif
}

// GAME - 0xAF7E80
// GECK - 0x8A6860
bool ArchiveManager::WildCardMatch(const char* apSearchName, const BSHash& arHash) {
#ifdef GAME
	return CdeclCall<bool>(0xAF7E80, apSearchName, &arHash);
#else
	return CdeclCall<bool>(0x8A6860, apSearchName, &arHash);
#endif
}

// GAME - 0xB014B0
// GECK - 0x8AE550
const char* ArchiveManager::TrimFileName(const char* apFileName) {
#ifdef GAME
	return CdeclCall<const char*>(0xB014B0, apFileName);
#else
	return CdeclCall<const char*>(0x8AE550, apFileName);
#endif
}
