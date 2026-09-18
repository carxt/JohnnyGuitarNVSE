#include "TESEffectShaderFixes.hpp"

namespace TESEffectShaderFixes {

	SPEC_NAKED void SkinChecks_Asm() {
		static constexpr uint32_t uiFailAddr	= 0x507C19;
		static constexpr uint32_t uiSuccessAddr	= 0x507C1D;
		static constexpr uint32_t uiReturnAddr	= 0x507BE8;
		__asm {
			mov		[ebp - 0x10], eax // Store material property

			// Fix 1: Beth did not update stuff from Oblivion
			// They use NiMaterialProperty names to check if something is a skin
			// FO3+ uses the FaceGen shader property flag for that, but this code doesn't...
			mov     ecx, [ebp - 0x8] // Get shader property
			bt		DWORD PTR [ecx + 0x20], 10 // Check FaceGen flag
			jb		SUCCESS

			// Fix 2: There's no NiMaterialProperty nullcheck lol
			mov		ecx, [ebp - 0x10] // Nullcheck material property
			test	ecx, ecx
			jz		FAIL

			jmp		uiReturnAddr
		
			FAIL:
			jmp		uiFailAddr

			SUCCESS:
			jmp		uiSuccessAddr
		}
	}

	void Install() {
		HookUtils::WriteRelJump(0x507BE2, SkinChecks_Asm);

		// Use NiFixedString comparison instead of strcmp
		HookUtils::PatchMemoryNop(0x507BF8, 5); // Remove "skin" str push
		// mov     ecx, dword ptr ds:[FixedStrings::pSkin] // pSkin is 0x11C6210
		// cmp     eax, [ecx] // eax is the NiMaterialProperty name ptr
		// jmp	   +1 // Skip nops
		HookUtils::SafeWriteBuf(0x507C0C, "\x8B\x0D\x10\x62\x1C\x01\x3B\x01\xEB\x01");
	}

}