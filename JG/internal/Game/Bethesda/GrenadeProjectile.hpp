#pragma once

#include "Projectile.hpp"

class GrenadeProjectile : public Projectile {
public:
	bool bCollisionGroupReset;

	TESFORM_TYPE(GrenadeProjectile);
};

ASSERT_SIZE(GrenadeProjectile, 0x154);