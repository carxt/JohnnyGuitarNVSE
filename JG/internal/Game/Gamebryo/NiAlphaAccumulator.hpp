#pragma once

#include "NiBackToFrontAccumulator.hpp"

NiSmartPointer(NiAlphaAccumulator);

class NiAlphaAccumulator : public NiBackToFrontAccumulator {
public:
	NiAlphaAccumulator();
	virtual ~NiAlphaAccumulator();

	bool m_bObserveNoSortHint;
	bool m_bSortByClosestPoint;
	bool m_bInterfaceSort;

	CREATE_OBJECT(NiAlphaAccumulator, 0xA9B4B0);
	NIRTTI_ADDRESS(0x11F5F74);
};

ASSERT_SIZE(NiAlphaAccumulator, 0x34);