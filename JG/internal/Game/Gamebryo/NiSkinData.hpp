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
		BoneVertData() = default;
		~BoneVertData() = default;

		uint16_t	m_usVert	= 0;
		float		m_fWeight	= 0.f;
	};

	class BoneData {
	public:
		BoneData() = default;
		~BoneData() = default;

		NiTransform		m_kSkinToBone		= NiTransform();
		NiBound			m_kBound			= NiBound();
		BoneVertData*	m_pkBoneVertData	= 0;
		uint16_t		m_usVerts			= 0;
	};

	NiSkinPartition*	m_spSkinPartition;
	NiTransform			m_kRootParentToSkin;
	BoneData*			m_pkBoneData;
	uint32_t			m_uiBones;

	CREATE_OBJECT(NiSkinData, 0xA84D30);
	NIRTTI_ADDRESS(0x11F5B24);

	static NiSkinData* Create(uint32_t auiBones, BoneData* apBoneData, const NiTransform& arRootParentToSkin, const NiPoint3* apVerts);
};

ASSERT_SIZE(NiSkinData, 0x48);