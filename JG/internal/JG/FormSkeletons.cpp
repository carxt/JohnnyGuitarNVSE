#include "FormSkeletons.hpp"
#include "Bethesda/TESActorBase.hpp"

namespace FormSkeletons {

	HookUtils::CallDetour kCopyBoundDataDetour;
	void __fastcall CopyBoundAndModel(TESActorBase* apThis, void*, TESActorBase* apSource) {
		ThisCall(kCopyBoundDataDetour, apThis, apSource);
		ThisCall(0x489430, static_cast<TESModel*>(apThis), static_cast<TESModel*>(apSource));
	}

	void Install() {
		// Jazzoid stubs TESNPC::SetModel, so game can never set the model
		// Even when loading the form...
		// Restore the original call
		if (*reinterpret_cast<uint32_t*>(0x104A1BC) == 0x401290)
			HookUtils::SafeWrite32(0x104A1BC, 0x489100);

		// Skip SetModel calls, so the skelly is not replaced with the GameSetting values (sNPCModelMale, sNPCModelFemale)
		// These happen post form load
		HookUtils::WriteRelJump(0x95F26C, 0x95F2BF); // PlayerCharacter::QueuePlayerAnims
		HookUtils::WriteRelJump(0x60A672, 0x60A706); // TESNPC::LoadFaceGen

		// Allow inheritance for leveled NPCs (if they have the model inheritance flag checked)
		// Game already does this for Creatures
		kCopyBoundDataDetour.ReplaceCall(0x604E67, &CopyBoundAndModel);
	}

}