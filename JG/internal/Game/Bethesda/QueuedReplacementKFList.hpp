#pragma once

#include "QueuedFile.hpp"

class Animation;

class QueuedReplacementKFList : public QueuedFile {
public:
	Animation*	pAnim;
	uint32_t	uiPostProcessingChildCount;
	uint32_t	uiPostProcessedChildCount;
};

ASSERT_SIZE(QueuedReplacementKFList, 0x38)