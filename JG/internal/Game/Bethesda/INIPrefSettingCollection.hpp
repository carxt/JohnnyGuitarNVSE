#pragma once

#include "INISettingCollection.hpp"

class INIPrefSettingCollection : public INISettingCollection {
public:
	struct Audio {
		static constexpr AddressPtr<Setting, 0x11F6E38> fDefaultEffectsVolume;
		static constexpr AddressPtr<Setting, 0x11F6E20> fDefaultFootVolume;
		static constexpr AddressPtr<Setting, 0x11F6E14> fDefaultMasterVolume;
		static constexpr AddressPtr<Setting, 0x11F6E44> fDefaultMusicVolume;
		static constexpr AddressPtr<Setting, 0x11F6E50> fDefaultRadioVolume;
		static constexpr AddressPtr<Setting, 0x11F6E2C> fDefaultVoiceVolume;
	};

	struct Controls {
		static constexpr AddressPtr<Setting, 0x11E0850> bGamePadRumble;
		static constexpr AddressPtr<Setting, 0x11E0A5C> bInvertYValues;
		static constexpr AddressPtr<Setting, 0x11E0A6C> fMouseSensitivity;
		static constexpr AddressPtr<Setting, 0x11E0928> fXenonHorizLookSpeed;
		static constexpr AddressPtr<Setting, 0x11E08B8> fXenonVertLookSpeed;
	};

	struct Display {
		static constexpr AddressPtr<Setting, 0x11C71AC> fGamma;
		static constexpr AddressPtr<Setting, 0x11DF124> iScreenShotIndex;
	};

	struct GamePlay {
		static constexpr AddressPtr<Setting, 0x11D8A38> bCrossHair;
		static constexpr AddressPtr<Setting, 0x11D8934> bDialogueSubtitles;
		static constexpr AddressPtr<Setting, 0x11D8A0C> bDisableDynamicCrosshair;
		static constexpr AddressPtr<Setting, 0x11D8928> bGeneralSubtitles;
		static constexpr AddressPtr<Setting, 0x11D8A20> bSaveOnInteriorExteriorSwitch;
		static constexpr AddressPtr<Setting, 0x11D89F0> bSaveOnRest;
		static constexpr AddressPtr<Setting, 0x11D8980> bSaveOnTravel;
		static constexpr AddressPtr<Setting, 0x11D8974> bSaveOnWait;
		static constexpr AddressPtr<Setting, 0x11E07F0> bShowQuestMarkers;
		static constexpr AddressPtr<Setting, 0x11D898C> bTrueIronSights;
		static constexpr AddressPtr<Setting, 0x11E0940> iDifficulty;
		static constexpr AddressPtr<Setting, 0x11E087C> iKillCamera;
		static constexpr AddressPtr<Setting, 0x11E0B00> uiRedeemedContent;
	};

	struct Interface {
		static constexpr AddressPtr<Setting, 0x11D8C4C> bDisable360Controller;
		static constexpr AddressPtr<Setting, 0x11DB094> bHelpEnabled;
		static constexpr AddressPtr<Setting, 0x11D9774> fHudOpacity;
		static constexpr AddressPtr<Setting, 0x11D8AD4> uHUDColor;
		static constexpr AddressPtr<Setting, 0x11D8AE4> uPipboyColor;
	};
};