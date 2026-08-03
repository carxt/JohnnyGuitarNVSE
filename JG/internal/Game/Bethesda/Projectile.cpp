#include "Projectile.hpp"
#include "BGSProjectile.hpp"

// GAME - 0x4181E0
BGSProjectile* Projectile::GetProjectileBase() const {
	return static_cast<BGSProjectile*>(GetObjectReference());
}

bool Projectile::IsFlagSet(uint32_t auiFlag) const {
	return uiProjectileFlags.IsSet(auiFlag);
}

// GAME - 0x9B7010
NiPoint3 Projectile::GetMovementDirection() const {
	return kMovementDirection;
}

// GAME - 0x9C3930
bool Projectile::GetMineReactsToTarget(const Actor* apTarget, const Actor* apShooterActor, const TESFaction* apOwnerFaction) const {
	return ThisCall<bool>(0x9C3930, this, apTarget, apShooterActor, apOwnerFaction);
}