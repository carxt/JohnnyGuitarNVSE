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
// GECK - 0x5051D0
TEX_SWAP* TESModelTextureSwap::GetTexSwap(int32_t aiIndex) const {
#ifdef GAME
	return ThisCall<TEX_SWAP*>(0x48AD70, this, aiIndex);
#else
	return ThisCall<TEX_SWAP*>(0x5051D0, this, aiIndex);
#endif
}

// GAME - 0x48AE30
// GECK - 0x5058D0
void TESModelTextureSwap::AddTexSwap(const char* apObjectName, int32_t aiIndex, BGSTextureSet* apTextureSet) {
#ifdef GAME
	ThisCall(0x48AE30, this, apObjectName, aiIndex, apTextureSet);
#else
	ThisCall(0x5058D0, this, apObjectName, aiIndex, apTextureSet);
#endif
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
// GECK - 0x505870
void TESModelTextureSwap::ClearTexSwapList() {
#ifdef GAME
	ThisCall(0x48ADE0, this);
#else
	ThisCall(0x505870, this);
#endif
}

#ifdef GAME
// GAME - 0x48B310
bool TESModelTextureSwap::HasTextureSwap(TESForm* apForm, TESObjectREFR* apRef) {
	return CdeclCall<bool>(0x48B310, apForm, apRef);
}
#endif

// GAME - 0x48AFE0
// GECK - 0x505B60
void TESModelTextureSwap::SwapTextures(NiAVObject* apObject) {
#ifdef GAME
	ThisCall(0x48AFE0, this, apObject);
#else
	ThisCall(0x505B60, this, apObject);
#endif
}
