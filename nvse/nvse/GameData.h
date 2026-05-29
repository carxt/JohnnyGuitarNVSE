#pragma once

#include "GameForms.h"
#include "GameExtraData.h"
#include "Utilities.h"

#include "Bethesda/TESDataHandler.hpp"
#include "Bethesda/TESFile.hpp"

class TESCaravanDeck;
class MediaSet;
class TESRegionManager;
class BSFile;

struct ChunkAndFormType {
	uint32_t		chunkType;	// ie
	uint32_t		formType;	// ie 0x2A
	const char* formName;	// ie 'NPC_'
};

#if 1
static const uint32_t _TESFile_GetNextChunk = 0x004726B0; // args: none retn: uint32_t subrecordType (third call in TESObjectARMO_LoadForm)
static const uint32_t _TESFile_GetChunkData = 0x00472890;	// args: void* buf, uint32_t bufSize retn: bool readSucceeded (fifth call in TESObjectARMO_LoadForm)
static const uint32_t _TESFile_Read32 = 0x004727F0;	// args: void* buf retn: void (find 'LPER', then next call, still in TESObjectARMO_LoadForm)
static const uint32_t _TESFile_HasMoreSubrecords = 0x004726F0;	// Last call before "looping" to GetNextChunk in TESObjectARMO_LoadForm.
static const uint32_t _TESFile_InitializeForm = 0x00472F60;	// args: TESForm* retn: void (second call in TESObjectARMO_LoadForm)

// addresses of static TESFile members holding type info about currently loading form
static uint32_t* s_TESFile_CurrentChunkTypeCode = (uint32_t*)0x011C54F4;
static uint32_t* s_TESFile_CurrentFormTypeEnum = (uint32_t*)0x011C54F0;
// in last call (SetStaticFieldsAndGetFormTypeEnum) of first call (TESFile__GetFormInfoTypeID) from _TESFile_InitializeForm
		//		s_TESFile_CurrentChunkTypeCode is first cmp
		//		s_TESFile_CurrentChunkTypeEnum is next mov
static const ChunkAndFormType* s_TESFile_ChunkAndFormTypes = (const ChunkAndFormType*)0x01187008;	// Array used in the loop in SetStaticFieldsAndGetFormTypeEnum, starts under dd offset aNone

static uint8_t** g_CreatedObjectData = (uint8_t**)0x011C54CC;	// pointer to FormInfo + form data, filled out by TESForm::SaveForm()
static uint32_t* g_CreatedObjectSize = (uint32_t*)0x011C54D0;
// in first call (Form_startSaveForm) in TESObjectARMO__SaveForm:
//		g_CreatedObjectSize is set to 18h
//		g_CreatedObjectData is set to the eax result of the next call
#elif EDITOR
#else
#error
#endif