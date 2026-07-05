#include "JohnnySerialization.hpp"
#include <JG/ExtraMiscStats.hpp>
#include <JG/LandRemapping.hpp>

namespace JohnnySerialization {

	bool (*_WriteRecord)(uint32_t type, uint32_t version, const void* buffer, uint32_t length);
	bool (*_WriteRecordData)(const void* buffer, uint32_t length);
	bool (*_GetNextRecordInfo)(uint32_t* type, uint32_t* version, uint32_t* length);
	uint32_t(*_ReadRecordData)(void* buffer, uint32_t length);
	bool (*_ResolveFormID)(uint32_t refID, uint32_t* outRefID);
	bool (*_OpenRecord)(uint32_t type, uint32_t version);

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

	void PreLoadGameCallback(void*) {

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
		serialization->SetPreLoadCallback(nvse->GetPluginHandle(), PreLoadGameCallback);
		serialization->SetLoadCallback(nvse->GetPluginHandle(), LoadGameCallback);
		serialization->SetSaveCallback(nvse->GetPluginHandle(), SaveGameCallback);
	}

}