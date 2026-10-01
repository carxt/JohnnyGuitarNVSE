#pragma once

namespace JohnnyPatches {

	extern bool bFixJIP;
#ifdef GAME
	extern bool bFixFleeing;
	extern bool bFixItemStacks;
	extern bool bResetVanityCam;
	extern bool bFixNPCShootingAngle;
	extern bool bNoMuzzleFlashCooldown;
	extern bool bEnableRadioSubtitles;
	extern bool bRemoveMainMenuMusic;
	extern bool bFixDeathSounds;
	extern bool bPatchPainedPlayer;
	extern bool bDisableDeathResponses;
	extern int32_t iFPSCapLoadScreen;
	extern bool bDisableDLLCompatibilityRoutines;
	extern bool bCombatMusicDisabled;
	extern float fViewmodelNearDistance;
#endif

	SPEC_NOINLINE void ReadINI();
	SPEC_NOINLINE void Init();
	SPEC_NOINLINE void PostLoadInit();
	SPEC_NOINLINE void DeferredInit();

	SPEC_NOINLINE void Update();

}