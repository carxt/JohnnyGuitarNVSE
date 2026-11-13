#pragma once

#include "Gamebryo/NiTPointerMap.hpp"
#include "BSSoundHandle.hpp"

class BGSAcousticSpace;
class TESSound;

class FalloutAudio {
public:
	static constexpr AddressPtr<bool, 0x11DCFA4> bRadioMute;
	static constexpr AddressPtr<bool, 0x11DCFA5> bMainMenuMusic;
	static constexpr AddressPtr<bool, 0x11DCFA6> bRegionUpdateDisabled;
	static constexpr AddressPtr<bool, 0x11DCFA7> bLockAcousticSpace;
	static constexpr AddressPtr<TESSound*, 0x11DCFA8> pNoActivationSound;
	static constexpr AddressPtr<int32_t, 0x11DCFAC> iCurrentTime;
	static constexpr AddressPtr<bool, 0x11DCFB0> bUseWalla;
	static constexpr AddressPtr<bool, 0x11DCFB1> bUpdateAcousticSpace;
	static constexpr AddressPtr<bool, 0x11DCFB2> bNewGameMusic;
	static constexpr AddressPtr<BGSAcousticSpace*, 0x11DCFB4> pCurrentSpace;
	static constexpr AddressPtr<BGSAcousticSpace*, 0x11DCFB8> pCurrentCellSpace;
	static constexpr AddressPtr<BSSoundHandle, 0x11DD0D8> kAmbientLoop;
	static constexpr AddressPtr<NiTPointerMap<uint32_t, BSSoundHandle*>, 0x11DD014> kCurrentRegionSounds;
};