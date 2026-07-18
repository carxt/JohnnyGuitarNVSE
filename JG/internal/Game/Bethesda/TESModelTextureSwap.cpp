#include "TESModelTextureSwap.hpp"

// GAME - 0x500940
const BSSimpleList<TEX_SWAP*>* TESModelTextureSwap::GetTexSwapList() const {
	return &kTextureSwaps;
}

// GAME - 0x500940
BSSimpleList<TEX_SWAP*>* TESModelTextureSwap::GetTexSwapList() {
	return &kTextureSwaps;
}

// GAME - 0x48AD70
TEX_SWAP* TESModelTextureSwap::GetTexSwap(int32_t aiIndex) const {
	return ThisCall<TEX_SWAP*>(0x48AD70, this, aiIndex);
}

// GAME - 0x48AE30
void TESModelTextureSwap::AddTexSwap(const char* apObjectName, int32_t aiIndex, BGSTextureSet* apTextureSet) {
	ThisCall(0x48AE30, this, apObjectName, aiIndex, apTextureSet);
}

void TESModelTextureSwap::RemoveTexSwap(int32_t aiIndex) {
	if (aiIndex == -1)
		return;

	auto pIter = GetTexSwapList();
	while (pIter && !pIter->IsEmpty()) {
		TEX_SWAP* pSwap = pIter->GetItem();
		if (pSwap && pSwap->iObjectIndex == aiIndex) {
			pIter->Remove(pSwap);
			delete pSwap;
			return;
		}
		pIter = pIter->GetNext();
	}
}

// GAME - 0x48ADE0
void TESModelTextureSwap::ClearTexSwapList() {
	ThisCall(0x48ADE0, this);
}

// GAME - 0x48B310
bool TESModelTextureSwap::HasTextureSwap(TESForm* apForm, TESObjectREFR* apRef) {
	return CdeclCall<bool>(0x48B310, apForm, apRef);
}

// GAME - 0x48AFE0
void TESModelTextureSwap::SwapTextures(NiAVObject* apObject) {
	ThisCall(0x48AFE0, this, apObject);
}
