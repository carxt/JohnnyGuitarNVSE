#include "BarterFilter.hpp"
#include "GameExtraData.h"
#include "GameUI.h"

#include "JGSetList.hpp"

#include "unordered_map"

namespace BarterFilter {
	using SellerFilter = std::unordered_set<uint32_t>;
	using ItemFilterMap = std::unordered_map<uint32_t, SellerFilter>;

	struct BarterFilters {
		enum FilterType {
			PLAYER,
			VENDOR,
			COUNT,
		};

		ItemFilterMap kItems[FilterType::COUNT];

		bool __fastcall Add(FilterType auiFilter, uint32_t auiItemFormID, uint32_t auiSellerFormID) {
			kItems[auiFilter][auiItemFormID].insert(auiSellerFormID);
			return true;
		}

		bool __fastcall Remove(FilterType auiFilter, uint32_t auiItemFormID, uint32_t auiSellerFormID) {
			bool bResult = false;
			ItemFilterMap& rItems = kItems[auiFilter];
			auto it = rItems.find(auiItemFormID);
			if (it != rItems.end()) {
				if (auiSellerFormID) {
					it->second.erase(auiSellerFormID);
				}
				else {
					it->second.clear();
					rItems.erase(it);
				}
				bResult |= true;
			}
			return bResult;
		}
		
		bool __fastcall Find(FilterType auiFilter, uint32_t auiItemFormID, uint32_t auiSellerFormID) {
			bool bResult = false;
			ItemFilterMap& rItems = kItems[auiFilter];
			auto it = rItems.find(auiItemFormID);
			if (it != rItems.end()) {
				bResult = true;
				if (auiSellerFormID)
					bResult = it->second.contains(auiSellerFormID);
			}
			return bResult;
		}

		DECLSPEC_NOINLINE bool __fastcall ShouldHideItem(FilterType auiFilter, const ItemChange* apItem) const {
			bool bShouldHide = false;
			const BarterMenu* pBarterMenu = BarterMenu::GetSingleton();
			if (!pBarterMenu) [[unlikely]]
				return bShouldHide;

			const TESObjectREFR* pMerchant = pBarterMenu->merchantRef;
			if (!pMerchant) [[unlikely]]
				return bShouldHide;

			const TESBoundObject* pObject = apItem->pObject;
			if (!pObject) [[unlikely]]
				return bShouldHide;

			const BSSimpleList<ItemChange*>* pMovedItems = auiFilter == FilterType::PLAYER ? &pBarterMenu->kItemsToBuy : &pBarterMenu->kItemsToSell;
			while (pMovedItems && !pMovedItems->IsEmpty()) {
				if (pMovedItems->GetItem() && pMovedItems->GetItem()->pObject == pObject)
					return bShouldHide;
				pMovedItems = pMovedItems->GetNext();
			}

			const ItemFilterMap& rItems = kItems[auiFilter];
			auto it = rItems.find(pObject->GetFormID());
			if (it != rItems.end()) {
				auto& rBarterSet = it->second;
				bShouldHide = rBarterSet.contains(pMerchant->GetFormID())
					|| rBarterSet.contains(pMerchant->baseForm->GetFormID())
					|| rBarterSet.contains(0)
					|| rBarterSet.contains(PlayerCharacter::GetSingleton()->GetFormID());
			}
			return bShouldHide;
		}
	};

	BarterFilters* pBarterFilters = nullptr;

	enum Flags {
		SHOW_IN_PLAYER = 1 << 0,
		SHOW_IN_VENDOR = 1 << 1,
	};



	template <uintptr_t uiAddress, BarterFilters::FilterType eFilter>
	class BarterHook {
	private:
		static inline HookUtils::CallDetour kDetour;
	public:
		static bool __cdecl FilterHook(ItemChange* apItem) {
			bool bShouldHide = CdeclCall<bool>(kDetour, apItem);
			if (bShouldHide || !pBarterFilters)
				return bShouldHide;

			return pBarterFilters->ShouldHideItem(eFilter, apItem);
		}

		BarterHook() {
			kDetour.SafeWrite32(uiAddress + 1, BarterHook::FilterHook);
		}
	};

	void Install() {
		BarterHook<0x72DA1C, BarterFilters::PLAYER>(); // BarterMenu::DoClick
		BarterHook<0x72DACA, BarterFilters::VENDOR>(); // BarterMenu::DoClick

		BarterHook<0x72E1BE, BarterFilters::PLAYER>(); // BarterMenu::UpdateLists
		BarterHook<0x72E207, BarterFilters::VENDOR>(); // BarterMenu::UpdateLists
	}

	void Reset() {
		if (pBarterFilters) {
			delete pBarterFilters;
			pBarterFilters = nullptr;
		}
	}

	bool __fastcall Add(uint32_t auiItemFormID, uint32_t auiFlags, uint32_t auiSellerFormID) {
		bool bResult = false;

		if (!pBarterFilters)
			pBarterFilters = new BarterFilters();

		if (pBarterFilters) {
			for (uint32_t i = 0; i < BarterFilters::COUNT; ++i) {
				if ((auiFlags & (1 << i)) == 0)
					bResult |= pBarterFilters->Add(BarterFilters::FilterType(i), auiItemFormID, auiSellerFormID);
			}
		}

		return bResult;
	}

	bool __fastcall Remove(uint32_t auiItemFormID, uint32_t auiFlags, uint32_t auiSellerFormID) {
		bool bResult = false;
		if (pBarterFilters) {
			for (uint32_t i = 0; i < BarterFilters::COUNT; ++i) {
				if ((auiFlags & (1 << i)) == 0)
					bResult |= pBarterFilters->Remove(BarterFilters::FilterType(i), auiItemFormID, auiSellerFormID);
			}
		}

		return bResult;
	}

	uint32_t __fastcall IsHidden(uint32_t auiItemFormID, uint32_t auiSellerFormID) {
		uint32_t uiResult = 0;
		if (pBarterFilters) {
			for (uint32_t i = 0; i < BarterFilters::COUNT; ++i) {
				uiResult |= !pBarterFilters->Find(BarterFilters::FilterType(i), auiItemFormID, auiSellerFormID) << i;
			}
		}

		return uiResult;
	}
};