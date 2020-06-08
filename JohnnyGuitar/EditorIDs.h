#include <unordered_map>
#include <inttypes.h>
#include <mutex>
std::unordered_map<uint32_t, const char *> g_EditorNameMap;
std::mutex g_NameMapLock;


namespace SpecialCaseEDIDs
{
	bool __fastcall SetEditorIdHookForTESQuest(TESQuest* Form, UInt32 EDX, const char* Name)
	{
		if (!(((bool(__thiscall*)(TESQuest*, const char*))(0x60DAB0))(Form, Name))) return false;
		if (strcmp(Name, "SysWindowCompileAndRun")) {
			std::lock_guard<std::mutex> lock(g_NameMapLock);
			g_EditorNameMap.insert(std::make_pair(Form->GetId(), _strdup(Name)));
		}
		return true;
	}
	void Handle()
	{

		//TESQuest

		SafeWrite32(0x104AC44 + 0x130, (UInt32)GetNameHook);
		SafeWrite32(0x104AC44 + 0x134, (UInt32)(SetEditorIdHookForTESQuest));
	}
}


UInt32 __cdecl JGNVSE_GetFormIDFromEDID(char* edid) {
	TESForm *form = ((TESForm * (__cdecl*)(char*))(0x483A00))(edid); //LookupEditorID
	if (form) {
		return form->refID;
	}
	return 0;
}

// vftable + 0x130
const char *TESForm::hk_GetName()
{
	std::lock_guard<std::mutex> lock(g_NameMapLock);
	auto itr = g_EditorNameMap.find(GetId());

	if (itr != g_EditorNameMap.end())
		return itr->second;

	// By default the game returns an empty string
	return "";
}

// vftable + 0x134
bool TESForm::hk_SetEditorId(const char *Name)
{
	if (strcmp(Name, "SysWindowCompileAndRun")) {
		std::lock_guard<std::mutex> lock(g_NameMapLock);
		g_EditorNameMap.insert(std::make_pair(GetId(), _strdup(Name)));
	}
	return true;
}

bool TESForm::hk_SetEditorID_REFR(const char* Name)
{
	std::lock_guard<std::mutex> lock(g_NameMapLock);
	if ((refID < 0xFF000000) && ((flags & 0xC20) == 0x400)) {
		g_EditorNameMap.insert(std::make_pair(GetId(), _strdup(Name)));
	}
	return true;
}

