#include "CombatTimeStamp.hpp"

// GAME - 0x435E00
float CombatTimeStamp::GetElapsedTime() const {
	return ThisCall<float>(0x435E00, this);
}

// GAME - 0x97FA90
float CombatTimeStamp::DisplayElapsedTime() const {
	return ThisCall<float>(0x97FA90, this);
}
