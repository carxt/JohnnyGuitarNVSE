#pragma once

class TESForm;
class TESObjectREFR;
class Actor;

#ifdef GetForm
#undef GetForm
#endif

#ifdef LoadString
#undef LoadString
#endif

class BGSSaveLoadFile;

class BGSLoadGameBuffer {
public:
	BGSLoadGameBuffer();
	~BGSLoadGameBuffer();

	virtual uint8_t			GetVersion() const;
	virtual TESForm*		GetForm() const;
	virtual TESObjectREFR*	GetReference() const;
	virtual Actor*			GetActor() const;

	char*		pBuffer;
	uint32_t	uiBufferSize;
	uint32_t	uiBufferPosition;
};

ASSERT_SIZE(BGSLoadGameBuffer, 0x10);