#pragma once

#include "NiTriBasedGeom.hpp"
#include "NiTriShapeData.hpp"

NiSmartPointer(NiTriShape);

class NiTriShape : public NiTriBasedGeom {
public:
	NiTriShape();
	virtual ~NiTriShape();

	CREATE_OBJECT(NiTriShape, 0xA744D0);
	NIRTTI_ADDRESS(0x11F4A40);

	static NiTriShape* Create(NiTriShapeData* apData);
	static NiTriShape* Create(uint16_t ausVertices, NiPoint3* apkVertex, NiPoint3* apkNormal, NiColorA* apkColor, NiPoint2* apkTexture, uint16_t ausNumTextureSets, uint32_t aeNBTMethod, uint16_t ausTriangles, uint16_t* apusTriList);

	NiTriShapeData* GetModelData() const;

	uint32_t GetTriListLength() const;
	uint16_t* GetTriList() const;
};

ASSERT_SIZE(NiTriShape, 0xC4);