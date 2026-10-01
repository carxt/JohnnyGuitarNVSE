#pragma once

#include "NiExtraData.hpp"

NiSmartPointer(NiStringExtraData);

class NiStringExtraData : public NiExtraData {
public:
	NiStringExtraData();
	virtual ~NiStringExtraData();

	NiFixedString m_kString;

	CREATE_OBJECT(NiStringExtraData, 0xA74230);
	NIRTTI_ADDRESS(0x11F4A38);
};

ASSERT_SIZE(NiStringExtraData, 0x10);