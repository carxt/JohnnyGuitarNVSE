#include "RSMBarberHook.hpp"
#include "GameForms.h"
namespace RSMBarberHook {
	JGSetList<DWORD> haircutSetList;
	JGSetList<DWORD> beardSetList;
	uintptr_t RSMDestructorOriginal = (uintptr_t)0x07AC530;

	bool __fastcall hk_TESHair_IsPlayable(TESHair* ptr_hair) {
		return (ptr_hair->IsPlayable()) && (haircutSetList.Allow(ptr_hair->GetFormID()));

	}

	bool __fastcall hk_BGSHeadPart_IsPlayable(BGSHeadPart* ptr_hdpt) {
		return (ptr_hdpt->headFlags & 0x1) && (beardSetList.Allow(ptr_hdpt->GetFormID()));
	}
	DWORD __fastcall hk_RSMDestroy(void* thisObj, void* EDX, BOOL heapFree) {
		auto ret = ThisCall<DWORD>(RSMDestructorOriginal, thisObj, heapFree);
		haircutSetList.dFlush();
		beardSetList.dFlush();
		return ret;
	}
	void Install() {
		RSMDestructorOriginal = *((uintptr_t*)0x1075974);
		SafeWrite32(0x1075974, (uintptr_t)hk_RSMDestroy);
		WriteRelCall(0x07AD35C, (uintptr_t)hk_BGSHeadPart_IsPlayable);
		WriteRelCall(0x07AF35B, (uintptr_t)hk_TESHair_IsPlayable);
		WriteRelCall(0x07B1D4A, (uintptr_t)hk_TESHair_IsPlayable);

	}
	void Reset()
	{
		haircutSetList.dFlush();
		beardSetList.dFlush();
	}
}