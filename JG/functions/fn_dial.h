#pragma once
// Functions that operate on dialog
DEFINE_COMMAND_PLUGIN(DialogResponseAddRelatedTopic, , 0, 4, kParams_OneDialogRes_OneTopic_OneInt_OneOptionalInt);
DEFINE_COMMAND_PLUGIN(DialogResponseRelatedGetAll, , 0, 4, kParams_OneForm_OneInt);


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

	if (ExtractArgsEx(EXTRACT_ARGS_EX, &dialogResponse, &responseType) && IS_TYPE(dialogResponse, TESTopicInfo)&&responseType >= ResponseRelatedTopicType::kRelatedTopicType_LinkFrom && responseType <= ResponseRelatedTopicType::kRelatedTopicType_FollowUp) {
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


