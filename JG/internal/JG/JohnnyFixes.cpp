#include "JohnnyFixes.hpp"
#include "EditorIDRestoration.hpp"
#include "CloudUpdateFix.hpp"
#include "CustomCameraShake.hpp"
#include "NPCAccuracy.hpp"
#include "DialogueResponseOverride.hpp"
#include "QuestObjectiveDisplayFix.hpp"
#include "GameForms.h"
#include "GameProcess.h"
#include <GameSettings.h>
#include "GameUI.h"

namespace JohnnyFixes {
	float vatsSpreadMultValue = 15.0;
	void(__thiscall* OriginalBipedModelUpdateWeapon)(BipedAnim*, TESObjectWEAP*, int) = (void(__thiscall*)(BipedAnim*, TESObjectWEAP*, int)) 0x4AB400;
	uint8_t(__thiscall* ItemChange_GetWeaponModFlags)(ItemChange* weapEntry) = (uint8_t(__thiscall*)(ItemChange*)) 0x4BD820;


	__declspec(naked) void InventoryAmmoHook() {
		static const uint32_t retnAddr = 0x7080A8;
		__asm {
			mov ecx, dword ptr[ebp - 0x2D4]
			call TESObjectWEAP::GetAmmoInInventory
			mov dword ptr[ebp - 0x2C8], eax
			jmp retnAddr
		}
	}

	tList<TESAmmoEffect>* __fastcall GetAmmoEffectsCheckType(TESForm* form)
	{
		if (IS_TYPE(form, TESAmmo))
		{
			return &((TESAmmo*)form)->effectList;
		}
		return nullptr;
	}

	__declspec(naked) void OnCloseContainerHook() {
		static const uint32_t retnAddr = 0x75B240;
		__asm
		{
			push    ecx
			mov     ecx, [ecx + 0x74]
			test    ecx, ecx
			jz      done
			mov     eax, [ecx]
			call    dword ptr[eax + 0x100]
			test    al, al
			jz      done
			mov     word ptr[ecx + 0x7C], 1
			done:
			pop     ecx
				jmp     retnAddr
		}
	}

	float* __fastcall VATSSpreadMultHook(void* ecx) {
		return &vatsSpreadMultValue;
	}

	void patchFixDisintegrationsStat() {
		// check if user has Unnecessary Tweaks or lStewieAl's Tweaks installed
		if (*(uint8_t*)0x8A1B4D == 0xE9 || *(uint8_t*)0x8A1B51 == 0x26) return;
		// critical stage 1, jump to checks for IncPCMiscStat
		SafeWrite8(0x8A1B51, 0x26); // change JE offset

		// critical stage 3, jump to checks for IncPCMiscStat
		SafeWriteBuf(0x8A1B1B, "\xF9\x01\x74\x12\x83\xF9\x02\x74\x30\x83\xF9\x04\x74\x2B\x83\xF9\x03\x74\x4A\xEB\x22\x90", 22);

		// critical stages 2 and 4, skip IncPCMiscStat
		SafeWriteBuf(0x8A1B6E, "\x82\xC0\x01\x00\x00\xFF\xD0\xEB\x53\x90", 10);
	}

	__declspec(naked) void NPCIncrementingChallengesHook() {
		static const uint32_t retnAddr = 0x88D0D8;
		static const uint32_t noIncrementAddr = 0x88D100;
		__asm {
			mov eax, [ebp - 0x80]
			cmp eax, dword ptr ds : [0x11DEA3C]
			jz INCREMENT
			jmp noIncrementAddr
			INCREMENT :
			push 0
				push 0
				push 0
				push 0
				jmp retnAddr
		}
	}
	void __fastcall BipedModelUpdateWeapon(BipedAnim* BipedAnim, Character* fnCharacter, TESObjectWEAP* weap, int weapMods) {
		if (fnCharacter && fnCharacter->baseProcess) {
			if (auto weapInfo = fnCharacter->baseProcess->GetWeaponInfo()) {
				weapMods = ItemChange_GetWeaponModFlags(weapInfo);
			}
		}
		OriginalBipedModelUpdateWeapon(BipedAnim, weap, weapMods);
	}

	__declspec (naked) void BipedModelUpdateWeaponHook() {
		__asm
		{
			mov edx, dword ptr[ebp + 0x8]
			jmp BipedModelUpdateWeapon
		}
	}

	Setting* __fastcall GetINISettingHook(INISettingCollection* ini, void* edx, char* name) {
		Setting* result = ThisCall<Setting*>(0x5E02B0, ini, name);
		if (result) return result;
		RendererSettingCollection* rendererSettings = SettingT<RendererSettingCollection>::GetCollection();
		if (rendererSettings && !rendererSettings->kSettings.IsEmpty()) {
			auto iter = rendererSettings->kSettings.GetHead();
			while (iter && !iter->IsEmpty()) {
				Setting* pSetting = iter->GetItem();
				iter = iter->GetNext();
				if (_stricmp(pSetting->pKey, name) == 0) {
					return pSetting;
				}
			}
		}
		return nullptr;
	}

	bool __fastcall SaveINIHook(INISettingCollection* a1, void* edx, char* a2) {
		ThisCall(0x5E01B0, a1, a2);
		RendererSettingCollection* rendererSettings = SettingT<RendererSettingCollection>::GetCollection();
		return ThisCall<bool>(0x5E01B0, rendererSettings, rendererSettings->cSettingFile);
	}

	void __stdcall HandleSettingType(Setting* setting, Setting::Type type) {
		switch (type) {
		case Setting::kSetting_Bool:
			if (IsConsoleMode()) Console_Print("INISetting %s >> %i", setting->pKey, setting->uValue.b);
			break;
		case Setting::kSetting_Integer:
			if (IsConsoleMode()) Console_Print("INISetting %s >> %d", setting->pKey, setting->uValue.i);
			break;
		case Setting::kSetting_Unsigned:
			if (IsConsoleMode()) Console_Print("INISetting %s >> %X", setting->pKey, setting->uValue.u);
			break;
		case Setting::kSetting_Float:
			if (IsConsoleMode()) Console_Print("INISetting %s >> %.2f", setting->pKey, setting->uValue.f);
			break;
		case Setting::kSetting_String:
			if (IsConsoleMode()) Console_Print("INISetting %s >> '%s'", setting->pKey, setting->uValue.str);
			break;
		case Setting::kSetting_r:
			if (IsConsoleMode()) Console_Print("INISetting %s >> R: %d G: %d B: %d", setting->pKey, setting->uValue.rgb[3], setting->uValue.rgb[2], setting->uValue.rgb[1]);
			break;
		case Setting::kSetting_a:
			if (IsConsoleMode()) Console_Print("INISetting %s >> R: %d G: %d B: %d alpha: %d", setting->pKey, setting->uValue.rgb[3], setting->uValue.rgb[2], setting->uValue.rgb[1], setting->uValue.rgb[0]);
			break;
		default:
			if (IsConsoleMode()) Console_Print("INISetting %s >> UNKNOWN TYPE", setting->pKey);
			break;
		}
	}

	__declspec(naked) void GetINISettingTypeHook() {
		__asm {
			push eax
			mov eax, dword ptr ds : [ebp - 4]
			push eax
			call HandleSettingType
			mov eax, 0x5BEE5D
			jmp eax
		}
	}

	bool __fastcall MenuGetFlagHook(StartMenu* menu, uint32_t flags) {
		return menu != nullptr ? ((flags & menu->flags) != 0) : false;
	}

	void __fastcall MenuSetFlagHook(StartMenu* menu, uint32_t flags, bool doSet) {
		if (menu != nullptr) {
			if (doSet) {
				menu->flags |= flags;
			}
			else {
				menu->flags &= ~flags;
			}
		}
	}

	void __fastcall TESRegionDataSoundIncidentalIDHook(TESFile* info, void* edx, uint32_t* refID) {
		ThisCall(0x4727F0, info, refID);
		if (*refID) {
			CdeclCall(0x485D50, refID, info);
		}
	}

	__declspec (naked) void StimpakHotkeyHook() {
		__asm {
			xor eax, eax
			test ecx, ecx
			jz doneLabel
			mov eax, dword ptr ds : [ecx + 0x8]
			doneLabel :
			ret
		}
	}

	__declspec (naked) void SimpleDecalHook() {
		__asm {
			test eax, eax
			jz done
			mov dword ptr[ebp - 0x128], eax
			mov dword ptr[ebp - 0x130], 0
			mov eax, 0x68D30C
			jmp eax
			done :
			mov eax, 0x68D64B
				jmp eax
		}
	}

	__declspec (naked) void AnimDataNullCheck() {
		__asm {
			push 0x0490BD8
			mov eax, dword ptr[ebp - 0xA4]
			test eax, eax
			jz retNoData
			push dword ptr[ebp - 0xAC]
			mov ecx, eax
			mov eax, dword ptr[eax]
			mov eax, dword ptr[eax + 0x9C]
			call eax
			retNoData :
			ret
		}
	}

	__declspec (naked) void NiContManNullCheck2() {
		__asm {
			test ecx, ecx
			jnz continueFunc
			xor eax, eax
			ret 8
			continueFunc:
			mov eax, 0xA2E7D0
				jmp eax
		}
	}

	bool __cdecl IsCurrentFurnitureRefHook(TESObjectREFR* apRef, void* apComparedRef, int, double& arResult) {
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

	char* __cdecl fixAudioMonoLookupOverflow(char* Dst, const char* suffix) {
		char subBuf[MAX_PATH] = {};
		if (!strstr(Dst, suffix)) {
			if (auto subchr = strrchr(Dst, '.')) {
				strcpy_s(subBuf, MAX_PATH, subchr + 1);
				*subchr = '\0';
				strcat_s(Dst, MAX_PATH, suffix);
				strcat_s(Dst, MAX_PATH, subBuf);
			}
		}
		return Dst;
	}

	void __fastcall SetCellImageSpaceHook(TESObjectCELL* cell, void* edx, TESImageSpace* imageSpace) {


		ThisCall<void>(0x547750, cell, imageSpace);
		PlayerCharacter* player = PlayerCharacter::GetSingleton();
		if (player->parentCell != nullptr && player->parentCell == cell) {
			CdeclCall<void>(0xB4F430, imageSpace->traitValues);
		}
	}

	bool __fastcall CanSpeakThroughHead(Actor* actor) {
		bool res = !(ThisCall<bool>(0x573090, actor, BGSBodyPartData::eBodyPart_Head1)) && !(ThisCall<bool>(0x573090, actor, BGSBodyPartData::eBodyPart_Head2));
		if (res) {
			res = [](Actor* actor) -> bool {
				if (auto thisObj = actor->baseProcess; thisObj->processLevel <= 0) {
					if (actor->GetDead()) {
						if (DialoguePackage* pPackage = (DialoguePackage*)thisObj->GetCurrentPackage()) {
							if ((actor != pPackage->subject) && (actor == pPackage->speaker)) { //check for subject because in some cases, subject == target
								return false;
							}
						}
					}
				}
				return true;
				}(actor);
		}
		return res;
	}

	__declspec (naked) void NoHeadlessTalkingHook() {
		__asm {
			mov eax, dword ptr ds : [ecx + 0x68] //The original call, GetBaseProcess
			test eax, eax
			jz done
			push eax
			mov ecx, dword ptr ds : [ebp + 8]
			call CanSpeakThroughHead
			test al, al
			pop eax
			jnz done
			xor eax, eax
			align 0x10
			done:
			retn
		}
	}

	void ClearPlayerFurniture()
	{
		if (auto playerProcess = PlayerCharacter::GetSingleton()->baseProcess)
		{
			playerProcess->SetFurnitureRef(PlayerCharacter::GetSingleton(), 0, NULL, 0x7F);

		}
	}

	void Init() {
		// for Runtime EDIDs
		EDIDRestoration::InitHooks();
		// use available ammo in inventory instead of NULL when default ammo isn't present
		WriteRelJump(0x70809E, (uint32_t)InventoryAmmoHook);

		// fix ammo effects list being checked for non-TESAmmo's when the Rock-It-Launcher is equipped
		for (auto addr : { 0x523AD8, 0x64529D, 0x64553B, 0x6462C5 })
		{
			WriteRelCall(addr, uint32_t(GetAmmoEffectsCheckType));
		}

		// fix for companions not saying the next topic after opening ContainerMenu through dialog
		SafeWrite32(0x10721AC, (uint32_t)OnCloseContainerHook);

		// replace fNPCMaxWobbleAngle with 15.0 for VATS
		WriteRelCall(0x8B102B, (uint32_t)VATSSpreadMultHook);

		// Fix for animations not working in dialog topics with sound
		PatchMemoryNop(0x8A56C4, 4);
		PatchMemoryNop(0x8A56C8, 4);

		// fix Disintegrations stat not incrementing properly
		patchFixDisintegrationsStat();

		// fix NPCs incrementing player challenges
		WriteRelJump(0x88D0D0, (uint32_t)NPCIncrementingChallengesHook);

		// use correct weapon skill req penalty setting in weapon spread calculation
		SafeWriteBuf(0x647902 + 1, "\xC8\xEA\x1C\x01", 4);

		// fix for various biped model update bugs
		WriteRelCall(0x06061E8, (uintptr_t)BipedModelUpdateWeaponHook);

		// missing nullcheck in NiMultiTargetTransformController::RemoveNodeRecurse
		SafeWrite8(0x4F064E, 0x7A);

		// fix for Get/Set/SaveINISetting not reading renderer INI setting list
		WriteRelCall(0x5BED66, (uint32_t)GetINISettingHook);
		WriteRelCall(0x5BEF13, (uint32_t)GetINISettingHook);
		WriteRelCall(0x5B6C80, (uint32_t)SaveINIHook);

		WriteRelJump(0x5BED86, (uint32_t)GetINISettingTypeHook);

		// fixes for null pointers when showing credits outside of start menu
		WriteRelCall(0x75F770, (uint32_t)MenuGetFlagHook);
		WriteRelCall(0x75F8AE, (uint32_t)MenuSetFlagHook);
		WriteRelCall(0x75F6DA, (uint32_t)MenuSetFlagHook);

		// missing nullcheck in HandleStealing
		SafeWriteBuf(0x8BFBC1, "\x85\xC9\x74\x36\x80\x79\x04", 7);

		// fix for incidental sounds not working in regions
		WriteRelCall(0x4F49AB, uint32_t(TESRegionDataSoundIncidentalIDHook));

		// fix for the stimpak crash
		WriteRelCall(0x7DB525, (uintptr_t)StimpakHotkeyHook);
		// Fix crash caused by wrong check inside AddSequence (thanks Stewie!)
		SafeWrite8(0xA2F0CB, 0x3A);
		//And also fix ANOTHER crash nearby caused by ANOTHER faulty nullptr check... this removes a DebugLog, but i don't care.
		WriteRelJump((uintptr_t)0x0490B10, (uintptr_t)0x0490B41);

		// fix NPE in BSTempEffectSimpleDecal
		WriteRelJump(0x68D2EB, (uint32_t)SimpleDecalHook);


		// Fix for missing baseprocess null check
		WriteRelJump(0x59DF40, (uint32_t)IsCurrentFurnitureRefHook);

		//AnimData NPEs
		//fix NPE in AnimData freeing
		WriteRelJump(0x0490BBB, (uintptr_t)AnimDataNullCheck);
		WriteRelCall(0x0A2EC64, (uintptr_t)NiContManNullCheck2);

		CloudUpdateFix::Install();

		//Stop game from crashing on extensions reeeeeeeeeee
		WriteRelCall(0x83509D, (uintptr_t)fixAudioMonoLookupOverflow);

		CustomCameraShake::Hook();
		NPCAccuracy::Install();
		DialogueResponseOverride::Install();

		QuestObjectiveDisplayFix::Install();

		WriteRelCall(0x5B7812, (uint32_t)SetCellImageSpaceHook);

		//Patch the game so the dialog subroutine stops if the actor's head is blown off, I'll add it as an ini setting later.
		WriteRelCall(0x8EC54D, (uintptr_t)NoHeadlessTalkingHook);
	}

}