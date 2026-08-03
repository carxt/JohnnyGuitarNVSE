#pragma once

#include "BSEnums.hpp"

// Helper "view" class for anim groups (see TESAnimGroup);
class ALIGN2 AnimGroup_View {
protected:
	uint8_t eType		: 8; // ANIM_GROUP_TYPE
	uint8_t eWeapon		: 4; // ANIM_GROUP_WEAPON
	uint8_t eMove		: 3; // ANIM_GROUP_MOVE
	bool	bPowerArmor : 1;

public:
	constexpr AnimGroup_View(uint16_t ausGroup) noexcept { *reinterpret_cast<uint16_t*>(this) = ausGroup; };
	constexpr explicit AnimGroup_View(ANIM_GROUP_MOVE aeMove, ANIM_GROUP_WEAPON aeWeapon, ANIM_GROUP_TYPE aeGroup, bool abPowerArmor) noexcept
		: eType(aeGroup), eWeapon(aeWeapon), eMove(aeMove), bPowerArmor(abPowerArmor) {};

	constexpr uint16_t			Get() const noexcept { return *reinterpret_cast<const uint16_t*>(this); };
	constexpr void				Set(uint16_t ausGroup) noexcept { *reinterpret_cast<uint16_t*>(this) = ausGroup; };

	constexpr ANIM_GROUP_TYPE	GetType() const noexcept { return static_cast<ANIM_GROUP_TYPE>(eType); };
	constexpr void				SetType(ANIM_GROUP_TYPE aeType) noexcept { eType = aeType; };

	constexpr ANIM_GROUP_WEAPON	GetWeapon() const noexcept { return static_cast<ANIM_GROUP_WEAPON>(eWeapon); };
	constexpr void				SetWeapon(ANIM_GROUP_WEAPON aeWeapon) noexcept { eWeapon = aeWeapon; };

	constexpr ANIM_GROUP_MOVE	GetMove() const noexcept { return static_cast<ANIM_GROUP_MOVE>(eMove); };
	constexpr void				SetMove(ANIM_GROUP_MOVE aeMove) noexcept { eMove = aeMove; };

	constexpr bool				GetPowerArmor() const noexcept { return bPowerArmor; };
	constexpr void				SetPowerArmor(bool abVal) noexcept { bPowerArmor = abVal; };
};

ASSERT_SIZE(AnimGroup_View, sizeof(uint16_t));