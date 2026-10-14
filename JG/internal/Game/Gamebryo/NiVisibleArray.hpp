#pragma once

#include "Bethesda/BSMemObject.hpp"

class NiGeometry;

class SPEC_EMPTY_BASES NiVisibleArray : public BSMemObject {
public:
	NiGeometry**	m_ppkArray;
	uint32_t		m_uiCurrentSize;
	uint32_t		m_uiAllocatedSize;
	uint32_t		m_uiGrowBy;
};

ASSERT_SIZE(NiVisibleArray, 0x10);