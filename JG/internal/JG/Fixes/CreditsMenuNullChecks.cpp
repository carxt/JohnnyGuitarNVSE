#include "CreditsMenuNullChecks.hpp"

class StartMenu;

namespace CreditsMenuNullChecks {

	template<uint32_t uiAddress>
	class SetFlagHook {
		static inline HookUtils::CallDetour kDetour;

		static void __fastcall Hook(StartMenu* apMenu, void*, uint32_t auiFlags, bool abSet) {
			if (apMenu != nullptr)
				ThisCall(kDetour, apMenu, auiFlags, abSet);
		}

	public:
		SetFlagHook() {
			kDetour.ReplaceCall(uiAddress, Hook);
		}
	};


	template<uint32_t uiAddress>
	class GetFlagHook {
		static inline HookUtils::CallDetour kDetour;

		static bool __fastcall Hook(StartMenu* apMenu, void*, uint32_t auiFlags) {
			if (!apMenu)
				return false;

			return ThisCall<bool>(kDetour, apMenu, auiFlags);
		}

	public:
		GetFlagHook() {
			kDetour.ReplaceCall(uiAddress, Hook);
		}
	};

	void Install() {
		GetFlagHook<0x75F770>();
		SetFlagHook<0x75F8AE>();
		SetFlagHook<0x75F6DA>();
	}
}
