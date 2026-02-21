#pragma once

#include "TESBoundObject.hpp"

class TESBoundAnimObject : public TESBoundObject {
public:
	TESBoundAnimObject();
	~TESBoundAnimObject();
};

ASSERT_SIZE(TESBoundAnimObject, 0x30);