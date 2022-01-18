#pragma once
DEFINE_COMMAND_PLUGIN(SetBipedIconPathAlt, , 0, 3, kParams_OneString_OneInt_OneForm);
DEFINE_COMMAND_PLUGIN(GetWorldSpaceMapTexture, , 0, 1, kParams_OneForm);
DEFINE_COMMAND_PLUGIN(SetWorldSpaceMapTexture, , 0, 2, kParams_OneForm_OneString);
DEFINE_COMMAND_PLUGIN(GetCustomMapMarker, , 0, 0, NULL);
DEFINE_COMMAND_PLUGIN(SetCustomMapMarkerIcon, , 0, 2, kParams_OneForm_OneString);
DEFINE_COMMAND_PLUGIN(QueueCinematicText, , 0, 7, kParams_TwoStrings_OneOptionalString_FourOptionalInts);
DEFINE_COMMAND_PLUGIN(QueueObjectiveText, , 0, 3, kParams_OneString_TwoOptionalInts);
DEFINE_COMMAND_PLUGIN(GetSystemColor, , 0, 1, kParams_OneInt);

bool Cmd_GetSystemColor_Execute(COMMAND_ARGS) {
	UInt32 type;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &type) && type > 0 && type <= 5) {
		SystemColorManager* colorMgr = SystemColorManager::GetSingleton();
		UInt32 color = (colorMgr->GetColor(type) >> 0x8);
		*result = color;
		if (IsConsoleMode()) Console_Print("GetSystemColor %d >> 0x%X", type, color);
	}
	return true;
};

bool Cmd_QueueObjectiveText_Execute(COMMAND_ARGS)
{
	char text[MAX_PATH];
	UInt32 isCompleted, allowDisplayMultiple;
	*result = 0;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &text, &isCompleted, &allowDisplayMultiple))
	{
		CdeclCall(0x77A5B0, text, isCompleted, allowDisplayMultiple == 0);
		*result = 1;
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

	char title[MAX_PATH], subtitle[MAX_PATH], soundEdid[MAX_PATH];
	*soundEdid = '\0';
	UInt32 queuePriority = kPriorityAppend;
	UInt32 justification = kJustifyLeft;
	int titleFont = -1, subTitleFont = -1;
	*result = 0;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &title, &subtitle, &soundEdid, &queuePriority, &justification, &titleFont, &subTitleFont))
	{
		if (justification > kJustifyRight) justification = kJustifyRight;

		if (queuePriority == kPriorityClearQueueShowNow) CdeclCall(0x77F500); // HUDMainMenu::HideQuestLocationText

		CdeclCall(0x76B960, title, subtitle, queuePriority == kPriorityAppend, justification, titleFont, subTitleFont, soundEdid); // QuestUpdateManager::SetCustomQuestText
		*result = 1;
	}
	return true;
};

bool Cmd_SetBipedIconPathAlt_Execute(COMMAND_ARGS) {
	UInt32 isFemale = 0;
	TESForm* form = NULL;
	char newPath[MAX_PATH];
	*result = 0;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &newPath, &isFemale, &form))
	{

		TESBipedModelForm* bipedModel = DYNAMIC_CAST(form, TESForm, TESBipedModelForm);
		if (bipedModel)
		{
			bipedModel->icon[isFemale].ddsPath.Set(newPath);
			*result = 1;
		}
	}

	return true;
}

bool Cmd_GetCustomMapMarker_Execute(COMMAND_ARGS) {
	*result = 0;
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
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &worlspace, &path) && IS_TYPE(worlspace, TESWorldSpace)) {
		worlspace->texture.ddsPath.Set(path);
		*result = 1;
	}
	return true;
}
bool Cmd_GetWorldSpaceMapTexture_Execute(COMMAND_ARGS) {
	*result = 0;
	TESWorldSpace* worlspace = NULL;
	char path[MAX_PATH];
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &worlspace) && IS_TYPE(worlspace, TESWorldSpace) && (worlspace->texture.ddsPath.m_data)) {
		strcpy(path, worlspace->texture.ddsPath.m_data);
		g_strInterface->Assign(PASS_COMMAND_ARGS, path);
		if (IsConsoleMode())
			Console_Print("GetWorldSpaceMapTexture >> %s", path);
	}
	return true;
}

bool Cmd_SetCustomMapMarkerIcon_Execute(COMMAND_ARGS) {
	TESObjectREFR* form;
	char iconPath[MAX_PATH];
	if (!ExtractArgsEx(EXTRACT_ARGS_EX, &form, &iconPath) || (!IS_TYPE(form, BGSListForm) && (!form->GetIsReference() || !form->IsMapMarker() || !GetExtraType(form->extraDataList, MapMarker)))) return true;
	if (IS_TYPE(form, BGSListForm))
	{
		ListNode<TESForm>* iterator = ((BGSListForm*)form)->list.Head();
		while (iterator)
		{
			TESObjectREFR* ref = (TESObjectREFR*)(iterator->data);
			if (ref->GetIsReference() && ref->IsMapMarker() && GetExtraType(ref->extraDataList, MapMarker))
			{
				SetCustomMapMarker(ref, iconPath);
			}
			iterator = iterator->next;
		}
	}
	else
	{
		SetCustomMapMarker(form, iconPath);
	}
	if (IsConsoleMode()) Console_Print("SetCustomMapMarkerIcon >> %u, %s", form->refID, iconPath);
	return true;
}