#pragma once

#include "BSMap.hpp"
#include "BSEnums.hpp"

class BGSImpactData;

class ImpactSwap {
public:
	struct _FootstepMaterialType {
		enum Type : uint32_t {
			STONE			= 0,
			CONCRETE_BROKEN	= 1,
			METAL			= 2,
			METAL_HOLLOW	= 3,
			METAL_SHEET		= 4,
			WOOD			= 5,
			SAND			= 6,
			DIRT			= 7,
			GRASS			= 8,
			WATER			= 9,
			COUNT,
			INVALID = COUNT
		};
	};
	using FootstepMaterialType = _FootstepMaterialType::Type;

	struct IMPACT_SWAP_DATA {
		IMPACT_MATERIAL_TYPE	eType;
		BGSImpactData*			pOrdData;
		BGSImpactData*			pNewData;
	};

	BSMap<BGSImpactData*, BGSImpactData*>*	pRemappedData[IMPACT_MATERIAL_TYPE::COUNT];
	char									cAltFootstepMaterialNames[FootstepMaterialType::COUNT][30];

	BGSImpactData* GetSwappedImpactData(IMPACT_MATERIAL_TYPE aeType, BGSImpactData* apOrgData) const;
	void AddSwappedImpactData(IMPACT_MATERIAL_TYPE aeType, BGSImpactData* apOrgData, BGSImpactData* apNewData);
	void RemoveSwappedImpactData(IMPACT_MATERIAL_TYPE aeType, BGSImpactData* apOrgData);

	const char* GetAltFootstepMaterialName(FootstepMaterialType aeType) const;

	static const char* GetFootstepMaterialName(FootstepMaterialType aeType);

protected:
#ifdef GAME
	static constexpr AddressPtr<const char*, 0x118C4D0, FootstepMaterialType::COUNT> pFootstepMaterialSoundNames;
#else
	static constexpr AddressPtr<const char*, 0xE9B8EC, FootstepMaterialType::COUNT> pFootstepMaterialSoundNames;
#endif
};

ASSERT_SIZE(ImpactSwap, 0x15C);