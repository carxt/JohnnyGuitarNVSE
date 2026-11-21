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

	int32_t Load(BGSSaveLoadFile* apFile);
	void LoadData(char* apData, uint32_t auiSize);

	template <typename T>
	void LoadData(T* apData) {
		LoadData((char*)apData, sizeof(T));
	}
	
	char* LoadString(char* apText);
};

ASSERT_SIZE(BGSLoadGameBuffer, 0x10);