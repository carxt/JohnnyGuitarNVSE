#pragma once

#include "BSSimpleArray.hpp"
#include "BSEnums.hpp"

class BSFile;

class FileFinder {
public:
	BSSimpleArray<const char*> kPaths;

	enum LOOKIN_FLAGS : uint8_t {
		SKIP_NONE		= 0x0,
		SKIP_ARCHIVE	= 0x1,
		SKIP_CWD		= 0x2,
		SKIP_PATHS		= 0x4,
	};
	enum OpenMode {
		READ_ONLY	= 0,
		WRITE_ONLY	= 1,
		APPEND_ONLY = 2,
	};

	static FileFinder* GetSingleton();

	bool Exist(const char* apFileName, char* apFilePath = nullptr, uint32_t auiFlags = SKIP_NONE, ARCHIVE_TYPE aeArchiveType = ARCHIVE_TYPE::ALL) const;

	static BSFile* GetFile(const char* apFileName, OpenMode aeMode, uint32_t auiSize, ARCHIVE_TYPE aeArchiveType = ARCHIVE_TYPE::ALL);

	static bool Locate(const char* apFileName, char* apFilePath = nullptr, uint32_t auiFlags = SKIP_NONE, ARCHIVE_TYPE aeArchiveType = ARCHIVE_TYPE::ALL);
};

ASSERT_SIZE(FileFinder, 0x10);