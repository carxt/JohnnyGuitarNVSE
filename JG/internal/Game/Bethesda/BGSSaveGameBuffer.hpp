#pragma once

class TESForm;
class TESObjectREFR;
class Actor;
class BGSSaveLoadFile;

class BGSSaveGameBuffer {
public:
	virtual TESForm*		GetForm() const;
	virtual TESObjectREFR*	GetReference() const;
	virtual Actor*			GetActor() const;

	char*		pBuffer;
	uint32_t	uiBufferSize;
	uint32_t	uiBufferPosition;
	uint32_t	uiDebugOverhead;

	void SaveData(const void* apData, uint32_t auiSize, uint32_t unused = 0);
	template <typename T>
	void SaveData(const T& aData) {
		SaveData(&aData, sizeof(T));
	}

	void SaveString(const char* apData, uint32_t auiSize);

	void Save(BGSSaveLoadFile* apFile);
};

ASSERT_SIZE(BGSSaveGameBuffer, 0x14);