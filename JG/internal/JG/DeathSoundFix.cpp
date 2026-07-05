#include "DeathSoundFix.hpp"
#include "GameObjects.h"
#include "GameProcess.h"
#include "GameSound.h"

namespace DeathSoundFix {
	
	int32_t iDeathSoundMaxTimer = 10;

	float __fastcall FixDeathSoundsTopic(HighProcess* apProcess, Actor* apActor) { //Simpler fix, though we run the risk of overassumptions. 14 seconds should be more than enough though tbh.
		//all the checks can be skipped because they were done above already
		if (apActor->GetDead()) {
			if (DialoguePackage* pPackage = static_cast<DialoguePackage*>(apProcess->GetCurrentPackage())) {
				if ((apActor != pPackage->subject) && (apActor == pPackage->speaker)) { //check for subject because in some cases, subject == target
					return -1.0f;
				}
			}
		}
		return apProcess->dyingTimer + iDeathSoundMaxTimer;
	}
	float __fastcall FixDeathSounds(HighProcess* apProcess, Actor* apActor) { //Simpler fix, though we run the risk of overassumptions. 14 seconds should be more than enough though tbh.
		return apProcess->dyingTimer + iDeathSoundMaxTimer;
	}


	float __fastcall FixDeathSoundsAlt(HighProcess* apProcess, Actor* apActor) { //Alternate complex, confusing, potentially buggy fix.
		constexpr float DYING_TIMER_MIN = FLT_EPSILON * 10; //Establish low tolerance, this should be ideal. Unless someone sets fDyingTimer to 0 or something, but that's their problem.
		float fDyingTimer = apProcess->dyingTimer;
		bool bKeepTalking = apActor->IsTalking() || !(apActor->unk80 & 1);
		if (bKeepTalking) {
			if (fDyingTimer <= DYING_TIMER_MIN) 
				fDyingTimer = DYING_TIMER_MIN;
		}
		return fDyingTimer;
	}

	SPEC_NAKED void FixDeathSoundsHook() {
		__asm {
			mov		edx, dword ptr[ebp + 8]
			jmp		FixDeathSoundsTopic
		}
	}

	void Install() {
		HookUtils::SafeWrite16(0x8EC5C6, 0xBA90);
		HookUtils::SafeWrite32(0x8EC5C8, uintptr_t(FixDeathSoundsHook));
	}

}