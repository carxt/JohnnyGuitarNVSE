#include "MagicTarget.hpp"

// GAME - 0x8248E0
void MagicTarget::Dispel(TESBoundObject* apEnchantmentSource, bool abNow) {
	ThisCall(0x8248E0, this, apEnchantmentSource, abNow);
}

// GAME - 0x822B40
Actor* MagicTarget::GetTargetAsActor() const {
	return ThisCall<Actor*>(0x822B40, this);
}

// GAME - 0x822E00
bool MagicTarget::HasDamageHealthEffect() const {
	return ThisCall<bool>(0x822E00, this);
}