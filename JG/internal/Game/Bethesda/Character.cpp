#include "Character.hpp"
#include "TESNPC.hpp"

TESNPC* Character::GetActorBase() const {
	return static_cast<TESNPC*>(GetObjectReference());
}

// GAME - 0x8D3110
float Character::GetClothingValue() const {
	return ThisCall<float>(0x8D3110, this);
}

// GAME - 0x8D3FA0
void Character::Reset3D() {
	ThisCall(0x8D3FA0, this);
}
