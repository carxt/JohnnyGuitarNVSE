#include "JohnnyFixes.hpp"
#include "GameForms.h"
#include "GameProcess.h"
#include "GameSettings.h"
#include "GameUI.h"

#include "SkyUpdateFixes.hpp"
#include "EditorIDRestoration.hpp"
#include "QuestObjectiveDisplayFix.hpp"

STACK_FRAME_OPT_DISABLE
namespace JohnnyFixes {
	SPEC_NAKED void InventoryAmmoHook() {
		static constexpr uint32_t uiReturnAddr = 0x7080A8;
		__asm {
			mov		ecx, dword ptr[ebp - 0x2D4]
			call	TESObjectWEAP::GetAmmoInInventory
			mov		dword ptr[ebp - 0x2C8], eax
			jmp		uiReturnAddr
		}
	}

	namespace AmmoEffectListNullChecks {

		template<uint32_t uiAddress>
		class NullCheckHook {
			static inline HookUtils::CallDetour kDetour;

			static BSSimpleList<TESAmmoEffect*>* __fastcall GetAmmoEffectsCheckType(TESForm* apForm) {
				if (IS_TYPE(apForm, TESAmmo))
					return ThisCall<BSSimpleList<TESAmmoEffect*>*>(kDetour, apForm);
				return nullptr;
			}

		public:
			NullCheckHook() {
				kDetour.ReplaceCall(uiAddress, GetAmmoEffectsCheckType);
			}
		};


		void InitHooks() {
			NullCheckHook<0x523AD8>();
			NullCheckHook<0x64529D>();
			NullCheckHook<0x64553B>();
			NullCheckHook<0x6462C5>();
			NullCheckHook<0x9B5AFA>();
			NullCheckHook<0x9B5BDA>();
			NullCheckHook<0x9B5D2B>();
			NullCheckHook<0x9B6267>();
		}
	}

	HookUtils::CallDetour kDestroyContainerMenuDetour;
	void __fastcall OnCloseContainerHook(ContainerMenu* apMenu) {
		TESObjectREFR* pRef = apMenu->containerRef;
		if (pRef && pRef->IsActor())
			static_cast<Actor*>(pRef)->bSpeakingDone = true;
		ThisCall(kDestroyContainerMenuDetour, apMenu);
	}

	namespace DisintegrationStatFix {

		void InitHooks() {
			// check if user has Unnecessary Tweaks or lStewieAl's Tweaks installed
			if (*reinterpret_cast<uint8_t*>(0x8A1B4D) == 0xE9 || *reinterpret_cast<uint8_t*>(0x8A1B51) == 0x26)
				return;

			// critical stage 1, jump to checks for IncPCMiscStat
			HookUtils::SafeWrite8(0x8A1B51, 0x26); // change JE offset

			// critical stage 3, jump to checks for IncPCMiscStat
			HookUtils::SafeWriteBuf(0x8A1B1B, "\xF9\x01\x74\x12\x83\xF9\x02\x74\x30\x83\xF9\x04\x74\x2B\x83\xF9\x03\x74\x4A\xEB\x22\x90");

			// critical stages 2 and 4, skip IncPCMiscStat
			HookUtils::SafeWriteBuf(0x8A1B6E, "\x82\xC0\x01\x00\x00\xFF\xD0\xEB\x53\x90");
		}
	}

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

	HookUtils::CallDetour kSetBipedWeaponDetour;
	void __fastcall SetBipedWeaponModFix(BipedAnim* apThis, void*, TESObjectWEAP* apWeapon, uint8_t aucModSlots) {
		uint8_t* pEBP = GetParentBasePtr(_AddressOfReturnAddress());
		TESObjectREFR* pReference = *reinterpret_cast<TESObjectREFR**>(pEBP + 0x8);
		if (pReference && pReference->IsActor()) {
			Actor* pActor = static_cast<Actor*>(pReference);
			if (pActor->baseProcess) {
				ItemChange* pWeaponItem = pActor->baseProcess->GetCurrentWeapon();
				if (pWeaponItem)
					aucModSlots = pWeaponItem->GetModSlots();
			}
		}
		ThisCall(kSetBipedWeaponDetour, apThis, apWeapon, aucModSlots);
	}

	namespace INISettingFixes {

		template<uint32_t uiAddress>
		class GetINISettingHook {
			static inline HookUtils::CallDetour kDetour;

			static Setting* __fastcall Hook(INISettingCollection* apINICollection, void*, const char* apSettingName) {
				Setting* pINISetting = ThisCall<Setting*>(kDetour, apINICollection, apSettingName);
				if (pINISetting)
					return pINISetting;

				RendererSettingCollection* pRendererSettings = SettingT<RendererSettingCollection>::GetCollection();
				return ThisCall<Setting*>(kDetour, pRendererSettings, apSettingName);
			}
		public:
			GetINISettingHook() {
				kDetour.ReplaceCall(uiAddress, GetINISettingHook::Hook);
			}
		};

		HookUtils::CallDetour kSaveINIDetour;
		bool __fastcall SaveINIHook(INISettingCollection* apINICollection, void*, const char* apFileName) {
			ThisCall(kSaveINIDetour, apINICollection, apFileName);
			RendererSettingCollection* rendererSettings = SettingT<RendererSettingCollection>::GetCollection();
			return ThisCall<bool>(kSaveINIDetour, rendererSettings, rendererSettings->cSettingFile);
		}

		void __stdcall HandleSettingType(Setting* apSetting, Setting::Type type) {
			if (!IsConsoleMode())
				return;

			const char* const pKey = apSetting->pKey;

			switch (type) {
				case Setting::kSetting_Bool:
					Console_Print("INISetting %s >> %i", pKey, apSetting->uValue.b);
					break;
				case Setting::kSetting_Integer:
					Console_Print("INISetting %s >> %d", pKey, apSetting->uValue.i);
					break;
				case Setting::kSetting_Unsigned:
					Console_Print("INISetting %s >> %X", pKey, apSetting->uValue.u);
					break;
				case Setting::kSetting_Float:
					Console_Print("INISetting %s >> %.2f", pKey, apSetting->uValue.f);
					break;
				case Setting::kSetting_String:
					Console_Print("INISetting %s >> '%s'", pKey, apSetting->uValue.str);
					break;
				case Setting::kSetting_r:
					Console_Print("INISetting %s >> R: %d G: %d B: %d", pKey, apSetting->uValue.rgb[3], apSetting->uValue.rgb[2], apSetting->uValue.rgb[1]);
					break;
				case Setting::kSetting_a:
					Console_Print("INISetting %s >> R: %d G: %d B: %d alpha: %d", pKey, apSetting->uValue.rgb[3], apSetting->uValue.rgb[2], apSetting->uValue.rgb[1], apSetting->uValue.rgb[0]);
					break;
				default:
					Console_Print("INISetting %s >> UNKNOWN TYPE", pKey);
					break;
			}
		}

		SPEC_NAKED void GetINISettingTypeHook() {
			__asm {
				push	eax
				mov		eax, dword ptr ds : [ebp - 4]
				push	eax
				call	HandleSettingType
				mov		eax, 0x5BEE5D
				jmp		eax
			}
		}
		
		void InitHooks() {
			// Fix for Get/Set/SaveINISetting not reading renderer INI setting list
			GetINISettingHook<0x5BED66>();
			GetINISettingHook<0x5BEF13>();
			kSaveINIDetour.ReplaceCall(0x5B6C80, SaveINIHook);

			// Extend setting type support in GetIniSetting
			HookUtils::WriteRelJump(0x5BED86, GetINISettingTypeHook);
		}
	}

	namespace CreditsMenuNullChecks {

		template<uint32_t uiAddress>
		class SetFlagHook {
			static inline HookUtils::CallDetour kDetour;

			static void __fastcall Hook(StartMenu* apMenu, void*, uint32_t auiFlags, bool abSet) {
				if (apMenu != nullptr)
					ThisCall(kDetour, apMenu, auiFlags, abSet);
			}

		public:
			SetFlagHook() {
				kDetour.ReplaceCall(uiAddress, Hook);
			}
		};


		template<uint32_t uiAddress>
		class GetFlagHook {
			static inline HookUtils::CallDetour kDetour;

			static bool __fastcall Hook(StartMenu* apMenu, void*, uint32_t auiFlags) {
				if (!apMenu)
					return false;

				return ThisCall<bool>(kDetour, apMenu, auiFlags);
			}

		public:
			GetFlagHook() {
				kDetour.ReplaceCall(uiAddress, Hook);
			}
		};

		void InitHooks() {
			GetFlagHook<0x75F770>();
			SetFlagHook<0x75F8AE>();
			SetFlagHook<0x75F6DA>();
		}
	}

	HookUtils::CallDetour kGetFileChunkDataDetour;
	void __fastcall TESRegionDataSoundIncidentalIDHook(TESFile* apFile, void* edx, uint32_t* apFormID) {
		ThisCall(kGetFileChunkDataDetour, apFile, apFormID);
		if (*apFormID)
			CdeclCall(0x485D50, apFormID, apFile);
	}

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
	void __fastcall RemoveSequenceNullCheck(NiControllerManager* apManager, void*, NiControllerSequence* apSequence, NiPointer<NiControllerSequence>& arResult) {
		if (apManager)
			ThisCall(kRemoveSequenceDetour, apManager, apSequence, &arResult);
	}

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

		if (IsConsoleMode()) {
			// Reuse the original string, no need to duplicate *all* data
			Console_Print(((const char*)0x10350A8), arResult);
		}

		return true;
	}

	namespace AudioMonoLookupOverflowFix {
		char* __cdecl strstrHook(char* apBuffer, const char* apSuffix) {
			if (!strstr(apBuffer, apSuffix)) {
				char* pDot = strrchr(apBuffer, '.');
				if (pDot) {
					char cTempBuf[MAX_PATH] = {};
					strcpy_s(cTempBuf, MAX_PATH, pDot + 1);
					*pDot = '\0';
					strcat_s(apBuffer, MAX_PATH, apSuffix);
					strcat_s(apBuffer, MAX_PATH, cTempBuf);
				}
			}
			return apBuffer;
		}

		void InitHooks() {
			HookUtils::WriteRelCall(0x83509D, strstrHook);
		}
	}

	HookUtils::CallDetour kSetCellImageSpaceDetour;
	void __fastcall SetCellImageSpaceHook(TESObjectCELL* apCell, void*, TESImageSpace* apImageSpace) {
		ThisCall(kSetCellImageSpaceDetour, apCell, apImageSpace);
		const PlayerCharacter* pPlayer = PlayerCharacter::GetSingleton();
		if (apImageSpace && pPlayer->parentCell && pPlayer->parentCell == apCell)
			CdeclCall(0xB4F430, apImageSpace->traitValues);
	}

	namespace NoHeadlessTalkingFix {

		bool __fastcall CanSpeakThroughHead(Actor* apActor) {
			const bool bNoHead = ThisCall<bool>(0x573090, apActor, BGSBodyPartData::eBodyPart_Head1) || ThisCall<bool>(0x573090, apActor, BGSBodyPartData::eBodyPart_Head2);

			bool bCanSpeak = !bNoHead;
			if (bCanSpeak) {
				const BaseProcess* pAIProcess = apActor->baseProcess;
				if (pAIProcess && pAIProcess->processLevel == PROCESS_TYPE::HIGH && apActor->GetDead()) {
					const DialoguePackage* pPackage = static_cast<DialoguePackage*>(pAIProcess->GetCurrentPackage());
					if (pPackage) {
						const bool bDialoguePackage = pPackage->type == PACKAGE_TYPE::DIALOGUE || pPackage->type == PACKAGE_TYPE::IN_GAME_DIALOGUE;
						if (bDialoguePackage && (apActor != pPackage->subject) && (apActor == pPackage->speaker))
							bCanSpeak = false;
					}
				}
			}
			return bCanSpeak;
		}

		HookUtils::CallDetour kCanTalkDetour;
		BaseProcess* __fastcall NoHeadlessTalkingHook(Actor* apActor) {
			uint8_t* pEBP = GetParentBasePtr(_AddressOfReturnAddress());
			Actor* pSpeaker = *reinterpret_cast<Actor**>(pEBP + 0x8);

			BaseProcess* pAIProcess = ThisCall<BaseProcess*>(kCanTalkDetour, apActor);
			if (!pAIProcess || !CanSpeakThroughHead(pSpeaker))
				return nullptr;

			return pAIProcess;
		}

		void InitHooks() {
			kCanTalkDetour.ReplaceCall(0x8EC54D, NoHeadlessTalkingHook);
		}
	}

	void ClearPlayerFurniture() {
		BaseProcess* pAIProcess = PlayerCharacter::GetSingleton()->baseProcess;
		if (pAIProcess)
			pAIProcess->SetFurnitureRef(PlayerCharacter::GetSingleton(), 0, nullptr, 0x7F);
	}

	void Init() {
		// for Runtime EDIDs
		EDIDRestoration::InitHooks();

		// use available ammo in inventory instead of NULL when default ammo isn't present
		HookUtils::WriteRelJump(0x70809E, InventoryAmmoHook);

		// fix ammo effects list being checked for non-TESAmmo's when the Rock-It-Launcher is equipped
		AmmoEffectListNullChecks::InitHooks();

		// fix for companions not saying the next topic after opening ContainerMenu through dialog
		kDestroyContainerMenuDetour.ReplaceCall(0x75B2FB, OnCloseContainerHook);

		// Fix for animations not working in dialog topics with sound
		HookUtils::PatchMemoryNop(0x8A56C4, 4);
		HookUtils::PatchMemoryNop(0x8A56C8, 4);

		// fix Disintegrations stat not incrementing properly
		DisintegrationStatFix::InitHooks();

		// fix NPCs incrementing player challenges
		HookUtils::WriteRelJump(0x88D0D0, NPCIncrementingChallengesHook);

		// use correct weapon skill req penalty setting in weapon spread calculation
		HookUtils::SafeWriteBuf(0x647902 + 1, "\xC8\xEA\x1C\x01");

		// fix for various biped model update bugs
		kSetBipedWeaponDetour.ReplaceCall(0x6061E8, SetBipedWeaponModFix);

		// missing nullcheck in NiMultiTargetTransformController::RemoveNodeRecurse
		HookUtils::SafeWrite8(0x4F064E, 0x7A);

		INISettingFixes::InitHooks();

		// fixes for null pointers when showing credits outside of start menu
		CreditsMenuNullChecks::InitHooks();

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
		AudioMonoLookupOverflowFix::InitHooks();

		QuestObjectiveDisplayFix::Install();

		kSetCellImageSpaceDetour.ReplaceCall(0x5B7812, SetCellImageSpaceHook);

		// Patch the game so the dialog subroutine stops if the actor's head is blown off, I'll add it as an ini setting later.
		NoHeadlessTalkingFix::InitHooks();
	}

}
STACK_FRAME_OPT_RESET