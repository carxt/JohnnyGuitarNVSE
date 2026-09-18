#include "INISettingFixes.hpp"
#include "Bethesda/RendererSettingCollection.hpp"
#include "Bethesda/SettingT.hpp"
#include "Bethesda/Script.hpp"
#include "Bethesda/Interface.hpp"

namespace INISettingFixes {
	STACK_FRAME_OPT_ENABLE

	template<uint32_t uiAddress>
	class GetINISettingHook {
		static inline HookUtils::CallDetour kDetour;

		static Setting* __fastcall Hook(INISettingCollection* apINICollection, void*, const char* apSettingName) {
			Setting* pINISetting = ThisCall<Setting*>(kDetour, apINICollection, apSettingName);
			if (pINISetting)
				return pINISetting;

			RendererSettingCollection* pRendererSettings = SettingT<RendererSettingCollection>::GetCollection();
			return ThisCall<Setting*>(kDetour, pRendererSettings, apSettingName);
		}
	public:
		GetINISettingHook() {
			kDetour.ReplaceCall(uiAddress, GetINISettingHook::Hook);
		}
	};

	HookUtils::CallDetour kSaveINIDetour;
	bool __fastcall SaveINIHook(INISettingCollection* apINICollection, void*, const char* apFileName) {
		ThisCall(kSaveINIDetour, apINICollection, apFileName);
		RendererSettingCollection* pRendererSettings = SettingT<RendererSettingCollection>::GetCollection();
		return ThisCall<bool>(kSaveINIDetour, pRendererSettings, pRendererSettings->cSettingFile);
	}

	void __stdcall HandleSettingType(Setting* apSetting, Setting::Type type) {
		if (!Script::GetConsoleOuput())
			return;

		const char* const pKey = apSetting->pKey;

		switch (type) {
			case Setting::kSetting_Bool:
				Interface::PrintLine("INISetting %s >> %i", pKey, apSetting->uValue.b);
				break;
			case Setting::kSetting_Integer:
				Interface::PrintLine("INISetting %s >> %d", pKey, apSetting->uValue.i);
				break;
			case Setting::kSetting_Unsigned:
				Interface::PrintLine("INISetting %s >> %X", pKey, apSetting->uValue.u);
				break;
			case Setting::kSetting_Float:
				Interface::PrintLine("INISetting %s >> %.2f", pKey, apSetting->uValue.f);
				break;
			case Setting::kSetting_String:
				Interface::PrintLine("INISetting %s >> '%s'", pKey, apSetting->uValue.str);
				break;
			case Setting::kSetting_r:
				Interface::PrintLine("INISetting %s >> R: %d G: %d B: %d", pKey, apSetting->uValue.rgb[3], apSetting->uValue.rgb[2], apSetting->uValue.rgb[1]);
				break;
			case Setting::kSetting_a:
				Interface::PrintLine("INISetting %s >> R: %d G: %d B: %d alpha: %d", pKey, apSetting->uValue.rgb[3], apSetting->uValue.rgb[2], apSetting->uValue.rgb[1], apSetting->uValue.rgb[0]);
				break;
			default:
				Interface::PrintLine("INISetting %s >> UNKNOWN TYPE", pKey);
				break;
		}
	}

	SPEC_NAKED void GetINISettingTypeHook() {
		__asm {
			push	eax
			mov		eax, dword ptr ds : [ebp - 4]
			push	eax
			call	HandleSettingType
			mov		eax, 0x5BEE5D
			jmp		eax
		}
	}

	void Install() {
		// Fix for Get/Set/SaveINISetting not reading renderer INI setting list
		GetINISettingHook<0x5BED66>();
		GetINISettingHook<0x5BEF13>();
		kSaveINIDetour.ReplaceCall(0x5B6C80, SaveINIHook);

		// Extend setting type support in GetIniSetting
		HookUtils::WriteRelJump(0x5BED86, GetINISettingTypeHook);
	}

	STACK_FRAME_OPT_RESET
}
