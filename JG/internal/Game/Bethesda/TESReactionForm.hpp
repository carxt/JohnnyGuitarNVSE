#pragma once

#include "BaseFormComponent.hpp"
#include "BSSimpleList.hpp"

class TESFaction;

// IMPORTANT!
// "Reaction" is actually a disposition mod (In-GECK name)
// Don't confuse it with fight reaction (Obsidian did...)
// I'm not renaming it due game's own script commands using that name
// I feel like renaming it would lead to even more confusion...

struct GroupReaction {
	TESForm*		pForm;
	int32_t			iReaction;
	FIGHT_REACTION	eFightReaction;
};

class TESReactionForm : public BaseFormComponent {
public:
	TESReactionForm();
	~TESReactionForm();

	BSSimpleList<GroupReaction*> kReactions;
	uint8_t						 ucGroupFormType;

	BSSimpleList<GroupReaction*>* GetReactionList();
	const BSSimpleList<GroupReaction*>* GetReactionList() const;

	int32_t GetReaction(const TESForm* apForm) const;
	void SetReaction(TESForm* apForm, int32_t aiReaction);
#ifdef GAME
	void ModReaction(TESForm* apForm, int32_t aiReaction);
#endif

	FIGHT_REACTION GetFactionCombatRelation(const TESForm* apForm) const;
#ifdef GAME
	void SetFightReaction(TESForm* apForm, FIGHT_REACTION aeFightReaction);
#endif
};

ASSERT_SIZE(TESReactionForm, 0x10);