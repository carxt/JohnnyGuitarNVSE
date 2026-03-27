#include "TESModel.hpp"

// GAME - 0x4AE8F0
bool TESModel::GetHasFacegenData() const {
	return ucFlags.bHasFacegen;
}

void TESModel::SetHasFacegenData(bool abVal) {
	ucFlags.bHasFacegen = abVal;
}

// GAME - 0x4ABF80
uint32_t TESModel::GetSkinFlags() const {
	return ucFlags.Get(Flags::SKIN_MASK);
}

// GAME - 0x4895B0
const char* TESModel::GetModel(const TESForm* apForm) {
	return CdeclCall<const char*>(0x4895B0, apForm);
}
