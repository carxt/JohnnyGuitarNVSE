#pragma once
#include "GameForms.h"
#include "GameObjects.h"
#include "Bethesda/MiddleHighProcess.hpp"
#include "Bethesda/HitData.hpp"

class BSTempEffect;
class NiBSBoneLODController;
struct CombatTarget;
class NiBSplineCompTransformInterpolator;

class Projectile;
class Explosion;
class bhkCharacterController;
struct DetectionData;
class NiControllerManager;
class AnimSequenceBase;

// 100+
class Animation {
public:
	struct Unk124
	{
		struct Unk18
		{
			uint32_t			unk00[9];
			uint32_t			unk24;
		};

		uint32_t			unk00[6];
		Unk18			*unk18;
	};

	struct Unk128
	{
		uint32_t			unk00[11];
		TESIdleForm		*idle2C;
	};

	uint32_t							unk000;				// 000
	Actor							*actor;				// 004
	NiNode							*nSceneRoot;		// 008
	NiNode							*nBip01;			// 00C
	uint32_t							unk010;				// 010
	float							flt014;				// 014
	float							flt018;				// 018
	uint32_t							unk01C;				// 01C
	float							flt020;				// 020
	uint32_t							unk024;				// 024
	NiNode							*nPelvis;			// 028
	NiNode							*nBip01Copy;		// 02C
	NiNode							*nLForearm;			// 030
	NiNode							*nHead;				// 034
	NiNode							*nWeapon;			// 038
	uint32_t							unk03C[2];			// 03C
	NiNode							*nNeck1;			// 044
	float							unk048;				// 048
	uint16_t						groupIDs[8];		// 04C
	int32_t							sequenceState1[8];	// 05C
	uint32_t						uiLoopCounts[8];	// 07C
	uint32_t						unk09C[12];			// 09C
	float							flt0CC;				// 0CC
	float							flt0D0;				// 0D0
	uint32_t							unk0D4;				// 0D4
	NiControllerManager				*unk0D8;			// 0D8
	NiTPointerMap<uint16_t, AnimSequenceBase*>* unk0DC;			// 0DC
	BSAnimGroupSequence				*animSequence[8];	// 0E0
	BSAnimGroupSequence				*animSeq100;		// 100
	uint32_t							unk104;				// 104
	uint32_t							unk108;				// 108
	float							flt10C;				// 10C
	float							flt110;				// 110
	float							flt114;				// 114
	float							flt118;				// 118
	float							flt11C;				// 11C
	uint32_t							unk120;				// 120
	Unk124							*unk124;			// 124
	Unk128							*unk128;			// 128

	void BlendOut(uint32_t aeGroupSection, bool abIronSights) {
		ThisCall(0x4994F0, this, aeGroupSection, abIronSights);
	}

	void ReloadTargets(bool abReload) {
		ThisCall(0x499240, this, abReload);
	}
};
static_assert(sizeof(Animation) == 0x12C);

class QueuedFile;
class BSFaceGenAnimationData;
class BSBound;
class NiTriShape;

class HighProcess : public MiddleHighProcess {
public:
	HighProcess();
	~HighProcess();

	enum {
		kAnimAction_None = -1,
		kAnimAction_Equip_Weapon,
		kAnimAction_Unequip_Weapon,
		kAnimAction_Attack,
		kAnimAction_Attack_Follow_Through,
		kAnimAction_Attack_Latency,
		kAnimAction_Attack_Throw_Attach,
		kAnimAction_Attack_Throw_Release,
		kAnimAction_Block,
		kAnimAction_Stagger,
		kAnimAction_Reload,
		kAnimAction_Dodge,
		kAnimAction_Wait_For_Lower_Body_Anim,
		kAnimAction_Wait_For_Special_Idle,
		kAnimAction_Force_Script_Anim
	};

	tList<DetectionData>* detectedActors;	// 25C
	tList<DetectionData>* detectingActors;	// 260
	void* ptr264;			// 264
	void* ptr268;			// 268
	void* ptr26C;			// 26C
	uint32_t								unk270;				// 270
	tList<CombatTarget>					list274;			// 274
	tList<void>							list27C;			// 27C
	tList<void>							list284;			// 284
	tList<void>							list28C;			// 28C
	float								flt294;				// 294
	float								flt298;				// 298
	uint32_t								unk29C;				// 29C
	float								flt2A0;				// 2A0
	uint32_t								unk2A4;				// 2A4
	float								flt2A8;				// 2A8
	uint32_t								unk2AC;				// 2AC
	float								flt2B0;				// 2B0
	float								flt2B4;				// 2B4
	float								flt2B8;				// 2B8
	float								flt2BC;				// 2BC
	uint32_t								unk2C0;				// 2C0
	uint32_t								unk2C4;				// 2C4
	float								flt2C8;				// 2C8
	uint32_t								unk2CC;				// 2CC
	float								flt2D0;				// 2D0
	float								flt2D4;				// 2D4
	float								flt2D8;				// 2D8
	uint32_t								unk2DC;				// 2DC
	float								flt2E0;				// 2E0
	NiBSBoneLODController* ptr2E4;			// 2E4
	uint32_t								unk2E8;				// 2E8
	int16_t								currentAction;		// 2EC
	uint8_t								pad2EE[2];			// 2EE
	BSAnimGroupSequence* currentSequence;	// 2F0
	uint32_t								unk2F4;				// 2F4
	float								flt2F8;				// 2F8
	uint32_t								unk2FC[5];			// 2FC
	float								flt310;				// 310
	uint32_t								unk314[7];			// 314
	float								dyingTimer;				// 330
	float								flt334;				// 334
	float								flt338;				// 338
	float								diveBreath;			// 33C
	uint32_t								unk340;				// 340
	float								flt344;				// 344
	uint32_t								unk348;				// 348
	float								flt34C;				// 34C
	TESIdleForm* idleForm350;		// 350
	uint32_t								unk354[4];			// 354
	NiBSplineCompTransformInterpolator** ptr364;			// 364
	uint32_t								unk368[4];			// 368
	float								flt378;				// 378
	float								flt37C;				// 37C
	uint32_t								unk380;				// 380
	float								flt384;				// 384
	float								flt388;				// 388
	tList<void>							list38C;			// 38C
	tList<void>							list394;			// 394
	uint32_t								unk39C;				// 39C
	uint32_t								unk3A0;				// 3A0
	float								flt3A4;				// 3A4
	uint32_t								unk3A8[5];			// 3A8
	float								flt3BC;				// 3BC
	float								flt3C0;				// 3C0
	float								lightAmount;		// 3C4
	float								flt3C8;				// 3C8
	uint32_t								unk3CC[7];			// 3CC
	uint32_t								fadeType;			// 3E8
	float								delayTime;			// 3EC
	uint32_t								unk3F0;				// 3F0
	uint32_t								unk3F4;				// 3F4
	uint32_t								unk3F8[3];			// 3F8
	Actor* combatTarget;		// 404
	uint32_t								unk408[4];			// 408
	float								flt418;				// 418
	TESObjectREFR* packageTarget;		// 41C
	uint32_t								unk420;				// 420
	uint32_t								queuedIdleFlags;	// 424
	uint32_t								unk428;				// 428
	float								flt42C;				// 42C
	uint32_t								unk430;				// 430
	bhkShapePhantom* ptr434;			// 434
	uint32_t								unk438;				// 438
	float								unk43C;				// 43C
	float								radsSec440;			// 440
	uint8_t								plantedExplosive;	// 444
	uint8_t								pad445[3];			// 445
	float								flt448;				// 448
	uint32_t								unk44C;				// 44C
	float								flt450;				// 450
	uint32_t								unk454[6];			// 454
};
static_assert(sizeof(HighProcess) == 0x46C);

// 160
struct ProcessLists {
	uint32_t					unk000;				// 000
	NiTPrimitiveArray<MobileObject*>	objects;			// 004
	uint32_t					beginOffsets[4];	// 014	0: High, 1: Mid-High, 2: Mid-Low, 3: Low
	uint32_t					endOffsets[4];		// 024
	uint32_t					unk034[11];			// 034
	tList<BSTempEffect>		tempEffects;		// 060
	uint32_t					unk068[6];			// 068
	tList<Actor>			highActors;			// 080
	uint32_t					unk088[54];			// 088

	static ProcessLists* GetSingleton() {
		return reinterpret_cast<ProcessLists*>(0x11E0E80);
	};

	bool AreHostileActorsNear(bool abInterior) {
		return ThisCall<bool>(0x9764A0, this, abInterior);
	}
};