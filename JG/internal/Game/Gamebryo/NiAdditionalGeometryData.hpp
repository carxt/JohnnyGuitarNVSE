#pragma once

#include "NiObject.hpp"

NiSmartPointer(NiAdditionalGeometryData);

class NiAdditionalGeometryData : public NiObject {
public:
	struct _DataType {
		enum Type : uint32_t {
			INVALID	= 0,
			FLOAT1	= 1,
			FLOAT2	= 2,
			FLOAT3	= 3,
			FLOAT4	= 4,
			LONG1	= 5,
			LONG2	= 6,
			LONG3	= 7,
			LONG4	= 8,
			ULONG1	= 9,
			ULONG2	= 10,
			ULONG3	= 11,
			ULONG4	= 12,
			SHORT1	= 13,
			SHORT2	= 14,
			SHORT3	= 15,
			SHORT4	= 16,
			USHORT1	= 17,
			USHORT2	= 18,
			USHORT3	= 19,
			USHORT4	= 20,
			BYTE1	= 21,
			BYTE2	= 22,
			BYTE3	= 23,
			BYTE4	= 24,
			UBYTE1	= 25,
			UBYTE2	= 26,
			UBYTE3	= 27,
			UBYTE4	= 28,
			BLEND1	= 29,
			BLEND2	= 30,
			BLEND3	= 31,
			BLEND4	= 32,
			COUNT	= 33,
			CUSTOM	= 34,
		};
	};
	using DataType = _DataType::Type;

	class NiAGDDataStream {
	public:
		Bitfield8	m_ucFlags;
		DataType	m_eType;
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

	bool GetDataStream(uint32_t auiStreamIndex, uint8_t*& apData, DataType& arType, uint16_t& arCount, uint32_t& arTotalSize, uint32_t& arUnitSize, uint32_t& arStride) const;
	bool SetDataStream(uint32_t auiStreamIndex, uint32_t auiBlockIndex, uint32_t auiBlockOffset, DataType aeType, uint16_t ausCount, uint32_t auiUnitSize, uint32_t auiStride);
};

ASSERT_SIZE(NiAdditionalGeometryData, 0x2C)