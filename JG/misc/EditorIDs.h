#include <unordered_map>

extern NiTMap<const char*, TESForm*>** g_gameFormEditorIDsMap;

std::unordered_map<uint32_t, const char**> g_EditorNameMap;
std::mutex g_NameMapLock;

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
		if (name)
			g_EditorNameMap.insert(std::make_pair(Form->GetId(), name));
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
		if (name)
			g_EditorNameMap.insert(std::make_pair(GetId(), name));
	}
	return true;
}

bool TESForm::hk_REFRSetEditorID(const char* Name) {
	std::lock_guard<std::mutex> lock(g_NameMapLock);
	if ((refID < 0xFF000000) && ((flags & 0x420) == 0x400)) {
		auto** name = AddToGameMap(Name, this);
		if (name)
			g_EditorNameMap.insert(std::make_pair(GetId(), name));
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

void LoadEditorIDs() {
	WriteRelCall(0x486903, (UInt32(GetNameHook))); // replaces empty string with editor id in TESForm::GetDebugName
	WriteRelCall(0x71B748, UInt32(ConsoleNameHook)); // replaces empty string with editor id in selected ref name in console
	WriteRelCall(0x710BFC, UInt32(ConsoleNameHook));
	WriteRelCall(0x55D498, (UInt32(GetNameHook))); // replaces empty string with editor id in TESObjectREFR::GetDebugName
	SafeWrite16(0x467A12, 0x3AEB); // loads more types in game's editor:form map

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
