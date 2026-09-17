#pragma once

#include "BGSPrimitive.hpp"

class BSOcclusionPlane;
class BSPortal;

class BGSPrimitivePlane : public BGSPrimitive {
public:
	virtual BSOcclusionPlane*	MakeOcclusionPlane() const;
	virtual BSPortal*			MakePortal() const;
};

ASSERT_SIZE(BGSPrimitivePlane, sizeof(BGSPrimitive));