#include "GameExtraData.h"
#include "GameBSExtraData.h"
#include "GameApi.h"
#include "GameObjects.h"
#include "GameRTTI.h"
#include "GameScript.h"

struct GetMatchingEquipped {
	FormMatcher& m_matcher;
	EquipData m_found;

	GetMatchingEquipped(FormMatcher& matcher) : m_matcher(matcher) {
		m_found.pForm = NULL;
		m_found.pExtraData = NULL;
	}

	bool Accept(ExtraContainerChanges::EntryData* pEntryData) {
		if (pEntryData) {
			// quick check - needs an extendData or can't be equipped
			ExtraContainerChanges::ExtendDataList* pExtendList = pEntryData->extendData;
			if (pExtendList && m_matcher.Matches(pEntryData->type)) {
				SInt32 n = 0;
				ExtraDataList* pExtraDataList = pExtendList->GetNthItem(n);
				while (pExtraDataList) {
					if (pExtraDataList->HasType(kExtraData_Worn) || pExtraDataList->HasType(kExtraData_WornLeft)) {
						m_found.pForm = pEntryData->type;
						m_found.pExtraData = pExtraDataList;
						return false;
					}
					n++;
					pExtraDataList = pExtendList->GetNthItem(n);
				}
			}
		}
		return true;
	}

	EquipData Found() {
		return m_found;
	}
};

EquipData ExtraContainerChanges::FindEquipped(FormMatcher& matcher) const {
	FoundEquipData equipData;
	if (data && data->objList) {
		GetMatchingEquipped getEquipped(matcher);
		data->objList->Visit(getEquipped);
		equipData = getEquipped.Found();
	}
	return equipData;
};

STATIC_ASSERT(sizeof(ExtraHealth) == 0x10);
STATIC_ASSERT(sizeof(ExtraLock) == 0x10);
STATIC_ASSERT(sizeof(ExtraCount) == 0x10);
STATIC_ASSERT(sizeof(ExtraTeleport) == 0x10);

STATIC_ASSERT(sizeof(ExtraWorn) == 0x0C);
STATIC_ASSERT(sizeof(ExtraWornLeft) == 0x0C);
STATIC_ASSERT(sizeof(ExtraCannotWear) == 0x0C);
STATIC_ASSERT(sizeof(ExtraContainerChanges::EntryData) == 0x0C);

#if RUNTIME_VERSION == RUNTIME_VERSION_1_4_0_525
static const UInt32 s_ExtraContainerChangesVtbl = 0x01015BB8;	//	0x0100fb78;
static const UInt32 s_ExtraWornVtbl = 0x01015BDC;
//static const UInt32 s_ExtraWornLeftVtbl							= 0x01015BE8;
static const UInt32 s_ExtraCannotWearVtbl = 0x01015BF4;

static const UInt32 s_ExtraOwnershipVtbl = 0x010158B4;	//	0x0100f874;
static const UInt32 s_ExtraRankVtbl = 0x010158CC;	//	0x0100f88c;
static const UInt32 s_ExtraActionVtbl = 0x01015BAC;
static const UInt32 s_ExtraFactionChangesVtbl = 0x01015F30;
static const UInt32 s_ExtraScriptVtbl = 0X1015914;

//static const UInt32 s_ExtraScript_init							= 0x0042C760;

static const UInt32 s_ExtraHealthVtbl = 0x010158E4;
static const UInt32 s_ExtraLockVtbl = 0x0101589C;
static const UInt32 s_ExtraCountVtbl = 0x010158D8;
static const UInt32 s_ExtraTeleportVtbl = 0x010158A8;
static const UInt32 s_ExtraWeaponModFlagsVtbl = 0x010159A4;

static const UInt32 s_ExtraHotkeyVtbl = 0x0101592C;

static const UInt32 s_ExtraSemaphore = 0x011C3920;
static const UInt32 s_SemaphoreWait = 0x0040FBF0;
static const UInt32 s_SemaphoreLeave = 0x0040FBA0;

#else
#error
#endif

static void** g_ExtraSemaphore = (void**)s_ExtraSemaphore;

void* GetExtraSemaphore() {
	return *g_ExtraSemaphore;
};

void CallSemaphore(void* Semaphore, UInt32 SemaphoreFunc) {
	_asm pushad
	_asm mov ecx, Semaphore
	_asm call SemaphoreFunc
	_asm popad
};

void CallSemaphore4(void* Semaphore, UInt32 SemaphoreFunc) {
	_asm pushad
	_asm push ecx;	does not seem to be used at all
	_asm mov ecx, Semaphore
	_asm call SemaphoreFunc
	_asm popad
};

ExtraContainerChanges::ExtendDataList* ExtraContainerChangesExtendDataListCreate(ExtraDataList* pExtraDataList) {
	ExtraContainerChanges::ExtendDataList* xData = (ExtraContainerChanges::ExtendDataList*)GameHeapAlloc(sizeof(ExtraContainerChanges::ExtendDataList));
	xData->Init();
	if (pExtraDataList) xData->Append(pExtraDataList);
	return xData;
}

static void ExtraContainerChangesExtendDataListFree(ExtraContainerChanges::ExtendDataList* xData, bool bFreeList) {
	if (xData) {
		if (bFreeList) xData->Clear();
		GameHeapFree(xData);
	}
}

void ExtraContainerChanges::EntryData::Cleanup() {
	if (!extendData) return;
	ListNode<ExtraDataList>* xdlIter = extendData->Head(), * prev = NULL;;
	ExtraDataList* xData;
	ExtraCount* xCount;
	do {
		xData = xdlIter->data;
		if (xData) {
			xCount = (ExtraCount*)xData->GetByType(kExtraData_Count);
			if (xCount && (xCount->count <= 1)) xData->RemoveByType(kExtraData_Count);
			if (xData->m_data) {
				prev = xdlIter;
				xdlIter = xdlIter->next;
				continue;
			}
		}
		GameHeapFree(xData);
		xdlIter = prev ? prev->RemoveNext() : xdlIter->RemoveMe();
	} while (xdlIter);
}

ExtraContainerChanges* ExtraContainerChanges::Create() {
	UInt32* dataPtr = (UInt32*)GameHeapAlloc(sizeof(ExtraContainerChanges));
	dataPtr[0] = kVtbl_ExtraContainerChanges;
	dataPtr[1] = kExtraData_ContainerChanges;
	dataPtr[2] = 0;
	dataPtr[3] = 0;
	return (ExtraContainerChanges*)dataPtr;
}

ExtraContainerChanges::Data* ExtraContainerChanges::Data::Create(TESObjectREFR* owner) {
	Data* data = (Data*)GameHeapAlloc(sizeof(Data));
	MemZero(data, sizeof(Data));
	data->owner = owner;
	data->objList = (EntryDataList*)GameHeapAlloc(sizeof(EntryDataList));
	data->objList->Init();
	return data;
}

void ExtraContainerChanges::Cleanup() {
	if (data && data->objList) {
		ListNode<EntryData>* entryIter = data->objList->Head();
		do {
			if (entryIter->data)
				entryIter->data->Cleanup();
		} while (entryIter = entryIter->next);
	}
}

BSExtraData* BSExtraData::Create(UInt8 xType, UInt32 size, UInt32 vtbl) {
	BSExtraData* xData = (BSExtraData*)GameHeapAlloc(size);
	MemZero(xData, size);
	*(UInt32*)xData = vtbl;
	xData->type = xType;
	return xData;
}

ExtraHealth* ExtraHealth::Create(float _health) {
	UInt32* dataPtr = (UInt32*)GameHeapAlloc(sizeof(ExtraHealth));
	dataPtr[0] = kVtbl_ExtraHealth;
	dataPtr[1] = kExtraData_Health;
	dataPtr[2] = 0;
	ExtraHealth* xHealth = (ExtraHealth*)dataPtr;
	xHealth->health = _health;
	return xHealth;
}

ExtraWorn* ExtraWorn::Create() {
	UInt32* dataPtr = (UInt32*)GameHeapAlloc(sizeof(ExtraWorn));
	dataPtr[0] = kVtbl_ExtraWorn;
	dataPtr[1] = kExtraData_Worn;
	dataPtr[2] = 0;
	return (ExtraWorn*)dataPtr;
}

ExtraCannotWear* ExtraCannotWear::Create() {
	UInt32* dataPtr = (UInt32*)GameHeapAlloc(sizeof(ExtraCannotWear));
	dataPtr[0] = kVtbl_ExtraCannotWear;
	dataPtr[1] = kExtraData_CannotWear;
	dataPtr[2] = 0;
	return (ExtraCannotWear*)dataPtr;
}

ExtraLock* ExtraLock::Create() {
	UInt32* dataPtr = (UInt32*)GameHeapAlloc(sizeof(ExtraLock));
	dataPtr[0] = kVtbl_ExtraLock;
	dataPtr[1] = kExtraData_Lock;
	dataPtr[2] = 0;
	UInt32* lockData = (UInt32*)GameHeapAlloc(sizeof(Data));
	MemZero(lockData, sizeof(Data));
	dataPtr[3] = (UInt32)lockData;
	return (ExtraLock*)dataPtr;
}

ExtraCount* ExtraCount::Create(UInt32 count) {
	UInt32* dataPtr = (UInt32*)GameHeapAlloc(sizeof(ExtraCount));
	dataPtr[0] = kVtbl_ExtraCount;
	dataPtr[1] = kExtraData_Count;
	dataPtr[2] = 0;
	dataPtr[3] = count;
	return (ExtraCount*)dataPtr;
}

ExtraTeleport* ExtraTeleport::Create() {
	UInt32* dataPtr = (UInt32*)GameHeapAlloc(sizeof(ExtraTeleport));
	dataPtr[0] = kVtbl_ExtraTeleport;
	dataPtr[1] = kExtraData_Teleport;
	dataPtr[2] = 0;
	UInt32* teleData = (UInt32*)GameHeapAlloc(sizeof(Data));
	MemZero(teleData, sizeof(Data));
	dataPtr[3] = (UInt32)teleData;
	return (ExtraTeleport*)dataPtr;
}

ExtraWeaponModFlags* ExtraWeaponModFlags::Create(UInt8 _flags) {
	UInt32* dataPtr = (UInt32*)GameHeapAlloc(sizeof(ExtraWeaponModFlags));
	dataPtr[0] = kVtbl_ExtraWeaponModFlags;
	dataPtr[1] = kExtraData_WeaponModFlags;
	dataPtr[2] = 0;
	dataPtr[3] = _flags;
	return (ExtraWeaponModFlags*)dataPtr;
}

UInt32 GetCountForExtraDataList(ExtraDataList* list) {
	if (!list)
		return 1;

	ExtraCount* xCount = (ExtraCount*)list->GetByType(kExtraData_Count);
	return xCount ? xCount->count : 1;
}

ExtraOwnership* ExtraOwnership::Create(TESForm* _owner) {
	UInt32* dataPtr = (UInt32*)GameHeapAlloc(sizeof(ExtraOwnership));
	dataPtr[0] = kVtbl_ExtraOwnership;
	dataPtr[1] = kExtraData_Ownership;
	dataPtr[2] = 0;
	dataPtr[3] = (UInt32)_owner;
	return (ExtraOwnership*)dataPtr;
}

ExtraRank* ExtraRank::Create(UInt32 _rank) {
	UInt32* dataPtr = (UInt32*)GameHeapAlloc(sizeof(ExtraRank));
	dataPtr[0] = kVtbl_ExtraRank;
	dataPtr[1] = kExtraData_Rank;
	dataPtr[2] = 0;
	dataPtr[3] = _rank;
	return (ExtraRank*)dataPtr;
}

ExtraAction* ExtraAction::Create(TESObjectREFR* _actionRef) {
	UInt32* dataPtr = (UInt32*)GameHeapAlloc(sizeof(ExtraAction));
	dataPtr[0] = kVtbl_ExtraAction;
	dataPtr[1] = kExtraData_Action;
	dataPtr[2] = 0;
	dataPtr[3] = 0;
	dataPtr[4] = (UInt32)_actionRef;
	return (ExtraAction*)dataPtr;
}

class TESScript;
class TESScriptableForm;

ExtraScript* ExtraScript::Create(TESForm* baseForm, bool create, TESObjectREFR* container) {
	UInt32* dataPtr = (UInt32*)GameHeapAlloc(sizeof(ExtraScript));
	dataPtr[0] = kVtbl_ExtraScript;
	dataPtr[1] = kExtraData_Script;
	dataPtr[2] = 0;
	dataPtr[3] = 0;
	dataPtr[4] = 0;
	ExtraScript* xScript = (ExtraScript*)dataPtr;
	if (baseForm) {
		TESScriptableForm* scriptable = DYNAMIC_CAST(baseForm, TESForm, TESScriptableForm);
		if (scriptable && scriptable->script) {
			xScript->script = scriptable->script;
			if (create) {
				ScriptEventList::Event* pEvent = (ScriptEventList::Event*)GameHeapAlloc(sizeof(ScriptEventList));
				pEvent->eventMask = ScriptEventList::kEvent_OnAdd;
				pEvent->object = container;
				ScriptEventList* pEventList = xScript->script->CreateEventList();
				if (pEventList) {
					xScript->eventList = pEventList;
					if (!pEventList->m_eventList) {
						pEventList->m_eventList = (ScriptEventList::EventList*)GameHeapAlloc(sizeof(ScriptEventList::EventList));
						pEventList->m_eventList->Init();
						pEventList->m_eventList->Insert(pEvent);
					}
				}
			}
		}
	}
	return xScript;
}

ExtraFactionChanges* ExtraFactionChanges::Create() {
	UInt32* dataPtr = (UInt32*)GameHeapAlloc(sizeof(ExtraFactionChanges));
	dataPtr[0] = kVtbl_ExtraFactionChanges;
	dataPtr[1] = kExtraData_FactionChanges;
	dataPtr[2] = 0;
	UInt32* listData = (UInt32*)GameHeapAlloc(sizeof(FactionListEntry));
	listData[0] = 0;
	listData[1] = 0;
	dataPtr[3] = (UInt32)listData;
	return (ExtraFactionChanges*)dataPtr;
}

ExtraFactionChanges::FactionListEntry* GetExtraFactionList(BaseExtraList& xDataList) {
	ExtraFactionChanges* xFactionChanges = GetExtraType(xDataList, FactionChanges);
	if (xFactionChanges)
		return xFactionChanges->data;
	return NULL;
}

void SetExtraFactionRank(BaseExtraList& xDataList, TESFaction* faction, char rank) {
	FactionListData* pData = NULL;
	ExtraFactionChanges* xFactionChanges = GetExtraType(xDataList, FactionChanges);
	if (xFactionChanges && xFactionChanges->data) {
		ExtraFactionChangesMatcher matcher(faction, xFactionChanges);
		pData = xFactionChanges->data->Find(matcher);
		if (pData)
			pData->rank = rank;
	}
	if (!pData) {
		if (!xFactionChanges) {
			xFactionChanges = ExtraFactionChanges::Create();
			xDataList.Add(xFactionChanges);
		}
		pData = (FactionListData*)GameHeapAlloc(sizeof(FactionListData));
		if (pData) {
			pData->faction = faction;
			pData->rank = rank;
			xFactionChanges->data->Append(pData);
		}
	}
}

ExtraHotkey* ExtraHotkey::Create(UInt8 _index) {
	UInt32* dataPtr = (UInt32*)GameHeapAlloc(sizeof(ExtraHotkey));
	dataPtr[0] = kVtbl_ExtraHotkey;
	dataPtr[1] = kExtraData_Hotkey;
	dataPtr[2] = 0;
	dataPtr[3] = _index;
	return (ExtraHotkey*)dataPtr;
}