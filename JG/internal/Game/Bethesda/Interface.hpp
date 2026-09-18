#pragma once

class TESObjectREFR;
class FORenderedMenu;
class FOPipboyManager;
class FOVATSEffectManager;
class TESModel;
class NiAVObject;

class Interface {
public:
	using MessageBoxCallback = void(__cdecl*)();

	struct _Emotion {
		enum Emotion : uint32_t {
			NEUTRAL	= 0,
			HAPPY	= 1,
			SAD		= 2,
			PAIN	= 3,
		};
	};
	using Emotion = _Emotion::Emotion;

	struct _Menus {
		enum Menus {
			NoMenu					= 0,
			MainFour				= 1,
			OtherRoot				= 2,
			Console					= 3,

			Message					= 1001,
			Inventory				= 1002,
			Stats					= 1003,
			HUDMainMenu				= 1004,
			Loading					= 1007,
			Container				= 1008,
			Dialog					= 1009,
			SleepWait				= 1012,
			Pause					= 1013,
			LockPick				= 1014,
			Quantity				= 1016,
			AudioMenu				= 1017,
			VideoMenu				= 1018,
			GamePlayMenu			= 1020,
			PipboyData				= 1023,
			BookMenu				= 1026,
			LevelUp					= 1027,
			PipboyRepair			= 1035,
			RaceMenu				= 1036,
			SurgeryMenu				= 1036,
			BarberMenu				= 1036,
			Credits					= 1047,
			CharGen					= 1048,
			TextEdit				= 1051,
			Barter					= 1053,
			Surgery					= 1054,
			Hacking					= 1055,
			VATS					= 1056,
			Computers				= 1057,
			VendorRepair			= 1058,
			Tutorial				= 1059,
			SPECIALBook				= 1060,
			ItemModMenu				= 1061,
			LoveTester				= 1074,
			CompanionWheel			= 1075,
			MedicalQuestionnaire	= 1076,
			Recipe					= 1077,
			SlotMachine				= 1080,
			BlackJack				= 1081,
			Roulette				= 1082,
			Caravan					= 1083,
			Traits					= 1084,
		};
	};
	using Menus = _Menus::Menus;

	static constexpr AddressPtr<bool, 0x11D8907> bIsLoadingNewGame;

	static bool IsInMenuMode();
	
	static bool IsPipBoyMenuOpen();
	
	static bool IsPipBoyOpening();
	
	static bool IsPipBoyOpened();
	
	static bool IsInPipBoy();
	
	static bool IsInRenderedMenu();

	static bool IsInDialog();


	static bool IsMenuIDVisible(Menus aeMenu, uint32_t auiFlags);
	
	static bool IsDebugTextVisible();
	
	static bool IsConsoleVisible();

	static bool IsLoadingMenuVisible();


	static bool IsTopMenuID(Menus aeMenu);

	static Menus GetTopMenuID();

	
	static TESObjectREFR* GetActivateTarget();
	
	static TESObjectREFR* GetDialogueTarget();

	
	static FORenderedMenu* GetCurrentRenderedMenu();
	
	static FOPipboyManager* GetPipboy();
	
	static FOVATSEffectManager* GetVATSEffect();


	static void InitGunScope(TESModel* apModel);

	static void SetGunScopeVisible(bool abVisible);

	static void ClearGunScope();


	static NiAVObject* CopyOrDeepCopyNode(NiAVObject* apObject);


	static void CreateRaceSexMenu(uint32_t aeType);


	static void PrintLine(const char* apText, auto...args);
	
	static bool ShowMessage(const char* apText, Emotion aeEmotion, const char* apImagePath, const char* apSoundName = nullptr, float afTime = 2.f, bool abInstant = false);
	
	static bool CreateMessageMenu(const char* apText, const char* apIcon, const char* apTitle, MessageBoxCallback apCallback, int8_t acFirstButtonResult = 1, int32_t aiWarningContext = 0, float afAlpha = 0.f, float afMenuWidth = 0.f, auto...args);
	
	static bool CreateMessageMenuSound(const char* apText, const char* apIcon, const char* apTitle, const char* apSound, MessageBoxCallback apCallback, int8_t acFirstButtonResult = 1, int32_t aiWarningContext = 0, float afAlpha = 0.f, float afMenuWidth = 0.f, auto...args);
};

#include "Interface.inl"