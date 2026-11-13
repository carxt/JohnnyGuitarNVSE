#pragma once

#include "Gamebryo/NiPoint3.hpp"

struct FurnitureMark {
	FurnitureMark(uint32_t auiNumber = 0xFF);

	NiPoint3	kPos;
	uint16_t	usHeading;
	uint8_t		ucNumber;

	bool operator==(const FurnitureMark& arOther) const;

	bool operator<(const FurnitureMark& arOther) const;
};

ASSERT_SIZE(FurnitureMark, 0x10);