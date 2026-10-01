#pragma once

#include "TESObjectACTI.hpp"
#include "Gamebryo/NiPoint3.hpp"

class TESFurniture : public TESObjectACTI {
public:
	struct ALIGN4 _FurnitureFlags {
		enum Flags : uint32_t {
			// 0 - 29 are marker enablement bits
			CAN_SIT_ON		= 1u << 30,
			CAN_SLEEP_ON	= 1u << 31,
		};

		bool					: 8;
		bool					: 8;
		bool					: 8;
		bool					: 6;
		bool bCanSitOn			: 1;
		bool bCanSleepOn		: 1;
	};
	using FurnitureFlags = _FurnitureFlags::Flags;

	Bitfield<_FurnitureFlags> uiFurnitureFlags;

	bool GetMarkerEnabled(uint32_t auiIndex) const;
	void SetMarkerEnabled(uint32_t auiIndex, bool abEnabled);

	bool CanSitOn() const;
	void SetCanSitOn(bool abVal);

	bool CanSleepOn() const;
	void SetCanSleepOn(bool abVal);

#ifdef GAME
	float GetMarkerHeadingOffset(uint32_t auiIndex) const;

	NiPoint3 GetMarkerTargetOffset(uint32_t auiIndex, float afScale) const;
#endif

	static bool IsSitMarker(uint32_t auiIndex);

	static bool IsSleepMarker(uint32_t auiIndex);
};

#ifdef GAME
ASSERT_SIZE(TESFurniture, 0x94);
#else
ASSERT_SIZE(TESFurniture, 0xC8);
#endif