#include "SafeWrite.h"

void __stdcall SafeWrite8(UInt32 addr, UInt32 data)
{
	UInt32 oldProtect;
	VirtualProtect((void*)addr, 4, PAGE_EXECUTE_READWRITE, &oldProtect);
	*(UInt8*)addr = data;
	VirtualProtect((void*)addr, 4, oldProtect, &oldProtect);
}

void __stdcall SafeWrite16(UInt32 addr, UInt32 data)
{
	UInt32 oldProtect;
	VirtualProtect((void*)addr, 4, PAGE_EXECUTE_READWRITE, &oldProtect);
	*(UInt16*)addr = data;
	VirtualProtect((void*)addr, 4, oldProtect, &oldProtect);
}

void __stdcall SafeWrite32(UInt32 addr, UInt32 data)
{
	UInt32 oldProtect;
	VirtualProtect((void*)addr, 4, PAGE_EXECUTE_READWRITE, &oldProtect);
	*(UInt32*)addr = data;
	VirtualProtect((void*)addr, 4, oldProtect, &oldProtect);
}

void __stdcall SafeWriteBuf(UInt32 addr, void * data, UInt32 len)
{
	UInt32 oldProtect;
	VirtualProtect((void*)addr, len, PAGE_EXECUTE_READWRITE, &oldProtect);
	memcpy((void*)addr, data, len);
	VirtualProtect((void*)addr, len, oldProtect, &oldProtect);
}

void __stdcall WriteRelJump(UInt32 jumpSrc, UInt32 jumpTgt)
{
	UInt32 oldProtect;
	VirtualProtect((void*)jumpSrc, 5, PAGE_EXECUTE_READWRITE, &oldProtect);
	*(UInt8*)jumpSrc = 0xE9;
	*(UInt32*)(jumpSrc + 1) = jumpTgt - jumpSrc - 5;
	VirtualProtect((void*)jumpSrc, 5, oldProtect, &oldProtect);
}

void __stdcall WriteRelCall(UInt32 jumpSrc, UInt32 jumpTgt)
{
	UInt32 oldProtect;
	VirtualProtect((void*)jumpSrc, 5, PAGE_EXECUTE_READWRITE, &oldProtect);
	*(UInt8*)jumpSrc = 0xE8;
	*(UInt32*)(jumpSrc + 1) = jumpTgt - jumpSrc - 5;
	VirtualProtect((void*)jumpSrc, 5, oldProtect, &oldProtect);
}

void WriteRelJnz(UInt32 jumpSrc, UInt32 jumpTgt)
{
	// jnz rel32
	SafeWrite16(jumpSrc, 0x850F);
	SafeWrite32(jumpSrc + 2, jumpTgt - jumpSrc - 2 - 4);
}

void WriteRelJle(UInt32 jumpSrc, UInt32 jumpTgt)
{
	// jle rel32
	SafeWrite16(jumpSrc, 0x8E0F);
	SafeWrite32(jumpSrc + 2, jumpTgt - jumpSrc - 2 - 4);
}
