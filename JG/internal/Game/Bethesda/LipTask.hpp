#pragma once

#include "QueuedFileEntry.hpp"

class Actor;
class LipSynchAnim;
class LipSyncBackgroundManager;

class ALIGN8 LipTask : public QueuedFileEntry {
public:
	Actor*						pActor;
	LipSynchAnim*				pLipSyncAnim;
	LipSyncBackgroundManager*	pOwner;
};

ASSERT_SIZE(LipTask, 0x40);