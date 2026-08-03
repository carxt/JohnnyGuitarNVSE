#pragma once

class NiBinaryStream {
public:
	using Read_t  = uint32_t(__cdecl*)(NiBinaryStream* apThis, void* apBuffer, uint32_t auiBytes, uint32_t* apComponentSizes, uint32_t auiComponentCount);
	using Write_t = uint32_t(__cdecl*)(NiBinaryStream* apThis, const void* apBuffer, uint32_t auiBytes, uint32_t* apComponentSizes, uint32_t auiComponentCount);

	NiBinaryStream();
	virtual ~NiBinaryStream();
	virtual bool		FileIsGood();
	virtual void		Seek(int32_t aiNumBytes);
	virtual uint32_t	GetPosition();
	virtual void		SetEndianSwap(bool abDoSwap);

	uint32_t	m_uiAbsoluteCurrentPos;
	Read_t		m_pfnRead;
	Write_t		m_pfnWrite;

	uint32_t Read(void* apBuffer, uint32_t auiBytes);
	uint32_t Write(const void* apBuffer, uint32_t auiBytes);

	uint32_t BinaryRead(void* apBuffer, uint32_t auiTotalBytes, uint32_t* apComponentSizes, uint32_t auiComponentCount);
	uint32_t BinaryWrite(const void* apBuffer, uint32_t auiTotalBytes, uint32_t* apComponentSizes, uint32_t auiComponentCount);

	static void DoByteSwap(void* apData, uint32_t auiBytes, uint32_t* apComponentSizes, uint32_t auiComponentCount);
};

ASSERT_SIZE(NiBinaryStream, 0x10);

template <class T>
void NiBinaryStreamLoad(NiBinaryStream& arStream, T* apValue, uint32_t auiCount = 1) {
	uint32_t uiSize = sizeof(T);
	arStream.BinaryRead(apValue, uiSize * auiCount, &uiSize, 1);
}

template <class T>
void NiBinaryStreamSave(NiBinaryStream& arStream, const T* apValue, uint32_t auiCount = 1) {
	uint32_t uiSize = sizeof(T);
	arStream.BinaryWrite(apValue, uiSize * auiCount, &uiSize, 1);
}

template <class T>
void NiStreamLoadBinary(NiBinaryStream& arStream, T& arValue) {
	NiBinaryStreamLoad(arStream, &arValue, 1);
}

template <class T>
void NiStreamLoadBinary(NiBinaryStream& arStream, T* apValue, uint32_t auiCount) {
	NiBinaryStreamLoad(arStream, apValue, auiCount);
}

template <class T>
void NiStreamSaveBinary(NiBinaryStream& arStream, const T& arValue) {
	NiBinaryStreamSave(arStream, &arValue, 1);
}

template <class T>
void NiStreamSaveBinary(NiBinaryStream& arStream, const T* apValue, uint32_t auiCount) {
	NiBinaryStreamSave(arStream, apValue, auiCount);
}