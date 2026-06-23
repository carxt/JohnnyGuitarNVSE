#include "MediaLocationControllerOverride.hpp"

class PlayerCharacter;

namespace MediaLocationControllerOverride {

	bool bOverrideActive = false;
	MediaLocationController* pOverrideController = nullptr;

	HookUtils::CallDetour kDetour;
	MediaLocationController* __fastcall GetMediaLocationControllerHook(PlayerCharacter* apPlayer) {
		if (bOverrideActive)
			return pOverrideController;
		return ThisCall<MediaLocationController*>(kDetour, apPlayer);

	}

	void Reset() {
		bOverrideActive = false;
		pOverrideController = nullptr;
	}

	void Set(MediaLocationController* apController) {
		bOverrideActive = true;
		pOverrideController = apController;
	}

	void Install() {
		kDetour.ReplaceCall(0x82FC95, GetMediaLocationControllerHook);
	}

}