#pragma once

#include "NiAnimationKey.hpp"

class NiFloatKey : public NiAnimationKey {
public:
	float m_fValue;
};

ASSERT_SIZE(NiFloatKey, 0x8);