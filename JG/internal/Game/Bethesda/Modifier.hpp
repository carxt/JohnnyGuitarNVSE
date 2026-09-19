#pragma once

class Modifier {
public:
	Modifier(int8_t acActorValue, float afValue) : cActorValue(acActorValue), fValue(afValue) {}
	~Modifier() {}

	int8_t	cActorValue;
	float	fValue;
};

ASSERT_SIZE(Modifier, 0x8);