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
		};
	};
	using SpellType = _SpellType::Type;

	struct _Range {
		enum Range : uint32_t {
			SELF,
			TOUCH,
			TARGET,
			ANY,
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
		};
	};
	using School = _School::School;
};