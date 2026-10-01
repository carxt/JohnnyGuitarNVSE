#include "TESResponse.hpp"

// GAME - 0x6815C0
const TESResponse::Data* TESResponse::GetData() const {
	return &kData;
}

// GAME - 0x6815C0
TESResponse::Data* TESResponse::GetData() {
	return &kData;
}

// GAME - 0x559450
DIALOGUE_EMOTION TESResponse::GetEmotion() const {
	return kData.eEmotionType;
}

void TESResponse::SetEmotion(DIALOGUE_EMOTION aeEmotion) {
	kData.eEmotionType = aeEmotion;
}

// GAME - 0x726070
uint32_t TESResponse::GetEmotionValue() const {
	return kData.uiEmotionValue;
}

// GAME - 0x6ECD40
void TESResponse::SetEmotionValue(uint32_t auiValue) {
	kData.uiEmotionValue = auiValue;
}

// GAME - 0x6174B0
uint8_t TESResponse::GetResponseID() const {
	return kData.ucResponseID;
}

void TESResponse::SetResponseID(uint8_t aucID) {
	kData.ucResponseID = aucID;
}

// GAME - 0x44EDB0
TESSound* TESResponse::GetVoiceSound() const {
	return kData.pVoiceSound;
}

void TESResponse::SetVoiceSound(TESSound* apSound) {
	kData.pVoiceSound = apSound;
}

// GAME - 0x843150
bool TESResponse::GetUseEmotion() const {
	return kData.bUseEmotion;
}

void TESResponse::SetUseEmotion(bool abVal) {
	kData.bUseEmotion = abVal;
}

// GAME - 0x616DE0
// GECK - 0x58C710
const char* TESResponse::GetResponseText() const {
#ifdef GAME
	return ThisCall<const char*>(0x616DE0, this);
#else
	return ThisCall<const char*>(0x58C710, this);
#endif
}

// GAME - 0x83E0A0
// GECK - 0x4060B0
uint32_t TESResponse::GetResponseTextLength() const {
#ifdef GAME
	return ThisCall<uint32_t>(0x83E0A0, this);
#else
	return ThisCall<uint32_t>(0x4060B0, this);
#endif
}

// GAME - 0x61EB40
void TESResponse::SetResponseText(const char* apText) {
#ifdef GAME
	ThisCall(0x61EB40, this, apText);
#else
	strResponseText.Set(apText);
#endif
}

// GAME - 0x7AF430
TESIdleForm* TESResponse::GetSpeakerIdle() const {
	return pSpeakerIdle;
}

// GAME - 0x50F9C0
void TESResponse::SetSpeakerIdle(TESIdleForm* apIdle) {
	pSpeakerIdle = apIdle;
}

// GAME - 0x59BB30
TESIdleForm* TESResponse::GetListenerIdle() const {
	return pListenerIdle;
}

// GAME - 0x7037C0
void TESResponse::GetListenerIdle(TESIdleForm* apIdle) {
	pListenerIdle = apIdle;
}

// GAME - 0x45CD60
TESResponse* TESResponse::GetNext() const {
	return pNext;
}

// GAME - 0x61CC90
void TESResponse::AddTail(TESResponse* apResponse) {
#ifdef GAME
	ThisCall(0x61CC90, this, apResponse);
#else
	TESResponse* pTarget = this;
	for (auto i = GetNext(); i; i = i->GetNext())
		pTarget = pTarget->GetNext();
	pTarget->pNext = apResponse;
#endif
}

// GAME - 0x9369D0
uint32_t TESResponse::GetListCount() const {
#ifdef GAME
	return ThisCall<uint32_t>(0x9369D0, this);
#else
	if (!this)
		return 0;

	uint32_t uiCount = 1;
	for (auto i = GetNext(); i; i = i->GetNext())
		++uiCount;
	return uiCount;
#endif
}

#ifdef GAME
// GAME - 0x616F40
bool TESResponse::GetAudioFullPath(const TESObjectREFR* apSpeaker, const TESQuest* apQuest, const TESTopic* apOwnerTopic, const TESTopicInfo* apOwnerInfo, BSString& arDest) const {
	return ThisCall<bool>(0x616F40, this, apSpeaker, apQuest, apOwnerTopic, apOwnerInfo, &arDest);
}
#endif

// GAME - 0x617400
// GECK - 0x58CEC0
void TESResponse::GetAudioFilename(const TESQuest* apQuest, const TESTopic* apTopic, const TESTopicInfo* apOwnerInfo, BSString& arDest) const {
#ifdef GAME
	ThisCall(0x617400, this, apQuest, apTopic, apOwnerInfo, &arDest);
#else
	ThisCall(0x58CEC0, this, apQuest, apTopic, apOwnerInfo, &arDest);
#endif
}

// GAME - 0x6172C0
// GECK - 0x58C2B0
void TESResponse::GetAudioQuestTopicCombined(const TESQuest* apQuest, const TESTopic* apTopic, char* apOutBuffer, uint32_t auiBufferSize) {
#ifdef GAME
	CdeclCall(0x6172C0, apQuest, apTopic, apOutBuffer, auiBufferSize);
#else
	CdeclCall(0x58C2B0, apQuest, apTopic, apOutBuffer, auiBufferSize);
#endif
}

// GAME - 0x44DEE0
ResponseListWrapper::ResponseListWrapper() {
	pHead = nullptr;
}

// GAME - 0x61F440
ResponseListWrapper::~ResponseListWrapper() {
#ifdef GAME
	ThisCall(0x61F440, this);
#else
	ClearResponseList();
#endif
}

// GAME - 0x9369A0
uint32_t ResponseListWrapper::GetListCount() const {
#ifdef GAME
	return ThisCall<uint32_t>(0x9369A0, this);
#else
	return pHead ? pHead->GetListCount() : 0;
#endif
}

// GAME - 0x61CC60
// GECK - 0x405E10
void ResponseListWrapper::AddTail(TESResponse* apResponse) {
#ifdef GAME
	ThisCall(0x61CC60, this, apResponse);
#else
	ThisCall(0x405E10, this, apResponse);
#endif
}

#ifdef GAME
// GAME - 0x61CB60
void ResponseListWrapper::CopyResponseList(TESResponse* apHead) {
	ThisCall(0x61CB60, this, apHead);
}
#endif

// GAME - 0x61CAD0
// GECK - 0x59AB00
void ResponseListWrapper::ClearResponseList() {
#ifdef GAME
	ThisCall(0x61CAD0, this);
#else
	ThisCall(0x59AB00, this);
#endif
}
