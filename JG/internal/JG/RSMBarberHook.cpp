#include "RSMBarberHook.hpp"
#include "GameForms.h"
#include <GameObjects.h>
namespace RSMBarberHook {
	JGSetList<DWORD> haircutSetList;
	JGSetList<DWORD> beardSetList;
	uintptr_t RSMDestructorOriginal = (uintptr_t)0x07AC530;

	bool __fastcall hk_TESHair_IsPlayable(TESHair* ptr_hair) {
		return (ptr_hair->IsPlayable()) && (haircutSetList.Find(ptr_hair->GetFormID()));

	}

	bool __fastcall hk_BGSHeadPart_IsPlayable(BGSHeadPart* ptr_hdpt) {
		return (ptr_hdpt->headFlags & 0x1) && (beardSetList.Find(ptr_hdpt->GetFormID()));
	}
	DWORD __fastcall hk_RSMDestroy(void* thisObj, void* EDX, BOOL heapFree) {
		auto ret = ThisCall<DWORD>(RSMDestructorOriginal, thisObj, heapFree);
		haircutSetList.Flush();
		beardSetList.Flush();
		return ret;
	}
	void Install() {
		RSMDestructorOriginal = *((uintptr_t*)0x1075974);
		HookUtils::SafeWrite32(0x1075974, (uintptr_t)hk_RSMDestroy);
		HookUtils::WriteRelCall(0x07AD35C, (uintptr_t)hk_BGSHeadPart_IsPlayable);
		HookUtils::WriteRelCall(0x07AF35B, (uintptr_t)hk_TESHair_IsPlayable);
		HookUtils::WriteRelCall(0x07B1D4A, (uintptr_t)hk_TESHair_IsPlayable);

	}
	void Reset()
	{
		haircutSetList.Flush();
		beardSetList.Flush();
	}

	enum {
		kFlag_WhiteListHair = 1 << 0,
		kFlag_WhiteListBeard,
	};

	void Load(BGSListForm* pList) {
		BSSimpleList<TESForm*>* pIter = pList->GetFormList();

		while (pIter && !pIter->IsEmpty()) {
			TESForm* currData = pIter->GetItem();
			pIter = pIter->GetNext();

			if (!currData) continue;
			if (IS_TYPE(currData, TESHair)) {
				haircutSetList.Add(currData->GetFormID());
				continue;
			}
			if (IS_TYPE(currData, BGSHeadPart)) {
				beardSetList.Add(currData->GetFormID());
			}
		};
	}

	void ShowMenu(uint32_t flags) {
		auto playerBase = reinterpret_cast<TESNPC*>(PlayerCharacter::GetSingleton()->GetActorBase());
		haircutSetList.bIsWhiteList = bool(flags & kFlag_WhiteListHair);
		if (haircutSetList.bIsWhiteList) {
			haircutSetList.Add(playerBase->hair->GetFormID());
		}
		else {
			haircutSetList.Remove(playerBase->hair->GetFormID());

		}
		beardSetList.bIsWhiteList = bool(flags & kFlag_WhiteListBeard);
		if (beardSetList.bIsWhiteList) {
			for (auto iter = playerBase->headPart.Begin(); !iter.End(); iter.Next()) {
				if (*iter) { beardSetList.Add((*iter)->GetFormID()); };
			}
		}
		else {
			for (auto iter = playerBase->headPart.Begin(); !iter.End(); iter.Next()) {
				if (*iter) { beardSetList.Remove((*iter)->GetFormID()); };
			}
		}
		CdeclCall<void>(0x705870, 2);
	}
}