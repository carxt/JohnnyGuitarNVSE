#pragma once

#include "NiAccumulator.hpp"
#include "NiTPointerList.hpp"

class NiGeometry;

NiSmartPointer(NiBackToFrontAccumulator);

class NiBackToFrontAccumulator : public NiAccumulator {
public:
	NiBackToFrontAccumulator();
	virtual ~NiBackToFrontAccumulator();

	virtual void Sort();

	NiTPointerList<NiGeometry*>		m_kItems;
	NiTPointerList<NiGeometry*>*	m_pGeometryList;
	int32_t							m_iNumItems;
	int32_t							m_iMaxItems;
	NiGeometry**					m_ppkItems;
	float*							m_pfDepths;
	int32_t							m_iCurrItem;

	NIRTTI_ADDRESS(0x11F6058);
};

ASSERT_SIZE(NiBackToFrontAccumulator, 0x30);