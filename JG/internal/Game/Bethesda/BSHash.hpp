#pragma once

class BSHash {
public:
	uint8_t		ucLast;
	uint8_t		ucLast2;
	uint8_t		ucLength;
	uint8_t		ucFirst;
	uint32_t	uiCRC;
};

ASSERT_SIZE(BSHash, 0x8);