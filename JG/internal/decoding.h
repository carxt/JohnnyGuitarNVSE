#pragma once
#include <GameSound.h>
#include <GameUI.h>
#include <GameAPI.h>

class LoadedAreaBound;
struct ExtraAudioMarkerData;
struct BGSSaveLoadFileEntry;
class Sky;
class BSTempNodeManager;
class ImageSpaceModifierInstanceRB;
class NiRefObject;
struct NavMeshClosedDoorInfo {};

// 34
class BGSPrimitive
{
public:
	BGSPrimitive();
	~BGSPrimitive();

	virtual void Destructor(bool doFree);
	virtual void Unk_01(void);
	virtual void Unk_02(void);
	virtual void Unk_03(void);
	virtual void Unk_04(void);
	virtual void Unk_05(void);

	uint32_t type; // 04
	float unk08[4]; // 08
	float bounds[3]; // 18
	NiRefObject* unk24; // 24
	NiRefObject* unk28; // 28
	NiRefObject* unk2C; // 2C
	uint32_t unk30; // 30
};

// 34
class BGSPrimitivePlane : public BGSPrimitive
{
public:
	BGSPrimitivePlane();
	~BGSPrimitivePlane();
};

// 4C
class BGSPrimitiveBox : public BGSPrimitive
{
public:
	BGSPrimitiveBox();
	~BGSPrimitiveBox();

	uint32_t unk34[6]; // 34
};

// 34
class BGSPrimitiveSphere : public BGSPrimitive
{
public:
	BGSPrimitiveSphere();
	~BGSPrimitiveSphere();
};

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


// 08
class SkyObject {
public:
	virtual				~SkyObject();
	virtual NiNode*		GetRoot() const;
	virtual void		Initialize(NiNode* apRoot);
	virtual void		Update(Sky* apSky, float afValue);

	NiPointer<NiNode> spRoot;
};

ASSERT_SIZE(SkyObject, 0x8)

class Atmosphere : public SkyObject {
public:
	virtual void	InitializeAlt(NiNode* apRoot, BSFogProperty* apFogProperty);

	NiPointer<NiNode>			spAtmosphere;
	NiPointer<BSFogProperty>	spFog;
	NiPointer<NiNode>			spSkyQuadNode;
	NiRefObjectPtr				spSkyQuad;
	bool						bUpdateFogDistance;
};

ASSERT_SIZE(Atmosphere, 0x1C);

class Stars : public SkyObject {
public:
	NiPointer<NiNode>	spStars;
	float				fAlpha;
};

ASSERT_SIZE(Stars, 0x10);

// 2C
class Sun : public SkyObject
{
public:
	Sun();
	~Sun();

	NiBillboardNode* node08; // 08
	NiBillboardNode* node0C; // 0C
	NiTriShape* shape10; // 10
	NiTriShape* shape14; // 14
	uint32_t unk18; // 18
	NiDirectionalLight* sunLight; // 1C	Same as g_TES->directionalLight
	float flt20; // 20
	uint8_t byte24; // 24
	uint8_t byte25; // 25
	uint8_t byte26; // 26
	uint8_t byte27; // 27
	BSShaderAccumulator* shaderAccum; // 28
};

// 5C
class Clouds : public SkyObject
{
public:
	Clouds();
	~Clouds();

	NiPointer<NiGeometry>	spClouds[4];
	NiPointer<NiTexture>	spTransTexture[4];
	NiColor					kColors[4];
	uint16_t				usNumLayers;
	bool					bForceTransTextureUpdate;

	void ForceTransTextureUpdate() {
		bForceTransTextureUpdate = true;
	}

	void RemoveTextures() {
		ThisCall(0x6349E0, this);
	}

	void ClearTransTextures() {
		ThisCall(0x634930, this);
	}
};

enum MoonUpdateStatus : __int32
{
	US_NOT_REQUIRED = 0x0,
	US_WHEN_CULLED = 0x1,
	US_INITIALIZE = 0x2,
};

// 7C
class Moon : public SkyObject
{
public:
	Moon();
	~Moon();

	virtual void Refresh(NiNode* niNode, const char* moonStr);


	NiRefObject* spMoonNode;
	NiRefObject* spShadowNode;
	NiRefObject* spMoonMesh;
	NiRefObject* spShadowMesh;
	uint32_t fullMoonPath;
	uint32_t unk01C;
	uint32_t threeWanPath;
	uint32_t unk024;
	uint32_t halfWanPath;
	uint32_t unk02C;
	uint32_t oneWanPath;
	uint32_t unk034;
	uint32_t unk038;
	uint32_t unk03C;
	uint32_t oneWaxPath;
	uint32_t unk044;
	uint32_t halfWaxPath;
	uint32_t unk04C;
	uint32_t threeWaxPath;
	uint32_t unk054;
	float angleFadeStart;
	float angleFadeEnd;
	float shadowEarlyFade;
	float speed;
	float zOffset;
	uint32_t size;
	MoonUpdateStatus eUpdateMoonTexture;
	float unk074;
	float lastUpdateHour;

	static constexpr AddressPtr<uint32_t, 0x11CCA80> eCurrentPhase;
};

// 18
class Precipitation
{
public:
	Precipitation();
	virtual ~Precipitation();

	NiNode* node04; // 04
	NiNode* node08; // 08
	uint32_t unk0C; // 0C
	float unk10; // 10
	uint32_t unk14; // 14
};

// 1C
class ImageSpaceModifierInstance : public NiObject
{
public:
	ImageSpaceModifierInstance();
	~ImageSpaceModifierInstance();

	virtual void Unk_23(void);
	virtual void Unk_24(void);
	virtual void Unk_25(void);
	virtual void Unk_26(uint32_t arg);

	uint8_t hidden; // 08
	uint8_t pad09[3]; // 09
	float percent; // 0C
	NiObject* obj10; // 10
	float flt14; // 14
	uint32_t unk18; // 18
};

// 30
class ImageSpaceModifierInstanceForm : public ImageSpaceModifierInstance
{
public:
	ImageSpaceModifierInstanceForm();
	~ImageSpaceModifierInstanceForm();

	TESImageSpaceModifier* imageSpace; // 1C
	TESImageSpaceModifier* lastImageSpace; // 20
	float lastStrength; // 24
	NiObject* lastTarget; // 28
	float transitionTime; // 2C
};

// 30
class ImageSpaceModifierInstanceDOF : public ImageSpaceModifierInstance
{
public:
	ImageSpaceModifierInstanceDOF();
	~ImageSpaceModifierInstanceDOF();

	float flt1C; // 1C
	float flt20; // 20
	float flt24; // 24
	float flt28; // 28
	uint32_t unk2C; // 2C
};

// 44
class ImageSpaceModifierInstanceDRB : public ImageSpaceModifierInstance
{
public:
	ImageSpaceModifierInstanceDRB();
	~ImageSpaceModifierInstanceDRB();

	float flt1C; // 1C
	float flt20; // 20
	float flt24; // 24
	float flt28; // 28
	float flt2C; // 2C
	uint32_t unk30; // 30
	uint32_t unk34; // 34
	float flt38; // 38
	float flt3C; // 3C
	uint32_t unk40; // 40
};

class SkyTextureManager {
public:
};

// 138
struct SPEC_EMPTY_BASES SkySound : public BSMemObject {
	BSSoundHandle	kHandle;
	TESWeather*		pWeather;
	uint32_t		uiType;
	uint32_t		uiFormID;
	uint32_t		uiData;

	static constexpr AddressPtr<uint8_t, 0x11CCB74> ucThunderCount;
};

class Sky {
public:
	Sky();
	virtual ~Sky();

	struct _SkyObjectType {
		enum Type {
			SUNGLARE	= 1,
			CLOUDS		= 3,
			STARS		= 5,
			MOON		= 7,
		};
	};
	using SkyObjectType = _SkyObjectType::Type;

	struct _SkyColor {
		enum Color {
			SKY_UPPER		= 0,
			FOG				= 1,
			CLOUDS_LOWER	= 2,
			AMBIENT			= 3,
			SUNLIGHT		= 4,
			SUN				= 5,
			STARS			= 6,
			SKY_LOWER		= 7,
			HORIZON			= 8,
			CLOUDS_UPPER	= 9,
			COUNT,
		};
	};
	using SkyColor = _SkyColor::Color;

	struct _FogDistance {
		enum Distance {
			FOG_NEAR		= 0,
			FOG_FAR			= 1,
			FOG_WATER_NEAR	= 2,
			FOG_WATER_FAR	= 3,
			COUNT			= 4,
		};
	};
	using FogDistance = _FogDistance::Distance;

	struct _Mode {
		enum Mode {
			NONE			= 0,
			INTERIOR		= 1,
			FAKE_EXTERIOR	= 2,
			FULL			= 3,
			COUNT,
		};
	};
	using Mode = _Mode::Mode;

	struct ALIGN4 _Flags {
		enum Flags : uint32_t {
			REFRESH_WEATHER			= 1u << 0,
			FORCED_UPDATE			= 1u << 1,
			UNDERWATER				= 1u << 2,
			REFRESH_ACCELERATION	= 1u << 3,
			FAST_TRAVEL				= 1u << 4,
			REFRESH_MOON			= 1u << 5,
			REFRESH_CLIMATE			= 1u << 6,
			//								7
			REFRESH_SUNRISE_BEGIN	= 1u << 8,
			REFRESH_SUNRISE_END		= 1u << 9,
			REFRESH_SUNSET_BEGIN	= 1u << 10,
			REFRESH_SUNSET_END		= 1u << 11,
			REFRESH_SUNRISE_COLOR	= 1u << 12,
			REFRESH_SUNSET_COLOR	= 1u << 13,
		};

		bool bRefreshWeather		: 1;
		bool bForcedUpdate			: 1;
		bool bUnderwater			: 1;
		bool bRefreshAcceleration	: 1;
		bool bFastTravel			: 1;
		bool bRefreshMoon			: 1;
		bool bRefreshClimate		: 1;
		bool bHideSky				: 1;
		bool bRefreshSunriseBegin	: 1;
		bool bRefreshSunriseEnd		: 1;
		bool bRefreshSunsetBegin	: 1;
		bool bRefreshSunsetEnd		: 1;
		bool bRefreshSunsetColor	: 1;
	};
	using Flags = _Flags::Flags;

	NiPointer<BSMultiBoundNode>		spRoot;
	NiPointer<NiNode>				spMoonsRoot;
	TESClimate*						pCurrentClimate;
	TESWeather*						pCurrentWeather;
	TESWeather*						pLastWeather;
	TESWeather*						pDefaultWeather;
	TESWeather*						pOverrideWeather;
	Atmosphere*						pAtmosphere;
	Stars*							pStars;
	Sun*							pSun;
	Clouds*							pClouds;
	Moon*							pMasser;
	Moon*							pSecunda;
	Precipitation*					pPrecipitation;
	NiColor							kColors[SkyColor::COUNT];
	NiColor							kWaterFogColor;
	NiColor							kSunSpecularColor;
	float							fWindSpeed;
	float							fWindAngle;
	float							fFogDistances[FogDistance::COUNT];
	float							fFogHeight;
	float							fFogPower;
	float							fCurrentGameHour;
	float							fLastWeatherUpdate;
	float							fCurrentWeatherPct;
	Mode							eMode;
	BSSimpleList<SkySound*>*		pSkySoundList;
	float							fFlash;
	uint32_t						uiFlashTime;
	uint32_t						uiLastMoonPhaseUpdate;
	float							fWindowReflectionTimer;
	float							fAccelBeginPct;
	SkyTextureManager				kTextureManager;
	Bitfield<_Flags>				uiFlags;
	ImageSpaceModifierInstanceForm* pFadeInIMODCurrent;
	ImageSpaceModifierInstanceForm* pFadeOutIMODCurrent;
	ImageSpaceModifierInstanceForm* pFadeInIMODLast;
	ImageSpaceModifierInstanceForm* pFadeOutIMODLast;
	float							fHighNoon;
	float							fMidnightWax;
	float							fMidnightWane;

	static Sky* GetSingleton() {
		return *reinterpret_cast<Sky**>(0x11DEA20);
	}

	void ReloadAllTextures() {
		ThisCall(0x63E2F0, this);
	}

	void ResetWeather() {
		ThisCall(0x63D060, this);
	}

	void ActivateWeatherSounds(TESWeather* apWeather) {
		ThisCall(0x63DDB0, this, apWeather);
	}

	void Update(float afDelta) {
		ThisCall(0x63AC70, this, afDelta);
	}

	void UpdateHDRValues() {
		ThisCall(0x63EF20, this);
	}

	bool GetIsRaining() {
		return ThisCall<bool>(0x59E950, this);
	}

};

ASSERT_SIZE(Sky, 0x138);

// 04
class GridArray
{
public:
	GridArray();
	~GridArray();

	virtual void Init();
	virtual void DetachAll();
	virtual void KillAll();
	virtual void SetCenter(uint32_t aiX, uint32_t aiY);
	virtual void Shift(int aiCols, int aiRows);
	virtual void Detach(uint32_t aiX, uint32_t aiY);
	virtual void ClearItem(uint32_t aiX, uint32_t aiY);
	virtual void MoveItem(uint32_t aiX1, uint32_t aiY1, uint32_t aiX2, uint32_t aiY2);
	virtual void SwapItem(uint32_t aiX1, uint32_t aiY1, uint32_t aiX2, uint32_t aiY2);
	int32_t iWorldX;
	int32_t iWorldY;
};

struct GridCell
{
	TESObjectCELL* pCell;
};

// 28

class GridCellArray : public GridArray
{
public:
	GridCellArray();
	~GridCellArray();

	int32_t iDimension;
	GridCell* pGridCells;
	NiPoint3 kWorldCenter;
	bool bLandAttached;
	NiPointer<void*> spShadowMask;

	GridCell* GetCell(int32_t aX, int32_t aY)
	{
		uint32_t uiGridSize = iDimension;
		if (aX < iDimension && aY < iDimension)
			return &pGridCells[aX + aY * uiGridSize];
		return nullptr;
	}
};

static_assert(sizeof(GridCellArray) == 0x28);

// A0
struct WaterSurfaceManager
{
	// 30
	struct WaterGroup
	{
		TESWaterForm* waterForm; // 00
		uint32_t unk04; // 04
		uint32_t unk08; // 08
		float flt0C; // 0C	Always 1.0 ?
		float waterHeight; // 10
		uint32_t unk14; // 14
		uint32_t unk18; // 18
		float flt1C; // 1C	-flt0C
		float flt20; // 20	-waterHeight
		DList<TESObjectREFR> waterPlanes; // 24
	};

	struct Struct8C
	{
		uint32_t unk00;
		uint32_t unk04;
		uint32_t unk08;
	};

	uint32_t unk00; // 00
	uint32_t unk04; // 04
	NiObject* object08; // 08
	NiObject* object0C; // 0C
	NiObject* object10; // 10
	NiObject* object14; // 14
	NiObject* object18; // 18
	NiObject* object1C; // 1C	Seen NiSourceTexture
	NiObject* object20; // 20
	uint32_t unk24; // 24
	uint32_t unk28; // 28
	uint32_t unk2C; // 2C
	uint32_t unk30; // 30
	uint32_t unk34; // 34
	uint32_t unk38; // 38
	DList<WaterGroup> waterGroups; // 3C
	WaterGroup* waterLOD; // 48	(Assumed)
	NiTPointerMap<TESObjectREFR*, TESObjectREFR*>	 map4C; // 4C
	NiTPointerMap<TESObjectREFR*, TESObjectREFR*>	 map5C; // 5C
	NiTPointerMap<TESWaterForm*, bool>				map6C; // 6C
	NiTPointerMap<TESObjectREFR*, void*> map7C; // 7C
	Struct8C unk8C; // 8C
	float flt98; // 98
	uint32_t unk9C; // 9C
};

static_assert(sizeof(WaterSurfaceManager) == 0xA0);

// C4
class TES
{
public:
	TES();
	~TES();

	virtual void Fn_00(uint32_t arg1, uint32_t arg2, uint32_t arg3, uint32_t arg4, uint32_t arg5);

	uint32_t unk04; // 04
	GridCellArray* gridCellArray; // 08
	NiNode* niNode0C; // 0C
	NiNode* niNode10; // 10
	NiNode* rootNode; // 14
	BSTempNodeManager* tempNodeMgr; // 18
	NiDirectionalLight* directionalLight; // 1C
	void* ptr20; // 20
	int32_t extGridX; // 24
	int32_t extGridY; // 28
	int32_t extCoordX; // 2C
	int32_t extCoordY; // 30
	TESObjectCELL* currentInterior; // 34
	TESObjectCELL** interiorsBuffer; // 38
	TESObjectCELL** exteriorsBuffer; // 3C
	uint32_t unk40[9]; // 40
	WaterSurfaceManager* waterManager; // 64
	Sky* sky; // 68
	tList<ImageSpaceModifierInstance> activeIMODs; // 6C
	uint32_t unk74[3]; // 74
	float flt80; // 80	Abs X distance from centre of grid.
	float flt84; // 84	Abs Y distance from centre of grid.
	TESWorldSpace* currentWrldspc; // 88
	tList<uint32_t> list8C; // 8C
	tList<uint32_t> list94; // 94
	tList<uint32_t> list9C; // 9C
	QueuedFile* unkA4; // A4
	NiSourceTexture* unkA8; // A8
	QueuedFile* unkAC; // AC
	void* ptrB0; // B0
	uint32_t unkB4[2]; // B4
	NavMeshInfoMap* navMeshInfoMap; // BC
	LoadedAreaBound* areaBound; // C0

	bool GetTerrainHeight(float* posXY, float* result);

	static TES* GetSingleton()
	{
		return *(TES**)0x11DEA10;
	}

	void CreateTextureImage(const char* apPath, NiSourceTexture*& aspTexture, bool abNoFileOK, bool abArchiveOnly)
	{
		ThisCall(0x4568C0, this, apPath, &aspTexture, abNoFileOK, abArchiveOnly);
	}

	TESObjectCELL* GetCellForPoint(NiPoint3 akPoint) const {
		return ThisCall<TESObjectCELL*>(0x4519D0, this, akPoint);
	}
};

static_assert(sizeof(TES) == 0xC4);

struct FontHeightData
{
	float heightBase;
	float heightwGap;
};

extern FontHeightData s_fontHeightDatas[90];

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

// 18
class LoadedReferenceMap : public NiTMap<uint32_t, TESObjectREFR*>
{
public:
	LoadedReferenceMap();
	~LoadedReferenceMap();

	uint32_t unk10; // 10
	uint32_t unk14; // 14
};

// 8C
class BackUpPackage : public TESPackage
{
public:
	BackUpPackage();
	~BackUpPackage();

	virtual void Unk_58(void);

	NiPoint3 destPos; // 80
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

struct ExtraInfoGeneralTopicDataElement
{
	BSString responseText;
	uint32_t emotionType;
	uint32_t emotionValue;
	BSString voiceFilePath;
	TESIdleForm* speakerAnimation;
	TESIdleForm* listenerAnimation;
	uint32_t sound;
	uint8_t flags;
	uint8_t gap25[3];
	uint32_t responseNumber;
};

struct List11DD58CItem
{
	TESObjectREFR* ref;
	BSSoundHandle sound04;
	BSSoundHandle sound10;
	uint8_t byte1C;
	uint8_t byte1D;
	uint8_t byte1E;
	uint8_t byte1F;
};

struct VoiceEntry
{
	tList<ExtraInfoGeneralTopicDataElement> list00;
	char* response;
	TESTopicInfo* topicInfo;
	TESTopic* topic;
	TESQuest* quest;
	Actor* actor;
};

struct VoiceEntryList
{
	tList<VoiceEntry> list00;
	uint32_t unk08;
};

enum RadioEntryDataFlags
{
	kMaybeActive = 0x1,
	kSignalLost = 0x4,
	kIsBroadcastingContinuously = 0x20,
	kMaybeTracklistEmpty = 0x100,
};

struct RadioEntryData
{
	VoiceEntryList* voiceEntry;
	VoiceEntryList* voiceEntry04;
	uint32_t offset;
	uint32_t soundTimeRemaining0C;
	uint8_t lastSignalToNoiseRatioPct;
	uint8_t signalToNoiseRatioPct;
	uint8_t gap12[2];
	RadioEntryDataFlags flags;
	tList<List11DD58CItem> list18;
};

// 24
struct RadioEntry
{
	TESObjectREFR* radioRef;
	RadioEntryData data;
};


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

// 34
struct GameTimeGlobals
{
	TESGlobal* year; // 00
	TESGlobal* month; // 04
	TESGlobal* day; // 08
	TESGlobal* hour; // 0C
	TESGlobal* daysPassed; // 10
	TESGlobal* timeScale; // 14
	uint32_t unk18; // 18
	bool gameLoaded; // 1C
	uint8_t pad1D[3]; // 1D
	uint32_t unk20; // 20
	uint32_t unk24; // 24
	uint32_t unk28; // 28
	float lastUpdHour; // 2C
	uint32_t initialized; // 30

	static GameTimeGlobals* GetSingleton() {
		return reinterpret_cast<GameTimeGlobals*>(0x11DE7B8);
	}
};

// 10
struct EffectArchTypeEntry
{
	const char* name;
	ActiveEffectCreate callback;
	uint32_t unk08[2];
};

// 10
struct EntryPointConditionInfo
{
	const char* entryPoint;
	uint8_t numTabs;
	uint8_t pad01[3];
	const char** runOn;
	uint8_t byte08;
	uint8_t pad09[3];
};

// 24
struct AnimGroupInfo
{
	const char* name; // 00
	uint32_t unk04; // 04
	uint32_t sequenceType; // 08
	uint32_t unk0C; // 0C
	uint32_t unk10; // 10
	uint32_t unk14[4]; // 14
};

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


class NavMesh : public TESForm, public TESChildCell, public NiRefObject
{
public:
	TESObjectCELL* pParentCell;
	BSSimpleArray<NiPoint3> kVertices;
	BSSimpleArray<NavMeshTriangle> kTriangles;
	BSSimpleArray<EdgeExtraInfo> kEdgeInfos;
	BSSimpleArray<NavMeshTriangleDoorPortal> kDoorPortals;
	BSSimpleArray<NavMeshClosedDoorInfo> kClosedDoorInfos;
	BSSimpleArray<uint16_t> unk078Arr;
	NiTMap<uint16_t, NavMeshPOVData*> kPOVDatas;
	BSSimpleArray<uint16_t> unk098Arr;
	uint32_t unk0A8;
	float unk0AC[8];
	BSSimpleArray<uint16_t>* pArray0CC;
	BSSimpleArray<ObstacleUndoData*> kObstacleUndos;
	NiTMap<uint16_t, NiPointer<ObstacleData>>* pObstacleDataMap;
	BSSimpleArray<uint16_t> unk0E4Arr;
	BSSimpleArray<NavMeshStaticAvoidNode> kAvoidNodes;
	NavMeshInfo* pNavMeshInfo;

	// GAME - 0x5582F0
	NavMeshTriangle* GetTriangle(uint16_t ausTriangle) const {
		return &kTriangles.GetAt(ausTriangle);
	}

	// GAME - 0x558200
	uint32_t GetTriangleCount() const {
		return kTriangles.GetSize();
	}

	// GAME - 0x68F0A0
	NiPoint3* GetVertex(uint16_t ausVertex) const {
		return &kVertices.GetAt(ausVertex);
	}

	uint32_t GetVertexCount() const {
		return kVertices.GetSize();
	}
};

static_assert(sizeof(NavMesh) == 0x108);

typedef NiPointer<NavMesh> NavMeshPtr;


class NavMeshArray : public BSSimpleArray<NavMeshPtr>
{
public:
	inline NavMeshPtr GetAt(uint32_t auiIndex)
	{
		if (auiIndex >= uiSize)
			return nullptr;
		else
			return pBuffer[auiIndex];
	}
};

class NavMeshObstacleManager {
public:
	enum OBSTACLE_MANAGER_BACKGROUND_STATE : __int32
	{
		OBSTACLE_MANAGER_BACKGROUND_STATE_PROCESSING_OBSTACLES = 0x0,
		OBSTACLE_MANAGER_BACKGROUND_STATE_WAITING_FOR_PATH_MANAGER_PAUSE = 0x1,
		OBSTACLE_MANAGER_BACKGROUND_STATE_PAUSE_REQUESTED = 0x2,
		OBSTACLE_MANAGER_BACKGROUND_STATE_PAUSED = 0x3,
	};

	_RTL_CRITICAL_SECTION criticalSection;
	uint8_t byte018;
	uint8_t gap019[3];
	uint32_t formIDMap;
	uint32_t unk020;
	uint32_t unk024;
	uint32_t unk028;
	tList<TESObjectREFR> queuedRefsToAdd;
	tList<TESObjectREFR> queuedRefsToRemove;
	uint32_t unk03C;
	uint32_t unk040;
	uint32_t unk044;
	uint32_t unk048;
	uint32_t unk04C;
	uint32_t unk050;
	uint32_t unk054;
	uint32_t unk058;
	uint32_t unk05C;
	uint32_t unk060;
	uint32_t unk064;
	uint32_t unk068;
	uint32_t unk06C;
	uint32_t unk070;
	uint32_t unk074;
	uint32_t unk078;
	uint32_t unk07C;
	uint32_t unk080;
	uint32_t unk084;
	uint32_t unk088;
	uint32_t unk08C;
	uint32_t unk090;
	uint32_t unk094;
	uint32_t unk098;
	uint32_t unk09C;
	uint32_t unk0A0;
	uint32_t unk0A4;
	uint32_t unk0A8;
	uint32_t unk0AC;
	uint32_t unk0B0;
	uint32_t unk0B4;
	uint32_t unk0B8;
	uint32_t unk0BC;
	uint32_t unk0C0;
	uint32_t unk0C4;
	uint32_t unk0C8;
	uint32_t unk0CC;
	uint32_t unk0D0;
	uint32_t unk0D4;
	uint32_t unk0D8;
	uint32_t unk0DC;
	uint32_t unk0E0;
	uint32_t unk0E4;
	uint32_t unk0E8;
	uint32_t unk0EC;
	tList<void> queuedClosedDoors;
	tList<void> queuedOpenDoors;
	uint32_t openDoorMap;
	uint32_t unk104;
	uint32_t unk108;
	uint32_t unk10C;
	uint32_t closedDoorMap;
	uint32_t unk114;
	uint32_t unk118;
	uint32_t unk11C;
	uint32_t unk120;
	uint32_t unk124;
	uint32_t unk128;
	uint32_t unk12C;
	uint32_t unk130;
	uint32_t unk134;
	uint32_t unk138;
	BSSimpleArray<void*> backgroundTasks;
	BSSimpleArray<void*> processedTasks;
	uint32_t unk15C;
	RTL_CRITICAL_SECTION taskCS160;
	uint32_t unk178;
	uint32_t unk17C;
	uint32_t unk180;
	uint32_t unk184;
	uint32_t unk188;
	uint32_t unk18C;
	NavMeshObstacleManager::OBSTACLE_MANAGER_BACKGROUND_STATE eState;
	float fTimeToNextSwap;
	uint8_t byte198[4];
	uint32_t obstacleRootNode;
	uint8_t mainThreadPerformaceTimer;
	uint8_t backgroundThreadPerformanceTimer;
	uint8_t gap1A2[2];

	static NavMeshObstacleManager* GetSingleton() {
		return CdeclCall<NavMeshObstacleManager*>(0x6C0720);
	}

	void AddObstacleForReference(TESObjectREFR* apReference) {
		ThisCall(0x6C0C30, this, apReference);
	}

	void RemoveObstacleForReference(TESObjectREFR* apReference) {
		ThisCall(0x6C0C80, this, apReference);
	}
};

static_assert(sizeof(NavMeshObstacleManager) == 0x1A4);

struct AnimGroupClassify
{
	uint8_t category; // 00
	uint8_t subType; // 01
	uint8_t flags; // 02
	uint8_t byte03; // 03
};
extern AnimGroupClassify s_animGroupClassify[];

enum ActorValueCode
{
	kAVCode_Aggression,
	kAVCode_Confidence,
	kAVCode_Energy,
	kAVCode_Responsibility,
	kAVCode_Mood,
	kAVCode_Strength,
	kAVCode_Perception,
	kAVCode_Endurance,
	kAVCode_Charisma,
	kAVCode_Intelligence,
	kAVCode_Agility,
	kAVCode_Luck,
	kAVCode_ActionPoints,
	kAVCode_CarryWeight,
	kAVCode_CritChance,
	kAVCode_HealRate,
	kAVCode_Health,
	kAVCode_MeleeDamage,
	kAVCode_DamageResist,
	kAVCode_PoisonResist,
	kAVCode_RadResist,
	kAVCode_SpeedMult,
	kAVCode_Fatigue,
	kAVCode_Karma,
	kAVCode_XP,
	kAVCode_PerceptionCondition,
	kAVCode_EnduranceCondition,
	kAVCode_LeftAttackCondition,
	kAVCode_RightAttackCondition,
	kAVCode_LeftMobilityCondition,
	kAVCode_RightMobilityCondition,
	kAVCode_BrainCondition,
	kAVCode_Barter,
	kAVCode_BigGuns,
	kAVCode_EnergyWeapons,
	kAVCode_Explosives,
	kAVCode_Lockpick,
	kAVCode_Medicine,
	kAVCode_MeleeWeapons,
	kAVCode_Repair,
	kAVCode_Science,
	kAVCode_Guns,
	kAVCode_Sneak,
	kAVCode_Speech,
	kAVCode_Survival,
	kAVCode_Unarmed,
	kAVCode_InventoryWeight,
	kAVCode_Paralysis,
	kAVCode_Invisibility,
	kAVCode_Chameleon,
	kAVCode_NightEye,
	kAVCode_Turbo,
	kAVCode_FireResist,
	kAVCode_WaterBreathing,
	kAVCode_RadiationRads,
	kAVCode_BloodyMess,
	kAVCode_UnarmedDamage,
	kAVCode_Assistance,
	kAVCode_ElectricResist,
	kAVCode_FrostResist,
	kAVCode_EnergyResist,
	kAVCode_EmpResist,
	kAVCode_Variable01,
	kAVCode_Variable02,
	kAVCode_Variable03,
	kAVCode_Variable04,
	kAVCode_Variable05,
	kAVCode_Variable06,
	kAVCode_Variable07,
	kAVCode_Variable08,
	kAVCode_Variable09,
	kAVCode_Variable10,
	kAVCode_IgnoreCrippledLimbs,
	kAVCode_Dehydration,
	kAVCode_Hunger,
	kAVCode_SleepDeprivation,
	kAVCode_DamageThreshold,
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

enum PerkEntryPointID : uint32_t
{
	kPerkEntry_CalculateWeaponDamage,
	kPerkEntry_CalculateMyCriticalHitChance,
	kPerkEntry_CalculateMyCriticalHitDamage,
	kPerkEntry_CalculateWeaponAttackAPCost,
	kPerkEntry_CalculateMineExplodeChance,
	kPerkEntry_AdjustRangePenalty,
	kPerkEntry_AdjustLimbDamage,
	kPerkEntry_CalculateWeaponRange,
	kPerkEntry_CalculateToHitChance,
	kPerkEntry_AdjustExperiencePoints,
	kPerkEntry_AdjustGainedSkillPoints,
	kPerkEntry_AdjustBookSkillPoints,
	kPerkEntry_ModifyRecoveredHealth,
	kPerkEntry_CalculateInventoryAPCost,
	kPerkEntry_GetDisposition,
	kPerkEntry_GetShouldAttack,
	kPerkEntry_GetShouldAssist,
	kPerkEntry_CalculateBuyPrice,
	kPerkEntry_GetBadKarma,
	kPerkEntry_GetGoodKarma,
	kPerkEntry_IgnoreLockedTerminal,
	kPerkEntry_AddLeveledListOnDeath,
	kPerkEntry_GetMaxCarryWeight,
	kPerkEntry_ModifyAddictionChance,
	kPerkEntry_ModifyAddictionDuration,
	kPerkEntry_ModifyPositiveChemDuration,
	kPerkEntry_AdjustDrinkingRadiation,
	kPerkEntry_Activate,
	kPerkEntry_MysteriousStranger,
	kPerkEntry_HasParalyzingPalm,
	kPerkEntry_HackingScienceBonus,
	kPerkEntry_IgnoreRunningDuringDetection,
	kPerkEntry_IgnoreBrokenLock,
	kPerkEntry_HasConcentratedFire,
	kPerkEntry_CalculateGunSpread,
	kPerkEntry_PlayerKillAPReward,
	kPerkEntry_ModifyEnemyCriticalHitChance,
	kPerkEntry_ReloadSpeed,
	kPerkEntry_EquipSpeed,
	kPerkEntry_ActionPointRegen,
	kPerkEntry_ActionPointCost,
	kPerkEntry_MissFortune,
	kPerkEntry_ModifyRunSpeed,
	kPerkEntry_ModifyAttackSpeed,
	kPerkEntry_ModifyRadiationConsumed,
	kPerkEntry_HasPipHacker,
	kPerkEntry_HasMeltdown,
	kPerkEntry_SeeEnemyHealth,
	kPerkEntry_HasJuryRigging,
	kPerkEntry_ModifyThreatRange,
	kPerkEntry_ModifyThread,
	kPerkEntry_HasFastTravelAlways,
	kPerkEntry_KnockdownChance,
	kPerkEntry_ModifyWeaponStrengthReq,
	kPerkEntry_ModifyAimingMoveSpeed,
	kPerkEntry_ModifyLightItems,
	kPerkEntry_ModifyDamageThresholdDefender,
	kPerkEntry_ModifyChanceforAmmoItem,
	kPerkEntry_ModifyDamageThresholdAttacker,
	kPerkEntry_ModifyThrowingVelocity,
	kPerkEntry_ChanceforItemonFire,
	kPerkEntry_HasUnarmedForwardPowerAttack,
	kPerkEntry_HasUnarmedBackPowerAttack,
	kPerkEntry_HasUnarmedCrouchedPowerAttack,
	kPerkEntry_HasUnarmedCounterAttack,
	kPerkEntry_HasUnarmedLeftPowerAttack,
	kPerkEntry_HasUnarmedRightPowerAttack,
	kPerkEntry_VATSHelperChance,
	kPerkEntry_ModifyItemDamage,
	kPerkEntry_HasImprovedDetection,
	kPerkEntry_HasImprovedSpotting,
	kPerkEntry_HasImprovedItemDetection,
	kPerkEntry_AdjustExplosionRadius,
	kPerkEntry_AdjustHeavyWeaponWeight
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

struct ItemEntryData {
	ItemEntryData(TESBoundObject* apForm, ItemChange* apItemChange, ExtraDataList* apExtraDataList) :
		pForm(apForm), pItemChange(apItemChange), pExtraDataList(apExtraDataList) {}

	TESBoundObject*	pForm			= nullptr;
	ItemChange*		pItemChange		= nullptr;
	ExtraDataList*	pExtraDataList	= nullptr;
};

class InventoryRef : public ItemEntryData {
public:
	class DeferredAction {
	public:
		enum Type {
			EQUIP,
			REMOVE,
		};

		Type			eType;
		ItemEntryData	pItemData;
		TESObjectREFR*	pTarget;
	};

	class ActionStack {
	public:
		struct Node {
			Node*			pNext;
			DeferredAction	kAction;
		};

		Node* pHead;
	};

	TESObjectREFR*	pContainerRef;
	TESObjectREFR*	pTempRef;
	ActionStack		kDeferredActions;
	ItemChange*		pTempItemChange;
	uint8_t			padding[0x10];
	bool			bDoValidation;
	bool			bRemoved;


	bool __fastcall CreateExtraData(BSExtraData* apExtraData);
};

ASSERT_SIZE(InventoryRef, 0x30);

struct SingleTimer
{
	float startTime;
};

struct TimePair : SingleTimer
{
	float cooldownTime;
};

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
	TimePair timer0A8;
	TimePair timer0B0;
	TimePair timer0B8;
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
	TimePair combatRestoreAndBuffItemTimers[2];
	TESForm* combatItem1BC;
	Actor* actor1C0;
	CombatController* cmbtCtrl;
	uint8_t byte1C8_maybeInitializing;
	uint8_t byte1C9;
	uint8_t gap1CA[2];
	TimePair timer1CC;
	TimePair findBetterWeaponTimer;
	TimePair explosiveProjectileBlockedResetTimer;
	TimePair avoidThreatsTimer;
	TimePair takeCoverTimer;
	TimePair timer1F4;
	TimePair timer1FC;
	TimePair strengthUpdateTimer;
	TimePair combatThreatRatioTimer;
	TimePair embeddedWeaponSwitchTimer;
	TimePair inventoryUpdateTimer;
	uint32_t ptr224;
	int32_t unk228;
};

static_assert(sizeof(CombatState) == 0x22C);

class BSShaderBloodSplatterProperty : public BSShaderProperty
{
public:
	NiPointer<NiTexture> spTexture[2];
	DWORD dword68;
	float* pfFadeAlpha;

	static __forceinline uint32_t GetShapeCount() { return *(uint32_t*)0x11FF0F0; };
	static __forceinline void SetShapeCount(uint32_t uiCount) { *(uint32_t*)0x11FF0F0 = uiCount; };

	static void SetFadeSourceRecurse(NiAVObject* apObject, float* apfFadeAlpha)
	{
		CdeclCall(0xB81420, apObject, apfFadeAlpha);
	}

	void SetTexture(uint32_t auiIndex, NiTexture* apTexture)
	{
		if (spTexture[auiIndex].m_pObject != apTexture)
		{
			if (spTexture[auiIndex].m_pObject)
				spTexture[auiIndex].m_pObject->DecRefCount();
			spTexture[auiIndex].m_pObject = apTexture;
			if (spTexture[auiIndex].m_pObject)
				spTexture[auiIndex].m_pObject->IncRefCount();
		}
	}
};

static_assert(sizeof(BSShaderBloodSplatterProperty) == 0x70);

struct BSSplatterData
{
	float fAge;
	float fDuration;
	float fAlpha;
	uint32_t uiCount;
};

class BSCustomSplatterExtraData : public NiExtraData
{
public:
	BSCustomSplatterExtraData();
	virtual ~BSCustomSplatterExtraData();

	static BSCustomSplatterExtraData* Create(BSSplatterData& arData)
	{
		BSCustomSplatterExtraData* pExtraData = CdeclCall<BSCustomSplatterExtraData*>(
			0xAA13E0, sizeof(BSCustomSplatterExtraData)); // NiNew
		return ThisCall<BSCustomSplatterExtraData*>(0x4DEA80, pExtraData, &arData);
	}

	BSSplatterData kData;
};

class ScreenCustomSplatter
{
public:
	static __forceinline NiNode* GetRootNode() { return *(NiNode**)0x11C7810; };
	static __forceinline bool IsEnabled() { return *(bool*)0x11C77E8; };

	static __forceinline NiNode* CreateGeometry(uint32_t auiCount, float afSizeMult, float afOpacityMult)
	{
		return CdeclCall<NiNode*>(0x4DF040, auiCount, afSizeMult, afOpacityMult);
	}

	static void ActivateAlt(uint32_t auiCount, float afDuration, float afSizeMult, float afOpacityMult,
	                        NiTexture* apAlphaTex, NiTexture* apColorTex, NiTexture* apFlareTex)
	{
#if 0
		CdeclCall(0x4DE8E0, auiCount, afDuration, 0, afSizeMult, afOpacityMult);
#else
		if (!IsEnabled() || auiCount == 0)
			return;

		NiNode* pNewNode = CreateGeometry(auiCount, afSizeMult, afOpacityMult);
		(*(uint32_t*)0x11C77DC) += auiCount;

		BSSplatterData kSplatterData{};
		kSplatterData.fAge = 0.f;
		kSplatterData.fDuration = afDuration;
		kSplatterData.fAlpha = 1.f;
		kSplatterData.uiCount = auiCount;

		BSCustomSplatterExtraData* pExtraData = BSCustomSplatterExtraData::Create(kSplatterData);
		pNewNode->AddExtraData(pExtraData);

		NiTriShape* pShape = static_cast<NiTriShape*>(pNewNode->GetAt(0));
		BSShaderBloodSplatterProperty* pShaderProp = static_cast<BSShaderBloodSplatterProperty*>(pShape->shaderProp);

		if (apAlphaTex)
			pShaderProp->SetTexture(0, apAlphaTex);

		if (apColorTex)
			pShaderProp->SetTexture(1, apColorTex);

		// IsHDR
		if (*(bool*)0x11F941E && apFlareTex)
		{
			NiTriShape* pHDRShape = static_cast<NiTriShape*>(pNewNode->GetAt(1));
			pShaderProp = static_cast<BSShaderBloodSplatterProperty*>(pHDRShape->shaderProp);
			pShaderProp->SetTexture(0, apFlareTex);
		}

		GetRootNode()->AttachChild(pNewNode, true);
		BSShaderBloodSplatterProperty::SetFadeSourceRecurse(pNewNode, &pExtraData->kData.fAlpha);
		NiUpdateData kUpdateData = NiUpdateData();
		GetRootNode()->Update(kUpdateData);
#endif
	};
};
