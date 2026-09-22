#include "DestructionFixes.hpp"
#include "Bethesda/TESForm.hpp"

#include "Shared/SafeWrite/SafeWrite.hpp"

namespace DestructionFixes {

	STACK_FRAME_OPT_ENABLE
	void __fastcall SetDeleteVirt(TESForm* apForm, void*, bool abDelete) {
		apForm->SetDelete(abDelete);
	}
	STACK_FRAME_OPT_RESET

	void Install() {
		// Simplify destruction stages check
		// TES Engine requires having a replacement model/explosion/debris or disablement in order to be considered valid
		// Which means if you only use BSDamageStages, or destruction instead of disablement... it won't work
		// CE only checks if data exists, and has stage count, which is what we replicate here (who's we?)
		HookUtils::SafeWriteBuf(0x475A32, "\x85\xC9\x7E\x49\xEB\x41");

		// TES Engine calls TESForm::SetDelete on the reference... instead of TESObjectREFR::SetDelete
		// This results in inproper cleanup of saved data
		// Naturally, fixed in CE...
		// I'm replacing it with a virtual call for better compat (sadly no space to do an inline write)
		HookUtils::ReplaceCall(0x475EA1, SetDeleteVirt);
	}

}
