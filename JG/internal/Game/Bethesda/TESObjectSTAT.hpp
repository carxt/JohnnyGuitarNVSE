#pragma once

#include "TESBoundObject.hpp"
#include "TESModelTextureSwap.hpp"

class TESSound;

class TESObjectSTAT : public TESBoundObject, public TESModelTextureSwap {
public:
	TESObjectSTAT();
	~TESObjectSTAT();

	uint8_t	  ucBrushSoundType;
	TESSound* pSound;

	TESFORM_TYPE(TESObjectSTAT);
};

ASSERT_SIZE(TESObjectSTAT, 0x58);