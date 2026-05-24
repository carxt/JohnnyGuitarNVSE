#pragma once

#include "IOTask.hpp"
#include "QueuedChildren.hpp"

class QueuedReference;
class QueuedChildren;
class QueuedParents;
class NiObject;

NiSmartPointer(QueuedFile);

class ALIGN8 QueuedFile : public IOTask {
public:
	QueuedFile();
	virtual ~QueuedFile();

	virtual void QueueMe();
	virtual void NotifyChildFinished(QueuedFile* apParent);
	virtual void CheckFinished();

	uint32_t					eContext;
	NiPointer<QueuedReference>	spParent;
	QueuedChildren*				pChildren;
	QueuedParents*				pParents;
};

ASSERT_SIZE(QueuedFile, 0x28);