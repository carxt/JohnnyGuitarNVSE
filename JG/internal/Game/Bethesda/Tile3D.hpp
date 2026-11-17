#pragma once

#include "BSStringT.hpp"
#include "Tile.hpp"

class BSAnimGroupSequence;

class Tile3D : public Tile {
public:
	NiControllerManager*	pAnimManager;
	BSAnimGroupSequence*	pCurrentSequence;
	BSString				strAnimation;
	BSString				strFileName;

	bool IsPlaying() const;

	bool PlaySequence(const char* apSequenceName);

	bool UpdateSequence(float afValue, bool abIsPercentage);
};

ASSERT_SIZE(Tile3D, 0x50);