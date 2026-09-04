#pragma once

class BSFileEntry;

class TESTextureList {
public:
#ifdef GAME
	uint8_t			ucCount;
	BSFileEntry**	pFileEntries;
#else
	void*			pHead;
	void*			pTail;
	uint32_t		uiCount;
#endif
};

#ifdef GAME
ASSERT_SIZE(TESTextureList, 0x8);
#else
ASSERT_SIZE(TESTextureList, 0xC);
#endif