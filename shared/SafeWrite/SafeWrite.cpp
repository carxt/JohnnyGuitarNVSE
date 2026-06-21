#include "SafeWrite.hpp"
#include <memoryapi.h>

STACK_FRAME_OPT_ENABLE

class MemoryUnlock {
public:
	MemoryUnlock(SIZE_T _addr, SIZE_T _size = sizeof(SIZE_T)) : addr(_addr), size(_size) {
		VirtualProtect((void*)addr, size, PAGE_EXECUTE_READWRITE, &oldProtect);
	}
	~MemoryUnlock() {
		VirtualProtect((void*)addr, size, oldProtect, &oldProtect);
	}

private:
	const SIZE_T addr;
	const SIZE_T size;
	SIZE_T oldProtect;
};

void __fastcall SafeWrite8(SIZE_T addr, SIZE_T data)
{
	MemoryUnlock unlock(addr);
	*((uint8_t*)addr) = data;
}

void __fastcall SafeWrite16(SIZE_T addr, SIZE_T data)
{
	MemoryUnlock unlock(addr);
	*((uint16_t*)addr) = data;
}

void __fastcall SafeWrite32(SIZE_T addr, SIZE_T data)
{
	MemoryUnlock unlock(addr);
	*((uint32_t*)addr) = data;
}

void __fastcall SafeWriteBuf(SIZE_T addr, const void *data, SIZE_T len)
{
	MemoryUnlock unlock(addr, len);
	memcpy((void *)addr, data, len);
}

void __fastcall WriteRelJump(SIZE_T jumpSrc, SIZE_T jumpTgt)
{
	MemoryUnlock unlock(jumpSrc, 5);
	*((uint8_t*)jumpSrc) = 0xE9;
	*((uint32_t*)(jumpSrc + 1)) = jumpTgt - jumpSrc - 1 - 4;
}

void __fastcall WriteRelCall(SIZE_T jumpSrc, SIZE_T jumpTgt)
{
	MemoryUnlock unlock(jumpSrc, 5);
	*((uint8_t*)jumpSrc) = 0xE8;
	*((uint32_t*)(jumpSrc + 1)) = jumpTgt - jumpSrc - 1 - 4;
}

void __fastcall ReplaceCall(SIZE_T jumpSrc, SIZE_T jumpTgt)
{
	SafeWrite32(jumpSrc + 1, jumpTgt - jumpSrc - 1 - 4);
}

void __fastcall ReplaceVirtualFunc(SIZE_T jumpSrc, void* jumpTgt) {
	SafeWrite32(jumpSrc, (SIZE_T)jumpTgt);
}

void __fastcall WriteRelJnz(SIZE_T jumpSrc, SIZE_T jumpTgt)
{
	// jnz rel32
	SafeWrite16(jumpSrc, 0x850F);
	SafeWrite32(jumpSrc + 2, jumpTgt - jumpSrc - 2 - 4);
}

void __fastcall WriteRelJle(SIZE_T jumpSrc, SIZE_T jumpTgt)
{
	// jle rel32
	SafeWrite16(jumpSrc, 0x8E0F);
	SafeWrite32(jumpSrc + 2, jumpTgt - jumpSrc - 2 - 4);
}

void __fastcall PatchMemoryNop(ULONG_PTR Address, SIZE_T Size)
{
	{
		MemoryUnlock unlock(Address, Size);
		for (SIZE_T i = 0; i < Size; i++)
			*(volatile BYTE*)(Address + i) = 0x90; //0x90 == opcode for NOP
	}
	FlushInstructionCache(GetCurrentProcess(), (LPVOID)Address, Size);
}

STACK_FRAME_OPT_RESET