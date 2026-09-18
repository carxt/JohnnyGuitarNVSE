#include "DisintegrationStatFix.hpp"

namespace DisintegrationStatFix {

	void Install() {
		// check if user has Unnecessary Tweaks or lStewieAl's Tweaks installed
		if (*reinterpret_cast<uint8_t*>(0x8A1B4D) == 0xE9 || *reinterpret_cast<uint8_t*>(0x8A1B51) == 0x26)
			return;

		// critical stage 1, jump to checks for IncPCMiscStat
		HookUtils::SafeWrite8(0x8A1B51, 0x26); // change JE offset

		// critical stage 3, jump to checks for IncPCMiscStat
		HookUtils::SafeWriteBuf(0x8A1B1B, "\xF9\x01\x74\x12\x83\xF9\x02\x74\x30\x83\xF9\x04\x74\x2B\x83\xF9\x03\x74\x4A\xEB\x22\x90");

		// critical stages 2 and 4, skip IncPCMiscStat
		HookUtils::SafeWriteBuf(0x8A1B6E, "\x82\xC0\x01\x00\x00\xFF\xD0\xEB\x53\x90");
	}

}
