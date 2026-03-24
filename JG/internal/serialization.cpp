#include "serialization.h"
#include <JG/ExtraMiscStats.hpp>

namespace Serialization {

	bool (*_WriteRecord)(uint32_t type, uint32_t version, const void* buffer, uint32_t length);
	bool (*_WriteRecordData)(const void* buffer, uint32_t length);
	bool (*_GetNextRecordInfo)(uint32_t* type, uint32_t* version, uint32_t* length);
	uint32_t(*_ReadRecordData)(void* buffer, uint32_t length);
	bool (*_ResolveRefID)(uint32_t refID, uint32_t* outRefID);
	bool (*_OpenRecord)(uint32_t type, uint32_t version);

	#define SERIALIZATION_VERSION 1

	enum RecordIDs
	{
		kRecordID_MiscStats = 'JGMS',
	};

	void SaveGameCallback(void*)
	{
		if (ExtraMiscStats::HasDataToSave())
		{
			_OpenRecord(kRecordID_MiscStats, SERIALIZATION_VERSION);
			ExtraMiscStats::SerializeData(_WriteRecordData);
		}
	}

	void LoadGameCallback(void*)
	{
		using namespace ExtraMiscStats;
		uint32_t type, version, length;
		while (_GetNextRecordInfo(&type, &version, &length))
		{
			switch (type)
			{
				case kRecordID_MiscStats: {
					ExtraMiscStats::DeserializeData(_ReadRecordData);
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
		_ResolveRefID = serialization->ResolveRefID;
		_OpenRecord = serialization->OpenRecord;
		serialization->SetLoadCallback(nvse->GetPluginHandle(), LoadGameCallback);
		serialization->SetSaveCallback(nvse->GetPluginHandle(), SaveGameCallback);
	}

}