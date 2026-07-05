#include "DisabledArrowKeys.hpp"

namespace DisabledArrowKeys {
	bool bArrowKeysDisabled = false;

	__declspec(naked) void DisableArrowKeysHook() {
		static const uint32_t retnAddr = 0x70F711;
		__asm {
			cmp byte ptr[bArrowKeysDisabled], 1
			jnz DONE
			cmp dword ptr[ebp + 8], 4
			jnz MATCHED
			cmp dword ptr[ebp + 8], 3
			jnz MATCHED
			cmp dword ptr[ebp + 8], 1
			jnz MATCHED
			cmp dword ptr[ebp + 8], 2
			jnz MATCHED
			jmp DONE
			MATCHED :
			mov dword ptr[ebp + 8], 0
				DONE :
				mov byte ptr[ebp - 0xD], 0
				mov eax, 1
				jmp retnAddr
		}
	}

	void Install()
	{
		// DisableMenuArrowKeys
		HookUtils::WriteRelJump(0x70F708, (uint32_t)DisableArrowKeysHook);
	}
	void Reset()
	{
		bArrowKeysDisabled = false;
	}

	void Toggle(bool toggle)
	{
		bArrowKeysDisabled = toggle;
	}
}