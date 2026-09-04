#pragma once

#include "BSDirectoryEntry.hpp"

class BSArchiveHeader {
public:
	struct ALIGN4 _ArchiveHeaderFlags {
		enum Flags : uint32_t {
			HAS_DIRECTORY_STRINGS			= 1u << 0,
			HAS_FILE_STRINGS				= 1u << 1,
			COMPRESSED						= 1u << 2,
			RETAIN_DIRECTORY_NAMES			= 1u << 3,
			RETAIN_FILE_NAMES				= 1u << 4,
			RETAIN_FILE_NAME_OFFSETS		= 1u << 5,
			XBOX_ARCHIVE					= 1u << 6,
			RETAIN_STRINGS_DURING_STARTUP	= 1u << 7,
			EMBEDDED_FILE_NAMES				= 1u << 8,
			XBOX_COMPRESSED					= 1u << 9,
		};

		bool bHasDirectoryStrings			: 1;
		bool bHasFileStrings				: 1;
		bool bIsCompressed					: 1;
		bool bRetainDirectoryNames			: 1;
		bool bRetainFileNames				: 1;
		bool bRetainFileNameOffsets			: 1;
		bool bIsXBoxArchive					: 1;
		bool bRetainStringsDuringStartup	: 1;
		bool bHasEmbeddedFileNames			: 1;
		bool bIsXBoxCompressed				: 1;
	};
	using ArchiveHeaderFlags = _ArchiveHeaderFlags::Flags;

	uint32_t						uiTag;
	uint32_t						uiVersion;
	uint32_t						uiHeaderSize;
	Bitfield<_ArchiveHeaderFlags>	uiFlags;
	uint32_t						uiDirectories;
	uint32_t						uiFiles;
	uint32_t						uiDirectoryNamesLength;
	uint32_t						uiFileNamesLength;
	Bitfield16						usArchiveType;
};

ASSERT_SIZE(BSArchiveHeader, 0x24);

class BSArchive : public BSArchiveHeader {
public:
	BSDirectoryEntry* pDirectories;

	bool IsCompressed() const { return uiFlags.bIsCompressed; }

	bool IsXBoxArchive() const { return uiFlags.bIsXBoxArchive; }

	bool IsXBoxCompressed() const { return uiFlags.bIsXBoxCompressed; }

	bool HasEmbeddedFileNames() const { return uiFlags.bHasEmbeddedFileNames; }

	bool HasDirectoryStrings() const { return uiFlags.bHasDirectoryStrings; }

	bool HasFileStrings() const { return uiFlags.bHasFileStrings; }

	bool RetainDirectoryNames() const { return uiFlags.bRetainDirectoryNames; }

	bool RetainFileNames() const { return uiFlags.bRetainFileNames; }

	bool RetainFileNameOffsets() const { return uiFlags.bRetainFileNameOffsets; }

	bool RetainStringsDuringStartup() const { return uiFlags.bRetainStringsDuringStartup; }

	bool IsFileEntryInArchive(BSFileEntry* apFileEntry) const;
};

ASSERT_SIZE(BSArchive, 0x28);