#include "JohnnyPatches.hpp"
namespace JohnnyPatches {
	bool fixFleeing = false;
	bool fixItemStacks = false;
	bool resetVanityCam = false;
	bool fixNPCShootingAngle = false;
	bool noMuzzleFlashCooldown = false;
	bool enableRadioSubtitles = false;
	bool removeMainMenuMusic = false;
	bool fixDeathSounds = true;
	bool patchPainedPlayer = false;
	bool bDisableDeathResponses = false;
	bool bFixJIP = true;
	bool bDisableDLLCompatibilityRoutines = false;
	bool isShowLevelUp = true;
	bool bArrowKeysDisabled = false;
	bool bCombatMusicDisabled = false;

	unsigned int iFPSCapLoadScreen = 0;
	float iDeathSoundMAXTimer = 10;
	uint32_t disableMuzzleLights = -1;
}