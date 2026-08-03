#include "NiSkinInstance.hpp"

// GAME - 0x6884C0
// GECK - N/A
NiSkinInstance* NiSkinInstance::Create(NiSkinData* apSkinData, NiAVObject* apRootParent, NiAVObject** ppBones) {
#ifdef GAME
	return NiCreate<NiSkinInstance, 0x6884C0>(apSkinData, apRootParent, ppBones);
#else
	NiSkinInstance* pSkinInstance = NiSkinInstance::CreateObject();
	pSkinInstance->m_spSkinData = apSkinData;
	pSkinInstance->m_pkRootParent = apRootParent;
	pSkinInstance->m_ppkBones = ppBones;
	return pSkinInstance;
#endif
}

// GAME - 0x43B230
NiSkinPartition* NiSkinInstance::GetSkinPartition() const { 
	return m_spSkinPartition; 
}

// GAME - 0x4ADDC0
void NiSkinInstance::SetSkinPartition(NiSkinPartition* apSkinPartition) { 
	m_spSkinPartition = apSkinPartition; 
}

// GAME - 0x5585E0
NiSkinData* NiSkinInstance::GetSkinData() const {
	return m_spSkinData;
}

void NiSkinInstance::SetSkinData(NiSkinData* apSkinData) {
	m_spSkinData = apSkinData;
}

void NiSkinInstance::GetWorldToSkinTransform(NiTransform& arWorldToSkin) const {
	NiTransform kWorldToRootParent;

	m_pkRootParent->GetWorldTransform().Invert(kWorldToRootParent);
	arWorldToSkin = m_spSkinData->m_kRootParentToSkin * kWorldToRootParent;
}

void NiSkinInstance::SetBoneMatrices(void* apMatrices, uint32_t auiAllocatedSize) {
	m_pvBoneMatrices = apMatrices;
	m_uiAllocatedSize = auiAllocatedSize;
}

void NiSkinInstance::SetBoneMatrixInfo(uint32_t auiNumMatrices, uint32_t auiNumRegisters) {
	m_uiNumMatrices = auiNumMatrices;
	m_uiNumRegisters = auiNumRegisters;
}
