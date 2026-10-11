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


		// Remove disabled/deleted refs during BGSDestructibleObjectForm::UpdateDestructibleObjects
		// Say the line Bart
		// 
		// call		TESForm::GetDisabledOrDeleted
		// test		al, al
		// jz		+26
		// push		[ebp - 0x10]
		// call		BGSDestructibleObjectForm::RemoveDestructibleObject
		// add		esp, 4
		// jmp		-79
		HookUtils::SafeWriteBuf(0x47734B, "\xE8\x40\x08\xFC\xFF\x84\xC0\x74\x1A\xFF\x75\xF0\xE8\xB4\x00\x00\x00\x83\xC4\x04\xEB\xAF");
	}

}
