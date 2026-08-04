#pragma once

#include "Gamebryo/NiStream.hpp"
#include "Gamebryo/NiTStringMap.hpp"
#include "BSNodeReferences.hpp"

class NiFile;

class BSStream : public NiStream {
public:
	BSStream();
	virtual ~BSStream();

	virtual bool Load3(const char* apFileName, NiFile* apFile);

	NiTStringMap<NiObjectNET*>* pObjectRefMap;
	NiPointer<BSNodeReferences> spNodeReferences;

	static BSStream* Create(BSStream* apThis);
};

ASSERT_SIZE(BSStream, 0x5CC)