#include "BSSoundHandle.hpp"

// GAME - 0x41A250
BSSoundHandle::BSSoundHandle() : uiSoundID(UINT32_MAX), bAssumeSuccess(false), eState(AssumedState::INITIALIZED) {}

// GAME - 0x57BD10
BSSoundHandle::BSSoundHandle(uint32_t auiSoundID) : uiSoundID(auiSoundID), bAssumeSuccess(false), eState(AssumedState::INITIALIZED) {}

// GAME - 0x418900
BSSoundHandle::BSSoundHandle(const BSSoundHandle& arOther) : uiSoundID(arOther.uiSoundID), bAssumeSuccess(arOther.bAssumeSuccess), eState(arOther.eState) {}

// GAME - 0x418900
BSSoundHandle BSSoundHandle::operator=(const BSSoundHandle& arOther) {
	uiSoundID = arOther.uiSoundID;
	bAssumeSuccess = arOther.bAssumeSuccess;
	eState = arOther.eState;
	return *this;
}

// GAME - 0x41A1F0
bool BSSoundHandle::operator==(const BSSoundHandle& arOther) const {
	return GetID() == arOther.GetID();
}

// GAME - 0x76B780
bool BSSoundHandle::operator==(uint32_t auiOther) const {
	return GetID() == auiOther;
}

// GAME - 0x559450
uint32_t BSSoundHandle::GetID() const {
	return uiSoundID;
}

// GAME - 0x4F15A0
void BSSoundHandle::SetAssumeSuccess(bool abAssumeSuccess) {
	bAssumeSuccess = abAssumeSuccess;
}

// GAME - 0x44DDC0
BSSoundHandle::AssumedState BSSoundHandle::GetState() const {
	return eState;
}

// GAME - 0x4188D0
void BSSoundHandle::Clear() {
	uiSoundID		= UINT32_MAX;
	bAssumeSuccess	= false;
	eState			= AssumedState::INITIALIZED;
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
// GECK - 0x886530
uint32_t BSSoundHandle::GetDuration() const {
#ifdef GAME
	return ThisCall<uint32_t>(0xAD8B30, this);
#else
	return ThisCall<uint32_t>(0x886530, this);
#endif
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

// GAME - 0xAD8870
// GECK - 0x886270
bool BSSoundHandle::PlayAfter(uint32_t auiDelay, uint32_t auiPlayFlags) {
#ifdef GAME
	return ThisCall<bool>(0xAD8870, this, auiDelay, auiPlayFlags);
#else
	return ThisCall<bool>(0x886270, this, auiDelay, auiPlayFlags);
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

// GAME - 0xAD8F70
// GECK - 0x886970
void BSSoundHandle::Seek(uint32_t auiMilliseconds) {
#ifdef GAME
	ThisCall(0xAD8F70, this, auiMilliseconds);
#else
	ThisCall(0x886970, this, auiMilliseconds);
#endif
}

// GAME - 0xAD88B0
// GECK - 0x8862B0
bool BSSoundHandle::Pause() {
#ifdef GAME
	return ThisCall<bool>(0xAD88B0, this);
#else
	return ThisCall<bool>(0x8862B0, this);
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

// GAME - 0xAD8980
// GECK - 0x886380
uint32_t BSSoundHandle::GetSoundType() const {
#ifdef GAME
	return ThisCall<uint32_t>(0xAD8980, this);
#else
	return ThisCall<uint32_t>(0x886380, this);
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

// GAME - 0xAD8A20
// GECK - 0x886420
float BSSoundHandle::GetVolume() const {
#ifdef GAME
	return ThisCall<float>(0xAD8A20, this);
#else
	return ThisCall<float>(0x886420, this);
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
bool BSSoundHandle::SetPosition(float afX, float afY, float afZ) {
#ifdef GAME
	return ThisCall<bool>(0xAD8B60, this, afX, afY, afZ);
#else
	return ThisCall<bool>(0x886560, this, afX, afY, afZ);
#endif
}

// GAME - 0x68A7D0
bool BSSoundHandle::SetPosition(const NiPoint3& arPosition) {
	return SetPosition(arPosition.x, arPosition.y, arPosition.z);
}

// GAME - 0xAD8FA0
// GECK - 0x8869A0
void BSSoundHandle::SetFollowsListener(bool abFollowsListener) {
#ifdef GAME
	ThisCall(0xAD8FA0, this, abFollowsListener);
#else
	ThisCall(0x8869A0, this, abFollowsListener);
#endif
}

// GAME - 0xAD8F20
// GECK - 0x886920
void BSSoundHandle::SetObjectToFollow(NiAVObject* apObject) {
#ifdef GAME
	ThisCall(0xAD8F20, this, apObject);
#else
	ThisCall(0x886920, this, apObject);
#endif
}

// GAME - 0xAD8BE0
// GECK - 0x8865E0
void BSSoundHandle::SetMinMaxDistance(float afMin, float afMax) {
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

// GAME - 0xAD8BA0
// GECK - 0x8865A0
bool BSSoundHandle::SetBeamEnd(float afX, float afY, float afZ) {
#ifdef GAME
	return ThisCall<bool>(0xAD8BA0, this, afX, afY, afZ);
#else
	return ThisCall<bool>(0x8865A0, this, afX, afY, afZ);
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

// GAME - 0xAD8E20
// GECK - 0x886820
void BSSoundHandle::SetTimeConstraints(uint8_t aucStart, uint8_t aucStop) {
#ifdef GAME
	ThisCall(0xAD8E20, this, aucStart, aucStop);
#else
	ThisCall(0x886820, this, aucStart, aucStop);
#endif
}

// GAME - 0xAD8A50
// GECK - 0x886450
bool BSSoundHandle::SetFrequency(float afFrequency) {
#ifdef GAME
	return ThisCall<bool>(0xAD8A50, this, afFrequency);
#else
	return ThisCall<bool>(0x886450, this, afFrequency);
#endif
}

// GAME - 0xAD8A90
// GECK - 0x886490
bool BSSoundHandle::SetModFrequency(float afFrequency) {
#ifdef GAME
	return ThisCall<bool>(0xAD8A90, this, afFrequency);
#else
	return ThisCall<bool>(0x886490, this, afFrequency);
#endif
}

// GAME - 0xAD8AD0
// GECK - 0x8864D0
bool BSSoundHandle::SetFrequencyVariance(uint8_t aucFreqVariance) {
#ifdef GAME
	return ThisCall<bool>(0xAD8AD0, this, aucFreqVariance);
#else
	return ThisCall<bool>(0x8864D0, this, aucFreqVariance);
#endif
}

// GAME - 0xAD8EC0
// GECK - 0x8868C0
void BSSoundHandle::SetPlayCallback(pfnPlayCallback_t apfnCallback, void* apContext) {
#ifdef GAME
	ThisCall(0xAD8EC0, this, apfnCallback, apContext);
#else
	ThisCall(0x8868C0, this, apfnCallback, apContext);
#endif
}

// GAME - 0xAD8E60
// GECK - 0x886860
void BSSoundHandle::SetCompletionCallback(pfnCompletionCallback_t apfnCallback, void* apContext) {
#ifdef GAME
	ThisCall(0xAD8E60, this, apfnCallback, apContext);
#else
	ThisCall(0x886860, this, apfnCallback, apContext);
#endif
}

// GAME - 0xAD8FD0
// GECK - 0x8869D0
void BSSoundHandle::SetSynchStartTime(uint32_t auiStartTime) {
#ifdef GAME
	ThisCall(0xAD8FD0, this, auiStartTime);
#else
	ThisCall(0x8869D0, this, auiStartTime);
#endif
}

// GAME - 0xAD9000
// GECK - 0x886A00
void BSSoundHandle::ClearSynchStartTime() {
#ifdef GAME
	ThisCall(0xAD9000, this);
#else
	ThisCall(0x886A00, this);
#endif
}
