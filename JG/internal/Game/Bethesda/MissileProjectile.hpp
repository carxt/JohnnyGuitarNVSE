#pragma once

#include "Projectile.hpp"

class MissileProjectile : public Projectile {
public:
	struct _ImpactResult {
		enum Result {
			NONE	= 0,
			DESTROY	= 1,
			BOUNCE	= 2,
			IMPALE	= 3,
			STICK	= 4,
		};
	};
	using ImpactResult = _ImpactResult::Result;

	ImpactResult	eImpactResult;
	bool			bWaitingToInitialize3D;
	float			fStickTime;
	float			fLocalRot;

	TESFORM_TYPE(MissileProjectile);
};

ASSERT_SIZE(MissileProjectile, 0x160);