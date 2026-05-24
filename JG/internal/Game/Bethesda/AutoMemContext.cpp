#include "AutoMemContext.hpp"
#include "TLSData.hpp"

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
	eOldMemContext = GetMemContext();
	SetMemContext(aeMemContext);
}

// GAME - 0x404F70
void AutoMemContext::Leave() const {
	SetMemContext(eOldMemContext);
}

// GAME - 0x404F50
MEM_CONTEXT GetMemContext() {
	return static_cast<MEM_CONTEXT>(TLSData::GetMemContext());
}

// GAME - 0x404F30
void SetMemContext(MEM_CONTEXT aeMemContext) {
	TLSData::SetMemContext(aeMemContext);
}
