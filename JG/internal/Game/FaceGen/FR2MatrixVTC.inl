#pragma once

#include "FR2MatrixVTC.hpp"

// GAME - 0x449610
// GECK - 0x446880
inline FR2MatrixVTC<float>::FR2MatrixVTC() {
#ifdef GAME
	ThisCall(0x449610, this);
#else
	ThisCall(0x446880, this);
#endif
}

// GAME - 0x449680
// GECK - 0x68DDD0
inline FR2MatrixVTC<float>::~FR2MatrixVTC() {
#ifdef GAME
	ThisCall(0x449680, this);
#else
	ThisCall(0x68DDD0, this);
#endif
}