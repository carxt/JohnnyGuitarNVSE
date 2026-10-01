#pragma once

#include "TESBoundObject.hpp"

class TESBoundAnimObject : public TESBoundObject {
public:
	TESBoundAnimObject();
	~TESBoundAnimObject();
};

#ifdef GAME
ASSERT_SIZE(TESBoundAnimObject, 0x30);
#else
ASSERT_SIZE(TESBoundAnimObject, 0x54);
#endif