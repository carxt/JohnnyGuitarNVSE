#pragma once

#include "FR2MatrixVTC.hpp"

inline FR2MatrixVTC<float>::FR2MatrixVTC() {
	ThisCall(0x449610, this);
}

inline FR2MatrixVTC<float>::~FR2MatrixVTC() {
	ThisCall(0x44A040, this);
}