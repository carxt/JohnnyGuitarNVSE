#include "CustomHUDShake.hpp"	
#include <unordered_map>
#include <GameUI.h>

namespace CustomHUDShake {

	using ShakeRequestMap = std::unordered_map<const TESFile*, float>;

	ShakeRequestMap* pShakeRequests = nullptr;

	static float GetHUDShakePower() {
		if (!pShakeRequests || pShakeRequests->empty())
			return 0.f;

		auto it = std::max_element(
			pShakeRequests->begin(), pShakeRequests->end(),
			[](const auto& a, const auto& b) {
				return a.second < b.second;
			});
		return it->second;
	}

	void Reset() {
		if (pShakeRequests) {
			delete pShakeRequests;
			pShakeRequests = nullptr;
		}
	}

	void Update() {
		if (InterfaceManager::GetSingleton()->currentMode == 1) {
			float fPower = GetHUDShakePower();
			if (fPower > 0.f)
				HUDMainMenu::SetHUDShake(fPower);
		}
	}

	float __fastcall Get(const TESFile* apFile) {
		if (pShakeRequests) {
			auto it = pShakeRequests->find(apFile);
			if (it != pShakeRequests->end())
				return it->second;
		}

		return 0.f;
	}

	void __fastcall Set(const TESFile* apFile, float afPower) {
		if (!pShakeRequests)
			pShakeRequests = new ShakeRequestMap();

		if (afPower <= 0.f)
			pShakeRequests->erase(apFile);
		else
			pShakeRequests->insert({ apFile, afPower });
	}

}