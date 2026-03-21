#pragma once
#include <GameObjects.h>
#include <unordered_map>
namespace NPCAccuracy {

	struct Tables {
		std::unordered_map<uintptr_t, float> ACTREF;

		std::unordered_map<uintptr_t, float> ACTBAS;
		std::unordered_map<uintptr_t, float> CSTY;
		std::unordered_map<uintptr_t, float> FACT;
	};

	extern Tables tables;
	void Hook();
	double __fastcall returnActorMult(Actor* a_refr);
	void FlushMapRefs();

	template <uintptr_t a_addr>
	class HookNPCAccuracy {
	private:
		static inline uintptr_t hookCall = a_addr;
	public:
		static  float __fastcall Hook(Actor* a_refr, void* edx, int mode) {
			auto res = ThisCall<float>(hookCall, a_refr, mode);
			res *= returnActorMult(a_refr);
			return res;
		}

		HookNPCAccuracy() {

			uintptr_t hookPoint = hookCall;
			hookCall = GetRelJumpAddr(hookCall);
			WriteRelCall(hookPoint, (uintptr_t)Hook);
		}
	};

	
};