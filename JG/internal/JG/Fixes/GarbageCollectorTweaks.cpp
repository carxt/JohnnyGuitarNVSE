#include "GarbageCollectorTweaks.hpp"
#include "Bethesda/Actor.hpp"
#include "Bethesda/ProcessLists.hpp"
#include "Bethesda/RefActivateData.hpp"

#include <shared/SafeWrite/SafeWrite.hpp>

namespace GarbageCollectorTweaks {

	STACK_FRAME_OPT_ENABLE
	HookUtils::CallDetour kGetFormIDDetour;
	static uint32_t __fastcall GetFormID(TESForm* apForm) {
		return apForm ? ThisCall<uint32_t>(kGetFormIDDetour, apForm) : 0;
	}

	HookUtils::CallDetour kRelease3DRelatedDataDetour;
	static void __fastcall Release3DRelatedData(TESObjectREFR* apRef) {
		if (apRef->GetInitialized()) {
			ExtraDataList* pExtra = apRef->GetExtra();
			for (auto pIter = pExtra->GetActivateRefChildren(); pIter && !pIter->IsEmpty(); pIter = pIter->GetNext()) {
				pIter->GetItem()->pActivateRef->GetExtra()->RemoveActivateParent(apRef);
			}

			TESObjectREFR* pParent = apRef->GetEnableStateParent();
			if (pParent)
				pParent->GetExtra()->RemoveEnableStateChild(apRef);

			for (auto pIter = pExtra->GetEnableStateChildren(); pIter && !pIter->IsEmpty(); pIter = pExtra->GetEnableStateChildren()) {
				pIter->GetItem()->SetEnableStateParent(nullptr);
			}
		}

		if (apRef->IsActor())
			ProcessLists::GetSingleton()->RemoveActorFromTempChangeList(static_cast<Actor*>(apRef));

		ThisCall(kRelease3DRelatedDataDetour, apRef);
	}

	HookUtils::CallDetour kGetLODTreeDetour;
	static bool __fastcall GetLODTree(TESForm* apForm) {
		return apForm ? ThisCall<bool>(kGetLODTreeDetour, apForm) : false;
	}
	STACK_FRAME_OPT_RESET

	void Install() {
		// Inspired by CE's changes and my own experience (read: crashes)

		// Nullcheck ref at the start of the func
		// Bethesda nullchecks it... after using it
		kGetFormIDDetour.ReplaceCall(0x8680A4, GetFormID);

		// Remove ref from various containers - normally they get removed in the destructor itself
		// Aka, too late
		kRelease3DRelatedDataDetour.ReplaceCall(0x868028, Release3DRelatedData);
		
		// Nullcheck the baseform ptr because game doesn't (it only does it in the destructor itself)
		kGetLODTreeDetour.ReplaceCall(0x8680B3, GetLODTree);
	}

}