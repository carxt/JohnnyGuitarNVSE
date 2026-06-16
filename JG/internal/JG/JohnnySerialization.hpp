#pragma once
#include <PluginAPI.h>

namespace JohnnySerialization {

	extern bool (*_WriteRecord)(uint32_t type, uint32_t version, const void* buffer, uint32_t length);
	extern bool (*_WriteRecordData)(const void* buffer, uint32_t length);
	extern bool (*_GetNextRecordInfo)(uint32_t* type, uint32_t* version, uint32_t* length);
	extern uint32_t(*_ReadRecordData)(void* buffer, uint32_t length);
	extern bool (*_ResolveFormID)(uint32_t refID, uint32_t* outRefID);
	extern bool (*_OpenRecord)(uint32_t type, uint32_t version);

	void Init(const NVSEInterface* nvse);
}
