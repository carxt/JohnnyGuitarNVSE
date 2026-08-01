#pragma once

#include "BaseFormComponent.hpp"

class TESForm;
class BGSMenuIcon;

class BGSEquipType : public BaseFormComponent {
public:
	BGSEquipType();
	~BGSEquipType();

	struct _Type {
		enum Type : int32_t {
			NONE			= -1,
			BIG_GUN			= 0,
			ENERGY_WEAPON	= 1,
			SMALL_GUN		= 2,
			MELEE_WEAPON	= 3,
			UNARMED_WEAPON	= 4,
			THROWN_WEAPON	= 5,
			MINE			= 6,
			BODY_WEAR		= 7,
			HEAD_WEAR		= 8,
			HAND_WEAR		= 9,
			CHEMS			= 10,
			STIMPACK		= 11,
			FOOD			= 12,
			ALCOHOL			= 13,
			COUNT,
		};
	};
	using Type = _Type::Type;

	Type	eEquipType;

	Type GetEquipType() const;
	void SetEquipType(Type aeEquipType);

	static Type GetEquipType(const TESForm* apForm);
	static BGSMenuIcon* GetEquipTypeIcon(Type aeType);
	static const char* GetEquipTypeIconFilename(Type aeType);
};

ASSERT_SIZE(BGSEquipType, 0x8);