#pragma once

#include "Gamebryo/NiSmartPointer.hpp"

class Sky;
class NiNode;

class SkyObject {
public:
	virtual				~SkyObject();
	virtual NiNode*		GetRoot() const;
	virtual void		Initialize(NiNode* apRoot);
	virtual void		Update(Sky* apSky, float afValue);

	NiPointer<NiNode> spRoot;
};

ASSERT_SIZE(SkyObject, 0x8)