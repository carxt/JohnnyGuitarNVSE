#include <unordered_map>
#include <inttypes.h>
#include <mutex>
std::unordered_map<uint32_t, const char *> g_EditorNameMap;
std::mutex g_NameMapLock;

// TESForm::GetName() is the vfunc at +0x130
// TESForm::GetId() returns the form id



// vftable + 0x90
void TESForm::hk_GetFullTypeName(char *Buffer, uint32_t BufferSize)
{
	const char *typeName = (const char*)ThisStdCall(0x00440E30, this); // TESForm_getRecordType

	_snprintf_s(Buffer, _TRUNCATE, BufferSize, "%s Form '%s' (%08X)", typeName, GetName(), GetId());
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

// 0x0055D480
const char *TESObjectREFR::hk_GetName()
{
	if (!*(bool *)0x11C40C8)
	{
		*(bool *)0x11C40C8 = true;
		const char *name = GetName();
		*(bool *)0x11C40C8 = false;

		if (name && strlen(name) > 0)
			return name;
	}

	TESForm *base = TESObjectREFR::baseForm;

	if (!base || (*(byte *)0x11C3F2C + 0x61D))
		return "";

	const char *name = base->GetName();

	if (name && strlen(name) > 0)
		return name;

	// Now it tries fetching any ExtraData - omitted because I don't care
	return "";
}


