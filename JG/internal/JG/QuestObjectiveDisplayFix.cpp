#include "QuestObjectiveDisplayFix.hpp"
#include <GameObjects.h>

namespace QuestObjectiveDisplayFix {

	HookUtils::JumpDetour kDetour;

	static uint32_t __fastcall QuestObjectiveDisplayHook(const BGSQuestObjective* pObjective) {
		uint32_t uiResult = 1;
		if (kDetour)
			uiResult = ThisCall<uint32_t>(kDetour, pObjective);

		if (uiResult) {
			uiResult = pObjective->status & BGSQuestObjective::eQObjStatus_displayed;
			if (!(pObjective->displayText.GetLength() || pObjective->quest->GetFullNameLength()))
				uiResult = 0;
		}

		return uiResult;
	}

	void Install() {
		kDetour.WriteRelJump(0x5A5E70, QuestObjectiveDisplayHook, true);
	}

}