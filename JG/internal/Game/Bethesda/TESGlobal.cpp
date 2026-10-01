#include "TESGlobal.hpp"

// GAME - 0x529EA0
uint8_t TESGlobal::GetType() const {
    return ucType;
}

// GAME - 0x526AC0
float TESGlobal::GetValue() const {
    return fValue;
}

// GAME - 0x46DCE0
void TESGlobal::SetValue(float afValue) {
	fValue = afValue;
}
