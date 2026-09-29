#pragma once

#include "QueuedFile.hpp"

class BSFileEntry;
class ArchiveFile;

class QueuedFileEntry : public QueuedFile {
public:
	QueuedFileEntry();
	~QueuedFileEntry();

	virtual uint8_t GetFileIndex() const;

	const char*		pFileName;
	BSFileEntry*	pFileEntry;

	const char* GetFileName() const;
	void SetFileName(const char* apFileName);

	BSFileEntry* GetFileEntry() const;
	void SetFileEntry(BSFileEntry* apEntry);

	void LookupFileEntry(ARCHIVE_TYPE_INDEX aeArchiveTypeIndex);
	void GetLookupFileName(ARCHIVE_TYPE_INDEX aeArchiveTypeIndex, char* apBuffer) const;

	bool GetDescription(char* apBuffer, size_t auiBufferSize, const char* apTaskName) const;

	ArchiveFile* GetFile(ARCHIVE_TYPE_INDEX aeArchiveTypeIndex, ARCHIVE_TYPE aeArchiveType);
};

ASSERT_SIZE(QueuedFileEntry, 0x30);