#pragma once

class hkMemoryRouter;

class bhkThreadMemoryRouter {
public:
	hkMemoryRouter* pHavokMemoryRouter	= nullptr;
	void*			pHavokAlloc			= nullptr;
	DWORD			dwOwnerID			= 0;

	static void Init(bhkThreadMemoryRouter& arRouter);
	static void Quit(bhkThreadMemoryRouter& arRouter);
};

ASSERT_SIZE(bhkThreadMemoryRouter, 0xC);