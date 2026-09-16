#include "GameForms.h"
#include "GameAPI.h"
#include "GameRTTI.h"
#include "GameObjects.h"
#include "GameData.h"
#include "Bethesda/ExtraContainerChanges.hpp"

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
#ifdef GAME
	return ammo.GetAmmoHelper();
#else
	return nullptr;
#endif
}

TESForm* TESObjectWEAP::GetAmmoInInventory()
{
	if (ammo.pAmmo) {
		if (IS_TYPE(ammo.pAmmo, BGSListForm)) {
			BGSListForm* ammoList = (BGSListForm*)ammo.pAmmo;
			ExtraContainerChanges* xChanges = PlayerCharacter::GetSingleton()->extraDataList.GetExtraData<ExtraContainerChanges>();
			if (ammoList && xChanges && xChanges->pChanges) {
				auto* pIter = ammoList->GetFormList();
				while (pIter && !pIter->IsEmpty()) {
					TESForm* pForm = pIter->GetItem();
					pIter = pIter->GetNext();

					if (IS_TYPE(pForm, TESAmmo)) {
						uint32_t count = xChanges->pChanges->GetObjectCount(static_cast<TESAmmo*>(pForm));
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

#if 1
static const char** s_procNames = (const char**)0x011A3CC0;
#elif EDITOR
#else
#error unsupported Fallout version
#endif