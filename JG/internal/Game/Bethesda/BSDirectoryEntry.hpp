#pragma once

#include "BSHash.hpp"
#include "BSFileEntry.hpp"

class BSDirectoryEntry : public BSHash {
public:
	BSDirectoryEntry() : uiFiles(0), pFiles(nullptr) {};

	uint32_t		uiFiles;
	BSFileEntry*	pFiles;

	bool IsFileEntryInDirectory(BSFileEntry* apFileEntry) const;
};

ASSERT_SIZE(BSDirectoryEntry, 0x10);