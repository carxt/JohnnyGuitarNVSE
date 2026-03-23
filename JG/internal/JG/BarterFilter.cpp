#include "BarterFilter.hpp"
#include <GameExtraData.h>
#include "GameUI.h"

namespace BarterFilter {
	std::unordered_map<DWORD, JGSetList<DWORD>> leftList;
	std::unordered_map<DWORD, JGSetList<DWORD>> rightList;

	template <uintptr_t a_addr>
	class BarterLeftHook {
	private:
		static inline uintptr_t hookCall = a_addr;
	public:
		static  DWORD __cdecl Hook(ContChangesEntry* ref) {
			auto shouldHide = CdeclCall<bool>(hookCall, ref);
			if (shouldHide) { return shouldHide; }
			auto barterMenu = *(BarterMenu**)0x11D8FA4;
			if (!barterMenu) return shouldHide;
			auto merchantRef = barterMenu->merchantRef;
			if (!merchantRef) return shouldHide;
			auto originalForm = ref->type;
			if (!PlayerCharacter::GetSingleton()) return shouldHide;
			auto it = leftList.find(originalForm->GetFormID());
			if (it != leftList.end()) {
				auto& barterSet = it->second;
				shouldHide = barterSet.Allow(merchantRef->GetFormID()) || barterSet.Allow(merchantRef->baseForm->GetFormID()) || barterSet.Allow(0) || barterSet.Allow(PlayerCharacter::GetSingleton()->GetFormID());
			}
			return shouldHide;
		}
		BarterLeftHook() {
			uintptr_t hk_hookPoint = hookCall;
			hookCall = *(uintptr_t*)(hk_hookPoint + 1);
			SafeWrite32((hk_hookPoint + 1), (uintptr_t)Hook);

		}

	};

	template <uintptr_t a_addr>
	class BarterRightHook {
	private:
		static inline uintptr_t hookCall = a_addr;
	public:
		static  DWORD __cdecl Hook(ContChangesEntry* ref) {
			auto shouldHide = CdeclCall<bool>(hookCall, ref);
			if (shouldHide) { return shouldHide; }
			auto barterMenu = *(BarterMenu**)0x11D8FA4;
			if (!barterMenu) return shouldHide;
			auto merchantRef = barterMenu->merchantRef;
			if (!merchantRef) return shouldHide;
			auto originalForm = ref->type;
			auto it = rightList.find(originalForm->GetFormID());
			if (it != rightList.end()) {
				auto& barterSet = it->second;
				shouldHide = barterSet.Allow(merchantRef->GetFormID()) || barterSet.Allow(merchantRef->baseForm->GetFormID()) || barterSet.Allow(0) || barterSet.Allow(PlayerCharacter::GetSingleton()->GetFormID());

			}
			return shouldHide;
		}
		BarterRightHook() {
			uintptr_t hk_hookPoint = hookCall;
			hookCall = *(uintptr_t*)(hk_hookPoint + 1);
			SafeWrite32((hk_hookPoint + 1), (uintptr_t)Hook);

		}

	};


	void Install() {
		BarterLeftHook<0x72DA1C>();
		BarterLeftHook<0x72E1BE>();

		BarterRightHook<0x72DACA>();
		BarterRightHook<0x72E207>();

	}
	void Reset()
	{
		leftList.clear();
		rightList.clear();
	}
};