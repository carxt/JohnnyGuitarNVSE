#pragma once

#include "TESBoundObject.hpp"
#include "TESModelTextureSwap.hpp"

class TESSound;

class BGSAddonNode : public TESBoundObject, public TESModelTextureSwap {
public:
	BGSAddonNode();
	~BGSAddonNode();

	struct ALIGN1 _AddonNodeFlags {
		enum Flags : uint8_t {
			IS_MASTER_PARTICLE_SYSTEM = 1u << 0,
		};

		bool bIsMasterParticleSystem : 1;
	};
	using AddonNodeFlags = _AddonNodeFlags::Flags;

	struct AddonData {
		uint16_t					usMasterParticleCap;
		Bitfield<_AddonNodeFlags>	ucFlags;
	};

	uint32_t	uiIndex;
	TESSound*	pSound;
	AddonData	kData;
	uint32_t	uiParticleSystemIndex;

	TESFORM_TYPE(BGSAddonNode);

	uint32_t GetIndex() const;
	uint32_t GetParticleSystemIndex() const;

	bool IsMasterParticleSystem() const;
	uint16_t GetMasterParticleCap() const;
};

ASSERT_SIZE(BGSAddonNode, 0x60);