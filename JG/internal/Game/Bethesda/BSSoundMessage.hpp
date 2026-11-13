#pragma once

#include "BSMemObject.hpp"
#include "Gamebryo/NiPoint3.hpp"
#include "Gamebryo/NiRefObject.hpp"
#include "Gamebryo/NiTPointerList.hpp"

class BSSoundMessage {
public:
	BSSoundMessage();
	~BSSoundMessage();

	uint32_t		uiType;
	uint32_t		uiID;
	int32_t			iData;
	void*			pData;
	NiRefObjectPtr	spData;
	union {
		float		fVector[3];
		uint16_t	usCurve[5];
	};

	BSSoundMessage& operator=(const BSSoundMessage& arOther);
};

ASSERT_SIZE(BSSoundMessage, 0x20);

using SoundMessageList = NiTPointerList<BSSoundMessage*>;