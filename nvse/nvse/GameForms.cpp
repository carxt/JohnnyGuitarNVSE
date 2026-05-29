#include "GameForms.h"
#include "GameAPI.h"
#include "GameRTTI.h"
#include "GameObjects.h"
#include "GameData.h"

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

TESAmmo* TESObjectWEAP::GetAmmo(Actor* apActor) {
	return ThisCall<TESAmmo*>(0x525980, this, apActor);
}

TESForm* TESObjectWEAP::GetAmmoInInventory()
{
	BGSListForm* pAmmoList = ammo.GetAmmoFormList();
	if (pAmmoList) {
		ExtraContainerChanges* xChanges = PlayerCharacter::GetSingleton()->extraDataList.GetExtraData<ExtraContainerChanges>();
		if (pAmmoList && xChanges && xChanges->pChanges) {
			auto pIter = pAmmoList->GetFormList();
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

bool AlchemyItem::IsPoison() {
	return magicItem.CanBePoison();
}

// GAME - 0x541AC0
void TESObjectCELL::CellRefLockEnter() {
	ThisCall(0x541AC0, this);
}

// GAME - 0x541AE0
void TESObjectCELL::CellRefLockLeave() {
	ThisCall(0x541AE0, this);
}
