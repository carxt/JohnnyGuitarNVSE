#pragma once

class NiTexture;
class NiNode;
class NiCamera;

class ScreenCustomSplatter {
public:
	static constexpr AddressPtr<uint32_t, 0x11C77DC> uiCount;

	static constexpr AddressPtr<bool, 0x11C77E8> bEnabled;
	
	static constexpr AddressPtr<bool, 0x11C77E9> bSecondsForFade;

	static NiNode* GetCurrentRoot();
	
	static NiCamera* GetCamera();

	static bool IsActiveSplatter();

	static NiNode* CreateGeometry(uint32_t auiCount, float afSizeMult, float afOpacityMult);
	
	static void Activate(uint32_t auiCount, float afDuration, uint32_t aeType = 0, float afSizeMult = 1.f, float afOpacityMult = 1.f);
};