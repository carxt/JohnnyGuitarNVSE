#include "TESFile.hpp"

// GAME - 0x4739B0
// GECK - 0x4E2E40
TESFile* TESFile::GetThreadSafeFile() {
#ifdef GAME
	return ThisCall<TESFile*>(0x4739B0, this);
#else
	return ThisCall<TESFile*>(0x4E2E40, this);
#endif
}

// GAME - 0x473C70
// GECK - 0x4DEA80
TESFile* TESFile::GetThreadSafeParent() const {
#ifdef GAME
	return ThisCall<TESFile*>(0x473C70, this);
#else
	return ThisCall<TESFile*>(0x4DEA80, this);
#endif
}

// GAME - 0x471C20
// GECK - 0x4DE370
bool TESFile::IsMaster() const {
	return uiFlags.bMaster;
}