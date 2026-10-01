#pragma once

#include "NiObject.hpp"
#include "NiFloatKey.hpp"

NiSmartPointer(NiFloatData);

class NiFloatData : public NiObject {
public:
	NiFloatData();
	virtual ~NiFloatData();

	uint32_t			m_uiNumKeys;
	NiFloatKey*			m_pkKeys;
	NiFloatKey::KeyType m_eType;
	uint8_t				m_ucKeySize;

	NIRTTI_ADDRESS(0x11F3748);
};

ASSERT_SIZE(NiFloatData, 0x18);