#pragma once

#include "BaseFormComponent.hpp"
#include "BSSimpleList.hpp"

class TESFaction;

struct GroupReaction {
	enum {
		NEUTRAL = 0,
		ENEMY,
		ALLY,
		FRIEND
	};

	TESFaction* pFaction;
	int32_t		iModifier;
	uint32_t	uiReaction;
};

class TESReactionForm : public BaseFormComponent {
public:
	TESReactionForm();
	~TESReactionForm();

	BSSimpleList<GroupReaction*> kReactions;
	uint8_t						 ucGroupFormType;
};

ASSERT_SIZE(TESReactionForm, 0x10);