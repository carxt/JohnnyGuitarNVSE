#include "JohnnyPatches.hpp"

#include "decoding.h"
#include "GameObjects.h"
#include "GameProcess.h"
#include "GameSound.h"
#include "GameUI.h"

#include "AddItemMessages.hpp"
#include "BarterFilter.hpp"
#include "CameraOverlay.hpp"
#include "CameraOverride.hpp"
#include "CustomCameraShake.hpp"
#include "DeathSoundFix.hpp"
#include "DialogueResponseOverride.hpp"
#include "DisabledArrowKeys.hpp"
#include "DisabledLevelUp.hpp"
#include "DisabledMuzzleFlashLights.hpp"
#include "DisabledSaves.hpp"
#include "EditorIDRestoration.hpp"
#include "ExtraMarkerIcons.hpp"
#include "ExtraMiscStats.hpp"
#include "ExtraReputationIcons.hpp"
#include "ExtraUISounds.hpp"
#include "LandRemapping.hpp"
#include "MediaLocationControllerTweaks.hpp"
#include "NPCAccuracy.hpp"
#include "RadioSkipOGGWAVPatch.hpp"
#include "RSMBarberHook.hpp"
#include "WorldToScreen.hpp"
#include "NewNiObjects.hpp"

#include "Bethesda/GameSettingCollection.hpp"

#include <algorithm>

namespace JohnnyPatches {
	bool bFixFleeing = false;
	bool bFixItemStacks = false;
	bool bResetVanityCam = false;
	bool bFixNPCShootingAngle = false;
	bool bNoMuzzleFlashCooldown = false;
	bool bEnableRadioSubtitles = false;
	bool bRemoveMainMenuMusic = false;
	bool bFixDeathSounds = true;
	bool bPatchPainedPlayer = false;
	bool bDisableDeathResponses = false;
	bool bFixJIP = true;
	bool bDisableDLLCompatibilityRoutines = false;
	bool bCombatMusicDisabled = false;
	bool bMultipleAddItemMessages = false;
	bool bFixOggWavRadioPlayback = false;
	int32_t iFPSCapLoadScreen = 0;
	float fViewmodelNearDistance = 0.f;

	HookUtils::CallDetour kPlayerInCombatDetour;
	bool __fastcall FleeFixHook(PlayerCharacter* apPlayer, void*, bool& abUnseen) {
		return ThisCall<bool>(kPlayerInCombatDetour, apPlayer, &abUnseen) && !abUnseen;
	}

	TESObjectREFR* __fastcall DropItemHook(PlayerCharacter* apPlayer, void*, TESForm* apItem, ExtraDataList* apExtraList, uint32_t aiCount, const NiPoint3* apPoint, const NiPoint3* apRotate) {
		if (aiCount > 10000) {
			for (aiCount; aiCount > 10000; aiCount -= 10000) {
				apPlayer->DropObject(apItem, apExtraList, 10000, apPoint, apRotate);
			}
		}
		return apPlayer->DropObject(apItem, apExtraList, aiCount, apPoint, apRotate);
	}

	SPEC_NAKED void PatchPlayerPainHook() {
		_asm {
			mov		ecx, dword ptr[ebp - 0x180]
			cmp		ecx, dword ptr ds : [0x11DEA3C]
			jz		PLAYER

			mov		al, byte ptr ds : [0x119B4E0]
			retn

			PLAYER:
			mov		al, 0
			retn
		}
	}

	SPEC_NAKED void DisableDeathResponsesHook() {
		__asm {
			movzx	eax, byte ptr ss : [ebp - 0x10]
			test	eax, eax
			jz		EXIT

			pop		eax
			add		eax, 0x6F
			push	eax
			mov		al, 1

			EXIT:
			ret
		}
	}

	HookUtils::CallDetour kShouldPlayCombatMusicDetour;
	bool __fastcall CombatMusicHook(void* apManager) {
		if (bCombatMusicDisabled) 
			return false;
		return ThisCall<bool>(kShouldPlayCombatMusicDetour, apManager);
	}


	HookUtils::CallDetour kSetViewFrustumDetour;
	void __fastcall SetViewmodelFrustumHook(NiCamera* apCamera, void*, NiFrustum& arViewFrustum) {
		if (fViewmodelNearDistance > 0.f) {
			NiFrustum kFrustum = arViewFrustum;
			kFrustum.m_fNear = std::max(fViewmodelNearDistance, 0.001f);

			const float fOrgRatio = apCamera->m_fMaxFarNearRatio;
			apCamera->m_fMaxFarNearRatio = kFrustum.m_fFar / kFrustum.m_fNear;
			ThisCall(kSetViewFrustumDetour, apCamera, &kFrustum);
			apCamera->m_fMaxFarNearRatio = fOrgRatio;
		}
		else {
			ThisCall(kSetViewFrustumDetour, apCamera, &arViewFrustum);
		}
	}

	HookUtils::CallDetour kHolotapePlayDetour;
	void __fastcall StopHolotapeSoundHook(BSSoundHandle* apHandle, void*, bool abLoop) {
		if (!bNoHolotapeStopSound)
			ThisCall(kHolotapePlayDetour, apHandle, abLoop);
		bNoHolotapeStopSound = false;
	}

	static float fVanityWheelState;
	void ResetVanityWheel() {
		if (!bResetVanityCam) 
			return;

		if (PlayerCharacter::GetSingleton()) {
			const bool bIsInVanityMode = PlayerCharacter::bIsVanityMode | PlayerCharacter::bIsAutoVanityMode | PlayerCharacter::GetSingleton()->bTemp3rdPerson;
			if (!bIsInVanityMode) {
				float& rVanityWheel = PlayerCharacter::kVanityModePos->y;
				if (GameSettingCollection::fChaseCameraMax->Float() < rVanityWheel)
					rVanityWheel = fVanityWheelState;
				else
					fVanityWheelState = rVanityWheel;
			}
		}
	}

	void Update() {
		ResetVanityWheel();
	}

	void ReadINI() {
		char filename[MAX_PATH];
		GetModuleFileNameA(NULL, filename, MAX_PATH);
		char* lastSlash = strrchr(filename, '\\') + 1;
		uint32_t length = MAX_PATH - (lastSlash - filename);;
		strcpy_s(lastSlash, length, "Data\\nvse\\plugins\\JohnnyGuitar.ini");
		bFixFleeing = GetPrivateProfileInt("MAIN", "bFixFleeing", 1, filename);
		bFixItemStacks = GetPrivateProfileInt("MAIN", "bFixItemStackCount", 1, filename);
		bFixNPCShootingAngle = GetPrivateProfileInt("MAIN", "bFixNPCShootingAngle", 1, filename);
		iFPSCapLoadScreen = GetPrivateProfileInt("MAIN", "iFPSLimitLoadScreen", 0, filename);
		bNoMuzzleFlashCooldown = GetPrivateProfileInt("MAIN", "bNoMuzzleFlashCooldown", 0, filename);
		bResetVanityCam = GetPrivateProfileInt("MAIN", "bReset3rdPersonCamera", 0, filename);
		bEnableRadioSubtitles = GetPrivateProfileInt("MAIN", "bEnableRadioSubtitles", 0, filename);
		bRemoveMainMenuMusic = GetPrivateProfileInt("MAIN", "bRemoveMainMenuMusic", 0, filename);
		bFixDeathSounds = GetPrivateProfileInt("MAIN", "bFixDeathVoicelines", 1, filename);
		bPatchPainedPlayer = GetPrivateProfileInt("MAIN", "bRemovePlayerPainExpression", 0, filename);
		bMultipleAddItemMessages = GetPrivateProfileInt("MAIN", "bMultipleAddItemMessages", 0, filename);
		bFixJIP = GetPrivateProfileInt("MAIN", "bJIPFixes", 1, filename);
		bFixOggWavRadioPlayback = GetPrivateProfileInt("MAIN", "bFixOggWavRadioPlayback", 1, filename);
		DeathSoundFix::iDeathSoundMaxTimer = GetPrivateProfileInt("DeathResponses", "iDeathSoundMAXTimer", 10, filename); //Hidden, don't actually expose it in the INI
		bDisableDLLCompatibilityRoutines = GetPrivateProfileInt("Misc", "bDisableDLLCompatibilityRoutines", 0, filename); //Hidden
	}

	void Init() {
		if (bFixOggWavRadioPlayback)
			RadioSkipOGGWAVPatch::Install();

		if (bFixFleeing) 
			kPlayerInCombatDetour.ReplaceCall(0x8F5FE2, FleeFixHook);

		if (bFixItemStacks)
			HookUtils::ReplaceVirtualCall(0x780D11, DropItemHook, 8);

		if (iFPSCapLoadScreen > 0) {
			int32_t iMSInterval = floor(1000.f / iFPSCapLoadScreen);
			iMSInterval = std::clamp(iMSInterval, 1, 1000);
			HookUtils::SafeWrite32(0x78D4A4, iMSInterval);
		}

		if (bFixNPCShootingAngle) 
			HookUtils::PatchMemoryNop(0x9D13B2, 8);

		if (bNoMuzzleFlashCooldown)	
			HookUtils::PatchMemoryNop(0x9BB6A8, 2);

		if (bEnableRadioSubtitles) 
			HookUtils::SafeWrite8(0x833876, 0x84);

		// fix for death topics getting cut off
		if (bFixDeathSounds) {
			DeathSoundFix::Install();
		}

		if (bPatchPainedPlayer) {
			HookUtils::WriteRelCall(0x936394, PatchPlayerPainHook);
			HookUtils::WriteRelCall(0x936703, PatchPlayerPainHook);
		}

		if (bRemoveMainMenuMusic) 
			HookUtils::SafeWrite16(0x830109, 0x2574);

		if (bDisableDeathResponses) {
			HookUtils::SafeWrite8(0x098414C, 0x90);
			HookUtils::WriteRelCall(0x098414D, DisableDeathResponsesHook);
		}

		if (bMultipleAddItemMessages) {
			AddItemMessages::Install();
		}

		WorldToScreen::Install();

		// ToggleLevelUpMenu
		DisabledLevelUp::Install();

		DisabledMuzzleFlashLights::Install();

		DisabledArrowKeys::Install();

		// SetUIUpdateSound
		ExtraUISounds::Install();

		// DisableCombatMusic
		kShouldPlayCombatMusicDetour.ReplaceCall(0x82FC0B, CombatMusicHook);

		// ToggleDisableSaves
		DisabledSaves::Install();

		ExtraMarkerIcons::Install();

		ExtraReputationIcons::Install();

		ExtraMiscStats::Install();

		// Hairstyle handlers
		RSMBarberHook::Install();

		BarterFilter::Install();

		kSetViewFrustumDetour.ReplaceCall(0x8752F2, SetViewmodelFrustumHook);

		MediaLocationControllerTweaks::Install();

		CameraOverride::Install();

		CameraOverlay::Install();

		LandRemapping::Install();

		kHolotapePlayDetour.ReplaceCall(0x798BB1, StopHolotapeSoundHook);

		CustomCameraShake::Install();

		NPCAccuracy::Install();

		DialogueResponseOverride::Install();

		NewNiObjects::Install();
	}

	void DeferredInit() {
		fVanityWheelState = GameSettingCollection::fChaseCameraMax->Float();
	}

}

// exports
extern "C" {
	bool __cdecl JGSetViewmodelClipDistance(float value) {
		JohnnyPatches::fViewmodelNearDistance = value;
		return true;
	}

	float __cdecl JGGetViewmodelClipDistance() {
		return JohnnyPatches::fViewmodelNearDistance;
	}
}