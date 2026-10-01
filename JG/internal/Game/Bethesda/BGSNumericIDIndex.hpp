#pragma once

using FormID = uint32_t;

struct BGSNumericIDIndex {
	uint8_t ucData1;
	uint8_t ucData2;
	uint8_t ucData3;

	FormID GetNumericID() const;
	void SetNumericID(FormID auiID);
};

ASSERT_SIZE(BGSNumericIDIndex, 0x3);