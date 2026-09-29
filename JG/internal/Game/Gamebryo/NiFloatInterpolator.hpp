#pragma once

#include "NiKeyBasedInterpolator.hpp"
#include "NiFloatData.hpp"

class NiFloatInterpolator : public NiKeyBasedInterpolator {
public:
	NiFloatInterpolator();
	virtual ~NiFloatInterpolator();

	float			m_fFloatValue;
	NiFloatDataPtr	m_spFloatData;
	uint32_t		m_uiLastIdx;

	NIRTTI_ADDRESS(0x11F3738);
};

ASSERT_SIZE(NiFloatInterpolator, 0x18);