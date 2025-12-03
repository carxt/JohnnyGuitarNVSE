#include <unordered_map>
#include <GameObjects.h>
#include <SafeWrite.h>
#include "misc.h"
#include <internal/JohnnyExtraData.hpp>

extern NiTMap<const char*, TESForm*>** g_gameFormEditorIDsMap;

namespace EDIDRestoration {

#define DEBUG_PRINTS 0

#if DEBUG_PRINTS
#define DEBUG_MSG(...) PrintLog(__VA_ARGS__)
#else
#define DEBUG_MSG(...)
#endif

	std::mutex g_NameMapLock;

	void __fastcall AddEDIDToExtraData(TESForm* apForm, const char* apEDID) {
		JohnnyExtraData* data = JohnnyExtraData::GetOrCreate(apForm);

		if (!data->kFormData.strEditorID) [[likely]] {
			DEBUG_MSG("%08X -> %s", apForm->refID, apEDID);
			data->kFormData.strEditorID = apEDID;
		}
		else if (data->kFormData.strEditorID != apEDID) [[unlikely]] {
			DEBUG_MSG("Warning: %08X already has an editor ID: %s, not overwriting with %s", apForm->refID, data->kFormData.strEditorID.c_str(), apEDID);
		}
	}

	const char* __fastcall GetEDIDFromExtraData(TESForm* apForm) {
		JohnnyExtraData* data = JohnnyExtraData::Find(apForm);
		if (data) [[likely]] {
			return data->kFormData.strEditorID.c_str();
		}
		return nullptr;
	}

	const char* __fastcall AddToGameMap(const char* apEDID, TESForm* apForm) {
		ThisCall<NiTMap<const char*, TESForm*>::Entry*>(0x470200, *g_gameFormEditorIDsMap, apEDID, apForm); // adds it to the game map
		auto* pItem = (*g_gameFormEditorIDsMap)->LookupEntry(apEDID);
		if (!pItem) [[unlikely]] // shouldn't happen
			return nullptr;
		return pItem->key;
	}

	// exported
	UInt32 __cdecl JGNVSE_GetFormIDFromEDID(char* apEDID) {
		TESForm* pForm = CdeclCall<TESForm*>(0x483A00, apEDID); // TESForm::GetFormByEditorID
		if (pForm) {
			return pForm->refID;
		}
		return 0;
	}

	class TESFormEx : public TESForm {
	public:
		// vftable + 0x130
		const char* hk_GetFormEditorID() {
			const char* pEDID = GetEDIDFromExtraData(this);
			if (pEDID)
				return pEDID;

			return "";
		}

		// vftable + 0x134
		bool hk_SetFormEditorID(const char* apEDID) {
			if (apEDID && strcmp(apEDID, "SysWindowCompileAndRun") != 0) {
				if (GetTemporary()) {
					AddEDIDToExtraData(this, apEDID);
				}
				else {
					std::lock_guard<std::mutex> lock(g_NameMapLock);
					const char* pEDID = AddToGameMap(apEDID, this);
					if (pEDID) {
						AddEDIDToExtraData(this, apEDID);
					}
				}
			}
			return true;
		}
	};

	class TESObjectREFREx : public TESObjectREFR {
	public:
		const char* GetNameForConsole() {
			if (baseForm) [[likely]] {
				__try {
					const char* name = baseForm->GetTheName();
					if (!name || !strlen(name))
						name = baseForm->GetFormEditorID();
					return name;
				}
				__except (EXCEPTION_ACCESS_VIOLATION) {
					return "";
				}
			}
			return "";
		}
	};

	template<uint32_t VTABLE_ADDR>
	class CustomSetReplacer {
	private:
		static inline VirtFuncDetour kDetour;

		bool SetFormEditorID(const char* apEDID) {
			bool bResult = ThisCall<bool>(kDetour.GetOverwrittenAddr(), this, apEDID);
			if (bResult) {
				return reinterpret_cast<TESFormEx*>(this)->hk_SetFormEditorID(apEDID);
			}
			return bResult;
		}

	public:
		CustomSetReplacer() {
			kDetour.ReplaceVirtualFuncEx(VTABLE_ADDR, &CustomSetReplacer::SetFormEditorID);
		}
		~CustomSetReplacer() {
		}
	};

	void InitHooks() {
		ReplaceCallEx(0x486903, &TESFormEx::hk_GetFormEditorID); // TESForm::GetFormDetailedString
		ReplaceCallEx(0x451CBA, &TESFormEx::hk_GetFormEditorID); // TESObjectCELL::GetCellName
		ReplaceCallEx(0x55D498, &TESFormEx::hk_GetFormEditorID); // TESObjectREFR::GetFormEditorID
		
		ReplaceCallEx(0x71B748, &TESObjectREFREx::GetNameForConsole); // replaces empty string with editor id in selected ref name in console
		ReplaceCallEx(0x710BFC, &TESObjectREFREx::GetNameForConsole);

		ReplaceCallEx(0x66FF57, &TESFormEx::hk_SetFormEditorID); // ActorValueInfo::ActorValueInfo
		
		SafeWrite16(0x467A12, 0x3AEB); // loads more types in game's editor:form map

		for (uint32_t i = 0; i < ARRAYSIZE(TESForm_Vtables); i++) {
			if (*reinterpret_cast<uintptr_t*>(TESForm_Vtables[i] + 0x130) == 0x00401280)
				ReplaceVirtualFuncEx(TESForm_Vtables[i] + 0x130, &TESFormEx::hk_GetFormEditorID);

			if (*reinterpret_cast<uintptr_t*>(TESForm_Vtables[i] + 0x134) == 0x00401290)
				ReplaceVirtualFuncEx(TESForm_Vtables[i] + 0x134, &TESFormEx::hk_SetFormEditorID);
		}

		// These forms already have SetFormEditorID that stores EDID in ExtraData, or a member variable
		// We wrap these functions to ensure the EDID is also stored in JohnnyExtraData, and updated in the game map
		CustomSetReplacer<0x102EAE8> kTESObjectCELL;
		CustomSetReplacer<0x1031A90> kTESWorldSpace;
		CustomSetReplacer<0x1036658> kTESGlobal;
		CustomSetReplacer<0x1045130> kTESSound;
		CustomSetReplacer<0x1047470> kBGSVoiceType;
		CustomSetReplacer<0x1049E40> kTESIdleForm;
		CustomSetReplacer<0x104AD78> kTESQuest;
		CustomSetReplacer<0x104B5F0> kTESRace;
		CustomSetReplacer<0x104D2D0> kTESTopic;
	}
}