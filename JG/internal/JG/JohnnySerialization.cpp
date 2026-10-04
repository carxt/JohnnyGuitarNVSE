#include "JohnnySerialization.hpp"
#include <JG/ExtraMiscStats.hpp>
#include <JG/LandRemapping.hpp>

#include "Shared/Utils/DebugLog.hpp"

namespace JohnnySerialization {

	bool		(__cdecl* _WriteRecord)(uint32_t type, uint32_t version, const void* buffer, uint32_t length);
	bool		(__cdecl* _WriteRecordData)(const void* buffer, uint32_t length);
	bool		(__cdecl* _GetNextRecordInfo)(uint32_t* type, uint32_t* version, uint32_t* length);
	uint32_t	(__cdecl* _ReadRecordData)(void* buffer, uint32_t length);
	bool		(__cdecl* _ResolveFormID)(uint32_t refID, uint32_t* outRefID);
	bool		(__cdecl* _OpenRecord)(uint32_t type, uint32_t version);

	void		(__cdecl* _WriteRecord8)(uint8_t inData);
	void		(__cdecl* _WriteRecord16)(uint16_t inData);
	void		(__cdecl* _WriteRecord32)(uint32_t inData);
	void		(__cdecl* _WriteRecord64)(const void* inData);

	uint8_t		(__cdecl* _ReadRecord8)();
	uint16_t	(__cdecl* _ReadRecord16)();
	uint32_t	(__cdecl* _ReadRecord32)();
	void		(__cdecl* _ReadRecord64)(void* outData);

#define SERIALIZATION_VERSION 1

	enum RecordIDs {
		kRecordID_MiscStats = 'JGMS',
		kRecordID_LandRemap = 'JGLR',
	};

	void SaveGameCallback(void*) {
		if (ExtraMiscStats::HasDataToSave()) {
			_OpenRecord(kRecordID_MiscStats, SERIALIZATION_VERSION);
			ExtraMiscStats::SerializeData(_WriteRecordData);
		}
		if (LandRemapping::HasDataToSave()) {
			_OpenRecord(kRecordID_LandRemap, SERIALIZATION_VERSION);
			LandRemapping::SerializeData(_WriteRecordData);
		}
	}

	void LoadGameCallback(void*)
	{
		using namespace ExtraMiscStats;
		uint32_t type, version, length;
		while (_GetNextRecordInfo(&type, &version, &length)) {
			if (version > SERIALIZATION_VERSION) {
				_MESSAGE("NVSE cosave was made with a newer JohnnyGuitar! %04X has version %i Skipping", type, version);
				continue;
			}

			switch (type) {
				case kRecordID_MiscStats: 
				{
					
					ExtraMiscStats::DeserializeData(_ReadRecordData);
					break;
				}
				case kRecordID_LandRemap:
				{
					LandRemapping::DeserializeData(_ReadRecordData);
					break;
				}
				default: {
					break;
				}
			}
		}
	}

	void Init(const NVSEInterface* nvse)
	{
		NVSESerializationInterface* serialization = (NVSESerializationInterface*)nvse->QueryInterface(kInterface_Serialization);
		_WriteRecord = serialization->WriteRecord;
		_WriteRecordData = serialization->WriteRecordData;
		_GetNextRecordInfo = serialization->GetNextRecordInfo;
		_ReadRecordData = serialization->ReadRecordData;
		_ResolveFormID = serialization->ResolveRefID;
		_OpenRecord = serialization->OpenRecord;
		_WriteRecord8 = serialization->WriteRecord8;
		_WriteRecord16 = serialization->WriteRecord16;
		_WriteRecord32 = serialization->WriteRecord32;
		_WriteRecord64 = serialization->WriteRecord64;
		_ReadRecord8 = serialization->ReadRecord8;
		_ReadRecord16 = serialization->ReadRecord16;
		_ReadRecord32 = serialization->ReadRecord32;
		_ReadRecord64 = serialization->ReadRecord64;

		serialization->SetLoadCallback(nvse->GetPluginHandle(), LoadGameCallback);
		serialization->SetSaveCallback(nvse->GetPluginHandle(), SaveGameCallback);
	}

}