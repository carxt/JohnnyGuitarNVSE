#pragma once

#include "IOTask.hpp"
#include "QueuedChildren.hpp"

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

	MEM_CONTEXT				eContext;
	NiPointer<QueuedFile>	spParent;
	QueuedChildren*			pChildren;
	QueuedParents*			pAdditionalParents;

	static QueuedFile* Create(IO_TASK_PRIORITY aePriority);

	void SetParent(QueuedFile* apParent);

	uint32_t GetChildCount() const;
	void AddChild(QueuedFile* apChild);

	void AddAdditionalParent(QueuedFile* apParent);
};

ASSERT_SIZE(QueuedFile, 0x28);