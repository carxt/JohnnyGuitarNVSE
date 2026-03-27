#include "TESTextureListArray.hpp"

// GAME - 0x4464C0
TESTextureList* TESTextureListArray::GetAt(uint32_t auiIndex) const {
	if (auiIndex >= uiTextureCount)
        return nullptr;
	return ppTextures[auiIndex];
}
