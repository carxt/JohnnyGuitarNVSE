#pragma once
#include <GameUI.h>
#include <GameAPI.h>

class LoadedAreaBound;
struct ExtraAudioMarkerData;
struct BGSSaveLoadFileEntry;
class Sky;
class BSTempNodeManager;
class ImageSpaceModifierInstanceRB;
class NiRefObject;

struct DetectionData
{
	Actor* actor; // 00
	uint8_t detectionLevel; // 04
	uint8_t byte05; // 05
	uint8_t byte06; // 06
	uint8_t byte07; // 07
	int32_t detectionValue; // 08
	NiPoint3 detectionLocation; // 0C
	float fDetectionTimestamp; // 18
	uint8_t bForceResetLOSBuffer; // 1C
	uint8_t byte1D; // 1D
	bool inLOS; // 1E
	uint8_t byte1F; // 1F
	int32_t detectionModSneak;
};

struct FontHeightData
{
	float heightBase;
	float heightwGap;
};
// 54
struct FontInfo
{
	struct BufferData
	{
		float lineHeight; // 0000
		uint32_t unk0004[73]; // 0004
		uint32_t unk0128[458]; // 0128
		float baseHeight; // 0850
		float flt0854; // 0854
		float flt0858; // 0858
	};

	struct ButtonIcon;

	uint8_t isLoaded; // 00
	uint8_t pad01[3]; // 01
	char* filePath; // 04
	uint8_t fontID; // 08
	uint8_t pad09[3]; // 09
	NiTexturingProperty* texProp; // 0C
	uint32_t unk10[7]; // 10
	float flt2C; // 2C
	float flt30; // 30
	uint32_t unk34; // 34
	BufferData* bufferData; // 38
	uint32_t unk3C[2]; // 3C
	BSSimpleArray<ButtonIcon*> arr44; // 44
};

static_assert(sizeof(FontInfo) == 0x54);

// 164 (24)
class FontManager
{
public:
	FontManager();
	~FontManager();

	FontInfo* fontInfos[8]; // 00
	uint8_t byte20; // 20
	uint8_t pad21[3]; // 21
	FontInfo* extraFonts[80]; // 24

	//	outDims.x := width (pxl); outDims.y := height (pxl); outDims.z := numLines
	NiPoint3* GetStringDimensions(NiPoint3* outDims, const char* srcString, uint32_t fontID, uint32_t maxFlt = 0x7F7FFFFF,
	                               uint32_t startIdx = 0);
};
// 229C
class DebugText
{
public:
	DebugText();
	~DebugText();

	virtual void Unk_00(void);
	virtual void Unk_01(uint32_t arg1, uint32_t arg2);
	virtual uint32_t Unk_02(uint32_t arg1, uint32_t arg2, uint32_t arg3, uint32_t arg4, uint32_t arg5, uint32_t arg6);
	virtual uint32_t Unk_03(uint32_t arg1, uint32_t arg2, uint32_t arg3, uint32_t arg4);
	virtual void Unk_04(uint32_t arg1, uint32_t arg2, uint32_t arg3, uint32_t arg4, uint32_t arg5, uint32_t arg6);
	virtual uint32_t Unk_05(uint32_t arg1, uint32_t arg2, uint32_t arg3, uint32_t arg4, uint32_t arg5);
	virtual void Unk_06(uint32_t arg1, uint32_t arg2, uint32_t arg3, uint32_t arg4, uint32_t arg5);
	virtual uint32_t Unk_07(uint32_t arg1, uint32_t arg2, uint32_t arg3, uint32_t arg4, uint32_t arg5, uint32_t arg6, uint32_t arg7);
	virtual uint32_t Unk_08(uint32_t arg1, uint32_t arg2, uint32_t arg3, uint32_t arg4, uint32_t arg5);
	virtual uint32_t Unk_09(uint32_t arg1, uint32_t arg2, uint32_t arg3, uint32_t arg4, uint32_t arg5, uint32_t arg6);
	virtual uint32_t Unk_0A(uint32_t arg1);
	virtual void Unk_0B(uint32_t arg1, uint32_t arg2);

	struct DebugLine
	{
		float offsetX; // 00
		float offsetY; // 04
		uint32_t isVisible; // 08
		NiNode* node; // 0C
		BSString text; // 10
		float flt18; // 18	Always -1.0
		NiColorA color; // 1C
	};

	DebugLine lines[200]; // 0004
	uint32_t unk2264[14]; // 2264

	static DebugText* GetSingleton();
	DebugLine* GetDebugInput();
};

static_assert(sizeof(DebugText) == 0x229C);

enum
{
	kMusicState_Pause = 1 << 2,
	kMusicState_Stop = 1 << 3,
	kMusicState_Play = 1 << 4,
	kMusicState_Loop = 1 << 5,
};

// 288
struct PlayingMusic
{
	char track1Path[MAX_PATH]; // 000
	void* ptr104; // 104
	char track2Path[MAX_PATH]; // 108
	uint32_t unk20C; // 20C
	float flt210; // 210
	float flt214; // 214
	float flt218; // 218
	float flt21C; // 21C
	uint8_t track1Flags; // 220
	uint8_t track2Flags; // 221
	uint8_t pad222[2]; // 222
	uint32_t unk224; // 224
	uint32_t unk228[8]; // 228
	float flt248; // 248
	float flt24C; // 24C
	float flt250; // 250
	float flt254; // 254
	uint32_t unk258; // 258
	uint32_t unk25C[8]; // 25C
	uint32_t track1Active; // 27C
	uint32_t unk280; // 280
	MediaLocationController* medLocCtrl; // 284
};

static_assert(sizeof(PlayingMusic) == 0x288);

struct PCMiscStat
{
	const char* name;
	uint32_t level;
};

// 08
struct TypeSignature
{
	char signature[8];
};

class ImageSpaceModifierInstanceForm;

// 48
struct VATSCameraData
{
	tList<VATSTargetInfo> targetsList; // 00
	uint32_t mode; // 08
	uint32_t cameraShots; // 0C
	BGSCameraShot* camShot; // 10
	float flt14; // 14
	float flt18; // 18
	uint32_t unk1C; // 1C
	uint32_t unk20; // 20
	TESIdleForm* attackAnim; // 24
	ImageSpaceModifierInstanceForm* isModInstForm; // 28
	ImageSpaceModifierInstanceRB* isModInstRB; // 2C
	uint32_t unk30; // 30
	NiPointLight* niPointLight; // 34
	uint8_t byte38; // 38
	uint8_t pad39[3]; // 39
	uint32_t numKills; // 3C
	uint32_t unk40; // 40
	uint32_t unk44; // 44
};

static_assert(sizeof(VATSCameraData) == 0x48);

// 10
struct SystemColorManager
{
	// 0C
	class SystemColor
	{
	public:
		SystemColor();
		~SystemColor();

		virtual void Destructor(bool doFree);
		virtual uint32_t GetColor();
		virtual void SetColor(uint32_t newColor);
		virtual bool IsHard();
		virtual bool IsSoft();

		BSString traitName;

		void SetColorRGB(uint32_t r, uint32_t g, uint32_t b)
		{
			this->SetColor(((r & 0xFF) << 16) + ((g & 0xFF) << 8) + (b & 0xFF));
		}
	};

	// 10
	class HardSystemColor : public SystemColor
	{
	public:
		HardSystemColor();
		~HardSystemColor();

		uint32_t color; // 0C
	};

	// 10
	class SoftSystemColor : public SystemColor
	{
	public:
		SoftSystemColor();
		~SoftSystemColor();

		uint32_t* setting; // 0C
	};

	DList<SystemColor> sysColors;
	uint32_t unk0C;

	static SystemColorManager* GetSingleton() { return ThisCall<SystemColorManager*>(0x718B60, nullptr); }
	uint32_t GetColor(uint32_t type) { return ThisCall<uint32_t>(0x7190A0, this, type); }
};

enum MiscStatCode
{
	kMiscStat_QuestsCompleted,
	kMiscStat_LocationsDiscovered,
	kMiscStat_PeopleKilled,
	kMiscStat_CreaturesKilled,
	kMiscStat_LocksPicked,
	kMiscStat_ComputersHacked,
	kMiscStat_StimpaksTaken,
	kMiscStat_RadXTaken,
	kMiscStat_RadAwayTaken,
	kMiscStat_ChemsTaken,
	kMiscStat_TimesAddicted,
	kMiscStat_MinesDisarmed,
	kMiscStat_SpeechSuccesses,
	kMiscStat_PocketsPicked,
	kMiscStat_PantsExploded,
	kMiscStat_BooksRead,
	kMiscStat_HealthFromStimpaks,
	kMiscStat_WeaponsCreated,
	kMiscStat_HealthFromFood,
	kMiscStat_WaterConsumed,
	kMiscStat_SandmanKills,
	kMiscStat_ParalyzingPunches,
	kMiscStat_RobotsDisabled,
	kMiscStat_TimesSlept,
	kMiscStat_CorpsesEaten,
	kMiscStat_MysteriousStrangerVisits,
	kMiscStat_DoctorBagsUsed,
	kMiscStat_ChallengesCompleted,
	kMiscStat_MissFortunateOccurrences,
	kMiscStat_Disintegrations,
	kMiscStat_HaveLimbsCrippled,
	kMiscStat_SpeechFailures,
	kMiscStat_ItemsCrafted,
	kMiscStat_WeaponModifications,
	kMiscStat_ItemsRepaired,
	kMiscStat_TotalThingsKilled,
	kMiscStat_DismemberedLimbs,
	kMiscStat_CaravanGamesWon,
	kMiscStat_CaravanGamesLost,
	kMiscStat_BarterAmountTraded,
	kMiscStat_RouletteGamesPlayed,
	kMiscStat_BlackjackGamesPlayed,
	kMiscStat_SlotsGamesPlayed,
};

enum SpecialInputCode
{
	kInputCode_Backspace = 0x80000000,
	kInputCode_ArrowLeft = 0x80000001,
	kInputCode_ArrowRight = 0x80000002,
	kInputCode_ArrowUp = 0x80000003,
	kInputCode_ArrowDown = 0x80000004,
	kInputCode_Home = 0x80000005,
	kInputCode_End = 0x80000006,
	kInputCode_Delete = 0x80000007,
	kInputCode_Enter = 0x80000008,
	kInputCode_PageUp = 0x80000009,
	kInputCode_PageDown = 0x8000000A
};

#ifdef GAME
#include "Bethesda/CombatTimer.hpp"

struct CombatState
{
	uint8_t byte000;
	uint8_t gap001[3];
	uint32_t flags;
	float fleeThreshold008;
	TESObjectWEAP* weaponsByCombatWeaponType[6];
	BSSimpleArray<void*> weapons_Array024;
	TESObjectWEAP* weap034;
	uint32_t availableCombatWeaponTypesFlags;
	float maxDPSPerWeaponType[7];
	float meleeDPS_58;
	float rangedDPS_5C;
	float unk060;
	float unk064;
	float distance068;
	uint32_t unk06C;
	uint8_t isInLineOfSight;
	uint8_t forceResetCombatLOSBufferTimer;
	uint8_t isTargetBlocked_dontIgnoreBlockedTarget072;
	uint8_t isTargetFlushed;
	uint8_t isTargetSpaceDifferent;
	uint8_t byte075;
	uint8_t byte076;
	uint8_t forceInventoryUpdate;
	BGSExplosion* dangerousExplosiveToThrow;
	uint32_t unk07C;
	float combatThreatScore;
	NiPoint3 pt084;
	uint32_t executionFlags090;
	float combatDetectionBufferTimer;
	float combatLOSBufferTimer;
	float timerLastFiredProjectile;
	float timer_maybeFlee0A0;
	float timerProjectile0A4;
	CombatTimer timer0A8;
	CombatTimer timer0B0;
	CombatTimer timer0B8;
	float timer0C0;
	void* ptr0C4;
	uint8_t initialConfidence;
	uint8_t currentConfidence;
	uint8_t gap0CA[2];
	float combatConfidenceModifier;
	float ownerThreatLevel;
	float ownerDPS;
	uint8_t byte0D8;
	uint8_t gap0D9[3];
	uint32_t doorFleeRefID;
	uint32_t lastDoorFleeTime;
	void* ptr0E4[2];
	void* ptr0EC;
	uint32_t unk0F0;
	uint32_t unk0F4;
	uint32_t unk0F8;
	uint32_t unk0FC;
	uint32_t unk100;
	uint32_t unk104;
	float unk108;
	BSSimpleArray<void*> PathingCoverLocation_Array10C;
	uint32_t unk11C;
	uint32_t unk120;
	uint32_t unk124;
	void* ptr128;
	uint32_t unk12C;
	uint32_t unk130;
	uint32_t unk134;
	uint32_t unk138;
	uint32_t unk13C;
	uint32_t unk140;
	float unk144;
	BSSimpleArray<void*> PathingCoverLocation_Array148;
	uint32_t unk158;
	uint32_t unk15C;
	uint32_t unk160;
	BSSimpleArray<void*> UnreachableCoverLocation_Array164;
	BSSimpleArray<void*> UnreachableLocation_Array174;
	float timer184;
	uint8_t byte188;
	uint8_t gap189[3];
	void* ptr18C;
	tList<void*>* restoreItemsList;
	tList<void*>* buffItemsList;
	tList<void*>* targetObjectItemsList;
	tList<void*>* ammoItemsList;
	tList<void*>* weaponItemsList;
	TESBoundObject* ingestiblesRestoreAndBuff[2];
	CombatTimer combatRestoreAndBuffItemTimers[2];
	TESForm* combatItem1BC;
	Actor* actor1C0;
	CombatController* cmbtCtrl;
	uint8_t byte1C8_maybeInitializing;
	uint8_t byte1C9;
	uint8_t gap1CA[2];
	CombatTimer timer1CC;
	CombatTimer findBetterWeaponTimer;
	CombatTimer explosiveProjectileBlockedResetTimer;
	CombatTimer avoidThreatsTimer;
	CombatTimer takeCoverTimer;
	CombatTimer timer1F4;
	CombatTimer timer1FC;
	CombatTimer strengthUpdateTimer;
	CombatTimer combatThreatRatioTimer;
	CombatTimer embeddedWeaponSwitchTimer;
	CombatTimer inventoryUpdateTimer;
	uint32_t ptr224;
	int32_t unk228;
};

static_assert(sizeof(CombatState) == 0x22C);
#endif