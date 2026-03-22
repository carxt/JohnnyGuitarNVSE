#include "JohnnyGameSettings.hpp"

namespace JohnnyGameSettings
{
	CustomGameSetting fCombatLocationTargetRadiusMaxBase;
	CustomGameSetting fCombatRangedWeaponRangeBaseMult;
	CustomGameSetting iOverrideDialogueEmotionValues;
	CustomGameSetting iFixAudioMarkerLookupAlgo;
	CustomGameSetting sNewline;

	void InitCombatLocation() { //Thanks lStewieAl
		CombatLocationHook<0x09A089F>();
		CombatLocationHook<0x09A0A0C>();
	}

	void InitCombatRangedWeaponRange() {
		CombatRangedWeaponRangeHook<0x09A91C1>();
	}

	void InitOverrideDialogueEmotionValues() {
		OverrideEmotionValuesHook<0x0617D59>();
	}

	void Init() {
		fCombatLocationTargetRadiusMaxBase.Initialize("fCombatLocationTargetRadiusMaxBase", 10.0f);
		fCombatRangedWeaponRangeBaseMult.Initialize("fCombatRangedWeaponRangeBaseMult", 1.0f);
		iOverrideDialogueEmotionValues.Initialize("iOverrideDialogueEmotionValues", 0);
		iFixAudioMarkerLookupAlgo.Initialize("iFixAudioMarkerLookupAlgo", 1);
		sNewline.Initialize("sNewline", "\n");
		InitCombatLocation();
		InitCombatRangedWeaponRange();
		InitOverrideDialogueEmotionValues();
	}

}