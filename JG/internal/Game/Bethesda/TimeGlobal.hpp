#pragma once

#include "BSTimer.hpp"

class TimeGlobal : public BSTimer {
public:
	static TimeGlobal* GetSingleton();
};
