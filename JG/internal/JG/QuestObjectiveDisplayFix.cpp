#include "QuestObjectiveDisplayFix.hpp"
#include <GameObjects.h>

namespace QuestObjectiveDisplayFix {

	HookUtils::JumpDetour kDetour;

	static uint32_t __fastcall QuestObjectiveDisplayHook(const BGSQuestObjective* apObjective) {
		uint32_t uiResult;
		if (kDetour)
			uiResult = ThisCall<uint32_t>(kDetour, apObjective);
		else
			uiResult = apObjective->status & BGSQuestObjective::eQObjStatus_displayed;

		if (uiResult) {
			if (!(apObjective->displayText.GetLength() || apObjective->quest->GetFullNameLength()))
				uiResult = 0;
		}

		return uiResult;
	}

	void Install() {
		kDetour.WriteRelJump(0x5A5E70, QuestObjectiveDisplayHook, true);
	}

}