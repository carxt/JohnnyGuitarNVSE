#include "Character.hpp"
#include "TESNPC.hpp"

TESNPC* Character::GetActorBase() const {
	return static_cast<TESNPC*>(GetObjectReference());
}