#include "fn_dial.h"
#include "Bethesda/TESDataHandler.hpp"

#include "JG\DialogueResponseOverride.hpp"
#include "JG\ScriptUtils.hpp"
using namespace ScriptUtils;

enum class ConversationTopicType {
	NONE = -1,
	LINK_FROM = 0,
	LINK_TO,
	FOLLOW_UP,
	COUNT
};


bool Cmd_DialogResponseGetResponseAmount_Execute(COMMAND_ARGS)
{
	TESTopicInfo* dialogResponse = nullptr;
	*result = 0;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &dialogResponse) && dialogResponse && IS_TYPE(dialogResponse, TESTopicInfo))
	{
		*result = DialogueResponseOverride::GetResponseAmount(dialogResponse->GetFormID());
	}
	return true;
}

bool Cmd_SetDialogResponseOverrideValues_Execute(COMMAND_ARGS) {
	TESTopicInfo* dialogResponse = nullptr;
	uint32_t responseNumber = 0;
	int32_t setOrRemove = 0;

	uint32_t responseEmotion = 0;
	int32_t responseEmotionValue = 0;
	uint32_t flags = -1;
	//Init to xMarker
	TESIdleForm* speakerAnim = *(TESIdleForm**)0x11CA244;
	TESIdleForm* listenerAnim = *(TESIdleForm**)0x11CA244;

	if (ExtractArgsEx(EXTRACT_ARGS_EX, &dialogResponse, &responseNumber, &setOrRemove, &responseEmotion, &responseEmotionValue, &speakerAnim, &listenerAnim, &flags) && dialogResponse && IS_TYPE(dialogResponse, TESTopicInfo))
	{
		if (setOrRemove > 0)
		{
			DialogueResponseOverride::Set(dialogResponse->GetFormID(), responseNumber, responseEmotion, responseEmotionValue, speakerAnim, listenerAnim, flags);
		}

		else
		{
			DialogueResponseOverride::Remove(dialogResponse->GetFormID(), responseNumber);
		}

	}
	return true;
}


bool Cmd_DialogResponseAddRelatedTopic_Execute(COMMAND_ARGS) {
	TESTopicInfo* pTopicInfo = nullptr;
	TESTopic* pTopic = nullptr;
	ConversationTopicType eType = ConversationTopicType::NONE;
	int32_t iPosition = 0;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &pTopicInfo, &pTopic, &eType, &iPosition) && pTopicInfo && IS_TYPE(pTopicInfo, TESTopicInfo) && InRange(eType)) {
		if (!pTopicInfo->GetConversationData())
			pTopicInfo->SetConversationData(nullptr);

		TESConversationData* pConvData = pTopicInfo->GetConversationData();
		switch (eType) {
			case ConversationTopicType::LINK_FROM:
				pConvData->GetLinkFrom()->AddAt(iPosition, pTopic);
				break;
			case ConversationTopicType::LINK_TO:
				pConvData->GetLinkTo()->AddAt(iPosition, pTopic);
				break;
			case ConversationTopicType::FOLLOW_UP:
				pConvData->GetFollowUp()->AddAt(iPosition, pTopic);
				break;
		}
	}
	return true;
}

bool Cmd_DialogResponseRelatedGetAll_Execute(COMMAND_ARGS) {
	TESTopicInfo* pTopicInfo = nullptr;
	ConversationTopicType eType = ConversationTopicType::NONE;
	NVSEArrayVar* pArray = g_arrInterface->CreateArray(nullptr, 0, scriptObj);

	if (ExtractArgsEx(EXTRACT_ARGS_EX, &pTopicInfo, &eType) && pTopicInfo && IS_TYPE(pTopicInfo, TESTopicInfo) && InRange(eType)) {
		TESConversationData* pConvData = pTopicInfo->GetConversationData();
		if (pConvData) {
			auto addToArray = [pArray](BSSimpleList<TESTopic*>* apIter) {
				TESTopic* pTopic = apIter->GetItem();
				if (pTopic)
					g_arrInterface->AppendElement(pArray, NVSEArrayElement(pTopic));
			};
			switch (eType) {
				case ConversationTopicType::LINK_FROM:
					pConvData->GetLinkFrom()->ForEach(addToArray);
					break;
				case ConversationTopicType::LINK_TO:
					pConvData->GetLinkTo()->ForEach(addToArray);
					break;
				case ConversationTopicType::FOLLOW_UP:
					pConvData->GetFollowUp()->ForEach(addToArray);
					break;
			}
		}
	}
	g_arrInterface->AssignCommandResult(pArray, result);
	return true;

}

SPEC_NOINLINE bool Cmd_GetSaidOnce_Eval(COMMAND_ARGS_EVAL) {
	*result = -1;
	TESTopicInfo* pInfo = static_cast<TESTopicInfo*>(arg1);
	if (pInfo && IS_TYPE(pInfo, TESTopicInfo))
		*result = pInfo->GetSaidOnce();
	return true;
}

bool Cmd_GetSaidOnce_Execute(COMMAND_ARGS) {
	TESTopicInfo* pInfo = nullptr;
	ExtractArgsEx(EXTRACT_ARGS_EX, &pInfo);
	return Cmd_GetSaidOnce_Eval(nullptr, pInfo, nullptr, result);;
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
			pInfo->bSaidOnce = bSaidOnce;
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
				const TopicInfoArray* pTopicInfos = pTargetTopic->GetInfoArray(pQuest);
				if (pTopicInfos) {
					for (uint32_t i = 0; i < pTopicInfos->GetSize(); i++) {
						TESTopicInfo* pTopicInfo = pTopicInfos->GetAt(i);
						if (pTopicInfo)
							g_arrInterface->AppendElement(pStoredInfos, NVSEArrayElement(pTopicInfo));
					}
				}
			}
			else
			{
				auto pIter = pTargetTopic->GetQuestInfoList();
				while (pIter && !pIter->IsEmpty()){
					const QuestInfo* pQuestInfo = pIter->GetItem();
					if (pQuestInfo) {
						auto pTopicInfos = pQuestInfo->GetTopicInfos();
						for (uint32_t i = 0; i < pTopicInfos->GetSize(); i++) {
							TESTopicInfo* pTopicInfo = pTopicInfos->GetAt(i);
							if (pTopicInfo)
								g_arrInterface->AppendElement(pStoredInfos, NVSEArrayElement(pTopicInfo));
						}
					}
					pIter = pIter->GetNext();
				}
			}

		}
		else {
			auto pIter = TESDataHandler::GetSingleton()->kTopics.GetHead();
			while (pIter && !pIter->IsEmpty()) {
				TESTopic* pTopic = pIter->GetItem();
				pIter = pIter->GetNext();
				const TopicInfoArray* pTopicInfos = pTopic->GetInfoArray(pQuest);
				if (pTopicInfos) {
					for (uint32_t i = 0; i < pTopicInfos->GetSize(); i++) {
						TESTopicInfo* pTopicInfo = pTopicInfos->GetAt(i);
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
			*reinterpret_cast<FormID*>(result) = pParentTopic->GetFormID();
		}
	}
	return true;
}