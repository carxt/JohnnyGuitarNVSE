#include "BGSListForm.hpp"

// GAME - 0x500940
BSSimpleList<TESForm*>* BGSListForm::GetFormList() {
    return &kList;
}

// GAME - 0x500940
const BSSimpleList<TESForm*>* BGSListForm::GetFormList() const {
    return &kList;
}

// GAME - 0x58FF60
int32_t BGSListForm::GetItemIndex(const TESForm* apForm) const {
    return ThisCall<int32_t>(0x58FF60, this, apForm);
}
