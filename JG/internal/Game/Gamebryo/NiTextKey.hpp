#pragma once

#include "NiFixedString.hpp"

class SPEC_EMPTY_BASES NiTextKey : public NiMemObject {
public:
	float			m_fTime;
	NiFixedString	m_kText;
};

ASSERT_SIZE(NiTextKey, 0x8);