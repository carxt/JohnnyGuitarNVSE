#pragma once

#include "NiTriBasedGeomData.hpp"

NiSmartPointer(NiTriShapeData);

class NiTriShapeData : public NiTriBasedGeomData {
public:
	NiTriShapeData();
	virtual ~NiTriShapeData();

	class SPEC_EMPTY_BASES SharedNormalArray : public NiMemObject {
	public:
		uint16_t	m_usNumSharedNormals;
		uint16_t*	m_pusSharedNormalIndexArray;
	};

	class SPEC_EMPTY_BASES SNAMemBlock : public NiMemObject {
	public:
		uint16_t*		m_pusBlock;
		uint16_t*		m_pusFreeBlock;
		uint32_t		m_uiBlockSize;
		uint32_t		m_uiFreeBlockSize;
		SNAMemBlock*	m_pkNext;
	};

	uint32_t			m_uiTriListLength;
	uint16_t*			m_pusTriList;
	SharedNormalArray*	m_pkSharedNormals;
	uint16_t			m_usSharedNormalsArraySize;
	SNAMemBlock*		m_pkSNAMemoryBlocks;

	CREATE_OBJECT(NiTriShapeData, 0xA7B790);
	NIRTTI_ADDRESS(0x11F4A88);

	static NiTriShapeData* Create(uint16_t ausVertices, NiPoint3* apVertex, NiPoint3* apNormal, NiColorA* apColor, NiPoint2* apTexture, uint16_t ausNumTextureSets, uint32_t aeNBTMethod, uint16_t ausTriangles, uint16_t* apTriList);

	uint32_t GetTriListLength() const;

	uint16_t* GetTriList() const;

	uint32_t GetIndexCount() const { return GetTriListLength(); }

	void SetTriangleIndices(uint16_t ausTriangle, uint16_t ausIndex0, uint16_t ausIndex1, uint16_t ausIndex2);

	void Replace(uint16_t ausTriangles, uint16_t* apTriList);
};

ASSERT_SIZE(NiTriShapeData, 0x58)