#pragma once

#include "Bethesda/Projectile.hpp"

class BeamShaderProperty;

class ContinuousBeamProjectile : public Projectile {
public:
	NiPointer<BeamShaderProperty>	spBeamProperty;
	int32_t							iShotsFired;

	TESFORM_TYPE(ContinuousBeamProjectile);
};

ASSERT_SIZE(ContinuousBeamProjectile, 0x158);