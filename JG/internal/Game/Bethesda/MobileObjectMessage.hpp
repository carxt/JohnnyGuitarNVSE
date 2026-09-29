#pragma once

class MobileObject;

class MobileObjectMessage {
public:
	MobileObjectMessage();
	MobileObjectMessage(MobileObject* apObject);
	MobileObjectMessage(uint32_t auiObjectCount);
	~MobileObjectMessage();

	enum Type {
		START	= 0,
		EXECUTE = 1,
		END		= 2
	};

	uint32_t		eType;
	uint32_t		uiObjectCount;
	MobileObject*	pObject;
};

ASSERT_SIZE(MobileObjectMessage, 0xC);