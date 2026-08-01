#include "fn_ui.h"

#include "decoding.h"
#include "GameObjects.h"
#include "GameRTTI.h"
#include "GameUI.h"

#include "Bethesda/FileFinder.hpp"
#include "Bethesda/ExtraMapMarker.hpp"

#include "JG/ExtraMarkerIcons.hpp"
#include "JG/ExtraMiscStats.hpp"
#include "JG/ExtraReputationIcons.hpp"
#include "JG/RSMBarberHook.hpp"

#include "Shared/Utils/StackObject.hpp"

extern InventoryRef* (*InventoryRefGetForID)(uint32_t refID);

bool Cmd_DumpQuestObjectiveList_Execute(COMMAND_ARGS) { //Does not update Tweaks.
	if (PlayerCharacter::GetSingleton()) {
		auto headNode = PlayerCharacter::GetSingleton()->questObjectiveList.Head();
		while (headNode) {
			Console_Print("objective %s from quest %s", headNode->data->GetDisplayText(), headNode->data->GetOwner()->GetEditorName());
			headNode = headNode->next;
		}
	}

	return true;
}

bool Cmd_PushUIQuestToTop_Execute(COMMAND_ARGS) {
	TESQuest* quest = nullptr;
	arResult = 0;
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
			if (node->data->GetOwner() == quest)
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

	arResult = 1;
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
	arResult = 0;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &name)) {
		arResult = ExtraMiscStats::InitStat(name);
	}
	return true;
}

bool Cmd_ModExtraMiscStat_Execute(COMMAND_ARGS) {
	char name[MAX_PATH] = {};
	int mod;
	arResult = 0;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &name, &mod)) {
		arResult = ExtraMiscStats::ModStat(name, mod);
	}
	return true;
}

bool Cmd_GetExtraMiscStat_Execute(COMMAND_ARGS) {
	char name[MAX_PATH] = {};
	arResult = 0;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &name)) {
		arResult = ExtraMiscStats::GetStat(name);
		if (IsConsoleMode()) Console_Print("GetExtraMiscStat \"%s\": %.f", name, arResult);
	}
	return true;
}

bool Cmd_SetCustomReputationChangeIcon_Execute(COMMAND_ARGS) {
	arResult = 0;
	TESReputation* rep = nullptr;
	uint32_t tierID = 0;
	char path[MAX_PATH] = {};
	if (!(ExtractArgsEx(EXTRACT_ARGS_EX, &rep, &tierID, &path) && rep && IS_TYPE(rep, TESReputation) && tierID >= 1 && tierID <= 4)) return true;
	ExtraReputationIcons::Set(rep->GetFormID(), tierID, path);
	arResult = 1;
	return true;
}

bool Cmd_GetSystemColorAlt_Execute(COMMAND_ARGS) {
	arResult = 0;
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
		arResult = color;
		if (IsConsoleMode()) Console_Print("GetSystemColor %d >> 0x%X", type, color);
	}
	return true;
};

bool Cmd_QueueObjectiveText_Execute(COMMAND_ARGS) {
	char text[MAX_PATH] = {};
	uint32_t isCompleted, allowDisplayMultiple;
	arResult = 0;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &text, &isCompleted, &allowDisplayMultiple)) {
		CdeclCall(0x77A5B0, text, isCompleted, allowDisplayMultiple == 0);
		arResult = 1;
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
	arResult = 0;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &title, &subtitle, &soundEdid, &queuePriority, &justification, &titleFont, &subTitleFont)) {
		if (justification > kJustifyRight) justification = kJustifyRight;

		if (queuePriority == kPriorityClearQueueShowNow) CdeclCall(0x77F500); // HUDMainMenu::HideQuestLocationText

		CdeclCall(0x76B960, title, subtitle, queuePriority == kPriorityAppend, justification, titleFont, subTitleFont, soundEdid); // QuestUpdateManager::SetCustomQuestText
		arResult = 1;
	}
	return true;
};

bool Cmd_SetBipedIconPathAlt_Execute(COMMAND_ARGS) {
	BOOL bFemale = 0;
	TESForm* pForm = nullptr;
	char cPath[MAX_PATH] = {};
	arResult = 0;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &cPath, &bFemale, &pForm) && pForm) {
		TESBipedModelForm* pBipedModel = DYNAMIC_CAST(pForm, TESForm, TESBipedModelForm);
		if (pBipedModel) {
			pBipedModel->kIcons[bFemale].SetTextureName(cPath);
			arResult = 1;
		}
	}

	return true;
}

bool Cmd_GetCustomMapMarker_Execute(COMMAND_ARGS) {
	arResult = 0;
	TESObjectREFR* markerRef = ThisCall<TESObjectREFR*>(0x77A400, PlayerCharacter::GetSingleton());
	if (markerRef) {
		reinterpret_cast<uint32_t&>(arResult) = markerRef->GetFormID();
	}
	return true;
}

bool Cmd_SetWorldSpaceMapTexture_Execute(COMMAND_ARGS) {
	arResult = 0;
	TESWorldSpace* pWorldSpace = nullptr;
	char cPath[MAX_PATH] = {};
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &pWorldSpace, &cPath) && pWorldSpace && IS_TYPE(pWorldSpace, TESWorldSpace)) {
		pWorldSpace->SetTextureName(cPath);
		arResult = 1;
	}
	return true;
}

bool Cmd_GetWorldSpaceMapTexture_Execute(COMMAND_ARGS) {
	arResult = 0;
	TESWorldSpace* pWorldSpace = nullptr;
	char cPath[MAX_PATH] = {};
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &pWorldSpace) && pWorldSpace && IS_TYPE(pWorldSpace, TESWorldSpace) && pWorldSpace->GetTextureNameLength()) {
		strcpy_s(cPath, pWorldSpace->GetTextureName());
		g_strInterface->Assign(PASS_COMMAND_ARGS, cPath);
		if (IsConsoleMode())
			Console_Print("GetWorldSpaceMapTexture >> %s", cPath);
	}
	return true;
}

bool Cmd_SetCustomMapMarkerIcon_Execute(COMMAND_ARGS) {
	TESObjectREFR* form;
	char iconPath[MAX_PATH] = {};
	if (!ExtractArgsEx(EXTRACT_ARGS_EX, &form, &iconPath) || !form || (!IS_TYPE(form, BGSListForm) && (!form->IsReference() || !form->IsMapMarker() || !form->HasExtra<ExtraMapMarker>())))
		return true;
	if (IS_TYPE(form, BGSListForm)) {
		BSSimpleList<TESForm*>* pIter = ((BGSListForm*)form)->GetFormList();
		while (pIter && !pIter->IsEmpty()) {
			TESObjectREFR* ref = (TESObjectREFR*)pIter->GetItem();
			pIter = pIter->GetNext();

			if (ref && ref->IsReference() && ref->IsMapMarker() && ref->HasExtra<ExtraMapMarker>()) {
				ExtraMarkerIcons::SetMapMarkerIcon(ref, iconPath);
			}
		}
	}
	else {
		ExtraMarkerIcons::SetMapMarkerIcon(form, iconPath);
	}
	if (IsConsoleMode())
		Console_Print("SetCustomMapMarkerIcon >> %u, %s", form->GetFormID(), iconPath);
	return true;
}

bool Cmd_GetCustomMapMarkerIcon_Execute(COMMAND_ARGS) {
	if (!apRef || (!apRef->IsReference() || !apRef->IsMapMarker()))
		return true;

	ExtraMapMarker* mapMarkerExtra = apRef->GetExtraData<ExtraMapMarker>();
	if (!mapMarkerExtra || !mapMarkerExtra->pData)
		return true;

	const char* resStr = ExtraMarkerIcons::GetMapMarker(apRef, mapMarkerExtra->pData->usType);
	g_strInterface->Assign(PASS_COMMAND_ARGS, resStr);
	if (IsConsoleMode())
		Console_Print("GetCustomMapMarkerIcon >> %s", resStr);
	return true;
}

bool Cmd_GetSleepWaitMenuState_Execute(COMMAND_ARGS) {
	arResult = 0;
	SleepWaitMenu* swMenu = SleepWaitMenu::Get();
	if (!swMenu) return true;
	arResult = DWORD(swMenu->isRest) + 1;
	if (IsConsoleMode()) Console_Print("GetSleepWaitMenuState >> %.f", arResult);
	return true;
}

bool Cmd_SetHUDVisibilityOverride_Execute(COMMAND_ARGS) {
	uint32_t visFlags = 0;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &visFlags)) {
		HUDMainMenu* hud = HUDMainMenu::GetSingleton();
		if (hud) {
			hud->visibilityOverrides = visFlags;
			CdeclCall(0x771700, HUDMainMenu::kHUDState_RECALCULATE);
			arResult = 1;
		}
	}

	return true;
}

bool Cmd_GetHUDVisibilityOverride_Execute(COMMAND_ARGS) {
	arResult = 0;
	HUDMainMenu* hud = HUDMainMenu::GetSingleton();
	if (hud) {
		arResult = hud->visibilityOverrides;
	}
	return true;
}

// To be hooked by RTM
SPEC_NOINLINE bool Cmd_IsMenuPaused_Eval(COMMAND_ARGS_EVAL) {
	arResult = 1.0;
	uint32_t uiMenuID = reinterpret_cast<uint32_t>(apParam1);
	if (uiMenuID == 0)
		arResult = InterfaceManager::GetSingleton()->currentMode != 1;
	return true;
}

bool Cmd_IsMenuPaused_Execute(COMMAND_ARGS) {
	arResult = 1;
	uint32_t uiMenuID = 0;
	ExtractArgsEx(EXTRACT_ARGS_EX, &uiMenuID);
	return Cmd_IsMenuPaused_Eval(apRef, reinterpret_cast<void*>(uiMenuID), nullptr, arResult);
}

float CalculateRepairedHealth(ItemChange* target, ItemChange* repairItem) {
	if (!target || !repairItem) return 0.0f;
	float targetHealth = target->GetItemHealth(true);
	float repairItemHealth = repairItem->GetItemHealth(true);
	int repairSkill = PlayerCharacter::GetSingleton()->GetActorValueI(ActorValue::Index::REPAIR);
	int outParam = -1;
	double arResult = CdeclCall<double>(0x648090, repairSkill, targetHealth, repairItemHealth, &outParam);
	return (float)(arResult / 100.0);
}

bool Cmd_UpdateRepairMenu_Execute(COMMAND_ARGS) {
	arResult = 0;
	RepairMenu* rm = *(RepairMenu**)0x11DA75C;
	if (!rm) return true;
	ItemChange* target = *(ItemChange**)0x11DA760;
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
	arResult = 1;
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
			arResult = 1;
		}
	}
	return true;
}

bool Cmd_ToggleWeaponScopeUIModel_Execute(COMMAND_ARGS) {
	BOOL bVisible = FALSE;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &bVisible)) {
		Interface::SetGunScopeVisible(bVisible);
		arResult = 1;
	}
	return true;
}

bool Cmd_ClearWeaponScopeUIModel_Execute(COMMAND_ARGS) {
	Interface::SetGunScopeVisible(false);
	Interface::ClearGunScope();
	return true;
}


bool Cmd_GetMenuItemListIndex_Execute(COMMAND_ARGS) {
	arResult = -1;

	if (!InterfaceManager::GetSingleton())
		return true;

	BOOL bRightSide = FALSE;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &bRightSide)) {
		// Find listbox
		const ListBox<ItemChange>* pListBox = nullptr;
		switch (Interface::GetTopMenuID()) {
			case Interface::Menus::MainFour:
			{
				if (Menu::IsMenuVisible(Interface::Menus::PipboyRepair))
					pListBox = &RepairMenu::GetSingleton()->repairItems;
				else if (Menu::IsMenuVisible(Interface::Menus::Inventory))
					pListBox = &InventoryMenu::GetSingleton()->itemList;
				break;
			}
			case Interface::Menus::Container:
			{
				const ContainerMenu* pMenu = ContainerMenu::GetSingleton();
				pListBox = bRightSide ? &pMenu->rightItems : &pMenu->leftItems;
				break;
			}
			case Interface::Menus::Barter:
			{
				const BarterMenu* pMenu = BarterMenu::GetSingleton();
				pListBox = bRightSide ? &pMenu->rightItems : &pMenu->leftItems;
				break;
			}
			case Interface::Menus::VendorRepair:
				pListBox = &RepairServicesMenu::GetSingleton()->itemList;
				break;
			default:
				return true;
		}

		if (!pListBox)
			return true;

		InventoryRef* pInvRef = InventoryRefGetForID(apRef->GetFormID());
		if (!pInvRef)
			return true;

		for (auto pIter = pListBox->GetHead(); pIter && !pIter->IsEmpty(); pIter = pIter->GetNext()) {
			auto pItem = pIter->GetItem();

			if (pItem && pItem->tile && pItem->object) {
				const ItemChange* pItemChange = pItem->object;

				if (pItemChange->GetContainerObject() != pInvRef->pForm)
					continue;

				bool bMatched = false;

				// Does extra data match
				if (pInvRef->pExtraDataList) {
					if (pItemChange->pExtraLists && pItemChange->pExtraLists->IsInList(pInvRef->pExtraDataList))
						bMatched = true;
				}

				// No extra data
				else if (!pItemChange->pExtraLists || pItemChange->pExtraLists->IsEmpty())
					bMatched = true;

				// Find matching tile index
				if (!bMatched)
					continue;

				const Tile* pEntryTile = pItem->tile;
				const Tile* pParent = pEntryTile->parent;
				if (!pParent) [[unlikely]]
					continue;

				auto kIter = pParent->children.GetHeadPos();
				uint32_t uiIndex = 0;
				while (kIter) {
					Tile* pChild = pParent->children.GetNext(kIter);
					if (pChild == pEntryTile) {
						arResult = uiIndex;
						if (IsConsoleMode())
							Console_Print("GetMenuItemListIndex >> %d", uiIndex);
						return true;
					}
					++uiIndex;
				}
			}
		}
	}
	return true;
}

bool Cmd_SelectMenuItemListIndex_Execute(COMMAND_ARGS) {
	arResult = 0;

	if (!InterfaceManager::GetSingleton())
		return true;

	uint32_t uiTileIndex = 0;
	BOOL bRightSide = FALSE;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &uiTileIndex, &bRightSide)) {
		// Find listbox
		ListBox<ItemChange>* pListBox = nullptr;
		switch (Interface::GetTopMenuID())
		{
			case Interface::Menus::MainFour:
				{
					if (Menu::IsMenuVisible(Interface::Menus::PipboyRepair))
						pListBox = &RepairMenu::GetSingleton()->repairItems;
					else if (Menu::IsMenuVisible(Interface::Menus::Inventory))
						pListBox = &InventoryMenu::GetSingleton()->itemList;
					break;
				}
			case Interface::Menus::Container:
			{
				ContainerMenu* pMenu = ContainerMenu::GetSingleton();
				pListBox = bRightSide ? &pMenu->rightItems : &pMenu->leftItems;
				break;
			}
			case Interface::Menus::Barter:
			{
				BarterMenu* pMenu = BarterMenu::GetSingleton();
				pListBox = bRightSide ? &pMenu->rightItems : &pMenu->leftItems;
				break;
			}
			case Interface::Menus::VendorRepair:
				pListBox = &RepairServicesMenu::GetSingleton()->itemList;
				break;
			default:
				return true;
		}

		if (!pListBox)
			return true;

		// Select tile
		if (uiTileIndex < pListBox->itemCount) {
			Tile* tile = pListBox->GetNthTile(uiTileIndex);
			pListBox->SetSelectedTile(tile);
			pListBox->ScrollToHighlight();
			arResult = 1;
		}
	}
	return true;
}