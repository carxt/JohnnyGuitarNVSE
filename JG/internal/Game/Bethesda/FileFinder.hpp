#pragma once

#include "BSFile.hpp"
#include "BSEnums.hpp"
#include "BSSimpleArray.hpp"
#include "BSSimpleList.hpp"

class FileFinder {
public:
	BSSimpleArray<const char*> kPaths;

	enum LookIn {
		SKIP_NONE		= 0,
		SKIP_ARCHIVE	= 1,
		SKIP_CWD		= 2,
		SKIP_PATHS		= 4,
	};

	static FileFinder* GetSingleton();

	static BSFile* GetFile(const char* apName, NiFile::OpenMode aeMode, uint32_t auiSize, ARCHIVE_TYPE aeArchiveType);

	static bool Locate(const char* apName, char* apFilePath, uint32_t auiFlags, ARCHIVE_TYPE aeArchiveType);

	static BSSimpleList<char const*>* BuildFileList(const char* apSearchName, const char* apBaseFilename, ARCHIVE_TYPE aeArchiveType, BSSimpleList<char const*>* apFileList);

	bool Exist(const char* apName, char* apFilePath, uint32_t auiFlags, ARCHIVE_TYPE aeArchiveType);

	uint32_t LookForFile(const char* apName, uint32_t auiFlags, ARCHIVE_TYPE aeArchiveType);
};

ASSERT_SIZE(FileFinder, 0x10);