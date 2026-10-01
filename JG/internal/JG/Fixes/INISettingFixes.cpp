#include "INISettingFixes.hpp"
#include "Bethesda/RendererSettingCollection.hpp"
#include "Bethesda/SettingT.hpp"
#include "Bethesda/Script.hpp"
#include "Bethesda/Interface.hpp"

#include "Shared/SafeWrite/SafeWrite.hpp"

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
		const char* pFormatString = reinterpret_cast<const char*>(0x103A440); // INISetting %s >> %i;
		switch (type) {
			case Setting::Type::BOOL:
				Interface::PrintLine(pFormatString, pKey, apSetting->Bool());
				break;
			case Setting::Type::INT:
				Interface::PrintLine(pFormatString, pKey, apSetting->Int());
				break;
			case Setting::Type::UINT:
				Interface::PrintLine("INISetting %s >> %u", pKey, apSetting->UInt());
				break;
			case Setting::Type::FLOAT:
				pFormatString = reinterpret_cast<const char*>(0x103A428); // INISetting %s >> %.2f
				Interface::PrintLine(pFormatString, pKey, apSetting->Float());
				break;
			case Setting::Type::STRING:
				pFormatString = reinterpret_cast<const char*>(0x103A410); // INISetting %s >> '%s'
				Interface::PrintLine(pFormatString, pKey, apSetting->String());
				break;
			case Setting::Type::RGB:
				Interface::PrintLine("INISetting %s >> R: %i G: %i B: %i", pKey, apSetting->uValue.r[3], apSetting->uValue.r[2], apSetting->uValue.r[1]);
				break;
			case Setting::Type::RGBA:
				Interface::PrintLine("INISetting %s >> R: %i G: %i B: %d A: %i", pKey, apSetting->uValue.a[3], apSetting->uValue.a[2], apSetting->uValue.a[1], apSetting->uValue.a[0]);
				break;
			default:
				pFormatString = reinterpret_cast<const char*>(0x103A3F0); // INISetting %s >> UNKNOWN TYPE
				Interface::PrintLine(pFormatString, pKey);
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
