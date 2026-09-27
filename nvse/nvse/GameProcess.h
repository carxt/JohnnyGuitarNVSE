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