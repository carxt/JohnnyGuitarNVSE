#pragma once

class Modifier;

class FastModifierCollection {
public:
	Modifier* pModifiers;
};

ASSERT_SIZE(FastModifierCollection, 0x4);