#include "NamedSpellLights.hpp"
#include "Bethesda/ActiveEffect.hpp"
#include "Bethesda/MagicSystem.hpp"
#include "Bethesda/SpellItem.hpp"
#include "Gamebryo/NiAVObject.hpp"

#include <GameRTTI.h>

#include "Shared/SafeWrite/SafeWrite.hpp"

namespace NamedSpellLights {

	STACK_FRAME_OPT_DISABLE
		NiAVObject* __fastcall SetLightNameHook(NiPointer<NiAVObject>& arLight) {
		uint8_t* pEBP = GetParentBasePtr(_AddressOfReturnAddress());
		const ActiveEffect* pEffect = *reinterpret_cast<ActiveEffect**>(pEBP - 0x60);
		const MagicItem* pSpell = pEffect->GetSpell();
		if (pSpell) [[likely]] {
			const TESForm* pMagicItemForm = DYNAMIC_CAST(pSpell, MagicItem, TESForm);
			if (pMagicItemForm) [[likely]] {
				const char* pEDID = pMagicItemForm->GetFormEditorID();
				if (pEDID && pEDID[0]) [[likely]] {
					char cName[MAX_PATH];
					our_snprintf(cName, sizeof(cName), "%s_PointLight", pEDID);
					arLight->SetName(cName);
				}
			}
		}
		return arLight.m_pObject;
	}
	STACK_FRAME_OPT_RESET

	void Install() {
		HookUtils::ReplaceCall(0x80ECD8, SetLightNameHook);
	}

}