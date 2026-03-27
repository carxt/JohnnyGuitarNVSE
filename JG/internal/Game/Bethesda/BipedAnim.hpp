#pragma once

#include "BSEnums.hpp"

class TESObjectREFR;
class TESForm;
class TESModel;
class TESObjectARMO;
class TESObjectWEAP;
class TESRace;
class NiNode;
class NiAVObject;

struct BIPOBJECT {
	union {
		TESForm*		pItem;
		TESObjectARMO*	pArmor;
		TESObjectWEAP*	pWeapon;
		TESRace*		pRace;
	};
	TESModel*	pPart;
	NiAVObject*	pPartClone;
	bool		bSkinned;
};

struct BIPBONE {
	bool	bExists;
	NiNode* pParent;
};

class BipedAnim {
public:
	BipedAnim(TESObjectREFR* apRef, NiNode* apRoot);
	~BipedAnim();

	NiNode*			pRoot;
	BIPBONE			kBones[BIPED_BONE::COUNT];
	BIPOBJECT		kObjects[BIPED_OBJECT::COUNT];
	BIPOBJECT		kBufferedObjects[BIPED_OBJECT::COUNT];
	float			fWeaponOffset;
	TESObjectREFR*	pRequester;

	NiNode* GetParentBone(BIPED_BONE aeBone) const;

	void RemoveBipedWeapon();
	void RemovePart(uint32_t aeObject, bool abClear, void* apClearValue = nullptr);
};

ASSERT_SIZE(BipedAnim, 0x2B4);