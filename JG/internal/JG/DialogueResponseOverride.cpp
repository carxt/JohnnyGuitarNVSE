#include "DialogueResponseOverride.hpp"
#include <GameSettings.h>
#include "JohnnyGameSettings.hpp"

namespace DialogueResponseOverride {

	std::unordered_map<FormID, std::map<uint32_t, DialogueEmotionOverride>> overrideMap;
	std::unordered_map<FormID, std::map<uint32_t, DialogueCache>> cachedDialogueInfo;

	static uintptr_t originalTopicInfoLoad = 0x104D5D4;
	DWORD __fastcall hk_TESTopicInfo_Load(TESTopicInfo* topicInfo, void* edx, TESFile* modInfo)
	{
		DWORD retVal = ThisCall<DWORD>(originalTopicInfoLoad, topicInfo, modInfo);
		if (retVal)
		{
			ResponseListWrapper* responseList = ThisCall<ResponseListWrapper*>(0x061E780, topicInfo, NULL);
			for (TESResponse* pIter = responseList->pHead; pIter; pIter = pIter->GetNext()) {
				DialogueCache diaCache = {};
				diaCache.emotionType = pIter->GetEmotion();
				diaCache.emotionValue = pIter->GetEmotionValue();
				diaCache.responseNumber = pIter->GetResponseID();
				diaCache.speakerAnimation = pIter->GetSpeakerIdle() ? pIter->GetSpeakerIdle()->GetFormID() : 0;
				diaCache.listenerAnimation = pIter->GetListenerIdle() ? pIter->GetListenerIdle()->GetFormID() : 0;
				cachedDialogueInfo[topicInfo->GetFormID()][pIter->GetResponseID()] = diaCache;
			}
		}
		return retVal;
	}

	static  DialogueResponse* __fastcall DialogueResponse_Init(DialogueResponse* responseCol,
		void* edx, TESQuest* quest, TESTopic* topic, TESTopicInfo* topicInfo, Actor* speaker, TESResponse* topicInfoResponse)
	{
		if (auto diaCont = overrideMap.find(topicInfo->GetFormID()); diaCont != overrideMap.end())
		{

			Setting* iSTDEmotionVal = (Setting*)0x11CBDF4;
			if (auto diaItem = diaCont->second.find(topicInfoResponse->GetResponseID()); diaItem != diaCont->second.end())
			{
				if (diaItem->second.m_emotionType < kEmotionMax)
				{
					responseCol->emotionType = diaItem->second.m_emotionType;
				}
				if (diaItem->second.m_emotionValue > 0)
				{
					responseCol->emotionValue = diaItem->second.m_emotionValue;

				}
				if ((responseCol->emotionType > 0) && JohnnyGameSettings::iOverrideDialogueEmotionValues.Int() >= 1)
				{
					responseCol->emotionValue = iSTDEmotionVal->Int();
				}

				if (IS_TYPE(diaItem->second.m_speakerAnimation, TESIdleForm) || (diaItem->second.m_speakerAnimation == NULL))
				{
					responseCol->speakerAnimation = diaItem->second.m_speakerAnimation;
				}
				if (IS_TYPE(diaItem->second.m_listenerAnimation, TESIdleForm) || (diaItem->second.m_listenerAnimation == NULL))
				{
					responseCol->listenerAnimation = diaItem->second.m_listenerAnimation;
				}
				if (diaItem->second.m_flags != -1)
				{
					responseCol->flags = diaItem->second.m_flags;

				}
			}

		}


		return responseCol;
	}

	static  __declspec(naked) void  asm_jumpManHook()
	{
		__asm
		{
			mov ecx, eax
			jmp DialogueResponse_Init
		}

	}

	void Install() {
		HookUtils::WriteRelJump(0x083D413, (uintptr_t)asm_jumpManHook);
	}

	DialogueEmotionOverride GetDialogueResponse(FormID refId, uint32_t responseNumber, DialogueEmotionOverride& newOverride)
	{
		TESIdleForm* speakerAnim = *(TESIdleForm**)0x11CA244;
		TESIdleForm* listenerAnim = *(TESIdleForm**)0x11CA244;
		auto it = overrideMap[refId].find(responseNumber);
		if (it == overrideMap[refId].end())
		{
			overrideMap[refId][responseNumber] = DialogueEmotionOverride(INT_MAX, -1, speakerAnim, listenerAnim, -1);

		}
		DialogueEmotionOverride currentOverride = overrideMap[refId][responseNumber];
		return currentOverride;

	}

	void Set(FormID formID, uint32_t responseNumber, uint32_t emotion, int32_t emotionValue, TESIdleForm* speakerAnim, TESIdleForm* listenerAnim, uint32_t flags) 
	{
		auto it = overrideMap[formID].find(responseNumber);
		//if (it != overrideMap[dialogResponse->GetFormID()].end())
		if (false)
		{

			it->second.m_emotionType = (it->second.m_emotionType <= kEmotionMax) ? emotion : it->second.m_emotionType;
			it->second.m_emotionValue = emotionValue;
		}
		else
		{
			overrideMap[formID][responseNumber] = DialogueEmotionOverride(emotion, emotionValue, speakerAnim, listenerAnim, flags);
		}
	}

	void Remove(FormID formID, uint32_t responseNumber)
	{
		auto it = overrideMap.find(formID);
		if (it != overrideMap.end())
		{
			it->second.erase(responseNumber);
			if (it->second.size() < 1)
			{
				overrideMap.erase(formID);
			}
		}
	}

	uint32_t GetResponseAmount(FormID formID) {
		auto it = cachedDialogueInfo.find(formID);
		if (it != cachedDialogueInfo.end())
		{
			return it->second.size();
		}
		return 0;
	}

};