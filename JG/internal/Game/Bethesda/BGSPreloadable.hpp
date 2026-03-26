#pragma once

#include "BaseFormComponent.hpp"
#include "IOTask.hpp"

class QueuedFile;

class BGSPreloadable : public BaseFormComponent {
public:
	BGSPreloadable();
	virtual ~BGSPreloadable();

	virtual void	Preload(IO_TASK_PRIORITY aePriority, QueuedFile* apFile);
};

ASSERT_SIZE(BGSPreloadable, 0x4);