#pragma once

#include "Archive.hpp"

class ArchiveFile : public BSFile {
public:
	ArchiveFile();
	~ArchiveFile();

	NiPointer<Archive>	spArchive;
	uint32_t			uiArchiveOffset;
};

ASSERT_SIZE(ArchiveFile, 0x160);