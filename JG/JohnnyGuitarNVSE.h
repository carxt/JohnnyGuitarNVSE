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
void (*ApplyPerkModifiers)(UInt32 entryPointID, TESObjectREFR* perkOwner, void* arg3, ...) = (void (*)(UInt32, TESObjectREFR*, void*, ...))0x5E58F0;
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
bool capLoadScreensTo60 = 0;
bool fixNPCShootingAngle = 0;
bool noMuzzleFlashCooldown = 0;
bool enableRadioSubtitles = 0;
bool removeMainMenuMusic = 0;
bool fixDeathSounds = 0;
TESSound* questFailSound = 0;
TESSound* questNewSound = 0;
TESSound* questCompeteSound = 0;
TESSound* locationDiscoverSound = 0;
std::unordered_map<UInt32, char*> markerIconMap;
std::unordered_map <UInt32, std::vector<char*>> factionRepIcons;
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
Sky** g_currentSky = nullptr;
void(__thiscall* OriginalBipedModelUpdateWeapon)(ValidBip01Names*, TESObjectWEAP*, int) = (void(__thiscall*)(ValidBip01Names*, TESObjectWEAP*, int)) 0x4AB400;
UInt8(__thiscall* ContChangesEntry_GetWeaponModFlags)(ContChangesEntry* weapEntry) = (UInt8(__thiscall*)(ContChangesEntry*)) 0x4BD820;
std::unordered_set<BYTE> SaveGameUMap;
uintptr_t FNVCanSaveOriginalCall = 0;
uintptr_t FNVCanSaveMenuOriginalCall = 0;

TESObjectCELL* TESObjectREFR::GetParentCell()
{
	if (this->parentCell) return parentCell;
	ExtraPersistentCell* xPersistentCell = (ExtraPersistentCell*)this->extraDataList.GetByType(kExtraData_PersistentCell);
	if (xPersistentCell && xPersistentCell->persistentCell) return xPersistentCell->persistentCell;
	return nullptr;

}

double GetVectorAngle2D(NiPoint3* pt)
{
	double angle;
	if (pt->y == 0)
	{
		if (pt->x <= 0)
		{
			angle = kDblPIx3d2;
		}
		else
		{
			angle = kDblPId2;
		}
	}
	else
	{
		double ratio = pt->x / pt->y;
		angle = dAtan(ratio);
		if (pt->y < 0.0)
		{
			angle += kDblPI;
		}
	}

	return angle;
}


double GetAngleBetweenPoints(NiPoint3* actorPos, NiPoint3* playerPos, float offset)
{
	NiPoint3 diff;
	diff.Init(actorPos);
	diff.Subtract(playerPos);

	double angle = GetVectorAngle2D(&diff) - offset;
	if (angle > -kDblPI)
	{
		if (angle > kDblPI)
		{
			angle = kDblPIx2 - angle;
		}
	}
	else
	{
		angle += kDblPIx2;
	}
	return angle * 57.295779513;
}

ContChangesEntry* ExtraContainerChanges::EntryDataList::FindForItem(TESForm* item)
{
	ListNode<ContChangesEntry>* iter = this->Head();

	do {
		if (iter->data && iter->data->type == item) return iter->data;
	} while (iter = iter->next);

	return nullptr;
}

float __declspec(naked) __fastcall NiNodeComputeDistance(NiVector3* Vector1, NiVector3* Vector2)
{
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
NiNode* NiNode::GetNode(const char* nodeName)
{
	NiAVObject* found = GetBlock(nodeName);
	return found ? found->GetNiNode() : NULL;
}

__forceinline void NiPointAssign(NiPoint3* NiPointBuffer, float& xIn, float& yIn, float& zIn)
{
	NiPointBuffer->x = xIn;
	NiPointBuffer->y = yIn;
	NiPointBuffer->z = zIn;
}

UInt8 TESForm::GetOverridingModIdx()
{
	return mods.GetLastItem() ? mods.GetLastItem()->modIndex : 0xFF;
}

NiAVObject* NiNode::GetBlock(const char* blockName)
{
	if (StrEqualCI(m_blockName, blockName))
		return this;
	NiAVObject* found = NULL;
	for (NiTArray<NiAVObject*>::Iterator iter(m_children); !iter.End(); ++iter)
	{
		if (!*iter) continue;
		if (iter->GetNiNode())
			found = ((NiNode*)*iter)->GetBlock(blockName);
		else if (StrEqualCI(iter->m_blockName, blockName))
			found = *iter;
		else continue;
		if (found) break;
	}
	return found;
}

static void PatchMemoryNop(ULONG_PTR Address, SIZE_T Size)
{
	DWORD d = 0;
	VirtualProtect((LPVOID)Address, Size, PAGE_EXECUTE_READWRITE, &d);

	for (SIZE_T i = 0; i < Size; i++)
		*(volatile BYTE*)(Address + i) = 0x90; //0x90 == opcode for NOP

	VirtualProtect((LPVOID)Address, Size, d, &d);

	FlushInstructionCache(GetCurrentProcess(), (LPVOID)Address, Size);
}

bool __fastcall HookCanSaveNow(void* ThisObj, void* edx, int isAutoSave)
{
	return ThisStdCall_B(FNVCanSaveOriginalCall, ThisObj, isAutoSave) && SaveGameUMap.empty();
}

bool __fastcall HookCanSaveNowMenu(void* ThisObj, void* edx, int isAutoSave)
{
	return ThisStdCall_B(FNVCanSaveMenuOriginalCall, ThisObj, isAutoSave) && SaveGameUMap.empty();
}

void __fastcall hk_BipedModel_UpdateWeapon(ValidBip01Names* BipedAnim, Character* fnCharacter, TESObjectWEAP* weap, int weapMods)
{

	if (fnCharacter && fnCharacter->baseProcess)
	{
		if (auto weapInfo = fnCharacter->baseProcess->GetWeaponInfo())
		{
			weapMods = ContChangesEntry_GetWeaponModFlags(weapInfo);

		}

	}
	OriginalBipedModelUpdateWeapon(BipedAnim, weap, weapMods);
}

__declspec (naked) void asm_BipedModelUpdateWeapon()
{
	__asm
	{
		mov edx, dword ptr[ebp + 0x8]
		jmp hk_BipedModel_UpdateWeapon
	}
}

bool(__thiscall* GetPlayerInCombat)(Actor*, bool& IsNotDetected) = (bool(__thiscall*)(Actor*, bool&)) 0x0953C50;


bool __fastcall FleeFixHook(PlayerCharacter* Player, void* unused, bool& IsHidden)
{
	return (GetPlayerInCombat(Player, IsHidden) && !IsHidden);
}

char** DefaultMarkers = (char**)0x11A0404;

char* __fastcall hk_GetMapMarker(TESObjectREFR* thisObj, UInt16 MapMarkerType)
{

	auto it = markerIconMap.find(thisObj->refID);
	if (it != markerIconMap.end()) return it->second;
	return DefaultMarkers[MapMarkerType];
}

__declspec (naked) void AsmGetMapMarkerRoute()
{
	//UInt32 static const retAddr = 0x079D337;
	__asm
	{
		mov edx, eax
		mov ecx, [ebp - 0x24]
		jmp hk_GetMapMarker
	}
}

void __fastcall DisableMuzzleFlashLightsHook(ProjectileData* a1)
{
	if (*&a1->muzzleFlash && a1->projectile->lightMuzzleFlash) {
		if (!disableMuzzleLights || (disableMuzzleLights == 2 && a1->sourceActor != (Actor*)g_thePlayer) || (disableMuzzleLights == 3 && a1->sourceActor == (Actor*)g_thePlayer)) {
			NiNode* niNode = ThisStdCall<NiNode*>(0x50D810, a1->projectile->lightMuzzleFlash, 0, *&a1->muzzleFlash, 1);
			ThisStdCall(0x66B0D0, &a1->flashLight, niNode);
		}
	}
}
void SetCustomMapMarker(TESObjectREFR* marker, char* iconPath)
{

	auto pos = markerIconMap.find(marker->refID);
	char* pathCopy = new char[strlen(iconPath) + 1];
	strcpy(pathCopy, iconPath);

	if (pos != markerIconMap.end())
	{
		delete[] pos->second;
		pos->second = pathCopy;
	}
	else
	{
		markerIconMap.insert({ marker->refID, pathCopy });
	}
}


_declspec(naked) void LevelUpHook() {
	static const UInt32 noShowAddr = 0x77D903;
	static const UInt32 showAddr = 0x77D618;
	_asm {
		jne noLevelUp
		cmp dword ptr ds : [isShowLevelUp] , 0
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
					UInt32 count = ThisStdCall<UInt32>(0x4C8F30, xChanges->data, ammo);
					if (count > 0) return ammo;
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



__declspec(naked) void OnCloseContainerHook()
{
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

void patchFixDisintegrationsStat()
{
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
__declspec(naked) void FixNPCIncrementingChallenges() {
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
void __fastcall PlayQuestFailSound(Sound* sound, int dummy) {
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



void ResetVanityWheel()
{
	float* VanityWheel = (float*)0x11E0B5C;
	float* MaxChaseCam = (ThisStdCall<float*>((uintptr_t)0x0403E20, (void*)0x11CD568));
	if (*MaxChaseCam < *VanityWheel)
		*VanityWheel = *MaxChaseCam;
}


__declspec (naked) void hk_VanityModeBug()
{
	static uintptr_t jmpDest = 0x942D43;
	static uintptr_t getGS = 0x403E20;
	__asm
	{
		fstp dword ptr ds : [0x011E07C4]
		call ResetVanityWheel
		jmp jmpDest
	}

}
bool __fastcall ShouldPlayCombatMusic(UInt32* a1) {
	if (bCombatMusicDisabled) return false;
	return ThisStdCall_B(0x992D90, a1);
}
TESRegionDataMap* GetMapData(TESRegion* region) {
	if (region->dataEntries->Empty()) return nullptr;
	ListNode<TESRegionData>* iter = region->dataEntries->Head();
	TESRegionData* regData;
	do
	{
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
	do
	{
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

void __fastcall TESRegionDataSoundLoadIncidentalID(ModInfo* info, void* edx, UInt32* refID)
{
	ThisStdCall(0x4727F0, info, refID);
	if (*refID)
	{
		CdeclCall(0x485D50, refID, info);
	}
}



bool _fastcall HighProcessGetIsTalking(HighProcess* thisObj) {
	if (!thisObj) { return false; }
	uintptr_t* highProcessvTable = *((uintptr_t**)(thisObj));

}
/*
float __fastcall CFixDeathResponseCutOff(HighProcess* thisObj, Actor* Actor) {
	uintptr_t* highProcessvTable = *((uintptr_t**)(thisObj));
	float DyingTimer = ThisStdCall<float>(highProcessvTable[0x12C], thisObj); //GetDyingTimer, or Unk_12C, too lazy to name
	bool IsTalking = (ThisStdCall<bool>(0x08A67F0, Actor) && ThisStdCall<bool>(0x9336C0, Actor)); //Set whenever lipsync is playing iirc
	if (false && IsTalking) { return 1; }
	return DyingTimer;

}*/
float __fastcall CFixDeathResponseCutOff(HighProcess* thisObj, Actor* Actor) {
	uintptr_t* highProcessvTable = *((uintptr_t**)(thisObj));
	float DyingTimer = ThisStdCall<float>(highProcessvTable[0x12C], thisObj); //GetDyingTimer, or Unk_12C, too lazy to name
	bool IsTalking = !(Actor->unk80 & 1);
	if (IsTalking && (DyingTimer <= FLT_EPSILON)) { DyingTimer = FLT_EPSILON; }
	return DyingTimer;

}
__declspec (naked) void AsmFixDeathResponseCuttoffHandler() {
	static const uintptr_t  jumptGt = (uintptr_t)CFixDeathResponseCutOff;
	__asm {
		mov edx, dword ptr [ebp+8]
		jmp jumptGt
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

void HandleGameHooks()
{
	WriteRelJump(0x70809E, (UInt32)InventoryAmmoHook); // use available ammo in inventory instead of NULL when default ammo isn't present
	WriteRelJump(0xC5244A, (UInt32)NiCameraGetAltHook);
	WriteRelJump(0x77D612, UInt32(LevelUpHook)); // for ToggleLevelUpMenu
	SafeWrite32(0x10721AC, (UInt32)OnCloseContainerHook);
	WriteRelCall(0x9BAFED, (UInt32)DisableMuzzleFlashLightsHook); // for DisableMuzzleFlashLights
	SafeWrite16(0x79D330, 0x9090);
	WriteRelCall(0x79D332, (UInt32)AsmGetMapMarkerRoute);
	WriteRelCall(0x8B102B, (UInt32)VATSSpreadMultHook); // replace fNPCMaxWobbleAngle with 15.0 for VATS
	PatchMemoryNop(0x8A56C4, 4); // Fix for animations not working in dialog topics with sound
	PatchMemoryNop(0x8A56C8, 4);
	WriteRelJump(0x70F708, (UInt32)DisableArrowKeysHook);
	patchFixDisintegrationsStat();
	WriteRelJump(0x88D0D0, (UInt32)FixNPCIncrementingChallenges);
	WriteRelCall(0x77A8E9, (UInt32)PlayQuestFailSound);
	if (resetVanityCam) WriteRelJump(0x942D3D, (uintptr_t)hk_VanityModeBug);
	SafeWriteBuf(0x647902 + 1, "\xC8\xEA\x1C\x01", 4); // to use fWeapSkillReqPenalty correctly in spread calc
	WriteRelCall(0x82FC0B, (UInt32)ShouldPlayCombatMusic);
	//SaveGameHook
	FNVCanSaveOriginalCall = (*(UInt32*)0x0850443) + 5 + 0x0850442;
	WriteRelCall(0x0850442, (uintptr_t)HookCanSaveNow);
	FNVCanSaveMenuOriginalCall = (*(UInt32*)0x07CBDC8) + 5 + 0x07CBDC7;
	WriteRelCall(0x07CBDC7, (uintptr_t)HookCanSaveNowMenu);
	if (fixFleeing) WriteRelCall(0x8F5FE2, (UInt32)FleeFixHook);
	if (fixItemStacks) {
		WriteRelCall(0x780D11, (UInt32)DropItemHook);
		SafeWriteBuf(0x780D11 + 5, "\x90\x90\x90", 3);
	}
	if (loadEditorIDs) LoadEditorIDs();
	WriteRelCall(0x06061E8, (uintptr_t)asm_BipedModelUpdateWeapon);
	if (capLoadScreensTo60)SafeWrite8(0x78D4A4, 0x10);

	WriteRelCall(0x4F49AB, UInt32(TESRegionDataSoundLoadIncidentalID));
	if (fixNPCShootingAngle) PatchMemoryNop(0x9D13B2, 8);
	SafeWriteBuf(0x8BFBC1, "\x85\xC9\x74\x36\x80\x79\x04", 7); // missing null check in Actor::HandleStealing
	if (noMuzzleFlashCooldown)	SafeWriteBuf(0x9BB6A8, "\x90\x90", 2);
	if (enableRadioSubtitles) SafeWrite8(0x833876, 0x84);
	 //Fix for death topics getting cut off
	if (fixDeathSounds){
	SafeWrite16(0x8EC5C6, 0xBA90);
	SafeWrite32(0x8EC5C8, (uintptr_t)AsmFixDeathResponseCuttoffHandler); }
	if (removeMainMenuMusic) SafeWrite16(0x830109, 0x2574);
	WriteRelCall(0x6156A2, UInt32(GetReputationIconHook));	
	WriteRelCall(0x6156FB, UInt32(GetReputationIconHook));
}
