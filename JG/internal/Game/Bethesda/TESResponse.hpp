#pragma once

#include "BSStringT.hpp"
#include "BSEnums.hpp"

class TESTopic;
class TESSound;
class TESQuest;
class TESIdleForm;
class TESTopicInfo;
class TESObjectREFR;

class TESResponse {
public:
	struct Data {
		DIALOGUE_EMOTION	eEmotionType;
		uint32_t			uiEmotionValue;
		TESTopic*			pTopic;
		uint8_t				ucResponseID;
		TESSound*			pVoiceSound;
		bool				bUseEmotion;
	};

	Data			kData;
	BSString		strResponseText;
	TESIdleForm*	pSpeakerIdle;
	TESIdleForm*	pListenerIdle;
	TESResponse*	pNext;

	const Data* GetData() const;
	Data* GetData();

	DIALOGUE_EMOTION GetEmotion() const;
	void SetEmotion(DIALOGUE_EMOTION aeEmotion);

	uint32_t GetEmotionValue() const;
	void SetEmotionValue(uint32_t auiValue);

	uint8_t GetResponseID() const;
	void SetResponseID(uint8_t aucID);

	TESSound* GetVoiceSound() const;
	void SetVoiceSound(TESSound* apSound);

	bool GetUseEmotion() const;
	void SetUseEmotion(bool abVal);

	const char* GetResponseText() const;
	uint32_t GetResponseTextLength() const;
	void SetResponseText(const char* apText);

	TESIdleForm* GetSpeakerIdle() const;
	void SetSpeakerIdle(TESIdleForm* apIdle);

	TESIdleForm* GetListenerIdle() const;
	void GetListenerIdle(TESIdleForm* apIdle);

	TESResponse* GetNext() const;

	void AddTail(TESResponse* apResponse);

	uint32_t GetListCount() const;

	bool GetAudioFullPath(const TESObjectREFR* apSpeaker, const TESQuest* apQuest, const TESTopic* apOwnerTopic, const TESTopicInfo* apOwnerInfo, BSString& arDest) const;
	void GetAudioFilename(const TESQuest* apQuest, const TESTopic* apTopic, const TESTopicInfo* apOwnerInfo, BSString& arDest) const;

	static void GetAudioQuestTopicCombined(const TESQuest* apQuest, const TESTopic* apTopic, char* apOutBuffer, uint32_t auiBufferSize);
};

class ResponseListWrapper {
public:
	ResponseListWrapper();
	~ResponseListWrapper();

	TESResponse* pHead;

	uint32_t GetListCount() const;

	void AddTail(TESResponse* apResponse);

	void CopyResponseList(TESResponse* apHead);

	void ClearResponseList();
};

ASSERT_SIZE(TESResponse, 0x2C);