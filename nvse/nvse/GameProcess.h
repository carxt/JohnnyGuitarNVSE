#pragma once
#include "GameForms.h"
#include "Bethesda/HighProcess.hpp"
#include "Bethesda/HitData.hpp"

class BSTempEffect;
class NiBSBoneLODController;
struct CombatTarget;
class NiBSplineCompTransformInterpolator;

class Projectile;
class Explosion;
class bhkCharacterController;
struct DetectionData;

class Animation;
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
	NiPointer<NiControllerManager> spManager;			// 0D8
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

	void Save(BGSSaveFormBuffer* apBuffer) { ThisCall(0x49AB40, this, apBuffer); };
	void Load(BGSLoadFormBuffer* apBuffer) { ThisCall(0x49B050, this, apBuffer); };
};
static_assert(sizeof(Animation) == 0x12C);

class QueuedFile;
class BSFaceGenAnimationData;
class BSBound;
class NiTriShape;

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