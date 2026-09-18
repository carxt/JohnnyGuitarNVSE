#include "JohnnyFixes.hpp"

#include "GameForms.h"
#include "GameProcess.h"
#include "GameAPI.h"
#ifdef GAME
#include "GameUI.h"
#include "Bethesda/BSShaderManager.hpp"
#include "Bethesda/DialoguePackage.hpp"
#include "Bethesda/ItemChange.hpp"

#include "Fixes/AmmoEffectListNullChecks.hpp"
#include "Fixes/AudioMonoLookupOverflowFix.hpp"
#include "Fixes/BipedAnimFixes.hpp"
#include "Fixes/CreditsMenuNullChecks.hpp"
#include "Fixes/DestructionFixes.hpp"
#include "Fixes/DisintegrationStatFix.hpp"
#include "Fixes/INISettingFixes.hpp"
#include "Fixes/NoHeadlessTalkingFix.hpp"
#include "Fixes/QuestObjectiveDisplayFix.hpp"
#include "Fixes/SkyUpdateFixes.hpp"
#include "Fixes/TESEffectShaderFixes.hpp"
#include "EditorIDRestoration.hpp"
#endif
#include "Fixes/FileFixes.hpp"

namespace JohnnyFixes {
#ifdef GAME
	SPEC_NAKED void InventoryAmmoHook() {
		static constexpr uint32_t uiReturnAddr = 0x7080A8;
		__asm {
			mov		ecx, dword ptr[ebp - 0x2D4]
			call	TESObjectWEAP::GetAmmoInInventory
			mov		dword ptr[ebp - 0x2C8], eax
			jmp		uiReturnAddr
		}
	}

	HookUtils::CallDetour kDestroyContainerMenuDetour;
	STACK_FRAME_OPT_ENABLE
	void __fastcall OnCloseContainerHook(ContainerMenu* apMenu) {
		TESObjectREFR* pRef = apMenu->containerRef;
		if (pRef && pRef->IsActor())
			static_cast<Actor*>(pRef)->bSpeakingDone = true;
		ThisCall(kDestroyContainerMenuDetour, apMenu);
	}
	STACK_FRAME_OPT_RESET

	SPEC_NAKED void NPCIncrementingChallengesHook() {
		static constexpr uint32_t uiReturnAddr = 0x88D0D8;
		static constexpr uint32_t uiNoIncrementAddr = 0x88D100;
		__asm {
			mov		eax, [ebp - 0x80]
			cmp		eax, dword ptr ds : [0x11DEA3C]
			jz		INCREMENT

			jmp		uiNoIncrementAddr

			INCREMENT:
			push	0
			push	0
			push	0
			push	0
			jmp		uiReturnAddr
		}
	}

	HookUtils::CallDetour kGetFileChunkDataDetour;
	STACK_FRAME_OPT_ENABLE
	void __fastcall TESRegionDataSoundIncidentalIDHook(TESFile* apFile, void* edx, FormID* apFormID) {
		ThisCall(kGetFileChunkDataDetour, apFile, apFormID);
		if (*apFormID)
			CdeclCall(0x485D50, apFormID, apFile);
	}
	STACK_FRAME_OPT_RESET

	SPEC_NAKED void StimpakHotkeyHook() {
		__asm {
			xor		eax, eax
			test	ecx, ecx
			jz		EXIT
			mov		eax, dword ptr ds : [ecx + 0x8]
			EXIT:
			ret
		}
	}

	SPEC_NAKED void SimpleDecalHook() {
		static constexpr uint32_t uiReturnAddr = 0x68D64B;
		static constexpr uint32_t uiContinueAddr = 0x68D30C;
		__asm {
			test	eax, eax
			jz EXIT
			mov		dword ptr[ebp - 0x128], eax
			mov		dword ptr[ebp - 0x130], 0
			jmp		uiContinueAddr
			EXIT:
			jmp		uiReturnAddr
		}
	}

	SPEC_NAKED void AnimDataNullCheck() {
		__asm {
			push	0x490BD8
			mov		eax, dword ptr[ebp - 0xA4]
			test	eax, eax
			jz		EXIT
			push	dword ptr[ebp - 0xAC]
			mov		ecx, eax
			mov		eax, dword ptr[eax]
			mov		eax, dword ptr[eax + 0x9C]
			call	eax
			EXIT:
			ret
		}
	}

	HookUtils::CallDetour kRemoveSequenceDetour;
	STACK_FRAME_OPT_ENABLE
	void __fastcall RemoveSequenceNullCheck(NiControllerManager* apManager, void*, NiControllerSequence* apSequence, NiPointer<NiControllerSequence>& arResult) {
		if (apManager)
			ThisCall(kRemoveSequenceDetour, apManager, apSequence, &arResult);
	}
	STACK_FRAME_OPT_RESET

	bool __cdecl IsCurrentFurnitureRefHook(TESObjectREFR* apRef, void* apComparedRef, void*, double& arResult) {
		arResult = 0;
		Actor* pActor = nullptr;

		if (apRef && apRef->IsActor()) {
			pActor = static_cast<Actor*>(apRef);
		}

		// Game does not null check the base process
		if (pActor && pActor->baseProcess && pActor->baseProcess->GetCurrentFurnitureRef() == apComparedRef) {
			arResult = 1;
		}

		if (Script::GetConsoleOuput()) {
			// Reuse the original string, no need to duplicate *all* data
			Interface::PrintLine(((const char*)0x10350A8), arResult);
		}

		return true;
	}

	HookUtils::CallDetour kSetCellImageSpaceDetour;
	STACK_FRAME_OPT_ENABLE
	void __fastcall SetCellImageSpaceHook(TESObjectCELL* apCell, void*, TESImageSpace* apImageSpace) {
		ThisCall(kSetCellImageSpaceDetour, apCell, apImageSpace);
		const PlayerCharacter* pPlayer = PlayerCharacter::GetSingleton();
		if (apImageSpace && pPlayer->parentCell && pPlayer->parentCell == apCell)
			BSShaderManager::SetImageSpaceParameters(&apImageSpace->kData);
	}
	STACK_FRAME_OPT_RESET

	void ClearPlayerFurniture() {
		BaseProcess* pAIProcess = PlayerCharacter::GetSingleton()->baseProcess;
		if (pAIProcess)
			pAIProcess->SetFurnitureRef(PlayerCharacter::GetSingleton(), 0, nullptr, 0x7F);
	}
#endif

	void Init() {
#ifdef GAME
		// for Runtime EDIDs
		EDIDRestoration::InitHooks();

		// use available ammo in inventory instead of NULL when default ammo isn't present
		HookUtils::WriteRelJump(0x70809E, InventoryAmmoHook);

		// fix ammo effects list being checked for non-TESAmmo's when the Rock-It-Launcher is equipped
		AmmoEffectListNullChecks::Install();

		// fix for companions not saying the next topic after opening ContainerMenu through dialog
		kDestroyContainerMenuDetour.ReplaceCall(0x75B2FB, OnCloseContainerHook);

		// Fix for animations not working in dialog topics with sound
		HookUtils::PatchMemoryNop(0x8A56C4, 4);
		HookUtils::PatchMemoryNop(0x8A56C8, 4);

		// fix Disintegrations stat not incrementing properly
		DisintegrationStatFix::Install();

		// fix NPCs incrementing player challenges
		HookUtils::WriteRelJump(0x88D0D0, NPCIncrementingChallengesHook);

		// use correct weapon skill req penalty setting in weapon spread calculation
		HookUtils::SafeWriteBuf(0x647902 + 1, "\xC8\xEA\x1C\x01");

		// missing nullcheck in NiMultiTargetTransformController::RemoveNodeRecurse
		HookUtils::SafeWrite8(0x4F064E, 0x7A);

		INISettingFixes::Install();

		// fixes for null pointers when showing credits outside of start menu
		CreditsMenuNullChecks::Install();

		// missing nullcheck in HandleStealing
		HookUtils::SafeWriteBuf(0x8BFBC1, "\x85\xC9\x74\x36\x80\x79\x04");

		// fix for incidental sounds not working in regions
		kGetFileChunkDataDetour.ReplaceCall(0x4F49AB, TESRegionDataSoundIncidentalIDHook);

		// fix for the stimpak crash
		HookUtils::WriteRelCall(0x7DB525, StimpakHotkeyHook);

		// Fix crash caused by wrong check inside AddSequence (thanks Stewie!)
		HookUtils::SafeWrite8(0xA2F0CB, 0x3A);

		// And also fix ANOTHER crash nearby caused by ANOTHER faulty nullptr check... this removes a DebugLog, but i don't care.
		HookUtils::WriteRelJump(0x490B10, 0x490B41);

		// fix NPE in BSTempEffectSimpleDecal
		HookUtils::WriteRelJump(0x68D2EB, SimpleDecalHook);

		// Fix for missing baseprocess null check
		HookUtils::WriteRelJump(0x59DF40, IsCurrentFurnitureRefHook);

		// AnimData NPEs
		// fix NPE in AnimData freeing
		HookUtils::WriteRelJump(0x490BBB, AnimDataNullCheck);
		kRemoveSequenceDetour.ReplaceCall(0xA2EC64, RemoveSequenceNullCheck);

		SkyUpdateFixes::Install();

		// Stop game from crashing on extensions reeeeeeeeeee
		AudioMonoLookupOverflowFix::Install();

		QuestObjectiveDisplayFix::Install();

		kSetCellImageSpaceDetour.ReplaceCall(0x5B7812, SetCellImageSpaceHook);

		// Patch the game so the dialog subroutine stops if the actor's head is blown off, I'll add it as an ini setting later.
		NoHeadlessTalkingFix::Install();

		// Add a baseform nullcheck for created refs in BGSSaveLoadGame::CheckInitialData
		HookUtils::SafeWriteBuf(0x849DE6, "\x85\xC0\x74\x08\x8B\x40\x0C");

		DestructionFixes::Install();
    
		// Disable frustum culling for the viewmodel
		// Game tries to do that by setting "always draw" on the player scene, but only on the root node
		// Fixed in CE... (are you even surprised by now?)
		HookUtils::SafeWrite8(0x875065 + 1, 1);

		BipedAnimFixes::Install();

		TESEffectShaderFixes::Install();
#endif

		FileFixes::Install();
	}

}
