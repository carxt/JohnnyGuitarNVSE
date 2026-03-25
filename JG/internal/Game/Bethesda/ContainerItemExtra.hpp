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
	float	fHealth;

	void AddToExtraDataList(ExtraDataList* apExtraList, TESHealthForm* apHealth);
};

ASSERT_SIZE(ContainerItemExtra, 0xC);