#include "RefDestructorFix.hpp"
#include "shared/SafeWrite/SafeWrite.hpp"

namespace RefDestructorFix {

	// Skip detaching linked refs and activation parents/children if reference is not even initialized
	// Otherwise, you crash and waste few hours (ask me how I know it)
	// ExtraData corruption my ass
	// (Fixed in CE, naturally)

	SPEC_NAKED void FormInitCheck_Asm() {
		static constexpr uint32_t uiReturnAddr = 0x55A961;
		static constexpr uint32_t uiSkipAddr = 0x55AA5B;
		__asm {
			mov		[ebp - 0x10], eax
			mov     ecx, [ebp - 0x5C]
			bt		dword ptr [ecx + 8], 3
			jnb		SKIP

			cmp     dword ptr[ebp - 0x10], 0
			jmp		uiReturnAddr

			SKIP:
			jmp		uiSkipAddr
		}
	}

	void Install() {
		HookUtils::WriteRelJump(0x55A95A, FormInitCheck_Asm);
	}

}