#pragma once

#include "Projectile.hpp"

class BeamShaderProperty;

class BeamProjectile : public Projectile {
public:
	NiPointer<BeamShaderProperty> spBeamProperty;

	TESFORM_TYPE(BeamProjectile);
};

ASSERT_SIZE(BeamProjectile, 0x154);