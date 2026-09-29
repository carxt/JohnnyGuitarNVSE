#pragma once

#include "TESBoundTreeObject.hpp"
#include "TESModelTree.hpp"
#include "TESIconTree.hpp"
#include "BGSDestructibleObjectForm.hpp"
#include "Gamebryo/NiTPrimitiveArray.hpp"
#include "Gamebryo/NiPoint2.hpp"

class TESObjectTREE : public TESBoundTreeObject, public TESModelTree, public TESIconTree, public BGSDestructibleObjectForm {
public:
	struct Data {
		float	fLeafCurvature;
		float	fLeafAngleMin;
		float	fLeafAngleMax;
		float	fBranchDimming;
		float	fLeafDimming;
		int32_t	iShadowRadius;
		float	fRockSpeed;
		float	fRustleSpeed;
	};

	virtual uint8_t		GetIndexForSeed(uint32_t auiSeed) const;
	virtual uint32_t	GetSeedAtIndex(uint8_t aucIndex) const;
	virtual Data*		GetData() const;
	virtual uint32_t	GetRandomSeed() const;
	virtual float		GetCurveScalar() const;
	virtual void		SetCurveScalar(float afValue);
	virtual float		GetMinimumLeafAngle() const;
	virtual void		SetMinimumLeafAngle(float afValue);
	virtual float		GetMaximumLeafAngle() const;
	virtual void		SetMaximumLeafAngle(float afValue);
	virtual float		GetBranchDimming() const;
	virtual void		SetBranchDimming(float afValue);
	virtual float		GetLeafDimming() const;
	virtual void		SetLeafDimming(float afValue);
	virtual float		GetShadowRadius() const;
	virtual void		SetShadowRadius(float afValue);
	virtual float		GetRockSpeed() const;
	virtual void		SetRockSpeed(float afValue);
	virtual float		GetRustleSpeed() const;
	virtual void		SetRustleSpeed(float afValue);
	virtual void		CreateDistant3D(NiPoint3* apLocArray, NiPoint3* apRotArray, float* apColorArray, uint32_t auiArraySize, uint32_t auiCellChunk, uint32_t auiCellKey, NiNode* apInstancedNode, NiNode* apFullNode);

	NiTPrimitiveArray<uint32_t>	kSpeedTreeSeeds;
	Data						kData;
	NiPoint2					kBillboardDimensions;

	TESFORM_TYPE(TESObjectTREE);
};

ASSERT_SIZE(TESObjectTREE, 0x94);