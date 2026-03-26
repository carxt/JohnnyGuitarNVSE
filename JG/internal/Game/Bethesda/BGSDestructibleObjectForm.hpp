#pragma once

#include "BaseFormComponent.hpp"

class NiAVObject;
class BGSExplosion;
class BGSDebris;
class TESModelTextureSwap;
class TESForm;
class TESObjectREFR;

struct DestructibleObjectStage {
	struct ALIGN2 _DestructibleObjectStageFlags {
		enum Flags : uint16_t {
			CAP_DAMAGE		= 1u << 0,
			DISABLE_OBJECT	= 1u << 1,
			DESTROY_OBJECT	= 1u << 2,
		};

		bool bCapDamage		: 1;
		bool bDisableObject : 1;
		bool bDestroyObject : 1;
	};
	using DestructibleObjectStageFlags = _DestructibleObjectStageFlags::Flags;

	uint8_t									ucModelDamageStage;
	uint8_t									ucHealthPercentage;
	Bitfield<_DestructibleObjectStageFlags>	usFlags;
	uint32_t								uiSelfDamagePerSecond;
	BGSExplosion*							pExplosion;
	BGSDebris*								pDebris;
	uint32_t								uiDebrisCount;
	TESModelTextureSwap*					pReplacementModel;
};

ASSERT_SIZE(DestructibleObjectStage, 0x18);

struct DestructibleObjectData {
	struct ALIGN1 _Flags {
		enum Flags : uint8_t {
			VATS_TARGETABLE = 1u << 0,
		};
		
		bool bVATSTargetable : 1;
	};

	uint32_t					uiHealth;
	uint8_t						ucNumStages;
	Bitfield<_Flags>			ucFlags;
	DestructibleObjectStage**	pStagesArray;
};

class BGSDestructibleObjectForm : public BaseFormComponent {
public:
	BGSDestructibleObjectForm();
	~BGSDestructibleObjectForm();

	DestructibleObjectData* pData;

	DestructibleObjectData* GetData() const;

	uint32_t GetMaxHealth(TESObjectREFR* apRef) const;

	DestructibleObjectStage* GetStage(uint32_t auiIndex) const;

	bool GetTargetableInVATS() const;

	static int32_t CalcDestructionStage(TESObjectREFR* apRef);

	static uint32_t GetSelfDamage(TESObjectREFR* apRef, float afHealth);

	static TESModelTextureSwap* GetModelSwap(TESForm* apForm, int32_t aiIndex);

	static int32_t GetModelSwapIndex(TESForm* apForm, TESModelTextureSwap* apModelSwap);

	static void UpdateDamageStageNodes(NiAVObject* apObject, uint32_t auiDamageLevel);

	static void ClearDestruction(TESObjectREFR* apRef);

	static BGSDestructibleObjectForm* GetDestructionForm(const TESForm* apForm);
};

ASSERT_SIZE(BGSDestructibleObjectForm, 0x8);