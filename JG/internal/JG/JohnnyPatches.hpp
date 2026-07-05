#pragma once
#include <unordered_set>
namespace JohnnyPatches {
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
	extern bool bFixJIP;
	extern int32_t iFPSCapLoadScreen;
	extern bool bDisableDLLCompatibilityRoutines;
	extern bool bCombatMusicDisabled;

	extern float fViewmodelNearDistance;

	SPEC_NOINLINE void ReadINI();
	SPEC_NOINLINE void Init();
	SPEC_NOINLINE void DeferredInit();

	SPEC_NOINLINE void Update();

}
// exports
extern "C" {
	bool __cdecl JGSetViewmodelClipDistance(float value);
	float __cdecl JGGetViewmodelClipDistance();
} 