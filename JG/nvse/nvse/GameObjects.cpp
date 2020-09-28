#include "GameObjects.h"
#include "GameRTTI.h"
#include "GameExtraData.h"
#include "GameTasks.h"
#include "GameUI.h"

ScriptEventList *TESObjectREFR::GetEventList() const
{
	ExtraScript *xScript = (ExtraScript*)extraDataList.GetByType(kExtraData_Script);
	return xScript ? xScript->eventList : NULL;
}

PlayerCharacter *PlayerCharacter::GetSingleton()
{
	return *(PlayerCharacter**)0x11DEA3C;
}

__declspec(naked) TESContainer *TESObjectREFR::GetContainer()
{
	__asm
	{
		mov		eax, [ecx]
		mov		eax, [eax+0x100]
		call	eax
		test	al, al
		mov		eax, [ecx+0x20]
		jz		notActor
		add		eax, 0x64
		retn
	notActor:
		cmp		dword ptr [eax], kVtbl_TESObjectCONT
		jnz		notCONT
		add		eax, 0x30
		retn
	notCONT:
		xor		eax, eax
		retn
	}
}

bool TESObjectREFR::IsMapMarker()
{
	return baseForm->refID == 0x10;
}

bool PlayerCharacter::SetSkeletonPath(const char* newPath)
{
	if (!bThirdPerson) {
		// ###TODO: enable in first person
		return false;
	}

	//// store parent of current niNode
	//NiNode* niParent = (NiNode*)(renderState->niNode->m_parent);

	//// set niNode to NULL via BASE CLASS Set3D() method
	//ThisStdCall(s_TESObjectREFR_Set3D, this, NULL);

	//// modify model path
	//if (newPath) {
	//	TESNPC* base = DYNAMIC_CAST(baseForm, TESForm, TESNPC);
	//	base->model.SetPath(newPath);
	//}

	//// create new NiNode, add to parent
	//*(g_bUpdatePlayerModel) = 1;
	//NiNode* newNode = (NiNode*)ThisStdCall(s_PlayerCharacter_GenerateNiNode, this);

	//niParent->AddObject(newNode, 1);
	//*(g_bUpdatePlayerModel) = 0;
	//newNode->SetName("Player");

	//// get and store camera node
	//// ### TODO: pretty this up
	//UInt32 vtbl = *((UInt32*)newNode);
	//UInt32 vfunc = *((UInt32*)(vtbl + 0x58));
	//NiObject* cameraNode = (NiObject*)ThisStdCall(vfunc, newNode, "Camera01");
	//*g_3rdPersonCameraNode = cameraNode;

	//cameraNode = (NiObject*)ThisStdCall(vfunc, (NiNode*)this->firstPersonNiNode, "Camera01");
	//*g_1stPersonCameraNode = cameraNode;

	//Unk_52();

	return true;
}

void TESObjectREFR::Update3D()
{
	if (this == PlayerCharacter::GetSingleton())
		ThisStdCall(kUpdateAppearanceAddr, this);
	else
	{
		Set3D(NULL, true);
		ModelLoader::GetSingleton()->QueueReference(this, 1, 0);
	}
}

TESObjectREFR *TESObjectREFR::Create(bool bTemp)
{
	TESObjectREFR *refr = (TESObjectREFR*)GameHeapAlloc(sizeof(TESObjectREFR));
	ThisStdCall(s_TESObject_REFR_init, refr);
	if (bTemp) ThisStdCall(0x484490, refr);
	return refr;
}
/*
TESForm* GetPermanentBaseForm(TESObjectREFR* thisObj)	// For LevelledForm, find real baseForm, not temporary one.
{
	ExtraLeveledCreature * pXCreatureData = NULL;

	if (thisObj) {
		pXCreatureData = GetExtraType(thisObj->extraDataList, LeveledCreature);
		if (pXCreatureData && pXCreatureData->baseForm) {
			return pXCreatureData->baseForm;
		}
	}
	if (thisObj && thisObj->baseForm) {
		return thisObj->baseForm;
	}
	return NULL;
}

EquippedItemsList Actor::GetEquippedItems()
{
	EquippedItemsList itemList;
	ExtraContainerDataArray outEntryData;
	ExtraContainerExtendDataArray outExtendData;

	ExtraContainerChanges	* xChanges = static_cast <ExtraContainerChanges *>(extraDataList.GetByType(kExtraData_ContainerChanges));
	if(xChanges) {
		UInt32 count = xChanges->GetAllEquipped(outEntryData, outExtendData);
		for (UInt32 i = 0; i < count ; i++)
			itemList.push_back(outEntryData[i]->type);

	}

	return itemList;
}

ExtraContainerDataArray	Actor::GetEquippedEntryDataList()
{
	ExtraContainerDataArray itemArray;
	ExtraContainerExtendDataArray outExtendData;

	ExtraContainerChanges	* xChanges = static_cast <ExtraContainerChanges *>(extraDataList.GetByType(kExtraData_ContainerChanges));
	if(xChanges)
		xChanges->GetAllEquipped(itemArray, outExtendData);

	return itemArray;
}

ExtraContainerExtendDataArray	Actor::GetEquippedExtendDataList()
{
	ExtraContainerDataArray itemArray;
	ExtraContainerExtendDataArray outExtendData;

	ExtraContainerChanges	* xChanges = static_cast <ExtraContainerChanges *>(extraDataList.GetByType(kExtraData_ContainerChanges));
	if(xChanges)
		xChanges->GetAllEquipped(itemArray, outExtendData);

	return outExtendData;
}
*/
