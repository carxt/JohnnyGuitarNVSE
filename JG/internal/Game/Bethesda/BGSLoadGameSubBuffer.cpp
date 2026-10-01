#include "BGSLoadGameSubBuffer.hpp"

// GAME - 0x864E20
BGSLoadFormBuffer* BGSLoadGameSubBuffer::CreateLoadFormBuffer(TESForm* apForm) {
	return ThisCall<BGSLoadFormBuffer*>(0x864E20, this, apForm);
}

// GAME - 0x865120
void BGSLoadGameSubBuffer::CopyBuffer(BGSSaveFormBuffer* apBuffer) {
	ThisCall(0x865120, this, apBuffer);
}
