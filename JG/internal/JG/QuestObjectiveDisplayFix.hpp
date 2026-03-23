#pragma once
#include <GameForms.h>
namespace QuestObjectiveDisplayFix {
	template <uintptr_t a_addr>
	class QuestObjectiveDisplayHook {
	private:
		static inline uintptr_t hPreviousAddressHook = 0;
	public:
		static  uintptr_t __fastcall Hook(BGSQuestObjective* pObjective) {
			DWORD result = 1;
			if (hPreviousAddressHook)
			{
				result = ThisCall<uintptr_t>(hPreviousAddressHook, pObjective);
			}
			if (result)
			{
				result = pObjective->status & BGSQuestObjective::eQObjStatus_displayed;
				auto questObjectiveDisplayStr = pObjective->displayText.c_str();
				auto questDisplayStr = TESFullName::GetFullName(pObjective->quest);
				if (!((questObjectiveDisplayStr && *questObjectiveDisplayStr) || (questDisplayStr && *questDisplayStr)))
				{
					result = 0;
				}
			}

			return result;
		}
		QuestObjectiveDisplayHook() {
			if (*(char*)a_addr == 0xE9) //there's a jump here, so detour it
			{
				hPreviousAddressHook = GetRelJumpAddr(a_addr);
			}
			WriteRelJump((a_addr), (uintptr_t)Hook);
		}

	};

	void Install();
}