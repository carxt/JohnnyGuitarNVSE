#include "GameObjects.h"
#include "GameRTTI.h"
#include "GameExtraData.h"
#include "GameTasks.h"
#include "GameUI.h"
#include "GameProcess.h"

#include "Bethesda/BSUtilities.hpp"

TESForm* TESObjectREFR::GetBaseForm()
{
	TESForm* baseform = nullptr;
	if (this->baseForm) {
		baseform = this->baseForm;
		if (baseform->GetCompileIndex() == 0xFF) {
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

NiNode* PlayerCharacter::GetNode(bool abFirstPerson) const {
	if (abFirstPerson)
		return playerNode;
	else if (renderState)
		return renderState->rootNode;
	else
		return nullptr;
}

// GAME - 0x950B00
BipedAnim* PlayerCharacter::GetBiped(bool abFirstPerson) const {
	return abFirstPerson ? p1stPersonBipedAnim : pBipedAnim;
}

// GAME - 0x950A60
Animation* PlayerCharacter::GetAnimation(bool abFirstPerson) const {
	if (abFirstPerson)
		return p1stPersonAnimation;
	else if (baseProcess)
		return baseProcess->GetAnimation();
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
	return baseForm->GetFormID() == 0x10;
}

// GAME - 0x55D520
const char* TESObjectREFR::GetFullName() const {
	return ThisCall<const char*>(0x55D520, this);
}

void TESObjectREFR::Update3D() {
	if (this == PlayerCharacter::GetSingleton())
		ThisCall(kUpdateAppearanceAddr, this);
	else {
		Set3D(NULL, true);
		ModelLoader::GetSingleton()->QueueReference(this, 1, 0);
	}
}

TESObjectREFR* TESObjectREFR::Create(bool bTemp) {
	TESObjectREFR* refr = BSMemory::malloc<TESObjectREFR>();
	ThisCall(s_TESObject_REFR_init, refr);
	if (bTemp) ThisCall(0x484490, refr);
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
				uint8_t motionType = rigidBody->motion.type;
				if ((motionType == 2) || (motionType == 3) || (motionType == 6))
					return rigidBody;
			}
		}
	}
	return NULL;
}

NiAVObject* TESObjectREFR::GetNiBlock(const char* blockName) {
	NiNode* rootNode = GetNiNode();
	return BSUtilities::GetObjectByName(rootNode,  blockName);
}

TESObjectWEAP* Actor::GetEquippedWeapon() {
	return ThisCall<TESObjectWEAP*>(0x8A1710, this);
}


bool TESObjectREFR::GetDisabled(bool checkQueue) const
{
	bool ((__fastcall * fn_GetDisabled)) (const TESObjectREFR*) = decltype(fn_GetDisabled)( 0x0440DA0);
	if (!checkQueue) return fn_GetDisabled(this);
	bool((__cdecl * fn_InEnableRefs)) (const TESObjectREFR*) = decltype(fn_InEnableRefs)(0x05AA680);
	bool((__cdecl * fn_InPendingDisableRefs)) (const TESObjectREFR*) = decltype(fn_InPendingDisableRefs)(0x05AA630);
	return (fn_GetDisabled(this) && !fn_InEnableRefs(this) ) || fn_InPendingDisableRefs(this);
}

// GAME - 0x8B36F0
bool Actor::SetPathfindingGoal(TESObjectREFR* apTargetRef, float afTargetRadius, PathingAvoidNodeArray* apAvoidNodes) {
	return ThisCall<bool>(0x8B36F0, this, apTargetRef, afTargetRadius, apAvoidNodes);
}

// GAME - 0x8B3690
bool Actor::SetPathfindingGoal(const NiPoint3& arGoalLocation, TESObjectCELL* apCell, TESWorldSpace* apWorldSpace, float afTargetRadius, PathingAvoidNodeArray* apAvoidNodes) {
	return ThisCall<bool>(0x8B3690, this, &arGoalLocation, apCell, apWorldSpace, afTargetRadius, apAvoidNodes);
}

// GAME - 0x8B37C0
bool Actor::SetPathfindingGoalAndAngle(TESObjectREFR* apTargetRef, float afTargetRadius, PathingAvoidNodeArray* apAvoidNodes) {
	return ThisCall<bool>(0x8B37C0, this, apTargetRef, afTargetRadius, apAvoidNodes);
}

// GAME - 0x8B3750
bool Actor::SetPathfindingGoalAndAngle(const NiPoint3& arGoalLocation, TESObjectCELL* apCell, TESWorldSpace* apWorldSpace, float afTargetRadius, float afTargetAngle, PathingAvoidNodeArray* apAvoidNodes) {
	return ThisCall<bool>(0x8B3750, this, &arGoalLocation, apCell, apWorldSpace, afTargetRadius, afTargetAngle, apAvoidNodes);
}

void Actor::StopMoving() {
	ThisCall(0x8B3AB0, this);
}

bool Actor::IsInDialogueWithPlayer() const {
	return ThisCall<bool>(0x933840, this);
}

bool Actor::GetRespawn() const {
	return ThisCall<bool>(0x87F4A0, this);
}
