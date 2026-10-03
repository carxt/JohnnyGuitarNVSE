#pragma once

#include "BSFile.hpp"
#include "BSEnums.hpp"
#include "BSSimpleArray.hpp"
#include "BSSimpleList.hpp"

class FileFinder {
public:
	BSSimpleArray<const char*> kPaths;

	struct _LookInFlags {
		enum Flags {
			SKIP_NONE		= 0,
			SKIP_ARCHIVE	= 1,
			SKIP_CWD		= 2,
			SKIP_PATHS		= 4,
		};
	};
	using LookInFlags = _LookInFlags::Flags;

	static FileFinder* GetSingleton();

	bool Exist(const char* apFileName, char* apFilePath = nullptr, uint32_t auiFlags = LookInFlags::SKIP_NONE, ARCHIVE_TYPE aeArchiveType = ARCHIVE_TYPE::ALL) const;

	uint32_t LookForFile(const char* apFileName, uint32_t auiFlags = LookInFlags::SKIP_NONE, ARCHIVE_TYPE aeArchiveType = ARCHIVE_TYPE::ALL) const;

	static BSFile* GetFile(const char* apFileName, NiFile::OpenMode aeMode, uint32_t auiSize, ARCHIVE_TYPE aeArchiveType = ARCHIVE_TYPE::ALL);

	static bool Locate(const char* apFileName, char* apFilePath, uint32_t auiFlags = LookInFlags::SKIP_NONE, ARCHIVE_TYPE aeArchiveType = ARCHIVE_TYPE::ALL);

	static BSSimpleList<char const*>* BuildFileList(const char* apSearchName, const char* apBaseFilename, ARCHIVE_TYPE aeArchiveType, BSSimpleList<char const*>* apFileList);
};

ASSERT_SIZE(FileFinder, 0x10);