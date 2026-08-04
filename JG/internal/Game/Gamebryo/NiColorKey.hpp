#pragma once

#include "NiAnimationKey.hpp"
#include "NiColorA.hpp"

class NiColorKey : public NiAnimationKey {
public:
	NiColorKey() = default;
	~NiColorKey() = default;

	NiColorA m_Color;
};

ASSERT_SIZE(NiColorKey, 0x14)