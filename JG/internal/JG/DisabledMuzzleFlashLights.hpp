#pragma once

namespace DisabledMuzzleFlashLights {

	struct _Mode {
		enum Mode {
			NONE = -1,
			ENABLE,
			DISABLE_ALL,
			DISABLE_PLAYER,
			DISABLE_NPCS,
			COUNT,
		};
	};
	using Mode = _Mode::Mode;

	void Install();

	void Reset();

	Mode SetMode(Mode aeMode);

}