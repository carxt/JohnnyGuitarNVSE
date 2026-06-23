#include "DisabledMuzzleFlashLights.hpp"
#include "GameObjects.h"

namespace DisabledMuzzleFlashLights {
	uint32_t disableMuzzleLights = -1;

	void __fastcall DisableMuzzleFlashLightsHook(ProjectileData* a1) {
		if (*&a1->muzzleFlash && a1->projectile->lightMuzzleFlash) {
			if (!disableMuzzleLights || (disableMuzzleLights == 2 && a1->sourceActor != (Actor*)PlayerCharacter::GetSingleton()) || (disableMuzzleLights == 3 && a1->sourceActor == (Actor*)PlayerCharacter::GetSingleton())) {
				NiNode* niNode = ThisCall<NiNode*>(0x50D810, a1->projectile->lightMuzzleFlash, 0, *&a1->muzzleFlash, 1);
				ThisCall(0x66B0D0, &a1->flashLight, niNode);
			}
		}
	}

	void Install() {
		// DisableMuzzleFlashLights
		HookUtils::WriteRelCall(0x9BAFED, (uint32_t)DisableMuzzleFlashLightsHook);
	}
	void Reset() {
		disableMuzzleLights = 0; //reset the muzzle hook every time
	}
	uint32_t SetMode(uint32_t mode)
	{
		disableMuzzleLights = mode;
		return disableMuzzleLights;
	}
}