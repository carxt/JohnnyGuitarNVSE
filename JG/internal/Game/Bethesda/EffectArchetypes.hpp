#pragma once

#include "ActorValue.hpp"

class EffectItem;
class MagicItem;
class MagicCaster;

typedef void* (*_CreateEffect)(MagicCaster*, MagicItem*, EffectItem*);

struct EffectArchetypes {
	struct _Type {
		enum Type {
			VALUE_MODIFIER,
			SCRIPT,
			DISPEL,
			CURE_DISEASE,
			ABSORB,
			SHIELD,
			CALM,
			DEMORALIZE,
			FRENZY,
			COMMAND_CREATURE,
			COMMAND_HUMANOID,
			INVISIBILITY,
			CHAMELEON,
			LIGHT,
			DARKNESS,
			NIGHT_EYE,
			LOCK,
			OPEN,
			BOUND_ITEM,
			SUMMON_CREATURE,
			DETECT_LIFE,
			TELEKINESIS,
			DISINTEGRATE_ARMOR,
			DISINTEGRATE_WEAPON,
			PARALYSIS,
			REANIMATE,
			SOUL_TRAP,
			TURN_UNDEAD,
			SUN_DAMAGE,
			VAMPIRISM,
			CURE_PARALYSIS,
			CURE_ADDICTION,
			CURE_POISON,
			CONCUSSION,
			VALUE_AND_PARTS,
			LIMB_CONDITION,
			TURBO,
			COUNT,
		};
	};
	using Type = _Type::Type;

	struct ALIGN4 _Flags {
		enum Flags : uint32_t {
			ASSOCIATED_ACTOR_VALUE		= 1u << 1,
			ASSOCIATED_CREATURE			= 1u << 2,
			ASSOCIATED_NPC				= 1u << 3,
			ASSOCIATED_WEAPON			= 1u << 4,
			ASSOCIATED_ARMOR			= 1u << 5,
			ASSOCIATED_SCRIPT			= 1u << 6,
		};

		bool bAssociatedActorValue		: 1;
		bool bAssociatedCreature		: 1;
		bool bAssociatedNPC				: 1;
		bool bAssociatedWeapon			: 1;
		bool bAssociatedArmor			: 1;
		bool bAssociatedScript			: 1;
	};
	using Flags = _Flags::Flags;

	struct ArchetypeDef {
		const char*			pName;
		_CreateEffect		pConstructor;
		Bitfield<_Flags>	uiFlags;
		ActorValue::Index	eFixedActorValue;
	};

	static ArchetypeDef* GetArchetype(Type aeType);
	static const char* GetArchetypeName(Type aeType);
	static bool IsFlagSet(Type aeType, uint32_t auiFlag);

private:
	static constexpr AddressPtr<ArchetypeDef, 0x1183320, Type::COUNT> kArchetypes;
};

ASSERT_SIZE(EffectArchetypes::ArchetypeDef, 0x10);