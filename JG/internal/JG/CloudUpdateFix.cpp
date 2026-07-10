#include "CloudUpdateFix.hpp"
#include "GameForms.h"
#include "GameAPI.h"

namespace CloudUpdateFix {
	uint8_t ucCompletedFirstUpdate = 0;

	bool __fastcall SkipCloudCheck(const TESWeather* apWeather) {
		if (ucCompletedFirstUpdate < 2 || !apWeather) {
			ucCompletedFirstUpdate = 1;
			return false;
		}
		return true;

	}
	
	HookUtils::VirtFuncDetour kCloudUpdateDetour;
	void __fastcall HookCloudUpdate(void* apClouds, void*, void* apSky, float afDelta) {
		ThisCall(kCloudUpdateDetour, apClouds, apSky, afDelta);
		if (ucCompletedFirstUpdate == 1)
			ucCompletedFirstUpdate = 2;
	}

	SPEC_NAKED void HookCloudCheck() {
		static constexpr uint32_t uiContAddr = 0x6346F9;
		static constexpr uint32_t uiSkipAddr = 0x634740;
		__asm {
			mov		ecx, dword ptr[ebp - 0x14]
			call	SkipCloudCheck
			test	al, al
			jne		SKIP
			jmp		uiContAddr
			ALIGN	16
			SKIP:
			jmp		uiSkipAddr
		}
	}

	bool __fastcall HookNewGameCloudUpdate(BGSSaveLoadGame* apThis) {
		return ThisCall<bool>(0x42CE10, apThis) || (*(bool*)0x11D8907);
	}

	void Install() {
		HookUtils::SafeWrite8(0x6346F3, 0x90);
		HookUtils::WriteRelJump(0x6346F4, HookCloudCheck);
		kCloudUpdateDetour.ReplaceVirtualFunc(0x104EC14, HookCloudUpdate);

		// Cloud int update
		HookUtils::SafeWrite8(0x63AD66, 0xEB);
		HookUtils::WriteRelCall(0x063ADAB, HookNewGameCloudUpdate);
	}


}