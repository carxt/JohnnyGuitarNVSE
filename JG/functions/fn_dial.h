#pragma once
// Functions that operate on dialog
DEFINE_COMMAND_PLUGIN(DialogResponseAddRelatedTopic, , 0, 4, kParams_OneDialogRes_OneTopic_OneInt_OneOptionalInt);
DEFINE_COMMAND_PLUGIN(DialogResponseRelatedGetAll, , 0, 2, kParams_OneForm_OneInt);
DEFINE_COMMAND_PLUGIN(SetDialogResponseOverrideValues, , 0, 8, kParams_OneForm_FourInts_TwoOptionalForms_OneOptionalInt);
DEFINE_COMMAND_PLUGIN(GetSaidOnce, , 0, 1, kParams_OneForm);
DEFINE_COMMAND_PLUGIN(SetSaidOnce, , 0, 3, kParams_OneForm_TwoInts);
DEFINE_COMMAND_PLUGIN(GetTopicInfo, , 0, 2, kParams_GetTopicInfo);
DEFINE_COMMAND_PLUGIN(GetParentTopic, , 0, 1, kParams_OneForm);


enum ResponseRelatedTopicType {
	kRelatedTopicType_LinkFrom = 0,
	kRelatedTopicType_Choice,
	kRelatedTopicType_FollowUp,
};


class TESTopicFinder {
	TESTopic* m_topicToFind;

public:
	TESTopicFinder(TESTopic* topic) : m_topicToFind(topic) {}
	bool Accept(TESTopic* topicCmp) {
		return topicCmp == m_topicToFind;
	}
};






bool Cmd_DialogResponseGetResponseAmount_Execute(COMMAND_ARGS) 
{

	TESTopicInfo* dialogResponse = nullptr;
	*result = 0;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &dialogResponse) && dialogResponse && IS_TYPE(dialogResponse, TESTopicInfo))
	{
		auto it = hk_DialogueTopicResponseManageHook::cachedDialogueInfo.find(dialogResponse->refID);
		if (it != hk_DialogueTopicResponseManageHook::cachedDialogueInfo.end()) 
		{
			*result = it->second.size();
		}
	}
	return true;
}

DialogueEmotionOverride GetDialogueResponse(UInt32 refId, UInt32 responseNumber, DialogueEmotionOverride& newOverride)
{
	TESIdleForm* speakerAnim = *(TESIdleForm**)0x11CA244;
	TESIdleForm* listenerAnim = *(TESIdleForm**)0x11CA244;
	auto it = dialogResponseOverrideMap[refId].find(responseNumber);
	if (it == dialogResponseOverrideMap[refId].end())
	{
		dialogResponseOverrideMap[refId][responseNumber] = DialogueEmotionOverride(INT_MAX, -1, speakerAnim, listenerAnim, -1);

	}
	DialogueEmotionOverride currentOverride = dialogResponseOverrideMap[refId][responseNumber];
	return currentOverride;

}

bool Cmd_SetDialogResponseOverrideValues_Execute(COMMAND_ARGS) {
	TESTopicInfo* dialogResponse = nullptr;
	UInt32 responseNumber = 0;
	SInt32 setOrRemove = 0;

	UInt32 responseEmotion = 0;
	SInt32 responseEmotionValue = 0;
	UInt32 flags = -1;
	//Init to xMarker
	TESIdleForm* speakerAnim = *(TESIdleForm**)0x11CA244;
	TESIdleForm* listenerAnim = *(TESIdleForm**)0x11CA244;

	//Unlike 99.9% of functions in this game, dialog responses use a 1-based index, not a 0-based index.
	//This means the first element will be 1, not 0.
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &dialogResponse, &responseNumber, &setOrRemove, &responseEmotion, &responseEmotionValue, &speakerAnim, &listenerAnim, &flags) && dialogResponse && IS_TYPE(dialogResponse, TESTopicInfo))
	{
		if (setOrRemove > 0)
		{
			auto it = dialogResponseOverrideMap[dialogResponse->refID].find(responseNumber);
			//if (it != dialogResponseOverrideMap[dialogResponse->refID].end())
			if (false)
			{

				it->second.m_emotionType = (it->second.m_emotionType <= hk_DialogueTopicResponseManageHook::kEmotionMax) ? responseEmotion : it->second.m_emotionType;
				it->second.m_emotionValue = responseEmotionValue;
			}
			else
			{
				dialogResponseOverrideMap[dialogResponse->refID][responseNumber] = DialogueEmotionOverride(responseEmotion, responseEmotionValue, speakerAnim, listenerAnim, flags);
			}
		}

		else
		{
			auto it = dialogResponseOverrideMap.find(dialogResponse->refID);
			if (it != dialogResponseOverrideMap.end())
			{
				it->second.erase(responseNumber);
				if (it->second.size() < 1)
				{
					dialogResponseOverrideMap.erase(dialogResponse->refID);
				}
			}
		}

	}
	return true;
}




bool Cmd_DialogResponseAddRelatedTopic_Execute(COMMAND_ARGS) {
	TESTopicInfo* dialogResponse = nullptr;
	TESTopic* topic = nullptr;
	UInt32 responseType = -1;
	SInt32 addPosition = 0;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &dialogResponse, &topic, &responseType, &addPosition) && dialogResponse && IS_TYPE(dialogResponse, TESTopicInfo) && responseType >= ResponseRelatedTopicType::kRelatedTopicType_LinkFrom && responseType <= ResponseRelatedTopicType::kRelatedTopicType_FollowUp) {
		if (!dialogResponse->relatedTopics) {
			//initializer for the relatedTopics structure.
			dialogResponse->relatedTopics = ThisCall<TESTopicInfo::RelatedTopics*>(0x061CE40, GameHeapAlloc(sizeof(TESTopicInfo::RelatedTopics)));
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
	UInt32 responseType = -1;
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
	UInt32 bSaidOnce = false;
	UInt32 bSave = true;
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
					for (uint32_t i = 0; i < pTopicInfos->Length(); i++) {
						auto pTopicInfo = pTopicInfos->Get(i);
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
						for (uint32_t i = 0; i < pTopicInfos->Length(); i++) {
							auto pTopicInfo = pTopicInfos->Get(i);
							g_arrInterface->AppendElement(pStoredInfos, NVSEArrayElement(pTopicInfo));
						}
					}
				}
			}

		}
		else {
			auto pTopicHandler = &DataHandler::Get()->topicList;
			for (auto kIter = pTopicHandler->Begin(); !kIter.End(); kIter.Next()) {
				if (*kIter) {
					TESTopic* pTopic = kIter.Get();
					auto pTopicInfos = pTopic->GetTopicInfosForQuest(pQuest);
					if (pTopicInfos) {
						for (uint32_t i = 0; i < pTopicInfos->Length(); i++) {
							auto pTopicInfo = pTopicInfos->Get(i);
							g_arrInterface->AppendElement(pStoredInfos, NVSEArrayElement(pTopicInfo));
						}
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