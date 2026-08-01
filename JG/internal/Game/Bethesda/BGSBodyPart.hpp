#pragma once

#include "BaseFormComponent.hpp"
#include "BSStringT.hpp"
#include "TESModelPSA.hpp"
#include "Gamebryo/NiPoint3.hpp"

class BGSDebris;
class BGSExplosion;
class BGSImpactDataSet;
class NiAVObject;

class BGSBodyPart : public BaseFormComponent {
public:
	BGSBodyPart();
	~BGSBodyPart();

	struct ALIGN1 _BodyPartFlags {
		enum Flags : uint8_t {
			SEVERABLE				= 1u << 0,
			HAS_IK					= 1u << 1,
			IK_BIPED				= 1u << 2,
			EXPLODABLE				= 1u << 3,
			IS_HEAD					= 1u << 4,
			HEADTRACKING			= 1u << 5,
			EXPLODE_CHANCE_ABSOLUTE	= 1u << 6,
		};

		bool bSeverable				: 1;
		bool bHasIK					: 1;
		bool bIKBipded				: 1;
		bool bExplodable			: 1;
		bool bIsHead				: 1;
		bool bHeadTracking			: 1;
		bool bExplodeChanceAbsolute	: 1;
	};
	using BodyPartFlags = _BodyPartFlags::Flags;

	struct Data {
		float						fDamageMult;
		Bitfield<_BodyPartFlags>	ucFlags;
		uint8_t						ucType;
		uint8_t						ucHealthPercent;
		int8_t						cActorValue;
		uint8_t						ucToHitChance;
		uint8_t						ucExplosionChance;
		uint8_t						ucExplosionGenericDebrisCount;
		BGSDebris*					pExplosionGenericDebris;
		BGSExplosion*				pExplosion;
		float						fTrackingMaxAngle;
		float						fExplosionGenericDebrisScale;
		uint8_t						ucDismemberGenericDebrisCount;
		BGSDebris*					pDismemberGenericDebris;
		BGSExplosion*				pDismemberExplosion;
		float						fDismemberGenericDebrisScale;
		NiPoint3					kGorePos;
		NiPoint3					kGoreRot;
		BGSImpactDataSet*			pDismemberImpactDataSet;
		BGSImpactDataSet*			pExplosionImpactDataSet;
		uint8_t						ucDismemberDecalCount;
		uint8_t						ucExplosionDecalCount;
		float						fExplosionSpecialDebrisScale;
	};

	BSString			strNodeName;
	BSString			strTargetName;
	BSString			strIKStartNodeName;
	BSString			strPartName;
	BSString			strGoreObjectName;
	TESModel			kExplosionSpecialDebris;
	TESModelPSA			kPoseMatchingModel;
	Data				kData;

	const char* GetNodeName() const;
	void SetNodeName(const char* apName);

	const char* GetTargetName() const;
	void SetTargetName(const char* apName);

	const char* GetIKStartNodeName() const;
	void SetIKStartNodeName(const char* apName);

	const char* GetPartName() const;
	void SetPartName(const char* apName);

	const char* GetGoreObjectName() const;
	void SetGoreObjectName(const char* apName);

	const char* GetPoseMatchingModel() const;
	void SetPoseMatchingModel(const char* apPath);

	bool IsSeverablePart() const;
	bool HasIKData() const;
	bool IsIKBiped() const;
	bool IsExplodablePart() const;
	bool DoesHeadtracking() const;
	bool IsExplodeChanceAbsolute() const;

	BODY_PART_TYPE GetPartType() const;
	int8_t GetActorValue() const;

	void ShowLimb(LIMB_TYPE aeLimb, NiAVObject* apObject);
	void UnhideLimb(LIMB_TYPE aeLimb, NiAVObject* apObject);
};

ASSERT_SIZE(BGSBodyPart, 0xB0);