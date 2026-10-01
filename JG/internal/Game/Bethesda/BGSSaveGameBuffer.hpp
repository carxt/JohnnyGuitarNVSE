#pragma once

class TESForm;
class TESObjectREFR;
class Actor;

class BGSSaveGameBuffer {
public:
	virtual TESForm*		GetForm();
	virtual TESObjectREFR*	GetReference();
	virtual Actor*			GetActor();

	char*		pBuffer;
	uint32_t	uiBufferSize;
	uint32_t	uiBufferPosition;
	uint32_t	uiDebugOverhead;
};

ASSERT_SIZE(BGSSaveGameBuffer, 0x14);