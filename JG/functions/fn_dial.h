#pragma once
// Functions that operate on dialog
DEFINE_COMMAND_PLUGIN(DialogResponseAddRelatedTopic, , 0, 4, kParams_OneDialogRes_OneTopic_OneInt_OneOptionalInt);
DEFINE_COMMAND_PLUGIN(DialogResponseRelatedGetAll, , 0, 4, kParams_OneForm_OneInt);
DEFINE_COMMAND_PLUGIN(SetDialogResponseOverrideValues, , 0, 5, kParams_OneForm_FourInts);


/*DEFINE_CMD_ALT_COND_PLUGIN(DialogResponseHasChoice, , 0, 2, kParams_OneForm_OneTopic);
DEFINE_CMD_ALT_COND_PLUGIN(DialogResponseHasLinkFrom, , 0, 2, kParams_OneForm_OneTopic);
DEFINE_CMD_ALT_COND_PLUGIN(DialogResponseHasFollowUp, , 0, 2, kParams_OneForm_OneTopic);
*/



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

	TESTopicInfo* dialogResponse = NULL;
	*result = 0;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &dialogResponse) && IS_TYPE(dialogResponse, TESTopicInfo))
	{
		auto it = hk_DialogueTopicResponseManageHook::cachedDialogueInfo.find(dialogResponse->refID);
		if (it != hk_DialogueTopicResponseManageHook::cachedDialogueInfo.end()) 
		{
			*result = it->second.size();
		}
	}
	return true;
}






bool Cmd_SetDialogResponseOverrideValues_Execute(COMMAND_ARGS) {
	TESTopicInfo* dialogResponse = NULL;
	UInt32 responseNumber = 0;
	SInt32 setOrRemove = 0;
	UInt32 responseEmotion = 0;
	SInt32 responseEmotionValue = 0;
	//Init to xMarker
	TESIdleForm* speakerAnim = *(TESIdleForm**)0x11CA244;
	TESIdleForm* listenerAnim = *(TESIdleForm**)0x11CA244;

	//Unlike 99.9% of functions in this game, dialog responses use a 1-based index, not a 0-based index.
	//This means the first element will be 1, not 0.
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &dialogResponse, &responseNumber, &setOrRemove, &responseEmotion, &responseEmotionValue, &speakerAnim, &listenerAnim) && IS_TYPE(dialogResponse, TESTopicInfo))
	{
		if (setOrRemove > 0)
		{
			dialogResponseOverrideMap[dialogResponse->refID][responseNumber] = DialogueEmotionOverride((int) responseEmotion, (int)responseEmotionValue, speakerAnim, listenerAnim);
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
	TESTopicInfo* dialogResponse = NULL;
	TESTopic* topic = NULL;
	UInt32 responseType = -1;
	SInt32 addPosition = 0;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &dialogResponse, &topic, &responseType, &addPosition) && IS_TYPE(dialogResponse, TESTopicInfo) && responseType >= ResponseRelatedTopicType::kRelatedTopicType_LinkFrom && responseType <= ResponseRelatedTopicType::kRelatedTopicType_FollowUp) {
		if (!dialogResponse->relatedTopics) {
			//initializer for the relatedTopics structure.
			dialogResponse->relatedTopics = ThisStdCall<TESTopicInfo::RelatedTopics*>(0x061CE40, GameHeapAlloc(sizeof(TESTopicInfo::RelatedTopics)));
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
	TESTopicInfo* dialogResponse = NULL;
	UInt32 responseType = -1;
	NVSEArrayVar* topicArr = g_arrInterface->CreateArray(NULL, 0, scriptObj);

	if (ExtractArgsEx(EXTRACT_ARGS_EX, &dialogResponse, &responseType) && IS_TYPE(dialogResponse, TESTopicInfo) && responseType >= ResponseRelatedTopicType::kRelatedTopicType_LinkFrom && responseType <= ResponseRelatedTopicType::kRelatedTopicType_FollowUp) {
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


