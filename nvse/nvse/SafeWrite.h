#pragma once

DECLSPEC_NOINLINE void __fastcall SafeWrite8(SIZE_T addr, SIZE_T data);
DECLSPEC_NOINLINE void __fastcall SafeWrite16(SIZE_T addr, SIZE_T data);
DECLSPEC_NOINLINE void __fastcall SafeWrite32(SIZE_T addr, SIZE_T data);
DECLSPEC_NOINLINE void __fastcall SafeWriteBuf(SIZE_T addr, const void* data, SIZE_T len);

// 5 bytes
DECLSPEC_NOINLINE void __fastcall WriteRelJump(SIZE_T jumpSrc, SIZE_T jumpTgt);
DECLSPEC_NOINLINE void __fastcall WriteRelCall(SIZE_T jumpSrc, SIZE_T jumpTgt);


// 6 bytes
DECLSPEC_NOINLINE void __fastcall WriteRelJnz(SIZE_T jumpSrc, SIZE_T jumpTgt);
DECLSPEC_NOINLINE void __fastcall WriteRelJle(SIZE_T jumpSrc, SIZE_T jumpTgt);

DECLSPEC_NOINLINE void __fastcall PatchMemoryNop(ULONG_PTR Address, SIZE_T Size);
void __fastcall PatchMemoryNopRange(ULONG_PTR StartAddress, ULONG_PTR EndAddress);

template <typename T>
void __fastcall WriteRelCall(SIZE_T jumpSrc, T jumpTgt) {
	WriteRelCall(jumpSrc, (SIZE_T)jumpTgt);
}

template <typename T>
void __fastcall WriteRelJump(SIZE_T jumpSrc, T jumpTgt) {
	WriteRelJump(jumpSrc, (SIZE_T)jumpTgt);
}

DECLSPEC_NOINLINE void __fastcall ReplaceCall(SIZE_T jumpSrc, SIZE_T jumpTgt);

template <typename T>
void __fastcall ReplaceCall(SIZE_T jumpSrc, T jumpTgt) {
	ReplaceCall(jumpSrc, (SIZE_T)jumpTgt);
}

void __fastcall ReplaceVirtualFunc(SIZE_T jumpSrc, void* jumpTgt);

// Stores the function-to-call before overwriting it, to allow calling the overwritten function after our hook is over.
// Thanks Demorome and lStewieAl

// Taken from lStewieAl.
// Returns the address of the jump/called function, assuming there is one.
static inline SIZE_T GetRelJumpAddr(SIZE_T jumpSrc) {
	return *(SIZE_T*)(jumpSrc + 1) + jumpSrc + 5;
}

static inline SIZE_T GetWriteAddr(SIZE_T writeAddr) {
	return *(SIZE_T*)(writeAddr);
}

// Specialization for member function pointers
template <typename C, typename Ret, typename... Args>
void __fastcall WriteRelJumpEx(SIZE_T source, Ret(C::* const target)(Args...) const) {
	union
	{
		Ret(C::* tgt)(Args...) const;
		SIZE_T funcPtr;
	} conversion;
	conversion.tgt = target;

	WriteRelJump(source, conversion.funcPtr);
}

template <typename C, typename Ret, typename... Args>
void __fastcall WriteRelJumpEx(SIZE_T source, Ret(C::* const target)(Args...)) {
	union
	{
		Ret(C::* tgt)(Args...);
		SIZE_T funcPtr;
	} conversion;
	conversion.tgt = target;

	WriteRelJump(source, conversion.funcPtr);
}

template <typename C, typename Ret, typename... Args>
void __fastcall WriteRelCallEx(SIZE_T source, Ret(C::* const target)(Args...) const) {
	union
	{
		Ret(C::* tgt)(Args...) const;
		SIZE_T funcPtr;
	} conversion;
	conversion.tgt = target;

	WriteRelCall(source, conversion.funcPtr);
}

template <typename C, typename Ret, typename... Args>
void __fastcall WriteRelCallEx(SIZE_T source, Ret(C::* const target)(Args...)) {
	union
	{
		Ret(C::* tgt)(Args...);
		SIZE_T funcPtr;
	} conversion;
	conversion.tgt = target;

	WriteRelCall(source, conversion.funcPtr);
}

template <typename C, typename Ret, typename... Args>
void __fastcall ReplaceCallEx(SIZE_T source, Ret(C::* const target)(Args...) const) {
	union
	{
		Ret(C::* tgt)(Args...) const;
		SIZE_T funcPtr;
	} conversion;
	conversion.tgt = target;

	ReplaceCall(source, conversion.funcPtr);
}

template <typename C, typename Ret, typename... Args>
void __fastcall ReplaceCallEx(SIZE_T source, Ret(C::* const target)(Args...)) {
	union
	{
		Ret(C::* tgt)(Args...);
		SIZE_T funcPtr;
	} conversion;
	conversion.tgt = target;

	ReplaceCall(source, conversion.funcPtr);
}

template <typename C, typename Ret, typename... Args>
void __fastcall ReplaceVirtualFuncEx(SIZE_T source, Ret(C::* const target)(Args...) const) {
	union
	{
		Ret(C::* tgt)(Args...) const;
		SIZE_T funcPtr;
	} conversion;
	conversion.tgt = target;

	SafeWrite32(source, conversion.funcPtr);
}

template <typename C, typename Ret, typename... Args>
void __fastcall ReplaceVirtualFuncEx(SIZE_T source, Ret(C::* const target)(Args...)) {
	union
	{
		Ret(C::* tgt)(Args...);
		SIZE_T funcPtr;
	} conversion;
	conversion.tgt = target;

	SafeWrite32(source, conversion.funcPtr);
}

template <typename C, typename Ret, typename... Args>
void __fastcall ReplaceVTableEntry(void** apVTable, uint32_t auiPosition, Ret(C::* const target)(Args...) const) {
	union {
		Ret(C::* tgt)(Args...) const;
		SIZE_T funcPtr;
	} conversion;
	conversion.tgt = target;

	apVTable[auiPosition] = (void*)conversion.funcPtr;
}

template <typename C, typename Ret, typename... Args>
void __fastcall ReplaceVTableEntry(void** apVTable, uint32_t auiPosition, Ret(C::* const target)(Args...)) {
	union {
		Ret(C::* tgt)(Args...);
		SIZE_T funcPtr;
	} conversion;
	conversion.tgt = target;

	apVTable[auiPosition] = (void*)conversion.funcPtr;
}

class CallDetour {
	SIZE_T overwritten_addr = 0;
public:
	DECLSPEC_NOINLINE void __fastcall WriteRelCall(SIZE_T jumpSrc, void* jumpTgt)
	{
		__assume(jumpSrc != 0);
		__assume(jumpTgt != nullptr);
		if (*reinterpret_cast<uint8_t*>(jumpSrc) != 0xE8) {
			char cTextBuffer[72];
			sprintf_s(cTextBuffer, "Cannot write detour; jumpSrc is not a function call. (0x%08X)", jumpSrc);
			MessageBoxA(nullptr, cTextBuffer, "WriteRelCall", MB_OK | MB_ICONERROR);
			return;
		}
		overwritten_addr = GetRelJumpAddr(jumpSrc);
		::WriteRelCall(jumpSrc, jumpTgt);
	}

	template <typename T>
	DECLSPEC_NOINLINE void __fastcall ReplaceCall(SIZE_T jumpSrc, T jumpTgt) {
		__assume(jumpSrc != 0);
		if (*reinterpret_cast<uint8_t*>(jumpSrc) != 0xE8) {
			char cTextBuffer[72];
			sprintf_s(cTextBuffer, "Cannot write detour; jumpSrc is not a function call. (0x%08X)", jumpSrc);
			MessageBoxA(nullptr, cTextBuffer, "WriteRelCall", MB_OK | MB_ICONERROR);
			return;
		}
		overwritten_addr = GetRelJumpAddr(jumpSrc);
		::ReplaceCall(jumpSrc, (SIZE_T)jumpTgt);
	}

	template <typename C, typename Ret, typename... Args>
	void __fastcall ReplaceCallEx(SIZE_T source, Ret(C::* const target)(Args...) const) {
		union
		{
			Ret(C::* tgt)(Args...) const;
			SIZE_T funcPtr;
		} conversion;
		conversion.tgt = target;

		ReplaceCall(source, conversion.funcPtr);
	}

	template <typename C, typename Ret, typename... Args>
	void __fastcall ReplaceCallEx(SIZE_T source, Ret(C::* const target)(Args...)) {
		union
		{
			Ret(C::* tgt)(Args...);
			SIZE_T funcPtr;
		} conversion;
		conversion.tgt = target;

		ReplaceCall(source, conversion.funcPtr);
	}

	template <typename T>
	void SafeWrite32(SIZE_T jumpSrc, T jumpTgt) {
		__assume(jumpSrc != 0);
		overwritten_addr = GetWriteAddr(jumpSrc);
		::SafeWrite32(jumpSrc, (SIZE_T)jumpTgt);
	}

	[[nodiscard]] SIZE_T GetOverwrittenAddr() const { return overwritten_addr; }
};

class VirtFuncDetour {
protected:
	SIZE_T overwritten_addr = 0;

public:
	template <typename C, typename Ret, typename... Args>
	void __fastcall ReplaceVirtualFuncEx(SIZE_T source, Ret(C::* const target)(Args...)) {
		union
		{
			Ret(C::* tgt)(Args...);
			SIZE_T funcPtr;
		} conversion;
		conversion.tgt = target;

		overwritten_addr = *(uint32_t*)source;

		SafeWrite32(source, conversion.funcPtr);
	}

	[[nodiscard]] SIZE_T GetOverwrittenAddr() const { return overwritten_addr; }
};