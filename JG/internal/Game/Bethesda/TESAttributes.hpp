#pragma once

#include "BaseFormComponent.hpp"
#include "ActorValue.hpp"

class TESAttributes : public BaseFormComponent {
public:
	TESAttributes();
	~TESAttributes();

	enum Attribute {
		STRENGTH		= 0,
		PERCEPTION		= 1,
		ENDURANCE		= 2,
		CHARISMA		= 3,
		INTELLIGENCE	= 4,
		AGILITY			= 5,
		LUCK			= 6,
		COUNT
	};

	uint8_t	ucAttributes[Attribute::COUNT];

	uint8_t GetAttributeValue(ActorValue::Index aeIndex) const;
	void SetAttributeValue(ActorValue::Index aeIndex, uint8_t aucValue, bool abMarkChange);
};

ASSERT_SIZE(TESAttributes, 0xC);