#pragma once
#include <unordered_set>
#include <unordered_map>

#include "JG/JohnnyGameSettings.hpp"
#include <JG/DialogueResponseOverride.hpp>
#include <JG/ExtraReputationIcons.hpp>
#include <JG/ExtraMiscStats.hpp> 
#include <JG/RSMBarberHook.hpp> 
#include <JG/BarterFilter.hpp> 
#include <JG/ExtraUISounds.hpp> 
#include <JG/NPCAccuracy.hpp>
#include <JG/JohnnyPatches.hpp>
#include <JG/CustomCameraShake.hpp>
#include <PluginAPI.h>
#include "nvse/GameProcess.h"
#include "misc/WorldToScreen.h"
#include "JG/EditorIDRestoration.hpp"
#include "internal/decoding.h"


#define REG_CMD(name) nvse->RegisterCommand(&kCommandInfo_##name);
#define REG_TYPED_CMD(name, type) nvse->RegisterTypedCommand(&kCommandInfo_##name,kRetnType_##type);

extern NVSEArrayVarInterface* g_arrInterface;
extern NVSEStringVarInterface* g_strInterface;
extern NVSEMessagingInterface* g_msg; 
extern NVSEScriptInterface* g_scriptInterface;
extern NVSECommandTableInterface* g_cmdTableInterface;
extern InventoryRef* (*InventoryRefGetForID)(uint32_t refID);
extern void (*ApplyPerkModifiers)(PerkEntryPointID entryPointID, TESObjectREFR* perkOwner, void* arg3, ...);
extern bool (*ExtractArgsEx)(COMMAND_ARGS_EX, ...);
extern std::unordered_map<uint8_t, float> shakeRequests;
extern float(*GetWeaponDPS)(ActorValueOwner* avOwner, TESObjectWEAP* weapon, float condition, uint8_t arg4, ContChangesEntry* entry, uint8_t arg6, uint8_t arg7, int arg8, float arg9, float arg10, uint8_t arg11, uint8_t arg12, TESForm* ammo);
extern uint32_t g_initialTickCount;
extern GameTimeGlobals* g_gameTimeGlobals;
extern StatsMenu* g_statsMenu;
extern std::unordered_set<DWORD> jg_gameRadioSet;
extern float g_viewmodel_near;
extern bool mlcOverridden;
extern MediaLocationController* mlcOverride;
extern std::unordered_set<BYTE> SaveGameUMap;

static float vatsSpreadMultValue = 15.0;

void(__thiscall* OriginalBipedModelUpdateWeapon)(BipedAnim*, TESObjectWEAP*, int) = (void(__thiscall*)(BipedAnim*, TESObjectWEAP*, int)) 0x4AB400;
uint8_t(__thiscall* ContChangesEntry_GetWeaponModFlags)(ContChangesEntry* weapEntry) = (uint8_t(__thiscall*)(ContChangesEntry*)) 0x4BD820;

uintptr_t g_canSaveNowAddr = 0;
uintptr_t g_canSaveNowMenuAddr = 0;




extern "C" {
	bool __cdecl JGSetViewmodelClipDistance(float value);
	float __cdecl JGGetViewmodelClipDistance();
}

NiVector3 kCameraPos;
NiMatrix3 kCameraRot = NiMatrix3::IDENTITY;
NiMatrix3 kCameraIdentity = NiMatrix3(0, 0, 1,
									  1, 0, 0,
									  0, 1, 0);
uint32_t uiReferenceToTrack = 0;
bool bOverrideCameraPos = false;
bool bOverrideCameraRot = false;
int eAxis = -3;



void __fastcall SetCameraTranslateHook(NiNode* apThis, void*, NiVector3& arPos) {
	PlayerCharacter* pPlayer = PlayerCharacter::GetSingleton();
	if (bOverrideCameraPos && pPlayer->IsThirdPerson())
		arPos = kCameraPos;

	apThis->SetLocalTranslate(arPos);
}

void __fastcall SetCameraRotateHook(NiNode* apThis, void*, NiMatrix3& arRot) {
	PlayerCharacter* pPlayer = PlayerCharacter::GetSingleton();
	NiCamera* pCamera = (NiCamera*)apThis->GetAt(0);
	if (eAxis == kCameraRotationType_Reset) {
		kCameraRot = arRot;
	}
	else if (bOverrideCameraRot && pPlayer->IsThirdPerson()) {
		if (eAxis == kCameraRotationType_TrackTarget) {
			TESForm* pForm = TESForm::GetFormByNumericID(uiReferenceToTrack);
			if (pForm->IsReference() && pCamera) {
				TESObjectREFR* pTrackRef = (TESObjectREFR*)pForm;
				NiNode* pRootNode = pTrackRef->Get3D();
				NiVector3 kPos;
				if (pRootNode && pRootNode->m_pWorldBound && pRootNode->m_pWorldBound->iRadius) {
					kPos = pRootNode->m_pWorldBound->kCenter;
				}
				else {
					kPos = *(NiVector3*)pTrackRef->GetPos();
				}

				pCamera->m_parent = nullptr;
				pCamera->LookAtWorldPoint(kPos, NiVector3(0, 0, 1));
				pCamera->m_parent = apThis;
				apThis->SetLocalRotate(pCamera->m_local.rotate);
				pCamera->SetLocalRotate(NiMatrix3::IDENTITY);
			}
		}
		else {
			apThis->SetLocalRotate(kCameraRot);
		}
		return;
	}
	else {
		pCamera->SetLocalRotate(kCameraIdentity);
	}

	apThis->SetLocalRotate(arRot);
}

namespace hk_CombatLocation
{

	template <uintptr_t a_addr>
	class hk_CombatLocationMaxCall {
	private:
		static inline uintptr_t hookCall = a_addr;
	public:
		static  float __cdecl hk_CLCHook(float m_a1, float m_a2) {
			auto res = CdeclCall<float>(hookCall, m_a1, m_a2);
			return fmax(res, JohnnyGameSettings::fCombatLocationTargetRadiusMaxBase.Float());
		}

		hk_CombatLocationMaxCall() {
			uintptr_t hk_hookPoint = hookCall;
			hookCall = GetRelJumpAddr(hookCall);
			WriteRelCall(hk_hookPoint, (uintptr_t)hk_CLCHook);
		}
	};

	template <uintptr_t a_addr>
	class hk_CombatRangedRangeMult {
	private:
		static inline uintptr_t hookCall = a_addr;
	public:
		static  float __fastcall hk_Hook(TESObjectWEAP* r_weap) {
			auto res = ThisCall<float>(hookCall, r_weap);
			if (!ThisCall<bool>(0x0647790, r_weap) && ThisCall<bool>(0x04C0C30, r_weap)) {
				res *= JohnnyGameSettings::fCombatRangedWeaponRangeBaseMult.Float();
			}
			return res;
		}

		hk_CombatRangedRangeMult() {
			uintptr_t hk_hookPoint = hookCall;
			hookCall = GetRelJumpAddr(hookCall);
			WriteRelCall(hk_hookPoint, (uintptr_t)hk_Hook);
		}
	};


	void CombatLocationMaxRadiusBaseInitHook() { //Thanks lStewieAl
		hk_CombatLocationMaxCall<0x09A089F>();
		hk_CombatLocationMaxCall<0x09A0A0C>();
		hk_CombatRangedRangeMult<0x09A91C1>();


	}

}

template <uintptr_t a_addr>
class hk_QuestObjectiveIsDisplayedCall {
private:
	static inline uintptr_t hPreviousAddressHook = 0;
public:
	static  uintptr_t __fastcall hookObjectiveDisplayed(BGSQuestObjective* pObjective) {
		DWORD result = 1;
		if (hPreviousAddressHook)
		{
			result = ThisCall<uintptr_t>(hPreviousAddressHook, pObjective);
		}
		if (result)
		{
			result = pObjective->status & BGSQuestObjective::eQObjStatus_displayed;
			auto questObjectiveDisplayStr = pObjective->displayText.c_str();
			auto questDisplayStr = TESFullName::GetFullName(pObjective->quest);
			if (!((questObjectiveDisplayStr && *questObjectiveDisplayStr) || (questDisplayStr && *questDisplayStr)))
			{
				result = 0;
			}
		}

		return result;
	}
	hk_QuestObjectiveIsDisplayedCall() {
		if (*(char*)a_addr == 0xE9) //there's a jump here, so detour it
		{
			hPreviousAddressHook = GetRelJumpAddr(a_addr);
		}
		WriteRelJump((a_addr), (uintptr_t)hookObjectiveDisplayed);
	}

};


template <uintptr_t a_addr>
class hk_EmotionOverrideUndo
{
	static void* __fastcall hk_UndoEmotionOverride(void** ptr)
	{
		auto retVal = ThisCall<void*>(hookCall, ptr);
		if (JohnnyGameSettings::iOverrideDialogueEmotionValues.Int() <= 0)
		{
			retVal = nullptr;
		}
		return retVal;
	}
	static inline uintptr_t hookCall = a_addr;
public:
	hk_EmotionOverrideUndo() {
		uintptr_t hk_hookPoint = hookCall;
		hookCall = GetRelJumpAddr(hookCall);
		WriteRelCall(hk_hookPoint,(uintptr_t) (hk_UndoEmotionOverride));
	}
};


namespace SkyCloudHook {
	static DWORD completedFirstUpdate = 0;
	bool __fastcall hk_han_SkipCloudCheck(TESWeather* a_wea) {
		if (completedFirstUpdate < 2 || !a_wea ) {
			completedFirstUpdate = 1;
			return false;
		}
		return true;

	}

	static uintptr_t fn_Clouds_Update = 0;
	DWORD __fastcall hk_Clouds_Upd (void* a_cloud, void* edx, void* Sky, float timePassed) {
		auto ret = ThisCall<DWORD>(fn_Clouds_Update, a_cloud, Sky, timePassed);
		if (completedFirstUpdate == 1) {
			completedFirstUpdate = 2;
		}
		return ret;
	}
	__declspec(naked) void asm_HookCloudCheck() {
		static uintptr_t jmpRet = 0x06346F9;
		static uintptr_t jneRet = 0x0634740;
		__asm {
			mov ecx, dword ptr[ebp - 0x14]
			call hk_han_SkipCloudCheck
			test al, al
			jne skip
			jmp jmpRet
			ALIGN 16
			skip:
			jmp jneRet
		}
	}
	void InstallCloudUpdHook() {
		SafeWrite8(0x06346F3, 0x90);
		WriteRelJump(0x06346F4, (uintptr_t)SkyCloudHook::asm_HookCloudCheck);
		SkyCloudHook::fn_Clouds_Update = *(uintptr_t*)0x104EC14;
		SafeWrite32(0x104EC14, (uintptr_t)SkyCloudHook::hk_Clouds_Upd);
	}

	DWORD __fastcall hk_han_NewGameCloudUpdate(BGSSaveLoadGame* a_obj) {
		return ThisCall<bool>(0x42CE10, a_obj) || (*(bool*)0x11D8907);

	}

}


TESObjectCELL* TESObjectREFR::GetParentCell() {
	if (this->parentCell) return parentCell;
	ExtraPersistentCell* xPersistentCell = (ExtraPersistentCell*)this->extraDataList.GetByType(kExtraData_PersistentCell);
	if (xPersistentCell && xPersistentCell->persistentCell) return xPersistentCell->persistentCell;
	return nullptr;
}





ContChangesEntry* ExtraContainerChanges::EntryDataList::FindForItem(TESForm* item) {
	ListNode<ContChangesEntry>* iter = this->Head();

	do {
		if (iter->data && iter->data->type == item) return iter->data;
	} while (iter = iter->next);

	return nullptr;
}


bool __fastcall CanSaveNowHook(void* ThisObj, void* edx, int isAutoSave) {
	return ThisCall<bool>(g_canSaveNowAddr, ThisObj, isAutoSave) && SaveGameUMap.empty();
}

bool __fastcall CanSaveNowMenuHook(void* ThisObj, void* edx, int isAutoSave) {
	return ThisCall<bool>(g_canSaveNowMenuAddr, ThisObj, isAutoSave) && SaveGameUMap.empty();
}

void __fastcall BipedModelUpdateWeapon(BipedAnim* BipedAnim, Character* fnCharacter, TESObjectWEAP* weap, int weapMods) {
	if (fnCharacter && fnCharacter->baseProcess) {
		if (auto weapInfo = fnCharacter->baseProcess->GetWeaponInfo()) {
			weapMods = ContChangesEntry_GetWeaponModFlags(weapInfo);
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

bool(__thiscall* GetPlayerInCombat)(Actor*, bool& IsNotDetected) = (bool(__thiscall*)(Actor*, bool&)) 0x0953C50;

bool __fastcall FleeFixHook(PlayerCharacter* Player, void* unused, bool& IsHidden) {
	return (GetPlayerInCombat(Player, IsHidden) && !IsHidden);
}


void __fastcall DisableMuzzleFlashLightsHook(ProjectileData* a1) {
	using namespace JohnnyPatches;
	if (*&a1->muzzleFlash && a1->projectile->lightMuzzleFlash) {
		if (!disableMuzzleLights || (disableMuzzleLights == 2 && a1->sourceActor != (Actor*)PlayerCharacter::GetSingleton()) || (disableMuzzleLights == 3 && a1->sourceActor == (Actor*)PlayerCharacter::GetSingleton())) {
			NiNode* niNode = ThisCall<NiNode*>(0x50D810, a1->projectile->lightMuzzleFlash, 0, *&a1->muzzleFlash, 1);
			ThisCall(0x66B0D0, &a1->flashLight, niNode);
		}
	}
}


_declspec(naked) void LevelUpHook() {
	static const uint32_t noShowAddr = 0x77D903;
	static const uint32_t showAddr = 0x77D618;
	_asm {
		jne noLevelUp
		mov al, JohnnyPatches::isShowLevelUp
		test al, al
		je noLevelUp
		jmp showAddr
		noLevelUp :
		jmp noShowAddr
	}
}

TESForm* __fastcall GetAmmoInInventory(TESObjectWEAP* weap) {
	if (weap->ammo.ammo) {
		if (IS_TYPE(weap->ammo.ammo, BGSListForm)) {
			BGSListForm* ammoList = (BGSListForm*)weap->ammo.ammo;
			ExtraContainerChanges* xChanges = GetExtraType(PlayerCharacter::GetSingleton()->extraDataList, ContainerChanges);
			TESForm* ammo = nullptr;
			if (ammoList && xChanges && xChanges->data) {
				for (uint32_t i = 0; i < ammoList->Count(); i++) {
					ammo = ammoList->GetNthForm(i);
					if (IS_TYPE(ammo, TESAmmo)) {
						uint32_t count = ThisCall<uint32_t>(0x4C8F30, xChanges->data, ammo);
						if (count > 0) return ammo;
					}
				}
			}
		}
	}
	return 0;
}

__declspec(naked) void InventoryAmmoHook() {
	static const uint32_t retnAddr = 0x7080A8;
	__asm {
		mov ecx, dword ptr[ebp - 0x2D4]
		call GetAmmoInInventory
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

float* __fastcall VATSSpreadMultHook(void* ecx) {
	return &vatsSpreadMultValue;
}

__declspec(naked) void DialogueAnimHook() {
	static const uint32_t jumpAddr = 0x8A56DF;
	static const uint32_t retnAddr = 0x8A566B;
	__asm {
		movzx eax, byte ptr ss : [ebp + 0x10]
		test eax, eax
		jnz ANIM
		jmp retnAddr
		ANIM :

		jmp jumpAddr
	}
}
__declspec(naked) void DisableArrowKeysHook() {
	static const uint32_t retnAddr = 0x70F711;
	__asm {
		cmp byte ptr[JohnnyPatches::bArrowKeysDisabled], 1
		jnz DONE
		cmp dword ptr[ebp + 8], 4
		jnz MATCHED
		cmp dword ptr[ebp + 8], 3
		jnz MATCHED
		cmp dword ptr[ebp + 8], 1
		jnz MATCHED
		cmp dword ptr[ebp + 8], 2
		jnz MATCHED
		jmp DONE
		MATCHED :
		mov dword ptr[ebp + 8], 0
			DONE :
			mov byte ptr[ebp - 0xD], 0
			mov eax, 1
			jmp retnAddr
	}
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
void __fastcall UIUpdateSoundHook(BSSoundHandle* sound, int dummy) {
	using namespace ExtraUISounds;
	tList<QuestUpdateManager>* g_questUpdateManager = (tList <QuestUpdateManager>*)0x11D970C;
	if (g_questUpdateManager) {
		ListNode<QuestUpdateManager>* iter = g_questUpdateManager->Head();
		do {
			switch (iter->data->updateType) {
				case QuestAdded:
					if (questNewSound != nullptr)
						*sound = BSWin32Audio::GetSingleton()->GetSoundHandleByFormID(questNewSound->GetFormID(), 0x121);
					break;
				case QuestCompleted:
					if (questCompeteSound != nullptr)
						*sound = BSWin32Audio::GetSingleton()->GetSoundHandleByFormID(questCompeteSound->GetFormID(), 0x121);
					break;
				case QuestFailed:
					if (questFailSound != nullptr)
						*sound = BSWin32Audio::GetSingleton()->GetSoundHandleByFormID(questFailSound->GetFormID(), 0x121);
					break;
				case LocationDiscovered:
					if (locationDiscoverSound != nullptr)
						*sound = BSWin32Audio::GetSingleton()->GetSoundHandleByFormID(locationDiscoverSound->GetFormID(), 0x121);
					break;
			}
			sound->Play(false);
		} while (iter = iter->next);
	}
}

void ResetVanityWheel() {
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

__declspec (naked) void VanityModeHook_DEPRECATED() {
	static uintptr_t jmpDest = 0x942D43;
	static uintptr_t getGS = 0x403E20;
	__asm
	{
		fstp dword ptr ds : [0x011E07C4]
		call ResetVanityWheel
		jmp jmpDest
	}
}
bool __fastcall CombatMusicHook(uint32_t* a1) {
	if (JohnnyPatches::bCombatMusicDisabled) return false;
	return ThisCall<bool>(0x992D90, a1);
}


void __fastcall DropItemHook(PlayerCharacter* a1, void* edx, TESForm* a2, BaseExtraList* a3, uint32_t itemCount, NiPoint3* a5, void* a6) {
	if (itemCount > 10000) {
		for (itemCount; itemCount > 10000; itemCount -= 10000) {
			ThisCall(0x954610, a1, a2, a3, 10000, a5, a6);
		}
	}
	ThisCall(0x954610, a1, a2, a3, itemCount, a5, a6);
}

void __fastcall TESRegionDataSoundIncidentalIDHook(TESFile* info, void* edx, uint32_t* refID) {
	ThisCall(0x4727F0, info, refID);
	if (*refID) {
		CdeclCall(0x485D50, refID, info);
	}
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
	return thisObj->dyingTimer + JohnnyPatches::iDeathSoundMAXTimer;
}
float __fastcall FixDeathSounds(HighProcess* thisObj, Actor* actor) { //Simpler fix, though we run the risk of overassumptions. 14 seconds should be more than enough though tbh.
	return thisObj->dyingTimer + JohnnyPatches::iDeathSoundMAXTimer;
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
__declspec (naked) void PatchPlayerPainHook(){
	_asm {
		mov ecx, dword ptr[ebp - 0x180]
		cmp ecx, dword ptr ds : [0x11DEA3C]
		jz PLAYER
		mov al, byte ptr ds : [0x119B4E0]
		retn
		PLAYER:
		mov al, 0
		retn
	}
}

void ComputeDiscoveredRadioDirectory() {
	static ULONGLONG timer = GetTickCount64();
	if (((GetTickCount64() - timer) > 1000) || jg_gameRadioSet.empty()) {
		timer = GetTickCount64();
		jg_gameRadioSet.clear();
		jg_gameRadioSet.insert(0);
		tList<TESObjectACTI>* discoveredRadios = CdeclCall<tList<TESObjectACTI>*>(0x79C080);
		for (auto radioIter = discoveredRadios->Begin(); !radioIter.End(); radioIter.Next()) {
			if (*radioIter) {
				jg_gameRadioSet.insert((*radioIter)->GetFormID());
			}
		}
	}

}

char* __cdecl fixAudioMonoLookupOverflow(char* Dst, const char* suffix){
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


__declspec (naked) void AnimDataNullCheck() {
	__asm {
		push 0x0490BD8
		mov eax, dword ptr [ebp-0xA4]
		test eax, eax
		jz retNoData
		push dword ptr [ebp-0xAC]
		mov ecx, eax
		mov eax, dword ptr [eax]
		mov eax, dword ptr [eax+0x9C]
		call eax
		retNoData:
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


__declspec (naked) void DisableDeathResponsesHook() {
	__asm {
		movzx eax, byte ptr ss : [ebp-0x10]
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

bool __fastcall SaveINIHook(INISettingCollection* a1, void* edx, char* a2) {
	ThisCall(0x5E01B0, a1, a2);
	RendererSettingCollection* rendererSettings = SettingT<RendererSettingCollection>::GetCollection();
	return ThisCall<bool>(0x5E01B0, rendererSettings, rendererSettings->cSettingFile);
}

bool __fastcall WantsToFleeHook(CombatState* state) {
	if (!state->cmbtCtrl->packageOwner) return false;
	float avCharisma = state->cmbtCtrl->packageOwner->avOwner.GetActorValueF(kAVCode_Charisma);
	if (state->currentConfidence > 0 && avCharisma <= 5) {
		Console_Print("0x%X confidence %d charisma %.f modified -1", state->cmbtCtrl->packageOwner->GetFormID(), state->currentConfidence, avCharisma);
		return (state->currentConfidence - 1) > state->fleeThreshold008;
	}
	else if (state->currentConfidence < 4 && avCharisma > 5) {
		Console_Print("0x%X confidence %d charisma %.f modified +1", state->cmbtCtrl->packageOwner->GetFormID(), state->currentConfidence, avCharisma);
		return (state->currentConfidence + 1) > state->fleeThreshold008;
	}
	else {
		return state->currentConfidence > state->fleeThreshold008;
	}
}

void ClearPlayerFurniture()
{
	if (auto playerProcess = PlayerCharacter::GetSingleton()->baseProcess)
	{
		playerProcess->SetFurnitureRef(PlayerCharacter::GetSingleton(), 0, NULL, 0x7F);

	}
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


bool __cdecl JGSetViewmodelClipDistance(float value) {
	g_viewmodel_near = value;
	return true;
}

float __cdecl JGGetViewmodelClipDistance() {
	return g_viewmodel_near;
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
		mov eax, dword ptr ds:[ebp-4]
		push eax
		call HandleSettingType
		mov eax, 0x5BEE5D
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

	if (IsConsoleMode()){
		// Reuse the original string, no need to duplicate *all* data
		Console_Print(((const char*)0x10350A8), arResult);
	}

	return true;
}

void __fastcall SetCellImageSpaceHook(TESObjectCELL* cell, void* edx, TESImageSpace* imageSpace) {


	ThisCall<void>(0x547750, cell, imageSpace);
	PlayerCharacter* player = PlayerCharacter::GetSingleton();
	if (player->parentCell != nullptr && player->parentCell == cell) {
		CdeclCall<void>(0xB4F430, imageSpace->traitValues);
	}
}


void HandleFixes() {
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

	//fix the clouds
	SkyCloudHook::InstallCloudUpdHook();
	//Cloud int update
	SafeWrite8(0x63AD66, 0xEB);
	WriteRelCall(0x063ADAB, (uintptr_t)SkyCloudHook::hk_han_NewGameCloudUpdate);
	//Stop game from crashing on extensions reeeeeeeeeee
	WriteRelCall(0x83509D, (uintptr_t)fixAudioMonoLookupOverflow);

	CustomCameraShake::Hook();
	NPCAccuracy::Hook();
	DialogueResponseOverride::Hook();

	hk_EmotionOverrideUndo< 0x0617D59>();
	hk_QuestObjectiveIsDisplayedCall<0x05A5E70>();

	WriteRelCall(0x5B7812, (uint32_t)SetCellImageSpaceHook);
}

void HandleIniOptions() {
	using namespace JohnnyPatches;
	// for bReset3rdPersonCamera
	//if (resetVanityCam) WriteRelJump(0x942D3D, (uintptr_t)VanityModeHook);

	// for bFixFleeing
	if (fixFleeing) WriteRelCall(0x8F5FE2, (uint32_t)FleeFixHook);

	// for bFixItemStackCount
	if (fixItemStacks) {
		WriteRelCall(0x780D11, (uint32_t)DropItemHook);
		SafeWriteBuf(0x780D11 + 5, "\x90\x90\x90", 3);
	}

	// for Runtime EDIDs
	EDIDRestoration::InitHooks();

	// for b60FPSDuringLoading
	if (iFPSCapLoadScreen > 0) {
		unsigned int fpsLoadScreenPatch = 1;
		fpsLoadScreenPatch = floor(1000.0f / float(iFPSCapLoadScreen));
		if (fpsLoadScreenPatch <= 0) { fpsLoadScreenPatch = 1; }
		if (fpsLoadScreenPatch >= 1000) { fpsLoadScreenPatch = 1000; }

		SafeWrite32(0x78D4A4, fpsLoadScreenPatch);
		//hk_SleepOneInterCall<0x078D557>();
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
	//Patch the game so the dialog subroutine stops if the actor's head is blown off, I'll add it as an ini setting later.
	WriteRelCall(0x8EC54D, (uintptr_t)NoHeadlessTalkingHook);
	if (bDisableDeathResponses) {
		SafeWrite8(0x098414C, 0x90);
		WriteRelCall(0x098414D, (uintptr_t)DisableDeathResponsesHook);
	}
}


__declspec (noinline) void HandleDLLInterop() {
	if (GetModuleHandle("jip_nvse.dll") != NULL) { //JIP is on.
		uint8_t* fnPtr = (uint8_t*) GetRelJumpAddr(0x0524014);
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


MediaLocationController* __fastcall MLCOverrideHook(PlayerCharacter* player)
{
	if (mlcOverridden)
	{
		return mlcOverride;
	}
	return ThisCall<MediaLocationController*>(0x9698A0, player);

}

float getHUDShakePower() {
	if (shakeRequests.empty()) {
		return 0.0f;
	}
	auto maxElement = std::max_element(
		shakeRequests.begin(), shakeRequests.end(),
		[](const auto& a, const auto& b) {
			return a.second < b.second;
		});
	return maxElement->second;
}

void HandleGameSettingsJG(){
	JohnnyGameSettings::Init();
	hk_CombatLocation::CombatLocationMaxRadiusBaseInitHook();

}

void __fastcall StopHolotapeSoundHook(BSSoundHandle* handle, void* edx, bool a2)
{
	if (!noHolotapeStopSound)
	{
		ThisCall(0xAD8830, handle, a2);
	}
	noHolotapeStopSound = false;
}

void HandleFunctionPatches() {
	// WorldToScreen
	WriteRelJump(0xC5244A, (uint32_t)NiCameraGetAltHook);

	// ToggleLevelUpMenu
	WriteRelJump(0x77D612, uint32_t(LevelUpHook));

	// DisableMuzzleFlashLights
	WriteRelCall(0x9BAFED, (uint32_t)DisableMuzzleFlashLightsHook);

	// DisableMenuArrowKeys
	WriteRelJump(0x70F708, (uint32_t)DisableArrowKeysHook);

	// SetUIUpdateSound
	WriteRelCall(0x77A8E9, (uint32_t)UIUpdateSoundHook);

	// DisableCombatMusic
	WriteRelCall(0x82FC0B, (uint32_t)CombatMusicHook);

	// ToggleDisableSaves
	g_canSaveNowAddr = (*(uint32_t*)0x0850443) + 5 + 0x0850442;
	WriteRelCall(0x0850442, (uintptr_t)CanSaveNowHook);
	g_canSaveNowMenuAddr = (*(uint32_t*)0x07CBDC8) + 5 + 0x07CBDC7;
	WriteRelCall(0x07CBDC7, (uintptr_t)CanSaveNowMenuHook);

	ExtraReputationIcons::Hook();

	ExtraMiscStats::Hook();

	//Hairstyle handlers
	RSMBarberHook::Hook();
	BarterFilter::Hook();

	WriteRelCall(0x8752F2, uint32_t(SetViewmodelFrustumHook));

	WriteRelCall(0x82FC95, (uint32_t)MLCOverrideHook);

	WriteRelCall(0x94AD8A, uint32_t(SetCameraTranslateHook));
	WriteRelCall(0x94AD9D, uint32_t(SetCameraRotateHook));

	WriteRelCall(0x94BDC2, uint32_t(SetCameraTranslateHook));
	WriteRelCall(0x94BDD5, uint32_t(SetCameraRotateHook));

	WriteRelCall(0x798BB1, (uint32_t)StopHolotapeSoundHook);
}
float timer22 = 30.0;
void HandleGameHooks() {
	HandleFixes();
	HandleIniOptions();
	HandleFunctionPatches();
	HandleGameSettingsJG();
}
