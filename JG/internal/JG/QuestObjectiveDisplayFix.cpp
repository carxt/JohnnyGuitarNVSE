#include "QuestObjectiveDisplayFix.hpp"
#include <GameObjects.h>

namespace QuestObjectiveDisplayFix {

	HookUtils::JumpDetour kDetour;

	static bool __fastcall QuestObjectiveDisplayHook(const BGSQuestObjective* apObjective) {
		bool bResult;
		if (kDetour)
			bResult = ThisCall<bool>(kDetour, apObjective);
		else
			bResult = apObjective->GetDisplayed();

		if (bResult) {
			if (!(apObjective->GetDisplayTextLength() || apObjective->GetOwner()->GetFullNameLength()))
				bResult = false;
		}

		return bResult;
	}

	void Install() {
		kDetour.WriteRelJump(0x5A5E70, QuestObjectiveDisplayHook, true);
	}

}