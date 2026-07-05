#pragma once

namespace JIPUtils {

	extern HMODULE hJIP;

	static inline BOOL IsValid() {
		return hJIP != 0;
	}

	static inline size_t __fastcall GetAddress(size_t aiAddress) {
		return reinterpret_cast<size_t>(hJIP) + aiAddress - 0x10000000;
	}

	SPEC_NOINLINE void Init();
}