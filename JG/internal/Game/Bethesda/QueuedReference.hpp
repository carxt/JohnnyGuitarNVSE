#pragma once

#include "QueuedFile.hpp"
#include "Model.hpp"
#include "Gamebryo/NiRefObject.hpp"

class TESObjectREFR;
class NiRefObject;
class NiNode;
class AttachDistant3DTask;

NiSmartPointer(QueuedReference);

class QueuedReference : public QueuedFile {
public:
	QueuedReference();
	~QueuedReference();

	virtual void QueueModels();
	virtual void UseDistant3D();
	virtual void AttachDistant3D(NiNode* apNode);
	virtual bool BackgroundClone();
	virtual void Attach();
	virtual void FinishAttach();

	TESObjectREFR*					pRef;
	NiPointer<IOTask>				spQueuedModel;
	NiPointer<Model>				spModel;
	NiRefObjectPtr					spCloned3D;
	NiPointer<AttachDistant3DTask>	spAttachDistant3DTask;
	uint32_t						uiWaitCount;
};

ASSERT_SIZE(QueuedReference, 0x40)