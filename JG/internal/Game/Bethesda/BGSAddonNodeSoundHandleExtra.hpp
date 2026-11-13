#pragma once

#include "BSSoundHandle.hpp"
#include "Gamebryo/NiExtraData.hpp"

class BGSAddonNodeSoundHandleExtra : public NiExtraData {
public:
	BSSoundHandle hSound;

	NIRTTI_ADDRESS(0x11C806C);

	static const NiFixedString& GetTag();

private:
	static constexpr AddressPtr<NiFixedString*, 0x11C8058> pTag;
};

ASSERT_SIZE(BGSAddonNodeSoundHandleExtra, 0x18)