#include "FilteredBarberMenu.hpp"
#include "GameObjects.h"
#include "Bethesda/Interface.hpp"

#include "JGSetList.hpp"

namespace FilteredBarberMenu {
	STACK_FRAME_OPT_ENABLE

	static JGSetList<FormID>* pHairStyles = nullptr;
	static JGSetList<FormID>* pBeards = nullptr;

	template<uint32_t uiAddress, JGSetList<FormID>*& pList>
	class IsPartPlayableHook {
		static inline HookUtils::CallDetour kDetour;

		bool Hook() {
			bool bPlayable = ThisCall<bool>(kDetour, this);
			if (bPlayable && pList)
				bPlayable = pList->Find(reinterpret_cast<TESForm*>(this)->GetFormID());
			return bPlayable;
		}

	public:
		IsPartPlayableHook() {
			kDetour.ReplaceCall(uiAddress, &IsPartPlayableHook::Hook);
		}
	};

	HookUtils::CallDetour kRaceSexMenuDestructorDetour;
	static void __fastcall ReleaseModelsAndLists(TESRace* apRace) {
		ThisCall(kRaceSexMenuDestructorDetour, apRace);
		Reset();
	}

	void Install() {
		kRaceSexMenuDestructorDetour.ReplaceCall(0x7AC5BE, ReleaseModelsAndLists);
		IsPartPlayableHook<0x7AD35C, pBeards>();
		IsPartPlayableHook<0x7AF35B, pHairStyles>();
		IsPartPlayableHook<0x7B1D4A, pHairStyles>();
	}

	SPEC_NOINLINE void Reset() {
		delete pHairStyles;
		pHairStyles = nullptr;

		delete pBeards;
		pBeards = nullptr;
	}

	SPEC_NOINLINE static void __fastcall ApplyFormFilter(JGSetList<FormID>* apList, const TESForm* apForm) {
		if (apList->bIsWhiteList)
			apList->Add(apForm->GetFormID());
		else
			apList->Remove(apForm->GetFormID());
	}

	SPEC_NOINLINE static void __fastcall InitFormFilter(JGSetList<FormID>*& apList, bool abWhiteList) {
		if (!apList)
			apList = new JGSetList<FormID>(abWhiteList);
		else
			apList->bIsWhiteList = abWhiteList;
	}

	static void __fastcall InitCustomFilter(const BGSListForm* apFilterList) {
		auto pIter = apFilterList->GetFormList();
		while (pIter && !pIter->IsEmpty()) {
			const TESForm* pForm = pIter->GetItem();
			pIter = pIter->GetNext();

			if (!pForm) [[unlikely]]
				continue;

			if (IS_ID(pForm, TESHair))
				pHairStyles->Add(pForm->GetFormID());
			else if (IS_ID(pForm, BGSHeadPart))
				pBeards->Add(pForm->GetFormID());
		};
	}

	SPEC_NOINLINE void __fastcall ShowMenu(Bitfield32 auiFlags, const BGSListForm* apFilterList) {
		const TESNPC* pPlayerBase = reinterpret_cast<TESNPC*>(PlayerCharacter::GetSingleton()->GetActorBase());

		InitFormFilter(pHairStyles, auiFlags.Get<Flags::WHITELIST_HAIR>());
		InitFormFilter(pBeards, auiFlags.Get<Flags::WHITELIST_BEARD>());

		if (apFilterList)
			InitCustomFilter(apFilterList);

		ApplyFormFilter(pHairStyles, pPlayerBase->GetHair());

		auto pIter = pPlayerBase->GetHeadPartList();
		while (pIter && !pIter->IsEmpty()) {
			const BGSHeadPart* pPart = pIter->GetItem();
			pIter = pIter->GetNext();
			if (pPart) [[likely]]
				ApplyFormFilter(pBeards, pPart);
		}

		Interface::CreateRaceSexMenu(2);
	}

	STACK_FRAME_OPT_RESET
}