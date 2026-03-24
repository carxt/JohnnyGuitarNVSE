#include "fn_ui.h"
#include "Shared/Utils/StackObject.hpp"
#include <GameObjects.h>
#include <GameUI.h>
#include <JG/RSMBarberHook.hpp>
#include <JG/ExtraMiscStats.hpp>
#include <decoding.h>
#include <GameRTTI.h>
#include <Bethesda/FileFinder.hpp>
#include <JG/ExtraReputationIcons.hpp>
#include <JG/ExtraMarkerIcons.hpp>

bool Cmd_DumpQuestObjectiveList_Execute(COMMAND_ARGS) { //Does not update Tweaks.
	if (PlayerCharacter::GetSingleton()) {
		auto headNode = PlayerCharacter::GetSingleton()->questObjectiveList.Head();
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
	if (!ExtractArgsEx(EXTRACT_ARGS_EX, &quest) || !PlayerCharacter::GetSingleton())
		return true;

	auto& list = PlayerCharacter::GetSingleton()->questObjectiveList;
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
	
	BGSListForm* formList = nullptr;
	uint32_t flags = 0;
	if (!PlayerCharacter::GetSingleton()) return true;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &flags, &formList)) {
		if (formList && IS_TYPE(formList, BGSListForm)) {
			RSMBarberHook::Load(formList);
		}
		RSMBarberHook::ShowMenu(flags);
	}
	return true;
}

bool Cmd_InitExtraMiscStat_Execute(COMMAND_ARGS) {
	char name[MAX_PATH] = {};
	*result = 0;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &name)) {
		*result = ExtraMiscStats::InitStat(name);
	}
	return true;
}

bool Cmd_ModExtraMiscStat_Execute(COMMAND_ARGS) {
	char name[MAX_PATH] = {};
	int mod;
	*result = 0;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &name, &mod)) {
		*result = ExtraMiscStats::ModStat(name, mod);
	}
	return true;
}

bool Cmd_GetExtraMiscStat_Execute(COMMAND_ARGS) {
	char name[MAX_PATH] = {};
	*result = 0;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &name)) {
		*result = ExtraMiscStats::GetStat(name);
		if (IsConsoleMode()) Console_Print("GetExtraMiscStat \"%s\": %.f", name, *result);
	}
	return true;
}
// TODO refactor: move logic to ExtraReputationIcons.cpp
bool Cmd_SetCustomReputationChangeIcon_Execute(COMMAND_ARGS) {
	using namespace ExtraReputationIcons;
	*result = 0;
	TESReputation* rep = nullptr;
	uint32_t tierID = 0;
	char path[MAX_PATH] = {};
	if (!(ExtractArgsEx(EXTRACT_ARGS_EX, &rep, &tierID, &path) && rep && IS_TYPE(rep, TESReputation) && tierID >= 1 && tierID <= 4)) return true;
	auto pos = factionRepIcons.find(rep->GetFormID());
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
		factionRepIcons.insert(std::pair<uint32_t, std::vector<const char*>>(rep->GetFormID(), v));
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
	TESObjectREFR* markerRef = ThisCall<TESObjectREFR*>(0x77A400, PlayerCharacter::GetSingleton());
	if (markerRef) {
		*(uint32_t*)result = markerRef->GetFormID();
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
	if (!ExtractArgsEx(EXTRACT_ARGS_EX, &form, &iconPath) || !form || (!IS_TYPE(form, BGSListForm) && (!form->IsReference() || !form->IsMapMarker() || !GetExtraType(form->extraDataList, MapMarker))))
		return true;
	if (IS_TYPE(form, BGSListForm)) {
		BSSimpleList<TESForm*>* pIter = ((BGSListForm*)form)->GetFormList();
		while (pIter && !pIter->IsEmpty()) {
			TESObjectREFR* ref = (TESObjectREFR*)pIter->GetItem();
			pIter = pIter->GetNext();

			if (ref && ref->IsReference() && ref->IsMapMarker() && GetExtraType(ref->extraDataList, MapMarker)) {
				ExtraMarkerIcons::SetMapMarkerIcon(ref, iconPath);
			}
		}
	}
	else {
		ExtraMarkerIcons::SetMapMarkerIcon(form, iconPath);
	}
	if (IsConsoleMode()) Console_Print("SetCustomMapMarkerIcon >> %u, %s", form->GetFormID(), iconPath);
	return true;
}

bool Cmd_GetCustomMapMarkerIcon_Execute(COMMAND_ARGS) {
	ExtraMapMarker* mapMarkerExtra;
	if (!thisObj || (!thisObj->IsReference() || !thisObj->IsMapMarker())) return true;
	mapMarkerExtra = GetExtraType(thisObj->extraDataList, MapMarker);
	if (!mapMarkerExtra || !mapMarkerExtra->data)  return true;
	const char* resStr = ExtraMarkerIcons::GetMapMarker(thisObj, mapMarkerExtra->data->type);
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
			CdeclCall(0x771700, HUDMainMenu::kHUDState_RECALCULATE);
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
	int repairSkill = PlayerCharacter::GetSingleton()->avOwner.GetActorValueI(kAVCode_Repair);
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


bool Cmd_SetWeaponScopeUIModel_Execute(COMMAND_ARGS) {
	TESForm* pScopeForm = nullptr;
	char cScopePath[MAX_PATH] = {};
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &cScopePath, &pScopeForm)) {
		if (pScopeForm && pScopeForm->GetFormType() == FORM_TYPE::TESObjectWEAP) {
			TESModel* pModel = &static_cast<TESObjectWEAP*>(pScopeForm)->kScope;
			Interface::InitGunScope(pModel);

		}
		else if (cScopePath[0] && FileFinder::Locate(cScopePath, nullptr, FileFinder::SKIP_NONE, FileFinder::ARCHIVE_TYPE_MESHES)) {
			StackObject<TESModel, 0x488F50, 0x489070> kScopeModel;
			kScopeModel->SetModel(cScopePath);
			Interface::InitGunScope(kScopeModel.GetPtr());
			*result = 1;
		}
	}
	return true;
}

bool Cmd_ToggleWeaponScopeUIModel_Execute(COMMAND_ARGS) {
	BOOL bVisible = FALSE;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &bVisible)) {
		Interface::SetGunScopeVisible(bVisible);
		*result = 1;
	}
	return true;
}

bool Cmd_ClearWeaponScopeUIModel_Execute(COMMAND_ARGS) {
	Interface::SetGunScopeVisible(false);
	Interface::ClearGunScope();
	return true;
}