#include "DisabledSaves.hpp"
#include <Bethesda/BGSSaveLoadManager.hpp>
#include <unordered_map>
#include <utility.h>

namespace DisabledSaves {
#pragma optimize("y", off)
	std::unordered_map<uint8_t, Bitfield32> kSaveBlockers;

	enum SaveTypeBits {
		NORMAL = 0,
		AUTO   = 1,
		SYSTEM = 2,
		FORCED = 3,
		QUICK  = 4,
	};

	CallDetour kCanSaveNowDetour;
	bool __fastcall CanSaveNowHook(BGSSaveLoadManager* apThis, void*, bool abAutoSave) {
		bool bCanSave = ThisCall<bool>(kCanSaveNowDetour.GetOverwrittenAddr(), apThis, abAutoSave);
		if (kSaveBlockers.empty())
			return bCanSave;

		if (bCanSave) {
			uint8_t* pEBP = GetParentBasePtr(_AddressOfReturnAddress());
			const bool bSystemSave = *reinterpret_cast<bool*>(pEBP - 0x9);
			const bool bQuickSave = *reinterpret_cast<bool*>(pEBP - 0x232);
			const bool bForcedSave = apThis->ucForceSaveTimer;

			uint32_t uiFlags = 0;
			if (bSystemSave)
				uiFlags |= (1 << SYSTEM);

			if (bQuickSave)
				uiFlags |= (1 << QUICK);

			if (bForcedSave)
				uiFlags |= (1 << FORCED);

			if (abAutoSave)
				uiFlags |= (1 << AUTO);


			for (auto& rMod : kSaveBlockers) {
				if (rMod.second.Get(uiFlags))
					return false;
				else if (rMod.second.GetBit(NORMAL) && !uiFlags)
					return false;
			}
		}

		return bCanSave;
	}

	CallDetour kSaveNowMenuDetour;
	bool __fastcall CanSaveNowMenuHook(void* apThis, void*, bool abAutoSave) {
		bool bCanSave = ThisCall<bool>(kCanSaveNowDetour.GetOverwrittenAddr(), apThis, abAutoSave);
		if (kSaveBlockers.empty())
			return bCanSave;

		if (bCanSave) {
			for (auto& rMod : kSaveBlockers) {
				if (rMod.second.GetBit(NORMAL))
					return false;
			}
		}

		return bCanSave;
	}

	void Init() {
		kSaveBlockers.reserve(0xFF);
	}

	void Reset() {
		kSaveBlockers.clear();
	}

	void Install() {
		// ToggleDisableSaves
		kCanSaveNowDetour.ReplaceCall(0x850442, CanSaveNowHook);
		kSaveNowMenuDetour.ReplaceCall(0x7CBDC7, CanSaveNowMenuHook);
	}

	void Toggle(uint8_t aucMod, bool abToggle, uint32_t auiTypeFlags) {
		if (abToggle)
			kSaveBlockers.insert({ aucMod, auiTypeFlags });
		else
			kSaveBlockers.erase(aucMod);
	}
#pragma optimize("y", on)
}
