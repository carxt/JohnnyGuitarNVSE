#include "XMLBufferFix.hpp"

#include "Shared/SafeWrite/SafeWrite.hpp"

namespace XMLBufferFix {

	// Beth allocates a string buffer without adding space for a null terminator
	// Chaos ensues, 7 hours wasted debugging UIO and JIP

	SPEC_NAKED void BufferSizeFix() {
		static constexpr uint32_t uiReturnAddr = 0xA1CFB6;
		__asm {
			mov     eax, [ebp - 4]
			inc		eax
			push	eax
			mov     ecx, 0x11F6238 // MemoryManager singleton
			mov		eax, 0xAA3E40  // MemoryManager::Allocate
			call    eax
			jmp		uiReturnAddr
		}
	}

	void Install() {
		HookUtils::WriteRelJump(0xA1CFA8, BufferSizeFix);
	}

}