#pragma once

using FormID = uint32_t;

namespace JohnnyRadios {
	void Reset();
	void Update();
	bool IsAvailable(FormID formID);
}