#pragma once

#include "NiBinaryStream.hpp"
#include "NiCriticalSection.hpp"
#include "NiFixedString.hpp"
#include "NiObject.hpp"
#include "NiObjectGroup.hpp"
#include "NiSearchPath.hpp"
#include "NiTPrimitiveArray.hpp"
#include "NiTLargeObjectArray.hpp"
#include "NiTLargePrimitiveArray.hpp"
#include "NiTPointerMap.hpp"
#include "NiTPrimitiveSet.hpp"
#include "NiProcessorAffinity.hpp"

class BackgroundLoadProcedure;
class NiTexturePalette;
class NiThread;

struct BSStreamHeader {
	uint32_t	uiVersion;
	char		cAuthor[64];
	char		cProcessScript[64];
	char		cExportScript[64];
};

class NiStream {
public:
	NiStream();

	enum ErrorMessages {
		STREAM_OKAY			= 0,
		FILE_NOT_LOADED		= 1,
		NOT_NIF_FILE		= 2,
		OLDER_VERSION		= 3,
		LATER_VERSION		= 4,
		NO_CREATE_FUNCTION	= 5,
		ENDIAN_MISMATCH		= 6,
	};

	enum ThreadStatus {
		IDLE		= 0,
		LOADING		= 1,
		CANCELLING	= 2,
		PAUSING		= 3,
		PAUSED		= 4,
	};

	virtual				~NiStream();
	virtual bool		Load(NiBinaryStream* apIstr);
	virtual bool		Load1(char* apBuffer, int32_t auiBufferSize);
	virtual bool		Load2(const char* apFileName);
	virtual bool		Save(NiBinaryStream* apOstr);
	virtual bool		Save1(char*& arBuffer, int32_t& arBufferSize);
	virtual bool		Save2(const char* apFileName);
	virtual void		BackgroundLoadOnExit();
	virtual bool		RegisterFixedString(const NiFixedString& arString);
	virtual bool		RegisterSaveObject(NiObject* apObject);
	virtual void		ChangeObject(NiObject* apNewObject);
	virtual uint32_t	GetLinkIDFromObject(const NiObject* apObject);
	virtual void		SaveLinkID(const NiObject* apObject);
	virtual bool		LoadHeader();
	virtual void		SaveHeader();
	virtual bool		LoadStream();
	virtual bool		SaveStream();
	virtual void		RegisterObjects();
	virtual void		LoadTopLevelObjects();
	virtual void		SaveTopLevelObjects();
	virtual bool		LoadObject();
	virtual uint32_t	PreSaveObjectSizeTable();
	virtual bool		SaveObjectSizeTable(uint32_t auiStartOffset);
	virtual bool		LoadObjectSizeTable();

	BSStreamHeader								m_BSStreamHeader;
	NiTPrimitiveArray<NiObjectGroup*>			m_kGroups;
	uint32_t									m_uiNifFileVersion;
	uint32_t									m_uiNifFileUserDefinedVersion;
	char										m_acFileName[260];
	bool										m_bSaveLittleEndian;
	bool										m_bSourceIsLittleEndian;
	NiSearchPath*								m_pkSearchPath;
	NiTLargeObjectArray<NiObjectPtr>			m_kObjects;
	NiTLargePrimitiveArray<uint32_t>			m_kObjectSizes;
	NiTLargeObjectArray<NiObjectPtr>			m_kTopObjects;
	NiTLargeObjectArray<NiFixedString>			m_kFixedStrings;
	NiBinaryStream*								m_pkIstr;
	NiBinaryStream*								m_pkOstr;
	NiTPrimitiveSet<uint32_t>					m_kLinkIDs;
	uint32_t									m_uiLinkIndex;
	NiTPrimitiveSet<uint32_t>					m_kLinkIDBlocks;
	uint32_t									m_uiLinkBlockIndex;
	NiTPointerMap<const NiObject*, uint32_t>	m_kRegisterMap;
	Bitfield16									m_usNiAVObjectFlags;
	Bitfield16									m_usNiTimeControllerFlags;
	Bitfield16									m_usNiPropertyFlags;
	ThreadStatus								m_eBackgroundLoadStatus;
	bool										m_bBackgroundLoadExitStatus;
	uint32_t									m_uiLoad;
	uint32_t									m_uiLink;
	uint32_t									m_uiPostLink;
	NiThread*									m_pkThread;
	BackgroundLoadProcedure*					m_pkBGLoadProc;
	uint32_t									m_ePriority;
	NiProcessorAffinity							m_kAffinity;
	char										m_acLastLoadedRTTI[260];
	ErrorMessages								m_uiLastError;
	char										m_acLastErrorMessage[260];
	char										m_acReferencePath[260];

	static NiStream* Create(NiStream* apThis);

	static void RegisterLoader(const char* apName, void* apFunc);

	NiObject* GetObjectAt(uint32_t auiIndex);
	uint32_t GetObjectCount() const;
	void InsertObject(NiObject* apObject);

	void ReadLinkID();
	uint32_t ReadMultipleLinkIDs();
	NiObject* GetObjectFromLinkID();

	void SaveFixedString(const NiFixedString& arStr);
	void LoadFixedString(NiFixedString& arStr);

	static uint32_t GetVersion(uint32_t auiMajor, uint32_t auiMinor, uint32_t auiPatch, uint32_t auiInternal);
};

ASSERT_SIZE(NiStream, 0x5C4)

template <class T>
inline void NiStreamSaveBinary(NiStream& arStream, const T& arValue) {
	NiBinaryStreamSave(*arStream.m_pkOstr, &arValue);
}

template <class T>
inline void NiStreamSaveBinary(NiStream& arStream, const T* apValue, uint32_t auiCount) {
	NiBinaryStreamSave(*arStream.m_pkOstr, apValue, auiCount);
}

template <class T>
inline void NiStreamSaveBinary(NiStream& arStream, T* apValue, uint32_t auiCount, uint32_t* apComponentSizes, uint32_t auiComponentCount) {
	NiBinaryStreamSave(*arStream.m_pkOstr, apValue, auiCount, apComponentSizes, auiComponentCount);
}

template <class T>
inline void NiStreamLoadBinary(NiStream& arStream, T& arValue) {
	NiBinaryStreamLoad(*arStream.m_pkIstr, &arValue);
}

template <class T>
inline void NiStreamLoadBinary(NiStream& arStream, T* apValue, uint32_t auiCount) {
	NiBinaryStreamLoad(*arStream.m_pkIstr, apValue, auiCount);
}

template <class T>
inline void NiStreamLoadBinary(NiStream& arStream, T* apValue, uint32_t auiCount, uint32_t* apComponentSizes, uint32_t auiComponentCount) {
	NiBinaryStreamLoad(*arStream.m_pkIstr, apValue, auiCount, apComponentSizes, auiComponentCount);
}