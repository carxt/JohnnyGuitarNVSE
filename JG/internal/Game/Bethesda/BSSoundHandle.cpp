#include "BSSoundHandle.hpp"

void BSSoundHandle::Clear() {
	uiSoundID		= UINT32_MAX;
	bAssumeSuccess	= false;
	uiState			= 0;
}

// GAME - 0xAD8CE0
// GECK - 0x8866E0
bool BSSoundHandle::IsValid() const {
#ifdef GAME
	return ThisCall<bool>(0xAD8CE0, this);
#else
	return ThisCall<bool>(0x8866E0, this);
#endif
}

// GAME - 0xAD8930
// GECK - 0x886330
bool BSSoundHandle::IsPlaying() const {
#ifdef GAME
	return ThisCall<bool>(0xAD8930, this);
#else
	return ThisCall<bool>(0x886330, this);
#endif
}

// GAME - 0xAD8B30
uint32_t BSSoundHandle::GetDuration() const {
	return ThisCall<uint32_t>(0xAD8B30, this);
}

// GAME - 0xAD8830
// GECK - 0x886230
bool BSSoundHandle::Play(bool abLoopPlayback) {
#ifdef GAME
	return ThisCall<bool>(0xAD8830, this, abLoopPlayback);
#else
	return ThisCall<bool>(0x886230, this, abLoopPlayback);
#endif
}

// GAME - 0xAD8D60
// GECK - 0x886760
bool BSSoundHandle::FadeInPlay(uint32_t auiMilliseconds) {
#ifdef GAME
	return ThisCall<bool>(0xAD8D60, this, auiMilliseconds);
#else 
	return ThisCall<bool>(0x886760, this, auiMilliseconds);
#endif
}

// GAME - 0xAD88F0
// GECK - 0x8862F0
bool BSSoundHandle::Stop() {
#ifdef GAME
	return ThisCall<bool>(0xAD88F0, this);
#else
	return ThisCall<bool>(0x8862F0, this);
#endif
}

// GAME - 0xAD8D10
// GECK - 0x886710
bool BSSoundHandle::Release() {
#ifdef GAME
	return ThisCall<bool>(0xAD8D10, this);
#else
	return ThisCall<bool>(0x886710, this);
#endif
}

// GAME - 0xAD9030
// GECK - 0x886A30
void BSSoundHandle::SetPriority(uint8_t aucPriority) const {
#ifdef GAME
	ThisCall(0xAD9030, this, aucPriority);
#else
	ThisCall(0x886A30, this, aucPriority);
#endif
}

// GAME - 0xAD89B0
// GECK - 0x8863B0
bool BSSoundHandle::SetStaticAttenuation(uint16_t ausAttenuation) {
#ifdef GAME
	return ThisCall<bool>(0xAD89B0, this, ausAttenuation);
#else
	return ThisCall<bool>(0x8863B0, this, ausAttenuation);
#endif
}

// GAME - 0xAD8C70
// GECK - 0x886670
bool BSSoundHandle::SetReverbAttenuation(uint16_t ausAttenuation) {
#ifdef GAME
	return ThisCall<bool>(0xAD8C70, this, ausAttenuation);
#else
	return ThisCall<bool>(0x886670, this, ausAttenuation);
#endif
}

// GAME - 0xAD89E0
// GECK - 0x8863E0
bool BSSoundHandle::SetVolume(float afVolume) {
#ifdef GAME
	return ThisCall<bool>(0xAD89E0, this, afVolume);
#else
	return ThisCall<bool>(0x8863E0, this, afVolume);
#endif
}

// GAME - 0xAD8A90
// GECK - 0x886490
bool BSSoundHandle::SetSpeed(float afSpeed) {
#ifdef GAME
	return ThisCall<bool>(0xAD8A90, this, afSpeed);
#else
	return ThisCall<bool>(0x886490, this, afSpeed);
#endif
}

// GAME - 0xAD8B60
// GECK - 0x886560
bool BSSoundHandle::SetPosition(NiPoint3 akPosition) {
#ifdef GAME
	return ThisCall<bool>(0xAD8B60, this, akPosition);
#else
	return ThisCall<bool>(0x886560, this, akPosition);
#endif
}

// GAME - 0xAD8F20
void BSSoundHandle::SetObjectToFollow(NiAVObject* apObject) {
	ThisCall(0xAD8F20, this, apObject);
}

// GAME - 0xAD8BE0
// GECK - 0x8865E0
void BSSoundHandle::SetMinMax(float afMin, float afMax) {
#ifdef GAME
	ThisCall(0xAD8BE0, this, afMin, afMax);
#else
	ThisCall(0x8865E0, this, afMin, afMax);
#endif
}

// GAME - 0xAD8C20
// GECK - 0x886620
void BSSoundHandle::SetAttenuationCurve(uint16_t ausVal0, uint16_t ausVal1, uint16_t ausVal2, uint16_t ausVal3, uint16_t ausVal4) {
#ifdef GAME
	ThisCall(0xAD8C20, this, ausVal0, ausVal1, ausVal2, ausVal3, ausVal4);
#else
	ThisCall(0x886620, this, ausVal0, ausVal1, ausVal2, ausVal3, ausVal4);
#endif
}

// GAME - 0xAD8DA0
// GECK - 0x8867A0
bool BSSoundHandle::FadeOutAndRelease(uint32_t auiMilliseconds) {
#ifdef GAME
	return ThisCall<bool>(0xAD8DA0, this, auiMilliseconds);
#else
	return ThisCall<bool>(0x8867A0, this, auiMilliseconds);
#endif
}
