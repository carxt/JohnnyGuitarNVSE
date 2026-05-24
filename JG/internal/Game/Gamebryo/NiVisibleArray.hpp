#pragma once

#include "NiMemObject.hpp"

class NiGeometry;

class SPEC_EMPTY_BASES NiVisibleArray : public NiMemObject {
public:
	NiGeometry**	m_ppkArray;
	uint32_t		m_uiCurrentSize;
	uint32_t		m_uiAllocatedSize;
	uint32_t		m_uiGrowBy;
};

ASSERT_SIZE(NiVisibleArray, 0x10);