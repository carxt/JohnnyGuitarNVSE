#include "TESModelList.hpp"

// GAME - 0x48D150
const TESTextureListArray* TESModelList::GetTextureListArray() const {
	return &kTextures;
}

// GAME - 0x48D150
TESTextureListArray* TESModelList::GetTextureListArray() {
	return &kTextures;
}

// GAME - 0x489FA0
// GECK - 0x504220
void TESModelList::AddModel(const char* apPath) {
#ifdef GAME
	ThisCall(0x489FA0, this, apPath);
#else
	ThisCall(0x504220, this, apPath);
#endif
}

// GAME - 0x489F20
// GECK - 0x503F10
bool TESModelList::IsModelInList(const char* apPath) const {
#ifdef GAME
	return ThisCall<bool>(0x489F20, this, apPath);
#else
	return ThisCall<bool>(0x503F10, this, apPath);
#endif
}
