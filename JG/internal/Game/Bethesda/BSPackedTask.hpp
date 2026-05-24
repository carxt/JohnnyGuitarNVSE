#pragma once

class BSPackedTask {
public:
	BSPackedTask();
	~BSPackedTask();

	union Data {
		bool		bData;
		char		cDataA[4];
		uint16_t	usDataA[2];
		int32_t		iData;
		float		fData;
		void*		pData;
		uint32_t	uiData;
	};

	Data uData[8];
};

ASSERT_SIZE(BSPackedTask, 0x20);