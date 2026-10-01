#pragma once

class TESObjectREFR;

class NavMeshTriangleDoorPortal {
public:
	TESObjectREFR*	pDoor			= nullptr;
	uint16_t		usTriangleIndex = UINT16_MAX;
};

ASSERT_SIZE(NavMeshTriangleDoorPortal, 0x8);