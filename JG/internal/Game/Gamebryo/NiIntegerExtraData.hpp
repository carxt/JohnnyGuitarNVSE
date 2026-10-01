#pragma once

#include "NiExtraData.hpp"

NiSmartPointer(NiIntegerExtraData);

class NiIntegerExtraData : public NiExtraData {
public:
	NiIntegerExtraData();
	virtual ~NiIntegerExtraData();

	int32_t m_iValue;

	CREATE_OBJECT(NiIntegerExtraData, 0xA99CD0);
	NIRTTI_ADDRESS(0x11F5F2C);
};

ASSERT_SIZE(NiIntegerExtraData, 0x10)