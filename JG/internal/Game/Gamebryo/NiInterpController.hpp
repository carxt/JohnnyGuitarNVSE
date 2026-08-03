#pragma once

#include "NiTimeController.hpp"

class NiInterpolator;
class NiBlendInterpolator;

NiSmartPointer(NiInterpController);

class NiInterpController : public NiTimeController {
public:
	NiInterpController();
	virtual ~NiInterpController();

	virtual uint16_t				GetInterpolatorCount() const;
	virtual const char*				GetInterpolatorID(uint16_t ausIndex = 0) const;
	virtual uint16_t				GetInterpolatorIndex(const char* apID) const;
	virtual uint16_t				GetInterpolatorIndexFx(uint16_t ausIndex = 0) const;
	virtual NiInterpolator*			GetInterpolator(uint16_t ausIndex = 0) const;
	virtual void					SetInterpolator(NiInterpolator* apInterpolator, uint16_t ausIndex = 0);
	virtual void					ResetTimeExtrema();
	virtual uint32_t				GetCtlrID() const;
	virtual NiInterpolator*			CreatePoseInterpolator(uint16_t ausIndex = 0);
	virtual void					SynchronizePoseInterpolator(NiInterpolator* apInterpolator, uint16_t ausIndex = 0);
	virtual NiBlendInterpolator*	CreateBlendInterpolator(uint16_t ausIndex = 0, bool abManagerControlled = false, bool abAccumulateAnimations = false, float afWeightThreshold = 0.0f, uint8_t aucArraySize = 2);
	virtual void					GuaranteeTimeRange(float afStartTime, float afEndTime);
	virtual bool					InterpolatorIsCorrectType(NiInterpolator* apInterpolator, uint16_t ausIndex = 0) const;

	NIRTTI_ADDRESS(0x11F36B4);

	static constexpr uint16_t	INVALID_INDEX	= UINT16_MAX;
	static constexpr float		INVALID_TIME	= -FLT_MAX;

	void SetManagerControlled(bool abManagerControlled);
	bool GetManagerControlled() const;
};

ASSERT_SIZE(NiInterpController, 0x34)