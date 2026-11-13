#pragma once

#include "Bethesda/BSExtraData.hpp"
#include "Bethesda/BSSimpleList.hpp"

class TESQuest;
class TESForm;
class TESActorBase;

class DialogExtraQuestFilter : public BSExtraData {
public:
	BSSimpleList<TESQuest*>			kQuests;
	TESForm*						dword14;
	uint32_t						dword18;
	BSSimpleList<TESActorBase*>		kList1C;

	BSEXTRA_TYPE(DialogExtraQuestFilter);
};

ASSERT_SIZE(DialogExtraQuestFilter, 0x24);