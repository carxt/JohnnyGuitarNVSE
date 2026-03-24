#pragma once

#include "Gamebryo/NiObject.hpp"
NiSmartPointer(BSRenderedTexture);

class NiRenderTargetGroup;
class NiRenderedTexture;

class BSRenderedTexture : public NiObject {
public:
	NiPointer<NiRenderTargetGroup>	spRenderTargetGroups[6];
	NiPointer<NiRenderTargetGroup>	spPreRestoreGroup;
	NiPointer<NiRenderTargetGroup>	spRestoreGroup;
	NiPointer<NiRenderTargetGroup>	spPostRestoreGroup;
	int32_t							eType;
	NiPointer<NiRenderedTexture>	spRenderedTextures[4];
};

ASSERT_SIZE(BSRenderedTexture, 0x40);