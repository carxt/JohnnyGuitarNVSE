#include "TESActorBase.hpp"

// GAME - 0x5F0CC0
SEX TESActorBase::GetSex() const {
    if (GetFormType() == FORM_TYPE::TESNPC)
        return SEX(IsFemale());

    return SEX::NONE;
}
