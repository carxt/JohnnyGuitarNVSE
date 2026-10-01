#pragma once

#include "Gamebryo/NiTLargePrimitiveArray.hpp"
#include "BSSimpleArray.hpp"
#include "TESForm.hpp"
#include "TESFullName.hpp"
#include "TESTopicInfo.hpp"

class TESQuest;
class DialogueItem;
class TESObjectREFR;
class TopicInfoArray;
struct QuestInfo;

class TESTopic : public TESForm, public TESFullName {
public:
	TESTopic();
	~TESTopic();

	struct ALIGN1 _TopicFlags {
		enum Flags : uint8_t {
			RUMORS			= 1u << 0,
			TOP_LEVEL		= 1u << 1,

			DUMMY_ONLY		= 1u << 4,
			NON_DUMMY_ONLY	= 1u << 5,
		};

		bool bRumors		: 1;
		bool bTopLevel		: 1;
		bool				: 2;
		bool bDummyOnly		: 1;
		bool bNonDummyOnly	: 1;
	};
	using TopicFlags = _TopicFlags::Flags;

	struct Data {
		int8_t					cType;
		Bitfield<_TopicFlags>	ucFlags;
	};

	Data						kData;
	float						fPriority;
	BSSimpleList<QuestInfo*>	kQuestInfos;
	BSString					strDummyPrompt;
#ifdef GAME
	uint32_t					uiJournalIndex;
	BSString					strEditorID;
#endif

	TESFORM_TYPE(TESTopic);

	DIALOGUE_TYPE GetDialogueType() const;

	bool IsRumors() const;

	bool IsTopLevel() const;

	DIALOGUE_DUMMY_STATE GetDummyNodeState() const;
	void SetDummyNodeState(DIALOGUE_DUMMY_STATE aeState);
	
	float GetPriority() const;
	void SetPriority(float afVal);

	const BSSimpleList<QuestInfo*>* GetQuestInfoList() const;
	BSSimpleList<QuestInfo*>* GetQuestInfoList();

	QuestInfo* GetQuestInfoElement(const TESTopicInfo* apTopicInfo) const;

	const BSString& GetDummyPrompt() const;
	bool HasDummyPrompt() const;
	void SetDummyPrompt(const char* apText);

	bool IsPersuasion() const;


	TESTopicInfo* GetInfoByID(FormID auiFormID, bool abReverse);

	TESTopicInfo* GetInfoByIndex(const TESQuest* apQuest, uint32_t auiIndex) const;
	static TESTopicInfo* GetInfoByIndex(const QuestInfo* apQuestInfo, uint32_t auiIndex);

	bool InsertInfo(TESQuest* apQuest, TESTopicInfo* apTopicInfo, FormID auiPreviousInfoID);

	TopicInfoArray* GetInfoArray(const TESQuest* apQuest) const;


	TESQuest* GetOwnerQuest(const TESTopicInfo* apTopicInfo) const;

	bool HasQuest(const TESQuest* apQuest, bool abRequireInfos) const;

	QuestInfo* InsertQuest(TESQuest* apQuest, bool abResort);


	static TESTopic* GetOwnerTopic(const TESTopicInfo* apTopicInfo);

	static TESTopic* GetTopic(DIALOGUE_TYPE aeType, int32_t aiIndex);

#ifdef GAME
	void ClearSaidOnceInfosForQuest(TESQuest* apQuest);
	static void ClearAllSaidOnceInfosForQuest(TESQuest* apQuest);

	DialogueItem* CreateDialogueItem(TESObjectREFR* apSpeaker, TESObjectREFR* apTarget, TESTopic* apPreviousTopic, BSSimpleList<DialogueItem*>* apConversationList, bool abRunImmediate);
	
	TESTopicInfo* GetMatchingInfo(TESObjectREFR* apSpeaker, TESObjectREFR* apTarget) const;
	TESTopicInfo* GetMatchingInfo(bool& abDispositionFailure, TESObjectREFR* apSpeaker, TESObjectREFR* apTarget) const;
	TESTopicInfo* GetMatchingInfo(bool& abDispositionFailure, TESObjectREFR* apSpeaker, TESObjectREFR* apTarget, bool abIsConversation, TESTopic* apPreviousTopic, BSSimpleList<DialogueItem*>* apConversationList) const;
	static TESTopicInfo* GetMatchingInfo(const TESTopic* apTopic, bool& abDispositionFailure, TESObjectREFR* apSpeaker, TESObjectREFR* apTarget, bool abIsConversation, TESTopic* apPreviousTopic, BSSimpleList<DialogueItem*>* apConversationList);
	
	static TESTopicInfo* GetMatchingFollowUpInfo(TESTopicInfo* apTopicInfo, bool& abDispositionFailure, TESObjectREFR* apSpeaker, TESObjectREFR* apTarget, bool abIsConversation, BSSimpleList<DialogueItem*>* apConversationList);
#endif
};

#ifdef GAME
ASSERT_SIZE(TESTopic, 0x48);
#else
ASSERT_SIZE(TESTopic, 0x50);
#endif

class TopicInfoArray : public NiTLargePrimitiveArray<TESTopicInfo*> {
public:
	void InsertTopicInfoAt(uint32_t auiIndex, TESTopicInfo* apTopicInfo);
};

struct INFO_LINK_ELEMENT {
	uint32_t		uiIndex;
	TESTopicInfo*	pInfo;
	int32_t			iDesiredIndex;
};

struct QuestInfo {
	TESQuest*							pQuest;
	TopicInfoArray						kTopicInfos;
	BSSimpleArray<INFO_LINK_ELEMENT>	kInfoLinks;
	TESQuest*							pRemovedQuest;
#ifdef GAME
	bool								bInitialized;
#endif

	const TopicInfoArray* GetTopicInfos() const;
	TopicInfoArray* GetTopicInfos();
};

#ifdef GAME
ASSERT_SIZE(QuestInfo, 0x34);
#else
ASSERT_SIZE(QuestInfo, 0x30);
#endif