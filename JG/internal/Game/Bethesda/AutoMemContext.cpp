#include "AutoMemContext.hpp"

// GAME - 0x404EB0
AutoMemContext::AutoMemContext(MEM_CONTEXT aeMemContext, bool abOverridable, const char* apFile, uint32_t auiLine) {
	Enter(aeMemContext, abOverridable, apFile, auiLine);
}

// GAME - 0x404EE0
AutoMemContext::~AutoMemContext() {
	Leave();
}

// GAME - 0x404F00
void AutoMemContext::Enter(MEM_CONTEXT aeMemContext, bool abOverridable, const char* apFile, uint32_t auiLine) {
	ThisCall(0x404F00, this, aeMemContext, abOverridable, apFile, auiLine);
}

// GAME - 0x404F70
void AutoMemContext::Leave() const {
	ThisCall(0x404F70, this);
}
