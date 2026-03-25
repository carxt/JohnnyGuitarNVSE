#include "GameExtraData.h"
#include "GameBSExtraData.h"
#include "GameApi.h"
#include "GameObjects.h"
#include "GameRTTI.h"
#include "GameScript.h"

static_assert(sizeof(ExtraHealth) == 0x10);
static_assert(sizeof(ExtraLock) == 0x10);
static_assert(sizeof(ExtraCount) == 0x10);
static_assert(sizeof(ExtraTeleport) == 0x10);

static_assert(sizeof(ExtraWorn) == 0x0C);
static_assert(sizeof(ExtraWornLeft) == 0x0C);
static_assert(sizeof(ExtraCannotWear) == 0x0C);

#if 1
static const uint32_t s_ExtraContainerChangesVtbl = 0x01015BB8;	//	0x0100fb78;
static const uint32_t s_ExtraWornVtbl = 0x01015BDC;
//static const uint32_t s_ExtraWornLeftVtbl							= 0x01015BE8;
static const uint32_t s_ExtraCannotWearVtbl = 0x01015BF4;

static const uint32_t s_ExtraOwnershipVtbl = 0x010158B4;	//	0x0100f874;
static const uint32_t s_ExtraRankVtbl = 0x010158CC;	//	0x0100f88c;
static const uint32_t s_ExtraActionVtbl = 0x01015BAC;
static const uint32_t s_ExtraFactionChangesVtbl = 0x01015F30;
static const uint32_t s_ExtraScriptVtbl = 0X1015914;

//static const uint32_t s_ExtraScript_init							= 0x0042C760;

static const uint32_t s_ExtraHealthVtbl = 0x010158E4;
static const uint32_t s_ExtraLockVtbl = 0x0101589C;
static const uint32_t s_ExtraCountVtbl = 0x010158D8;
static const uint32_t s_ExtraTeleportVtbl = 0x010158A8;
static const uint32_t s_ExtraWeaponModFlagsVtbl = 0x010159A4;

static const uint32_t s_ExtraHotkeyVtbl = 0x0101592C;

static const uint32_t s_ExtraSemaphore = 0x011C3920;
static const uint32_t s_SemaphoreWait = 0x0040FBF0;
static const uint32_t s_SemaphoreLeave = 0x0040FBA0;

#else
#error
#endif