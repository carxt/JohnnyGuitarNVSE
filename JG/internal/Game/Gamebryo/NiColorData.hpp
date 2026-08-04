#pragma once

#include "NiObject.hpp"
#include "NiColorKey.hpp"

NiSmartPointer(NiColorData);

class NiColorData : public NiObject {
public:
	NiColorData();
	virtual ~NiColorData();

	uint32_t				m_uiNumKeys;
	NiColorKey*				m_pkKeys;
	NiColorKey::KeyType		m_eType;
	uint8_t					m_ucKeySize;

	NIRTTI_ADDRESS(0x11F3750);
};

ASSERT_SIZE(NiColorData, 0x18);