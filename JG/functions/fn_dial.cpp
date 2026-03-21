#include "fn_dial.h"
#include "JG\DialogueResponseOverride.hpp"
#include <Bethesda/TESDataHandler.hpp>

enum ResponseRelatedTopicType {
	kRelatedTopicType_LinkFrom = 0,
	kRelatedTopicType_Choice,
	kRelatedTopicType_FollowUp,
};

bool Cmd_DialogResponseGetResponseAmount_Execute(COMMAND_ARGS)
{
	using namespace DialogueResponseOverride;
	TESTopicInfo* dialogResponse = nullptr;
	*result = 0;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &dialogResponse) && dialogResponse && IS_TYPE(dialogResponse, TESTopicInfo))
	{
		auto it = cachedDialogueInfo.find(dialogResponse->GetFormID());
		if (it != cachedDialogueInfo.end())
		{
			*result = it->second.size();
		}
	}
	return true;
}

bool Cmd_SetDialogResponseOverrideValues_Execute(COMMAND_ARGS) {
	using namespace DialogueResponseOverride;
	TESTopicInfo* dialogResponse = nullptr;
	uint32_t responseNumber = 0;
	int32_t setOrRemove = 0;

	uint32_t responseEmotion = 0;
	int32_t responseEmotionValue = 0;
	uint32_t flags = -1;
	//Init to xMarker
	TESIdleForm* speakerAnim = *(TESIdleForm**)0x11CA244;
	TESIdleForm* listenerAnim = *(TESIdleForm**)0x11CA244;

	//Unlike 99.9% of functions in this game, dialog responses use a 1-based index, not a 0-based index.
	//This means the first element will be 1, not 0.
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &dialogResponse, &responseNumber, &setOrRemove, &responseEmotion, &responseEmotionValue, &speakerAnim, &listenerAnim, &flags) && dialogResponse && IS_TYPE(dialogResponse, TESTopicInfo))
	{
		if (setOrRemove > 0)
		{
			auto it = overrideMap[dialogResponse->GetFormID()].find(responseNumber);
			//if (it != overrideMap[dialogResponse->GetFormID()].end())
			if (false)
			{

				it->second.m_emotionType = (it->second.m_emotionType <= kEmotionMax) ? responseEmotion : it->second.m_emotionType;
				it->second.m_emotionValue = responseEmotionValue;
			}
			else
			{
				overrideMap[dialogResponse->GetFormID()][responseNumber] = DialogueEmotionOverride(responseEmotion, responseEmotionValue, speakerAnim, listenerAnim, flags);
			}
		}

		else
		{
			auto it = overrideMap.find(dialogResponse->GetFormID());
			if (it != overrideMap.end())
			{
				it->second.erase(responseNumber);
				if (it->second.size() < 1)
				{
					overrideMap.erase(dialogResponse->GetFormID());
				}
			}
		}

	}
	return true;
}


bool Cmd_DialogResponseAddRelatedTopic_Execute(COMMAND_ARGS) {
	TESTopicInfo* dialogResponse = nullptr;
	TESTopic* topic = nullptr;
	uint32_t responseType = -1;
	int32_t addPosition = 0;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &dialogResponse, &topic, &responseType, &addPosition) && dialogResponse && IS_TYPE(dialogResponse, TESTopicInfo) && responseType >= ResponseRelatedTopicType::kRelatedTopicType_LinkFrom && responseType <= ResponseRelatedTopicType::kRelatedTopicType_FollowUp) {
		if (!dialogResponse->relatedTopics) {
			//initializer for the relatedTopics structure.
			dialogResponse->relatedTopics = ThisCall<TESTopicInfo::RelatedTopics*>(0x061CE40, BSMemory::malloc<TESTopicInfo::RelatedTopics>());
		}
		TESTopicInfo::RelatedTopics* relTopics = dialogResponse->relatedTopics;
		switch (responseType) {
		case kRelatedTopicType_LinkFrom:
			relTopics->linkFrom.AddAt(topic, addPosition);
			break;
		case kRelatedTopicType_Choice:
			relTopics->choices.AddAt(topic, addPosition);
			break;
		case kRelatedTopicType_FollowUp:
			relTopics->followUps.AddAt(topic, addPosition);
			break;
		}
	}
	return true;
}

bool Cmd_DialogResponseRelatedGetAll_Execute(COMMAND_ARGS) {
	TESTopicInfo* dialogResponse = nullptr;
	uint32_t responseType = -1;
	NVSEArrayVar* topicArr = g_arrInterface->CreateArray(nullptr, 0, scriptObj);

	if (ExtractArgsEx(EXTRACT_ARGS_EX, &dialogResponse, &responseType) && dialogResponse && IS_TYPE(dialogResponse, TESTopicInfo) && responseType >= ResponseRelatedTopicType::kRelatedTopicType_LinkFrom && responseType <= ResponseRelatedTopicType::kRelatedTopicType_FollowUp) {
		TESTopicInfo::RelatedTopics* relTopics = dialogResponse->relatedTopics;
		if (relTopics) {
			auto addToArray = [topicArr](tList<TESTopic>::Iterator iter) -> void {
				for (; !iter.End(); iter.Next()) {
					g_arrInterface->AppendElement(topicArr, NVSEArrayElement(*iter));
				}
				};
			switch (responseType) {
			case kRelatedTopicType_LinkFrom:
				addToArray(relTopics->linkFrom.Begin());
				break;
			case kRelatedTopicType_Choice:
				addToArray(relTopics->choices.Begin());
				break;
			case kRelatedTopicType_FollowUp:
				addToArray(relTopics->followUps.Begin());
				break;
			}
		}
	}
	g_arrInterface->AssignCommandResult(topicArr, result);
	return true;

}


bool Cmd_GetSaidOnce_Execute(COMMAND_ARGS) {
	*result = -1;
	TESTopicInfo* pInfo = nullptr;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &pInfo) && pInfo && IS_TYPE(pInfo, TESTopicInfo)) {
		*result = pInfo->saidOnce;
	}
	return true;
}

bool Cmd_SetSaidOnce_Execute(COMMAND_ARGS) {
	*result = 0;
	TESTopicInfo* pInfo = nullptr;
	uint32_t bSaidOnce = false;
	uint32_t bSave = true;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &pInfo, &bSaidOnce, &bSave) && pInfo && IS_TYPE(pInfo, TESTopicInfo)) {
		if (bSave) {
			if (bSaidOnce)
				pInfo->SetSaidOnce();
			else
				pInfo->ResetSaidOnceFlags();
		}
		else {
			pInfo->saidOnce = bSaidOnce;
		}
	}
	return true;
}

bool Cmd_GetTopicInfo_Execute(COMMAND_ARGS) {
	*result = 0;
	TESTopic* pTargetTopic = nullptr;
	int32_t iIndex = -1;
	TESQuest* pQuest = nullptr;

	NVSEArrayVar* pStoredInfos = g_arrInterface->CreateArray(nullptr, 0, scriptObj);
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &pTargetTopic, &pQuest)) {

		if (pQuest && !IS_TYPE(pQuest, TESQuest)) //exclude xMarker 
		{

			return true;
		}


		if (pTargetTopic && !IS_TYPE(pTargetTopic, TESTopic))
		{
			if (!pQuest)
			{
				return true;
			}
			else
			{
				pTargetTopic = nullptr;
			}

		}
		if (pTargetTopic) {
			if (pQuest)
			{
				auto pTopicInfos = pTargetTopic->GetTopicInfosForQuest(pQuest);
				if (pTopicInfos) {
					for (uint32_t i = 0; i < pTopicInfos->GetSize(); i++) {
						auto pTopicInfo = pTopicInfos->GetAt(i);
						if (pTopicInfo)
							g_arrInterface->AppendElement(pStoredInfos, NVSEArrayElement(pTopicInfo));
					}
				}
			}
			else
			{
				auto pTargetTopicInfoList = &pTargetTopic->infos;
				for (auto kIter = pTargetTopicInfoList->Begin(); !kIter.End(); kIter.Next()) {
					if (*kIter) {
						auto pTopicInfos = &(*kIter)->infoArray;
						for (uint32_t i = 0; i < pTopicInfos->GetSize(); i++) {
							auto pTopicInfo = pTopicInfos->GetAt(i);
							if (pTopicInfo)
								g_arrInterface->AppendElement(pStoredInfos, NVSEArrayElement(pTopicInfo));
						}
					}
				}
			}

		}
		else {
			auto pIter = TESDataHandler::GetSingleton()->kTopics.GetHead();
			while (pIter && !pIter->IsEmpty()) {
				TESTopic* pTopic = pIter->GetItem();
				pIter = pIter->GetNext();
				auto pTopicInfos = pTopic->GetTopicInfosForQuest(pQuest);
				if (pTopicInfos) {
					for (uint32_t i = 0; i < pTopicInfos->GetSize(); i++) {
						auto pTopicInfo = pTopicInfos->GetAt(i);
						if (pTopicInfo)
							g_arrInterface->AppendElement(pStoredInfos, NVSEArrayElement(pTopicInfo));
					}
				}
			}
		}

	}
	g_arrInterface->AssignCommandResult(pStoredInfos, result);

	return true;
}

bool Cmd_GetParentTopic_Execute(COMMAND_ARGS) {
	*result = 0;
	TESTopicInfo* pTopicInfo = nullptr;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &pTopicInfo) && pTopicInfo && IS_TYPE(pTopicInfo, TESTopicInfo)) {
		TESTopic* pParentTopic = pTopicInfo->pParentTopic;
		if (pParentTopic) {
			*reinterpret_cast<uint32_t*>(result) = pParentTopic->GetFormID();
		}
	}
	return true;
}