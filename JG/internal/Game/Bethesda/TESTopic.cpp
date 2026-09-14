#include "TESTopic.hpp"

// GAME - 0x61B9F0
DIALOGUE_TYPE TESTopic::GetDialogueType() const {
	return static_cast<DIALOGUE_TYPE>(kData.cType);
}

// GAME - 0x619DF0
bool TESTopic::IsRumors() const {
	return kData.ucFlags.bRumors;
}

// GAME - 0x619410
bool TESTopic::IsTopLevel() const {
	return kData.ucFlags.bTopLevel;
}

// GAME - 0x83F0D0
DIALOGUE_DUMMY_STATE TESTopic::GetDummyNodeState() const {
#ifdef GAME
	return ThisCall<DIALOGUE_DUMMY_STATE>(0x83F0D0, this);
#else
	if (kData.ucFlags.bDummyOnly)
		return DIALOGUE_DUMMY_STATE::DUMMY;
	else if (kData.ucFlags.bNonDummyOnly)
		return DIALOGUE_DUMMY_STATE::NON_DUMMY;
	else
		return DIALOGUE_DUMMY_STATE::EITHER;
#endif
}

void TESTopic::SetDummyNodeState(DIALOGUE_DUMMY_STATE aeState) {
	kData.ucFlags.Clear(TopicFlags::DUMMY_ONLY | TopicFlags::NON_DUMMY_ONLY);
	if (aeState == DIALOGUE_DUMMY_STATE::DUMMY)
		kData.ucFlags.bDummyOnly = true;
	if (aeState == DIALOGUE_DUMMY_STATE::NON_DUMMY)
		kData.ucFlags.bNonDummyOnly = true;
}

// GAME - 0x5D8A70
const BSSimpleList<QuestInfo*>* TESTopic::GetQuestInfoList() const {
    return &kQuestInfos;
}

// GAME - 0x5D8A70
BSSimpleList<QuestInfo*>* TESTopic::GetQuestInfoList() {
    return &kQuestInfos;
}

// GAME - 0x619C50
// GECK - 0x5936C0
QuestInfo* TESTopic::GetQuestInfoElement(const TESTopicInfo* apTopicInfo) const {
#ifdef GAME
	return ThisCall<QuestInfo*>(0x619C50, this, apTopicInfo);
#else
	return ThisCall<QuestInfo*>(0x5936C0, this, apTopicInfo);
#endif
}

// GAME - 0x526AE0
float TESTopic::GetPriority() const {
    return fPriority;
}

// GAME - 0x965250
void TESTopic::SetPriority(float afVal) {
	fPriority = afVal;
}

// GAME - 0x6A9540
const BSString& TESTopic::GetDummyPrompt() const {
	return strDummyPrompt;
}

// GAME - 0x83DEA0
bool TESTopic::HasDummyPrompt() const {
#ifdef GAME
	return ThisCall<bool>(0x83DEA0, this);
#else
	return strDummyPrompt.GetLength() != 0;
#endif
}

// GAME - 0x619010
void TESTopic::SetDummyPrompt(const char* apText) {
#ifdef GAME
	ThisCall(0x619010, this, apText);
#else
	strDummyPrompt.Set(apText);
#endif
}

// GAME - 0x83DE60
bool TESTopic::IsPersuasion() const {
#ifdef GAME
    return ThisCall<bool>(0x83DE60, this);
#else
	return GetFormID() == 0xFD || GetFormID() == 0x118;
#endif
}

// GAME - 0x619E10
// GECK - 0x593790
TESTopicInfo* TESTopic::GetInfoByID(FormID auiFormID, bool abReverse) {
#ifdef GAME
	return ThisCall<TESTopicInfo*>(0x619E10, this, auiFormID, abReverse);
#else
	return ThisCall<TESTopicInfo*>(0x593790, this, auiFormID, abReverse);
#endif
}

// GECK - 0x593810
TESTopicInfo* TESTopic::GetInfoByIndex(const TESQuest* apQuest, uint32_t auiIndex) const {
#ifdef GAME
	auto pIter = GetQuestInfoList();
	while (pIter && pIter->GetItem()) {
		QuestInfo* pQuestInfo = pIter->GetItem();
		pIter = pIter->GetNext();

		if (apQuest == pQuestInfo->pQuest && (apQuest || !pQuestInfo->pRemovedQuest))
			return GetInfoByIndex(pQuestInfo, auiIndex);
	}
	return nullptr;
#else
	return ThisCall<TESTopicInfo*>(0x593810, this, apQuest, auiIndex);
#endif
}

// GAME - 0x619F20
TESTopicInfo* TESTopic::GetInfoByIndex(const QuestInfo* apQuestInfo, uint32_t auiIndex) {
#ifdef GAME
	return CdeclCall<TESTopicInfo*>(0x619F20, apQuestInfo, auiIndex);
#else
	if (!apQuestInfo)
		return nullptr;

    if (auiIndex >= apQuestInfo->GetTopicInfos()->GetSize())
		return nullptr;

	return apQuestInfo->GetTopicInfos()->GetAt(auiIndex);
#endif
}

// GAME - 0x619820
// GECK - 0x596790
bool TESTopic::InsertInfo(TESQuest* apQuest, TESTopicInfo* apTopicInfo, FormID auiPreviousInfoID) {
#ifdef GAME
	return ThisCall<bool>(0x619820, this, apQuest, apTopicInfo, auiPreviousInfoID);
#else
	return ThisCall<bool>(0x596790, this, apQuest, apTopicInfo, auiPreviousInfoID);
#endif
}

// GAME - 0x619F70
// GECK - 0x590EA0
TopicInfoArray* TESTopic::GetInfoArray(const TESQuest* apQuest) const {
#ifdef GAME
	return ThisCall<TopicInfoArray*>(0x619F70, this, apQuest);
#else
	return ThisCall<TopicInfoArray*>(0x590EA0, this, apQuest);
#endif
}

// GAME - 0x619D00
// GECK - 0x593710
TESQuest* TESTopic::GetOwnerQuest(const TESTopicInfo* apTopicInfo) const {
#ifdef GAME
	return ThisCall<TESQuest*>(0x619D00, this, apTopicInfo);
#else
	return ThisCall<TESQuest*>(0x593710, this, apTopicInfo);
#endif
}

// GAME - 0x619BC0
// GECK - 0x590E40
bool TESTopic::HasQuest(const TESQuest* apQuest, bool abRequireInfos) const {
#ifdef GAME
	return ThisCall<bool>(0x619BC0, this, apQuest, abRequireInfos);
#else
	return ThisCall<bool>(0x590E40, this, apQuest, abRequireInfos);
#endif
}

// GAME - 0x6195D0
// GECK - 0x596690
QuestInfo* TESTopic::InsertQuest(TESQuest* apQuest, bool abResort) {
#ifdef GAME
	return ThisCall<QuestInfo*>(0x6195D0, this, apQuest, abResort);
#else
	return ThisCall<QuestInfo*>(0x596690, this, apQuest, abResort);
#endif
}

// GAME - 0x61A310
// GECK - 0x5938A0
TESTopic* TESTopic::GetOwnerTopic(const TESTopicInfo* apTopicInfo) {
#ifdef GAME
	return CdeclCall<TESTopic*>(0x61A310, apTopicInfo);
#else
	return CdeclCall<TESTopic*>(0x5938A0, apTopicInfo);
#endif
}

// GAME - 0x61A2D0
// GECK - 0x590A50
TESTopic* TESTopic::GetTopic(DIALOGUE_TYPE aeType, int32_t aiIndex) {
#ifdef GAME
    return CdeclCall<TESTopic*>(0x61A2D0, aeType, aiIndex);
#else
    return CdeclCall<TESTopic*>(0x590A50, aeType, aiIndex);
#endif
}

#ifdef GAME
// GAME - 0x619A90
void TESTopic::ClearSaidOnceInfosForQuest(TESQuest* apQuest) {
	ThisCall(0x619A90, this, apQuest);
}

// GAME - 0x619B60
void TESTopic::ClearAllSaidOnceInfosForQuest(TESQuest* apQuest) {
	CdeclCall(0x619B60, apQuest);
}

// GAME - 0x61B320
DialogueItem* TESTopic::CreateDialogueItem(TESObjectREFR* apSpeaker, TESObjectREFR* apTarget, TESTopic* apPreviousTopic, BSSimpleList<DialogueItem*>* apConversationList, bool abRunImmediate) {
	return ThisCall<DialogueItem*>(0x61B320, this, apSpeaker, apTarget, apPreviousTopic, apConversationList, abRunImmediate);
}

// GAME - 0x61A720
TESTopicInfo* TESTopic::GetMatchingInfo(TESObjectREFR* apSpeaker, TESObjectREFR* apTarget) const {
	return ThisCall<TESTopicInfo*>(0x61A720, this, apSpeaker, apTarget);
}

// GAME - 0x61A760
TESTopicInfo* TESTopic::GetMatchingInfo(bool& abDispositionFailure, TESObjectREFR* apSpeaker, TESObjectREFR* apTarget) const {
	return ThisCall<TESTopicInfo*>(0x61A760, this, &abDispositionFailure, apSpeaker, apTarget);
}

// GAME - 0x61A790
TESTopicInfo* TESTopic::GetMatchingInfo(bool& abDispositionFailure, TESObjectREFR* apSpeaker, TESObjectREFR* apTarget, bool abIsConversation, TESTopic* apPreviousTopic, BSSimpleList<DialogueItem*>* apConversationList) const {
	return ThisCall<TESTopicInfo*>(0x61A790, this, &abDispositionFailure, apSpeaker, apTarget, abIsConversation, apPreviousTopic, apConversationList);
}

// GAME - 0x61A7D0
TESTopicInfo* TESTopic::GetMatchingInfo(const TESTopic* apTopic, bool& abDispositionFailure, TESObjectREFR* apSpeaker, TESObjectREFR* apTarget, bool abIsConversation, TESTopic* apPreviousTopic, BSSimpleList<DialogueItem*>* apConversationList) {
	return CdeclCall<TESTopicInfo*>(0x61A790, apTopic, &abDispositionFailure, apSpeaker, apTarget, abIsConversation, apPreviousTopic, apConversationList);
}

// GAME - 0x61AF30
TESTopicInfo* TESTopic::GetMatchingFollowUpInfo(TESTopicInfo* apTopicInfo, bool& abDispositionFailure, TESObjectREFR* apSpeaker, TESObjectREFR* apTarget, bool abIsConversation, BSSimpleList<DialogueItem*>* apConversationList) {
	return CdeclCall<TESTopicInfo*>(0x61AF30, apTopicInfo, &abDispositionFailure, apSpeaker, apTarget, abIsConversation, apConversationList);
}
#endif

// GAME - 0x61BC10
// GECK - 0x5945E0
void TopicInfoArray::InsertTopicInfoAt(uint32_t auiIndex, TESTopicInfo* apTopicInfo) {
#ifdef GAME
	ThisCall(0x61BC10, this, auiIndex, apTopicInfo);
#else
	ThisCall(0x5945E0, this, auiIndex, apTopicInfo);
#endif
}

// GAME - 0x717E50
const TopicInfoArray* QuestInfo::GetTopicInfos() const {
	return &kTopicInfos;
}

// GAME - 0x717E50
TopicInfoArray* QuestInfo::GetTopicInfos() {
	return &kTopicInfos;
}