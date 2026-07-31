#include "DisabledSaves.hpp"
#include <Bethesda/BGSSaveLoadManager.hpp>
#include <Bethesda/GameSettingCollection.hpp>
#include <unordered_map>
#include <utility.h>

namespace DisabledSaves {

	using SaveBlockMap = std::unordered_map<const TESFile*, Bitfield32>;

	SaveBlockMap* pSaveBlockers = nullptr;

	static bool __fastcall CanSave(uint32_t auiFlags) {
		if (pSaveBlockers) {
			for (auto& rMod : *pSaveBlockers) {
				if (rMod.second.Get(auiFlags))
					return false;
				else if (rMod.second.GetBit(SaveTypeBits::NORMAL) && !auiFlags)
					return false;
			}
		}
		return true;
	}

STACK_FRAME_OPT_DISABLE
	HookUtils::CallDetour kCanSaveNowDetour;
	static bool __fastcall CanSaveNowHook(BGSSaveLoadManager* apThis, void*, bool abAutoSave) {
		bool bCanSave = ThisCall<bool>(kCanSaveNowDetour, apThis, abAutoSave);
		if (!pSaveBlockers || pSaveBlockers->empty())
			return bCanSave;

		if (bCanSave) {
			uint8_t* pEBP = GetParentBasePtr(_AddressOfReturnAddress());
			const bool bSystemSave = *reinterpret_cast<bool*>(pEBP - 0x9);
			const bool bQuickSave = *reinterpret_cast<bool*>(pEBP - 0x232);
			const bool bForcedSave = apThis->ucForceSaveTimer;

			uint32_t uiFlags = 0;
			if (bSystemSave)
				uiFlags |= SaveTypeFlags::SYSTEM;

			if (bQuickSave)
				uiFlags |= SaveTypeFlags::QUICK;

			if (bForcedSave)
				uiFlags |= SaveTypeFlags::FORCED;

			if (abAutoSave)
				uiFlags |= SaveTypeFlags::AUTO;


			bCanSave = CanSave(uiFlags);
		}

		return bCanSave;
	}

	HookUtils::CallDetour kSaveNowMenuDetour;
	static bool __fastcall CanSaveNowMenuHook(void* apThis, void*, bool abAutoSave) {
		bool bCanSave = ThisCall<bool>(kCanSaveNowDetour, apThis, abAutoSave);
		if (!pSaveBlockers || pSaveBlockers->empty())
			return bCanSave;

		if (bCanSave)
			bCanSave = CanSave(SaveTypeFlags::NORMAL);

		return bCanSave;
	}

	HookUtils::CallDetour kSaveMessageDetour;
	static bool __cdecl ShowMessage(const char* apText, uint32_t aeEmotion, const char* apImagePath, const char* apSoundName, float afTime, bool abInstant) {
		const bool bCanSave = CanSave(SaveTypeFlags::QUICK);
		const char* pText = apText;
		const char* pImagePath = apImagePath;
		if (!bCanSave) {
			pText = GameSettingCollection::sCantSaveNow->String();
			pImagePath = reinterpret_cast<const char*>(0x10208A0); // glow_message_vaultboy_sad.
		}
		return CdeclCall<bool>(kSaveMessageDetour, pText, aeEmotion, pImagePath, apSoundName, afTime, abInstant);
	}

	void Reset() {
		if (pSaveBlockers) {
			delete pSaveBlockers;
			pSaveBlockers = nullptr;
		}
	}

	void Install() {
		// ToggleDisableSaves
		kCanSaveNowDetour.ReplaceCall(0x850442, CanSaveNowHook);
		kSaveNowMenuDetour.ReplaceCall(0x7CBDC7, CanSaveNowMenuHook);
		kSaveMessageDetour.ReplaceCall(0x8509C7, ShowMessage);
	}
STACK_FRAME_OPT_RESET

	void __fastcall Toggle(const TESFile* apFile, uint32_t auiTypeFlags, bool abToggle) {
		if (!pSaveBlockers)
			pSaveBlockers = new SaveBlockMap;

		if (abToggle)
			pSaveBlockers->insert({ apFile, auiTypeFlags });
		else
			pSaveBlockers->erase(apFile);
	}

}
