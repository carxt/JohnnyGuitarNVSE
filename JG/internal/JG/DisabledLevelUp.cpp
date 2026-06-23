#include "DisabledLevelUp.hpp"	

namespace DisabledLevelUp {

	bool isShowLevelUp = true;

	_declspec(naked) void LevelUpHook() {
		static const uint32_t noShowAddr = 0x77D903;
		static const uint32_t showAddr = 0x77D618;
		_asm {
			jne noLevelUp
			mov al, isShowLevelUp
			test al, al
			je noLevelUp
			jmp showAddr
			noLevelUp :
			jmp noShowAddr
		}
	}

	void Install() {
		HookUtils::WriteRelJump(0x77D612, uint32_t(LevelUpHook));
	}
	void Reset()
	{
		isShowLevelUp = true;
	}
}