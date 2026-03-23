#include "DisabledSaves.hpp"
#include <unordered_set>

namespace DisabledSaves {
	uintptr_t g_canSaveNowAddr = 0;
	uintptr_t g_canSaveNowMenuAddr = 0;

	std::unordered_set<BYTE> SaveGameUMap;

	bool __fastcall CanSaveNowHook(void* ThisObj, void* edx, int isAutoSave) {
		return ThisCall<bool>(g_canSaveNowAddr, ThisObj, isAutoSave) && SaveGameUMap.empty();
	}

	bool __fastcall CanSaveNowMenuHook(void* ThisObj, void* edx, int isAutoSave) {
		return ThisCall<bool>(g_canSaveNowMenuAddr, ThisObj, isAutoSave) && SaveGameUMap.empty();
	}

	void Init()
	{
		SaveGameUMap.reserve(0xFF);
	}

	void Reset() {
		SaveGameUMap.clear();
	}

	void Install() {
		// ToggleDisableSaves
		g_canSaveNowAddr = (*(uint32_t*)0x0850443) + 5 + 0x0850442;
		WriteRelCall(0x0850442, (uintptr_t)CanSaveNowHook);
		g_canSaveNowMenuAddr = (*(uint32_t*)0x07CBDC8) + 5 + 0x07CBDC7;
		WriteRelCall(0x07CBDC7, (uintptr_t)CanSaveNowMenuHook);
	}
	void Toggle(uint8_t modId, bool toggle)
	{
		if (toggle) {
			SaveGameUMap.insert(modId);
		}
		else {
			SaveGameUMap.erase(modId);
		}
	}
}