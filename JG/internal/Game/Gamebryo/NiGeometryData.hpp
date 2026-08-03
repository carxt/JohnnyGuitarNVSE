#pragma once

#include "NiObject.hpp"
#include "NiBound.hpp"
#include "NiShaderDeclaration.hpp"
#include "NiAdditionalGeometryData.hpp"

NiSmartPointer(NiGeometryData);

class NiGeometryBufferData;
class NiColorA;
class NiPoint2;
class NiTriStripsData;
class NiTriShapeData;

class NiGeometryData : public NiObject {
public:
	NiGeometryData();
	virtual ~NiGeometryData();

	virtual void				SetActiveVertexCount(uint16_t ausActive);
	virtual uint16_t			GetActiveVertexCount() const;
	virtual NiTriStripsData*	IsStripsData() const;
	virtual NiTriShapeData*		IsShapeData() const;
	virtual bool				ContainsVertexData(NiShaderDeclaration::ShaderParameter aeParameter) const;
	virtual void				CalculateNormals();

	enum Consistency {
		MUTABLE				= 0x0000,
		STATIC				= 0x4000,
		CONSISTENCY_MASK	= 0x7000,
	};

	enum KeepFlags {
		KEEP_NONE		= 0,
		KEEP_XYZ		= 1u <<  0,
		KEEP_NORM		= 1u <<  1,
		KEEP_COLOR		= 1u <<  2,
		KEEP_UV			= 1u <<  3,
		KEEP_INDICES	= 1u <<  4,
		KEEP_BONEDATA	= 1u <<  5,
		KEEP_ALL		= 0x3F,
	};

	enum DataFlags {
		NBT_METHOD_NONE			= 0x0000,
		NBT_METHOD_NDL			= 0x1000,
		NBT_METHOD_DEPRECATED	= 0x2000,
		NBT_METHOD_ATI			= 0x3000,
		NBT_METHOD_MASK			= 0xF000,
		TEXTURE_SET_MASK		= 0x3F
	};

	enum Compression {
		COMPRESS_NORM		= 1u <<  0,
		COMPRESS_COLOR		= 1u <<  1,
		COMPRESS_UV			= 1u <<  2,
		COMPRESS_WEIGHT		= 1u <<  3,
		COMPRESS_POSITION	= 1u <<  4,
		COMPRESS_ALL		= 0x1F,
	};

	enum MarkAsChangedFlags {
		VERTEX_MASK				= 1u <<  0,
		NORMAL_MASK				= 1u <<  1,
		COLOR_MASK				= 1u <<  2,
		TEXTURE_MASK			= 1u <<  3,
		TRIANGLE_INDEX_MASK		= 1u <<  4,
		TRIANGLE_COUNT_MASK		= 1u <<  5,
		ALL_MASK				= VERTEX_MASK | NORMAL_MASK | COLOR_MASK | TEXTURE_MASK,
		DIRTY_MASK				= 0xFFF,
	};

	uint16_t							m_usVertices;
	uint16_t							m_usID;
	Bitfield16							m_usDataFlags;
	Bitfield16							m_usDirtyFlags;
	NiBound								m_kBound;
	NiPoint3*							m_pkVertex;
	NiPoint3*							m_pkNormal;
	NiColorA*							m_pkColor;
	NiPoint2*							m_pkTexture;
	NiPointer<NiAdditionalGeometryData> m_spAdditionalGeomData;
	NiGeometryBufferData*				m_pkBuffData;
	Bitfield8							m_ucKeepFlags;
	Bitfield8							m_ucCompressFlags;
	bool								m_bVBLocked;
	bool								m_bVBLockWrite;
	bool								m_bSaveVertexData;

	NIRTTI_ADDRESS(0x11F4884);

	const NiBound& GetBound() const;

	NiPoint3* GetVertices() const;

	NiPoint3* GetNormals() const;

	NiPoint3* GetBinormals() const;

	NiPoint3* GetTangents() const;

	NiColorA* GetColors() const;

	NiPoint2* GetTextures() const;

	uint16_t GetTextureSets() const;
	NiPoint2* GetTextureSet(uint16_t ausSet = 0);

	uint16_t GetVertexCount() const;

	void SetNormalBinormalTangentMethod(NiGeometryData::DataFlags aeNBTMethod);
	NiGeometryData::DataFlags GetNormalBinormalTangentMethod() const;

	void SetKeepFlags(uint32_t aeFlags);
	void SetCompressFlags(uint32_t aeFlags);

	NiGeometryData::Consistency GetConsistency() const;
	void SetConsistency(Consistency aeConsistency);

	bool LockPackedVertexData(bool abWriteAccess = true);
	void UnlockPackedVertexData();

	NiAdditionalGeometryData* GetAdditionalGeomData() const;
	void SetAdditionalGeomData(NiAdditionalGeometryData* apData);

	void MarkAsChanged(uint32_t auiFlags);
	void ClearRevisionID();

	void Replace(uint16_t ausVertices, NiPoint3* apVertex, NiPoint3* apNormal, NiColorA* apColor, NiPoint2* apTexture, uint16_t ausNumTextureSets, NiGeometryData::DataFlags aeNBTMethod);
	void ReplaceData(uint16_t ausVertices, NiPoint3* apVertex, NiPoint3* apNormal, NiColorA* apColor, NiPoint2* apTexture, uint16_t ausNumTextureSets, NiGeometryData::DataFlags aeNBTMethod);
};

ASSERT_SIZE(NiGeometryData, 0x40);