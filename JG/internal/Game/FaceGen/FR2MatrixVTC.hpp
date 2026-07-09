#pragma once

#include "oldstd.hpp"

template<typename T>
struct FR2MatrixVTC {
	FR2MatrixVTC();
	~FR2MatrixVTC();

	oldstd::vector<T>	data;
	uint32_t			nrows;
	uint32_t			ncols;
};

#include "FR2MatrixVTC.inl"

ASSERT_SIZE(FR2MatrixVTC<float>, 0x20);