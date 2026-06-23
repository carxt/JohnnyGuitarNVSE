#pragma once
#include <GameSettings.h>

namespace JohnnyGameSettings {

	extern CustomGameSetting fCombatLocationTargetRadiusMaxBase;
	extern CustomGameSetting fCombatRangedWeaponRangeBaseMult;
	extern CustomGameSetting iOverrideDialogueEmotionValues;
	extern CustomGameSetting iFixAudioMarkerLookupAlgo;
	extern CustomGameSetting sNewline;

	SPEC_NOINLINE void Init();
	
};