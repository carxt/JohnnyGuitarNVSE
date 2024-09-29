#include <unordered_map>

extern NiTMap<const char*, TESForm*>** g_gameFormEditorIDsMap;

std::unordered_map<uint32_t, const char**> g_EditorNameMap;
std::mutex g_NameMapLock;

bool IsInserted(uint32_t id, const char** name) {
	auto itr = g_EditorNameMap.find(id);
	if (itr != g_EditorNameMap.end()) {
		if (strcmp(*itr->second, *name)) {
			PrintDebug("%08X - Tried to replace EDID \"%s\" with \"%s\"", id, *itr->second, *name);
			return true;
		}
	}
	else if (id) {
		PrintDebug("%08X - Inserted EDID \"%s\"", id, *name);
	}
	else {
		PrintDebug("We have a FormID of 0, this shouldn't happen.");
	}
	return false;
}

__declspec(naked) void GetNameHook() {
	__asm jmp TESForm::hk_GetName
}
__declspec(naked) void SetEditorIdHook() {
	__asm jmp TESForm::hk_SetEditorId
}
__declspec(naked) void REFRSetEditorIdHook() {
	__asm jmp TESForm::hk_REFRSetEditorID
}

void __fastcall AVInfoSetEditorIDHook(TESForm* form, UInt32 EDX, char* name) {
	form->SetEditorID(name);
}

const char** AddToGameMap(const char* name, TESForm* form) {
	ThisStdCall<NiTMap<const char*, TESForm*>::Entry*>(0x470200, *g_gameFormEditorIDsMap, name, form); // adds it to the game map
	auto* entry = (*g_gameFormEditorIDsMap)->LookupEntry(name);
	if (!entry) // shouldn't happen
		return nullptr;
	return &entry->key;
}

bool __fastcall TESQuestSetEditorIdHook(TESQuest* Form, UInt32 EDX, const char* Name) {
	if (!(((bool(__thiscall*)(TESQuest*, const char*))(0x60DAB0))(Form, Name))) return false;
	if (strcmp(Name, "SysWindowCompileAndRun")) {
		std::lock_guard<std::mutex> lock(g_NameMapLock);
		auto** name = AddToGameMap(Name, Form);
		if (name) {
#if _DEBUG
			IsInserted(Form->GetId(), name);
#endif
			g_EditorNameMap.insert(std::make_pair(Form->GetId(), name));
		}
			
	}
	return true;
}

// exported
UInt32 __cdecl JGNVSE_GetFormIDFromEDID(char* edid) {
	TESForm* form = ((TESForm * (__cdecl*)(char*))(0x483A00))(edid); //LookupEditorID
	if (form) {
		return form->refID;
	}
	return 0;
}

// vftable + 0x130
const char* TESForm::hk_GetName() {
	std::lock_guard<std::mutex> lock(g_NameMapLock);
	auto itr = g_EditorNameMap.find(GetId());

	if (itr != g_EditorNameMap.end())
		return *itr->second;

	// By default the game returns an empty string
	return "";
}

// vftable + 0x134
bool TESForm::hk_SetEditorId(const char* Name) {
	if (strcmp(Name, "SysWindowCompileAndRun")) {
		std::lock_guard<std::mutex> lock(g_NameMapLock);
		auto** name = AddToGameMap(Name, this);
		if (name) {
#if _DEBUG
			IsInserted(GetId(), name);
#endif
			g_EditorNameMap.insert(std::make_pair(GetId(), name));
		}
	}
	return true;
}

bool TESForm::hk_REFRSetEditorID(const char* Name) {
	std::lock_guard<std::mutex> lock(g_NameMapLock);
	if ((refID < 0xFF000000) && ((flags & 0x420) == 0x400)) {
		auto** name = AddToGameMap(Name, this);
		if (name) {
#if _DEBUG
			IsInserted(GetId(), name);
#endif
			g_EditorNameMap.insert(std::make_pair(GetId(), name));
		}
	}
	return true;
}
const char* __fastcall ConsoleNameHook(TESObjectREFR* ref) {
	__try {
		const char* name = ref->baseForm->GetTheName();
		if (!strlen(name)) name = ref->baseForm->GetName();
		return name;
	}
	__except (EXCEPTION_ACCESS_VIOLATION) {
		return "";
	}
	return "";
}

void RemoveEDID(uint32_t id, bool removeFromGame) {
	auto itr = g_EditorNameMap.find(id);
	if (itr != g_EditorNameMap.end()) {
		if (removeFromGame) {
#if _DEBUG
			PrintDebug("%08X - Completely Removed EDID \"%s\"", id, *itr->second);
#endif
			ThisStdCall(0xE91FD0, *g_gameFormEditorIDsMap, itr->second);
		}
#if _DEBUG
		else {
			PrintDebug("%08X - Removed EDID \"%s\"", id, *itr->second);
		}
#endif
		g_EditorNameMap.erase(itr);
	}
}

void __fastcall TESDataHandler__RemoveIDFromDataHandler(void* apThis, void*, unsigned int aiID) {
	ThisStdCall(0x4696F0, apThis, aiID);

	std::lock_guard<std::mutex> lock(g_NameMapLock);
	RemoveEDID(aiID, true);
}

void __fastcall NiTMapBase_DWORD_DWORD___SetAt(void* apThis, void*, UInt32 key, TESForm* val) {
	ThisStdCall(0x844700, apThis, key, val);
	UInt32 newID = key;
	UInt32 oldID = val->GetId();
	std::lock_guard<std::mutex> lock(g_NameMapLock);
	auto itr = g_EditorNameMap.find(val->GetId());
	if (itr != g_EditorNameMap.end()) {
		// No removal from game map here because it's not being deleted
		const char** name = itr->second;
#if _DEBUG
		PrintDebug("%08X -> %08X - Removing stale FormID entry for \"%s\"", oldID, newID, *name);
#endif
		g_EditorNameMap.erase(itr);

		RemoveEDID(newID, false);

#if _DEBUG
		IsInserted(newID, name);
#endif
		g_EditorNameMap.insert(std::make_pair(newID, name));
	}
}

void LoadEditorIDs() {
	WriteRelCall(0x486903, (UInt32(GetNameHook))); // replaces empty string with editor id in TESForm::GetDebugName
	WriteRelCall(0x71B748, UInt32(ConsoleNameHook)); // replaces empty string with editor id in selected ref name in console
	WriteRelCall(0x710BFC, UInt32(ConsoleNameHook));
	WriteRelCall(0x55D498, (UInt32(GetNameHook))); // replaces empty string with editor id in TESObjectREFR::GetDebugName
	SafeWrite16(0x467A12, 0x3AEB); // loads more types in game's editor:form map

	WriteRelCall(0x483D12, UInt32(TESDataHandler__RemoveIDFromDataHandler)); // removes editor id in TESForm's destructor
	WriteRelCall(0x485D0B, UInt32(TESDataHandler__RemoveIDFromDataHandler)); // removes editor id in TESForm::SetFormID (only if the ID is being freed)
	WriteRelCall(0x485D24, UInt32(NiTMapBase_DWORD_DWORD___SetAt));			 // replaces editor id in TESForm::SetFormID

	for (uint32_t i = 0; i < ARRAYSIZE(TESForm_Vtables); i++) {
		if (*(uintptr_t*)(TESForm_Vtables[i] + 0x130) == 0x00401280)
			SafeWrite32(TESForm_Vtables[i] + 0x130, (UInt32)GetNameHook);

		if (*(uintptr_t*)(TESForm_Vtables[i] + 0x134) == 0x00401290)
			SafeWrite32(TESForm_Vtables[i] + 0x134, (UInt32)SetEditorIdHook);
	}
	for (uint32_t i = 0; i < ARRAYSIZE(TESObjectREFR_Vtables); i++) {
		if (*(uintptr_t*)(TESObjectREFR_Vtables[i] + 0x130) == 0x00401280)
			SafeWrite32(TESObjectREFR_Vtables[i] + 0x130, (UInt32)GetNameHook);

		if (*(uintptr_t*)(TESObjectREFR_Vtables[i] + 0x134) == 0x00401290)
			SafeWrite32(TESObjectREFR_Vtables[i] + 0x134, (UInt32)REFRSetEditorIdHook);
	}

	// TESQuest
	SafeWrite32(0x104AC44 + 0x130, (UInt32)GetNameHook);
	SafeWrite32(0x104AC44 + 0x134, (UInt32)(TESQuestSetEditorIdHook));

	// ActorValueInfo
	WriteRelCall(0x66FF57, reinterpret_cast<UInt32>(AVInfoSetEditorIDHook));
}
