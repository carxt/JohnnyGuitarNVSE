#include "BGSDestructibleObjectForm.hpp"

// GAME - 0x726070
DestructibleObjectData* BGSDestructibleObjectForm::GetData() const {
	return pData;
}

// GAME - 0x475AB0
uint32_t BGSDestructibleObjectForm::GetMaxHealth(TESObjectREFR* apRef) const {
	return ThisCall<uint32_t>(0x475AB0, this, apRef);
}

// GAME - 0x476A40
DestructibleObjectStage* BGSDestructibleObjectForm::GetStage(uint32_t auiIndex) const {
	if (pData && auiIndex < pData->ucNumStages) {
		return pData->pStagesArray[auiIndex];
	}
	return nullptr;
}

// GAME - 0x576100
bool BGSDestructibleObjectForm::GetTargetableInVATS() const {
	return pData && pData->ucFlags.bVATSTargetable;
}

// GAME - 0x477430
int32_t BGSDestructibleObjectForm::CalcDestructionStage(TESObjectREFR* apRef) {
	return CdeclCall<int32_t>(0x477430, apRef);
}

// GAME - 0x477BC0
uint32_t BGSDestructibleObjectForm::GetSelfDamage(TESObjectREFR* apRef, float afHealth) {
	return CdeclCall<uint32_t>(0x477BC0, apRef, afHealth);
}

// GAME - 0x4759A0
TESModelTextureSwap* BGSDestructibleObjectForm::GetModelSwap(TESForm* apForm, int32_t aiIndex) {
	return CdeclCall<TESModelTextureSwap*>(0x4759A0, apForm, aiIndex);
}

// GAME - 0x475920
int32_t BGSDestructibleObjectForm::GetModelSwapIndex(TESForm* apForm, TESModelTextureSwap* apModelSwap) {
	return CdeclCall<int32_t>(0x475920, apForm, apModelSwap);
}

// GAME - 0x476EC0
void BGSDestructibleObjectForm::UpdateDamageStageNodes(NiAVObject* apObject, uint32_t auiDamageLevel) {
	CdeclCall(0x476EC0, apObject, auiDamageLevel);
}

// GAME - 0x477D10
void BGSDestructibleObjectForm::ClearDestruction(TESObjectREFR* apRef) {
	CdeclCall(0x477D10, apRef);
}

// GAME - 0x475400
BGSDestructibleObjectForm* BGSDestructibleObjectForm::GetDestructionForm(const TESForm* apForm) {
	return CdeclCall<BGSDestructibleObjectForm*>(0x475400, apForm);
}