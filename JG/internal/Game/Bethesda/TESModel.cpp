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
// GECK - 0x501B20
const char* TESModel::GetModel(const TESForm* apForm) {
#ifdef GAME
	return CdeclCall<const char*>(0x4895B0, apForm);
#else
	return CdeclCall<const char*>(0x501B20, apForm);
#endif
}

// GAME - 0x48CEE0
// GECK - 0x4497D0
uint32_t TESModel::GetModelLength() const {
#ifdef GAME
	return ThisCall<uint32_t>(0x48CEE0, this);
#else
	return ThisCall<uint32_t>(0x4497D0, this);
#endif
}

// GAME - 0x489540
// GECK - 0x501FA0
uint32_t TESModel::GetModelLength(const TESForm* apForm) {
#ifdef GAME
	return CdeclCall<uint32_t>(0x489540, apForm);
#else
	return CdeclCall<uint32_t>(0x501FA0, apForm);
#endif
}
