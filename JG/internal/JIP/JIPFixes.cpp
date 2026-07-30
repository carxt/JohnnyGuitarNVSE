#include "JIPFixes.hpp"
#include "JIPSettings.hpp"
#include "JIPUtils.hpp"

#include "Bethesda/AutoMemContext.hpp"
#include "Bethesda/BSStringT.hpp"
#include "Bethesda/BSUtilities.hpp"
#include "Bethesda/FixedStrings.hpp"
#include "Bethesda/RendererSettingCollection.hpp"
#include "Bethesda/Setting.hpp"
#include "Bethesda/TimeGlobal.hpp"

#include "decoding.h"
#include "events/EventFramework.h"
#include "GameData.h"
#include "GameObjects.h"
#include "GameOSDepend.h"
#include "GameProcess.h"
#include "GameRTTI.h"
#include "GameTiles.h"
#include "ParamInfos.h"
#include "PluginAPI.h"
#include "utility.h"

#include "JG/JohnnyExtraData.hpp"
#include "internal/CommandOpcodes.h"

#include "Shared/BSMemory/BSScrapMemory.hpp"
#include "Shared/Utils/StackObject.hpp"
#include "Shared/Utils/CustomClass.hpp"

#include <GameUI.h>
#include <Bethesda/BSShaderUtil.hpp>

class BSRenderedTexture;

extern NVSECommandTableInterface* g_cmdTableInterface;
extern NVSEScriptInterface* g_scriptInterface;
extern bool bFixJIP;
extern bool (*ExtractArgsEx)(COMMAND_ARGS_EX, ...);
extern InventoryRef* (*InventoryRefGetForID)(uint32_t auiFormID);
extern TESObjectREFR* (__stdcall* InventoryRefCreateEntry)(TESObjectREFR* container, TESForm* itemForm, uint32_t countDelta, ExtraDataList* xData);

namespace JIPFixes {

	namespace ConsoleCmdFix {

		class ScriptCompileData {
		public:
			char*		pInput;
			uint32_t	uiInputOffset;
			uint32_t	eCompilerIndex;
			BSString	strCompilerName;
			// ... rest is not needed
		};

		STACK_FRAME_OPT_ENABLE
		bool __fastcall ScriptCompiler_Compile(void* apThis, void*, void* apScript, ScriptCompileData* apCompileData) {
			if (apCompileData->strCompilerName.pString && apCompileData->strCompilerName.pString[0] == 'C') {
				apCompileData->eCompilerIndex = strcmp(apCompileData->strCompilerName.pString, "Console") == 0;
			}

			return ThisCall<bool>(0x5AEB90, apThis, apScript, apCompileData);
		}
		STACK_FRAME_OPT_RESET

		void InitHooks() {
			HookUtils::SafeWrite32(JIPUtils::GetAddress(0x10059A86 + 1), uint32_t(ScriptCompiler_Compile));
		}

	}

	namespace PaletteCorruptionFix {

		STACK_FRAME_OPT_ENABLE

		static void __fastcall InvalidateObjPalette(NiAVObject* apObject) {
			if (!apObject) [[unlikely]]
				return;

			NiControllerManager* pControllerManager = apObject->GetController<NiControllerManager>();
			if (pControllerManager && pControllerManager->m_spObjectPalette) [[likely]]
				ThisCall(0xA6E960, pControllerManager->m_spObjectPalette.m_pObject);
		}

		HookUtils::CallDetour kMemPoolFree;
		void __fastcall MemoryPool_Free(void* apBlock, uint32_t auiSize) {
			char* pData = static_cast<char*>(apBlock);
			TESForm* pForm = *reinterpret_cast<TESForm**>(pData);

			if (pForm && pForm->IsReference()) [[likely]] {
				if (pForm == PlayerCharacter::GetSingleton()) {
					PlayerCharacter* pPlayer = static_cast<PlayerCharacter*>(pForm);
					InvalidateObjPalette(pPlayer->Get3D(true));
					InvalidateObjPalette(pPlayer->Get3D(false));
				}
				else {
					TESObjectREFR* pRef = static_cast<TESObjectREFR*>(pForm);
					InvalidateObjPalette(pRef->Get3DSimple());
				}
			}

			FastCall(kMemPoolFree, apBlock, auiSize);
		}

		STACK_FRAME_OPT_RESET

		void InitHooks() {
			kMemPoolFree.ReplaceCall(JIPUtils::GetAddress(0x1002BF45), MemoryPool_Free);
		}
	}

	namespace NotifyDurationFix {
		// This was painful
		uint32_t uiDefaultTimes[] = {
			0x4825C5,
			0x482619,
			0x4C5623,
			0x4CB8FC,
			0x4CEBDE,
			0x4CEC34,
			0x4CF14E,
			0x4CF1A7,
			0x4CF57B,
			0x4CF5D4,
			0x4CF7FB,
			0x4CF854,
			0x4CFB15,
			0x4CFB6E,
			0x4FEEE8,
			0x5013FD,
			0x501492,
			0x5016E8,
			0x508C7F,
			0x508D1F,
			0x509693,
			0x5096EB,
			0x50973C,
			0x509789,
			0x5097C7,
			0x509809,
			0x5150C6,
			0x5151CD,
			0x516F92,
			0x517063,
			0x51814E,
			0x518367,
			0x51853B,
			0x5185FF,
			0x5732E2,
			0x573449,
			0x5B5236,
			0x5B5285,
			0x5C1E86,
			0x5C86FD,
			0x5CDD75,
			0x5D0266,
			0x5D0473,
			0x5F5D34,
			0x5F5EE2,
			0x5F62DE,
			0x5F648C,
			0x5FA5D1,
			0x5FA687,
			0x5FA911,
			0x607BAD,
			0x607C63,
			0x60822D,
			0x608D3A,
			0x615845,
			0x61593C,
			0x615B09,
			0x615BF4,
			0x615DF6,
			0x615EFB,
			0x6160FA,
			0x6161F3,
			0x678442,
			0x702009,
			0x70E558,
			0x70E59C,
			0x7289B8,
			0x73380F,
			0x7338CB,
			0x73398D,
			0x733A48,
			0x7351AD,
			0x7352C7,
			0x737D32,
			0x7410FD,
			0x75739C,
			0x758295,
			0x75DE47,
			0x75E1A6,
			0x780506,
			0x780567,
			0x780849,
			0x7809B3,
			0x780A01,
			0x780A3D,
			0x780A8D,
			0x780AD5,
			0x780E83,
			0x780ED4,
			0x781C7F,
			0x781CEC,
			0x78DBEB,
			0x78EEB3,
			0x790160,
			0x790487,
			0x7981F4,
			0x7BBFEF,
			0x7BC0AB,
			0x7BC16A,
			0x7BC225,
			0x7BD714,
			0x7BD82E,
			0x7BEC27,
			0x7C0AFC,
			0x7C0C7B,
			0x7C0D37,
			0x7C0DF9,
			0x7C0EB4,
			0x7C18C2,
			0x7C2EDE,
			0x7C2FF8,
			0x7C3FC5,
			0x8159F6,
			0x823F58,
			0x825165,
			0x82BFC7,
			0x833E7B,
			0x834151,
			0x85045C,
			0x85057D,
			0x8505E2,
			0x8509AA,
			0x8509FA,
			0x856D21,
			0x878E46,
			0x88C914,
			0x88C969,
			0x88CB00,
			0x88CBE6,
			0x88CDB8,
			0x88CF98,
			0x88D1EC,
			0x88D840,
			0x891680, // The only ones with 4s duration instead of 2s
			0x8916C7, // The only ones with 4s duration instead of 2s
			0x891A9A, // The only ones with 4s duration instead of 2s
			0x8929F2,
			0x89AD83,
			0x89E0A9,
			0x8BA3AF,
			0x8C1E19,
			0x8C35CE,
			0x8C54E3,
			0x8C5523,
			0x8C557F,
			0x8C55BF,
			0x8C5771,
			0x8C57B1,
			0x8C580D,
			0x8C584D,
			0x8C59F1,
			0x8C5A31,
			0x8C5A8D,
			0x8C5ACD,
			0x8C5C71,
			0x8C5CB1,
			0x8C5D0D,
			0x8C5D4D,
			0x93D6C3,
			0x93D742,
			0x93D862,
			0x93D8CC,
			0x93D966,
			0x93D9F4,
			0x93DA50,
			0x93DB04,
			0x9423C6,
			0x942402,
			0x942462,
			0x9424AF,
			0x94250A,
			0x942562,
			0x9425A0,
			0x94260A,
			0x94264C,
			0x94DC08,
			0x94DD34,
			0x94FDEB,
			0x94FE1B,
			0x94FEEC,
			0x94FF1C,
			0x9627C2,
			0x966B38,
			0x969FC3,
			0x969FFF,
			0x96A05F,
			0x96A0AC,
			0x96A107,
			0x96A15F,
			0x96A19D,
			0x96A1FE,
			0x96A240,
		};

		void InitHooks() {
			const uint32_t uiJIPMessageDurationAddr = JIPUtils::GetAddress(0x1006A1B4);
			for (uint32_t uiAddress : uiDefaultTimes)
				HookUtils::SafeWrite32(uiAddress + 2, uiJIPMessageDurationAddr);

			HookUtils::SafeWriteBuf(0x70535C, "\x51\xD9\x45\x18\xD9\x1C\x24");
		}
	}

	namespace CloseActiveMenuFix {
		void InitHooks() {
			HookUtils::SafeWrite8(JIPUtils::GetAddress(0x1003B87B + 1), 0x7A);
		}
	}

	namespace FireWeaponFix {
		thread_local bool bScriptedCall = false;
		uint32_t uiDoFireWeaponAddr = 0;


		STACK_FRAME_OPT_ENABLE

		void __fastcall DoFireWeaponExWrapper(Actor* apActor, void*, TESObjectWEAP* apWeapon) {
			bScriptedCall = true;
			FastCall(uiDoFireWeaponAddr, apActor, nullptr, apWeapon);
			bScriptedCall = false;
		}

		HookUtils::VirtCallDetour kDetour;
		class ActorEx : public Actor {
		public:
			CombatController* GetCombatControllerEx() {
				CombatController* pController;
				if (kDetour)
					pController = ThisCall<CombatController*>(kDetour, this);
				else
					pController = GetCombatController();

				if (bScriptedCall && pController && !pController->combatProcedure1)
					return nullptr;

				return pController;
			}
		};

		STACK_FRAME_OPT_RESET

		void InitHooks() {
			uiDoFireWeaponAddr = JIPUtils::GetAddress(0x1001B6F0);
			HookUtils::SafeWrite32(JIPUtils::GetAddress(0x1001B827) + 4, uint32_t(DoFireWeaponExWrapper));

			kDetour.ReplaceVirtualCall(0x523B3F, &ActorEx::GetCombatControllerEx, 8);
		}
	}

	namespace ItemDescriptionFixFix {

		STACK_FRAME_OPT_ENABLE
		const char* __fastcall ConstructItemEntryNameHookFix(TESBoundObject* apObject, uint32_t* arLength) {
			*arLength = 0;
			const TESFullName* pFullName = DYNAMIC_CAST(apObject, TESBoundObject, TESFullName);
			if (!pFullName)
				return nullptr;

			const char* pString = pFullName->c_str();
			if (!pString || pString[0] == '\0')
				return nullptr;

			*arLength = pFullName->GetFullNameLength();
			return pString;
		}
		STACK_FRAME_OPT_RESET

		static uint32_t uiFailAddr = 0;
		static uint32_t uiSuccessAddr = 0;

		static SPEC_NAKED void ConstructItemEntryNameHookFix_Asm() {
			__asm {
				sub		esp, 4
				mov		edx, esp
				mov		ecx, eax
				call	ConstructItemEntryNameHookFix
				mov		edx, dword ptr[esp]
				add		esp, 4
				test	eax, eax
				jz		EXIT // If null, exit
				mov		ecx, edx
				jmp		uiSuccessAddr
			EXIT:
				jmp		uiFailAddr
			}
		}

		void InitHooks() {
			uiFailAddr		= JIPUtils::GetAddress(0x1000DF10);
			uiSuccessAddr	= JIPUtils::GetAddress(0x1000DECA);
			HookUtils::WriteRelJump(JIPUtils::GetAddress(0x1000DEC2), ConstructItemEntryNameHookFix_Asm);
			HookUtils::SafeWriteBuf(JIPUtils::GetAddress(0x1000DECC), "\x8D\x30\x90"); // Patch to use string from EAX instead of EAX+0x34
		}
	}

	namespace UpdateDataFix {
		// This one is personal - my mistake for making it a global... sorry Jazz

		STACK_FRAME_OPT_ENABLE
		class Hook {
		public:
			void UpdateDownwardPass(NiUpdateData& arData, uint32_t auiFlags) {
				NiUpdateData kData;
				reinterpret_cast<NiAVObject*>(this)->UpdateDownwardPass(kData, auiFlags);
			}

			void UpdateTransformAndBounds(NiUpdateData& arData) {
				NiUpdateData kData;
				reinterpret_cast<NiAVObject*>(this)->UpdateTransformAndBounds(kData);
			}

			void Update(NiUpdateData& arUpdateData) {
				NiUpdateData kData;
				reinterpret_cast<NiTimeController*>(this)->Update(kData);
			}
		};
		STACK_FRAME_OPT_RESET

		void InitHooks() {
			HookUtils::ReplaceVirtualCall(JIPUtils::GetAddress(0x1000A09A), &Hook::UpdateTransformAndBounds, 6);
			HookUtils::ReplaceVirtualCall(JIPUtils::GetAddress(0x10019C7A), &Hook::UpdateDownwardPass, 6);

			HookUtils::ReplaceVirtualCall(JIPUtils::GetAddress(0x1002AE08), &Hook::UpdateDownwardPass, 6);
			HookUtils::ReplaceVirtualCall(JIPUtils::GetAddress(0x1002B07A), &Hook::UpdateDownwardPass, 6);
			HookUtils::ReplaceVirtualCall(JIPUtils::GetAddress(0x1002B18A), &Hook::UpdateDownwardPass, 6);

			HookUtils::ReplaceVirtualCall(JIPUtils::GetAddress(0x1002CE4D), &Hook::Update, 6);

			HookUtils::ReplaceVirtualCall(JIPUtils::GetAddress(0x1005887C), &Hook::UpdateDownwardPass, 7);
			HookUtils::ReplaceVirtualCall(JIPUtils::GetAddress(0x10058927), &Hook::UpdateDownwardPass, 7);
			HookUtils::ReplaceVirtualCall(JIPUtils::GetAddress(0x10058A7E), &Hook::UpdateDownwardPass, 7);

			HookUtils::ReplaceVirtualFunc(JIPUtils::GetAddress(0x100280FE + 1), &Hook::UpdateDownwardPass);
		}
	}

	namespace EarlyFixedStrings {

		static uint32_t uiFoundStringAddr = 0x1000CE06;
		static uint32_t uiNewStringAddr = 0x1000CDDB;

		int32_t __fastcall StrCmp(const char* a, const char* b) {
			return strcmp(a, b);
		}

		static SPEC_NAKED void CompareFix_Asm() {
			__asm {
				START:
				cmp		[eax + 4], esi
				jnz		CONTINUE
				push	eax
				mov		edx, [ebp + 8]
				mov		ecx, [eax + 8]
				cmp		ecx, edx
				jnz		FULL_COMPARE
				pop		eax
				jmp		MATCH
				FULL_COMPARE:
				call	StrCmp
				test	eax, eax
				pop		eax
				jnz		CONTINUE
				MATCH:
				jmp		uiFoundStringAddr
				CONTINUE:
				mov		eax, [eax]
				test	eax, eax
				jnz		START
				jmp		uiNewStringAddr
			}
		}

		void* __fastcall StaticAlloc(size_t aSize) {
			MEMORY_CONTEXT(MC_STATIC_VARS);
			return BSMemory::malloc(aSize);
		}

		void InitHooks() {
			// Replaced by us now - see FixedStringsRework.cpp
#if 0
			uiFoundStringAddr = JIPUtils::GetAddress(0x1000CE06);
			uiNewStringAddr = JIPUtils::GetAddress(0x1000CDDB);
			HookUtils::WriteRelJump(JIPUtils::GetAddress(0x1000CDD0), CompareFix_Asm);
			HookUtils::SafeWrite8(0xA5B630, 0xC3);
			HookUtils::WriteRelJump(0xA5B690, JIPUtils::GetAddress(0x1000CE20));
			HookUtils::WriteRelJump(0xA5B460, JIPUtils::GetAddress(0x1000CEA0));
			HookUtils::PatchMemoryNopRange(JIPUtils::GetAddress(0x10012260), JIPUtils::GetAddress(0x1001228D));

			HookUtils::WriteRelJump(uint32_t(CompareFix_Asm) + 0x1D, uiFoundStringAddr);
			HookUtils::WriteRelJump(uint32_t(CompareFix_Asm) + 0x29, uiNewStringAddr);

			constexpr uint32_t BUCKET_SIZE = 4;
			constexpr uint32_t NEW_BUCKET_COUNT = 8192;

			HookUtils::SafeWrite32(JIPUtils::GetAddress(0x1000CD8E) + 1, NEW_BUCKET_COUNT * BUCKET_SIZE);
			HookUtils::SafeWrite32(JIPUtils::GetAddress(0x1000CD9A) + 1, NEW_BUCKET_COUNT);
			HookUtils::SafeWrite32(JIPUtils::GetAddress(0x1000CDBD) + 2, NEW_BUCKET_COUNT - 1);

			HookUtils::SafeWrite32(JIPUtils::GetAddress(0x1000CEB4) + 2, NEW_BUCKET_COUNT * BUCKET_SIZE);

			HookUtils::ReplaceCall(JIPUtils::GetAddress(0x1000CD93), StaticAlloc);
#endif
		}
	}

	namespace PerkEntryFix {
		void InitHooks() {
			HookUtils::PatchMemoryNop(JIPUtils::GetAddress(0x1000F3F3), 6);
		}
	}

	namespace CopyFaceGenFromFix {

		bool(__cdecl* CopyFaceGenFrom)(COMMAND_ARGS) = nullptr;

		STACK_FRAME_OPT_ENABLE
		bool Cmd_CopyFaceGenFrom_Execute(COMMAND_ARGS) {
			const bool bLoadFaceGenHeadEGTFilesOrg = *reinterpret_cast<bool*>(0x11D5AE0);
			const bool bResult = CopyFaceGenFrom(PASS_COMMAND_ARGS);
			*reinterpret_cast<bool*>(0x11D5AE0) = bLoadFaceGenHeadEGTFilesOrg;
			return bResult;
		}
		STACK_FRAME_OPT_RESET

		void InitHooks() {
			CommandInfo* pInfo = const_cast<CommandInfo*>(g_cmdTableInterface->GetByOpcode(CommandOpcodes::kCopyFaceGenFrom));
			if (pInfo) {
				CopyFaceGenFrom = pInfo->execute;
				pInfo->execute = Cmd_CopyFaceGenFrom_Execute;
			}
		}
	}

	namespace SoundSourceFileFix {
		bool(__cdecl* SetSoundSourceFile)(COMMAND_ARGS) = nullptr;

		bool Cmd_SetSoundSourceFile_Execute(COMMAND_ARGS) {
			TESSound* pSound = nullptr;
			char cPath[1024];
			if (ExtractArgsEx(EXTRACT_ARGS_EX, &pSound, &cPath) && pSound)
				pSound->soundFile.Set(cPath);
			return true;
		}

		void InitHooks() {
			CommandInfo* pInfo = const_cast<CommandInfo*>(g_cmdTableInterface->GetByOpcode(CommandOpcodes::kSetSoundSourceFile));
			if (pInfo) {
				SetSoundSourceFile = pInfo->execute;
				pInfo->execute = Cmd_SetSoundSourceFile_Execute;
			}
		}

	}
	namespace SetOnDialogTopicEventHandlerEx {

		EventInformation* OnDialogTopicHandler = nullptr;

		bool Cmd_SetOnDialogTopicEventHandler_JG_Execute(COMMAND_ARGS) {
			BOOL setOrRemove = FALSE;
			Script* script = nullptr;
			TESForm* filter[1] = { nullptr };
			if (ExtractArgsEx(EXTRACT_ARGS_EX, &script, &setOrRemove, &filter[0]) && script && IS_TYPE(script, Script)) {
				TESForm* pFilterForm = filter[0];

				if (!pFilterForm || IS_TYPE(pFilterForm, TESTopic) || IS_TYPE(pFilterForm, TESTopicInfo)) {
					if (OnDialogTopicHandler) {
						if (setOrRemove)
							OnDialogTopicHandler->RegisterEvent(script, (void**)&filter);
						else
							OnDialogTopicHandler->RemoveEvent(script, (void**)&filter);
					}
				}
			}
			return true;
		}

		HookUtils::CallDetour kGetResultScript;
		STACK_FRAME_OPT_DISABLE
		class TESTopicInfoEx : public TESTopicInfo {
		public:
			enum ResultScriptType : uint32_t {
				BEGIN	= 0,
				END		= 1,
				COUNT	= 2,
			};


			Script* GetResultScript(ResultScriptType aeScript) {
				if (aeScript == ResultScriptType::BEGIN) {
					uint8_t* pEBP = GetParentBasePtr(_AddressOfReturnAddress());
					TESObjectREFR* pOwner = *reinterpret_cast<TESObjectREFR**>(pEBP + 0xC);
					if (pOwner) {
						for (auto const& callback : OnDialogTopicHandler->callbacks) {
							auto filter = reinterpret_cast<FilterForm*>(callback.eventFilter);
							if (filter->IsFilterEmpty(0) || filter->IsBaseInFilter(0, this)) {
								CallUDF(callback.script, pOwner, OnDialogTopicHandler->numMaxArgs, this);
							}
							else if (pParentTopic && filter->IsBaseInFilter(0, pParentTopic)) {
								CallUDF(callback.script, pOwner, OnDialogTopicHandler->numMaxArgs, pParentTopic);
							}
						}
					}
				}

				return ThisCall<Script*>(kGetResultScript, this, aeScript);
			}
		};
		STACK_FRAME_OPT_RESET

		void InitHooks(bool abGECK) {
			CommandInfo* pInfo = const_cast<CommandInfo*>(g_cmdTableInterface->GetByOpcode(CommandOpcodes::kSetOnDialogTopicEventHandler));
			if (pInfo) {
				pInfo->execute = Cmd_SetOnDialogTopicEventHandler_JG_Execute;
				HookUtils::SafeWrite32(reinterpret_cast<SIZE_T>(&pInfo->params[2].isOptional), 1);

				if (!abGECK) {
					OnDialogTopicHandler = JGCreateEvent("OnDialogTopicHandler", 1, 1);
					kGetResultScript.ReplaceCall(0x61F18B, &TESTopicInfoEx::GetResultScript);
					HookUtils::SafeWriteBuf(0x61F184, "\x8B\x45\x08\x50\x8B\x4D\xF4\xE8");
				}
			}
		}

	}

	namespace RespawnDisableFix {

		bool(__cdecl* ClearDeadActors)(COMMAND_ARGS) = nullptr;

		thread_local BOOL bSkipRespawning = FALSE;

		STACK_FRAME_OPT_ENABLE

		class HighProcessEx : public HighProcess {
		public:
			void FadeAndDisable(Actor* apActor) {
				if (bSkipRespawning && apActor->GetRespawn())
					return;

				ThisCall(0x8FEB60, this, apActor);
			}
		};

		bool Cmd_ClearDeadActors_Execute(COMMAND_ARGS) {
			if (ExtractArgsEx(EXTRACT_ARGS_EX, &bSkipRespawning)) {
				ClearDeadActors(PASS_COMMAND_ARGS);
				bSkipRespawning = FALSE;
			}
			return true;
		}

		STACK_FRAME_OPT_RESET

		void InitHooks(bool abGECK) {
			CommandInfo* pInfo = const_cast<CommandInfo*>(g_cmdTableInterface->GetByOpcode(CommandOpcodes::kClearDeadActors));
			if (pInfo) {
				pInfo->params = kParams_OneOptionalInt;
				pInfo->numParams = 1;
				ClearDeadActors = pInfo->execute;
				pInfo->execute = Cmd_ClearDeadActors_Execute;

				if (!abGECK) {
					HookUtils::WriteRelCall(JIPUtils::GetAddress(0x10030C38), &HighProcessEx::FadeAndDisable);
					HookUtils::PatchMemoryNop(JIPUtils::GetAddress(0x10030C3D), 2);
				}
			}
		}

	}

	namespace ModelReloadFix {

		uint32_t uiWeaponHasScope = 0;

		bool Cmd_ReloadEquippedModels_Execute(COMMAND_ARGS) {
			const TESMain* pMain = TESMain::GetSingleton();
			if (pMain->bIsFlyCam && pMain->bFreezeTime)
				return true;

			constexpr uint32_t uiDisallowedFlags = TESForm::FormFlags::STILL_LOADING | TESForm::FormFlags::DELETED | TESForm::FormFlags::DISABLED;
			if (thisObj->uiFormFlags.Get(uiDisallowedFlags) || !thisObj->IsCharacter())
				return true;

			Actor* pActor = static_cast<Actor*>(thisObj);
			const BaseProcess* pProcess = pActor->baseProcess;
			if (!pProcess || pProcess->processLevel != PROCESS_TYPE::HIGH)
				return true;

			const NiNode* pRoot = thisObj->Get3D();
			BipedAnim* pBiped = thisObj->GetBiped();
			if (!pRoot || !pBiped)
				return true;

			int32_t iTargetObject = -1;
			if (reinterpret_cast<uint8_t*>(scriptData)[*opcodeOffsetPtr - 2] && reinterpret_cast<uint8_t*>(scriptData)[*opcodeOffsetPtr]) {
				int32_t iArgSlot;
				if (!ExtractArgsEx(EXTRACT_ARGS_EX, &iArgSlot))
					return true;

				iTargetObject = iArgSlot;
			}

			if (iTargetObject != 6 && iTargetObject < 20) {
				Bitfield32 uiValidParts = 0xFFFFFFBF;
				if (iTargetObject >= 0)
					uiValidParts = (1u << iTargetObject) & 0xFFFFFFBF;

				const bool bPlayer = pActor == PlayerCharacter::GetSingleton();
				if (bPlayer) {
					PlayerCharacter* pPlayer = static_cast<PlayerCharacter*>(pActor);
					BipedAnim* pBiped1st = pPlayer->GetBiped(true);
					BipedAnim* pBiped3rd = pPlayer->GetBiped(false);
					for (uint32_t i = 0; i < 20; i++) {
						if (uiValidParts.GetBit(i)) {
							if (i == 5) {
								pBiped1st->RemoveBipedWeapon();
								pBiped3rd->RemoveBipedWeapon();
							}
							else {
								pBiped1st->RemovePart(i, true);
								pBiped3rd->RemovePart(i, true);
							}
						}
					}
				}
				else {
					for (uint32_t i = 0; i < 20; i++) {
						if (uiValidParts.GetBit(i)) {
							if (i == 5)
								pBiped->RemoveBipedWeapon();
							else
								pBiped->RemovePart(i, true);
						}
					}
				}

				thisObj->ReplaceModel();

				bool bWeaponDrawn = pProcess->GetWeaponDrawn();

				if (bPlayer) {
					if (uiValidParts.GetBit(5)) {
						TESObjectWEAP* pWeapon = pBiped->kObjects[5].pWeapon;
						if (pWeapon && ThisCall<uint8_t>(uiWeaponHasScope, pActor)) {
							const bool bScopeVisible = HUDMainMenu::GetSingleton()->bScopeVisible;
							Interface::InitGunScope(&pWeapon->kScope);
							Interface::SetGunScopeVisible(bScopeVisible);
						}
					}

					PlayerCharacter* pPlayer = static_cast<PlayerCharacter*>(pActor);
					Animation* pAnim1st = pPlayer->GetAnimation(true);
					Animation* pAnim3rd = pPlayer->GetAnimation(false);

					if (bWeaponDrawn && pAnim1st->animSequence[4])
						pAnim1st->BlendOut(4, false);
					if (bWeaponDrawn && pAnim3rd->animSequence[4])
						pAnim3rd->BlendOut(4, false);

					pAnim1st->ReloadTargets(true);
					pAnim3rd->ReloadTargets(false);
				}
				else {
					Animation* pAnim = pActor->GetAnimation();

					if (bWeaponDrawn && pAnim->animSequence[4])
						pAnim->BlendOut(4, false);
					pAnim->ReloadTargets(false);
				}
			}
			return true;
		}

		void InitHooks() {
			uiWeaponHasScope = JIPUtils::GetAddress(0x10058F10);
			CommandInfo* pInfo = const_cast<CommandInfo*>(g_cmdTableInterface->GetByOpcode(CommandOpcodes::kReloadEquippedModels));
			if (pInfo) {
				pInfo->execute = Cmd_ReloadEquippedModels_Execute;
			}
		}
	}

	namespace BetterSearch {

		static ParamInfo kSearchParams[] =
		{
			{ "Query", kParamType_String, false },
			{ "Form Type", kParamType_String, true },
			{ "Plugin Name", kParamType_String, true },
			{ "Runtime Form Handling (0 - none, 1 - skip, 2 - only)", kParamType_Integer, true }
		};

		constexpr uint32_t MAX_LINE_WIDTH = 1700;
		constexpr uint32_t MAX_LINE_LENGTH = 120;

		class AutoLineWidth {
			static constexpr uint32_t LINE_WIDTH_ADDR = 0x71D122 + 6;

			uint32_t uiOriginalWidth;
		public:
			AutoLineWidth(uint32_t auiNewWidth) {
				uiOriginalWidth = *reinterpret_cast<uint32_t*>(LINE_WIDTH_ADDR);
				HookUtils::SafeWrite32(LINE_WIDTH_ADDR, auiNewWidth);
			}
			~AutoLineWidth() {
				HookUtils::SafeWrite32(LINE_WIDTH_ADDR, uiOriginalWidth);
			}
		};

		enum RuntimeFormHandling {
			NONE = 0,
			SKIP = 1,
			ONLY = 2
		};

		void __fastcall StringToLower(std::string_view& arString) {
			std::transform(arString.begin(), arString.end(), const_cast<char*>(arString.data()), [](unsigned char c) { return std::tolower(c); });
		}

		bool __fastcall CaseInsensitiveSubStr(const std::string_view& arString, const std::string_view& arSubString, size_t aStartPos = 0) {
			auto it = std::search(
				arString.begin() + aStartPos, arString.end(),
				arSubString.begin(), arSubString.end(),
				[](char ch1, char ch2) { return std::tolower(ch1) == ch2; }
			);
			return (it != arString.end());
		}

		bool __fastcall CaseInsensitiveStrCmp(const std::string_view& arString, const std::string_view& arSubString) {
			if (arString.length() != arSubString.length())
				return false;

			// Substring is assumed to be already lowercased
			for (size_t i = 0; i < arString.length(); ++i) {
				if (std::tolower(arString[i]) != arSubString[i])
					return false;
			}
			return true;
		}

		bool __fastcall FindSubstring(const std::string_view& arString, const std::string_view& arSubString, bool abExact = true) {
			if (arSubString.empty())
				return false;

			if (arSubString.front() == '*' && arSubString.length() == 1)
				return true;

			if (arSubString.front() == '*' && arSubString.back() == '*') {
				uint32_t uiCount = arSubString.length() >= 2 ? arSubString.length() - 2 : 0;
				uiCount = std::clamp(uiCount, 0u, arString.length());
				const std::string_view svSubStr = arSubString.substr(1, uiCount);
				return CaseInsensitiveSubStr(arString, svSubStr);
			}
			else if (arSubString.front() == '*') {
				const std::string_view svSubStr = arSubString.substr(1);
				uint32_t uiStartPos = arString.length() >= svSubStr.length() ? arString.length() - svSubStr.length() : 0;
				uiStartPos = std::clamp(uiStartPos, 0u, arString.length());
				return CaseInsensitiveStrCmp(arString.substr(uiStartPos), svSubStr);
			}
			else if (arSubString.back() == '*') {
				uint32_t uiCount = arString.length() >= arSubString.length() - 1 ? arSubString.length() - 1 : arString.length();
				uiCount = std::clamp(uiCount, 0u, arString.length());
				const std::string_view svSubStr = arSubString.substr(0, uiCount);
				return CaseInsensitiveStrCmp(arString.substr(0, svSubStr.length()), svSubStr);
			}
			else if (abExact)
				return CaseInsensitiveStrCmp(arString, arSubString);
			else
				return CaseInsensitiveSubStr(arString, arSubString);
		}

		void __fastcall TruncateString(const char* apString, char* apBuffer, size_t aBufferSize) {
			constexpr const char SUFFIX[] = "...";
			const uint32_t uiCopySize = aBufferSize - sizeof(SUFFIX) - 1;
			memcpy(apBuffer, apString, uiCopySize);
			memcpy(apBuffer + uiCopySize, SUFFIX, sizeof(SUFFIX));
			apBuffer[aBufferSize - 1] = '\0';
		}

		void __fastcall DisplayForm(const TESForm* apForm, const char* apEDID) {
			const TESFile* pFile = apForm->GetFile(0);
			const char* pFullName = apForm->IsReference() ? static_cast<const TESObjectREFR*>(apForm)->GetFullName() : TESFullName::GetFullName(apForm);
			const char* pFileName = pFile ? pFile->GetName() : "Runtime";
			const char* pType = apForm->GetFormTypeName();
			const char* pEDID = (apEDID && apEDID[0]) ? apEDID : "NO-EDID";
			if (pFullName && pFullName[0]) {
				constexpr uint32_t FRONT_PADDING = 24; // Tweaks' time + FormID
				constexpr uint32_t SEPARATOR_PADDING = 3 * 3; // " | "
				constexpr uint32_t BRACKETS_PADDING = 2; // "()"
				const uint32_t uiTypeLength = strlen(pType);
				const uint32_t uiEDIDLength = strlen(pEDID);
				const uint32_t uiFileNameLength = strlen(pFileName);
				const uint32_t uiFullNameLength = strlen(pFullName);

				const uint32_t uiTotalLength = FRONT_PADDING + uiTypeLength + uiEDIDLength + uiFullNameLength + uiFileNameLength + SEPARATOR_PADDING + BRACKETS_PADDING;

				char cTruncatedFullName[32];
				// TLDR: Console's line breaks suck ass, so let's try to avoid them as much as possible
				if (uiTotalLength > MAX_LINE_LENGTH) {
					const uint32_t uiExcessLength = uiTotalLength - MAX_LINE_LENGTH;
					const uint32_t uiTruncatedLength = uiFullNameLength >= uiExcessLength ? (uiFullNameLength - uiExcessLength) : uiExcessLength;
					// If we need to trim, truncate the full name and add "..." at the end
					TruncateString(pFullName, cTruncatedFullName, std::clamp<uint32_t>(uiTruncatedLength, 8, sizeof(cTruncatedFullName)));
					pFullName = cTruncatedFullName;
				}
				Console_Print("%08X | %s | %s (%s) | %s", apForm->GetFormID(), pType, pEDID, pFullName, pFileName);
			}
			else {
				Console_Print("%08X | %s | %s | %s", apForm->GetFormID(), pType, pEDID, pFileName);
			}
		}

		bool __fastcall SearchEDID(const TESForm* apForm, const std::string_view& arSearch) {
			JohnnyExtraData* pJGE = JohnnyExtraData::Find(apForm);
			if (!pJGE)
				return false;

			auto pEDIDIter = pJGE->kFormData.kEditorIDs.GetHead();
			while (pEDIDIter && !pEDIDIter->IsEmpty()) {
				const NiFixedString& rEDID = pEDIDIter->GetItem();
				pEDIDIter = pEDIDIter->GetNext();

				std::string_view svEDID(rEDID.c_str(), rEDID.GetLength());
				if (FindSubstring(svEDID, arSearch, false)) {
					DisplayForm(apForm, rEDID.c_str());
					return true;
				}
			}

			return false;
		}

		bool __fastcall SearchFullName(const TESForm* apForm, const std::string_view& arSearch) {
			const char* pFullName = apForm->IsReference() ? static_cast<const TESObjectREFR*>(apForm)->GetFullName() : TESFullName::GetFullName(apForm);
			if (pFullName && pFullName[0]) {
				if (FindSubstring(pFullName, arSearch, false)) {
					DisplayForm(apForm, apForm->GetFormEditorID());
					return true;
				}
			}
			return false;
		}

		bool __fastcall GetFiles(std::vector<TESFile*, BSScrapAllocator<TESFile*>>& arFiles, const std::string_view& arSearch) {
			auto pIter = TESDataHandler::GetSingleton()->kFiles.GetHead();
			while (pIter && !pIter->IsEmpty()) {
				TESFile* pFile = pIter->GetItem();
				pIter = pIter->GetNext();
				if (pFile && FindSubstring(pFile->GetName(), arSearch))
					arFiles.push_back(pFile);
			}
			return !arFiles.empty();
		}

		bool __fastcall SearchFiles(const TESForm* apForm, const std::vector<TESFile*, BSScrapAllocator<TESFile*>>& arFiles) {
			const TESFile* pFile = apForm->GetFile(0);
			if (!pFile)
				return false;

			return std::find(arFiles.begin(), arFiles.end(), pFile) != arFiles.end();
		}

		bool __fastcall SearchType(const TESForm* apForm, const std::vector<FORM_TYPE, BSScrapAllocator<FORM_TYPE>>& arTypes) {
			const FORM_TYPE eFormType = apForm->GetFormType();
			return std::find(arTypes.begin(), arTypes.end(), eFormType) != arTypes.end();
		}

		bool Cmd_Search_JG_Execute(COMMAND_ARGS) {
			char cSearchBuffer[256] = { 0 };
			char cTypeBufer[128] = { 0 };
			char cPluginBuffer[MAX_PATH] = { 0 };
			RuntimeFormHandling eRuntimeHandling = RuntimeFormHandling::SKIP;
			if (!ExtractArgsEx(EXTRACT_ARGS_EX, &cSearchBuffer, &cTypeBufer, &cPluginBuffer, &eRuntimeHandling))
				return true;

			if (!cSearchBuffer[0])
				return true;

			bool bSearchFiles = false;
			bool bSearchType = false;

			std::string_view svSearch(cSearchBuffer);
			StringToLower(svSearch);

			std::vector<TESFile*, BSScrapAllocator<TESFile*>> kFiles;
			if (cPluginBuffer[0] && cPluginBuffer[0] != ' ') {
				std::string_view svPlugin(cPluginBuffer);
				if (svPlugin.front() != '*' || svPlugin.length() > 1) {
					StringToLower(svPlugin);
					GetFiles(kFiles, svPlugin);
					bSearchFiles = true;
				}
			}

			std::vector<FORM_TYPE, BSScrapAllocator<FORM_TYPE>> kFormTypes;
			if (cTypeBufer[0] && cTypeBufer[0] != ' ') {
				if (cTypeBufer[0] >= '0' && cTypeBufer[0] <= '9') {
					FORM_TYPE eFormType = static_cast<FORM_TYPE>(atoi(cTypeBufer));
					if (eFormType > FORM_TYPE::NONE && eFormType < FORM_TYPE::COUNT)
						kFormTypes.push_back(eFormType);
					bSearchType = true;
				}
				else {
					std::string_view svType(cTypeBufer);
					if (svType.front() != '*' || svType.length() > 1) {
						StringToLower(svType);
						for (uint32_t i = FORM_TYPE::NONE; i < FORM_TYPE::COUNT; i++) {
							if (FindSubstring(TESForm::GetFormTypeString(i), svType) || FindSubstring(TESForm::GetFormTypeName(i), svType))
								kFormTypes.push_back(static_cast<FORM_TYPE>(i));
						}
						bSearchType = true;
					}
				}
			}

			AutoLineWidth kLineWidthFix(MAX_LINE_WIDTH);
			auto kIter = TESForm::pAllForms->GetFirstPos();
			while (kIter) {
				uint32_t uiID = 0;
				TESForm* pForm = nullptr;
				TESForm::pAllForms->GetNext(kIter, uiID, pForm);

				constexpr uint32_t uiDisallowedFlags = TESForm::FormFlags::DELETED | TESForm::FormFlags::STILL_LOADING;
				if (pForm && pForm->uiFormFlags.IsClear(uiDisallowedFlags)) {
					if (eRuntimeHandling != RuntimeFormHandling::NONE) {
						bool bRuntime = pForm->kFiles.IsEmpty();
						if (eRuntimeHandling == RuntimeFormHandling::SKIP && bRuntime)
							continue;
						else if (eRuntimeHandling == RuntimeFormHandling::ONLY && !bRuntime)
							continue;
					}

					if (bSearchType && (kFormTypes.empty() || !SearchType(pForm, kFormTypes)))
						continue;

					if (bSearchFiles && (kFiles.empty() || !SearchFiles(pForm, kFiles)))
						continue;

					if (!SearchEDID(pForm, svSearch))
						SearchFullName(pForm, svSearch);
				}
			}

			return true;
		}

		bool(__cdecl* Cmd_Search_Org_Parse)(uint32_t, ParamInfo*, ScriptLineBuffer*, ScriptBuffer*) = nullptr;
		bool Cmd_Search_JG_Parse(uint32_t numParams, ParamInfo* paramInfo, ScriptLineBuffer* lineBuf, ScriptBuffer* scriptBuf) {
			// Replace "" with " " because obsnig is stupid and doesn't allow empty strings as params
			const char* pText = lineBuf->paramText;
			char cNewText[512] = { 0 };
			uint32_t uiNewTextLen = 0;
			for (uint32_t i = 0; i < lineBuf->paramTextLen; i++) {
				cNewText[uiNewTextLen++] = pText[i];
				if (pText[i] == '"' && pText[i + 1] == '"') {
					cNewText[uiNewTextLen] = ' ';
					uiNewTextLen++;
				}
			}
			strcpy_s(lineBuf->paramText, cNewText);
			lineBuf->paramTextLen = uiNewTextLen;
			return Cmd_Search_Org_Parse(numParams, paramInfo, lineBuf, scriptBuf);
		}

		void InitHooks() {
			CommandInfo* pInfo = const_cast<CommandInfo*>(g_cmdTableInterface->GetByOpcode(CommandOpcodes::kSearch));
			if (pInfo) {
				Cmd_Search_Org_Parse = pInfo->parse;
				pInfo->execute		= Cmd_Search_JG_Execute;
				pInfo->parse		= Cmd_Search_JG_Parse;
				pInfo->params		= kSearchParams;
				pInfo->numParams	= ARRAYSIZE(kSearchParams);
			}
		}

	}

	namespace WeaponModEffectsFix {
		void InitHooks() {
			HookUtils::PatchMemoryNop(JIPUtils::GetAddress(0x1003DA30), 5);
			HookUtils::SafeWrite8(JIPUtils::GetAddress(0x1003DA2B + 2), 0xF);
		}
	}

	namespace OnMenuClickFix {

		static inline Tile* const INVALID_TILE = reinterpret_cast<Tile*>(-1);
		Tile* pClickedTile = INVALID_TILE;
		uint32_t uiMenuHandleClickHook = 0;
		char cEmptyBuffer[4] = { 0 };

		STACK_FRAME_OPT_ENABLE
		void __fastcall MenuHandleClickHookDetour(void* apMenu, void* edx, uint32_t auiTileID, Tile* apTile) {
			pClickedTile = apTile;
			FastCall(uiMenuHandleClickHook, apMenu, edx, auiTileID, apTile);
		}
		STACK_FRAME_OPT_RESET

		STACK_FRAME_OPT_DISABLE
		bool __cdecl CallFunctionAlt(Script* apScript, TESObjectREFR* apRef, uint8_t aucArgCount, uint32_t auiMenuID, uint32_t auiTileID, const char* apTileString) {
			uint8_t* pEBP = GetParentBasePtr(_AddressOfReturnAddress());
			if (pClickedTile == INVALID_TILE) {
				const char* pTilePath = reinterpret_cast<const char*>(pEBP - 0x94);
				char cErrorBuffer[512];
				our_snprintf(cErrorBuffer, sizeof(cErrorBuffer), "Error! \"%s\" has been unloaded while being processed by OnClickMenuHandler. Do NOT do this!", pTilePath);
				_MESSAGE(cErrorBuffer);
				Console_Print(cErrorBuffer);
				*reinterpret_cast<DWORD*>(pEBP + 0xC) = 0;
				return false;
			}
			else if (pClickedTile) {
				return g_scriptInterface->CallFunctionAlt(apScript, apRef, aucArgCount, auiMenuID, auiTileID, pClickedTile->name.c_str());
			}
			else {
				return g_scriptInterface->CallFunctionAlt(apScript, apRef, aucArgCount, auiMenuID, auiTileID, cEmptyBuffer);
			}
		}
		STACK_FRAME_OPT_RESET

		HookUtils::CallDetour kRemoveTileFromUpdateList;
		STACK_FRAME_OPT_ENABLE
		class Hook {
		public:
			void CleanupTile(Tile* apTile) {
				if (pClickedTile == apTile)
					pClickedTile = INVALID_TILE;

				ThisCall(kRemoveTileFromUpdateList, this, apTile);
			}
		};
		STACK_FRAME_OPT_RESET

		void InitHooks() {
			uiMenuHandleClickHook = JIPUtils::GetAddress(0x10008570);
			HookUtils::SafeWrite32(JIPUtils::GetAddress(0x10039C8A) + 1, uint32_t(MenuHandleClickHookDetour));
			HookUtils::SafeWrite32(JIPUtils::GetAddress(0x1003A008) + 1, uint32_t(MenuHandleClickHookDetour));

			HookUtils::SafeWriteBuf(JIPUtils::GetAddress(0x10008683), "\x6A\x00\x90");
			HookUtils::PatchMemoryNop(JIPUtils::GetAddress(0x10008693), 6);
			HookUtils::WriteRelCall(JIPUtils::GetAddress(0x10008693), CallFunctionAlt);

			HookUtils::WriteRelJump(JIPUtils::GetAddress(0x1000872F), JIPUtils::GetAddress(0x1000873B));
			HookUtils::PatchMemoryNop(JIPUtils::GetAddress(0x10008791), 6);
			HookUtils::WriteRelCall(JIPUtils::GetAddress(0x10008791), CallFunctionAlt);

			kRemoveTileFromUpdateList.ReplaceCall(0x706C98, &Hook::CleanupTile);
		}
	}

	namespace PowerArmorCondition {

		STACK_FRAME_OPT_ENABLE
		bool Cmd_GetPCCanUsePowerArmor_Eval(COMMAND_ARGS_EVAL) {
			*result = PlayerCharacter::GetSingleton()->canUsePA;
			return true;
		}
		STACK_FRAME_OPT_RESET

		void InitHooks() {
			CommandInfo* pInfo = const_cast<CommandInfo*>(g_cmdTableInterface->GetByOpcode(CommandOpcodes::kGetPCCanUsePowerArmor));
			if (pInfo) {
				pInfo->eval = Cmd_GetPCCanUsePowerArmor_Eval;
			}
		}
	}

	namespace GetMenuItemListRefsFix {

		STACK_FRAME_OPT_ENABLE
		uint32_t __fastcall GetTileIndex(Tile* apTile) {
			const Tile* pParent = apTile->parent;
			if (pParent) [[likely]] {
				auto kIter = pParent->children.GetHeadPos();
				uint32_t uiIndex = 0;
				while (kIter) {
					const Tile* pChild = pParent->children.GetNext(kIter);
					if (pChild == apTile)
						return uiIndex;
					++uiIndex;
				}
			}
			return 0;
		}
		STACK_FRAME_OPT_RESET

		static uint32_t uiReturnAddr;
		static SPEC_NAKED void GetTileIndex_Asm() {
			__asm {
				// Store SetElement ptr
				mov		[esp + 0x1C], edi

				// Our code - ECX now contains the tile
				mov     ecx, [ecx]
				push	eax
				push	edx
				call	GetTileIndex
				mov		edi, eax
				pop		edx
				pop		eax

				// Get Item
				mov     ecx, [eax]

				jmp		uiReturnAddr
			}
		}

		void InitHooks() {
			uiReturnAddr = JIPUtils::GetAddress(0x1003BD6C);
			HookUtils::SafeWrite8(JIPUtils::GetAddress(0x1003BD5A) + 1, 0x3D); // Change reg to EDI
			HookUtils::SafeWrite8(JIPUtils::GetAddress(0x1003BDB1), 0x90);
			HookUtils::SafeWrite8(JIPUtils::GetAddress(0x1003BD58) + 1, 0x58);
			HookUtils::WriteRelJump(JIPUtils::GetAddress(0x1003BD66), GetTileIndex_Asm);
		}
	}

	namespace WaterRenderFix {

		constexpr float WATER_OPACITY = 0.8f;
		constexpr float WATER_REFLECTIVITY = 0.3f;

		static constexpr AddressPtr<NiPointer<BSRenderedTexture>, 0x11C7C2C>	spSkyReflectionMap;

		STACK_FRAME_OPT_ENABLE

		// Greetings from Real Time Reflections
		class JIPCullingProcess : public CustomClass<BSCullingProcess> {
		private:
			struct WaterShaderEntry {
				bool							bLOD;
				bool							bDepth;
				bool							bReflect;
				bool							bRefract;
				float							fWaterReflectivityAmt;
				float							fWaterOpacity;
				NiPointer<BSRenderedTexture>	spReflectionTexture;
			};

			// Holy crap, stl sucks
			using ScrapMap = std::unordered_map<WaterShaderProperty*, WaterShaderEntry, std::hash<WaterShaderProperty*>, std::equal_to<WaterShaderProperty*>, BSScrapAllocator<std::pair<WaterShaderProperty* const, WaterShaderEntry>>>;

			ScrapMap kWaterShaderProps;

			bool __fastcall DowngradeWaterShader(WaterShaderProperty* apWaterShaderProp) {
				if (apWaterShaderProp->bDisplacement)
					return false;

				WaterShaderEntry kExistingEntry;
				auto kIter = kWaterShaderProps.find(apWaterShaderProp);
				if (kIter != kWaterShaderProps.end()) {
					return true;
				}

				WaterShaderEntry kEntry;
				kEntry.bDepth = apWaterShaderProp->bDepth;
				kEntry.bReflect = apWaterShaderProp->bReflections;
				kEntry.bRefract = apWaterShaderProp->bRefractions;
				kEntry.fWaterReflectivityAmt = apWaterShaderProp->kVarAmounts.fWaterReflectivityAmt;
				kEntry.fWaterOpacity = apWaterShaderProp->kVarAmounts.fWaterOpacity;
				kEntry.spReflectionTexture = apWaterShaderProp->spReflectionMap;

				apWaterShaderProp->bDepth = false;
				apWaterShaderProp->bRefractions = false;
				apWaterShaderProp->kVarAmounts.fWaterReflectivityAmt = WATER_REFLECTIVITY;
				apWaterShaderProp->kVarAmounts.fWaterOpacity = WATER_OPACITY;
				if (!TES::GetSingleton()->currentInterior && spSkyReflectionMap.Get()) {
					if (apWaterShaderProp->bReflections) {
						apWaterShaderProp->spReflectionMap = spSkyReflectionMap.Get();
					}
				}
				else {
					apWaterShaderProp->bReflections = false;
				}

				apWaterShaderProp->ClearRenderPasses();

				kWaterShaderProps.insert({ apWaterShaderProp, kEntry });
				return true;
			}

			void __fastcall RestoreWaterShaders() {
				for (auto& rItem : kWaterShaderProps) {
					WaterShaderProperty* pKey = rItem.first;
					WaterShaderEntry& rEntry = rItem.second;
					if (pKey) {
						pKey->bDepth = rEntry.bDepth;
						pKey->bReflections = rEntry.bReflect;
						pKey->bRefractions = rEntry.bRefract;
						pKey->kVarAmounts.fWaterReflectivityAmt = rEntry.fWaterReflectivityAmt;
						pKey->kVarAmounts.fWaterOpacity = rEntry.fWaterOpacity;
						pKey->spReflectionMap = rEntry.spReflectionTexture;

						pKey->ClearRenderPasses();
					}
				}
			}

			void _Append(NiGeometry* apGeom) {
				BSShaderProperty* pShaderProp = apGeom->shaderProp;
				if (pShaderProp->iShader == 17) {
					if (!DowngradeWaterShader(static_cast<WaterShaderProperty*>(const_cast<BSShaderProperty*>(pShaderProp))))
						return;
				}

				spAccumulator->RegisterObject(apGeom);
			}

		public:
			void __fastcall Initialize() {
				BuildVTable<BSCullingProcess, 20>(
					{
						{ 19, &JIPCullingProcess::_Append }
					},
					0x101E2EC
				);

				new (&kWaterShaderProps) ScrapMap();
			}

			void __fastcall Destroy() {
				RestoreWaterShaders();
				kWaterShaderProps.~ScrapMap();
			}
		};

		void __fastcall RenderWater(void* apWaterManager, NiCamera* apCamera) {
			if (TES::GetSingleton()->currentInterior)
				return;

			BSShaderAccumulator* pAccum = TESMain::GetSingleton()->spDrawWorldAccum;
			if (pAccum->bCellHasWater && !pAccum->bIsUnderwater) {
				ThisCall(0x4EAF80, apWaterManager, apCamera);
				ThisCall(0x4EBBE0, apWaterManager);
			}
		}

		void __cdecl AccumulateScene(NiCamera* apCamera, NiNode* apNode, BSCullingProcess* apCullingProcess) {
			BSShaderAccumulator* pAccum = TESMain::GetSingleton()->spDrawWorldAccum;
			BSShaderAccumulator* pCullingAccum = static_cast<BSShaderAccumulator*>(apCullingProcess->GetAccumulator());
			pCullingAccum->bCellHasWater = pAccum->bCellHasWater;
			pCullingAccum->bIsUnderwater = pAccum->bIsUnderwater;
			pCullingAccum->iCurrentWaterHeight = pAccum->iCurrentWaterHeight;

			if (pAccum->bCellHasWater) {
				StackObject<JIPCullingProcess, 0x4A0EB0, 0x4A0F60> kCullingProcess(nullptr);
				kCullingProcess->m_pkCamera = apCullingProcess->m_pkCamera;
				kCullingProcess->eCullMode = apCullingProcess->eCullMode;
				kCullingProcess->spAccumulator = apCullingProcess->spAccumulator;
				kCullingProcess->Initialize();
				BSShaderUtil::AccumulateScene(apCamera, apNode, kCullingProcess.GetPtr());
				BSShaderUtil::RenderScene(apCamera, pCullingAccum);
				kCullingProcess->Destroy();
			}
			else {
				BSShaderUtil::AccumulateScene(apCamera, apNode, apCullingProcess);
				BSShaderUtil::RenderScene(apCamera, pCullingAccum);
			}
		}

		STACK_FRAME_OPT_RESET

		void InitHooks() {
			HookUtils::SafeWrite32(JIPUtils::GetAddress(0x10004963) + 1, uint32_t(AccumulateScene));
			HookUtils::ReplaceCall(JIPUtils::GetAddress(0x1002D27D), RenderWater);
			HookUtils::PatchMemoryNop(JIPUtils::GetAddress(0x10004976), 2);
		}
	}

	namespace GetSelectedItemRefFix {

		static uint32_t uiReturnAddr;
		static SPEC_NAKED void GetBarterRef_Asm() {
			__asm {
				test	eax, eax
				jz		NO_MERCHANT_CONTAINER

				mov     edx, [eax + 0xC]
				jmp		EXIT

				NO_MERCHANT_CONTAINER:
				mov     edx, dword ptr ds : [0x11D8FA4]
				mov     edx, [edx + 0x80]

			EXIT:
				jmp		uiReturnAddr
			}
		}

		void InitHooks() {
			uiReturnAddr = JIPUtils::GetAddress(0x10038FA2);
			HookUtils::WriteRelJump(JIPUtils::GetAddress(0x10038F4A), GetBarterRef_Asm);
		}
	}

	namespace Update3DTweak {

		void InitHooks() {
			HookUtils::SafeWrite8(JIPUtils::GetAddress(0x1005825F) + 1, 0); // Change priority to critical
		}
	}

	namespace AddItemAltNoCond {

		uint32_t uiSetItemHealthAddr;
		STACK_FRAME_OPT_ENABLE
		void __fastcall SetItemHealth(TESContainer* apContainer, float afHealth) {
			if (afHealth >= 0.f)
				FastCall(uiSetItemHealthAddr, apContainer, afHealth);
		}
		STACK_FRAME_OPT_RESET

		void InitHooks() {
			uiSetItemHealthAddr = JIPUtils::GetAddress(0x1000D520);
			HookUtils::ReplaceCall(JIPUtils::GetAddress(0x10058476), SetItemHealth);
		}
	}

	namespace CursorPosUICords {

		bool* pbHUDCursorMode = nullptr;

		bool Cmd_GetCursorPos_Execute(COMMAND_ARGS) {
			*result = 0;
			char cAxis;
			BOOL bUICoordinates = FALSE;
			if (ExtractArgsEx(EXTRACT_ARGS_EX, &cAxis, &bUICoordinates)) {
				float fCursorPos = (cAxis == 'X' || cAxis == 'x') ? InterfaceManager::GetSingleton()->cursorX : InterfaceManager::GetSingleton()->cursorY;
				if (bUICoordinates) {
					const float fUIPixelSize = *reinterpret_cast<float*>(0x11D8A48);
					fCursorPos *= fUIPixelSize;
				}
				*result = fCursorPos;
			}

			return true;
		}

		bool Cmd_SetCursorPos_Execute(COMMAND_ARGS) {
			*result = 0;
			float fPosX, fPosY;
			BOOL bUICoordinates = FALSE;
			InterfaceManager* pUIMgr = InterfaceManager::GetSingleton();
			if (ExtractArgsEx(EXTRACT_ARGS_EX, &fPosX, &fPosY, &bUICoordinates) && (pUIMgr->IsInMenuMode() || *pbHUDCursorMode)) {
				const float fUIPixelSize = *reinterpret_cast<float*>(0x11D8A48);
				const float fScreenWidth = RendererSettingCollection::Display::iSizeW->Int() * fUIPixelSize * 0.5f;
				const float fScreenHeight = RendererSettingCollection::Display::iSizeH->Int() * fUIPixelSize * 0.5f;
				if (bUICoordinates) {
					fPosX /= fUIPixelSize;
					fPosY /= fUIPixelSize;
				}
				pUIMgr->cursorX = fPosX;
				pUIMgr->cursorY = fPosY;
				pUIMgr->cursor->node->m_kLocal.m_kTranslate.x = (fPosX * fUIPixelSize) - fScreenWidth;
				pUIMgr->cursor->node->m_kLocal.m_kTranslate.z = fScreenHeight - (fPosY * fUIPixelSize);
				*result = 1;
			}

			return true;
		}

		void InitHooks() {
			pbHUDCursorMode = reinterpret_cast<bool*>(JIPUtils::GetAddress(0x10076378));
			{
				CommandInfo* pInfo = const_cast<CommandInfo*>(g_cmdTableInterface->GetByOpcode(CommandOpcodes::kGetCursorPos));
				if (pInfo) {
					pInfo->params = kParams_OneAxis_OneOptionalInt;
					pInfo->numParams = 2;
					pInfo->execute = Cmd_GetCursorPos_Execute;
				}
			}
			{
				CommandInfo* pInfo = const_cast<CommandInfo*>(g_cmdTableInterface->GetByOpcode(CommandOpcodes::kSetCursorPos));
				if (pInfo) {
					pInfo->params = kParams_TwoFloats_OneOptionalInt;
					pInfo->numParams = 3;
					pInfo->execute = Cmd_SetCursorPos_Execute;
				}
			}
		}
	}

	namespace SetHotkeyItemRefFix {

		uint32_t uiJIPCreateExtraDataAddr;
		class JIPInventoryRef : public InventoryRef {
		public:
			ExtraDataList* CreateExtraData() {
				return ThisCall<ExtraDataList*>(uiJIPCreateExtraDataAddr, this);
			}
		};

		bool Cmd_GetHotkeyItemRef_Execute(COMMAND_ARGS) {
			int32_t iHotkey = 0;
			if (ExtractArgsEx(EXTRACT_ARGS_EX, &iHotkey) && iHotkey > 0) {
				const int32_t iCorrectedHotKey = iHotkey - 1;
				const InventoryChanges* pInvChanges = InventoryChanges::GetInventoryChanges(PlayerCharacter::GetSingleton());
				if (pInvChanges) {
					ItemChange* pHotkeyItem = pInvChanges->GetHotkeyItem(iCorrectedHotKey);
					if (pHotkeyItem) {
						ExtraDataList* pExtraList = pHotkeyItem->pExtraLists ? pHotkeyItem->pExtraLists->GetItem() : nullptr;
						TESObjectREFR* pInvRef = InventoryRefCreateEntry(PlayerCharacter::GetSingleton(), pHotkeyItem->pObject, pHotkeyItem->iNumber, pExtraList);
						if (pInvRef)
							*reinterpret_cast<uint32_t*>(result) = pInvRef->GetFormID();
					}

					delete pHotkeyItem;
				}
			}
			return true;
		}

        bool Cmd_SetHotkeyItemRef_Execute(COMMAND_ARGS) {
            int32_t iHotkey = 0;
            if (ExtractArgsEx(EXTRACT_ARGS_EX, &iHotkey) && iHotkey > 0) {
                InventoryRef* pInvRef = InventoryRefGetForID(thisObj->GetFormID());
                if (!pInvRef || pInvRef->pContainerRef != PlayerCharacter::GetSingleton())
                    return true;

                if (!pInvRef->pForm)
                    return true;

                const FORM_TYPE eFormType = pInvRef->pForm->GetFormType();
                if (eFormType != FORM_TYPE::TESObjectARMO && eFormType != FORM_TYPE::TESObjectWEAP && eFormType != FORM_TYPE::AlchemyItem && eFormType != FORM_TYPE::TESObjectBOOK)
                    return true;

                const int32_t iCorrectedHotKey = iHotkey - 1;

                InventoryChanges* pInvChanges = InventoryChanges::GetInventoryChanges(PlayerCharacter::GetSingleton());
                if (pInvChanges) {
                    ItemChange* pHotkeyItem = pInvChanges->GetHotkeyItem(iCorrectedHotKey);
                    if (pHotkeyItem)
                        pInvChanges->RemoveHotkeyItem(pHotkeyItem, iCorrectedHotKey);

                    ExtraDataList* pExtraList = pInvRef->pItemChange->pExtraLists ? pInvRef->pItemChange->pExtraLists->GetItem() : static_cast<JIPInventoryRef*>(pInvRef)->CreateExtraData();
					pInvChanges->SetHotkeyItem(pInvRef->pItemChange, pExtraList, iCorrectedHotKey);

                    if (InventoryMenu::GetSingleton())
                        InventoryMenu::GetSingleton()->kHotKeyWheel.UpdateHotkeyList();

                    delete pHotkeyItem;

                    *result = 1;
                }
            }
            return true;
        }

		void InitHooks() {
			uiJIPCreateExtraDataAddr = JIPUtils::GetAddress(0x10002A00);
			{
				CommandInfo* pInfo = const_cast<CommandInfo*>(g_cmdTableInterface->GetByOpcode(CommandOpcodes::kGetHotkeyItemRef));
				if (pInfo) {
					pInfo->execute = Cmd_GetHotkeyItemRef_Execute;
				}
			}
			{
				CommandInfo* pInfo = const_cast<CommandInfo*>(g_cmdTableInterface->GetByOpcode(CommandOpcodes::kSetHotkeyItemRef));
				if (pInfo) {
					pInfo->execute = Cmd_SetHotkeyItemRef_Execute;
				}
			}
		}
	}


	namespace TriggerLightningFXFix {

		bool Cmd_TriggerLightningFX_Execute(COMMAND_ARGS) {
			*result = 0;
			Sky* pSky = Sky::GetSingleton();
			if (pSky && pSky->GetIsRaining()) {
				pSky->fFlash = 1;
				pSky->uiFlashTime = TimeGlobal::GetSingleton()->uiLastTime;
				*result = 1;
			}
			return true;
		}

		void InitHooks() {
			CommandInfo* pInfo = const_cast<CommandInfo*>(g_cmdTableInterface->GetByOpcode(CommandOpcodes::kTriggerLightningFX));
			if (pInfo) {
				pInfo->execute = Cmd_TriggerLightningFX_Execute;
			}
		}
	}


	namespace LeveledListFixes {

		bool Cmd_LeveledListRemoveForm_Execute(COMMAND_ARGS) {
			*result = 0;
			TESForm* pListForm = nullptr;
			TESForm* pForm = nullptr;
			if (!ExtractArgsEx(EXTRACT_ARGS_EX, &pListForm, &pForm))
				return true;

			TESLeveledList* pList = TESLeveledList::GetFormAsLeveledList(pListForm);
			if (!pList || !pForm)
				return true;

			uint32_t uiDeletedCount = 0;
			auto pIter = pList->GetLeveledList();
			while (pIter && !pIter->IsEmpty()) {
				LeveledObject* pItem = pIter->GetItem();
				if (pItem && pItem->pForm == pForm) {

					auto pScriptIter = pList->kScriptAddedObjects.GetHead();
					while (pScriptIter && !pScriptIter->IsEmpty()) {
						auto pItem = pScriptIter->GetItem();
						if (pItem == pItem)
							pScriptIter->RemoveHead();
						pScriptIter = pScriptIter->GetNext();
					}

					delete pItem;
					pIter->RemoveHead();
					++uiDeletedCount;
				}
				else {
					pIter = pIter->GetNext();
				}
			}

			if (pList->kScriptAddedObjects.IsEmpty())
				pListForm->RemoveChange(0x80000000);

			*result = uiDeletedCount;
			return true;
		}

		bool Cmd_LeveledListClear_Execute(COMMAND_ARGS) {
			*result = 0;
			TESForm* pListForm = nullptr;
			if (!ExtractArgsEx(EXTRACT_ARGS_EX, &pListForm))
				return true;

			TESLeveledList* pList = TESLeveledList::GetFormAsLeveledList(pListForm);
			if (!pList)
				return true;

			uint32_t uiDeletedCount = 0;
			auto pIter = pList->GetLeveledList();
			while (pIter && !pIter->IsEmpty()) {
				LeveledObject* pItem =  pIter->GetItem();
				if (pItem) {
					auto pScriptIter = pList->kScriptAddedObjects.GetHead();
					while (pScriptIter && !pScriptIter->IsEmpty()) {
						auto pItem = pScriptIter->GetItem();
						if (pItem == pItem)
							pScriptIter->RemoveHead();
						pScriptIter = pScriptIter->GetNext();
					}

					delete pItem;
					pIter->RemoveHead();
					++uiDeletedCount;
				}
				else {
					pIter = pIter->GetNext();
				}
			}

			if (pList->kScriptAddedObjects.IsEmpty())
				pListForm->RemoveChange(0x80000000);

			*result = uiDeletedCount;
			return true;
		}

		bool Cmd_RemoveNthLevItem_Execute(COMMAND_ARGS) {
			*result = 0;
			TESForm* pListForm = nullptr;
			uint32_t uiIndex = 0;
			if (!ExtractArgsEx(EXTRACT_ARGS_EX, &pListForm, &uiIndex))
				return true;

			TESLeveledList* pList = TESLeveledList::GetFormAsLeveledList(pListForm);
			if (!pList)
				return true;

			auto pIter = pList->GetLeveledList();
			while (pIter && !pIter->IsEmpty()) {
				if (uiIndex == 0) {
					LeveledObject* pItem = pIter->GetItem();
					if (pItem) {
						auto pScriptIter = pList->kScriptAddedObjects.GetHead();
						while (pScriptIter && !pScriptIter->IsEmpty()) {
							auto pItem = pScriptIter->GetItem();
							if (pItem == pItem)
								pScriptIter->RemoveHead();
							pScriptIter = pScriptIter->GetNext();
						}

						delete pItem;
						pIter->RemoveHead();
						*result = 1;
					}
					break;
				}
				else {
					pIter = pIter->GetNext();
					--uiIndex;
				}
			}

			if (pList->kScriptAddedObjects.IsEmpty())
				pListForm->RemoveChange(0x80000000);

			return true;
		}

		void InitHooks() {
			{
				CommandInfo* pInfo = const_cast<CommandInfo*>(g_cmdTableInterface->GetByOpcode(CommandOpcodes::kLeveledListRemoveForm));
				if (pInfo) {
					pInfo->execute = Cmd_LeveledListRemoveForm_Execute;
				}
			}
			{
				CommandInfo* pInfo = const_cast<CommandInfo*>(g_cmdTableInterface->GetByOpcode(CommandOpcodes::kRemoveNthLevItem));
				if (pInfo) {
					pInfo->execute = Cmd_RemoveNthLevItem_Execute;
				}
			}
			{
				CommandInfo* pInfo = const_cast<CommandInfo*>(g_cmdTableInterface->GetByOpcode(CommandOpcodes::kLeveledListClear));
				if (pInfo) {
					pInfo->execute = Cmd_LeveledListClear_Execute;
				}
			}
		}
	}

	namespace ExtraDataFixes {

		// Credits to alex19ep for finding the bug and analysis

		constexpr uint32_t uiJIPExtraDataVersion = 2;

		static uint32_t uiReturnAddr;
		static uint32_t uiGiveUpAddr;
		static SPEC_NAKED void SanityCheck_Asm() {
			__asm {
				// If version is from the unpatched JIP, don't even bother
				// It's not possible to assess how much corrupted the save data is
				// As much as I'd like to attempt to recover it, after seeing affected cosaves, it's hopeless
				cmp		dword ptr[ebp - 0x28], 1
				je		GIVE_UP

				mov     edx, [ebp - 0x10]
				lea     ecx, [ebp - 0x14]
				jmp		uiReturnAddr;

				// Give up. Giving up is always easiest
			GIVE_UP:
				jmp		uiGiveUpAddr;
			}
		}

		void InitHooks() {
			uiReturnAddr = JIPUtils::GetAddress(0x10015B43);
			uiGiveUpAddr = JIPUtils::GetAddress(0x10015560);

			HookUtils::WriteRelJump(JIPUtils::GetAddress(0x10015B3D), SanityCheck_Asm);

			// Fix offset size
			HookUtils::SafeWrite8(JIPUtils::GetAddress(0x100167EA + 2), 0xC0);

			// Raise current version to 2
			HookUtils::SafeWrite8(JIPUtils::GetAddress(0x10015B33 + 3), uiJIPExtraDataVersion);
			HookUtils::SafeWrite8(JIPUtils::GetAddress(0x10016761 + 1), uiJIPExtraDataVersion);
		}
	}

	namespace GameSettingFix {

		struct SettingsMap {
			struct ALIGN8 Entry {
				Entry*		pNext;
				uint32_t    uiKey;
				Setting*	pData;
			};

			struct Bucket {
				Entry* pEntries;
			};

			Bucket*		pBuckets;
			uint32_t    uiSize;
			uint32_t    uiCount;
		};

		static constexpr uint32_t uiMapSize = 4096;
		SettingsMap* pGSMap = nullptr;

		STACK_FRAME_OPT_ENABLE

		uint32_t uiHashAddr;
		static inline uint32_t __fastcall StrHashCI(const char* apKey) {
			return FastCall<uint32_t>(uiHashAddr, apKey);
		}

		uint32_t uiAllocAddr;
		template<typename T>
		inline T* PoolAlloc(uint32_t auiCount = 1) {
			return FastCall<T*>(uiAllocAddr, sizeof(T) * auiCount);
		}

		static void InitializeMap() {
			MEMORY_CONTEXT(MC_STATIC_VARS);
			pGSMap->uiCount = 0;
			pGSMap->uiSize = uiMapSize;
			pGSMap->pBuckets = BSMemory::malloc<SettingsMap::Bucket>(uiMapSize);
			ZeroMemory(pGSMap->pBuckets, sizeof(SettingsMap::Bucket) * uiMapSize);
		}

		static void __fastcall AddGameSetting(Setting* apSetting) {
			ASSUME_ASSERT(pGSMap != nullptr);
			ASSUME_ASSERT(pGSMap->pBuckets != nullptr);

			const uint32_t uiHash = StrHashCI(apSetting->pKey);
			const uint32_t uiBucket = uiHash % uiMapSize;

			SettingsMap::Bucket* pBucket = &pGSMap->pBuckets[uiBucket];
			SettingsMap::Entry* pEntry = PoolAlloc<SettingsMap::Entry>();
			pEntry->pData = apSetting;
			pEntry->uiKey = uiHash;
			pEntry->pNext = pBucket->pEntries;
			pBucket->pEntries = pEntry;
			++pGSMap->uiCount;
		}

		HookUtils::CallDetour kRegisterGameSetting;
		class Hook {
		public:
			void RegisterGameSetting(const char* apKey, Setting* apSetting) {
				AddGameSetting(apSetting);
				ThisCall(kRegisterGameSetting, this, apKey, apSetting);
			}
		};

		STACK_FRAME_OPT_RESET

		void InitHooks() {
			uiHashAddr = JIPUtils::GetAddress(0x100010F0);
			uiAllocAddr = JIPUtils::GetAddress(0x10003C80);

			HookUtils::PatchMemoryNop(JIPUtils::GetAddress(0x10011B13), 2);

			pGSMap = reinterpret_cast<SettingsMap*>(JIPUtils::GetAddress(0x1006FF84));
			InitializeMap();

			kRegisterGameSetting.ReplaceCall(0x404E87, &Hook::RegisterGameSetting);
		}
	}

	namespace EDIDLookupFix {

		STACK_FRAME_OPT_ENABLE
		TESForm* __fastcall GetEDID(void* apThis, const char* apEDID) {
			return TESForm::GetFormByEditorID(apEDID);
		}
		STACK_FRAME_OPT_RESET

		void InitHooks() {
			HookUtils::ReplaceCall(JIPUtils::GetAddress(0x1000178C), GetEDID);
			HookUtils::ReplaceCall(JIPUtils::GetAddress(0x10002E25), GetEDID);
			HookUtils::ReplaceCall(JIPUtils::GetAddress(0x10009ACB), GetEDID);
		}
	}

	namespace SanerWeaponWobbleHook {

		HookUtils::CallDetour kGetGunSpreadDetour;
		STACK_FRAME_OPT_ENABLE
		class Hook : public Actor {
		public:
			float GetGunSpreadHook(enum SpreadMode aeMode) {
				if (jipActorFlags2 & 8)
					return 0.f;

				return ThisCall<float>(kGetGunSpreadDetour, this, aeMode);
			}
		};
		STACK_FRAME_OPT_RESET

		void InitHooks() {
			HookUtils::PatchMemoryNopRange(JIPUtils::GetAddress(0x1000BA54), JIPUtils::GetAddress(0x1000BA63));
			kGetGunSpreadDetour.ReplaceCall(0x524019, &Hook::GetGunSpreadHook);
		}
	}

	namespace ProjectileLightFix {

		uint32_t uiCreateJIPLightAddr;
		HookUtils::CallDetour kFreeLightDetour;
		class Hook {
		public:
			NiAVObject* GenDynamic(TESObjectREFR* apRequester, BSFadeNode* apNode, bool abForceDynamic) {
				TESObjectLIGH* pLight = reinterpret_cast<TESObjectLIGH*>(this);
				NiNode* pLightNode = apNode;
				NiAVObject* pAttach = BSUtilities::GetObjectByName(apNode, FixedStrings::GetAttachLight());
				if (pAttach && pAttach->IsNode())
					pLightNode = static_cast<NiNode*>(pAttach);
				return FastCall<NiAVObject*>(uiCreateJIPLightAddr, this, pLightNode);
			}

			void FreeLight(void* apNewVal) {
				NiLight* pLight = reinterpret_cast<NiPointer<NiLight>*>(this)->m_pObject;
				NiNode* pParent = pLight->GetParent();
				if (pParent)
					pParent->DetachChild(pLight);
				ThisCall(kFreeLightDetour, this, apNewVal);
			}
		};

		void InitHooks() {
			uiCreateJIPLightAddr = JIPUtils::GetAddress(0x10009B80);
			HookUtils::PatchMemoryNopRange(JIPUtils::GetAddress(0x100127E0), JIPUtils::GetAddress(0x100127FE));

			HookUtils::ReplaceCall(0x9C3DF5, &Hook::GenDynamic);
			kFreeLightDetour.ReplaceCall(0x9C3E54, &Hook::FreeLight);
		}
	}

	namespace LogMover {

		void InitHooks() {
			// We're using JIP's fs functions to avoid issues with our Debug build's imports
			using pfn_fclose = int(__cdecl*)(FILE*);
			using pfn_fsopen = FILE*(__cdecl*)(const char*, const char*, int);
			using pfn_PrintLog = void(__cdecl*)(const char*, ...);

			pfn_fclose fclose = *reinterpret_cast<pfn_fclose*>(JIPUtils::GetAddress(0x1005C1A8));
			pfn_fsopen fsopen = *reinterpret_cast<pfn_fsopen*>(JIPUtils::GetAddress(0x1005C180));
			FILE** pLog = reinterpret_cast<FILE**>(JIPUtils::GetAddress(0x1006A388));
			if (!pLog[0] || fclose(pLog[0]))
				return;

			if (MoveFileEx("jip_ln_nvse.log", "logs\\jip_ln_nvse.log", MOVEFILE_REPLACE_EXISTING)) {
				pLog[0] = fsopen("logs\\jip_ln_nvse.log", "a+b", _SH_DENYWR);
				pfn_PrintLog PrintLog = reinterpret_cast<pfn_PrintLog>(JIPUtils::GetAddress(0x10006740));
				PrintLog("JohnnyGuitar Fixes and Tweaks initialized");
			}
		}

	}

	namespace VersionPrint {

		const char cVersionString[] = "JIP LN version: %.2f + JohnnyGuitar Fixes and Tweaks";

		void InitHooks() {
			HookUtils::SafeWrite32(JIPUtils::GetAddress(0x1001359D) + 1, size_t(&cVersionString));
		}

	}

	void InitData() {
		JIPUtils::Init();
	}

	void InitEarlyHooks(bool abGECK) {
		if (!JIPUtils::IsValid())
			return;

		if (abGECK) {
			LogMover::InitHooks();
		}
		else {
			JIPSettings::InitConditionalHooks();
			EarlyFixedStrings::InitHooks();
			GameSettingFix::InitHooks();
			LogMover::InitHooks();
			VersionPrint::InitHooks();
			SanerWeaponWobbleHook::InitHooks();
			ProjectileLightFix::InitHooks();
		}
	}

	void InitHooks(bool abGECK) {
		if (!JIPUtils::IsValid())
			return;

		if (abGECK) {

		}
		else {
			UpdateDataFix::InitHooks();
			ConsoleCmdFix::InitHooks();
			PaletteCorruptionFix::InitHooks();
			NotifyDurationFix::InitHooks();
			CloseActiveMenuFix::InitHooks();
			FireWeaponFix::InitHooks();
			ItemDescriptionFixFix::InitHooks();
			ModelReloadFix::InitHooks();
			PerkEntryFix::InitHooks();
			WeaponModEffectsFix::InitHooks();
			OnMenuClickFix::InitHooks();
			GetMenuItemListRefsFix::InitHooks();
			WaterRenderFix::InitHooks();
			GetSelectedItemRefFix::InitHooks();
			Update3DTweak::InitHooks();
			AddItemAltNoCond::InitHooks();
			ExtraDataFixes::InitHooks();
			EDIDLookupFix::InitHooks();
		}
	}

	void InitCommandHooks(bool abGECK) {
		if (!JIPUtils::IsValid())
			return;

		SetOnDialogTopicEventHandlerEx::InitHooks(abGECK);
		RespawnDisableFix::InitHooks(abGECK);
		CopyFaceGenFromFix::InitHooks();
		SoundSourceFileFix::InitHooks();
		BetterSearch::InitHooks();
		PowerArmorCondition::InitHooks();
		LeveledListFixes::InitHooks();
		CursorPosUICords::InitHooks();
		TriggerLightningFXFix::InitHooks();
		SetHotkeyItemRefFix::InitHooks();

	}

	void InitDeferredHooks(bool abGECK) {
		if (!JIPUtils::IsValid())
			return;

		if (abGECK) {
		}
		else {
		}
	}
}
