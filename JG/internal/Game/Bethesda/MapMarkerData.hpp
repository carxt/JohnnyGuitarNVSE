#pragma once

#include "TESFullName.hpp"

class TESForm;

class MapMarkerData {
public:
	struct ALIGN2 _Flags {
		enum Flags : uint16_t {
			VISIBLE		= 1u << 0,
			CAN_TRAVEL	= 1u << 1,
			HIDDEN		= 1u << 2,
		};

		bool bVisible	: 1;
		bool bCanTravel : 1;
		bool bHidden	: 1;
	};
	using Flags = _Flags::Flags;

	enum Type {
		NONE = 0,
		CITY,
		SETTLEMENT,
		ENCAMPMENT,
		NATURAL_LANDMARK,
		CAVE,
		FACTORY,
		MEMORIAL,
		MILITARY,
		OFFICE,
		TOWN_RUINS,
		URBAN_RUINS,
		SEWER_RUINS,
		METRO,
		VAULT,
	};

	TESFullName			kLocationName;
	Bitfield<_Flags>	usFlags;
	uint16_t			usType;
	TESForm*			pReputation;

	bool IsVisible() const			{ return usFlags.Get(Flags::VISIBLE); }
	bool CanTravel() const			{ return usFlags.Get(Flags::CAN_TRAVEL); }
	bool IsHidden() const			{ return usFlags.Get(Flags::HIDDEN); }
	void SetVisible(bool abVal)		{ usFlags.Set(Flags::VISIBLE, abVal); }
	void SetCanTravel(bool abVal)	{ usFlags.Set(Flags::CAN_TRAVEL, abVal); }
	void SetHidden(bool abVal)		{ usFlags.Set(Flags::HIDDEN, abVal); }
};

ASSERT_SIZE(MapMarkerData, 0x14);