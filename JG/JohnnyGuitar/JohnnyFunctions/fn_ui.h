#pragma once
DEFINE_COMMAND_PLUGIN(SetBipedIconPathAlt, , 0, 3, kParamsJohnny_OneString_OneInt_OneForm); 
DEFINE_COMMAND_PLUGIN(GetWorldSpaceMapTexture, , 0, 1, kParams_OneForm);
DEFINE_COMMAND_PLUGIN(SetWorldSpaceMapTexture, , 0, 2, kParamsJohnny_OneForm_OneString);
DEFINE_COMMAND_PLUGIN(GetCustomMapMarker, , 0, 0, NULL);
DEFINE_COMMAND_PLUGIN(SetCustomMapMarkerIcon, , 0, 2, kParamsJohnny_OneForm_OneString);
DEFINE_COMMAND_PLUGIN(QueueCinematicText, , 0, 7, kParamsJohnnyTwoStringsOneOptionalStringFourOptionalInts);
DEFINE_COMMAND_PLUGIN(QueueObjectiveText, , 0, 3, kParamsJohnnyOneStringTwoOptionalInts);

bool Cmd_QueueObjectiveText_Execute(COMMAND_ARGS)
{
	char text[MAX_PATH];
	UInt32 isCompleted, allowDisplayMultiple;
	if (ExtractArgs(EXTRACT_ARGS, &text, &isCompleted, &allowDisplayMultiple))
	{
		CdeclCall(0x77A5B0, text, isCompleted, allowDisplayMultiple == 0);
	}
	return true;
};

bool Cmd_QueueCinematicText_Execute(COMMAND_ARGS)
{
	enum {
		kPriorityAppend = 0,
		kPriorityPrepend,
		kPriorityClearQueueShowNow,
	};
	enum {
		kJustifyLeft = 0,
		kJustifyCenter,
		kJustifyRight
	};

	char title[MAX_PATH], subtitle[MAX_PATH], soundPath[MAX_PATH];
	*soundPath = '\0';
	UInt32 queuePriority = kPriorityAppend;
	UInt32 justification = kJustifyLeft;
	UInt32 titleFont = -1, subTitleFont = -1;
	if (ExtractArgs(EXTRACT_ARGS, &title, &subtitle, &soundPath, &queuePriority, &justification, &titleFont, &subTitleFont))
	{
		if (justification > kJustifyRight) justification = kJustifyRight;

		if (queuePriority == kPriorityClearQueueShowNow) CdeclCall(0x77F500); // HUDMainMenu::HideQuestLocationText

		CdeclCall(0x76B960, title, subtitle, queuePriority == kPriorityAppend, justification, titleFont, subTitleFont, soundPath); // QuestUpdateManager::SetCustomQuestText
	}
	return true;
};

bool Cmd_SetBipedIconPathAlt_Execute(COMMAND_ARGS) {
	UInt32 isFemale = 0;
	TESForm* form = NULL;
	char newPath[MAX_PATH];

	if (ExtractArgs(EXTRACT_ARGS, &newPath, &isFemale, &form))
	{

		TESBipedModelForm* bipedModel = DYNAMIC_CAST(form, TESForm, TESBipedModelForm);
		if (bipedModel)
		{
			bipedModel->icon[isFemale].ddsPath.Set(newPath);
		}
	}

	return true;
}

bool Cmd_GetCustomMapMarker_Execute(COMMAND_ARGS) {
	*result = 0;
	PlayerCharacter* g_thePlayer = PlayerCharacter::GetSingleton();
	TESObjectREFR* markerRef = ThisStdCall<TESObjectREFR*>(0x77A400, g_thePlayer);
	if (markerRef) {
		*(UInt32*)result = markerRef->refID;
	}
	return true;
}

bool Cmd_SetWorldSpaceMapTexture_Execute(COMMAND_ARGS) {
	*result = 0;
	TESWorldSpace* worlspace = NULL;
	char path[MAX_PATH];
	if (ExtractArgs(EXTRACT_ARGS, &worlspace, &path) && IS_TYPE(worlspace, TESWorldSpace)) {
		worlspace->texture.ddsPath.Set(path);
	}
	return true;
}
bool Cmd_GetWorldSpaceMapTexture_Execute(COMMAND_ARGS) {
	*result = 0;
	TESWorldSpace* worlspace = NULL;
	char path[MAX_PATH];
	if (ExtractArgs(EXTRACT_ARGS, &worlspace) && IS_TYPE(worlspace, TESWorldSpace) && (worlspace->texture.ddsPath.m_data)) {
		strcpy(path, worlspace->texture.ddsPath.m_data);
		StrIfc->Assign(PASS_COMMAND_ARGS, path);
		if (IsConsoleMode())
			Console_Print("GetWorldSpaceMapTexture >> %s", path);
	}
	return true;
}

bool Cmd_SetCustomMapMarkerIcon_Execute(COMMAND_ARGS) {
	TESObjectREFR* form;
	char MapMarkerRoute[MAX_PATH];
	if (!ExtractArgs(EXTRACT_ARGS, &form, &MapMarkerRoute) || (!IS_TYPE(form, BGSListForm) && (!form->GetIsReference() || !form->IsMapMarker() || !GetExtraType(form->extraDataList, MapMarker)))) return true;
	if (IS_TYPE(form, BGSListForm))
	{
		ListNode<TESForm>* iterator = ((BGSListForm*)form)->list.Head();
		while (iterator)
		{
			TESObjectREFR* Refer = (TESObjectREFR*)(iterator->data);
			if (Refer->GetIsReference() && Refer->IsMapMarker() && GetExtraType(form->extraDataList, MapMarker))
			{
				DoCustomMapMarker(Refer, MapMarkerRoute);
			}
			iterator = iterator->next;
		}
	}
	else
	{
		DoCustomMapMarker(form, MapMarkerRoute);
	}
	if (IsConsoleMode()) Console_Print("SetCustomMapMarkerIcon >> %u, %s", form->refID, MapMarkerRoute);
	return true;
}