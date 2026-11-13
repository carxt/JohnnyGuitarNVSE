#pragma once

#include "NiExtraData.hpp"
#include "NiTextKey.hpp"

class NiTextKeyExtraData : public NiExtraData {
public:
	uint32_t	m_uiNumKeys;
	NiTextKey*	m_pKeys;

	CREATE_OBJECT(NiTextKeyExtraData, 0xA46B70);
	NIRTTI_ADDRESS(0x11F3F28);
};

ASSERT_SIZE(NiTextKeyExtraData, 0x14);