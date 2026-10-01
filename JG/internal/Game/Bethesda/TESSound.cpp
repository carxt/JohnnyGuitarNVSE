#include "TESSound.hpp"

// GAME - 0x82D660
uint8_t TESSound::GetMinDistance() const {
	return kData.ucMinDistance;
}

void TESSound::SetMinDistance(uint8_t aucVal) {
	kData.ucMinDistance = aucVal;
}

// GAME - 0x553B90
uint8_t TESSound::GetMaxDistance() const {
	return kData.ucMaxDistance;
}

void TESSound::SetMaxDistance(uint8_t aucVal) {
	kData.ucMaxDistance = aucVal;
}

bool TESSound::GetFlag(uint32_t auiFlag) const {
	return kData.uiFlags.IsSet(auiFlag);
}

void TESSound::SetFlag(uint32_t auiFlag, bool abSet) {
	kData.uiFlags.Set(auiFlag, abSet);
}

// GAME - 0x82D6E0
uint8_t TESSound::GetStartTime() const {
	return kData.ucStartTime;
}

void TESSound::SetStartTime(uint8_t aucTime) {
	kData.ucStartTime = aucTime;
}

// GAME - 0x82D700
uint8_t TESSound::GetEndTime() const {
	return kData.ucEndTime;
}

void TESSound::SetEndTime(uint8_t aucTime) {
	kData.ucEndTime = aucTime;
}

// GAME - 0x82D680
uint16_t TESSound::GetStaticAttenuation() const {
	return kData.usStaticAttenuation;
}

void TESSound::SetStaticAttenuation(uint16_t ausVal) {
	kData.usStaticAttenuation = ausVal;
}

// GAME - 0x82D6A0
uint16_t TESSound::GetAttenuationCurveValue(int32_t aiIndex) const {
	return kData.usAttenuationCurve[aiIndex];
}

void TESSound::SetAttenuationCurveValue(int32_t aiIndex, uint16_t ausVal) {
	kData.usAttenuationCurve[aiIndex] = ausVal;
}

// GAME - 0x82D6C0
uint16_t TESSound::GetReverbAttenuation() const {
	return kData.usReverbAttenuation;
}

void TESSound::SetReverbAttenuation(uint16_t ausVal) {
	kData.usReverbAttenuation = ausVal;
}

// GAME - 0x82D720
uint32_t TESSound::GetPriority() const {
	return kData.uiPriority;
}

void TESSound::SetPriority(uint32_t auiPriority) {
	kData.uiPriority = auiPriority;
}

// GAME - 0x4E75D0
TESSound::Data TESSound::GetData() const {
	return kData;
}

// GAME - 0x553B60
int8_t TESSound::GetRandomPercentChance() const {
#ifdef GAME
	return ThisCall<int8_t>(0x553B60, this);
#else
	if (kData.uiFlags.bPlayAtRandom)
		return cRandomPercentChance;
	return 0;
#endif
}

// GAME - 0x511840
const char* TESSound::GetFilename() const {
	return GetSoundFile();
}

// GAME - 0x5E3570
// GECK - 0x5CC110
TESSound* TESSound::FindSoundByFilename(const char* apName) {
#ifdef GAME
	return CdeclCall<TESSound*>(0x5E3570, apName);
#else
	return CdeclCall<TESSound*>(0x5CC110, apName);
#endif
}
