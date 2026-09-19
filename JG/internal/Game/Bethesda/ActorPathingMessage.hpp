#pragma once

#include "Gamebryo/NiSmartPointer.hpp"

class PathingSolution;

class ActorPathingMessage {
public:
	uint32_t					eType;
	NiPointer<PathingSolution>	spPathingSolution;
	ActorPathingMessage*		pNext;
};

ASSERT_SIZE(ActorPathingMessage, 0xC);