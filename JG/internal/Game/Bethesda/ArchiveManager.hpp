#pragma once

#include "BSEnums.hpp"

class Archive;
class BSFileEntry;
class ArchiveFile;
class BSHash;

class ArchiveManager {
public:
#ifdef GAME
	static constexpr AddressPtr<bool, 0x11ACDF9>						bInvalidateOlderFiles;
#else
	static constexpr AddressPtr<bool, 0xEB7DD1>							bInvalidateOlderFiles;
#endif

	static Archive* OpenArchive(const char* apArchiveName, uint16_t aiForceArchiveType, bool abInvalidateOtherArchives);

	static Archive* GetArchiveForFile(const char* apFileName, ARCHIVE_TYPE aeArchiveType);
	static Archive* GetArchiveForFileEntry(BSFileEntry* apFileEntry, ARCHIVE_TYPE aeArchiveType);
	static Archive* GetArchiveByName(const char* apArchiveName);

	static bool FindFile(const char* apFileName, ARCHIVE_TYPE aeArchiveType);

	static ArchiveFile* GetFile(const char* apFileName, uint32_t aiBufferSize, ARCHIVE_TYPE aeArchiveType);
	static ArchiveFile* GetFileByFileEntry(ARCHIVE_TYPE_INDEX aeArchiveTypeIndex, BSFileEntry* apFileEntry, uint32_t auiBufferSize, const char* apFileName);
	static BSFileEntry* GetFileEntryForFileFromAllArchives(ARCHIVE_TYPE_INDEX aeArchiveTypeIndex, const BSHash& arDirectoryHash, const BSHash& arFileNameHash, const char* apFileName);

	static ARCHIVE_TYPE GetArchiveTypeFromFileName(const char* apFileName);
	static ARCHIVE_TYPE GetArchiveTypeFromFileExtension(const char* apExtension);

	static bool GetFileNameForSmallestFileInDirectory(const char* apDirectory, char* apFileName, ARCHIVE_TYPE aeArchiveType);
	static bool GetRandomFileNameForDirectory(const char* apDirectory, char* apFileName, ARCHIVE_TYPE aeArchiveType);

	static bool WildCardMatch(const char* apSearchName, const BSHash& arHash);

	static const char* TrimFileName(const char* apFileName);
};