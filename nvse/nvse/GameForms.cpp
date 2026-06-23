#include "GameForms.h"
#include "GameAPI.h"
#include "GameRTTI.h"
#include "GameObjects.h"
#include "GameData.h"

#if 1
static const ActorValueInfo** ActorValueInfoPointerArray = (const ActorValueInfo**)0x0011D61C8;		// See GetActorValueInfo
static const _GetActorValueInfo GetActorValueInfo = (_GetActorValueInfo)0x00066E920;	// See GetActorValueName
BGSDefaultObjectManager** g_defaultObjectManager = (BGSDefaultObjectManager**)0x011CA80C;
#else
static const ActorValueInfo** ActorValueInfoPointerArray = (const ActorValueInfo**)0;
static const _GetActorValueInfo GetActorValueInfo = (_GetActorValueInfo)0;
BGSDefaultObjectManager** g_defaultObjectManager = (BGSDefaultObjectManager**)0x0;
#endif

TESForm* __fastcall GetTESForm(const TESForm* apForm) {
	if (!apForm) 
		return nullptr;

	if (apForm->IsReference()) {
		const TESObjectREFR* refr = static_cast<const TESObjectREFR*>(apForm);
		if (refr->baseForm) 
			return refr->baseForm;
	}

	return const_cast<TESForm*>(apForm);
}

#if 0
TESFullName* TESForm::GetFullName() {
	if (typeID == FORM_TYPE::TESObjectCELL) // some exterior cells inherit name of parent worldspace
	{
		TESObjectCELL* cell = (TESObjectCELL*)this;
		TESFullName* fullName = &cell->fullName;
		if ((!fullName->name.pString || !fullName->name.GetLength()) && cell->worldSpace)
			return &cell->worldSpace->fullName;
		return fullName;
	}
	const TESForm* baseForm = IsReference() ? ((TESObjectREFR*)this)->baseForm : this;
	return DYNAMIC_CAST(baseForm, TESForm, TESFullName);
}

const char* TESForm::GetTheName() {
	TESFullName* fullName = GetFullName();
	return fullName ? fullName->name.c_str() : "";
}

TESForm* TESForm::CloneForm(bool persist) const {
	TESForm* result = CreateFormInstance(typeID);
	if (result) {
		result->CopyFrom(this);
		// it looks like some fields are not copied, case in point: TESObjectCONT does not copy BoundObject information.
		TESBoundObject* boundObject = DYNAMIC_CAST(result, TESForm, TESBoundObject);
		if (boundObject) {
			TESBoundObject* boundSource = DYNAMIC_CAST(this, TESForm, TESBoundObject);
			if (boundSource) {
				for (uint8_t i = 0; i < 6; i++)
					boundObject->bounds[i] = boundSource->bounds[i];
			}
		}
		DoAddForm(result, persist);
	}

	return result;
}
#endif

// static
uint32_t TESBipedModelForm::MaskForSlot(uint32_t slot) {
	switch (slot) {
		case ePart_Head:		return eSlot_Head;
		case ePart_Hair:		return eSlot_Hair;
		case ePart_UpperBody:	return eSlot_UpperBody;
		case ePart_LeftHand:	return eSlot_LeftHand;
		case ePart_RightHand:	return eSlot_RightHand;
		case ePart_Weapon:		return eSlot_Weapon;
		case ePart_PipBoy:		return eSlot_PipBoy;
		case ePart_Backpack:	return eSlot_Backpack;
		case ePart_Necklace:	return eSlot_Necklace;
		case ePart_Headband:	return eSlot_Headband;
		case ePart_Hat:			return eSlot_Hat;
		case ePart_Eyeglasses:	return eSlot_Eyeglasses;
		case ePart_Nosering:	return eSlot_Nosering;
		case ePart_Earrings:	return eSlot_Earrings;
		case ePart_Mask:		return eSlot_Mask;
		case ePart_Choker:		return eSlot_Choker;
		case ePart_MouthObject:	return eSlot_MouthObject;
		case ePart_BodyAddon1:	return eSlot_BodyAddon1;
		case ePart_BodyAddon2:	return eSlot_BodyAddon2;
		case ePart_BodyAddon3:	return eSlot_BodyAddon3;
		default:				return -1;
	}
}

uint32_t TESBipedModelForm::GetSlotsMask() const {
	return partMask;
}

void TESBipedModelForm::SetSlotsMask(uint32_t mask) {
	partMask = (mask & ePartBitMask_Full);
}

uint32_t TESBipedModelForm::GetBipedMask() const {
	return bipedFlags;
}

void TESBipedModelForm::SetBipedMask(uint32_t mask) {
	bipedFlags = mask & 0xFF;
}

void TESBipedModelForm::SetPath(const char* newPath, uint32_t whichPath, bool bFemalePath) {
	BSString* toSet = NULL;

	switch (whichPath) {
		case ePath_Biped:
			toSet = &bipedModel[bFemalePath ? 1 : 0].strModel;
			break;
		case ePath_Ground:
			toSet = &groundModel[bFemalePath ? 1 : 0].strModel;
			break;
		case ePath_Icon:
			toSet = &icon[bFemalePath ? 1 : 0].strTextureName;
			break;
	}

	if (toSet)
		toSet->Set(newPath);
}

const char* TESBipedModelForm::GetPath(uint32_t whichPath, bool bFemalePath) {
	BSString* pathStr = NULL;

	switch (whichPath) {
		case ePath_Biped:
			pathStr = &bipedModel[bFemalePath ? 1 : 0].strModel;
			break;
		case ePath_Ground:
			pathStr = &groundModel[bFemalePath ? 1 : 0].strModel;
			break;
		case ePath_Icon:
			pathStr = &icon[bFemalePath ? 1 : 0].strTextureName;
			break;
	}

	if (pathStr)
		return pathStr->pString;
	else
		return "";
}

char TESActorBaseData::GetFactionRank(TESFaction* faction) {
	auto pIter = factionList.GetHead();
	while (pIter && !pIter->IsEmpty()) {
		FactionRank* pRank = pIter->GetItem();
		if (pRank && pRank->pFaction == faction)
			return pRank->cRank;

		pIter = pIter->GetNext();
	}
	return -1;
}

static const uint8_t kHandGripTable[] =
{
	TESObjectWEAP::eHandGrip_Default,
	TESObjectWEAP::eHandGrip_1,
	TESObjectWEAP::eHandGrip_2,
	TESObjectWEAP::eHandGrip_3,
	TESObjectWEAP::eHandGrip_4,
	TESObjectWEAP::eHandGrip_5,
	TESObjectWEAP::eHandGrip_6,
};

uint8_t TESObjectWEAP::HandGrip() const {
	for (uint32_t i = 0; i < sizeof(kHandGripTable) / sizeof(kHandGripTable[0]); i++)
		if (handGrip == kHandGripTable[i])
			return i;

	return 0;
}

void TESObjectWEAP::SetHandGrip(uint8_t _handGrip) {
	if (_handGrip < sizeof(kHandGripTable) / sizeof(kHandGripTable[0]))
		handGrip = kHandGripTable[_handGrip];
}

uint8_t TESObjectWEAP::AttackAnimation() const {
	switch (attackAnim) {
		case eAttackAnim_Default:		return 0;
		case eAttackAnim_Attack3:		return 1;
		case eAttackAnim_Attack4:		return 2;
		case eAttackAnim_Attack5:		return 3;
		case eAttackAnim_Attack6:		return 4;
		case eAttackAnim_Attack7:		return 5;
		case eAttackAnim_Attack8:		return 6;
		case eAttackAnim_AttackLeft:	return 7;
		case eAttackAnim_AttackLoop:	return 8;
		case eAttackAnim_AttackRight:	return 9;
		case eAttackAnim_AttackSpin:	return 10;
		case eAttackAnim_AttackSpin2:	return 11;
		case eAttackAnim_AttackThrow:	return 12;
		case eAttackAnim_AttackThrow2:	return 13;
		case eAttackAnim_AttackThrow3:	return 14;
		case eAttackAnim_AttackThrow4:	return 15;
		case eAttackAnim_AttackThrow5:	return 16;
		case eAttackAnim_PlaceMine:		return 17;
		case eAttackAnim_PlaceMine2:	return 18;
		case eAttackAnim_Attack9:		return 19;
		case eAttackAnim_AttackThrow6:	return 20;
		case eAttackAnim_AttackThrow7:	return 21;
		case eAttackAnim_AttackThrow8:	return 22;
		default:						return 255;
	}
}

const uint8_t kAttackAnims[] = { 255, 38, 44, 50, 56, 62, 68, 26, 74, 32, 80, 86, 114, 120, 126, 132, 138, 102, 108, 144, 150, 156, 162 };

void TESObjectWEAP::SetAttackAnimation(uint32_t _attackAnim) {
	attackAnim = kAttackAnims[_attackAnim];
}

TESObjectIMOD* TESObjectWEAP::GetItemMod(uint8_t which) {
	if ((which < 1) || (which > 3)) return NULL;
	return itemMod[which - 1];
}

TESAmmo* TESObjectWEAP::GetAmmo() {
	if (!ammo.ammo) return NULL;
	if IS_ID(ammo.ammo, BGSListForm)
		return (TESAmmo*)((BGSListForm*)ammo.ammo)->GetFormList()->GetItem();
	return (TESAmmo*)ammo.ammo;
}

TESForm* TESObjectWEAP::GetAmmoInInventory()
{
	if (ammo.ammo) {
		if (IS_TYPE(ammo.ammo, BGSListForm)) {
			BGSListForm* ammoList = (BGSListForm*)ammo.ammo;
			ExtraContainerChanges* xChanges = PlayerCharacter::GetSingleton()->extraDataList.GetExtraData<ExtraContainerChanges>();
			if (ammoList && xChanges && xChanges->pChanges) {
				auto* pIter = ammoList->GetFormList();
				while (pIter && !pIter->IsEmpty()) {
					TESForm* pForm = pIter->GetItem();
					pIter = pIter->GetNext();

					if (IS_TYPE(pForm, TESAmmo)) {
						uint32_t count = ThisCall<uint32_t>(0x4C8F30, xChanges->pChanges, pForm);
						if (count > 0) 
							return pForm;
					}
				}
			}
		}
	}
	return nullptr;
}

class FindByForm {
	TESForm* m_pForm;
public:
	FindByForm(TESForm* pForm) : m_pForm(pForm) {}
	bool Accept(TESForm* pForm) const {
		return pForm && (pForm->GetFormID() == m_pForm->GetFormID()) ? true : false;
	}
};

bool TESPackage::IsFlagSet(uint32_t flag) {
	return (packageFlags & flag) == flag;
}

void TESPackage::SetFlag(uint32_t flag, bool bSet) {
	if (bSet)
		packageFlags |= flag;
	else
		packageFlags &= ~flag;

	// handle either-or flags
	switch (flag) {
		case kPackageFlag_LockDoorsAtStart:
			if (IsFlagSet(kPackageFlag_UnlockDoorsAtStart) == bSet)
				SetFlag(kPackageFlag_UnlockDoorsAtStart, !bSet);
			break;
		case kPackageFlag_UnlockDoorsAtStart:
			if (IsFlagSet(kPackageFlag_LockDoorsAtStart) == bSet)
				SetFlag(kPackageFlag_LockDoorsAtStart, !bSet);
			break;
		case kPackageFlag_LockDoorsAtEnd:
			if (IsFlagSet(kPackageFlag_UnlockDoorsAtEnd) == bSet)
				SetFlag(kPackageFlag_UnlockDoorsAtEnd, !bSet);
			break;
		case kPackageFlag_UnlockDoorsAtEnd:
			if (IsFlagSet(kPackageFlag_LockDoorsAtEnd) == bSet)
				SetFlag(kPackageFlag_LockDoorsAtEnd, !bSet);
			break;
		case kPackageFlag_LockDoorsAtLocation:
			if (IsFlagSet(kPackageFlag_UnlockDoorsAtLocation) == bSet)
				SetFlag(kPackageFlag_UnlockDoorsAtLocation, !bSet);
			break;
		case kPackageFlag_UnlockDoorsAtLocation:
			if (IsFlagSet(kPackageFlag_LockDoorsAtLocation) == bSet)
				SetFlag(kPackageFlag_LockDoorsAtLocation, !bSet);
			break;
	}
}

static const char* TESPackage_ObjectTypeStrings[TESPackage::kObjectType_Max] =
{
	"NONE", "Activators", "Armors", "Books", "Clothing", "Containers", "Doors", "Ingredients", "Lights", "Miscellaneous", "Flora", "Furniture",
	"Weapons: Any", "Ammo", "NPCs", "Creatures", "Keys", "Alchemy", "Food", "All: Combat Wearable", "All: Wearable", "Weapons: Ranged", "Weapons: Melee",
	"Weapons: NONE", "Actor Effects: Any", "Actor Effects: Range Target", "Actor Effects: Range Touch", "Actor Effects: Range Self"
};

// add 1 to code before indexing
static const char* TESPackage_DayStrings[] = {
	"Any", "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Weekdays", "Weekends", "MWF", "TT"
};

// add 1
static const char* TESPackage_MonthString[] = {
	"Any", "January", "February", "March", "April", "May", "June", "July", "August", "September",
	"October", "November", "December", "Spring", "Summer", "Autumn", "Winter"
};

static const char* TESPackage_LocationStrings[] = {
	"Reference", "Cell", "Current", "Editor", "Object", "ObjectType"
};

static const char* TESPackage_TypeStrings[] = {
	"Find", "Follow", "Escort", "Eat", "Sleep", "Wander", "Travel", "Accompany", "UseItemAt", "Ambush",
	"FleeNotCombat", "Sandbox", "Patrol", "Guard", "Dialogue", "UseWeapon"
};

static const char* TESPackage_ProcedureStrings[] = {
	"TRAVEL", "ACTIVATE", "ACQUIRE", "WAIT", "DIALOGUE", "GREET", "GREET DEAD", "WANDER", "SLEEP",
	"OBSERVE COMBAT", "EAT", "FOLLOW", "ESCORT", "COMBAT", "ALARM", "PURSUE", "FLEE", "DONE", "YELD",
	"TRAVEL TARGET", "CREATE FOLLOW", "GET UP", "MOUNT HORSE", "DISMOUNT HORSE", "DO NOTHING", "UNKNOWN 019", "UNKNOWN 01B",
	"ACCOMPANY", "USE ITEM AT", "AIM", "NOTIFY", "SANDMAN", "WAIT AMBUSH", "SURFACE", "WAIT FOR SPELL", "CHOOSE CAST",
	"FLEE NON COMBAT", "REMOVE WORN ITEMS", "SEARCH", "CLEAR MOUNT POSITION", "SUMMON CREATURE DEFEND", "AVOID AREA",
	"UNEQUIP ARMOR", "PATROL", "USE WEAPON", "DIALOGUE ACTIVATE", "GUARD", "SANDBOX", "USE IDLE MARKER", "TAKE BACK ITEM",
	"SITTING", "MOVEMENT BLOCKED", "CANIBAL FEED",
};

const char* TESPackage::StringForPackageType(uint32_t pkgType) {
	if (pkgType < kPackType_MAX) {
		return TESPackage_TypeStrings[pkgType];
	}
	else {
		return "";
	}
}

const char* TESPackage::StringForObjectCode(uint8_t objCode) {
	if (objCode < kObjectType_Max)
		return TESPackage_ObjectTypeStrings[objCode];

	return "";
}

uint8_t TESPackage::ObjectCodeForString(const char* objString) {
	for (uint32_t i = 0; i < kObjectType_Max; i++) {
		if (!_stricmp(objString, TESPackage_ObjectTypeStrings[i]))
			return i;
	}

	return kObjectType_Max;
}

#if 1
static const char** s_procNames = (const char**)0x011A3CC0;
#elif EDITOR
#else
#error unsupported Fallout version
#endif

const char* TESFaction::GetNthRankName(uint32_t whichRank, bool bFemale) {
	TESFaction::Rank* rank = ranks.GetNthItem(whichRank);
	if (!rank)
		return NULL;
	else
		return bFemale ? rank->femaleName.c_str() : rank->name.c_str();
}

void TESFaction::SetNthRankName(const char* newName, uint32_t whichRank, bool bFemale) {
	TESFaction::Rank* rank = ranks.GetNthItem(whichRank);
	if (rank) {
		if (bFemale)
			rank->femaleName.Set(newName);
		else
			rank->name.Set(newName);
	}
}

#if 0
uint32_t EffectItemList::CountItems() const {
	return list.Count();
}

EffectItem* EffectItemList::ItemAt(uint32_t whichItem) {
	return list.GetNthItem(whichItem);
}

const char* EffectItemList::GetNthEIName(uint32_t whichEffect) const {
	EffectItem* effItem = list.GetNthItem(whichEffect);
	if (effItem->setting)
		return GetFullName(effItem->setting);
	else
		return "<no name>";
}
#endif

BGSDefaultObjectManager* BGSDefaultObjectManager::GetSingleton() {
	return *g_defaultObjectManager;
}

bool AlchemyItem::IsPoison() {
	EffectItem* effItem;
	EffectSetting* effSetting = NULL;
	BSSimpleList<EffectItem*>* iter = magicItem.list.GetHead();
	do {
		if (!(effItem = iter->GetItem())) continue;
		effSetting = effItem->setting;
		if (effSetting && !(effSetting->effectFlags & 4)) return false;
	} while (iter = iter->GetNext());
	return effSetting != NULL;
}

// GAME - 0x541AC0
void TESObjectCELL::CellRefLockEnter() {
	ThisCall(0x541AC0, this);
}

// GAME - 0x541AE0
void TESObjectCELL::CellRefLockLeave() {
	ThisCall(0x541AE0, this);
}

bool TESContainer::ContainerCanHoldType(uint8_t aucFormType) {
	return CdeclCall<bool>(0x481F30, aucFormType);
}

bool TESContainer::ContainerCanHoldForm(const TESForm* apForm) {
	if (!apForm)
		return false;

	if (apForm->IsReference()) {
		const TESObjectREFR* pRef = static_cast<const TESObjectREFR*>(apForm);
		return ContainerCanHoldForm(pRef->baseForm);
	}
	else if (apForm->GetFormType() == FORM_TYPE::TESObjectLIGH) {
		const TESObjectLIGH* pLight = static_cast<const TESObjectLIGH*>(apForm);
		return pLight->GetCanCarry();
	}
	else {
		return ContainerCanHoldType(apForm->GetFormType());
	}
}
