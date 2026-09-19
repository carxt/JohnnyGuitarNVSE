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

class BipedAnim {
public:
	struct Bone {
		bool	bExists;
		NiNode* pParent;
	};

	struct Object {
		union {
			TESForm*		pItem;
			TESObjectARMO*	pArmor;
			TESObjectWEAP*	pWeapon;
			TESRace*		pRace;
		};
		TESModel*	pPart;
		NiAVObject* pPartClone;
		bool		bSkinned;
	};

	NiNode*			pRoot;
	Bone			kBones[BIPED_BONE::COUNT];
	Object			kObjects[BIPED_OBJECT::COUNT];
	Object			kBufferedObjects[BIPED_OBJECT::COUNT];
	float			fWeaponOffset;
	TESObjectREFR*	pRequester;

	NiNode* GetParentBone(BIPED_BONE aeBone) const;

	void RemoveBipedWeapon();
#ifdef GAME
	void RemovePart(BIPED_OBJECT aeObject, bool abClear, void* apClearValue = nullptr);

	static void RunBiped3DDetach(NiAVObject* apObject);
#endif

	static void AttachToSkeleton(NiNode* apSkeleton, NiAVObject* apSkin, NiNode* apParentNode, bool abShowWarnings = false);
};

ASSERT_SIZE(BipedAnim, 0x2B4);