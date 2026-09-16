#include "InventoryRef.hpp"
#include "Bethesda/InventoryChanges.hpp"
#include "Bethesda/ExtraDataList.hpp"
#include <GameObjects.h>

bool __fastcall InventoryRef::CreateExtraData(BSExtraData* apExtraData) {
	BSSimpleList<ItemChange*>* pItemChanges = pContainerRef->GetContainerChangesList();
	if (!pItemChanges)
		return false;

	BSSimpleList<ItemChange*>* pEntry = pItemChanges->Find([&](const BSSimpleList<ItemChange*>* apEntry) {
		return apEntry->GetItem()->pObject == pForm;
		}
	);

	if (!pEntry)
		return false;

	ItemChange* pChange = pEntry->GetItem();
	if (!pChange)
		return false;

	pExtraDataList = ExtraDataList::Create();
	pExtraDataList->AddExtra(apExtraData);

	if (!pChange->pExtraLists)
		pChange->pExtraLists = new BSSimpleList<ExtraDataList*>();

	pChange->pExtraLists->AddHead(pExtraDataList);
	return true;
}