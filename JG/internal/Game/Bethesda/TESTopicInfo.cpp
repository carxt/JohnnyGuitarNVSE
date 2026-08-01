#include "TESTopicInfo.hpp"

// GAME - 0x500940
const TESCondition* TESTopicInfo::GetInfoConditions() const {
	return &kConditions;
}

// GAME - 0x500940
TESCondition* TESTopicInfo::GetInfoConditions() {
	return &kConditions;
}

// GAME - 0x61E0F0
void TESTopicInfo::SetInfoConditions(TESCondition* apConditions) {
	ThisCall(0x61E0F0, this, apConditions);
}

// GAME - 0x619A70
uint16_t TESTopicInfo::GetInfoIndex() const {
	return usInfoIndex;
}

// GAME - 0x61F340
void TESTopicInfo::SetInfoIndex(uint16_t ausIndex) {
	usInfoIndex = ausIndex;
}

// GAME - 0x619B40
bool TESTopicInfo::GetSaidOnce() const {
	return bSaidOnce;
}

// GAME - 0x61F220
void TESTopicInfo::SetSaidOnce() {
	ThisCall(0x61F220, this);
}

// GAME - 0x61F280
void TESTopicInfo::ResetSaidOnceFlags() {
	ThisCall(0x61F280, this);
}

DIALOGUE_TYPE TESTopicInfo::GetDialogueType() const {
	return static_cast<DIALOGUE_TYPE>(kData.eType);
}

void TESTopicInfo::SetDialogueType(DIALOGUE_TYPE aeType) {
	kData.eType = aeType;
}

// GAME - 0x61B9F0
DIALOGUE_SPEAKER TESTopicInfo::GetNextSpeaker() const {
	return static_cast<DIALOGUE_SPEAKER>(kData.eNextSpeaker);
}

void TESTopicInfo::SetNextSpeaker(DIALOGUE_SPEAKER aeSpeaker) {
	kData.eNextSpeaker = aeSpeaker;
}

// GAME - 0x619DF0
bool TESTopicInfo::IsGoodbye() const {
	return kData.usFlags.bGoodbye;
}

// GAME - 0x619410
bool TESTopicInfo::IsRandom() const {
	return kData.usFlags.bRandom;
}

// GAME - 0x619B20
bool TESTopicInfo::IsSayOnce() const {
	return kData.usFlags.bSayOnce;
}

// GAME - 0x579200
bool TESTopicInfo::IsRunImmediately() const {
	return kData.usFlags.bRunImmediately;
}

// GAME - 0x61F260
bool TESTopicInfo::IsInfoRefusal() const {
	return kData.usFlags.bInfoRefusal;
}

// GAME - 0x61AED0
bool TESTopicInfo::IsRandomEnd() const {
	return kData.usFlags.bRandomEnd;
}

// GAME - 0x83EC10
bool TESTopicInfo::IsRunForRumors() const {
	return kData.usFlags.bRunForRumors;
}

// GAME - 0x7627C0
bool TESTopicInfo::IsSpeechChallenge() const {
	return kData.usFlags.bSpeechChallenge;
}

// GAME - 0x61AEF0
bool TESTopicInfo::IsSayOnceADay() const {
	return kData.usFlags.bSayOnceADay;
}

// GAME - 0x763FD0
bool TESTopicInfo::IsAlwaysDarkened() const {
	return kData.usFlags.bAlwaysDarken;
}

// GAME - 0x61E720
TESTopicInfo::IntelligenceCheckType TESTopicInfo::GetIntelligenceCheckType() const {
	return ThisCall<IntelligenceCheckType>(0x61E720, this);
}

// GAME - 0x4610D0
const BSString& TESTopicInfo::GetPrompt() const {
	return strPrompt;
}

// GAME - 0x83DE40
bool TESTopicInfo::HasPrompt() const {
	return ThisCall<bool>(0x83DE40, this);
}

// GAME - 0x61CFD0
void TESTopicInfo::SetPrompt(const char* apText) {
	ThisCall(0x61CFD0, this, apText);
}

// GAME - 0x436AA0
const BSSimpleList<TESTopic*>* TESTopicInfo::GetAddTopicList() const {
	return &kAddTopics;
}

// GAME - 0x436AA0
BSSimpleList<TESTopic*>* TESTopicInfo::GetAddTopicList() {
	return &kAddTopics;
}

// GAME - 0x61F150
void TESTopicInfo::AddTopicList() const {
	ThisCall(0x61F150, this);
}

// GAME - 0x9E32D0
TESConversationData* TESTopicInfo::GetConversationData() const {
	return pConversationData;
}

// GAME - 0x61E180
void TESTopicInfo::SetConversationData(TESConversationData* apData) {
	ThisCall(0x61E180, this, apData);
}

// GAME - 0x639B40
TESActorBase* TESTopicInfo::GetSpeaker() const {
	return pSpeaker;
}

// GAME - 0x409480
void TESTopicInfo::SetSpeaker(TESActorBase* apSpeaker) {
	pSpeaker = apSpeaker;
}

// GAME - 0x7627E0
ActorValueInfo* TESTopicInfo::GetActorValue() const {
	return ThisCall<ActorValueInfo*>(0x7627E0, this);
}

// GAME - 0x87CE80
void TESTopicInfo::SetActorValue(ActorValueInfo* apActorValue) {
	pActorValue = apActorValue;
}

// GAME - 0x762820
BGSPerk* TESTopicInfo::GetPerk() const {
	return ThisCall<BGSPerk*>(0x762820, this);
}

// GAME - 0x87CE80
void TESTopicInfo::SetPerk(BGSPerk* apPerk) {
	pPerk = apPerk;
}

// GAME - 0x8041A0
TESTopicInfo::SpeechChallengeLevel TESTopicInfo::GetDifficultyLevel() const {
	return eSpeechDifficulty;
}

// GAME - 0x8D8040
void TESTopicInfo::SetDifficultyLevel(SpeechChallengeLevel aeLevel) {
	eSpeechDifficulty = aeLevel;
}

// GAME - 0x61F2B0
int32_t TESTopicInfo::GetDifficulty() const {
	return ThisCall<int32_t>(0x61F2B0, this);
}

// GAME - 0x6733E0
TESQuest* TESTopicInfo::GetOwnerQuest() const {
	return pOwnerQuest;
}

// GAME - 0x673400
void TESTopicInfo::SetOwnerQuest(TESQuest* apQuest) {
	pOwnerQuest = apQuest;
}

#if USE_MODDED_CHANGES
TESTopic* TESTopicInfo::GetParentTopic() {
	return pParentTopic;
}
#endif

// GAME - 0x61EB60
Script* TESTopicInfo::GetResultScript(DIALOGUE_SCRIPT_TYPE aeType) {
	return ThisCall<Script*>(0x61EB60, this, aeType);
}

// GAME - 0x61E600
bool TESTopicInfo::CheckCondition(bool& abDispositionFailure, TESQuest* apQuest, TESObjectREFR* apActionRef, TESObjectREFR* apTargetRef) const {
	return ThisCall<bool>(0x61E600, this, &abDispositionFailure, apQuest, apActionRef, apTargetRef);
}

// GAME - 0x61E2B0
void TESTopicInfo::GetInfoDisplayText(BSString& arString, bool abFirstOnly) const {
	ThisCall(0x61E2B0, this, &arString, abFirstOnly);
}
