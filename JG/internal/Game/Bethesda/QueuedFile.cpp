#include "QueuedFile.hpp"

// GAME - 0xC3C590
// GECK - 0x9E6CE0
QueuedFile* QueuedFile::Create(IO_TASK_PRIORITY aePriority) {
#ifdef GAME
	return BSMemory::create<QueuedFile, 0xC3C590>(aePriority);
#else
	return BSMemory::create<QueuedFile, 0x9E6CE0>(aePriority);
#endif
}

// GAME - 0x443AA0
// GECK - 0x4BE100
void QueuedFile::SetParent(QueuedFile* apParent) {
#ifdef  GAME
	ThisCall(0x443AA0, this, apParent);
#else
	ThisCall(0x4BE100, this, apParent);
#endif
}

// GAME - 0x446990
uint32_t QueuedFile::GetChildCount() const {
#ifdef GAME
	return ThisCall<uint32_t>(0x446990, this);
#else
	return pChildren ? pChildren->GetSize() : 0;
#endif
}

// GAME - 0xC3C700
// GECK - 0x9E6E50
void QueuedFile::AddChild(QueuedFile* apChild) {
#ifdef  GAME
	ThisCall(0xC3C700, this, apChild);
#else
	ThisCall(0x9E6E50, this, apChild);
#endif
}

// GAME - 0xC3C7E0
// GECK - 0x9E6F30
void QueuedFile::AddAdditionalParent(QueuedFile* apParent) {
#ifdef  GAME
	ThisCall(0xC3C7E0, this, apParent);
#else
	ThisCall(0x9E6F30, this, apParent);
#endif
}
