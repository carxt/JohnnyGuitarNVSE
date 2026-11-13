#pragma once

#include "NiKeyBasedInterpolator.hpp"
#include "NiColor.hpp"
#include "NiColorData.hpp"

NiSmartPointer(NiColorInterpolator);

class NiColorInterpolator : public NiKeyBasedInterpolator {
public:
	NiColorInterpolator();
	virtual ~NiColorInterpolator();

	NiColorA		m_kColorValue;
	NiColorDataPtr	m_spColorData;
	uint32_t		m_uiLastIdx;

	CREATE_OBJECT(NiColorInterpolator, 0xA3C130);
	NIRTTI_ADDRESS(0x11F3730);
};

ASSERT_SIZE(NiColorInterpolator, 0x24)