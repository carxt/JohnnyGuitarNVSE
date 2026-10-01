#pragma once

#include "BGSDestructibleObjectForm.hpp"
#include "TESFullName.hpp"
#include "TESObjectSTAT.hpp"

class BGSMovableStatic : public TESFullName, public BGSDestructibleObjectForm, public TESObjectSTAT {
public:
	struct Data {
		Bitfield8 ucFlags;
	};

	TESSound*	pLoopSound;
	Data		kData;

	TESSound* GetLoopingSound() const;
	void SetLoopingSound(TESSound* apSound);
};

#ifdef GAME
ASSERT_SIZE(BGSMovableStatic, 0x74);
#else
ASSERT_SIZE(BGSMovableStatic, 0xA8);
#endif