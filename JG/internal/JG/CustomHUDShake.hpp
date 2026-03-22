#pragma once

namespace CustomHUDShake {
	void Init();
	void Reset();
	void Update();
	float Get(uint8_t modId);
	void Set(uint8_t modId, float power);
}