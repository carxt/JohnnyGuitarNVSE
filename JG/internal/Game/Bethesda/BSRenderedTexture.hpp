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

	NiRenderTargetGroup* GetGroup() const;

	static bool IsOutsideFrame();

	static void Start(uint32_t auiClearMode, NiRenderTargetGroup* apGroup);
	static void StartOffscreen(uint32_t auiClearMode, NiRenderTargetGroup* apGroup);

	static void Stop();
	static void StopOffscreen();

	static void Begin(NiRenderTargetGroup* apGroup, uint32_t uiClearMode);
	static void BeginTexture(BSRenderedTexture* apTexture, uint32_t auiClearMode);

	static void End();
	static void EndAll();
};

ASSERT_SIZE(BSRenderedTexture, 0x40);