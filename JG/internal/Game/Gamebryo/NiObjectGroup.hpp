#pragma once

#include "NiSmartPointer.hpp"

NiSmartPointer(NiObjectGroup);

class NiObjectGroup {
public:
	uint32_t	m_uiSize;
	void*		m_pvBuffer;
	void*		m_pvFree;
	uint32_t	m_uiRefCount;
};

ASSERT_SIZE(NiObjectGroup, 0x10);