#include "GameObjects.h"
#include "GameRTTI.h"
#include "GameExtraData.h"
#include "GameTasks.h"
#include "GameUI.h"

TESForm* TESObjectREFR::GetBaseForm()
{
	TESForm* baseform = nullptr;
	if (this->baseForm) {
		baseform = this->baseForm;
		if (baseform->modIndex == 0xFF) {
			if (IS_TYPE(baseform, BGSPlaceableWater)) {
				return ((BGSPlaceableWater*)baseform)->water;
			}
			ExtraLeveledCreature* xLvlCrea = (ExtraLeveledCreature*)this->extraDataList.GetByType(kExtraData_LeveledCreature);
			if (xLvlCrea && xLvlCrea->baseForm) {
				return xLvlCrea->baseForm;
			}
		}
	}
	return baseform;
}
ScriptEventList* TESObjectREFR::GetEventList() const {
	ExtraScript* xScript = (ExtraScript*)extraDataList.GetByType(kExtraData_Script);
	return xScript ? xScript->eventList : NULL;
}

PlayerCharacter* PlayerCharacter::GetSingleton() {
	return *(PlayerCharacter**)0x11DEA3C;
}

NiNode* PlayerCharacter::GetNode(const bool abFirstPerson) const {
	if (abFirstPerson)
		return playerNode;
	else if (renderState)
		return renderState->rootNode;
	else
		return nullptr;
}

__declspec(naked) TESContainer* TESObjectREFR::GetContainer() {
	__asm
	{
		mov		eax, [ecx]
		mov		eax, [eax + 0x100]
		call	eax
		test	al, al
		mov		eax, [ecx + 0x20]
		jz		notActor
		add		eax, 0x64
		retn
		notActor :
		cmp		dword ptr[eax], kVtbl_TESObjectCONT
			jnz		notCONT
			add		eax, 0x30
			retn
			notCONT :
		xor eax, eax
			retn
	}
}

bool TESObjectREFR::IsMapMarker() {
	return baseForm->refID == 0x10;
}

void TESObjectREFR::Update3D() {
	if (this == PlayerCharacter::GetSingleton())
		ThisStdCall(kUpdateAppearanceAddr, this);
	else {
		Set3D(NULL, true);
		ModelLoader::GetSingleton()->QueueReference(this, 1, 0);
	}
}

TESObjectREFR* TESObjectREFR::Create(bool bTemp) {
	TESObjectREFR* refr = (TESObjectREFR*)GameHeapAlloc(sizeof(TESObjectREFR));
	ThisStdCall(s_TESObject_REFR_init, refr);
	if (bTemp) ThisStdCall(0x484490, refr);
	return refr;
}

TESForm* GetPermanentBaseForm(TESObjectREFR* thisObj)	// For LevelledForm, find real baseForm, not temporary one.
{
	ExtraLeveledCreature* pXCreatureData = NULL;

	if (thisObj) {
		pXCreatureData = (ExtraLeveledCreature*) thisObj->extraDataList.GetByType(kExtraData_LeveledCreature);
		if (pXCreatureData && pXCreatureData->baseForm) {
			return pXCreatureData->baseForm;
		}
		return thisObj->baseForm;
	}
	return NULL;
}


TESCombatStyle* Actor::GetCombatStyle() 
{
	ExtraCombatStyle* xCmbStyle = GetExtraType(extraDataList, CombatStyle);
	if (xCmbStyle && xCmbStyle->combatStyle) return xCmbStyle->combatStyle;
	return ((TESActorBase*)baseForm)->GetCombatStyle();
}

TESActorBase* Actor::GetActorBase() {
	ExtraLeveledCreature* xLvlCre = GetExtraType(extraDataList, LeveledCreature);
	return (xLvlCre && xLvlCre->form) ? (TESActorBase*)xLvlCre->form : (TESActorBase*)baseForm;
}

NiNode* TESObjectREFR::GetNode(const char* nodeName) {
	NiNode* rootNode = GetNiNode();
	return rootNode ? (*nodeName ? rootNode->GetNode(nodeName) : rootNode) : NULL;
}
hkpRigidBody* TESObjectREFR::GetRigidBody(const char* nodeName) {
	NiNode* rootNode = GetNiNode();
	if (rootNode) {
		NiNode* targetNode = rootNode->GetNode(nodeName);
		if (targetNode && targetNode->m_collisionObject) {
			bhkWorldObject* hWorldObj = targetNode->m_collisionObject->worldObj;
			if (hWorldObj) {
				hkpRigidBody* rigidBody = (hkpRigidBody*)hWorldObj->refObject;
				UInt8 motionType = rigidBody->motion.type;
				if ((motionType == 2) || (motionType == 3) || (motionType == 6))
					return rigidBody;
			}
		}
	}
	return NULL;
}

NiAVObject* TESObjectREFR::GetNiBlock(const char* blockName) {
	NiNode* rootNode = GetNiNode();
	return rootNode ? rootNode->GetBlock(blockName) : NULL;
}

TESObjectWEAP* Actor::GetEquippedWeapon() {
	return ThisStdCall<TESObjectWEAP*>(0x8A1710, this);
}
