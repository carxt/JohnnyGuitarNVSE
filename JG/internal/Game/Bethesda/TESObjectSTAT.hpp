#pragma once

#include "TESBoundObject.hpp"
#include "TESModelTextureSwap.hpp"

class TESSound;

class TESObjectSTAT : public TESBoundObject, public TESModelTextureSwap {
public:
	TESObjectSTAT();
	~TESObjectSTAT();

	uint8_t	  ucPassThroughSoundType;
	TESSound* pSound;

	TESFORM_TYPE(TESObjectSTAT);

	uint8_t GetPassThroughSoundType() const;
	void SetPassThroughSoundType(uint8_t aucType);

	TESSound* GetSound() const;
	void SetSound(TESSound* apSound);
};

#ifdef GAME
ASSERT_SIZE(TESObjectSTAT, 0x58);
#else
ASSERT_SIZE(TESObjectSTAT, 0x8C);
#endif