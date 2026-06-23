#pragma once

namespace HookUtils {

	namespace {
		template <typename T>
		class _MethodConverter {
			union {
				const T		func;
				uintptr_t	funcPtr;
			};
		public:
			constexpr _MethodConverter(const T function) noexcept : func(function) {};

			constexpr operator uintptr_t() const noexcept { return funcPtr; };
		};

		template <typename T>
		concept WritableFunction =
			std::is_member_function_pointer_v<T> ||
			std::is_pointer_v<T> ||
			std::is_integral_v<T>;

		template <typename T>
		concept DetourFunction =
			std::is_member_function_pointer_v<T> ||
			std::is_pointer_v<T>;
	}

	class MemoryUnlock {
		const uintptr_t _addr;
		const uintptr_t _size;
		DWORD _oldProtect;
	public:
		MemoryUnlock(uintptr_t address, uintptr_t size = sizeof(uintptr_t), uint32_t flags = 0x40) noexcept; // flags set to PAGE_EXECUTE_READWRITE
		~MemoryUnlock() noexcept;
	};

	// Taken from lStewieAl.
	// Returns the address of the jump/called function, assuming there is one.
	constexpr uintptr_t __fastcall GetRelAddr(uintptr_t address, uintptr_t target, uint32_t offset) noexcept {
		return target - address - offset - 4;
	}

	constexpr uintptr_t __fastcall GetRelJumpAddr(uintptr_t address) noexcept {
		return *reinterpret_cast<uintptr_t*>(address + 1) + address + 5;
	}

	constexpr uintptr_t __fastcall GetWriteAddr(uintptr_t address) noexcept {
		return *reinterpret_cast<uintptr_t*>(address);
	}

	void __fastcall PatchMemoryNop(uintptr_t address, uint32_t size) noexcept;

	void __fastcall SafeWrite8(uintptr_t address, uint8_t data) noexcept;
	void __fastcall SafeWrite16(uintptr_t address, uint16_t data) noexcept;
	void __fastcall SafeWrite32(uintptr_t address, uint32_t data) noexcept;
	void __fastcall SafeWrite64(uintptr_t address, uint64_t data) noexcept;
	void __fastcall SafeWriteBuf(uintptr_t address, const void* data, uint32_t dataLength) noexcept;

	void __fastcall ReplaceCall(uintptr_t address, uintptr_t target) noexcept;
	void __fastcall ReplaceVirtualCall(uintptr_t address, uintptr_t target, uint32_t overwriteLength) noexcept;

	void __fastcall WriteRelCall(uintptr_t address, uintptr_t target) noexcept;
	void __fastcall WriteRelJump(uintptr_t address, uintptr_t target) noexcept;
	void __fastcall WriteRelJnz(uintptr_t address, uintptr_t target) noexcept;
	void __fastcall WriteRelJle(uintptr_t address, uintptr_t target) noexcept;

	inline void __fastcall PatchMemoryNopRange(uintptr_t startAddress, uintptr_t endAddress) noexcept {
		PatchMemoryNop(startAddress, endAddress - startAddress);
	}

	template <uintptr_t N>
	inline void SafeWriteBuf(uintptr_t address, const char(&data)[N]) noexcept {
		SafeWriteBuf(address, data, N - 1);
	}


	template <WritableFunction T>
	inline void __fastcall ReplaceCall(uintptr_t address, T target) noexcept {
		using _TYPE = std::conditional_t<std::is_member_function_pointer_v<T>, _MethodConverter<T>, uintptr_t>;
		ReplaceCall(address, _TYPE(target));
	}

	template <WritableFunction T>
	inline void __fastcall WriteRelCall(uintptr_t address, T target) noexcept {
		using _TYPE = std::conditional_t<std::is_member_function_pointer_v<T>, _MethodConverter<T>, uintptr_t>;
		WriteRelCall(address, _TYPE(target));
	}

	template <WritableFunction T>
	inline void __fastcall WriteRelJump(uintptr_t address, T target) noexcept {
		using _TYPE = std::conditional_t<std::is_member_function_pointer_v<T>, _MethodConverter<T>, uintptr_t>;
		WriteRelJump(address, _TYPE(target));
	}

	template <WritableFunction T>
	inline void __fastcall ReplaceVirtualCall(uintptr_t address, T target, uint32_t overwriteLength) noexcept {
		using _TYPE = std::conditional_t<std::is_member_function_pointer_v<T>, _MethodConverter<T>, uintptr_t>;
		ReplaceVirtualCall(address, _TYPE(target), overwriteLength);
	}

	template <WritableFunction T>
	inline void __fastcall ReplaceVirtualFunc(uintptr_t address, T target) noexcept {
		using _TYPE = std::conditional_t<std::is_member_function_pointer_v<T>, _MethodConverter<T>, uintptr_t>;
		SafeWrite32(address, _TYPE(target));
	}

	constexpr void** __fastcall GetVTable(void* __restrict apClass) noexcept {
		return *reinterpret_cast<void***>(apClass);
	}

	constexpr void __fastcall SetVTable(void* __restrict apClass, void** __restrict apVTable) noexcept {
		*reinterpret_cast<void***>(apClass) = apVTable;
	}

	template <typename T>
	inline void __fastcall ReplaceVTableEntry(void** apVTable, uint32_t auiPosition, T target) noexcept {
		using _TYPE = std::conditional_t<std::is_member_function_pointer_v<T>, _MethodConverter<T>, uintptr_t>;
		reinterpret_cast<uintptr_t*>(apVTable)[auiPosition] = _TYPE(target);
	}

	// Stores the function-to-call before overwriting it, to allow calling the overwritten function after our hook is over.
	// Thanks Demorome and lStewieAl
	class Detour {
	protected:
		uintptr_t overwritten_addr = 0;

		static DECLSPEC_NOINLINE bool __fastcall ValidateCallAddress(uintptr_t address, const char* caller, bool noError = false) noexcept {
			if (*reinterpret_cast<uint8_t*>(address) != 0xE8) {
				if (!noError) {
					char cTextBuffer[72];
					sprintf_s(cTextBuffer, "Cannot write detour - address 0x%08X is not a function call.", address);
					MessageBoxA(nullptr, cTextBuffer, caller, MB_OK | MB_ICONERROR);
				}
				return false;
			}
			return true;
		}

		static DECLSPEC_NOINLINE bool __fastcall ValidateJumpAddress(uintptr_t address, const char* caller, bool noError = false) noexcept {
			if (*reinterpret_cast<uint8_t*>(address) != 0xE9) {
				if (!noError) {
					char cTextBuffer[72];
					sprintf_s(cTextBuffer, "Cannot write detour - address 0x%08X is not a jump.", address);
					MessageBoxA(nullptr, cTextBuffer, caller, MB_OK | MB_ICONERROR);
				}
				return false;
			}
			return true;
		}

	public:
		[[nodiscard]] inline uintptr_t GetOverwrittenAddr() const noexcept { return overwritten_addr; }

		operator uintptr_t () const {
			return GetOverwrittenAddr();
		}

		template <DetourFunction T>
		inline void __fastcall SafeWrite32(uintptr_t address, T target) noexcept {
			using _TYPE = std::conditional_t<std::is_member_function_pointer_v<T>, _MethodConverter<T>, uintptr_t>;
			overwritten_addr = GetWriteAddr(address);
			HookUtils::SafeWrite32(address, _TYPE(target));
		}
	};

	class CallDetour : public Detour {
	public:
		template <DetourFunction T>
		inline void __fastcall WriteRelCall(uintptr_t address, T target, bool optional = false) noexcept {
			bool bHook = optional;
			if (ValidateCallAddress(address, __FUNCTION__, optional)) {
				overwritten_addr = GetRelJumpAddr(address);
				bHook = true;
			}

			if (bHook)
				HookUtils::WriteRelCall(address, target);
		}

		template <DetourFunction T>
		inline void __fastcall ReplaceCall(uintptr_t address, T target, bool optional = false) noexcept {
			bool bHook = optional;
			if (ValidateCallAddress(address, __FUNCTION__, optional)) {
				overwritten_addr = GetRelJumpAddr(address);
				bHook = true;
			}

			if (bHook)
				HookUtils::ReplaceCall(address, target);
		}
	};

	class JumpDetour : public Detour {
	public:
		template <DetourFunction T>
		inline void __fastcall WriteRelJump(uintptr_t address, T target, bool optional = false) noexcept {
			bool bHook = optional;
			if (ValidateJumpAddress(address, __FUNCTION__, optional)) {
				overwritten_addr = GetRelJumpAddr(address);
				bHook = true;
			}

			if (bHook)
				HookUtils::WriteRelJump(address, target);
		}
	};

	class VirtFuncDetour : public Detour {
	public:
		template <DetourFunction T>
		inline void __fastcall ReplaceVirtualFunc(uintptr_t address, T target) noexcept {
			overwritten_addr = *reinterpret_cast<uintptr_t*>(address);
			HookUtils::ReplaceVirtualFunc(address, target);
		}
	};

	// This detour is conditional due to its nature
	// Detour returns only an overwritten, *non virtual* call
	class VirtCallDetour : public Detour {
	public:
		template <DetourFunction T>
		inline void __fastcall ReplaceVirtualCall(uintptr_t address, T target, uint32_t overwriteLength) noexcept {
			if (*reinterpret_cast<uint8_t*>(address) == 0xE8)
				overwritten_addr = GetRelJumpAddr(address);

			HookUtils::ReplaceVirtualCall(address, target, overwriteLength);
		}
	};

};