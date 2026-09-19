#pragma once

#include "ActorMover.hpp"

class PlayerMover : public ActorMover {
public:
	NiPoint3					kSideVector;
	Bitfield<_MovementFlags>	uiMoveMode;
	Bitfield32					uiLastTurnDir;
	float						fMinTurnTime;
};

ASSERT_SIZE(PlayerMover, 0xA0);