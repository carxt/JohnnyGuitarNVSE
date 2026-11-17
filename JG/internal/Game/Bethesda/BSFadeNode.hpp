#pragma once

#include "BSEnums.hpp"
#include "BSSimpleList.hpp"
#include "Gamebryo/NiNode.hpp"

class TESObjectREFR;
class BSNiBoundArray;

NiSmartPointer(BSFadeNode);

class BSFadeNode : public NiNode {
public:
	BSFadeNode();
	~BSFadeNode();

	float									fNearDistSqr;
	float									fFarDistSqr;
	float									fLastFadePct;
	float									fCurrentFade;
	float									fBoundRadius;
	float									fTimeSinceUpdate;
	LOD_MULT_TYPE							eLODMultType;
	int32_t									iFrameCounter;
	TESObjectREFR*							pReference;
	BSNiBoundArray*							pBoundArray;	// Unused, could repurpose? 
	BSSimpleList<class BSMultiBoundRoom*>	kParentRooms;   // Unused
	BSSimpleList<class BSPortal*>			kParentPortals; // Unused

	CREATE_OBJECT(BSFadeNode, 0xB4EAA0);
	NIRTTI_ADDRESS(0x11F9140);

	void SetRange(float afNearDist, float afFarDist);

	float GetFarDistanceSqr() const;

	float GetLastFadePercent() const;

	float GetBoundRadius() const;

	LOD_MULT_TYPE GetLODMultType() const;
	void SetLODMultType(LOD_MULT_TYPE aeType);

	TESObjectREFR* GetReference() const;
	void SetReference(TESObjectREFR* apRef);

	float GetMaxAlpha();

	bool IsVisible() const;

	void TurnFadeNodeOn();
	void TurnFadeNodeOff();

	static float GetFadeOutMultiplier(LOD_MULT_TYPE aeType);
	static void SetFadeOutMultiplier(LOD_MULT_TYPE aeType, float afMult);

	static bool GetFadeEnabled();
	static void SetFadeEnabled(bool abVal);
};

ASSERT_SIZE(BSFadeNode, 0xE4);