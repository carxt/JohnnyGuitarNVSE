#pragma once
#include <PluginAPI.h>

namespace JohnnySerialization {

	extern bool		(__cdecl* _WriteRecord)(uint32_t type, uint32_t version, const void* buffer, uint32_t length);
	extern bool		(__cdecl* _WriteRecordData)(const void* buffer, uint32_t length);
	extern bool		(__cdecl* _GetNextRecordInfo)(uint32_t* type, uint32_t* version, uint32_t* length);
	extern uint32_t	(__cdecl* _ReadRecordData)(void* buffer, uint32_t length);
	extern bool		(__cdecl* _ResolveFormID)(uint32_t refID, uint32_t* outRefID);
	extern bool		(__cdecl* _OpenRecord)(uint32_t type, uint32_t version);

	extern void		(__cdecl* _WriteRecord8)(uint8_t inData);
	extern void		(__cdecl* _WriteRecord16)(uint16_t inData);
	extern void		(__cdecl* _WriteRecord32)(uint32_t inData);
	extern void		(__cdecl* _WriteRecord64)(const void* inData);

	extern uint8_t	(__cdecl* _ReadRecord8)();
	extern uint16_t	(__cdecl* _ReadRecord16)();
	extern uint32_t	(__cdecl* _ReadRecord32)();
	extern void		(__cdecl* _ReadRecord64)(void* outData);

	void Init(const NVSEInterface* nvse);
}
