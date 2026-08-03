#pragma once

#include "BSCriticalSection.hpp"
#include "Gamebryo/NiMemObject.hpp"
#include "Gamebryo/NiSmartPointer.hpp"

class BSFile;

NiSmartPointer(LoadedFile);

// NiRefObject in FO3 GECK
class SPEC_EMPTY_BASES LoadedFile : public NiMemObject {
public:
	LoadedFile(const char* apFileName, BSFile* apFile);
	~LoadedFile();

	int32_t		iRefCount;
	const char*	pFileName;
	BSFile*		pFile;
	bool		bAddedToMap;
	bool		bUsed;

	void IncRefCount();
	void DecRefCount();

	BSFile* GetFile();

private:
#ifdef GAME
	static constexpr AddressPtr<BSCriticalSection, 0x11C3B6C> kRefCountCS;
#else
	static constexpr AddressPtr<BSCriticalSection, 0xED36CC> kRefCountCS;
#endif
};

ASSERT_SIZE(LoadedFile, 0x10);