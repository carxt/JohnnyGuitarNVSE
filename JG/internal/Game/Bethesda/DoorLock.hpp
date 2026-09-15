#pragma once

class TESObjectCELL;
class LockData;
class TESForm;
class TESGlobal;

class DoorLock {
public:
	TESObjectCELL*	pDoorCell;
	TESObjectCELL*	pTeleportDoorCell;
	LockData*		pLock;
	TESForm*		pOwnershipForm;
	int32_t			iOwnershipRank;
	TESGlobal*		pOwnershipGlobal;
};

ASSERT_SIZE(DoorLock, 0x18);