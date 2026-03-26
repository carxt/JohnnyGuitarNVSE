#include "TESImageSpaceModifiableForm.hpp"

// GAME - 0x726070
TESImageSpaceModifier* TESImageSpaceModifiableForm::GetFormImageSpaceModifier() const {
    return pImageSpaceModifier;
}

// GAME - 0x6ECD40
void TESImageSpaceModifiableForm::SetFormImageSpaceModifier(TESImageSpaceModifier* apModifier) {
	pImageSpaceModifier = apModifier;
}
