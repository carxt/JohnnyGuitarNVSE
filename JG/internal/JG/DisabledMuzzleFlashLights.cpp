#include "DisabledMuzzleFlashLights.hpp"
#include "GameObjects.h"

namespace DisabledMuzzleFlashLights {

	Mode eDisableMode = Mode::ENABLE;

	HookUtils::CallDetour kDetour;

	void __fastcall DisableMuzzleFlashLightsHook(MuzzleFlash* apMuzzleFlash) {
		if (eDisableMode == Mode::ENABLE
			|| (eDisableMode == Mode::DISABLE_NPCS && apMuzzleFlash->pSourceActor != PlayerCharacter::GetSingleton())
			|| (eDisableMode == Mode::DISABLE_PLAYER && apMuzzleFlash->pSourceActor == PlayerCharacter::GetSingleton())) {
			ThisCall(kDetour, apMuzzleFlash);
		}
	}

	void Install() {
		kDetour.ReplaceCall(0x9BAFED, DisableMuzzleFlashLightsHook);
	}

	void Reset() {
		eDisableMode = Mode::ENABLE; //reset the muzzle hook every time
	}

	Mode SetMode(Mode aeMode) {
		eDisableMode = aeMode;
		return eDisableMode;
	}

}