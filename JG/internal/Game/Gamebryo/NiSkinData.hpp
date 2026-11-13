#pragma once

#include "NiObject.hpp"
#include "NiSkinPartition.hpp"
#include "NiTransform.hpp"
#include "NiBound.hpp"

NiSmartPointer(NiSkinData);

class NiSkinData : public NiObject {
public:
	NiSkinData();
	~NiSkinData();

	class BoneVertData {
	public:
		uint16_t	m_usVert;
		float		m_fWeight;
	};

	class BoneData {
	public:
		NiTransform		m_kSkinToBone;
		NiBound			m_kBound;
		BoneVertData*	m_pkBoneVertData;
		uint16_t		m_usVerts;
	};

	NiSkinPartitionPtr	m_spSkinPartition;
	NiTransform			m_kRootParentToSkin;
	BoneData*			m_pkBoneData;
	uint32_t			m_uiBones;

	CREATE_OBJECT(NiSkinData, 0xA84D30);
	NIRTTI_ADDRESS(0x11F5B24);

	static NiSkinData* Create(uint32_t auiBones, BoneData* apBoneData, const NiTransform& arRootParentToSkin, const NiPoint3* apVerts);
};

ASSERT_SIZE(NiSkinData, 0x48);