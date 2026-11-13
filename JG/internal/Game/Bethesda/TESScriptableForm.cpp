#include "TESScriptableForm.hpp"
#include "Script.hpp"
#include <GameRTTI.h>

// GAME - 0x726070
Script* TESScriptableForm::GetFormScript() const {
	return pScript;
}

// GAME - 0x6ECD40
void TESScriptableForm::SetFormScript(Script* apScript) {
	pScript = apScript;
}

const char* TESScriptableForm::GetFormScriptEditorID() const {
	return pScript ? pScript->GetFormEditorID() : "";
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

// GECK - 0x509EC0
const char* TESScriptableForm::GetFormScriptEditorID(const TESForm* apForm) {
#ifdef GAME
	const Script* pScript = GetFormScript(apForm);
	return pScript ? pScript->GetFormEditorID() : "";
#else
	return CdeclCall<const char*>(0x509EC0, apForm);
#endif
}
