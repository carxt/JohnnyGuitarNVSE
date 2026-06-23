#include "JIPSettings.hpp"
#include "JIPUtils.hpp"

namespace JIPSettings {

	bool IsSettingClear(const char* apSetting, const char* apPath) {
		return GetPrivateProfileInt("JIP", apSetting, 1, apPath) == 0;
	}

	void InitConditionalHooks() {
		char cFilename[MAX_PATH];
		GetModuleFileNameA(NULL, cFilename, MAX_PATH);
		char* pLastSlash = strrchr(cFilename, '\\') + 1;
		uint32_t uiLength = MAX_PATH - (pLastSlash - cFilename);
		strcpy_s(pLastSlash, uiLength, "Data\\nvse\\plugins\\JohnnyGuitar.ini");

		if (IsSettingClear("bFixPositiveChemDuration", cFilename))
			HookUtils::PatchMemoryNopRange(JIPUtils::GetAddress(0x100128C3), JIPUtils::GetAddress(0x100128E1));

		if (IsSettingClear("bWorldSpaceShellCasings", cFilename))
			HookUtils::PatchMemoryNopRange(JIPUtils::GetAddress(0x10011F9A), JIPUtils::GetAddress(0x10011FA9));
	}

}