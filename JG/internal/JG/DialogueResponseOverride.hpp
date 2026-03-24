#pragma once
#include "GameForms.h"
#include <unordered_map>
#include <map>


namespace DialogueResponseOverride {


	enum kDialogEmotionType
	{
		kEmotionNeutral,
		kEmotionAnger,
		kEmotionDisgust,
		kEmotionFear,
		kEmotionSad,
		kEmotionHappy,
		kEmotionSurprise,
		kEmotionPained,
		kEmotionMax
	};
	struct DialogueResponse
	{
		BSString responseText;
		uint32_t emotionType;
		uint32_t emotionValue;
		BSString voiceFilePath;
		TESIdleForm* speakerAnimation;
		TESIdleForm* listenerAnimation;
		uint32_t sound;
		uint8_t flags;
		uint8_t pad25[3];
		uint32_t responseNumber;
	};

	struct DialogueCache
	{
		uint32_t emotionType;
		uint32_t emotionValue;
		uint32_t responseNumber;
		uint32_t speakerAnimation;
		uint32_t listenerAnimation;
	};

	class DialogueEmotionOverride
	{
	public:

		DialogueEmotionOverride() {};
		virtual ~DialogueEmotionOverride() {}

		unsigned int m_emotionType;
		int m_emotionValue;
		TESIdleForm* m_speakerAnimation;
		TESIdleForm* m_listenerAnimation;
		unsigned int m_flags;

		DialogueEmotionOverride(int emotionType, int emotionValue, TESIdleForm* speakerAnim, TESIdleForm* listenAnim, unsigned int flags) :
			m_emotionType(emotionType), m_emotionValue(emotionValue), m_speakerAnimation(speakerAnim), m_listenerAnimation(listenAnim), m_flags(flags)
		{

		}

	};

	void Install();
	void Set(uint32_t formID, uint32_t responseNumber, uint32_t emotion, int32_t emotionValue, TESIdleForm* speakerAnim, TESIdleForm* listenerAnim, uint32_t flags);
	void Remove(uint32_t formID, uint32_t responseNumber);
	uint32_t GetResponseAmount(uint32_t formID);
};