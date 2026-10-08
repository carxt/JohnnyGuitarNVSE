#include "DisabledMuzzleFlashLights.hpp"
#include "Bethesda/MuzzleFlash.hpp"
#include "Bethesda/PlayerCharacter.hpp"
#include "Bethesda/ProcessLists.hpp"

#include "Shared/SafeWrite/SafeWrite.hpp"

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

	SPEC_NOINLINE void __fastcall ToggleMuzzleFlashLight(MuzzleFlash* apFlash, bool abEnable) {
		if (abEnable)
			apFlash->AttachLight();
		else
			apFlash->DetachLight();
	}

	SPEC_NOINLINE void __fastcall ToggleLightForActors(bool abEnable) {
		ProcessLists* pLists = ProcessLists::GetSingleton();
		const ProcessArray* pArray = pLists->GetProcessArray();
		pLists->kUpdateLock.Lock();
		const uint32_t uiHead = pArray->GetHead(PROCESS_LEVEL::HIGH);
		const uint32_t uiTail = pArray->GetTail(PROCESS_LEVEL::HIGH);
		for (uint32_t i = uiHead; i < uiTail; ++i) {
			MobileObject* pObject = pArray->GetItem(i);
			if (pObject && pObject->IsActor() && pObject != PlayerCharacter::GetSingleton()) {
				BaseProcess* pAIProcess = pObject->GetCurrentAIProcess();
				MuzzleFlash* pFlash = pAIProcess->GetCurrentMuzzleFlash();
				if (pFlash)
					ToggleMuzzleFlashLight(pFlash, abEnable);
			}
		}
		pLists->kUpdateLock.Unlock();
	}

	SPEC_NOINLINE void __fastcall ToggleLightForPlayer(bool abEnable) {
		BaseProcess* pAIProcess = PlayerCharacter::GetSingleton()->GetCurrentAIProcess();
		MuzzleFlash* pFlash = pAIProcess->GetCurrentMuzzleFlash();
		if (pFlash)
			ToggleMuzzleFlashLight(pFlash, abEnable);
	}

	Mode SetMode(Mode aeMode) {
		eDisableMode = aeMode;
		switch (aeMode) {
			case Mode::DISABLE_PLAYER:
				ToggleLightForActors(true);
				ToggleLightForPlayer(false);
				break;
			case Mode::DISABLE_NPCS:
				ToggleLightForActors(false);
				ToggleLightForPlayer(true);
				break;
			default:
				ToggleLightForActors(true);
				ToggleLightForPlayer(true);
				break;
		}

		return eDisableMode;
	}

}