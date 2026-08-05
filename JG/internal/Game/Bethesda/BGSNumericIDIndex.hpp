#pragma once

struct BGSNumericIDIndex {
	uint8_t ucData1;
	uint8_t ucData2;
	uint8_t ucData3;

	uint32_t GetNumericID() const;
	void SetNumericID(uint32_t auiID);
};

ASSERT_SIZE(BGSNumericIDIndex, 0x3);