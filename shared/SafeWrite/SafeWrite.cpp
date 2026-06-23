#include "SafeWrite.hpp"
#include <memoryapi.h>

STACK_FRAME_OPT_ENABLE

namespace HookUtils {

	MemoryUnlock::MemoryUnlock(uintptr_t addr, uintptr_t size, uint32_t flags) noexcept : _addr(addr), _size(size) {
		VirtualProtect(reinterpret_cast<void*>(_addr), _size, flags, &_oldProtect);
	}

	MemoryUnlock::~MemoryUnlock() noexcept {
		VirtualProtect(reinterpret_cast<void*>(_addr), _size, _oldProtect, &_oldProtect);
	}

	template<typename TYPE>
	inline void __fastcall RawWrite(uintptr_t address, TYPE data) noexcept {
		*reinterpret_cast<TYPE*>(address) = data;
	}

	template<uint32_t offset>
	inline void __fastcall RawWriteRel(uintptr_t address, uintptr_t target) noexcept {
		*reinterpret_cast<uintptr_t*>(address + offset) = GetRelAddr(address, target, offset);
	}

	template<typename TYPE>
	DECLSPEC_NOINLINE void __fastcall SafeWrite(uintptr_t address, TYPE data) noexcept {
		MemoryUnlock unlock(address, sizeof(TYPE));
		RawWrite(address, data);
	}

	template <typename T>
	DECLSPEC_NOINLINE void __fastcall SafeWriteRel(uintptr_t address, uintptr_t target) noexcept {
		constexpr uint32_t offset = sizeof(T);
		MemoryUnlock unlock(address, sizeof(uintptr_t) + offset);
		RawWriteRel<offset>(address, target);
	}

	template <typename T>
	DECLSPEC_NOINLINE void __fastcall SafeWriteRel(uintptr_t address, uintptr_t target, T opcode) noexcept {
		constexpr uint32_t offset = sizeof(T);
		MemoryUnlock unlock(address, sizeof(uintptr_t) + offset);
		RawWrite<T>(address, opcode);
		RawWriteRel<offset>(address, target);
	}

	void __fastcall SafeWrite8(uintptr_t address, uint8_t data) noexcept {
		SafeWrite<uint8_t>(address, data);
	}

	void __fastcall SafeWrite16(uintptr_t address, uint16_t data) noexcept {
		SafeWrite<uint16_t>(address, data);
	}

	void __fastcall SafeWrite32(uintptr_t address, uint32_t data) noexcept {
		SafeWrite<uint32_t>(address, data);
	}

	void __fastcall SafeWrite64(uintptr_t address, uint64_t data) noexcept {
		SafeWrite<uint64_t>(address, data);
	}

	SPEC_NOINLINE void __fastcall SafeWriteBuf(uintptr_t address, const void* data, uint32_t dataLength) noexcept {
		MemoryUnlock unlock(address, dataLength);
		memcpy(reinterpret_cast<void*>(address), data, dataLength);
	}

	void __fastcall ReplaceCall(uintptr_t address, uintptr_t target) noexcept {
		SafeWriteRel<uint8_t>(address, target);
	}

	SPEC_NOINLINE void __fastcall ReplaceVirtualCall(uintptr_t address, uintptr_t target, uint32_t overwriteLength) noexcept {
		constexpr uint32_t call_length = 5;
		bool validOverwrite = overwriteLength > call_length;
		MemoryUnlock unlock(address, validOverwrite ? overwriteLength : call_length);
		if (validOverwrite)
			memset(reinterpret_cast<void*>(address + call_length), 0x90, overwriteLength - call_length);

		RawWrite<uint8_t>(address, 0xE8);
		RawWriteRel<sizeof(uint8_t)>(address, target);
	}

	void __fastcall WriteRelCall(uintptr_t address, uintptr_t target) noexcept {
		SafeWriteRel<uint8_t>(address, target, 0xE8);
	}

	void __fastcall WriteRelJump(uintptr_t address, uintptr_t target) noexcept {
		SafeWriteRel<uint8_t>(address, target, 0xE9);
	}

	void __fastcall WriteRelJnz(uintptr_t address, uintptr_t target) noexcept {
		SafeWriteRel<uint16_t>(address, target, 0x850F);
	}

	void __fastcall WriteRelJle(uintptr_t address, uintptr_t target) noexcept {
		SafeWriteRel<uint16_t>(address, target, 0x8E0F);
	}

	SPEC_NOINLINE void __fastcall PatchMemoryNop(uintptr_t address, uint32_t size) noexcept {
		{
			MemoryUnlock unlock(address, size);
			memset(reinterpret_cast<void*>(address), 0x90, size);
		}
		FlushInstructionCache(GetCurrentProcess(), reinterpret_cast<void*>(address), size);
	}

}

STACK_FRAME_OPT_RESET