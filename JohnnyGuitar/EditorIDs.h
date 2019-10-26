#include <unordered_map>
#include <inttypes.h>
#include <mutex>
std::unordered_map<uint32_t, const char *> g_EditorNameMap;
std::mutex g_NameMapLock;
UInt32 GetRefIDFromEditorID(char* edid);
// TESForm::GetName() is the vfunc at +0x130
// TESForm::GetId() returns the form id

UInt32 GetRefIDFromEditorID(char* edid) {
	std::lock_guard<std::mutex> lock(g_NameMapLock);
	for (std::unordered_map<uint32_t, const char *>::const_iterator it = g_EditorNameMap.begin(); it != g_EditorNameMap.end(); ++it) {
		if (!strcmp(edid, it->second)) {
			return it->first;
		}
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



