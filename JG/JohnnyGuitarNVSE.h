#pragma once

NVSEArrayVarInterface* g_arrInterface = NULL;
NVSEStringVarInterface* g_strInterface = NULL;
NVSEMessagingInterface* g_msg = NULL;
NVSEScriptInterface* g_scriptInterface = NULL;
NVSECommandTableInterface* g_cmdTableInterface = NULL;
VATSCameraData* g_VATSCameraData = NULL;
InventoryRef* (*InventoryRefGetForID)(UInt32 refID);
float(*GetWeaponDPS)(ActorValueOwner* avOwner, TESObjectWEAP* weapon, float condition, UInt8 arg4, ContChangesEntry* entry, UInt8 arg6, UInt8 arg7, int arg8, float arg9, float arg10, UInt8 arg11, UInt8 arg12, TESForm* ammo) =
(float(*)(ActorValueOwner*, TESObjectWEAP*, float, UInt8, ContChangesEntry*, UInt8, UInt8, int, float, float, UInt8, UInt8, TESForm*))0x645380;
void (*ApplyPerkModifiers)(PerkEntryPointID entryPointID, TESObjectREFR* perkOwner, void* arg3, ...) = (void (*)(PerkEntryPointID, TESObjectREFR*, void*, ...))0x5E58F0;
bool isShowLevelUp = true;
bool bArrowKeysDisabled = false;
bool bCombatMusicDisabled = false;
char* s_strArgBuf;
#define ExtractFormatStringArgs(...) g_scriptInterface->ExtractFormatStringArgs(__VA_ARGS__)
#define IS_TYPE(form, type) (*(UInt32*)form == kVtbl_##type)
#define NOT_ID(form, type) (form->typeID != kFormType_##type)
#define IS_ID(form, type) (form->typeID == kFormType_##type)
#define REG_CMD(name) nvse->RegisterCommand(&kCommandInfo_##name);
#define REG_TYPED_CMD(name, type) nvse->RegisterTypedCommand(&kCommandInfo_##name,kRetnType_##type);
#define VarNameSize 64
bool (*ExtractArgsEx)(COMMAND_ARGS_EX, ...);
bool loadEditorIDs = 0;
bool fixHighNoon = 0;
bool fixFleeing = 0;
bool fixItemStacks = 0;
bool resetVanityCam = 0;
bool fixNPCShootingAngle = 0;
bool noMuzzleFlashCooldown = 0;
bool enableRadioSubtitles = 0;
bool removeMainMenuMusic = 0;
bool fixDeathSounds = 1;
bool patchPainedPlayer = 0;
bool bDisableDeathResponses = 0;
unsigned int iFPSCapLoadScreen = 0;
float iDeathSoundMAXTimer = 10;
TESSound* questFailSound = 0;
TESSound* questNewSound = 0;
TESSound* questCompeteSound = 0;
TESSound* locationDiscoverSound = 0;
std::unordered_map<UInt32, char*> markerIconMap;
std::unordered_map <UInt32, std::vector<char*>> factionRepIcons;
std::unordered_map<std::string, int> miscStatMap;
std::unordered_set<std::string> availableMiscStats;
UInt32 disableMuzzleLights = -1;
static float vatsSpreadMultValue = 15.0;
UInt32 g_initialTickCount = 0;
// Singletons
PlayerCharacter* g_thePlayer = nullptr;
ProcessManager* g_processManager = nullptr;
InterfaceManager* g_interfaceManager = nullptr;
BSWin32Audio* g_bsWin32Audio = nullptr;
DataHandler* g_dataHandler = nullptr;
BSAudioManager* g_audioManager = nullptr;
GameTimeGlobals* g_gameTimeGlobals = nullptr;
StatsMenu* g_statsMenu = nullptr;
UInt8 recalculateStatFilters = 0;
Sky** g_currentSky = nullptr;
void(__thiscall* OriginalBipedModelUpdateWeapon)(ValidBip01Names*, TESObjectWEAP*, int) = (void(__thiscall*)(ValidBip01Names*, TESObjectWEAP*, int)) 0x4AB400;
UInt8(__thiscall* ContChangesEntry_GetWeaponModFlags)(ContChangesEntry* weapEntry) = (UInt8(__thiscall*)(ContChangesEntry*)) 0x4BD820;
std::unordered_set<BYTE> SaveGameUMap;
uintptr_t g_canSaveNowAddr = 0;
uintptr_t g_canSaveNowMenuAddr = 0;
Setting** g_miscStatData = (Setting**)0x11C6D50;
char g_workingDir[MAX_PATH];
std::unordered_set<DWORD> jg_gameRadioSet;
static float g_viewmodel_near = 0.f;

extern "C" {
	bool __cdecl JGSetViewmodelClipDistance(float value);
	float __cdecl JGGetViewmodelClipDistance();
}


namespace GMSTJG {
	static uintptr_t func_AddGameSetting = 0x040E0B0;
	Setting fCombatLocationTargetRadiusMaxBase;
	template <uintptr_t a_addr>
	class hk_CombatLocationMaxCall {
	private:
		static inline uintptr_t hookCall = a_addr;
	public:
		static  double __cdecl hk_CLCHook(float m_a1, float m_a2) {
			auto res = CdeclCall<double>(hookCall, m_a1, m_a2);
			return fmax(res, fCombatLocationTargetRadiusMaxBase.data.f);
		}

		hk_CombatLocationMaxCall() {
			uintptr_t hk_hookPoint = hookCall;
			hookCall = GetRelJumpAddr(hookCall);
			WriteRelCall(hk_hookPoint, (uintptr_t)hk_CLCHook);
		}
	};
	void CombatLocationMaxRadiusBaseInitHook() { //Thanks lStewieAl
		hk_CombatLocationMaxCall<0x09A089F>();
		hk_CombatLocationMaxCall<0x09A0A0C>();
		ThisStdCall<void>(func_AddGameSetting, &fCombatLocationTargetRadiusMaxBase, "fCombatLocationTargetRadiusMaxBase", 10.0f);

	}


}

template <class T>
struct JGSetList {
	bool isWhiteList = false;
	std::unordered_set<T> set;
	void dFlush() {
		isWhiteList = false;
		set.clear();
	};
	bool Allow(T obj) {
		return bool(set.count(obj)) == isWhiteList;
	}
	void Add(T obj) {
		set.insert(obj);
	}
	void Remove(T obj) {
		set.erase(obj);
	}
};

namespace hk_CameraShakeHook {
	float camShakeMinAlt = 0, camShakeTimeAlt = 0;
	bool __fastcall fn_camAltShakeHook(Actor* a_refr, void* edx, NiMatrix33* outMatrix) {
		NiMatrix33 shakeMatrix = {};
		AnimData* anData = ThisStdCall<AnimData*>(0x08B70D0, a_refr);
		if (!anData) return true;
		float timePassed = anData->flt0D0;
		auto originalShakeMult = *(float*)(0x11DFED4), originalShakeTime = *(float*)(0x11DFED8);
		*(float*)(0x11DFED4) = camShakeMinAlt;
		*(float*)(0x11DFED8) = camShakeTimeAlt;
		float remainTime = CdeclCall<double>(0x8D1B30, timePassed, &shakeMatrix);
		camShakeMinAlt = *(float*)(0x11DFED4);
		camShakeTimeAlt = *(float*)(0x11DFED8);
		*(float*)(0x11DFED4) = originalShakeMult;
		*(float*)(0x11DFED8) = originalShakeTime;
		if (remainTime > 0.0f) {
			float euX = 0, euY= 0, euZ = 0;
			ThisStdCall<void>(0x0A592C0, &shakeMatrix, &euX, &euY, &euZ);
			euX *= remainTime;
			euY *= remainTime;
			euZ *= remainTime;
			ThisStdCall<void>(0x0A59540, &shakeMatrix, euX, euY, euZ);
			ThisStdCall<void*>(0x43F8D0, outMatrix, outMatrix, &shakeMatrix);

		}
		return true;

	}
	__declspec(naked) void asm_CameraShakeHook() {
		__asm {
			fnstsw ax
			test ah, 0x41
			jz retAbort
			lea edx, dword ptr ss: [ebp-0x34]
			push edx
			mov ecx, dword ptr ss: [ebp-0x414]
			call fn_camAltShakeHook
			ALIGN 16
			test al, al
			jmp retEnd
			retAbort:
			fldz
			fst camShakeMinAlt
			fstp camShakeTimeAlt
			retEnd:
			setnz al
			ret
		}
	}
	void CreateHook() {
		WriteRelCall(0x94BCF6, (uintptr_t)asm_CameraShakeHook);
	}

}

namespace hk_BarterHook {
	std::unordered_map<DWORD, JGSetList<DWORD>> barterFilterListLeft;
	std::unordered_map<DWORD, JGSetList<DWORD>> barterFilterListRight;
	enum barterHideFlags {
		kBarterDoNotHideLeft = 1 << 0,
		kBarterDoNotHideRight
	};
	template <uintptr_t a_addr>
	class hk_BarterFilterHookClassLeft {
	private:
		static inline uintptr_t hookCall = a_addr;
	public:
		static  DWORD __cdecl hk_BarterFilterHook(ContChangesEntry* ref) {
			auto shouldHide = CdeclCall<bool>(hookCall, ref);
			if (shouldHide){ return shouldHide; }
			auto barterMenu = *(BarterMenu**)0x11D8FA4;
			if (!barterMenu) return shouldHide;
			auto merchantRef = barterMenu->merchantRef;
			if (!merchantRef) return shouldHide;
			auto originalForm = ref->type;
			if (!g_thePlayer) return shouldHide;
			auto it = barterFilterListLeft.find(originalForm->refID);
			if (it != barterFilterListLeft.end()) {
				auto &barterSet = it->second;
				shouldHide = barterSet.Allow(merchantRef->refID) || barterSet.Allow(merchantRef->baseForm->refID) || barterSet.Allow(0) || barterSet.Allow(g_thePlayer->refID);
			}
			return shouldHide;
		}
		hk_BarterFilterHookClassLeft() {
			uintptr_t hk_hookPoint = hookCall;
			hookCall = *(uintptr_t*)(hk_hookPoint + 1);
			SafeWrite32((hk_hookPoint + 1) , (uintptr_t) hk_BarterFilterHook);

		}

	};

	template <uintptr_t a_addr>
	class hk_BarterFilterHookClassRight {
	private:
		static inline uintptr_t hookCall = a_addr;
	public:
		static  DWORD __cdecl hk_BarterFilterHook(ContChangesEntry* ref) {
			auto shouldHide = CdeclCall<bool>(hookCall, ref);
			if (shouldHide) { return shouldHide; }
			auto barterMenu = *(BarterMenu**)0x11D8FA4;
			if (!barterMenu) return shouldHide;
			auto merchantRef = barterMenu->merchantRef;
			if (!merchantRef) return shouldHide;
			auto originalForm = ref->type;
			auto it = barterFilterListRight.find(originalForm->refID);
			if (it != barterFilterListRight.end()) {
				auto& barterSet = it->second;
				shouldHide = barterSet.Allow(merchantRef->refID) || barterSet.Allow(merchantRef->baseForm->refID) || barterSet.Allow(0) || barterSet.Allow(g_thePlayer->refID);

			}
			return shouldHide;
		}
		hk_BarterFilterHookClassRight() {
			uintptr_t hk_hookPoint = hookCall;
			hookCall = *(uintptr_t*)(hk_hookPoint + 1);
			SafeWrite32((hk_hookPoint + 1), (uintptr_t)hk_BarterFilterHook);

		}

	};


	void CreateHook() {
		hk_BarterFilterHookClassLeft<0x72DA1C>();
		hk_BarterFilterHookClassLeft<0x72E1BE>();

		hk_BarterFilterHookClassRight<0x72DACA>();
		hk_BarterFilterHookClassRight<0x72E207>();

	}
};




template <uintptr_t a_addr>
class hk_SleepOneInterCall {
private:
	static inline uintptr_t hookCall = a_addr;
public:
	static  uintptr_t __cdecl hk_SleepOneInterCallHook() {
		auto res = CdeclCall<uintptr_t>(hookCall);
		Sleep(1);
		return res;
	}
	hk_SleepOneInterCall() {
		uintptr_t hk_hookPoint = hookCall;
		hookCall = *(uintptr_t*)(hk_hookPoint + 1);
		SafeWrite32((hk_hookPoint + 1), (uintptr_t)hk_SleepOneInterCallHook);

	}

};







namespace hk_RSMBarberHook {
	JGSetList<DWORD> haircutSetList;
	JGSetList<DWORD> beardSetList;
	uintptr_t RSMDestructorOriginal = (uintptr_t)0x07AC530;
	bool __fastcall hk_TESHair_IsPlayable(TESHair* ptr_hair) {
		return (ptr_hair->IsPlayable()) && (haircutSetList.Allow(ptr_hair->refID));

	}

	bool __fastcall hk_BGSHeadPart_IsPlayable(BGSHeadPart* ptr_hdpt) {
		return (ptr_hdpt->headFlags & 0x1) && (beardSetList.Allow(ptr_hdpt->refID));
	}
	DWORD __fastcall hk_RSMDestroy(void* thisObj, void* EDX, BOOL heapFree) {
		auto ret = ThisStdCall<DWORD>(RSMDestructorOriginal, thisObj, heapFree);
		haircutSetList.dFlush();
		beardSetList.dFlush();
		return ret;
	}
	void Hook() {
		RSMDestructorOriginal = *((uintptr_t*) 0x1075974);
		SafeWrite32(0x1075974, (uintptr_t)hk_RSMDestroy);
		WriteRelCall(0x07AD35C, (uintptr_t)hk_BGSHeadPart_IsPlayable);
		WriteRelCall(0x07AF35B, (uintptr_t)hk_TESHair_IsPlayable);
		WriteRelCall(0x07B1D4A, (uintptr_t)hk_TESHair_IsPlayable);

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
		auto ret = ThisStdCall<DWORD>(fn_Clouds_Update, a_cloud, Sky, timePassed);
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
		return ThisStdCall<bool>(0x42CE10, a_obj) || (*(bool*)0x11D8907);
	
	}
	


}



TESObjectCELL* TESObjectREFR::GetParentCell() {
	if (this->parentCell) return parentCell;
	ExtraPersistentCell* xPersistentCell = (ExtraPersistentCell*)this->extraDataList.GetByType(kExtraData_PersistentCell);
	if (xPersistentCell && xPersistentCell->persistentCell) return xPersistentCell->persistentCell;
	return nullptr;
}

double GetVectorAngle2D(NiPoint3* pt) {
	double angle;
	if (pt->y == 0) {
		if (pt->x <= 0) {
			angle = kDblPIx3d2;
		}
		else {
			angle = kDblPId2;
		}
	}
	else {
		double ratio = pt->x / pt->y;
		angle = dAtan(ratio);
		if (pt->y < 0.0) {
			angle += kDblPI;
		}
	}

	return angle;
}

double GetAngleBetweenPoints(NiPoint3* actorPos, NiPoint3* playerPos, float offset) {
	NiPoint3 diff;
	diff.Init(actorPos);
	diff.Subtract(playerPos);

	double angle = GetVectorAngle2D(&diff) - offset;
	if (angle > -kDblPI) {
		if (angle > kDblPI) {
			angle = kDblPIx2 - angle;
		}
	}
	else {
		angle += kDblPIx2;
	}
	return angle * 57.295779513;
}

ContChangesEntry* ExtraContainerChanges::EntryDataList::FindForItem(TESForm* item) {
	ListNode<ContChangesEntry>* iter = this->Head();

	do {
		if (iter->data && iter->data->type == item) return iter->data;
	} while (iter = iter->next);

	return nullptr;
}

float __declspec(naked) __fastcall NiNodeComputeDistance(NiVector3* Vector1, NiVector3* Vector2) {
	__asm
	{
		movd xmm0, [ecx]
		subss xmm0, [edx]
		mulss xmm0, xmm0
		movd xmm1, [ecx + 4]
		subss xmm1, [edx + 4]
		mulss xmm1, xmm1
		movd xmm2, [ecx + 8]
		subss xmm2, [edx + 8]
		mulss xmm2, xmm2
		addss xmm0, xmm1
		addss xmm0, xmm2
		sqrtss xmm0, xmm0
		movd eax, xmm0
		push eax
		fld dword ptr[esp]
		add esp, 4
		ret
	}
}
NiNode* NiNode::GetNode(const char* nodeName) {
	NiAVObject* found = GetBlock(nodeName);
	return found ? found->GetNiNode() : NULL;
}

__forceinline void NiPointAssign(NiPoint3* NiPointBuffer, float& xIn, float& yIn, float& zIn) {
	NiPointBuffer->x = xIn;
	NiPointBuffer->y = yIn;
	NiPointBuffer->z = zIn;
}

UInt8 TESForm::GetOverridingModIdx() {
	return mods.GetLastItem() ? mods.GetLastItem()->modIndex : 0xFF;
}

NiAVObject* NiNode::GetBlock(const char* blockName) {
	if (StrEqualCI(m_blockName.handle, blockName))
		return this;
	NiAVObject* found = NULL;
	for (NiTArray<NiAVObject*>::Iterator iter(m_children); !iter.End(); ++iter) {
		if (!*iter) continue;
		if (iter->GetNiNode())
			found = ((NiNode*)*iter)->GetBlock(blockName);
		else if (StrEqualCI(iter->m_blockName.handle, blockName))
			found = *iter;
		else continue;
		if (found) break;
	}
	return found;
}

static void PatchMemoryNop(ULONG_PTR Address, SIZE_T Size) {
	DWORD d = 0;
	VirtualProtect((LPVOID)Address, Size, PAGE_EXECUTE_READWRITE, &d);

	for (SIZE_T i = 0; i < Size; i++)
		*(volatile BYTE*)(Address + i) = 0x90; //0x90 == opcode for NOP

	VirtualProtect((LPVOID)Address, Size, d, &d);

	FlushInstructionCache(GetCurrentProcess(), (LPVOID)Address, Size);
}

bool __fastcall CanSaveNowHook(void* ThisObj, void* edx, int isAutoSave) {
	return ThisStdCall_B(g_canSaveNowAddr, ThisObj, isAutoSave) && SaveGameUMap.empty();
}

bool __fastcall CanSaveNowMenuHook(void* ThisObj, void* edx, int isAutoSave) {
	return ThisStdCall_B(g_canSaveNowMenuAddr, ThisObj, isAutoSave) && SaveGameUMap.empty();
}

void __fastcall BipedModelUpdateWeapon(ValidBip01Names* BipedAnim, Character* fnCharacter, TESObjectWEAP* weap, int weapMods) {
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

char** defaultMarkerList = (char**)0x11A0404;

char* __fastcall GetMapMarker(TESObjectREFR* thisObj, UInt16 mapMarkerType) {
	auto it = markerIconMap.find(thisObj->refID);
	if (it != markerIconMap.end()) return it->second;
	return defaultMarkerList[mapMarkerType];
}

__declspec (naked) void GetMapMarkerHook() {
	//UInt32 static const retAddr = 0x079D337;
	__asm
	{
		mov edx, eax
		mov ecx, [ebp - 0x24]
		jmp GetMapMarker
	}
}

void __fastcall DisableMuzzleFlashLightsHook(ProjectileData* a1) {
	if (*&a1->muzzleFlash && a1->projectile->lightMuzzleFlash) {
		if (!disableMuzzleLights || (disableMuzzleLights == 2 && a1->sourceActor != (Actor*)g_thePlayer) || (disableMuzzleLights == 3 && a1->sourceActor == (Actor*)g_thePlayer)) {
			NiNode* niNode = ThisStdCall<NiNode*>(0x50D810, a1->projectile->lightMuzzleFlash, 0, *&a1->muzzleFlash, 1);
			ThisStdCall(0x66B0D0, &a1->flashLight, niNode);
		}
	}
}
void SetCustomMapMarker(TESObjectREFR* marker, char* iconPath) {
	auto pos = markerIconMap.find(marker->refID);
	char* pathCopy = new char[strlen(iconPath) + 1];
	strcpy(pathCopy, iconPath);

	if (pos != markerIconMap.end()) {
		delete[] pos->second;
		pos->second = pathCopy;
	}
	else {
		markerIconMap.insert({ marker->refID, pathCopy });
	}
}

_declspec(naked) void LevelUpHook() {
	static const UInt32 noShowAddr = 0x77D903;
	static const UInt32 showAddr = 0x77D618;
	_asm {
		jne noLevelUp
		mov al, isShowLevelUp
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
			ExtraContainerChanges* xChanges = GetExtraType(g_thePlayer->extraDataList, ContainerChanges);
			TESForm* ammo = nullptr;
			if (ammoList && xChanges && xChanges->data) {
				for (int i = 0; i < ammoList->Count(); i++) {
					ammo = ammoList->GetNthForm(i);
					if (IS_TYPE(ammo, TESAmmo)) {
						UInt32 count = ThisStdCall<UInt32>(0x4C8F30, xChanges->data, ammo);
						if (count > 0) return ammo;
					}
				}
			}
		}
	}
	return 0;
}

__declspec(naked) void InventoryAmmoHook() {
	static const UInt32 retnAddr = 0x7080A8;
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
	static const UInt32 retnAddr = 0x75B240;
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
	if (*(UInt8*)0x8A1B4D == 0xE9 || *(UInt8*)0x8A1B51 == 0x26) return;
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
	static const UInt32 jumpAddr = 0x8A56DF;
	static const UInt32 retnAddr = 0x8A566B;
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
	static const UInt32 retnAddr = 0x70F711;
	__asm {
		cmp byte ptr[bArrowKeysDisabled], 1
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
	static const UInt32 retnAddr = 0x88D0D8;
	static const UInt32 noIncrementAddr = 0x88D100;
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
void __fastcall UIUpdateSoundHook(Sound* sound, int dummy) {
	tList<QuestUpdateManager>* g_questUpdateManager = (tList <QuestUpdateManager>*)0x11D970C;
	if (g_questUpdateManager) {
		ListNode<QuestUpdateManager>* iter = g_questUpdateManager->Head();
		do {
			switch (iter->data->updateType) {
				case QuestAdded:
					if (questNewSound != nullptr) sound = &Sound(questNewSound->refID, 0x121);
					break;
				case QuestCompleted:
					if (questCompeteSound != nullptr) sound = &Sound(questCompeteSound->refID, 0x121);
					break;
				case QuestFailed:
					if (questFailSound != nullptr) sound = &Sound(questFailSound->refID, 0x121);
					break;
				case LocationDiscovered:
					if (locationDiscoverSound != nullptr) sound = &Sound(locationDiscoverSound->refID, 0x121);
					break;
			}
			sound->Play();
		} while (iter = iter->next);
	}
}

void ResetVanityWheel() {
	float* VanityWheel = (float*)0x11E0B5C;
	float* MaxChaseCam = (ThisStdCall<float*>((uintptr_t)0x0403E20, (void*)0x11CD568));
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
bool __fastcall CombatMusicHook(UInt32* a1) {
	if (bCombatMusicDisabled) return false;
	return ThisStdCall_B(0x992D90, a1);
}
TESRegionDataMap* GetMapData(TESRegion* region) {
	if (region->dataEntries->Empty()) return nullptr;
	ListNode<TESRegionData>* iter = region->dataEntries->Head();
	TESRegionData* regData;
	do {
		regData = iter->data;
		if ((*(UInt32*)regData == 0x1023D28))
			return (TESRegionDataMap*)regData;
	} while (iter = iter->next);
	return nullptr;;
}

TESRegionDataWeather* GetWeatherData(TESRegion* region) {
	if (region->dataEntries->Empty()) return nullptr;
	ListNode<TESRegionData>* iter = region->dataEntries->Head();
	TESRegionData* regData;
	do {
		regData = iter->data;
		if ((*(UInt32*)regData == 0x1023E18))
			return (TESRegionDataWeather*)regData;
	} while (iter = iter->next);
	return nullptr;
}
void __fastcall DropItemHook(PlayerCharacter* a1, void* edx, TESForm* a2, BaseExtraList* a3, UInt32 itemCount, NiPoint3* a5, void* a6) {
	if (itemCount > 10000) {
		for (itemCount; itemCount > 10000; itemCount -= 10000) {
			ThisStdCall(0x954610, a1, a2, a3, 10000, a5, a6);
		}
	}
	ThisStdCall(0x954610, a1, a2, a3, itemCount, a5, a6);
}

void __fastcall TESRegionDataSoundIncidentalIDHook(ModInfo* info, void* edx, UInt32* refID) {
	ThisStdCall(0x4727F0, info, refID);
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
	return thisObj->dyingTimer + iDeathSoundMAXTimer;
}
float __fastcall FixDeathSounds(HighProcess* thisObj, Actor* actor) { //Simpler fix, though we run the risk of overassumptions. 14 seconds should be more than enough though tbh.
	return thisObj->dyingTimer + iDeathSoundMAXTimer;
}



float __fastcall FixDeathSoundsAlt(HighProcess* thisObj, Actor* actor) { //Alternate complex, confusing, potentially buggy fix.
	constexpr float dyingTimerMin = FLT_EPSILON * 10; //Establish low tolerance, this should be ideal. Unless someone sets fDyingTimer to 0 or something, but that's their problem.
	float dyingTimer = thisObj->dyingTimer;
	bool keepTalkingDe = false;
	keepTalkingDe = (ThisStdCall<bool>(0x8A67F0, actor)) || !(actor->unk80 & 1);
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
		xor eax, eax
		mov ecx, dword ptr ss: [ebp-0x180]
		cmp ecx, dword ptr ds: [0x11DEA3C]
		cmovnz al, byte ptr ds: [0x119B4E0]
		retn
	}
}


char* __fastcall GetReputationIconHook(TESReputation* rep) {
	auto it = factionRepIcons.find(rep->refID);
	if (it != factionRepIcons.end()) {
		UInt8 tierID = 0;
		UInt8 pos = ThisStdCall<UInt8>(0x616950, rep, 1);
		UInt8 neg = ThisStdCall<UInt8>(0x616950, rep, 0);
		if ((pos == 0 && neg == 1) || (pos == 2 && (neg == 2 || neg == 3)) || (pos == 3 && neg == 3)) {
			tierID = 0; // in pain
		}
		else if (((neg == 2 || neg == 3) && (pos == 0 || pos == 1)) || (pos == 3 && neg == 2)) {
			tierID = 1; // sad
		}
		else if (((pos == 0 || pos == 1) && neg == 0) || (pos == 1 && neg == 1)) {
			tierID = 2; // neutral
		}
		else {
			tierID = 3; // very happy
		}
		if (*it->second[tierID]) return it->second[tierID];
	}
	return ThisStdCall<char*>(0x6167D0, rep);
}

char* __fastcall GetReputationMessageIconHook(UInt32 a1) {
	UInt32 addr = (UInt32)_ReturnAddress();
	auto* _ebp = GetParentBasePtr(_AddressOfReturnAddress(), false);
	TESReputation* rep = nullptr;
	switch (addr) {
		case 0x615951:
		case 0x61585A:
		case 0x615B1E:
		case 0x615C09:
			rep = *reinterpret_cast<TESReputation**>(_ebp - 0x110);
			break;
		case 0x615E0B:
		case 0x615F10:
		case 0x61610F:
		case 0x616208:
			rep = *reinterpret_cast<TESReputation**>(_ebp - 0x128);
			break;
		default:
			break;
	}
	if (rep && rep->refID) {
		auto it = factionRepIcons.find(rep->refID);
		if (it != factionRepIcons.end()) {
			UInt8 tierID = 0;
			if (a1 == 0x11CBAD0 || a1 == 0x11CBC34) {
				tierID = 1;
			}
			else if (a1 == 0x11CBA00 || a1 == 0x11CBD5C) {
				tierID = 3;
			}
			if (*it->second[tierID]) return it->second[tierID];
		}
	}
	return a1 ? ((Setting*)a1)->data.str : "\0";
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
				jg_gameRadioSet.insert((*radioIter)->refID);
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



Setting* __fastcall GetINISettingHook(IniSettingCollection* ini, void* edx, char* name) {
	Setting* result = ThisStdCall<Setting*>(0x5E02B0, ini, name);
	if (result) return result;
	IniSettingCollection* rendererSettings = *(IniSettingCollection**)0x11F35A4;
	if (rendererSettings && !rendererSettings->settings.Empty()) {
		ListNode<Setting>* iter = rendererSettings->settings.Head();
		do {
			if (iter->data && !stricmp(iter->data->name, name)) return iter->data;
		} while (iter = iter->next);
	}
	return nullptr;
}
bool __fastcall MenuGetFlagHook(StartMenu* menu, UInt32 flags) {
	return menu != nullptr ? ((flags & menu->flags) != 0) : false;
}
void __fastcall MenuSetFlagHook(StartMenu* menu, UInt32 flags, bool doSet) {
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
	return !(ThisStdCall<bool>(0x573090, actor, BGSBodyPartData::eBodyPart_Head1)) && !(ThisStdCall<bool>(0x573090, actor, BGSBodyPartData::eBodyPart_Head2));
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

bool __fastcall SaveINIHook(IniSettingCollection* a1, void* edx, char* a2) {
	ThisStdCall<void>(0x5E01B0, a1, a2);
	IniSettingCollection* rendererSettings = *(IniSettingCollection**)0x11F35A4;
	return ThisStdCall_B(0x5E01B0, rendererSettings, rendererSettings->iniPath);
}

bool __fastcall WantsToFleeHook(CombatState* state) {
	if (!state->cmbtCtrl->packageOwner) return false;
	float avCharisma = state->cmbtCtrl->packageOwner->avOwner.GetActorValue(kAVCode_Charisma);
	if (state->currentConfidence > 0 && avCharisma <= 5) {
		Console_Print("0x%X confidence %d charisma %.f modified -1", state->cmbtCtrl->packageOwner->refID, state->currentConfidence, avCharisma);
		return (state->currentConfidence - 1) > state->fleeThreshold008;
	}
	else if (state->currentConfidence < 4 && avCharisma > 5) {
		Console_Print("0x%X confidence %d charisma %.f modified +1", state->cmbtCtrl->packageOwner->refID, state->currentConfidence, avCharisma);
		return (state->currentConfidence + 1) > state->fleeThreshold008;
	}
	else {
		return state->currentConfidence > state->fleeThreshold008;
	}
}
void __cdecl MiscStatRefreshHook(Tile* tile, int id) {
	int value = 0;
	if (id < 43) {
		value = g_miscStatData[id]->data.i;
	}
	else {
		std::string sName = tile->name.m_data;
		auto it = miscStatMap.find(sName);
		if (it != miscStatMap.end()) {
			value = it->second;
		}
	}

	tile->SetFloat(kTileValue_user1, (float)value, 1);
}
bool __cdecl ShouldHideStat(UInt32* id) {
	if ((UInt32)id >= 43) {
		Tile* tile = g_statsMenu->miscStatIDList.GetTileFromItem(&id);
		std::string sName = tile->name.CStr();
		if (miscStatMap.find(sName) == miscStatMap.end()) return true;
	}
	return false;
}
void UpdateMiscStatList(const char* name, int value) {
	Tile* tile = nullptr;
	auto iter = g_statsMenu->miscStatIDList.list.Head();
	do
	{
		if (iter->data && iter->data->tile && !strcmp(iter->data->tile->name.CStr(), name)) {
			tile = iter->data->tile;
			break;
		}
	} while (iter = iter->next);
	if (!tile) {
		tile = ThisStdCall<Tile*>(0x7E1190, &g_statsMenu->miscStatIDList, g_statsMenu->miscStatIDList.itemCount, 0, 0, 0);
		tile->SetString(kTileValue_string, name, 1);
		tile->name.Set(name);
		recalculateStatFilters = true;
	}
	else if (auto listIdxTileVal = tile->GetValue(kTileValue_listindex)){
		if (listIdxTileVal && listIdxTileVal->num < 0) {
			recalculateStatFilters = true;
		}
	}
	tile->SetFloat(kTileValue_user1, (float)value, 1);
}

void ResetMiscStatMap() {
	miscStatMap.clear();
	for (auto element : availableMiscStats) {
		miscStatMap[element] = 0;
		UpdateMiscStatList(element.c_str(), 0);
	}

}
void DumpModules() {
	HMODULE hMods[1024];
	HANDLE hProcess = INVALID_HANDLE_VALUE;
	DWORD cbNeeded;
	if (EnumProcessModules(GetCurrentProcess(), hMods, sizeof(hMods), &cbNeeded))
	{
		PrintLog("\n===== DUMPING LOADED MODULES =====\n");
		std::string userStr = "=== USER MODULES ===\n";
		std::string systemStr = "=== SYSTEM MODULES ===\n";
		for (int i = 0; i < (cbNeeded / sizeof(HMODULE)); i++)
		{
			TCHAR szModName[MAX_PATH];


			if (GetModuleFileNameEx(hProcess, hMods[i], szModName,
				sizeof(szModName) / sizeof(TCHAR)))
			{
				char* trimName = (char*)(strrchr(szModName, '\\') + 1);
				if (strstr(szModName, g_workingDir)) {
					userStr += trimName;
					userStr += "\n";
				}
				else {
					systemStr += trimName;
					systemStr += "\n";
				}
			}
		}
		PrintLog("%s", userStr.c_str());
		PrintLog("%s", systemStr.c_str());
	}
}

void __fastcall SetViewmodelFrustumHook(NiCameraAlt* camera, void*, NiFrustum* frustum) {
	float nearDistance = frustum->n;
	float ratio = camera->maxFarNearRatio;
	if (g_viewmodel_near > 0.f) {
		nearDistance = max(g_viewmodel_near, 0.001);
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
void __stdcall HandleSettingType(Setting* setting, Setting::EType type) {
	switch (type) {
	case Setting::EType::kSetting_Bool:
		if (IsConsoleMode()) Console_Print("INISetting %s >> %i", setting->name, setting->data.b);
		break;
	case Setting::EType::kSetting_Integer:
		if (IsConsoleMode()) Console_Print("INISetting %s >> %d", setting->name, setting->data.i);
		break;
	case Setting::EType::kSetting_Unsigned:
		if (IsConsoleMode()) Console_Print("INISetting %s >> %X", setting->name, setting->data.uint);
		break;
	case Setting::EType::kSetting_Float:
		if (IsConsoleMode()) Console_Print("INISetting %s >> %.2f", setting->name, setting->data.f);
		break;
	case Setting::EType::kSetting_String:
		if (IsConsoleMode()) Console_Print("INISetting %s >> '%s'", setting->name, setting->data.str);
		break;
	case Setting::EType::kSetting_r:
		if (IsConsoleMode()) Console_Print("INISetting %s >> R: %d G: %d B: %d", setting->name, setting->data.rgb[3], setting->data.rgb[2], setting->data.rgb[1]);
		break;
	case Setting::EType::kSetting_a:
		if (IsConsoleMode()) Console_Print("INISetting %s >> R: %d G: %d B: %d alpha: %d", setting->name, setting->data.rgb[3], setting->data.rgb[2], setting->data.rgb[1], setting->data.rgb[0]);
		break;
	default:
		if (IsConsoleMode()) Console_Print("INISetting %s >> UNKNOWN TYPE", setting->name);
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

void HandleFixes() {
	// use available ammo in inventory instead of NULL when default ammo isn't present
	WriteRelJump(0x70809E, (UInt32)InventoryAmmoHook);

	// fix ammo effects list being checked for non-TESAmmo's when the Rock-It-Launcher is equipped
	for (auto addr : { 0x523AD8, 0x64529D, 0x64553B, 0x6462C5 })
	{
		WriteRelCall(addr, UInt32(GetAmmoEffectsCheckType));
	}

	// fix for companions not saying the next topic after opening ContainerMenu through dialog
	SafeWrite32(0x10721AC, (UInt32)OnCloseContainerHook);

	// replace fNPCMaxWobbleAngle with 15.0 for VATS
	WriteRelCall(0x8B102B, (UInt32)VATSSpreadMultHook);

	// Fix for animations not working in dialog topics with sound
	PatchMemoryNop(0x8A56C4, 4);
	PatchMemoryNop(0x8A56C8, 4);

	// fix Disintegrations stat not incrementing properly
	patchFixDisintegrationsStat();

	// fix NPCs incrementing player challenges
	WriteRelJump(0x88D0D0, (UInt32)NPCIncrementingChallengesHook);

	// use correct weapon skill req penalty setting in weapon spread calculation
	SafeWriteBuf(0x647902 + 1, "\xC8\xEA\x1C\x01", 4);

	// fix for various biped model update bugs
	WriteRelCall(0x06061E8, (uintptr_t)BipedModelUpdateWeaponHook);

	// missing nullcheck in NiMultiTargetTransformController::RemoveNodeRecurse
	SafeWrite8(0x4F064E, 0x7A);

	// fix for Get/Set/SaveINISetting not reading renderer INI setting list
	WriteRelCall(0x5BED66, (UInt32)GetINISettingHook);
	WriteRelCall(0x5BEF13, (UInt32)GetINISettingHook);
	WriteRelCall(0x5B6C80, (UInt32)SaveINIHook);

	WriteRelJump(0x5BED86, (UInt32)GetINISettingTypeHook);

	// fixes for null pointers when showing credits outside of start menu
	WriteRelCall(0x75F770, (UInt32)MenuGetFlagHook);
	WriteRelCall(0x75F8AE, (UInt32)MenuSetFlagHook);
	WriteRelCall(0x75F6DA, (UInt32)MenuSetFlagHook);

	// missing nullcheck in HandleStealing
	SafeWriteBuf(0x8BFBC1, "\x85\xC9\x74\x36\x80\x79\x04", 7);

	// fix for incidental sounds not working in regions
	WriteRelCall(0x4F49AB, UInt32(TESRegionDataSoundIncidentalIDHook));

	// fix for the stimpak crash
	WriteRelCall(0x7DB525, (uintptr_t)StimpakHotkeyHook);
	// Fix crash caused by wrong check inside AddSequence (thanks Stewie!)
	SafeWrite8(0xA2F0CB, 0x3A);
	//And also fix ANOTHER crash nearby caused by ANOTHER faulty nullptr check... this removes a DebugLog, but i don't care.
	WriteRelJump((uintptr_t)0x0490B10, (uintptr_t)0x0490B41);

	// fix NPE in BSTempEffectSimpleDecal
	WriteRelJump(0x68D2EB, (UInt32)SimpleDecalHook);



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
	//CamShakeHook
	hk_CameraShakeHook::CreateHook();


}

void HandleIniOptions() {
	// for bReset3rdPersonCamera
	//if (resetVanityCam) WriteRelJump(0x942D3D, (uintptr_t)VanityModeHook);

	// for bFixFleeing
	if (fixFleeing) WriteRelCall(0x8F5FE2, (UInt32)FleeFixHook);

	// for bFixItemStackCount
	if (fixItemStacks) {
		WriteRelCall(0x780D11, (UInt32)DropItemHook);
		SafeWriteBuf(0x780D11 + 5, "\x90\x90\x90", 3);
	}

	// for Runtime EDIDs
	if (loadEditorIDs) LoadEditorIDs();

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








void HandleGameSettingsJG(){

	GMSTJG::CombatLocationMaxRadiusBaseInitHook();

}

void HandleFunctionPatches() {
	// WorldToScreen
	WriteRelJump(0xC5244A, (UInt32)NiCameraGetAltHook);

	// ToggleLevelUpMenu
	WriteRelJump(0x77D612, UInt32(LevelUpHook));

	// DisableMuzzleFlashLights
	WriteRelCall(0x9BAFED, (UInt32)DisableMuzzleFlashLightsHook);

	// SetCustomMapMarkerIcon
	SafeWrite16(0x79D330, 0x9090);
	WriteRelCall(0x79D332, (UInt32)GetMapMarkerHook);

	// DisableMenuArrowKeys
	WriteRelJump(0x70F708, (UInt32)DisableArrowKeysHook);

	// SetUIUpdateSound
	WriteRelCall(0x77A8E9, (UInt32)UIUpdateSoundHook);

	// DisableCombatMusic
	WriteRelCall(0x82FC0B, (UInt32)CombatMusicHook);

	// ToggleDisableSaves
	g_canSaveNowAddr = (*(UInt32*)0x0850443) + 5 + 0x0850442;
	WriteRelCall(0x0850442, (uintptr_t)CanSaveNowHook);
	g_canSaveNowMenuAddr = (*(UInt32*)0x07CBDC8) + 5 + 0x07CBDC7;
	WriteRelCall(0x07CBDC7, (uintptr_t)CanSaveNowMenuHook);

	// SetCustomReputationChangeIcon
	WriteRelCall(0x6156A2, UInt32(GetReputationIconHook));
	WriteRelCall(0x6156FB, UInt32(GetReputationIconHook));
	WriteRelCall(0x615B19, UInt32(GetReputationMessageIconHook));
	WriteRelCall(0x615C04, UInt32(GetReputationMessageIconHook));
	WriteRelCall(0x61610A, UInt32(GetReputationMessageIconHook));
	WriteRelCall(0x616203, UInt32(GetReputationMessageIconHook));
	WriteRelCall(0x615855, UInt32(GetReputationMessageIconHook));
	WriteRelCall(0x61594C, UInt32(GetReputationMessageIconHook));
	WriteRelCall(0x615F0B, UInt32(GetReputationMessageIconHook));
	WriteRelCall(0x615E06, UInt32(GetReputationMessageIconHook));

	// Get/ModExtraMiscStat
	SafeWrite32(0x7DDAB1, UInt32(MiscStatRefreshHook));

	//Hairstyle handlers
	hk_RSMBarberHook::Hook();
	hk_BarterHook::CreateHook();

	WriteRelCall(0x8752F2, UInt32(SetViewmodelFrustumHook));

}
float timer22 = 30.0;
void HandleGameHooks() {
	HandleFixes();
	HandleIniOptions();
	HandleFunctionPatches();
	HandleGameSettingsJG();
	//  wip shit for void
	//	WriteRelCall(0x97E745, (UInt32)WantsToFleeHook);
	//	WriteRelCall(0x999082, (UInt32)WantsToFleeHook);
	//	WriteRelCall(0x9AAC17, (UInt32)WantsToFleeHook);
	//  SafeWrite32(0x8868CF, (UInt32)&timer22);
}
