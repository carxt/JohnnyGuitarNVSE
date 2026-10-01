#include "TESScriptableForm.hpp"
#include <GameRTTI.h>

// GAME - 0x726070
Script* TESScriptableForm::GetFormScript() const {
	return pScript;
}

// GAME - 0x6ECD40
void TESScriptableForm::SetFormScript(Script* apScript) {
	pScript = apScript;
}

// GAME - 0x4826D0
// GECK - 0x4A5870
Script* TESScriptableForm::GetFormScript(const TESForm* apForm) {
#ifdef GAME
	return CdeclCall<Script*>(0x4826D0, apForm);
#else
	return CdeclCall<Script*>(0x4A5870, apForm);
#endif
}

// GAME - 0x4CE300
void TESScriptableForm::SetFormScript(TESForm* apForm, Script* apScript) {
#ifdef GAME
	CdeclCall(0x4CE300, apForm, apScript);
#else
	TESScriptableForm* pScriptForm = DYNAMIC_CAST(apForm, TESForm, TESScriptableForm);
	if (pScriptForm)
		pScriptForm->SetFormScript(apScript);
#endif
}
