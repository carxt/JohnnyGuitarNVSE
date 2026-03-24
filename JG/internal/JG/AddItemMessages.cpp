#include "AddItemMessages.hpp"

namespace AddItemMessages {

	// When adding item lists, allows per-item "Item Added" messages insated of issuing one message for the last item added

	void __declspec(naked) MessageLoop_Asm() {
		static constexpr uint32_t uiRet = 0x482201;
		static constexpr uint32_t uiDestructor = 0x4037D0;
		__asm {
			call	uiDestructor
			jmp     uiRet
		}
	}

	void Install() {
		SafeWriteBuf(0x482205, "\x0F\x84\x42\x04");
		PatchMemoryNop(0x4824BA, 5);
		SafeWriteBuf(0x4824C8, "\x0F\x85\x33\xFD\xFF\xFF");
		SafeWriteBuf(0x4824D2, "\x0F\x84\x29\xFD\xFF\xFF");
		SafeWriteBuf(0x4824DE, "\x0F\x84\x1D\xFD\xFF\xFF");
		WriteRelJump(0x482648, (uintptr_t)MessageLoop_Asm);
	}

}
