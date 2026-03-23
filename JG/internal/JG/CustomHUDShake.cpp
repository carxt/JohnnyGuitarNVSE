#include "CustomHUDShake.hpp"	
#include <unordered_map>
#include <GameUI.h>

namespace CustomHUDShake {
	std::unordered_map<uint8_t, float> shakeRequests;

	float GetHUDShakePower() {
		if (shakeRequests.empty()) {
			return 0.0f;
		}
		auto maxElement = std::max_element(
			shakeRequests.begin(), shakeRequests.end(),
			[](const auto& a, const auto& b) {
				return a.second < b.second;
			});
		return maxElement->second;
	}

	void Init()
	{
		shakeRequests.reserve(0xFF);
	}

	void Reset() {
		shakeRequests.clear();
	}

	void Update()
	{
		if (InterfaceManager::GetSingleton()->currentMode == 1) {
			float power = GetHUDShakePower();
			if (power > 0.0f) {
				CdeclCall<void>(0x94C3A0, power);
			}
		}
	}
	float Get(uint8_t modId)
	{
		if (modId < 0xFF && shakeRequests.find(modId) != shakeRequests.end()) {
			return shakeRequests[modId];
		}
		return 0.0f;
	}

	void Set(uint8_t modId, float power)
	{
		if (power == 0.0f) {
			shakeRequests.erase(modId);
		}
		else {
			shakeRequests[modId] = power;
		}
	}
}