#include "NoHeadlessTalkingFix.hpp"
#include <GameObjects.h>
#include <GameProcess.h>
#include "Bethesda/DialoguePackage.hpp"

#include "Shared/SafeWrite/SafeWrite.hpp"

namespace NoHeadlessTalkingFix {

	bool __fastcall CanSpeakThroughHead(Actor* apActor) {
		const bool bNoHead = ThisCall<bool>(0x573090, apActor, BODY_PART_TYPE::HEAD_1) || ThisCall<bool>(0x573090, apActor, BODY_PART_TYPE::HEAD_2);

		bool bCanSpeak = !bNoHead;
		if (bCanSpeak) {
			const BaseProcess* pAIProcess = apActor->GetCurrentAIProcess();
			if (pAIProcess && pAIProcess->GetProcessLevel() == PROCESS_TYPE::HIGH && apActor->IsDead(true)) {
				const DialoguePackage* pPackage = static_cast<DialoguePackage*>(pAIProcess->GetCurrentPackage());
				if (pPackage) {
					const bool bDialoguePackage = pPackage->GetPackType() == PACKAGE_TYPE::DIALOGUE || pPackage->GetPackType() == PACKAGE_TYPE::IN_GAME_DIALOGUE;
					if (bDialoguePackage && (apActor != pPackage->GetTargetOfConversation()) && (apActor == pPackage->GetActorStartedConversation()))
						bCanSpeak = false;
				}
			}
		}
		return bCanSpeak;
	}

	HookUtils::CallDetour kCanTalkDetour;
	BaseProcess* __fastcall NoHeadlessTalkingHook(Actor* apActor) {
		uint8_t* pEBP = GetParentBasePtr(_AddressOfReturnAddress());
		Actor* pSpeaker = *reinterpret_cast<Actor**>(pEBP + 0x8);

		BaseProcess* pAIProcess = ThisCall<BaseProcess*>(kCanTalkDetour, apActor);
		if (!pAIProcess || !CanSpeakThroughHead(pSpeaker))
			return nullptr;

		return pAIProcess;
	}

	void Install() {
		kCanTalkDetour.ReplaceCall(0x8EC54D, NoHeadlessTalkingHook);
	}

}
