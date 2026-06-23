#include "CloudUpdateFix.hpp"
#include "GameForms.h"
#include "GameAPI.h"

namespace CloudUpdateFix {
	DWORD completedFirstUpdate = 0;
	uintptr_t fn_Clouds_Update = 0;

	bool __fastcall SkipCloudCheck(TESWeather* a_wea) {
		if (completedFirstUpdate < 2 || !a_wea) {
			completedFirstUpdate = 1;
			return false;
		}
		return true;

	}
	
	DWORD __fastcall HookCloudUpdate(void* a_cloud, void* edx, void* Sky, float timePassed) {
		auto ret = ThisCall<DWORD>(fn_Clouds_Update, a_cloud, Sky, timePassed);
		if (completedFirstUpdate == 1) {
			completedFirstUpdate = 2;
		}
		return ret;
	}
	__declspec(naked) void HookCloudCheck() {
		static uintptr_t jmpRet = 0x06346F9;
		static uintptr_t jneRet = 0x0634740;
		__asm {
			mov ecx, dword ptr[ebp - 0x14]
			call SkipCloudCheck
			test al, al
			jne skip
			jmp jmpRet
			ALIGN 16
			skip:
			jmp jneRet
		}
	}
	DWORD __fastcall HookNewGameCloudUpdate(BGSSaveLoadGame* a_obj) {
		return ThisCall<bool>(0x42CE10, a_obj) || (*(bool*)0x11D8907);

	}
	void Install() {
		HookUtils::SafeWrite8(0x06346F3, 0x90);
		HookUtils::WriteRelJump(0x06346F4, (uintptr_t)HookCloudCheck);
		fn_Clouds_Update = *(uintptr_t*)0x104EC14;
		HookUtils::SafeWrite32(0x104EC14, (uintptr_t)HookCloudUpdate);

		//Cloud int update
		HookUtils::SafeWrite8(0x63AD66, 0xEB);
		HookUtils::WriteRelCall(0x063ADAB, (uintptr_t)HookNewGameCloudUpdate);
	}


}