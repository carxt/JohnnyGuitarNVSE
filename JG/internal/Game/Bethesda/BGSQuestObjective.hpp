#pragma once

#include "BSStringT.hpp"
#include "BSSimpleList.hpp"

class TESObjectREFR;
class TESQuestTarget;
class TESQuest;

class BGSQuestObjective {
public:
	BGSQuestObjective();
	virtual ~BGSQuestObjective();

	struct _State {
		enum State : uint32_t {
			DORMANT				= 0,
			DISPLAYED			= 1,
			COMPLETED			= 2,
			COMPLETED_DISPLAYED = 3,
		};
	};
	using State = _State::State;

	uint32_t						uiIndex;
	BSString						strDisplayText;
	TESQuest*						pOwnerQuest;
	BSSimpleList<TESQuestTarget*>	kTargets;
	bool							bInitialized;
	State							eState;

	bool GetCompleted() const;
	bool GetDisplayed() const;

	uint32_t GetIndex() const;

	const char* GetDisplayText() const;
	void SetDisplayText(const char* apText);

	uint32_t GetDisplayTextLength() const;

	TESQuest* GetOwner() const;
	void SetOwner(TESQuest* apOwner);

	const BSSimpleList<TESQuestTarget*>* GetTargetList() const;
	BSSimpleList<TESQuestTarget*>* GetTargetList();

	State GetState() const;
	void SetState(State aeState);
	void SetStateSimple(State aeState);

	bool CheckState(State aeState) const;

	void UpdateCurrentTargetList(BSSimpleList<TESQuestTarget*>* apListToFill);
};

ASSERT_SIZE(BGSQuestObjective, 0x24);