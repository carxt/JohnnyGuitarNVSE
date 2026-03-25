#include "BarterFilter.hpp"
#include <GameExtraData.h>
#include "GameUI.h"

namespace BarterFilter {
	std::unordered_map<DWORD, JGSetList<DWORD>> leftList;
	std::unordered_map<DWORD, JGSetList<DWORD>> rightList;

	enum Flags {
		kDoNotHideLeft = 1 << 0,
		kDoNotHideRight
	};

	template <uintptr_t a_addr>
	class BarterLeftHook {
	private:
		static inline uintptr_t hookCall = a_addr;
	public:
		static  DWORD __cdecl Hook(ItemChange* ref) {
			auto shouldHide = CdeclCall<bool>(hookCall, ref);
			if (shouldHide) { return shouldHide; }
			auto barterMenu = *(BarterMenu**)0x11D8FA4;
			if (!barterMenu) return shouldHide;
			auto merchantRef = barterMenu->merchantRef;
			if (!merchantRef) return shouldHide;
			auto originalForm = ref->pObject;
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
		static  DWORD __cdecl Hook(ItemChange* ref) {
			auto shouldHide = CdeclCall<bool>(hookCall, ref);
			if (shouldHide) { return shouldHide; }
			auto barterMenu = *(BarterMenu**)0x11D8FA4;
			if (!barterMenu) return shouldHide;
			auto merchantRef = barterMenu->merchantRef;
			if (!merchantRef) return shouldHide;
			auto originalForm = ref->pObject;
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

	void Add(uint32_t item, uint32_t flags, uint32_t vendor)
	{
		if ((flags & kDoNotHideLeft) == 0) {
			leftList[item].Add(vendor);
			leftList[item].isWhiteList = true;
		}
		if ((flags & kDoNotHideRight) == 0) {
			rightList[item].Add(vendor);
			rightList[item].isWhiteList = true;
		}
	}

	void Remove(uint32_t item, uint32_t flags, uint32_t vendor)
	{
		if ((flags & kDoNotHideLeft) == 0) {
			auto it = leftList.find(item);
			if (it != leftList.end()) {
				if (vendor) {
					it->second.Remove(vendor);
				}
				else {
					it->second.dFlush();
					leftList.erase(it);
				}
			}

		}
		if ((flags & kDoNotHideRight) == 0) {

			auto it = rightList.find(item);
			if (it != rightList.end()) {
				if (vendor) {
					it->second.Remove(vendor);
				}
				else {
					it->second.dFlush();
					rightList.erase(it);
				}
			}
		}
	}
	uint32_t IsHidden(uint32_t item)
	{
		uint32_t result = 0;
		auto it = BarterFilter::leftList.find(item);
		if (it != BarterFilter::leftList.end()) {
			result |= 1 << 0;
		}
		it = BarterFilter::rightList.find(item);
		if (it != BarterFilter::rightList.end()) {
			result |= 1 << 1;
		}
		return result;
	}
};