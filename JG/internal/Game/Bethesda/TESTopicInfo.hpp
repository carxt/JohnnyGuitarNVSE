#pragma once

#include "Gamebryo/NiTArray.hpp"
#include "TESCondition.hpp"
#include "TESForm.hpp"
#include "TESResponse.hpp"
#include "TESConversationData.hpp"

class TESTopic;
class TESQuest;
class TESActorBase;
class BGSPerk;
class ActorValueInfo;
class Script;

class TESTopicInfo : public TESForm {
public:
	TESTopicInfo();
	~TESTopicInfo();

	struct _SpeechChallengeType {
		enum Type : uint32_t {
			NONE		= 0,
			VERY_EASY	= 1,
			EASY		= 2,
			AVERAGE		= 3,
			HARD		= 4,
			VERY_HARD	= 5,
			COUNT,
		};
	};
	using SpeechChallengeLevel = _SpeechChallengeType::Type;

	struct _IntelligenceCheckType {
		enum Type : uint32_t {
			NONE		= 0,
			DUMMY		= 1,
			EITHER		= 2,
			NON_DUMMY	= 3,
			COUNT
		};
	};
	using IntelligenceCheckType = _IntelligenceCheckType::Type;

	struct ALIGN2 _TopicInfoFlags {
		enum Flags1 {
			GOODBYE					= 1u << 0,
			RANDOM					= 1u << 1,
			SAY_ONCE				= 1u << 2,
			RUN_IMMEDIATELY			= 1u << 3,
			INFO_REFUSAL			= 1u << 4,
			RANDOM_END				= 1u << 5,
			RUN_FOR_RUMORS			= 1u << 6,
			SPEECH_CHALLENGE		= 1u << 7,
		};

		enum Flags2 {
			SAY_ONCE_A_DAY			= 1u << 0,
			ALWAYS_DARKEN			= 1u << 1,


			LOW_INTELLIGENCE		= 1u << 4,
			HIGH_INTELLIGENCE		= 1u << 5,
		};

		bool bGoodbye				: 1;
		bool bRandom				: 1;
		bool bSayOnce				: 1;
		bool bRunImmediately		: 1;
		bool bInfoRefusal			: 1;
		bool bRandomEnd				: 1;
		bool bRunForRumors			: 1;
		bool bSpeechChallenge		: 1;

		bool bSayOnceADay			: 1;
		bool bAlwaysDarken			: 1;
		bool 						: 1;
		bool 						: 1;
		bool bDummyOnly				: 1;
		bool bNonDummyOnly			: 1;
	};
	using TopicInfoFlags1 = _TopicInfoFlags::Flags1;
	using TopicInfoFlags2 = _TopicInfoFlags::Flags2;

	struct Data {
		uint8_t		eType;
		uint8_t		eNextSpeaker;
		union {
			struct {
				Bitfield8		ucFlags1;
				Bitfield8		ucFlags2;
			};
			Bitfield<_TopicInfoFlags> usFlags;
		};
	};

	TESCondition			kConditions;
	uint16_t				usInfoIndex;
	bool					bSaidOnce;	
	Data 					kData;
	BSString				strPrompt;			
	BSSimpleList<TESTopic*>	kAddTopics;		
	TESConversationData*	pConversationData;
	TESActorBase*			pSpeaker;
	union {
		BGSPerk*		__restrict pPerk;
		ActorValueInfo* __restrict pActorValue;
	};
	SpeechChallengeLevel	eSpeechDifficulty;
	TESQuest*				pOwnerQuest;
	uint32_t				uiFileOffset;
#if USE_MODDED_CHANGES
	TESTopic*				pParentTopic;
#endif

	TESFORM_TYPE(TESTopicInfo);

	const TESCondition* GetInfoConditions() const;
	TESCondition* GetInfoConditions();
	void SetInfoConditions(TESCondition* apConditions);

	uint16_t GetInfoIndex() const;
	void SetInfoIndex(uint16_t ausIndex);

	bool GetSaidOnce() const;
	void SetSaidOnce();
	void ResetSaidOnceFlags();

	DIALOGUE_TYPE GetDialogueType() const;
	void SetDialogueType(DIALOGUE_TYPE aeType);

	DIALOGUE_SPEAKER GetNextSpeaker() const;
	void SetNextSpeaker(DIALOGUE_SPEAKER aeSpeaker);

	bool IsGoodbye() const;
	bool IsRandom() const;
	bool IsSayOnce() const;
	bool IsRunImmediately() const;
	bool IsInfoRefusal() const;
	bool IsRandomEnd() const;
	bool IsRunForRumors() const;
	bool IsSpeechChallenge() const;

	bool IsSayOnceADay() const;
	bool IsAlwaysDarkened() const;

	IntelligenceCheckType GetIntelligenceCheckType() const;

	const BSString& GetPrompt() const;
	bool HasPrompt() const;
	void SetPrompt(const char* apText);

	const BSSimpleList<TESTopic*>* GetAddTopicList() const;
	BSSimpleList<TESTopic*>* GetAddTopicList();
	void AddTopicList() const;
	 
	TESConversationData* GetConversationData() const;
	void SetConversationData(TESConversationData* apData);

	TESActorBase* GetSpeaker() const;
	void SetSpeaker(TESActorBase* apSpeaker);

	ActorValueInfo* GetActorValue() const;
	void SetActorValue(ActorValueInfo* apActorValue);

	BGSPerk* GetPerk() const;
	void SetPerk(BGSPerk* apPerk);

	SpeechChallengeLevel GetDifficultyLevel() const;
	void SetDifficultyLevel(SpeechChallengeLevel aeLevel);

	int32_t GetDifficulty() const;

	TESQuest* GetOwnerQuest() const;
	void SetOwnerQuest(TESQuest* apQuest);

#if USE_MODDED_CHANGES
	TESTopic* GetParentTopic();
#endif

	Script* GetResultScript(DIALOGUE_SCRIPT_TYPE aeType);

	bool CheckCondition(bool& abDispositionFailure, TESQuest* apQuest, TESObjectREFR* apActionRef, TESObjectREFR* apTargetRef) const;

	void GetInfoDisplayText(BSString& arString, bool abFirstOnly) const;
};

#if USE_MODDED_CHANGES
ASSERT_SIZE(TESTopicInfo, 0x54);
#else
ASSERT_SIZE(TESTopicInfo, 0x50);
#endif