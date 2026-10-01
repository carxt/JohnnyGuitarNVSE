#pragma once

#include "SkyObject.hpp"

class BSFogProperty;

class Atmosphere : public SkyObject {
public:
	virtual void	InitializeAlt(NiNode* apRoot, BSFogProperty* apFogProperty);

	NiNodePtr					spAtmosphere;
	NiPointer<BSFogProperty>	spFog;
	NiNodePtr					spSkyQuadNode;
	NiRefObjectPtr				spSkyQuad;
	bool						bUpdateFogDistance;
};

ASSERT_SIZE(Atmosphere, 0x1C);