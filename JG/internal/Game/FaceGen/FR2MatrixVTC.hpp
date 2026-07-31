#pragma once

#include "oldstd.hpp"

template<typename T>
struct FR2MatrixVTC {
	FR2MatrixVTC();
	~FR2MatrixVTC();

	oldstd::vector<T>	kData;
	uint32_t			uiRowCount;
	uint32_t			uiColCount;
};

#include "FR2MatrixVTC.inl"

ASSERT_SIZE(FR2MatrixVTC<float>, 0x20);