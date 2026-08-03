#include "DisabledMuzzleFlashLights.hpp"
#include "Bethesda/MuzzleFlash.hpp"
#include "GameObjects.h"

namespace DisabledMuzzleFlashLights {

	Mode eDisableMode = Mode::ENABLE;

	HookUtils::CallDetour kDetour;

	void __fastcall CreateMuzzleFlashLightsHook(MuzzleFlash* apMuzzleFlash) {
		if (eDisableMode == Mode::ENABLE
			|| (eDisableMode == Mode::DISABLE_NPCS && apMuzzleFlash->GetParentRef() == PlayerCharacter::GetSingleton())
			|| (eDisableMode == Mode::DISABLE_PLAYER && apMuzzleFlash->GetParentRef() != PlayerCharacter::GetSingleton())) {

			ThisCall(kDetour, apMuzzleFlash);
		}
	}

	void Install() {
		kDetour.ReplaceCall(0x9BAFED, CreateMuzzleFlashLightsHook);
	}

	void Reset() {
		eDisableMode = Mode::ENABLE; //reset the muzzle hook every time
	}

	Mode SetMode(Mode aeMode) {
		eDisableMode = aeMode;
		return eDisableMode;
	}

}