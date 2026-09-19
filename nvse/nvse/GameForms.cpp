#include "GameForms.h"
#include "GameObjects.h"
#include "Bethesda/ExtraContainerChanges.hpp"

TESForm* __fastcall GetTESForm(const TESForm* apForm) {
	if (!apForm) 
		return nullptr;

	if (apForm->IsReference()) {
		const TESObjectREFR* refr = static_cast<const TESObjectREFR*>(apForm);
		if (refr->GetObjectReference()) 
			return refr->GetObjectReference();
	}

	return const_cast<TESForm*>(apForm);
}

TESAmmo* TESObjectWEAP::GetAmmo() {
#ifdef GAME
	return ammo.GetAmmoHelper();
#else
	return nullptr;
#endif
}

#ifdef GAME
TESForm* TESObjectWEAP::GetAmmoInInventory()
{
	if (ammo.pAmmo) {
		if (IS_TYPE(ammo.pAmmo, BGSListForm)) {
			BGSListForm* ammoList = (BGSListForm*)ammo.pAmmo;
			ExtraContainerChanges* xChanges = PlayerCharacter::GetSingleton()->GetExtra()->GetExtraData<ExtraContainerChanges>();
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
#endif