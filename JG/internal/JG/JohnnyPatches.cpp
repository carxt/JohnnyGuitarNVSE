#include "JohnnyPatches.hpp"
#include "GameObjects.h"
#include "GameProcess.h"
#include "EditorIDRestoration.hpp"
#include "misc/WorldToScreen.h"
#include "GameSound.h"
#include <decoding.h>
#include "ExtraUISounds.hpp"
#include "ExtraReputationIcons.hpp"
#include "ExtraMiscStats.hpp"
#include "RSMBarberHook.hpp"
#include "BarterFilter.hpp"
#include <GameUI.h>
#include "MediaLocationControllerOverride.hpp"
#include "CameraOverride.hpp"
#include "DisabledSaves.hpp"
#include "DisabledLevelUp.hpp"
#include "DisabledMuzzleFlashLights.hpp"
#include "DisabledArrowKeys.hpp"
#include "AddItemMessages.hpp"
#include "ExtraMarkerIcons.hpp"
#include "RadioSkipOGGWAVPatch.hpp"

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
	bool bCombatMusicDisabled = false;
	bool bMultipleAddItemMessages = false;
	bool bFixOggWavRadioPlayback = false;

	unsigned int iFPSCapLoadScreen = 0;
	float iDeathSoundMAXTimer = 10;
	float g_viewmodel_near = 0.f;


	bool(__thiscall* GetPlayerInCombat)(Actor*, bool& IsNotDetected) = (bool(__thiscall*)(Actor*, bool&)) 0x0953C50;

	bool __fastcall FleeFixHook(PlayerCharacter* Player, void* unused, bool& IsHidden) {
		return (GetPlayerInCombat(Player, IsHidden) && !IsHidden);
	}

	void __fastcall DropItemHook(PlayerCharacter* a1, void* edx, TESForm* a2, BaseExtraList* a3, uint32_t itemCount, NiPoint3* a5, void* a6) {
		if (itemCount > 10000) {
			for (itemCount; itemCount > 10000; itemCount -= 10000) {
				ThisCall(0x954610, a1, a2, a3, 10000, a5, a6);
			}
		}
		ThisCall(0x954610, a1, a2, a3, itemCount, a5, a6);
	}


	float __fastcall FixDeathSoundsTopic(HighProcess* thisObj, Actor* actor) { //Simpler fix, though we run the risk of overassumptions. 14 seconds should be more than enough though tbh.
		//all the checks can be skipped because they were done above already
		if (actor->GetDead()) {
			if (DialoguePackage* pPackage = (DialoguePackage*)thisObj->GetCurrentPackage()) {
				if ((actor != pPackage->subject) && (actor == pPackage->speaker)) { //check for subject because in some cases, subject == target
					return -1.0f;
				}
			}
		}
		return thisObj->dyingTimer + iDeathSoundMAXTimer;
	}
	float __fastcall FixDeathSounds(HighProcess* thisObj, Actor* actor) { //Simpler fix, though we run the risk of overassumptions. 14 seconds should be more than enough though tbh.
		return thisObj->dyingTimer + iDeathSoundMAXTimer;
	}


	float __fastcall FixDeathSoundsAlt(HighProcess* thisObj, Actor* actor) { //Alternate complex, confusing, potentially buggy fix.
		constexpr float dyingTimerMin = FLT_EPSILON * 10; //Establish low tolerance, this should be ideal. Unless someone sets fDyingTimer to 0 or something, but that's their problem.
		float dyingTimer = thisObj->dyingTimer;
		bool keepTalkingDe = false;
		keepTalkingDe = (ThisCall<bool>(0x8A67F0, actor)) || !(actor->unk80 & 1);
		if (keepTalkingDe) {
			if (dyingTimer <= dyingTimerMin) { dyingTimer = dyingTimerMin; }
		}
		return dyingTimer;
	}
	__declspec (naked) void FixDeathSoundsHook() {
		__asm {
			mov edx, dword ptr[ebp + 8]
			jmp FixDeathSoundsTopic
		}
	}

	__declspec (naked) void PatchPlayerPainHook() {
		_asm {
			mov ecx, dword ptr[ebp - 0x180]
			cmp ecx, dword ptr ds : [0x11DEA3C]
			jz PLAYER
			mov al, byte ptr ds : [0x119B4E0]
			retn
			PLAYER :
			mov al, 0
				retn
		}
	}

	__declspec (naked) void DisableDeathResponsesHook() {
		__asm {
			movzx eax, byte ptr ss : [ebp - 0x10]
			test eax, eax
			jz retExit
			pop eax
			add eax, 0x6F
			push eax
			mov al, 1
			retExit:
			ret

		}
	}

	void __stdcall CopyNiCamera(NiCameraAlt* MemoryAddressToCopy, float fov) {
		SceneGraph* sing_SceneGraph = *(SceneGraph**)0x11DEB7C;
		PlayerCharacter* g_ThePlayer = *(PlayerCharacter**)0x11DEA3C;
		if (!sing_SceneGraph || !g_ThePlayer) return;
		if ((NiCamera*)MemoryAddressToCopy != sing_SceneGraph->camera || fabs(fov - g_ThePlayer->worldFOV) > 0.0000099999997) return;
		memcpy(JGGameCamera.CamPos, &(((NiAVObject*)MemoryAddressToCopy)->m_local.rotate), sizeof(JGCameraPosition));
		memcpy(JGGameCamera.WorldMatrx, &(MemoryAddressToCopy->m_aafWorldToCam[0][0]), sizeof(JGWorldToScreenMatrix));
	}

	__declspec(naked) void NiCameraGetAltHook() {
		__asm
		{
			push dword ptr ss : [ebp + 8]
			push dword ptr ss : [ebp - 8]
			call CopyNiCamera
			leave
			retn 0x10
		}
	}

	bool __fastcall CombatMusicHook(uint32_t* a1) {
		if (bCombatMusicDisabled) return false;
		return ThisCall<bool>(0x992D90, a1);
	}



	void __fastcall SetViewmodelFrustumHook(NiCameraAlt* camera, void*, NiFrustum* frustum) {
		float nearDistance = frustum->n;
		float ratio = camera->maxFarNearRatio;
		if (g_viewmodel_near > 0.f) {
			nearDistance = std::max(g_viewmodel_near, 0.001f);
			ratio = frustum->f / nearDistance;
		}

		camera->frustum.n = nearDistance;
		float fMinNear = frustum->f / ratio;
		if (fMinNear > camera->frustum.n)
			camera->frustum.n = fMinNear;
		if (camera->minNearPlaneDist > camera->frustum.n)
			camera->frustum.n = camera->minNearPlaneDist;
		camera->frustum.l = frustum->l;
		camera->frustum.r = frustum->r;
		camera->frustum.t = frustum->t;
		camera->frustum.b = frustum->b;
		camera->frustum.f = frustum->f;
		camera->frustum.o = frustum->o;
	}

	void __fastcall StopHolotapeSoundHook(BSSoundHandle* handle, void* edx, bool a2)
	{
		if (!noHolotapeStopSound)
		{
			ThisCall(0xAD8830, handle, a2);
		}
		noHolotapeStopSound = false;
	}

	void ResetVanityWheel() {
		if (!resetVanityCam) return;
		if (PlayerCharacter::GetSingleton()) {
			bool bIsInVanityMode = *reinterpret_cast<uint16_t*>(0x11E07B8) || PlayerCharacter::GetSingleton()->byte64D; //64d = autovanity mode.
			if (!bIsInVanityMode) {
				float* VanityWheel = (float*)0x11E0B5C;
				float* MaxChaseCam = (ThisCall<float*>((uintptr_t)0x0403E20, (void*)0x11CD568));
				static float f_VanityWheelcState = *MaxChaseCam;

				if (*MaxChaseCam < *VanityWheel) {
					*VanityWheel = f_VanityWheelcState;
				}
				else {
					f_VanityWheelcState = *VanityWheel;
				}
			}
		}
	}

	__declspec (noinline) void HandleDLLInterop() {
		if (!bDisableDLLCompatibilityRoutines) return;
		if (GetModuleHandle("jip_nvse.dll") != NULL) { //JIP is on.
			uint8_t* fnPtr = (uint8_t*)GetRelJumpAddr(0x0524014);
			while ((fnPtr[0] != 0xCC) && fnPtr[1] != 0xCC) {
				if ((fnPtr[0] == 0x75) && (fnPtr[2] == 0x6A) && (fnPtr[3] == 0x2) && (fnPtr[9] == 0xFF) && (fnPtr[10] == 0xD0)) {
					fnPtr += 4;
					if ((*(uint32_t*)(fnPtr) == 0x8B0DD0B8) && fnPtr[4] == 0) {
						//found
						uintptr_t dest = GetRelJumpAddr(0x0524019);
						SafeWrite32((uintptr_t)(fnPtr + 1), dest);
					}
				}
				fnPtr++;
			}
		}
	}

	void ReadINI() {
		char filename[MAX_PATH];
		GetModuleFileNameA(NULL, filename, MAX_PATH);
		char* lastSlash = strrchr(filename, '\\') + 1;
		uint32_t length = MAX_PATH - (lastSlash - filename);;
		strcpy_s(lastSlash, length, "Data\\nvse\\plugins\\JohnnyGuitar.ini");
		fixFleeing = GetPrivateProfileInt("MAIN", "bFixFleeing", 1, filename);
		fixItemStacks = GetPrivateProfileInt("MAIN", "bFixItemStackCount", 1, filename);
		fixNPCShootingAngle = GetPrivateProfileInt("MAIN", "bFixNPCShootingAngle", 1, filename);
		iFPSCapLoadScreen = GetPrivateProfileInt("MAIN", "iFPSLimitLoadScreen", 0, filename);
		noMuzzleFlashCooldown = GetPrivateProfileInt("MAIN", "bNoMuzzleFlashCooldown", 0, filename);
		resetVanityCam = GetPrivateProfileInt("MAIN", "bReset3rdPersonCamera", 0, filename);
		enableRadioSubtitles = GetPrivateProfileInt("MAIN", "bEnableRadioSubtitles", 0, filename);
		removeMainMenuMusic = GetPrivateProfileInt("MAIN", "bRemoveMainMenuMusic", 0, filename);
		fixDeathSounds = GetPrivateProfileInt("MAIN", "bFixDeathVoicelines", 1, filename);
		patchPainedPlayer = GetPrivateProfileInt("MAIN", "bRemovePlayerPainExpression", 0, filename);
		bMultipleAddItemMessages = GetPrivateProfileInt("MAIN", "bMultipleAddItemMessages", 0, filename);
		bFixJIP = GetPrivateProfileInt("MAIN", "bJIPFixes", 1, filename);
		bFixOggWavRadioPlayback = GetPrivateProfileInt("MAIN", "bFixOggWavRadioPlayback", 1, filename);
		iDeathSoundMAXTimer = GetPrivateProfileInt("DeathResponses", "iDeathSoundMAXTimer", 10, filename); //Hidden, don't actually expose it in the INI
		bDisableDLLCompatibilityRoutines = GetPrivateProfileInt("Misc", "bDisableDLLCompatibilityRoutines", 0, filename); //Hidden
	}

	void Install() {

		if (bFixOggWavRadioPlayback) {
			RadioSkipOGGWAVPatch::Install();
		}
		// for bFixFleeing
		if (fixFleeing) WriteRelCall(0x8F5FE2, (uint32_t)FleeFixHook);

		// for bFixItemStackCount
		if (fixItemStacks) {
			WriteRelCall(0x780D11, (uint32_t)DropItemHook);
			SafeWriteBuf(0x780D11 + 5, "\x90\x90\x90", 3);
		}

		// for b60FPSDuringLoading
		if (iFPSCapLoadScreen > 0) {
			unsigned int fpsLoadScreenPatch = 1;
			fpsLoadScreenPatch = floor(1000.0f / float(iFPSCapLoadScreen));
			if (fpsLoadScreenPatch <= 0) { fpsLoadScreenPatch = 1; }
			if (fpsLoadScreenPatch >= 1000) { fpsLoadScreenPatch = 1000; }

			SafeWrite32(0x78D4A4, fpsLoadScreenPatch);
		}
		// for bFixNPCShootingAngle
		if (fixNPCShootingAngle) PatchMemoryNop(0x9D13B2, 8);

		// for bNoMuzzleFlashCooldown
		if (noMuzzleFlashCooldown)	SafeWriteBuf(0x9BB6A8, "\x90\x90", 2);

		// for bEnableRadioSubtitles
		if (enableRadioSubtitles) SafeWrite8(0x833876, 0x84);

		// fix for death topics getting cut off
		if (fixDeathSounds) {
			SafeWrite16(0x8EC5C6, 0xBA90);
			SafeWrite32(0x8EC5C8, (uintptr_t)FixDeathSoundsHook);
		}
		if (patchPainedPlayer) {
			WriteRelCall(0x936394, (uintptr_t)PatchPlayerPainHook);
			WriteRelCall(0x936703, (uintptr_t)PatchPlayerPainHook);
		}
		// for bRemoveMainMenuMusic
		if (removeMainMenuMusic) SafeWrite16(0x830109, 0x2574);

		if (bDisableDeathResponses) {
			SafeWrite8(0x098414C, 0x90);
			WriteRelCall(0x098414D, (uintptr_t)DisableDeathResponsesHook);
		}

		if (bMultipleAddItemMessages) {
			AddItemMessages::Install();
		}

		// WorldToScreen
		WriteRelJump(0xC5244A, (uint32_t)NiCameraGetAltHook);

		// ToggleLevelUpMenu
		DisabledLevelUp::Install();

		DisabledMuzzleFlashLights::Install();

		DisabledArrowKeys::Install();

		// SetUIUpdateSound
		ExtraUISounds::Install();

		// DisableCombatMusic
		WriteRelCall(0x82FC0B, (uint32_t)CombatMusicHook);

		// ToggleDisableSaves
		DisabledSaves::Install();

		ExtraMarkerIcons::Install();

		ExtraReputationIcons::Install();

		ExtraMiscStats::Install();

		//Hairstyle handlers
		RSMBarberHook::Install();
		BarterFilter::Install();

		WriteRelCall(0x8752F2, uint32_t(SetViewmodelFrustumHook));

		MediaLocationControllerOverride::Install();

		CameraOverride::Install();

		WriteRelCall(0x798BB1, (uint32_t)StopHolotapeSoundHook);



	}

}

// exports
extern "C" {
	bool __cdecl JGSetViewmodelClipDistance(float value) {
		JohnnyPatches::g_viewmodel_near = value;
		return true;
	}

	float __cdecl JGGetViewmodelClipDistance() {
		return JohnnyPatches::g_viewmodel_near;
	}
}