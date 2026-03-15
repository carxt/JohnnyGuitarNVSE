#pragma once

class BSFileEntry;

class TESTextureList {
public:
	uint8_t			ucCount;
	BSFileEntry**	pFileEntries;
};

ASSERT_SIZE(TESTextureList, 0x8);