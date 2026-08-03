#include "fn_dial.h"
#ifdef GAME
#include "Bethesda/TESDataHandler.hpp"

#include "JG/DialogueResponseOverride.hpp"
#include "JG/ScriptUtils.hpp"
using namespace ScriptUtils;

enum class ConversationTopicType {
	NONE = -1,
	LINK_FROM = 0,
	LINK_TO,
	FOLLOW_UP,
	COUNT
};

bool Cmd_DialogResponseGetResponseAmount_Execute(COMMAND_ARGS) {
	TESTopicInfo* pTopicInfo = nullptr;
	arResult = 0;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &pTopicInfo) && pTopicInfo && IS_TYPE(pTopicInfo, TESTopicInfo)) {
		arResult = DialogueResponseOverride::GetResponseAmount(pTopicInfo->GetFormID());
	}
	return true;
}

bool Cmd_SetDialogResponseOverrideValues_Execute(COMMAND_ARGS) {
	TESTopicInfo* pTopicInfo = nullptr;
	uint32_t uiResponseID = 0;
	BOOL bAdd = FALSE;
	DIALOGUE_EMOTION eEmotion = DIALOGUE_EMOTION::NEUTRAL;
	uint32_t uiEmotionValue = 0;
	TESIdleForm* pSpeakerAnim	= pXMarker.ReadAs<TESIdleForm*>();
	TESIdleForm* pListenerAnim	= pXMarker.ReadAs<TESIdleForm*>();
	uint32_t uiFlags = -1;

	if (ExtractArgsEx(EXTRACT_ARGS_EX, &pTopicInfo, &uiResponseID, &bAdd, &eEmotion, &uiEmotionValue, &pSpeakerAnim, &pListenerAnim, &uiFlags) && pTopicInfo && IS_TYPE(pTopicInfo, TESTopicInfo)) {
		if (bAdd > 0) {
			DialogueResponseOverride::Set(pTopicInfo->GetFormID(), uiResponseID, eEmotion, uiEmotionValue, pSpeakerAnim, pListenerAnim, uiFlags);
		}
		else {
			DialogueResponseOverride::Remove(pTopicInfo->GetFormID(), uiResponseID);
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
	NVSEArrayVar* pArray = g_arrInterface->CreateArray(nullptr, 0, apScript);

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
	g_arrInterface->AssignCommandResult(pArray, &arResult);
	return true;

}

SPEC_NOINLINE bool Cmd_GetSaidOnce_Eval(COMMAND_ARGS_EVAL) {
	arResult = -1;
	TESTopicInfo* pInfo = static_cast<TESTopicInfo*>(apParam1);
	if (pInfo && IS_TYPE(pInfo, TESTopicInfo))
		arResult = pInfo->GetSaidOnce();
	return true;
}

bool Cmd_GetSaidOnce_Execute(COMMAND_ARGS) {
	TESTopicInfo* pInfo = nullptr;
	ExtractArgsEx(EXTRACT_ARGS_EX, &pInfo);
	return Cmd_GetSaidOnce_Eval(nullptr, pInfo, nullptr, arResult);
}

bool Cmd_SetSaidOnce_Execute(COMMAND_ARGS) {
	arResult = 0;
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
	arResult = 0;
	TESTopic* pTargetTopic = nullptr;
	int32_t iIndex = -1;
	TESQuest* pQuest = nullptr;

	NVSEArrayVar* pStoredInfos = g_arrInterface->CreateArray(nullptr, 0, apScript);
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &pTargetTopic, &pQuest)) {
		if (pQuest && !IS_TYPE(pQuest, TESQuest)) {
			goto FINISH;
		}

		if (pTargetTopic && !IS_TYPE(pTargetTopic, TESTopic)) {
			if (!pQuest) {
				goto FINISH;
			}
			else {
				pTargetTopic = nullptr;
			}
		}

		if (pTargetTopic) {
			if (pQuest) {
				auto pTopicInfos = pTargetTopic->GetTopicInfosForQuest(pQuest);
				if (pTopicInfos) {
					for (uint32_t i = 0; i < pTopicInfos->GetSize(); i++) {
						auto pTopicInfo = pTopicInfos->GetAt(i);
						if (pTopicInfo)
							g_arrInterface->AppendElement(pStoredInfos, NVSEArrayElement(pTopicInfo));
					}
				}
			}
			else {
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
				if (!pTopicInfos)
					continue;

				for (uint32_t i = 0; i < pTopicInfos->GetSize(); i++) {
					auto pTopicInfo = pTopicInfos->GetAt(i);
					if (pTopicInfo)
						g_arrInterface->AppendElement(pStoredInfos, NVSEArrayElement(pTopicInfo));
				}
			}
		}
	}

	FINISH:
	g_arrInterface->AssignCommandResult(pStoredInfos, &arResult);

	return true;
}

bool Cmd_GetParentTopic_Execute(COMMAND_ARGS) {
	arResult = 0;
	TESTopicInfo* pTopicInfo = nullptr;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &pTopicInfo) && pTopicInfo && IS_TYPE(pTopicInfo, TESTopicInfo)) {
		TESTopic* pParentTopic = pTopicInfo->GetParentTopic();
		if (pParentTopic)
			ScriptUtils::SetFormIDResult(arResult, pParentTopic->GetFormID());
	}
	return true;
}
#endif