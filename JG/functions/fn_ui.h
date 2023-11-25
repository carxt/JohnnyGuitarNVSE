#pragma once
DEFINE_COMMAND_PLUGIN(SetBipedIconPathAlt, , 0, 3, kParams_OneString_OneInt_OneForm);
DEFINE_COMMAND_PLUGIN(GetWorldSpaceMapTexture, , 0, 1, kParams_OneForm);
DEFINE_COMMAND_PLUGIN(SetWorldSpaceMapTexture, , 0, 2, kParams_OneForm_OneString);
DEFINE_COMMAND_PLUGIN(GetCustomMapMarker, , 0, 0, NULL);
DEFINE_COMMAND_PLUGIN(SetCustomMapMarkerIcon, , 0, 2, kParams_OneForm_OneString);
DEFINE_COMMAND_PLUGIN(QueueCinematicText, , 0, 7, kParams_TwoStrings_OneOptionalString_FourOptionalInts);
DEFINE_COMMAND_PLUGIN(QueueObjectiveText, , 0, 3, kParams_OneString_TwoOptionalInts);
DEFINE_COMMAND_PLUGIN(GetSystemColor, , 0, 1, kParams_OneInt);
DEFINE_COMMAND_PLUGIN(GetSystemColorAlt, , 0, 4, kParams_OneInt_ThreeScriptVars);
DEFINE_COMMAND_ALT_PLUGIN(SetCustomReputationChangeIcon, scrci, , 0, 3, kParams_OneForm_OneInt_OneString);
DEFINE_COMMAND_PLUGIN(GetExtraMiscStat, , 0, 1, kParams_OneString);
DEFINE_COMMAND_PLUGIN(ModExtraMiscStat, , 0, 2, kParams_OneString_OneInt);
DEFINE_COMMAND_PLUGIN(InitExtraMiscStat, , 0, 1, kParams_OneString);
DEFINE_COMMAND_PLUGIN(ShowBarberMenuEx, , 0, 2, kParams_OneInt_OneOptionalForm);



bool Cmd_ShowBarberMenuEx_Execute(COMMAND_ARGS) {
	enum {
		kFlag_WhiteListHair = 1 << 0,
		kFlag_WhiteListBeard,
	};
	BGSListForm* formList = NULL;
	UInt32 flags = 0;
	if (!g_thePlayer) return true;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &flags, &formList)) {
		if (IS_TYPE(formList, BGSListForm)) {
			ListNode<TESForm>* iter = formList->list.Head();

			do {
				TESForm* currData = iter->data;
				if (!currData) continue;
				if (IS_TYPE(currData, TESHair)) {
					haircutSetList.Add(currData->refID);
					continue;
				}
				if (IS_TYPE(currData, BGSHeadPart)) {
					beardSetList.Add(currData->refID);
				}
			} while (iter = iter->next);
		}
		auto playerBase =	reinterpret_cast<TESNPC*>(g_thePlayer->GetActorBase());
		haircutSetList.isWhiteList = bool(flags & kFlag_WhiteListHair);
		if (haircutSetList.isWhiteList) {
			haircutSetList.Add(playerBase->hair->refID);
		}
		else {
			haircutSetList.Remove(playerBase->hair->refID);

		}
		beardSetList.isWhiteList = bool(flags & kFlag_WhiteListBeard);
		if (beardSetList.isWhiteList) {
			for (auto iter = playerBase->headPart.Begin(); !iter.End(); iter.Next()) {
				if (*iter) { beardSetList.Add((*iter)->refID);};
			}
		} else{
			for (auto iter = playerBase->headPart.Begin(); !iter.End(); iter.Next()) {
				if (*iter) { beardSetList.Remove((*iter)->refID); };
			}
		}
		CdeclCall<void>(0x705870, 2);
	}
	return true;
}

bool Cmd_InitExtraMiscStat_Execute(COMMAND_ARGS) {
	char name[MAX_PATH];
	int mod = 0;
	int value;
	constexpr size_t maxMiscStatCount = UINT16_MAX;
	*result = 0;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &name)) {
		std::string sName = name;
		if (availableMiscStats.size() > maxMiscStatCount) {
			TerminateProcess(GetCurrentProcess(), 0xE);
		}
		if (bool(availableMiscStats.count(sName))) return true;
		availableMiscStats.emplace(sName);
		miscStatMap[sName] = mod;
		value = mod;
		// creating/updating menu entry
		*result = 1;
	}
	return true;
}

bool Cmd_ModExtraMiscStat_Execute(COMMAND_ARGS) {
	char name[MAX_PATH];
	int mod;
	int value;
	*result = 0;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &name, &mod)) {
		std::string sName = name;
		if (!bool(availableMiscStats.count(sName))) return true;
		auto it = miscStatMap.find(sName);
		if (it != miscStatMap.end()) {
			it->second += mod;
			value = it->second;
		}
		else {
			miscStatMap[sName] = mod;
			value = mod;
		}
		// creating/updating menu entry
		UpdateMiscStatList(name, value);

		*result = 1;
	}
	return true;
}

bool Cmd_GetExtraMiscStat_Execute(COMMAND_ARGS) {
	char name[MAX_PATH];
	*result = 0;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &name)) {
		std::string sName = name;
		if (!availableMiscStats.count(sName)) return true;
		auto it = miscStatMap.find(sName);
		if (it != miscStatMap.end()) *result = it->second;
		if (IsConsoleMode()) Console_Print("GetExtraMiscStat \"%s\": %.f", name, *result);
	}
	return true;
}
bool Cmd_SetCustomReputationChangeIcon_Execute(COMMAND_ARGS) {
	*result = 0;
	TESReputation* rep;
	UInt32 tierID = 0;
	char path[MAX_PATH];
	if (!(ExtractArgsEx(EXTRACT_ARGS_EX, &rep, &tierID, &path) && IS_TYPE(rep, TESReputation) && tierID >= 1 && tierID <= 4)) return true;
	auto pos = factionRepIcons.find(rep->refID);
	char* pathCopy = new char[strlen(path) + 1];
	strcpy(pathCopy, path);

	if (pos != factionRepIcons.end()) {
		if (*pos->second[tierID - 1]) delete[] pos->second[tierID - 1];
		pos->second[tierID - 1] = pathCopy;
	}
	else {
		std::vector<char*> v{ "", "", "", "" };
		v[tierID - 1] = pathCopy;
		factionRepIcons.insert(std::pair<UInt32, std::vector<char*>>(rep->refID, v));
	}
	*result = 1;
	return true;
}

bool Cmd_GetSystemColorAlt_Execute(COMMAND_ARGS) {
	*result = 0;
	ScriptVar* rOut, * gOut, * bOut;
	UInt32 type;
	UInt8 color[3] = { 0, 0, 0 };
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &type, &rOut, &gOut, &bOut) && type > 0 && type <= 5) {
		SystemColorManager* colorMgr = SystemColorManager::GetSingleton();
		UInt32 color = (colorMgr->GetColor(type) >> 0x8);
		bOut->data = color & 0xFF;
		gOut->data = (color >> 8) & 0xFF;
		rOut->data = (color >> 16) & 0xFF;
		if (IsConsoleMode()) Console_Print("GetSystemColor %d >> %d %d %d", type, rOut->data, gOut->data, bOut->data);
	}
	return true;
}
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

bool Cmd_QueueObjectiveText_Execute(COMMAND_ARGS) {
	char text[MAX_PATH];
	UInt32 isCompleted, allowDisplayMultiple;
	*result = 0;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &text, &isCompleted, &allowDisplayMultiple)) {
		CdeclCall(0x77A5B0, text, isCompleted, allowDisplayMultiple == 0);
		*result = 1;
	}
	return true;
};

bool Cmd_QueueCinematicText_Execute(COMMAND_ARGS) {
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
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &title, &subtitle, &soundEdid, &queuePriority, &justification, &titleFont, &subTitleFont)) {
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
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &newPath, &isFemale, &form)) {
		TESBipedModelForm* bipedModel = DYNAMIC_CAST(form, TESForm, TESBipedModelForm);
		if (bipedModel) {
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
	if (IS_TYPE(form, BGSListForm)) {
		ListNode<TESForm>* iterator = ((BGSListForm*)form)->list.Head();
		while (iterator) {
			TESObjectREFR* ref = (TESObjectREFR*)(iterator->data);
			if (ref->GetIsReference() && ref->IsMapMarker() && GetExtraType(ref->extraDataList, MapMarker)) {
				SetCustomMapMarker(ref, iconPath);
			}
			iterator = iterator->next;
		}
	}
	else {
		SetCustomMapMarker(form, iconPath);
	}
	if (IsConsoleMode()) Console_Print("SetCustomMapMarkerIcon >> %u, %s", form->refID, iconPath);
	return true;
}
