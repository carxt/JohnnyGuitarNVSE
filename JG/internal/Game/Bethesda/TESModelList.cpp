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
void TESModelList::AddModel(const char* apPath) {
	ThisCall(0x489FA0, this, apPath);
}

// GAME - 0x489F20
bool TESModelList::IsModelInList(const char* apPath) const {
	return ThisCall<bool>(0x489F20, this, apPath);
}
