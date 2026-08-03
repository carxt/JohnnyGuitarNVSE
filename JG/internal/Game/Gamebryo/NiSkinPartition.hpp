#pragma once

#include "NiObject.hpp"
#include "NiTPrimitiveSet.hpp"

NiSmartPointer(NiSkinPartition);

class NiGeometryBufferData;
class NiTriBasedGeomData;
class NiSkinData;

class NiSkinPartition : public NiObject {
public:
	NiSkinPartition();
	virtual ~NiSkinPartition();

	class SPEC_EMPTY_BASES Interaction : public NiMemObject {
	public:
		uint32_t	m_uiBone;
		float		m_fWeight;
	};

	class SPEC_EMPTY_BASES Partition : public NiMemObject {
	public:
		virtual ~Partition();

		uint16_t*				m_pusBones;
		float*					m_pfWeights;
		uint16_t*				m_pusVertexMap;
		uint8_t*				m_pucBonePalette;
		uint16_t*				m_pusTriList;
		uint16_t*				m_pusStripLengths;
		uint16_t				m_usVertices;
		uint16_t				m_usTriangles;
		uint16_t				m_usBones;
		uint16_t				m_usStrips;
		uint16_t				m_usBonesPerVertex;
		NiGeometryBufferData*	m_pkBuffData;
	};

	class VertexInteractions : public NiTPrimitiveSet<Interaction> {
	public:
	};

	class BoneSet : public NiTPrimitiveSet<uint16_t> {
	public:
	};

	class TriangleSet : public NiTPrimitiveSet<uint16_t> {
	public:
	};

	class SPEC_EMPTY_BASES BoneSetMerger : public NiMemObject {
	public:
		uint32_t		m_uiIndex[2];
		uint16_t		m_usEl[2];
		const BoneSet&	m_kSet0;
		const BoneSet&	m_kSet1;
	};

	typedef NiTPrimitiveSet<BoneSet*> NiBoneSetCollection;

	uint32_t	m_uiPartitions;
	Partition*	m_pkPartitions;

	CREATE_OBJECT(NiSkinPartition, 0xA81FB0);
	NIRTTI_ADDRESS(0x11F5B1C);

	bool MakePartitions(const NiTriBasedGeomData* apTriData, const NiSkinData* apSkinData, uint8_t aucBonesPerPartition, uint8_t aucBonesPerVertex, bool abForcePalette, void** a7 = 0, uint16_t* a8 = 0, bool* a9 = 0);
	
	VertexInteractions* CreateVertexInteractions(uint32_t auiVertices, const NiSkinData* apSkinData);
	
	bool RemoveExcessInteractions(NiTriBasedGeomData* apTriData, uint8_t aucBonesPerPartition, uint8_t aucBonesPerVertex, VertexInteractions* apVertexInteraction);
	
	bool MakeBoneSets(const NiTriBasedGeomData* apTriData, const NiSkinData* apSkinData, uint8_t aucBonesPerPartition, NiSkinPartition::VertexInteractions* apVertexInteraction, NiBoneSetCollection& arBoneSets, uint32_t*& apuiTriangleToPartition, uint32_t** apUnk18);
};

ASSERT_SIZE(NiSkinPartition, 0x10);