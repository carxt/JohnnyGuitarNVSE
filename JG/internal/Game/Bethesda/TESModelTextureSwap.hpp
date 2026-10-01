#pragma once

#include "TESModel.hpp"
#include "BSSimpleList.hpp"

class BGSTextureSet;
class NiAVObject;
class TESObjectREFR;
class TESForm;

struct SPEC_EMPTY_BASES TEX_SWAP : public BSMemObject {
	BGSTextureSet*	pTextureSet;
	int32_t			iObjectIndex;
	char			cObjectName[128];
};

class TESModelTextureSwap : public TESModel {
public:
	TESModelTextureSwap();
	~TESModelTextureSwap();

#ifdef EDITOR
	uint32_t				uiControlID24;
#endif
	BSSimpleList<TEX_SWAP*> kTextureSwaps;

	const BSSimpleList<TEX_SWAP*>* GetTexSwapList() const;
	BSSimpleList<TEX_SWAP*>* GetTexSwapList();

	TEX_SWAP* GetTexSwap(int32_t aiIndex) const;
	void AddTexSwap(const char* apObjectName, int32_t aiIndex, BGSTextureSet* apTextureSet);
	void RemoveTexSwap(int32_t aiIndex);

	void ClearTexSwapList();

	static bool HasTextureSwap(TESForm* apForm, TESObjectREFR* apRef);

	void SwapTextures(NiAVObject* apObject);
};

#ifdef GAME
ASSERT_SIZE(TESModelTextureSwap, 0x20);
#else
ASSERT_SIZE(TESModelTextureSwap, 0x30);
#endif