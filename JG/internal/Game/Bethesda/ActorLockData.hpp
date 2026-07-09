#pragma once

class TESActorBase;
class InventoryChanges;

class ActorLockData {
public:
	TESActorBase*		pActorBase;
	InventoryChanges*	pInventory;
	bool				bIsAlarmed;
};

ASSERT_SIZE(ActorLockData, 0xC);