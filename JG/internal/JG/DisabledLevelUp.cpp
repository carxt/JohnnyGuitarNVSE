#include "DisabledLevelUp.hpp"	

namespace DisabledLevelUp {

	bool bShowLevelUp = true;

	SPEC_NAKED void LevelUpHook() {
		static constexpr uint32_t uiNoShowLvlUpAddr	= 0x77D903;
		static constexpr uint32_t uiShowLvlUpAddr	= 0x77D618;
		_asm {
			jne		NO_LEVEL_UP

			mov		al, bShowLevelUp
			test	al, al
			je		NO_LEVEL_UP

			jmp		uiShowLvlUpAddr

			NO_LEVEL_UP:
			jmp		uiNoShowLvlUpAddr
		}
	}

	void Reset() {
		bShowLevelUp = true;
	}

	void Install() {
		HookUtils::WriteRelJump(0x77D612, LevelUpHook);
	}

	bool GetShowLevelUpMenu() {
		return bShowLevelUp;
	}

	void SetShowLevelUpMenu(bool abVal) {
		bShowLevelUp = abVal;
	}

}