#pragma once

class TESForm;
class TESGlobal;
class ExtraDataList;
class TESHealthForm;

class ContainerItemExtra {
public:
	TESForm* pOwnerForm;
	union {
		TESGlobal*	pOwnerGlobal;
		int32_t		iOwnerRank;
		void*		pUnion;
	};
	float	fHealthMult;

#ifdef GAME
	void AddToExtraDataList(ExtraDataList* apExtraList, TESHealthForm* apHealth);
#endif
};

ASSERT_SIZE(ContainerItemExtra, 0xC);