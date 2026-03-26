#include "TESScriptableForm.hpp"

// GAME - 0x726070
Script* TESScriptableForm::GetFormScript() const {
	return pScript;
}

// GAME - 0x4826D0
Script* TESScriptableForm::GetFormScript(TESForm* apForm) {
	return CdeclCall<Script*>(0x4826D0, apForm);
}
