#pragma once

#include "TESForm.hpp"
#include "TESScriptableForm.hpp"
#include "TESIcon.hpp"
#include "TESCondition.hpp"
#include "TESQuestStage.hpp"
#include "TESFullName.hpp"

class BGSQuestObjective;
class ScriptLocals;

class TESQuest : public TESForm, public TESScriptableForm, public TESIcon, public TESFullName {
public:
	TESQuest();
	~TESQuest();

	virtual const char* GetEditorName() const; // GetFormEditorID duplicate, works in vanilla

	struct ALIGN1 _QuestFlags {
		enum Flags : uint8_t {
			ENABLED					= 1u << 0,
			COMPLETED				= 1u << 1,
			ALLOW_REPEATED_TOPICS	= 1u << 2,
			ALLOW_REPEATED_STAGES	= 1u << 3,
			STARTS_ENABLED			= 1u << 4,
			DISPLAYED_IN_HUD		= 1u << 5,
			FAILED					= 1u << 6,
		};

		bool bEnabled				: 1;
		bool bCompleted				: 1;
		bool bAllowRepeatedTopics	: 1;
		bool bAllowRepeatedStages	: 1;
		bool bStartsEnabled			: 1;
		bool bDisplayedInHUD		: 1;
		bool bFailed				: 1;
	};
	using QuestFlags = _QuestFlags::Flags;

	struct Data {
		Bitfield<_QuestFlags>	ucFlags;
		uint8_t					ucPriority;
		float					fQuestDelayTime;
	};

	Data								kData;
	BSSimpleList<TESQuestStage*>		kStages;
	BSSimpleList<BGSQuestObjective*>	kObjectives;
	TESCondition						kConditions;
	ScriptLocals*						pScriptLocals;
	uint8_t								ucCurrentStage;
	BSString							strEditorID;

	TESFORM_TYPE(TESQuest);

	const Data& GetData() const;
	Data& GetData();

	uint32_t GetPriority() const;

	float GetScriptProcessingDelay() const;
	void SetScriptProcessingDelay(float afVal);

	const BSSimpleList<TESQuestStage*>* GetStageList() const;
	BSSimpleList<TESQuestStage*>* GetStageList();

	TESQuestStage* GetStage(uint8_t aucIndex) const;
	bool IsStageDone(uint8_t aucIndex) const;
	uint8_t GetStageIndexForStageItem(TESQuestStageItem* apItem) const;

	const BSSimpleList<BGSQuestObjective*>* GetObjectiveList() const;
	BSSimpleList<BGSQuestObjective*>* GetObjectiveList();

	BGSQuestObjective* GetObjective(uint32_t auiIndex) const;

	bool GetEnabled() const;
	void SetEnabled(bool abVal);

	bool GetCompleted() const;
	void SetCompleted(bool abVal);

	bool GetAllowRepeats() const;
	void SetAllowRepeats(bool abVal);

	bool GetAllowRepeatStages() const;
	void SetAllowRepeatStages(bool abVal);

	bool GetStartsEnabled() const;
	void SetStartsEnabled(bool abVal);

	bool GetDisplayedInHUD() const;
	void SetDisplayedInHUD(bool abVal);

	bool GetFailed() const;
	void SetFailed(bool abVal);

	const TESCondition* GetConditions() const;
	TESCondition* GetConditions();

	ScriptLocals* GetScriptLocals() const;

	uint32_t GetCurrentStage() const;

	void SetAllObjectivesComplete(bool abVal);

	void ResetQuest();

	void RunScript();

	static void GetQuestLog(BSSimpleList<TESQuestStageItem*>* apListToFill, TESQuest* apQuest, bool abShowCompleted, bool abNewestFirst, bool abShowAll);
};

ASSERT_SIZE(TESQuest, 0x6C);