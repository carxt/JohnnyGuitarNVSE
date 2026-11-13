#pragma once

class CachedValuesOwner {
public:
	CachedValuesOwner();
	~CachedValuesOwner();

	virtual float		CalculateCachedRadius();
	virtual float		CalculateCachedWidth();
	virtual float		CalculateCachedLength();
	virtual float		CalculateCachedHeight();
	virtual float		CalculateCachedDamagePerSecond();
	virtual float		CalculateCachedMedicineMult();
	virtual float		CalculateCachedSurvivalMult();
	virtual float		CalculateCachedParalysis();
	virtual float		CalculateCachedHealRate();
	virtual float		CalculateCachedFatigueReturnRate();
	virtual float		CalculateCachedPerceptionCondition();
	virtual float		CalculateCachedEyeLevel();
	virtual uint32_t	CalculateCachedAggression();
	virtual uint32_t	CalculateCachedAssistance();
	virtual float		CalculateCachedWalkSpeedMult();
	virtual float		CalculateCachedRunSpeedMult();
	virtual bool		CalculateCachedNoCrippledLegs();
};

ASSERT_SIZE(CachedValuesOwner, 0x004);