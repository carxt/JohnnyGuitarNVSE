#include "TESSound.hpp"

// GAME - 0x4E75D0
TESSound::Data TESSound::GetData() const {
	return kData;
}

bool TESSound::GetFlag(uint32_t auiFlag) const {
	return kData.uiFlags.IsSet(auiFlag);
}

void TESSound::SetFlag(uint32_t auiFlag, bool abSet) {
	kData.uiFlags.Set(auiFlag, abSet);
}

// GAME - 0x82D6E0
uint32_t TESSound::GetStartsAt() const {
	return kData.ucStartsAt;
}

// GAME - 0x82D700
uint32_t TESSound::GetEndsAt() const {
	return kData.ucEndsAt;
}

// GAME - 0x553B60
int8_t TESSound::GetRandomPercentChance() const {
	return ThisCall<int8_t>(0x553B60, this);
}

// GAME - 0x511840
const char* TESSound::GetFilename() const {
	return GetSoundFile();
}