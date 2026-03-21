#include "JohnnyGameSettings.hpp"

namespace JohnnyGameSettings
{
	CustomGameSetting fCombatLocationTargetRadiusMaxBase;
	CustomGameSetting fCombatRangedWeaponRangeBaseMult;
	CustomGameSetting iOverrideDialogueEmotionValues;
	CustomGameSetting iFixAudioMarkerLookupAlgo;
	CustomGameSetting sNewline;


	void Init() {
		fCombatLocationTargetRadiusMaxBase.Initialize("fCombatLocationTargetRadiusMaxBase", 10.0f);
		fCombatRangedWeaponRangeBaseMult.Initialize("fCombatRangedWeaponRangeBaseMult", 1.0f);
		iOverrideDialogueEmotionValues.Initialize("iOverrideDialogueEmotionValues", 0);
		iFixAudioMarkerLookupAlgo.Initialize("iFixAudioMarkerLookupAlgo", 1);
		sNewline.Initialize("sNewline", "\n");
	}

}