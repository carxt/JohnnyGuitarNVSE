#pragma once

#include "NiObject.hpp"

NiSmartPointer(NiAdditionalGeometryData);

class NiAdditionalGeometryData : public NiObject {
public:
	enum Types : uint32_t {
		AGD_NITYPE_INVALID	= 0,
		AGD_NITYPE_FLOAT1	= 1,
		AGD_NITYPE_FLOAT2	= 2,
		AGD_NITYPE_FLOAT3	= 3,
		AGD_NITYPE_FLOAT4	= 4,
		AGD_NITYPE_LONG1	= 5,
		AGD_NITYPE_LONG2	= 6,
		AGD_NITYPE_LONG3	= 7,
		AGD_NITYPE_LONG4	= 8,
		AGD_NITYPE_ULONG1	= 9,
		AGD_NITYPE_ULONG2	= 10,
		AGD_NITYPE_ULONG3	= 11,
		AGD_NITYPE_ULONG4	= 12,
		AGD_NITYPE_SHORT1	= 13,
		AGD_NITYPE_SHORT2	= 14,
		AGD_NITYPE_SHORT3	= 15,
		AGD_NITYPE_SHORT4	= 16,
		AGD_NITYPE_USHORT1	= 17,
		AGD_NITYPE_USHORT2	= 18,
		AGD_NITYPE_USHORT3	= 19,
		AGD_NITYPE_USHORT4	= 20,
		AGD_NITYPE_BYTE1	= 21,
		AGD_NITYPE_BYTE2	= 22,
		AGD_NITYPE_BYTE3	= 23,
		AGD_NITYPE_BYTE4	= 24,
		AGD_NITYPE_UBYTE1	= 25,
		AGD_NITYPE_UBYTE2	= 26,
		AGD_NITYPE_UBYTE3	= 27,
		AGD_NITYPE_UBYTE4	= 28,
		AGD_NITYPE_BLEND1	= 29,
		AGD_NITYPE_BLEND2	= 30,
		AGD_NITYPE_BLEND3	= 31,
		AGD_NITYPE_BLEND4	= 32,
		AGD_NITYPE_COUNT	= 33,
		AGD_NITYPE_CUSTOM	= 34,
	};

	class NiAGDDataStream {
	public:
		Bitfield8	m_ucFlags;
		uint32_t	m_uiType;
		uint32_t	m_uiUnitSize;
		uint32_t	m_uiTotalSize;
		uint32_t	m_uiStride;
		uint32_t	m_uiBlockIndex;
		uint32_t	m_uiBlockOffset;
	};

	class SPEC_EMPTY_BASES NiAGDDataBlock : public NiMemObject {
	public:
		NiAGDDataBlock();
		virtual ~NiAGDDataBlock();
		virtual void*	AllocateBuffer(uint32_t auiBufferSize);
		virtual void	ProtectBuffer(void* apBuffer, uint32_t auiBufferSize);
		virtual void	UnprotectBuffer(void* apBuffer, uint32_t auiBufferSize);
		virtual void	FreeBuffer(void* apBuffer);

		uint32_t	m_uiDataBlockSize;
		uint8_t*	m_pucDataBlock;
		bool		m_bOwnData;
		bool		m_bBSHeap;
	};

	NiAdditionalGeometryData();
	virtual ~NiAdditionalGeometryData();

	virtual bool			GetVBReady() const;
	virtual NiAGDDataBlock* CreateAGDDataBlock();

	uint32_t							m_uiRevID;
	uint16_t							m_usVertexCount;
	uint32_t							m_uiDataStreamCount;
	NiAGDDataStream*					m_pkDataStreamEntries;
	uint32_t							m_uiD3DStream;
	NiTPrimitiveArray<NiAGDDataBlock*>	m_aDataBlocks;

	CREATE_OBJECT(NiAdditionalGeometryData, 0xA73E20);
	NIRTTI_ADDRESS(0x11F4A30);

	static NiAdditionalGeometryData* Create(uint16_t ausVertCount, uint32_t auiObjectCount);
	static NiAdditionalGeometryData* Create(uint16_t ausVertCount);

	bool SetDataBlock(uint32_t auiIndex, uint8_t* apData, uint32_t auiTotalSize, bool abCopyData);

	void SetDataBlockCount(uint32_t auiCount);
	void SetDataStreamCount(uint32_t auiCount);

	bool GetDataStream(uint32_t auiStreamIndex, uint8_t*& apData, uint32_t& arType, uint16_t& arCount, uint32_t& arTotalSize, uint32_t& arUnitSize, uint32_t& arStride) const;
	bool SetDataStream(uint32_t auiStreamIndex, uint32_t auiBlockIndex, uint32_t auiBlockOffset, Types auiType, uint16_t ausCount, uint32_t auiUnitSize, uint32_t auiStride);
};

ASSERT_SIZE(NiAdditionalGeometryData, 0x2C)