#include "Creature.hpp"
#include "TESCreature.hpp"

TESCreature* Creature::GetActorBase() const {
	return static_cast<TESCreature*>(GetObjectReference());
}