#pragma once

#include "Projectile.hpp"

class FlameProjectile : public Projectile {
public:
	float fExpirationTimer;
	float fConeAngle;

	TESFORM_TYPE(FlameProjectile);
};

ASSERT_SIZE(FlameProjectile, 0x158);