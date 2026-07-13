#include "CustomCameraShake.hpp"
#include "GameObjects.h"
#include "GameProcess.h"

namespace CustomCameraShake {
	float mult = 0, duration = 0;
	bool __fastcall fn_camAltShakeHook(Actor* a_refr, void* edx, NiMatrix3* outMatrix) {
		NiMatrix3 shakeMatrix = {};
		Animation* anData = ThisCall<Animation*>(0x08B70D0, a_refr);
		if (!anData) return true;
		float timePassed = anData->flt0D0;
		auto originalShakeMult = *(float*)(0x11DFED4), originalShakeTime = *(float*)(0x11DFED8);
		*(float*)(0x11DFED4) = mult;
		*(float*)(0x11DFED8) = duration;
		float remainTime = CdeclCall<double>(0x8D1B30, timePassed, &shakeMatrix);
		mult = *(float*)(0x11DFED4);
		duration = *(float*)(0x11DFED8);
		*(float*)(0x11DFED4) = originalShakeMult;
		*(float*)(0x11DFED8) = originalShakeTime;
		if (remainTime > 0.0f) {
			float euX = 0, euY = 0, euZ = 0;
			ThisCall(0x0A592C0, &shakeMatrix, &euX, &euY, &euZ);
			euX *= remainTime;
			euY *= remainTime;
			euZ *= remainTime;
			ThisCall(0x0A59540, &shakeMatrix, euX, euY, euZ);
			ThisCall<void*>(0x43F8D0, outMatrix, outMatrix, &shakeMatrix);

		}
		return true;

	}
	__declspec(naked) void asm_CameraShakeHook() {
		__asm {
			fnstsw ax
			test ah, 0x41
			jz retAbort
			lea edx, dword ptr ss : [ebp - 0x34]
			push edx
			mov ecx, dword ptr ss : [ebp - 0x414]
			call fn_camAltShakeHook
			ALIGN 16
			test al, al
			jmp retEnd
			retAbort :
			fldz
				fst mult
				fstp duration
				retEnd :
			setnz al
				ret
		}
	}
	void Install() {
		HookUtils::WriteRelCall(0x94BCF6, (uintptr_t)asm_CameraShakeHook);
	}

}