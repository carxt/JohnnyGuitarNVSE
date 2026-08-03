#include "fn_ui.h"
#ifdef GAME
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
#include "Shared/BSMemory/BSScrapMemory.hpp"

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

template<typename T>
using ScrapVector = std::vector<T, BSScrapAllocator<T>>;

bool Cmd_PushUIQuestToTop_Execute(COMMAND_ARGS) {
	TESQuest* pQuest = nullptr;
	arResult = 0;
	if (!ExtractArgsEx(EXTRACT_ARGS_EX, &pQuest) || !PlayerCharacter::GetSingleton())
		return true;

	auto& kList = PlayerCharacter::GetSingleton()->questObjectiveList;
	if (kList.Empty())
		return true;

	ScrapVector<BGSQuestObjective*> kMatching;
	ScrapVector<BGSQuestObjective*> kOthers;

	auto node = kList.Head();
	while (node) {
		if (node->data) {
			if (node->data->GetOwner() == pQuest)
				kMatching.push_back(node->data);
			else
				kOthers.push_back(node->data);
		}
		node = node->next;
	}

	if (kMatching.empty())
		return true;

	node = kList.Head();
	while (node->next) {
		auto next = node->next;
		node->next = next->next;
		BSMemory::free(next);
	}

	node->data = kMatching[0];
	for (size_t i = 1; i < kMatching.size(); i++)
		kList.Append(kMatching[i]);
	for (auto obj : kOthers)
		kList.Append(obj);

	MapMenu* pMapMenu = MapMenu::GetSingleton();
	if (pMapMenu) {
		pMapMenu->questList.RemoveAll();
		pMapMenu->questList.usNextIndex = 0;
	}

	arResult = 1;
	return true;
}

bool Cmd_ShowBarberMenuEx_Execute(COMMAND_ARGS) {
	uint32_t uiFlags = 0;
	BGSListForm* pFormList = nullptr;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &uiFlags, &pFormList)) {
		if (pFormList && IS_TYPE(pFormList, BGSListForm))
			RSMBarberHook::Load(pFormList);

		RSMBarberHook::ShowMenu(uiFlags);
	}
	return true;
}

bool Cmd_InitExtraMiscStat_Execute(COMMAND_ARGS) {
	arResult = 0;
	char cName[MAX_PATH] = {};
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &cName))
		arResult = ExtraMiscStats::InitStat(cName);
	return true;
}

bool Cmd_ModExtraMiscStat_Execute(COMMAND_ARGS) {
	arResult = 0;
	char cName[MAX_PATH] = {};
	int32_t iModValue;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &cName, &iModValue))
		arResult = ExtraMiscStats::ModStat(cName, iModValue);
	return true;
}

bool Cmd_GetExtraMiscStat_Execute(COMMAND_ARGS) {
	arResult = 0;
	char cName[MAX_PATH] = {};
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &cName)) {
		arResult = ExtraMiscStats::GetStat(cName);
		if (IsConsoleMode()) 
			Console_Print("GetExtraMiscStat \"%s\": %.f", cName, arResult);
	}
	return true;
}

bool Cmd_SetCustomReputationChangeIcon_Execute(COMMAND_ARGS) {
	arResult = 0;
	TESReputation* pReputation = nullptr;
	uint32_t uiTierID = 0;
	char cPath[MAX_PATH] = {};
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &pReputation, &uiTierID, &cPath) && pReputation && IS_TYPE(pReputation, TESReputation) && uiTierID >= 1 && uiTierID <= 4) {
		ExtraReputationIcons::Set(pReputation->GetFormID(), uiTierID, cPath);
		arResult = 1;
	}
	return true;
}

bool Cmd_GetSystemColorAlt_Execute(COMMAND_ARGS) {
	arResult = 0;
	ScriptVar* pRed, * pGreen, * pBlue;
	uint32_t uiType;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &uiType, &pRed, &pGreen, &pBlue) && uiType > 0 && uiType <= 5) {
		SystemColorManager* pMgr = SystemColorManager::GetSingleton();
		uint32_t uiColor = (pMgr->GetColor(uiType) >> 0x8);
		pBlue->data		= uiColor & 0xFF;
		pGreen->data	= (uiColor >> 8) & 0xFF;
		pRed->data		= (uiColor >> 16) & 0xFF;
		if (IsConsoleMode())
			Console_Print("GetSystemColor %d >> %d %d %d", uiType, pRed->data, pGreen->data, pBlue->data);
	}
	return true;
}
bool Cmd_GetSystemColor_Execute(COMMAND_ARGS) {
	arResult = 0;
	uint32_t uiType;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &uiType) && uiType > 0 && uiType <= 5) {
		SystemColorManager* pMgr = SystemColorManager::GetSingleton();
		uint32_t uiColor = (pMgr->GetColor(uiType) >> 0x8);
		arResult = uiColor;
		if (IsConsoleMode())
			Console_Print("GetSystemColor %d >> 0x%X", uiType, uiColor);
	}
	return true;
};

bool Cmd_QueueObjectiveText_Execute(COMMAND_ARGS) {
	arResult = 0;
	char cText[MAX_PATH] = {};
	BOOL bCompleted, bAllowMultiple;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &cText, &bCompleted, &bAllowMultiple)) {
		CdeclCall(0x77A5B0, cText, bCompleted, bAllowMultiple == 0); // HUDMainMenu::ShowQuestObjective
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
		if (justification > kJustifyRight) 
			justification = kJustifyRight;

		if (queuePriority == kPriorityClearQueueShowNow)
			CdeclCall(0x77F500); // HUDMainMenu::HideQuestLocationText

		CdeclCall(0x76B960, title, subtitle, queuePriority == kPriorityAppend, justification, titleFont, subTitleFont, soundEdid); // QuestUpdateManager::SetCustomQuestText
		arResult = 1;
	}
	return true;
};

bool Cmd_SetBipedIconPathAlt_Execute(COMMAND_ARGS) {
	arResult = 0;
	char cPath[MAX_PATH] = {};
	BOOL bFemale = FALSE;
	TESForm* pForm = nullptr;
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
	TESObjectREFR* pMarker = ThisCall<TESObjectREFR*>(0x77A400, PlayerCharacter::GetSingleton()); // PlayerCharacter::GetPlayerMarkerTrackingRef
	if (pMarker)
		ScriptUtils::SetFormIDResult(arResult, pMarker->GetFormID());
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
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &pWorldSpace) && pWorldSpace && IS_TYPE(pWorldSpace, TESWorldSpace) && pWorldSpace->GetTextureNameLength()) {
		const char* pPath = pWorldSpace->GetTextureName();
		g_strInterface->Assign(PASS_COMMAND_ARGS, pPath);
		if (IsConsoleMode())
			Console_Print("GetWorldSpaceMapTexture >> %s", pPath);
	}
	return true;
}

bool Cmd_SetCustomMapMarkerIcon_Execute(COMMAND_ARGS) {
	arResult = 0;
	TESForm* pForm = nullptr;
	char cIconPath[MAX_PATH] = {};
	if (!ExtractArgsEx(EXTRACT_ARGS_EX, &pForm, &cIconPath) || !pForm)
		return true;
	
	bool bSuccess = false;
	if (pForm->IsReference()) {
		TESObjectREFR* pReference = static_cast<TESObjectREFR*>(pForm);
		ExtraMarkerIcons::SetMapMarkerIcon(pReference, cIconPath);
		if (pReference && pReference->IsReference() && pReference->IsMapMarker() && pReference->HasExtra<ExtraMapMarker>()) {
			ExtraMarkerIcons::SetMapMarkerIcon(pReference, cIconPath);
			bSuccess = true;
		}
	}
	else if (IS_TYPE(pForm, BGSListForm)) {
		BSSimpleList<TESForm*>* pIter = static_cast<BGSListForm*>(pForm)->GetFormList();
		while (pIter && !pIter->IsEmpty()) {
			TESObjectREFR* pReference = static_cast<TESObjectREFR*>(pIter->GetItem());
			pIter = pIter->GetNext();

			if (pReference && pReference->IsReference() && pReference->IsMapMarker() && pReference->HasExtra<ExtraMapMarker>()) {
				ExtraMarkerIcons::SetMapMarkerIcon(pReference, cIconPath);
				bSuccess = true;
			}
		}
	}

	arResult = bSuccess;

	if (bSuccess && IsConsoleMode())
		Console_Print("SetCustomMapMarkerIcon >> %u, %s", pForm->GetFormID(), cIconPath);

	return true;
}

bool Cmd_GetCustomMapMarkerIcon_Execute(COMMAND_ARGS) {
	if (!apRef || (!apRef->IsReference() || !apRef->IsMapMarker()))
		return true;

	ExtraMapMarker* pMarker = apRef->GetExtraData<ExtraMapMarker>();
	if (!pMarker || !pMarker->pData)
		return true;

	const char* pString = ExtraMarkerIcons::GetMapMarker(apRef, pMarker->pData->usType);
	g_strInterface->Assign(PASS_COMMAND_ARGS, pString);

	if (IsConsoleMode())
		Console_Print("GetCustomMapMarkerIcon >> %s", pString);

	return true;
}

bool Cmd_GetSleepWaitMenuState_Execute(COMMAND_ARGS) {
	arResult = 0;
	SleepWaitMenu* pMenu = SleepWaitMenu::Get();
	if (!pMenu) 
		return true;

	arResult = DWORD(pMenu->isRest) + 1;
	if (IsConsoleMode()) 
		Console_Print("GetSleepWaitMenuState >> %.f", arResult);

	return true;
}

bool Cmd_SetHUDVisibilityOverride_Execute(COMMAND_ARGS) {
	uint32_t uiFlags = 0;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &uiFlags)) {
		HUDMainMenu* pMenu = HUDMainMenu::GetSingleton();
		if (pMenu) {
			pMenu->visibilityOverrides = uiFlags;
			CdeclCall(0x771700, HUDMainMenu::kHUDState_RECALCULATE);
			arResult = 1;
		}
	}
	return true;
}

bool Cmd_GetHUDVisibilityOverride_Execute(COMMAND_ARGS) {
	arResult = 0;
	HUDMainMenu* pMenu = HUDMainMenu::GetSingleton();
	if (pMenu)
		arResult = pMenu->visibilityOverrides;
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
	if (!target || !repairItem)
		return 0.f;

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
		if (listItem && listItem->pTile && listItem->data) {
			float repairedHealth = CalculateRepairedHealth(target, listItem->data);
			listItem->pTile->Set(TILE_TRAIT::USER0, repairedHealth);
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
		else if (cScopePath[0] && FileFinder::Locate(cScopePath, nullptr, FileFinder::SKIP_NONE, ARCHIVE_TYPE::MESHES)) {
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

			if (pItem && pItem->pTile && pItem->data) {
				const ItemChange* pItemChange = pItem->data;

				if (pItemChange->GetContainerObject() != pInvRef->pForm)
					continue;

				bool bMatched = false;

				// Does extra data match
				if (pInvRef->pExtraDataList) {
					if (pItemChange->GetExtraDataList() && pItemChange->GetExtraDataList()->IsInList(pInvRef->pExtraDataList))
						bMatched = true;
				}

				// No extra data
				else if (!pItemChange->GetExtraDataList() || pItemChange->GetExtraDataList()->IsEmpty())
					bMatched = true;

				// Find matching tile index
				if (!bMatched)
					continue;

				const Tile* pEntryTile = pItem->pTile;
				const Tile* pParent = pEntryTile->GetParent();
				if (!pParent) [[unlikely]]
					continue;

				auto kIter = pParent->kChildren.GetHeadPos();
				uint32_t uiIndex = 0;
				while (kIter) {
					Tile* pChild = pParent->kChildren.GetNext(kIter);
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
		if (uiTileIndex < pListBox->usNextIndex) {
			Tile* pTile = pListBox->GetTileAt(uiTileIndex, true);
			pListBox->Highlight(pTile);
			pListBox->ScrollToHighlight();
			arResult = 1;
		}
	}
	return true;
}
#endif