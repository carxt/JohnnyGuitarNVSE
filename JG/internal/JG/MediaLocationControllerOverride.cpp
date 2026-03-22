#include "MediaLocationControllerOverride.hpp"
#include <GameObjects.h>

namespace MediaLocationControllerOverride {

	bool mlcOverridden = false;
	MediaLocationController* mlcOverride = nullptr;

	MediaLocationController* __fastcall MLCOverrideHook(PlayerCharacter* player)
	{
		if (mlcOverridden)
		{
			return mlcOverride;
		}
		return ThisCall<MediaLocationController*>(0x9698A0, player);

	}

	void Reset() {
		mlcOverridden = false;
		mlcOverride = nullptr;
	}

	void Set(MediaLocationController* newMLC) {
		mlcOverridden = true;
		mlcOverride = newMLC;
	}

	void Install()
	{
		WriteRelCall(0x82FC95, (uint32_t)MLCOverrideHook);
	}
}