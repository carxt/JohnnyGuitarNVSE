#include "TaskQueue.hpp"
#include "Bethesda/AutoMemContext.hpp"
#include <Utilities.h>

TaskQueue TaskQueue::kSingleton;

void __fastcall TaskQueue::QueueTask(const QueuedTask& arTask) noexcept {
	SRWUniqueLock kLock(kSingleton.kQueueLock);
	MEMORY_CONTEXT(MEM_CONTEXT::MC_DEFAULT);
	kSingleton.kTaskQueue.push(arTask);
}

void __fastcall TaskQueue::ExecuteTasks() noexcept {
	SRWUniqueLock kLock(kSingleton.kQueueLock);
	for (; !kSingleton.kTaskQueue.empty(); kSingleton.kTaskQueue.pop()) {
		const QueuedTask& kTask = kSingleton.kTaskQueue.front();
		kTask.pFunction(kTask);
	}
}

QueuedTask::QueuedTask() noexcept {
	__m128i* pThis = reinterpret_cast<__m128i*>(this);
	pThis[0] = _mm_setzero_si128();
	pThis[1] = _mm_setzero_si128();
}

QueuedTask::QueuedTask(const QueuedTask& arOther) noexcept {
	__m128i* pThis = reinterpret_cast<__m128i*>(this);
	const __m128i* pOther = reinterpret_cast<const __m128i*>(&arOther);
	pThis[0] = pOther[0];
	pThis[1] = pOther[1];
}

QueuedTask::QueuedTask(QueuedTask&& arOther) noexcept {
	__m128i* pThis = reinterpret_cast<__m128i*>(this);
	__m128i* pOther = reinterpret_cast<__m128i*>(&arOther);
	pThis[0] = pOther[0];
	pThis[1] = pOther[1];
	pOther[0] = _mm_setzero_si128();
	pOther[1] = _mm_setzero_si128();
}
