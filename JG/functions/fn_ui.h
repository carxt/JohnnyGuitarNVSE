#pragma once
DEFINE_COMMAND_PLUGIN(SetBipedIconPathAlt, , false, kParams_OneString_OneInt_OneForm);
DEFINE_COMMAND_PLUGIN(GetWorldSpaceMapTexture, , false, kParams_OneForm);
DEFINE_COMMAND_PLUGIN(SetWorldSpaceMapTexture, , false, kParams_OneForm_OneString);
DEFINE_COMMAND_PLUGIN(GetCustomMapMarker, , false, nullptr);
DEFINE_COMMAND_PLUGIN(GetCustomMapMarkerIcon, , true, nullptr);
DEFINE_COMMAND_PLUGIN(SetCustomMapMarkerIcon, , false, kParams_OneForm_OneString);
DEFINE_COMMAND_PLUGIN(QueueCinematicText, , false, kParams_TwoStrings_OneOptionalString_FourOptionalInts);
DEFINE_COMMAND_PLUGIN(QueueObjectiveText, , false, kParams_OneString_TwoOptionalInts);
DEFINE_COMMAND_PLUGIN(GetSystemColor, , false, kParams_OneInt);
DEFINE_COMMAND_PLUGIN(GetSystemColorAlt, , false, kParams_OneInt_ThreeScriptVars);
DEFINE_COMMAND_ALT_PLUGIN(SetCustomReputationChangeIcon, scrci, , false, kParams_OneForm_OneInt_OneString);
DEFINE_COMMAND_PLUGIN(GetExtraMiscStat, , false, kParams_OneString);
DEFINE_COMMAND_PLUGIN(ModExtraMiscStat, , false, kParams_OneString_OneInt);
DEFINE_COMMAND_PLUGIN(InitExtraMiscStat, , false, kParams_OneString);
DEFINE_COMMAND_PLUGIN(ShowBarberMenuEx, , false, kParams_OneInt_OneOptionalForm);
DEFINE_COMMAND_ALT_PLUGIN(PushUIQuestToTop, PushSelectedQuestInterfaceListEntryToTheTopOfThePipBoyQuestLogInterfaceImmediately, , false, kParams_OneQuest);
DEFINE_COMMAND_PLUGIN(DumpQuestObjectiveList, , false, nullptr); //DO NOT REGISTER YET.
DEFINE_COMMAND_PLUGIN(GetSleepWaitMenuState, , false, nullptr);
DEFINE_CMD_ALT_COND_PLUGIN(IsMenuPaused, , "", false, kParams_OneOptionalInt);
DEFINE_COMMAND_PLUGIN(SetHUDVisibilityOverride, "Sets HUD element visibility override flags", false, kParams_OneInt);
DEFINE_COMMAND_PLUGIN(GetHUDVisibilityOverride, "Gets HUD element visibility override flags", false, nullptr);
DEFINE_COMMAND_PLUGIN(UpdateRepairMenu, , false, nullptr);

bool Cmd_DumpQuestObjectiveList_Execute(COMMAND_ARGS) { //Does not update Tweaks.
		if (g_thePlayer) {
			auto headNode = g_thePlayer->questObjectiveList.Head();
			while (headNode) {
				Console_Print("objective %s from quest %s", headNode->data->displayText.c_str(), headNode->data->quest->GetEditorName());
				headNode = headNode->next;
			}
		}

	return true;
}





bool Cmd_PushUIQuestToTop_Execute(COMMAND_ARGS) {
	TESQuest* quest = nullptr;
	*result = 0;
	if (!ExtractArgsEx(EXTRACT_ARGS_EX, &quest) || !g_thePlayer)
		return true;

	auto& list = g_thePlayer->questObjectiveList;
	if (list.Empty())
		return true;

	std::vector<BGSQuestObjective*> matching;
	std::vector<BGSQuestObjective*> others;

	auto node = list.Head();
	while (node) {
		if (node->data) {
			if (node->data->quest == quest)
				matching.push_back(node->data);
			else
				others.push_back(node->data);
		}
		node = node->next;
	}

	if (matching.empty())
		return true;

	node = list.Head();
	while (node->next) {
		auto next = node->next;
		node->next = next->next;
		BSMemory::free(next);
	}

	node->data = matching[0];
	for (size_t i = 1; i < matching.size(); i++)
		list.Append(matching[i]);
	for (auto obj : others)
		list.Append(obj);

	MapMenu* mapMenu = MapMenu::GetSingleton();
	if (mapMenu) {
		mapMenu->questList.FreeAllTiles();
		mapMenu->questList.itemCount = 0;
	}

	*result = 1;
	return true;
}





bool Cmd_ShowBarberMenuEx_Execute(COMMAND_ARGS) {
	enum {
		kFlag_WhiteListHair = 1 << 0,
		kFlag_WhiteListBeard,
	};
	BGSListForm* formList = nullptr;
	uint32_t flags = 0;
	if (!g_thePlayer) return true;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &flags, &formList)) {
		if (formList && IS_TYPE(formList, BGSListForm)) {
			ListNode<TESForm>* iter = formList->list.Head();

			do {
				TESForm* currData = iter->data;
				if (!currData) continue;
				if (IS_TYPE(currData, TESHair)) {
					hk_RSMBarberHook::haircutSetList.Add(currData->refID);
					continue;
				}
				if (IS_TYPE(currData, BGSHeadPart)) {
					hk_RSMBarberHook::beardSetList.Add(currData->refID);
				}
			} while (iter = iter->next);
		}
		auto playerBase =	reinterpret_cast<TESNPC*>(g_thePlayer->GetActorBase());
		hk_RSMBarberHook::haircutSetList.isWhiteList = bool(flags & kFlag_WhiteListHair);
		if (hk_RSMBarberHook::haircutSetList.isWhiteList) {
			hk_RSMBarberHook::haircutSetList.Add(playerBase->hair->refID);
		}
		else {
			hk_RSMBarberHook::haircutSetList.Remove(playerBase->hair->refID);

		}
		hk_RSMBarberHook::beardSetList.isWhiteList = bool(flags & kFlag_WhiteListBeard);
		if (hk_RSMBarberHook::beardSetList.isWhiteList) {
			for (auto iter = playerBase->headPart.Begin(); !iter.End(); iter.Next()) {
				if (*iter) { hk_RSMBarberHook::beardSetList.Add((*iter)->refID);};
			}
		} else{
			for (auto iter = playerBase->headPart.Begin(); !iter.End(); iter.Next()) {
				if (*iter) { hk_RSMBarberHook::beardSetList.Remove((*iter)->refID); };
			}
		}
		CdeclCall<void>(0x705870, 2);
	}
	return true;
}

bool Cmd_InitExtraMiscStat_Execute(COMMAND_ARGS) {
	char name[MAX_PATH] = {};
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
	char name[MAX_PATH] = {};
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
	char name[MAX_PATH] = {};
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
	TESReputation* rep = nullptr;
	uint32_t tierID = 0;
	char path[MAX_PATH] = {};
	if (!(ExtractArgsEx(EXTRACT_ARGS_EX, &rep, &tierID, &path) && rep && IS_TYPE(rep, TESReputation) && tierID >= 1 && tierID <= 4)) return true;
	auto pos = factionRepIcons.find(rep->refID);
	uint32_t bufferSize = strlen(path) + 1;
	char* pathCopy = new char[bufferSize];
	strcpy_s(pathCopy, bufferSize, path);

	if (pos != factionRepIcons.end()) {
		if (*pos->second[tierID - 1]) delete[] pos->second[tierID - 1];
		pos->second[tierID - 1] = pathCopy;
	}
	else {
		std::vector<const char*> v{ "", "", "", "" };
		v[tierID - 1] = pathCopy;
		factionRepIcons.insert(std::pair<uint32_t, std::vector<const char*>>(rep->refID, v));
	}
	*result = 1;
	return true;
}

bool Cmd_GetSystemColorAlt_Execute(COMMAND_ARGS) {
	*result = 0;
	ScriptVar* rOut, * gOut, * bOut;
	uint32_t type;
	uint8_t color[3] = { 0, 0, 0 };
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &type, &rOut, &gOut, &bOut) && type > 0 && type <= 5) {
		SystemColorManager* colorMgr = SystemColorManager::GetSingleton();
		uint32_t color = (colorMgr->GetColor(type) >> 0x8);
		bOut->data = color & 0xFF;
		gOut->data = (color >> 8) & 0xFF;
		rOut->data = (color >> 16) & 0xFF;
		if (IsConsoleMode()) Console_Print("GetSystemColor %d >> %d %d %d", type, rOut->data, gOut->data, bOut->data);
	}
	return true;
}
bool Cmd_GetSystemColor_Execute(COMMAND_ARGS) {
	uint32_t type;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &type) && type > 0 && type <= 5) {
		SystemColorManager* colorMgr = SystemColorManager::GetSingleton();
		uint32_t color = (colorMgr->GetColor(type) >> 0x8);
		*result = color;
		if (IsConsoleMode()) Console_Print("GetSystemColor %d >> 0x%X", type, color);
	}
	return true;
};

bool Cmd_QueueObjectiveText_Execute(COMMAND_ARGS) {
	char text[MAX_PATH] = {};
	uint32_t isCompleted, allowDisplayMultiple;
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

	char title[MAX_PATH], subtitle[MAX_PATH], soundEdid[MAX_PATH] = {};
	*soundEdid = '\0';
	uint32_t queuePriority = kPriorityAppend;
	uint32_t justification = kJustifyLeft;
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
	uint32_t isFemale = 0;
	TESForm* form = nullptr;
	char newPath[MAX_PATH] = {};
	*result = 0;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &newPath, &isFemale, &form) && form) {
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
	TESObjectREFR* markerRef = ThisCall<TESObjectREFR*>(0x77A400, g_thePlayer);
	if (markerRef) {
		*(uint32_t*)result = markerRef->refID;
	}
	return true;
}

bool Cmd_SetWorldSpaceMapTexture_Execute(COMMAND_ARGS) {
	*result = 0;
	TESWorldSpace* worlspace = nullptr;
	char path[MAX_PATH] = {};
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &worlspace, &path) && worlspace && IS_TYPE(worlspace, TESWorldSpace)) {
		worlspace->texture.ddsPath.Set(path);
		*result = 1;
	}
	return true;
}
bool Cmd_GetWorldSpaceMapTexture_Execute(COMMAND_ARGS) {
	*result = 0;
	TESWorldSpace* worlspace = nullptr;
	char path[MAX_PATH] = {};
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &worlspace) && worlspace && IS_TYPE(worlspace, TESWorldSpace) && (worlspace->texture.ddsPath.pString)) {
		strcpy_s(path, worlspace->texture.ddsPath.pString);
		g_strInterface->Assign(PASS_COMMAND_ARGS, path);
		if (IsConsoleMode())
			Console_Print("GetWorldSpaceMapTexture >> %s", path);
	}
	return true;
}

bool Cmd_SetCustomMapMarkerIcon_Execute(COMMAND_ARGS) {
	TESObjectREFR* form;
	char iconPath[MAX_PATH] = {};
	if (!ExtractArgsEx(EXTRACT_ARGS_EX, &form, &iconPath) || !form || (!IS_TYPE(form, BGSListForm) && (!form->GetIsReference() || !form->IsMapMarker() || !GetExtraType(form->extraDataList, MapMarker)))) 
		return true;
	if (IS_TYPE(form, BGSListForm)) {
		ListNode<TESForm>* iterator = ((BGSListForm*)form)->list.Head();
		while (iterator) {
			TESObjectREFR* ref = (TESObjectREFR*)(iterator->data);
			if (ref->GetIsReference() && ref->IsMapMarker() && GetExtraType(ref->extraDataList, MapMarker)) {
				SetMapMarkerIcon(ref, iconPath);
			}
			iterator = iterator->next;
		}
	}
	else {
		SetMapMarkerIcon(form, iconPath);
	}
	if (IsConsoleMode()) Console_Print("SetCustomMapMarkerIcon >> %u, %s", form->refID, iconPath);
	return true;
}

bool Cmd_GetCustomMapMarkerIcon_Execute(COMMAND_ARGS) {
	ExtraMapMarker* mapMarkerExtra;
	if (!thisObj || (!thisObj->GetIsReference() || !thisObj->IsMapMarker())) return true;
	mapMarkerExtra = GetExtraType(thisObj->extraDataList, MapMarker);
	if (!mapMarkerExtra || !mapMarkerExtra->data)  return true;
	const char* resStr = GetMapMarker(thisObj, mapMarkerExtra->data->type);
	g_strInterface->Assign(PASS_COMMAND_ARGS, resStr);
	if (IsConsoleMode()) Console_Print("GetCustomMapMarkerIcon >> %s", resStr);
	return true;
}

bool Cmd_GetSleepWaitMenuState_Execute(COMMAND_ARGS) {
	*result = 0;
	SleepWaitMenu* swMenu = SleepWaitMenu::Get();
	if (!swMenu) return true;
	*result = DWORD(swMenu->isRest) + 1;
	if (IsConsoleMode()) Console_Print("GetSleepWaitMenuState >> %.f", *result);
	return true;
}

bool Cmd_SetHUDVisibilityOverride_Execute(COMMAND_ARGS) {
	uint32_t visFlags = 0;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &visFlags)) {
		HUDMainMenu* hud = HUDMainMenu::GetSingleton();
		if (hud) {
			hud->visibilityOverrides = visFlags;
			HUDMainMenu_UpdateVisibilityState(HUDMainMenu::kHUDState_RECALCULATE);
      *result = 1;
		}
  }

  return true;
}

bool Cmd_GetHUDVisibilityOverride_Execute(COMMAND_ARGS) {
	*result = 0;
	HUDMainMenu* hud = HUDMainMenu::GetSingleton();
	if (hud) {
		*result = hud->visibilityOverrides;
	}
	return true;
}

// To be hooked by RTM
bool Cmd_IsMenuPaused_Eval(COMMAND_ARGS_EVAL) {
	uint32_t uiMenuID = reinterpret_cast<uint32_t>(arg1);
	if (uiMenuID == 0) {
		*result = InterfaceManager::GetSingleton()->currentMode != 1;
	}
	else {
		*result = 1.0;
	}
	return true;
}

bool Cmd_IsMenuPaused_Execute(COMMAND_ARGS) {
	*result = 1;
	uint32_t uiMenuID = 0;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &uiMenuID)) {
		Cmd_IsMenuPaused_Eval(thisObj, reinterpret_cast<void*>(uiMenuID), nullptr, result);
	}
	return true;
}

float CalculateRepairedHealth(ContChangesEntry* target, ContChangesEntry* repairItem) {
	if (!target || !repairItem) return 0.0f;
	float targetHealth = target->GetItemHealthPerc(true);
	float repairItemHealth = repairItem->GetItemHealthPerc(true);
	int repairSkill = g_thePlayer->avOwner.GetActorValueI(kAVCode_Repair);
	int outParam = -1;
	double result = CdeclCall<double>(0x648090, repairSkill, targetHealth, repairItemHealth, &outParam);
	return (float)(result / 100.0);
}

bool Cmd_UpdateRepairMenu_Execute(COMMAND_ARGS) {
	*result = 0;
	RepairMenu* rm = *(RepairMenu**)0x11DA75C;
	if (!rm) return true;
	ContChangesEntry* target = *(ContChangesEntry**)0x11DA760;
	if (!target) return true;
	auto iter = rm->repairItems.GetHead();
	if (!iter) return true;
	do {
		auto listItem = iter->GetItem();
		if (listItem && listItem->tile && listItem->object) {
			float repairedHealth = CalculateRepairedHealth(target, listItem->object);
			listItem->tile->SetFloat(kTileValue_user0, repairedHealth);
		}
	} while (iter = iter->GetNext());
	*result = 1;
	return true;
}
