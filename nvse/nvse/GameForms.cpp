#include "GameForms.h"
#ifdef GAME
#include "Bethesda/PlayerCharacter.hpp"
#include "Bethesda/ExtraContainerChanges.hpp"

TESAmmo* TESObjectWEAP::GetAmmo() {
	return ammo.GetAmmoHelper();
}

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