#include "GameTasks.h"
#include "GameAPI.h"
#include "GameForms.h"
#include "GameObjects.h"
#include "Hooks_Gameplay.h"

#if RUNTIME_VERSION == RUNTIME_VERSION_1_4_0_525
	// IOManager** g_ioManager = (IOManager**)0x00B33A10;
	UInt32 kModelLoader_QueueReference = 0x00444850;
	UInt32 * kBSTaskCounter = (UInt32*) 0x0011C3B38;
#elif RUNTIME_VERSION == RUNTIME_VERSION_1_4_0_525ng
	// IOManager** g_ioManager = (IOManager**)0x00B33A10;
	UInt32 kModelLoader_QueueReference = 0x004446D0;
	UInt32 * kBSTaskCounter = (UInt32*)0x0011C3B38;
#else
#error unsupported Oblivion version
#endif

#if 0
bool IOManager::IsInQueue(TESObjectREFR *refr) 
{
	for (LockFreeQueue< NiPointer<IOTask> >::Node *node = taskQueue->head->next; node; node = node->next) 
	{
		QueuedReference *qr = OBLIVION_CAST(node->data, IOTask, QueuedReference);
		if (!qr)
			continue;

		if (qr->refr == refr)
			return true;
	}

	return false;
}

void IOManager::DumpQueuedTasks()
{
#if 0
	_MESSAGE("Dumping queued tasks:");
	for (LockFreeQueue< NiPointer<IOTask> >::Node *node = taskQueue->head->next; node; node = node->next)
	{
		QueuedReference* qr = OBLIVION_CAST(node->data, IOTask, QueuedReference);
		if (!qr)
			continue;
		else if (qr->refr)
		{
			Console_Print("\t%s (%08x)", GetFullName(qr->refr), qr->refr->refID);
			_MESSAGE("\t%s (%08x)", GetFullName(qr->refr), qr->refr->refID);
		}
		else
			_MESSAGE("NULL reference");
	}
#endif

}

IOManager* IOManager::GetSingleton()
{
	return *g_ioManager;
}
#endif

ModelLoader *ModelLoader::GetSingleton()
{
	return *(ModelLoader**)0x011C3B3C;
}

__declspec(naked) void ModelLoader::QueueReference(TESObjectREFR *refr, UInt32 arg2, UInt32 arg3)
// arg2 is encoded based on the parent cell and arg3 is most likely a boolean
{
	__asm	jmp		kModelLoader_QueueReference
}

UInt32 *BSTask::GetCounterSingleton()
{
	return kBSTaskCounter;
}

