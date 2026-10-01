#pragma once

#include "BSEnums.hpp"
#include "BSFile.hpp"
#include "BSArchive.hpp"
#include "BSCriticalSection.hpp"
#include "Gamebryo/NiRefObject.hpp"

NiSmartPointer(Archive);

class ArchiveFile;

class Archive : public BSFile, public NiRefObject, public BSArchive {
public:
	Archive();
	~Archive();

	struct ALIGN1 _ArchiveFlags {
		enum Flags : uint8_t {
			DISABLED				= 1u << 0,
			PRIMARY					= 1u << 2,
			SECONDARY				= 1u << 3,
			HAS_DIRECTORY_STRINGS	= 1u << 4,
			HAS_FILE_STRINGS		= 1u << 5,
		};

		bool bDisabled				: 1;
		bool						: 1;
		bool bPrimary				: 1;
		bool bSecondary				: 1;
		bool bHasDirectoryStrings	: 1;
		bool bHasFileStrings		: 1;
	};
	using ArchiveFlags = _ArchiveFlags::Flags;

	time_t					ulArchiveFileTime;
	uint32_t				uiFileNameArrayOffset;
	uint32_t				uiLastDirectoryIndex;
	uint32_t				uiLastFileIndex;
	BSCriticalSection		kArchiveCriticalSection;
	Bitfield<_ArchiveFlags>	ucArchiveFlags;
	char*					pDirectoryStringArray;
	uint32_t*				pDirectoryStringOffsets;
	char*					pFileNameStringArray;
	uint32_t**				pFileNameStringOffsets;
	uint32_t				uiID;

	bool IsType(ARCHIVE_TYPE aeArchiveType) const;

	bool IsType(ARCHIVE_TYPE_INDEX aeArchiveTypeIndex) const;

	bool GetHasDirectoryStrings() const;
	void SetHasDirectoryStrings(bool abHasDirectoryStrings);

	bool GetHasFileStrings() const;
	void SetHasFileStrings(bool abHasFileStrings);

	const char* GetFileNameForFileEntry(BSFileEntry* apFileEntry);

	bool FindFile(const BSHash& arDirectoryHash, const BSHash& arFileNameHash, uint32_t& arDirectoryID, uint32_t& arFileID, const char* apFileName);

	ArchiveFile* GetFile(uint32_t auiDirectoryIndex, uint32_t auiFileIndex, uint32_t auiBufferSize, const char* apFileName);

	BSFileEntry* GetFileEntryForFile(const BSHash& arDirectoryHash, const BSHash& arFileNameHash, const char* apFileName);

	const char* GetDirectoryString(uint32_t auiDirectoryIndex);

	const char* GetFileString(uint32_t auiDirectoryIndex, uint32_t auiFileIndex);
};

ASSERT_SIZE(Archive, 0x1D0);