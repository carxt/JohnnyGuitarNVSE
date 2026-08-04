#pragma once

class MagicSystem {
public:
	struct _SpellType {
		enum Type : uint32_t {
			SPELL,
			DISEASE,
			POWER,
			LESSER_POWER,
			ABILITY,
			POISON,
			ENCHANTMENT,
			POTION,
			WORTCRAFT,
			LEVELLED,
			ADDICTION,
			COUNT,
		};
	};
	using SpellType = _SpellType::Type;

	struct _Range {
		enum Range : uint32_t {
			SELF,
			TOUCH,
			TARGET,
			ANY,
			COUNT,
		};
	};
	using Range = _Range::Range;

	struct _School {
		enum School : uint32_t {
			ALTERATION,
			CONJURATION,
			DESTRUCTION,
			ILLUSION,
			MYSTICISM,
			RESTORATION,
			COUNT,
		};
	};
	using School = _School::School;

	struct _CastingType {
		enum Type : uint32_t {
			CAST_ONCE			= 0,
			WHEN_USED			= 1,
			WHEN_STRIKES		= 2,
			CONSTANT_EFFECT		= 3,
			COUNT,
		};
	};
	using CastingType = _CastingType::Type;
};