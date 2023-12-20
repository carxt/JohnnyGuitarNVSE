#pragma once

bool (*_WriteRecord)(UInt32 type, UInt32 version, const void* buffer, UInt32 length);
bool (*_WriteRecordData)(const void* buffer, UInt32 length);
bool (*_GetNextRecordInfo)(UInt32* type, UInt32* version, UInt32* length);
UInt32(*_ReadRecordData)(void* buffer, UInt32 length);
bool (*_ResolveRefID)(UInt32 refID, UInt32* outRefID);
bool (*_OpenRecord)(UInt32 type, UInt32 version);
#define SERIALIZATION_VERSION 1
enum RecordIDs
{
	kRecordID_MiscStats = 'JGMS',
};

void SaveGameCallback(void*)
{
	if (!miscStatMap.empty())
		{
		_OpenRecord(kRecordID_MiscStats, SERIALIZATION_VERSION);
		UInt16 mapLen = miscStatMap.size();
		_WriteRecordData(&mapLen, sizeof(UInt16));
		for (auto it : miscStatMap) {
			UInt16 len = it.first.length();
			_WriteRecordData(&len, sizeof(UInt16));
			_WriteRecordData(it.first.c_str(), it.first.length());
			_WriteRecordData(&it.second, sizeof(int));
		}
		}

	
}



void LoadGameCallback(void*)
{

	UInt32 type, version, length;
	while (_GetNextRecordInfo(&type, &version, &length))
	{
		switch (type)
		{
		case kRecordID_MiscStats: {
			UInt16 mapLen = 0;
			_ReadRecordData(&mapLen, sizeof(UInt16));
			if (mapLen > 0) {
				char buffer[MAX_PATH] = { 0 };
				for (int i = 0; i < mapLen; i++) {
					UInt16 len = 0;
					_ReadRecordData(&len, sizeof(UInt16));
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

	g_statsMenu->miscStatIDList.Filter(ShouldHideStat);
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

