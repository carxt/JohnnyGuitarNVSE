#pragma once

#include "SkyObject.hpp"

class NiPick;
class NiBillboardNode;
class NiTriShape;
class NiDirectionalLight;
class BSShaderAccumulator;

class Sun : public SkyObject {
public:
	NiPointer<NiBillboardNode>		spSunBaseNode;
	NiPointer<NiBillboardNode>		spSunGlareNode;
	NiPointer<NiTriShape>			spSunBase;
	NiPointer<NiTriShape>			spSunQuery;
	NiPick*							pSunPick; // Unused
	NiPointer<NiDirectionalLight>	spLight;
	float							fGlareScale;
	bool							bDoOcclusionTests;
	NiPointer<BSShaderAccumulator>	spSunAccumulator;
};

ASSERT_SIZE(Sun, 0x2C);