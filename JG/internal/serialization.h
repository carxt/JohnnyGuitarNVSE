#pragma once
#include <JG/ExtraMiscStats.hpp>

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
	using namespace ExtraMiscStats;
	if (!miscStatMap.empty())
		{
		_OpenRecord(kRecordID_MiscStats, SERIALIZATION_VERSION);
		uint16_t mapLen = static_cast<uint16_t>(miscStatMap.size());
		_WriteRecordData(&mapLen, sizeof(uint16_t));
		for (auto& it : miscStatMap) {
			uint16_t len = static_cast<uint16_t>(it.first.length());
			_WriteRecordData(&len, sizeof(uint16_t));
			_WriteRecordData(it.first.c_str(), it.first.length());
			_WriteRecordData(&it.second, sizeof(int));
		}
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
			uint16_t mapLen = 0;
			_ReadRecordData(&mapLen, sizeof(uint16_t));
			if (mapLen > 0) {
				char buffer[MAX_PATH] = { 0 };
				for (int i = 0; i < mapLen; i++) {
					uint16_t len = 0;
					_ReadRecordData(&len, sizeof(uint16_t));
					_ReadRecordData(buffer, len);
					buffer[len] = 0;
					std::string sName = std::string(buffer);
					int value = 0;
					_ReadRecordData(&value, sizeof(int));
					auto statIter = miscStatMap.find(sName);
					if (statIter == miscStatMap.end()) { continue; }
					miscStatMap[sName] = value;
					UpdateMiscStatList(buffer, value);
					
				}
			}
		}
		default:
			break;
		}
	}

	StatsMenu::Get()->miscStatIDList.Filter(ShouldHideStat);
}

	void SerializationInit(const NVSEInterface* nvse)
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

