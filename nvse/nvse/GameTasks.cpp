#include "GameTasks.h"
#include "GameAPI.h"
#include "GameForms.h"
#include "GameObjects.h"

#if 1
// IOManager** g_ioManager = (IOManager**)0x00B33A10;
uint32_t kModelLoader_QueueReference = 0x00444850;
uint32_t* kBSTaskCounter = (uint32_t*)0x0011C3B38;
#else
#error unsupported Oblivion version
#endif

#if 0
bool IOManager::IsInQueue(TESObjectREFR* refr) {
	for (LockFreeQueue< NiPointer<IOTask> >::Node* node = taskQueue->head->next; node; node = node->next) {
		QueuedReference* qr = OBLIVION_CAST(node->data, IOTask, QueuedReference);
		if (!qr)
			continue;

		if (qr->refr == refr)
			return true;
	}

	return false;
}

void IOManager::DumpQueuedTasks() {
#if 0
	_MESSAGE("Dumping queued tasks:");
	for (LockFreeQueue< NiPointer<IOTask> >::Node* node = taskQueue->head->next; node; node = node->next) {
		QueuedReference* qr = OBLIVION_CAST(node->data, IOTask, QueuedReference);
		if (!qr)
			continue;
		else if (qr->refr) {
			Console_Print("\t%s (%08x)", GetFullName(qr->refr), qr->refr->GetFormID());
			_MESSAGE("\t%s (%08x)", GetFullName(qr->refr), qr->refr->GetFormID());
		}
		else
			_MESSAGE("NULL reference");
	}
#endif
}

IOManager* IOManager::GetSingleton() {
	return *g_ioManager;
}
#endif

ModelLoader* ModelLoader::GetSingleton() {
	return *(ModelLoader**)0x011C3B3C;
}

void ModelLoader::QueueReference(TESObjectREFR* apRef, IO_TASK_PRIORITY aePriority, bool abAllowQueueReferenceQueuing) {
	ThisCall(0x444850, this, apRef, aePriority, abAllowQueueReferenceQueuing);
}