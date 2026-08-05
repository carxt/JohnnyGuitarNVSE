#include "BGSSaveFormBuffer.hpp"

// GAME - 0x865AD0
void BGSSaveFormBuffer::SetHeader(uint32_t auiFormID, uint32_t auiChangeFlags, FORM_TYPE aeFormType, uint8_t aucVersion) {
    ThisCall(0x865AD0, this, auiFormID, auiChangeFlags, aeFormType, aucVersion);
}

// GAME - 0x50F9C0
void BGSSaveFormBuffer::SetForm(TESForm* apForm) {
    pForm = apForm;
}

BGSChangeFlags BGSSaveFormBuffer::GetChangeFlags() const {
    return kHeader.uiChangeFlags;
}

// GAME - 0x5621F0
void BGSSaveFormBuffer::RemoveChange(uint32_t auiFlags) {
    ThisCall(0x5621F0, this, auiFlags);
}
