#include "AddItemMessages.hpp"

namespace AddItemMessages {

	// When adding item lists, allow per-item "Item Added" messages instead of issuing one message for the last item added

	SPEC_NAKED void MessageLoop_Asm() {
		static constexpr uint32_t uiReturnAddr		= 0x482201;
		static constexpr uint32_t uiDestructorAddr	= 0x4037D0;
		__asm {
			call	uiDestructorAddr
			jmp     uiReturnAddr
		}
	}

	void Install() {
		HookUtils::SafeWriteBuf(0x482205, "\x0F\x84\x42\x04");
		HookUtils::PatchMemoryNop(0x4824BA, 5);
		HookUtils::SafeWriteBuf(0x4824C8, "\x0F\x85\x33\xFD\xFF\xFF");
		HookUtils::SafeWriteBuf(0x4824D2, "\x0F\x84\x29\xFD\xFF\xFF");
		HookUtils::SafeWriteBuf(0x4824DE, "\x0F\x85\x1D\xFD\xFF\xFF");
		HookUtils::WriteRelJump(0x482648, MessageLoop_Asm);
	}

}
