#include "Projectile.hpp"
#include "BGSProjectile.hpp"

// GAME - 0x4181E0
BGSProjectile* Projectile::GetProjectileBase() const {
	return static_cast<BGSProjectile*>(GetObjectReference());
}

// GAME - 0x9C3930
bool Projectile::GetMineReactsToTarget(const Actor* apTarget, const Actor* apShooterActor, const TESFaction* apOwnerFaction) const {
	return ThisCall<bool>(0x9C3930, this, apTarget, apShooterActor, apOwnerFaction);
}