#include "BipedAnimFixes.hpp"
#include "Bethesda/ItemChange.hpp"
#include "Bethesda/Actor.hpp"
#include <GameProcess.h>

#include "Shared/SafeWrite/SafeWrite.hpp"

namespace BipedAnimFixes {

	HookUtils::CallDetour kSetBipedWeaponDetour;
	STACK_FRAME_OPT_DISABLE
	void __fastcall SetBipedWeaponModFix(BipedAnim* apThis, void*, TESObjectWEAP* apWeapon, uint8_t aucModSlots) {
		uint8_t* pEBP = GetParentBasePtr(_AddressOfReturnAddress());
		TESObjectREFR* pReference = *reinterpret_cast<TESObjectREFR**>(pEBP + 0x8);
		if (pReference && pReference->IsActor()) {
			Actor* pActor = static_cast<Actor*>(pReference);
			if (pActor->GetCurrentAIProcess()) {
				ItemChange* pWeaponItem = pActor->GetCurrentAIProcess()->GetCurrentWeapon();
				if (pWeaponItem)
					aucModSlots = pWeaponItem->GetModSlots();
			}
		}
		ThisCall(kSetBipedWeaponDetour, apThis, apWeapon, aucModSlots);
	}
	STACK_FRAME_OPT_RESET

	HookUtils::CallDetour kRemoveAllExtraDetour;
	STACK_FRAME_OPT_ENABLE
	void __fastcall ReattachBSXFlags(NiAVObject* apObject) {
		const NiFixedString& rFlagsTag = BSXFlags::GetTag();
		NiPointer<NiExtraData> spFlags = apObject->GetExtraData(rFlagsTag);
		ThisCall(kRemoveAllExtraDetour, apObject);
		if (spFlags)
			apObject->AddExtraData(rFlagsTag, spFlags);
	}
	STACK_FRAME_OPT_RESET

	HookUtils::CallDetour kSetClonePtrDetour;
	STACK_FRAME_OPT_DISABLE
	NiRefObjectPtr* __fastcall AddControllerToBiped(NiRefObjectPtr* apThis, void*, NiAVObject* apClone) {
		uint8_t* pEBP = GetParentBasePtr(_AddressOfReturnAddress());
		NiAVObject* pNewObj = *reinterpret_cast<NiAVObject**>(pEBP - 0x18);
		if (pNewObj) {
			NiControllerManager* pCtrlMgr = apClone->GetController<NiControllerManager>();
			if (pCtrlMgr) {
				pNewObj->PrependController(pCtrlMgr);
				if (pCtrlMgr->m_spObjectPalette)
					pCtrlMgr->m_spObjectPalette->SetScene(pNewObj);
			}
		}
		return ThisCall<NiRefObjectPtr*>(kSetClonePtrDetour, apThis, apClone);
	}
	STACK_FRAME_OPT_RESET;

	HookUtils::CallDetour kFindSkinnedNodeDetour;
	STACK_FRAME_OPT_ENABLE
	bool __cdecl FindSkinnedNode(NiAVObject* apObject) {
		if (BSXFlags::GetFlags(apObject, BSXFlags::SKINNED_WEAPON))
			return false;

		return CdeclCall<bool>(kFindSkinnedNodeDetour, apObject);
	}
	STACK_FRAME_OPT_RESET

	void Install() {
		// Pass weapon mod flags during TESNPC::InitWornObject
		// Vaniller doesn't (the only spot where it's 0'd) so NPCs end up with wrong weapon models
		kSetBipedWeaponDetour.ReplaceCall(0x6061E8, SetBipedWeaponModFix);

		// Fix wrong checks in BipedAnim::RunBiped3DDetach
		// TLDR is, wrong order of operation and badly made checks
		// Havok removal no longer depends on object having a parent, and no longer is dependant on BSXFlags presence
		// Fixed in CE...
		HookUtils::SafeWriteBuf(0x4AB0F5, "\x89\x45\xFC\x90\x6A\x01");
		HookUtils::SafeWriteBuf(0x4AB10C, "\x8B\x45\xFC\x85\xC0\x74\x15\x90");

		// Allow skinned weapons
		// Fixed in CE...
		kFindSkinnedNodeDetour.ReplaceCall(0x4AF0FC, FindSkinnedNode);

		// Preserve BSXFlags in BipedAnim::LoadAndAttachAddOn
		// Fixed in, ffs, CE...
		kRemoveAllExtraDetour.ReplaceCall(0x4AF07A, ReattachBSXFlags);

		// Support existing NiControllerManagers
		// You can guess what'll say
		kSetClonePtrDetour.ReplaceCall(0x4AD44C, AddControllerToBiped);
	}
}