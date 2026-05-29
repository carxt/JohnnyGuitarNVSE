#pragma once

class Modifier {
public:
	Modifier(uint8_t aucActorValue, float afValue) : ucActorValue(aucActorValue), fValue(afValue) {}
	~Modifier() {}

	uint8_t ucActorValue;
	float	fValue;
};

ASSERT_SIZE(Modifier, 0x8);