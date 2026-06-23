#pragma once
#include <unordered_set>
namespace JohnnyPatches {
	extern bool fixFleeing;
	extern bool fixItemStacks;
	extern bool resetVanityCam;
	extern bool fixNPCShootingAngle;
	extern bool noMuzzleFlashCooldown;
	extern bool enableRadioSubtitles;
	extern bool removeMainMenuMusic;
	extern bool fixDeathSounds;
	extern bool patchPainedPlayer;
	extern bool bDisableDeathResponses;
	extern bool bFixJIP;
	extern unsigned int iFPSCapLoadScreen;
	extern float iDeathSoundMAXTimer;
	extern bool bDisableDLLCompatibilityRoutines;
	extern bool bCombatMusicDisabled;

	extern float g_viewmodel_near;

	SPEC_NOINLINE void ReadINI();
	SPEC_NOINLINE void Init();

	SPEC_NOINLINE void Update();

}
// exports
extern "C" {
	bool __cdecl JGSetViewmodelClipDistance(float value);
	float __cdecl JGGetViewmodelClipDistance();
} 