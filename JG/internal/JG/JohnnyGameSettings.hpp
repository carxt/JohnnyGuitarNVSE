#pragma once
#include <GameSettings.h>

namespace JohnnyGameSettings {
	constexpr uintptr_t func_AddGameSetting_Float = 0x040E0B0;
	constexpr uintptr_t func_AddGameSetting_IntOrStaticStr = 0x40C150;

	extern CustomGameSetting fCombatLocationTargetRadiusMaxBase;
	extern CustomGameSetting fCombatRangedWeaponRangeBaseMult;
	extern CustomGameSetting iOverrideDialogueEmotionValues;
	extern CustomGameSetting iFixAudioMarkerLookupAlgo;
	extern CustomGameSetting sNewline;

	void Init();
	
}