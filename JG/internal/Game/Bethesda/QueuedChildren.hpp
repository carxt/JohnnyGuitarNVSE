#pragma once

#include "BSSimpleArray.hpp"
#include "Gamebryo/NiSmartPointer.hpp"

class QueuedFile;

class QueuedChildren : public BSSimpleArray<NiPointer<QueuedFile>> {
public:
	uint32_t	uiNumChildrenFinished;
};

ASSERT_SIZE(QueuedChildren, 0x14);