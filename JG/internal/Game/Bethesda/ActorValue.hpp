#pragma once

class ActorValueInfo;

class ActorValue {
public:
	struct _Index {
		enum Index {
			NONE						= -1,
			AGGRESSION					= 0,
			CONFIDENCE					= 1,
			ENERGY						= 2,
			RESPONSIBILITY				= 3,
			MOOD						= 4,
			STRENGTH					= 5,
			PERCEPTION					= 6,
			ENDURANCE					= 7,
			CHARISMA					= 8,
			INTELLIGENCE				= 9,
			AGILITY						= 10,
			LUCK						= 11,
			ACTION_POINTS				= 12,
			CARRY_WEIGHT				= 13,
			CRIT_CHANCE					= 14,
			HEAL_RATE					= 15,
			HEALTH						= 16,
			MELEE_DAMAGE				= 17,
			DAMAGE_RESISTANCE			= 18,
			POISON_RESIST				= 19,
			RAD_RESIST					= 20,
			SPEED_MULT					= 21,
			FATIGUE						= 22,
			KARMA						= 23,
			XP							= 24,
			PERCEPTION_CONDITION		= 25,
			ENDURANCE_CONDITION			= 26,
			LEFT_ATTACK_CONDITION		= 27,
			RIGHT_ATTACK_CONDITION		= 28,
			LEFT_MOBILITY_CONDITION		= 29,
			RIGHT_MOBILITY_CONDITION	= 30,
			BRAIN_CONDITION				= 31,
			BARTER						= 32,
			BIG_GUNS					= 33,
			ENERGY_WEAPONS				= 34,
			EXPLOSIVES					= 35,
			LOCKPICK					= 36,
			MEDICINE					= 37,
			MELEE_WEAPONS				= 38,
			REPAIR						= 39,
			SCIENCE						= 40,
			GUNS						= 41,
			SNEAK						= 42,
			SPEECH						= 43,
			SURVIVAL					= 44,
			UNARMED						= 45,
			INVENTORY_WEIGHT			= 46,
			PARALYSIS					= 47,
			INVISIBILITY				= 48,
			CHAMELEON					= 49,
			NIGHTEYE					= 50,
			TURBO						= 51,
			FIRE_RESIST					= 52,
			WATER_BREATHING				= 53,
			RADIATION_RADS				= 54,
			BLOODY_MESS					= 55,
			UNARMED_DAMAGE				= 56,
			ASSISTANCE					= 57,
			ELECTRIC_RESIST				= 58,
			FROST_RESIST				= 59,
			ENERGY_RESIST				= 60,
			EMP_RESIST					= 61,
			VARIABLE_01					= 62,
			VARIABLE_02					= 63,
			VARIABLE_03					= 64,
			VARIABLE_04					= 65,
			VARIABLE_05					= 66,
			VARIABLE_06					= 67,
			VARIABLE_07					= 68,
			VARIABLE_08					= 69,
			VARIABLE_09					= 70,
			VARIABLE_10					= 71,
			IGNORE_CRIPPLED_LIMBS		= 72,
			DEHYDRATION					= 73,
			HUNGER						= 74,
			SLEEP_DEPRIVATION			= 75,
			DAMAGE_THRESHOLD			= 76,
			COUNT,
			INVALID = COUNT,
		};
	};
	using Index = _Index::Index;

	struct _Section {
		enum Section {
			ATTRIBUTE			= 0,
			DERIVED_ATTRIBUTE	= 1,
			SKILL				= 2,
			AI_ATTRIBUTE		= 3,
			CONDITION			= 4,
			INT_VALUE			= 5,
			RESISTANCE			= 6,
			VARIABLE			= 7,
			COUNT,
		};
	};
	using Section = _Section::Section;

	struct _Flags {
		enum Flags {
			FAST_MODIFIER			= 0x1,
			CREATURE_MAPPED			= 0x2,
			EFFECT_SKILL			= 0x4,
			MAX_TEN					= 0x8,
			MAX_ONE_HUNDRED			= 0x10,
			DAMAGE_MIN_ZERO			= 0x20,
			DERIVED_PLUS_BASE		= 0x40,
			DERIVED_IF_AUTOCALC		= 0x80,
			ENUMERATION				= 0x100,
			DAMAGE_IS_POSITIVE		= 0x200,
			COMBAT_SKILL			= 0x400,
			DERIVED_ALWAYS			= 0x800,
			CREATURE_NOT_DERIVED	= 0x1000,
			DEPRECATED				= 0x2000,
			NO_SCRIPT_MODAV			= 0x4000,
			MIN_ONE					= 0x8000,
			UNK_10000				= 0x10000,
			UNK_20000				= 0x20000,
			UNK_40000				= 0x40000,
			UNK_80000				= 0x80000,
		};
	};
	using Flags = _Flags::Flags;

	ActorValueInfo* pInfos[77];

	static ActorValue* GetSingleton();

	static bool GetIsSkill(Index aeIndex);
	static bool GetFlag(Index aeIndex, uint32_t auiFlag);
	static uint8_t ToArrayIndex(Section aeSection, Index aeIndex);
	static Index ToActorValue(Section aeSection, uint8_t aeIndex);
	static const char* GetActorValueName(Index aeIndex);
};

ASSERT_SIZE(ActorValue, 0x134);