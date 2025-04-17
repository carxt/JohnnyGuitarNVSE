#pragma once

class LoadedAreaBound;
struct ExtraAudioMarkerData;
struct BGSSaveLoadFileEntry;
class Sky;
class BSTempNodeManager;
class ImageSpaceModifierInstanceRB;
struct NavMeshClosedDoorInfo;

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

	UInt32 type; // 04
	float unk08[4]; // 08
	float bounds[3]; // 18
	NiRefObject* unk24; // 24
	NiRefObject* unk28; // 28
	NiRefObject* unk2C; // 2C
	UInt32 unk30; // 30
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

	UInt32 unk34[6]; // 34
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
	UInt8 detectionLevel; // 04
	UInt8 byte05; // 05
	UInt8 byte06; // 06
	UInt8 byte07; // 07
	SInt32 detectionValue; // 08
	NiPoint3 detectionLocation; // 0C
	float fDetectionTimestamp; // 18
	UInt8 bForceResetLOSBuffer; // 1C
	UInt8 byte1D; // 1D
	bool inLOS; // 1E
	UInt8 byte1F; // 1F
	SInt32 detectionModSneak;
};


// 08
class SkyObject
{
public:
	SkyObject();
	~SkyObject();

	virtual SkyObject* Destroy(bool doFree);
	virtual void Fn_01(void);
	virtual void Fn_02(NiNode* niNode);
	virtual void Update(Sky* sky, float value);

	NiNode* rootNode; // 04
};

// 1C
class Atmosphere : public SkyObject
{
public:
	Atmosphere();
	~Atmosphere();

	virtual void Fn_04(NiNode* niNode, NiRefObject* unk);

	NiNode* node08; // 08
	BSFogProperty* fogProp; // 0C	Same as *0x11DEB00
	NiRefObject* object10; // 10
	NiRefObject* object14; // 14
	UInt8 byte18; // 18
	UInt8 pad19[3]; // 19
};

// 10
class Stars : public SkyObject
{
public:
	Stars();
	~Stars();

	NiNode* node08; // 08
	float flt0C; // 0C
};

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
	UInt32 unk18; // 18
	NiDirectionalLight* sunLight; // 1C	Same as g_TES->directionalLight
	float flt20; // 20
	UInt8 byte24; // 24
	UInt8 byte25; // 25
	UInt8 byte26; // 26
	UInt8 byte27; // 27
	BSShaderAccumulator* shaderAccum; // 28
};

// 5C
class Clouds : public SkyObject
{
public:
	Clouds();
	~Clouds();

	NiAVObject* layer0; // 08	(NiTriStrips)
	NiAVObject* layer1; // 0C		"
	NiAVObject* layer2; // 10		"
	NiAVObject* layer3; // 14		"
	UInt32 unk18[4]; // 18
	float flt28; // 28
	float flt2C; // 2C
	float flt30; // 30
	float flt34; // 34
	float flt38; // 38
	float flt3C; // 3C
	float flt40; // 40
	float flt44; // 44
	float flt48; // 48
	float flt4C; // 4C
	float flt50; // 50
	float flt54; // 54
	UInt32 numLayers; // 58
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
	UInt32 fullMoonPath;
	UInt32 unk01C;
	UInt32 threeWanPath;
	UInt32 unk024;
	UInt32 halfWanPath;
	UInt32 unk02C;
	UInt32 oneWanPath;
	UInt32 unk034;
	UInt32 unk038;
	UInt32 unk03C;
	UInt32 oneWaxPath;
	UInt32 unk044;
	UInt32 halfWaxPath;
	UInt32 unk04C;
	UInt32 threeWaxPath;
	UInt32 unk054;
	float angleFadeStart;
	float angleFadeEnd;
	float shadowEarlyFade;
	float speed;
	float zOffset;
	UInt32 size;
	MoonUpdateStatus eUpdateMoonTexture;
	float unk074;
	float lastUpdateHour;
};

// 18
class Precipitation
{
public:
	Precipitation();
	~Precipitation();

	virtual Precipitation* Destroy(bool doFree);

	NiNode* node04; // 04
	NiNode* node08; // 08
	UInt32 unk0C; // 0C
	float unk10; // 10
	UInt32 unk14; // 14
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
	virtual void Unk_26(UInt32 arg);

	UInt8 hidden; // 08
	UInt8 pad09[3]; // 09
	float percent; // 0C
	NiObject* obj10; // 10
	float flt14; // 14
	UInt32 unk18; // 18
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
	UInt32 unk2C; // 2C
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
	UInt32 unk30; // 30
	UInt32 unk34; // 34
	float flt38; // 38
	float flt3C; // 3C
	UInt32 unk40; // 40
};

// 138
class Sky
{
public:
	Sky();
	~Sky();

	virtual Sky* Destructor(bool doFree);

	NiNode* niNode004; // 004
	NiNode* niNode008; // 008
	TESClimate* firstClimate; // 00C
	TESWeather* firstWeather; // 010
	TESWeather* weather014; // 014
	TESWeather* weather018; // 018
	TESWeather* weatherOverride; // 01C
	Atmosphere* atmosphere; // 020
	Stars* stars; // 024
	Sun* sun; // 028
	Clouds* clouds; // 02C
	Moon* masserMoon; // 030
	Moon* secundaMoon; // 034
	Precipitation* precipitation; // 038
	NiVector3 vector03C; // 03C
	NiColor waterReflection; // 048
	NiVector3 vector054; // 054
	NiColor sunAmbient; // 060
	NiColor sunDirectional; // 06C
	NiVector3 vector078; // 078
	NiVector3 vector084; // 084
	NiVector3 vector090; // 090
	NiVector3 vector09C; // 09C
	NiVector3 vector0A8; // 0A8
	NiVector3 vector0B4; // 0B4
	NiColor sunFog; // 0C0
	float windSpeed; // 0CC
	float windDirection; // 0D0
	UInt32 unk0D4[6]; // 0D4
	float gameHour; // 0EC
	float lastUpdateHour; // 0F0
	float weatherPercent; // 0F4
	UInt32 unk0F8; // 0F8
	UInt32 unk0FC; // 0FC
	float lightningFxPerc; // 100
	UInt32 unk104; // 104
	float flt108; // 108
	float flt10C; // 10C
	float flt110; // 110
	UInt32 unk114; // 114
	UInt32 flags; // 118
	ImageSpaceModifierInstanceForm* pCurrentWeatherImageSpaceMod; // 11C
	ImageSpaceModifierInstanceForm* pCurrentWeatherImageSpaceMod2; // 120
	ImageSpaceModifierInstanceForm* pLastWeatherImageSpaceMod; // 124
	ImageSpaceModifierInstanceForm* pLastWeatherImageSpaceMod2; // 128
	float flt12C; // 12C
	float flt130; // 130
	float flt134; // 134

	void RefreshMoon();
	void RefreshClimate(TESClimate* climate, bool immediate = true);
	bool GetIsRaining();
	__forceinline static Sky* Get() { return *(Sky**)0x11DEA20; }
};

STATIC_ASSERT(sizeof(Sky) == 0x138);

// 04
class GridArray
{
public:
	GridArray();
	~GridArray();

	virtual void Init();
	virtual void DetachAll();
	virtual void KillAll();
	virtual void SetCenter(UInt32 aiX, UInt32 aiY);
	virtual void Shift(int aiCols, int aiRows);
	virtual void Detach(UInt32 aiX, UInt32 aiY);
	virtual void ClearItem(UInt32 aiX, UInt32 aiY);
	virtual void MoveItem(UInt32 aiX1, UInt32 aiY1, UInt32 aiX2, UInt32 aiY2);
	virtual void SwapItem(UInt32 aiX1, UInt32 aiY1, UInt32 aiX2, UInt32 aiY2);
	SInt32 iWorldX;
	SInt32 iWorldY;
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

	SInt32 iDimension;
	GridCell* pGridCells;
	NiPoint3 kWorldCenter;
	bool bLandAttached;
	NiPointer<void*> spShadowMask;

	GridCell* GetCell(SInt32 aX, SInt32 aY)
	{
		UInt32 uiGridSize = iDimension;
		if (aX < iDimension && aY < iDimension)
			return &pGridCells[aX + aY * uiGridSize];
		return nullptr;
	}
};

STATIC_ASSERT(sizeof(GridCellArray) == 0x28);

// A0
struct WaterSurfaceManager
{
	// 30
	struct WaterGroup
	{
		TESWaterForm* waterForm; // 00
		UInt32 unk04; // 04
		UInt32 unk08; // 08
		float flt0C; // 0C	Always 1.0 ?
		float waterHeight; // 10
		UInt32 unk14; // 14
		UInt32 unk18; // 18
		float flt1C; // 1C	-flt0C
		float flt20; // 20	-waterHeight
		DList<TESObjectREFR> waterPlanes; // 24
	};

	struct Struct8C
	{
		UInt32 unk00;
		UInt32 unk04;
		UInt32 unk08;
	};

	UInt32 unk00; // 00
	UInt32 unk04; // 04
	NiObject* object08; // 08
	NiObject* object0C; // 0C
	NiObject* object10; // 10
	NiObject* object14; // 14
	NiObject* object18; // 18
	NiObject* object1C; // 1C	Seen NiSourceTexture
	NiObject* object20; // 20
	UInt32 unk24; // 24
	UInt32 unk28; // 28
	UInt32 unk2C; // 2C
	UInt32 unk30; // 30
	UInt32 unk34; // 34
	UInt32 unk38; // 38
	DList<WaterGroup> waterGroups; // 3C
	WaterGroup* waterLOD; // 48	(Assumed)
	NiTPointerMap<TESObjectREFR> map4C; // 4C
	NiTPointerMap<TESObjectREFR> map5C; // 5C
	NiTPointerMap<TESWaterForm> map6C; // 6C
	NiTMapBase<TESObjectREFR*, void*> map7C; // 7C
	Struct8C unk8C; // 8C
	float flt98; // 98
	UInt32 unk9C; // 9C
};

STATIC_ASSERT(sizeof(WaterSurfaceManager) == 0xA0);

// C4
class TES
{
public:
	TES();
	~TES();

	virtual void Fn_00(UInt32 arg1, UInt32 arg2, UInt32 arg3, UInt32 arg4, UInt32 arg5);

	UInt32 unk04; // 04
	GridCellArray* gridCellArray; // 08
	NiNode* niNode0C; // 0C
	NiNode* niNode10; // 10
	NiNode* rootNode; // 14
	BSTempNodeManager* tempNodeMgr; // 18
	NiDirectionalLight* directionalLight; // 1C
	void* ptr20; // 20
	SInt32 extGridX; // 24
	SInt32 extGridY; // 28
	SInt32 extCoordX; // 2C
	SInt32 extCoordY; // 30
	TESObjectCELL* currentInterior; // 34
	TESObjectCELL** interiorsBuffer; // 38
	TESObjectCELL** exteriorsBuffer; // 3C
	UInt32 unk40[9]; // 40
	WaterSurfaceManager* waterManager; // 64
	Sky* sky; // 68
	tList<ImageSpaceModifierInstance> activeIMODs; // 6C
	UInt32 unk74[3]; // 74
	float flt80; // 80	Abs X distance from centre of grid.
	float flt84; // 84	Abs Y distance from centre of grid.
	TESWorldSpace* currentWrldspc; // 88
	tList<UInt32> list8C; // 8C
	tList<UInt32> list94; // 94
	tList<UInt32> list9C; // 9C
	QueuedFile* unkA4; // A4
	NiSourceTexture* unkA8; // A8
	QueuedFile* unkAC; // AC
	void* ptrB0; // B0
	UInt32 unkB4[2]; // B4
	NavMeshInfoMap* navMeshInfoMap; // BC
	LoadedAreaBound* areaBound; // C0

	bool GetTerrainHeight(float* posXY, float* result);

	static TES* TES::GetSingleton()
	{
		return *(TES**)0x11DEA10;
	}

	void TES::CreateTextureImage(const char* apPath, NiSourceTexture*& aspTexture, bool abNoFileOK, bool abArchiveOnly)
	{
		ThisCall(0x4568C0, this, apPath, &aspTexture, abNoFileOK, abArchiveOnly);
	}
};

STATIC_ASSERT(sizeof(TES) == 0xC4);

struct FontHeightData
{
	float heightBase;
	float heightwGap;
} s_fontHeightDatas[90];

// 54
struct FontInfo
{
	struct BufferData
	{
		float lineHeight; // 0000
		UInt32 unk0004[73]; // 0004
		UInt32 unk0128[458]; // 0128
		float baseHeight; // 0850
		float flt0854; // 0854
		float flt0858; // 0858
	};

	struct ButtonIcon;

	UInt8 isLoaded; // 00
	UInt8 pad01[3]; // 01
	char* filePath; // 04
	UInt8 fontID; // 08
	UInt8 pad09[3]; // 09
	NiTexturingProperty* texProp; // 0C
	UInt32 unk10[7]; // 10
	float flt2C; // 2C
	float flt30; // 30
	UInt32 unk34; // 34
	BufferData* bufferData; // 38
	UInt32 unk3C[2]; // 3C
	BSSimpleArray<ButtonIcon> arr44; // 44
};

STATIC_ASSERT(sizeof(FontInfo) == 0x54);

// 164 (24)
class FontManager
{
public:
	FontManager();
	~FontManager();

	FontInfo* fontInfos[8]; // 00
	UInt8 byte20; // 20
	UInt8 pad21[3]; // 21
	FontInfo* extraFonts[80]; // 24

	//	outDims.x := width (pxl); outDims.y := height (pxl); outDims.z := numLines
	NiVector3* GetStringDimensions(NiVector3* outDims, const char* srcString, UInt32 fontID, UInt32 maxFlt = 0x7F7FFFFF,
	                               UInt32 startIdx = 0);
};

__declspec(naked) NiVector3* FontManager::GetStringDimensions(NiVector3* outDims, const char* srcString, UInt32 fontID,
                                                              UInt32 maxFlt, UInt32 startIdx)
{
	static const UInt32 procAddr = 0xA1B020;
	__asm jmp procAddr
}

// 18
class LoadedReferenceMap : public NiTPointerMap<TESObjectREFR>
{
public:
	LoadedReferenceMap();
	~LoadedReferenceMap();

	UInt32 unk10; // 10
	UInt32 unk14; // 14
};

// 8C
class BackUpPackage : public TESPackage
{
public:
	BackUpPackage();
	~BackUpPackage();

	virtual void Unk_58(void);

	NiVector3 destPos; // 80
};

// 229C
class DebugText
{
public:
	DebugText();
	~DebugText();

	virtual void Unk_00(void);
	virtual void Unk_01(UInt32 arg1, UInt32 arg2);
	virtual UInt32 Unk_02(UInt32 arg1, UInt32 arg2, UInt32 arg3, UInt32 arg4, UInt32 arg5, UInt32 arg6);
	virtual UInt32 Unk_03(UInt32 arg1, UInt32 arg2, UInt32 arg3, UInt32 arg4);
	virtual void Unk_04(UInt32 arg1, UInt32 arg2, UInt32 arg3, UInt32 arg4, UInt32 arg5, UInt32 arg6);
	virtual UInt32 Unk_05(UInt32 arg1, UInt32 arg2, UInt32 arg3, UInt32 arg4, UInt32 arg5);
	virtual void Unk_06(UInt32 arg1, UInt32 arg2, UInt32 arg3, UInt32 arg4, UInt32 arg5);
	virtual UInt32 Unk_07(UInt32 arg1, UInt32 arg2, UInt32 arg3, UInt32 arg4, UInt32 arg5, UInt32 arg6, UInt32 arg7);
	virtual UInt32 Unk_08(UInt32 arg1, UInt32 arg2, UInt32 arg3, UInt32 arg4, UInt32 arg5);
	virtual UInt32 Unk_09(UInt32 arg1, UInt32 arg2, UInt32 arg3, UInt32 arg4, UInt32 arg5, UInt32 arg6);
	virtual UInt32 Unk_0A(UInt32 arg1);
	virtual void Unk_0B(UInt32 arg1, UInt32 arg2);

	struct DebugLine
	{
		float offsetX; // 00
		float offsetY; // 04
		UInt32 isVisible; // 08
		NiNode* node; // 0C
		BSString text; // 10
		float flt18; // 18	Always -1.0
		NiColorAlpha color; // 1C
	};

	DebugLine lines[200]; // 0004
	UInt32 unk2264[14]; // 2264

	static DebugText* GetSingleton();
	DebugLine* GetDebugInput();
};

STATIC_ASSERT(sizeof(DebugText) == 0x229C);

DebugText* DebugText::GetSingleton()
{
	return ((DebugText * (*)(bool))0xA0D9E0)(true);
}

DebugText::DebugLine* DebugText::GetDebugInput()
{
	DebugLine *linesPtr = lines, *result = lines;
	UInt32 counter = 200;
	do
	{
		linesPtr++;
		if (!linesPtr->isVisible) break;
		if (result->offsetY < linesPtr->offsetY)
			result = linesPtr;
	}
	while (--counter);
	return result;
}


struct ExtraInfoGeneralTopicDataElement
{
	BSString responseText;
	UInt32 emotionType;
	UInt32 emotionValue;
	BSString voiceFilePath;
	TESIdleForm* speakerAnimation;
	TESIdleForm* listenerAnimation;
	UInt32 sound;
	UInt8 flags;
	UInt8 gap25[3];
	UInt32 responseNumber;
};

struct List11DD58CItem
{
	TESObjectREFR* ref;
	Sound sound04;
	Sound sound10;
	UInt8 byte1C;
	UInt8 byte1D;
	UInt8 byte1E;
	UInt8 byte1F;
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
	UInt32 unk08;
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
	UInt32 offset;
	UInt32 soundTimeRemaining0C;
	UInt8 lastSignalToNoiseRatioPct;
	UInt8 signalToNoiseRatioPct;
	UInt8 gap12[2];
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
	UInt32 unk20C; // 20C
	float flt210; // 210
	float flt214; // 214
	float flt218; // 218
	float flt21C; // 21C
	UInt8 track1Flags; // 220
	UInt8 track2Flags; // 221
	UInt8 pad222[2]; // 222
	UInt32 unk224; // 224
	UInt32 unk228[8]; // 228
	float flt248; // 248
	float flt24C; // 24C
	float flt250; // 250
	float flt254; // 254
	UInt32 unk258; // 258
	UInt32 unk25C[8]; // 25C
	UInt32 track1Active; // 27C
	UInt32 unk280; // 280
	MediaLocationController* medLocCtrl; // 284
};

STATIC_ASSERT(sizeof(PlayingMusic) == 0x288);

// 34
struct GameTimeGlobals
{
	TESGlobal* year; // 00
	TESGlobal* month; // 04
	TESGlobal* day; // 08
	TESGlobal* hour; // 0C
	TESGlobal* daysPassed; // 10
	TESGlobal* timeScale; // 14
	UInt32 unk18; // 18
	bool gameLoaded; // 1C
	UInt8 pad1D[3]; // 1D
	UInt32 unk20; // 20
	UInt32 unk24; // 24
	UInt32 unk28; // 28
	float lastUpdHour; // 2C
	UInt32 initialized; // 30

	float GetDaysPassed(int bgnYear = 2281, int bgnMonth = 9, int bgnDay = 13);
};

// 10
struct EffectArchTypeEntry
{
	const char* name;
	ActiveEffectCreate callback;
	UInt32 unk08[2];
};

// 10
struct EntryPointConditionInfo
{
	const char* entryPoint;
	UInt8 numTabs;
	UInt8 pad01[3];
	const char** runOn;
	UInt8 byte08;
	UInt8 pad09[3];
};

// 24
struct AnimGroupInfo
{
	const char* name; // 00
	UInt32 unk04; // 04
	UInt32 sequenceType; // 08
	UInt32 unk0C; // 0C
	UInt32 unk10; // 10
	UInt32 unk14[4]; // 14
};

struct PCMiscStat
{
	const char* name;
	UInt32 level;
};

// 08
struct TypeSignature
{
	char signature[8];
};


// 24
class SeenData
{
public:
	SeenData();
	~SeenData();

	virtual void* Destroy(bool doFree);
	virtual void Unk_01(void);
	virtual void Unk_02(void);
	virtual void Unk_03(void);
	virtual void Unk_04(void);
	virtual void Unk_05(void);
	virtual void Unk_06(void);

	UInt32 alphaLevels[8]; // 04

	bool GetBitSeen(UInt32 row, UInt32 column);
};

// 2C
class IntSeenData : public SeenData
{
public:
	IntSeenData();
	~IntSeenData();

	SInt8 segmentX; // 24
	SInt8 segmentY; // 25
	UInt8 pad26[2]; // 26
	IntSeenData* nextSegment; // 28

	IntSeenData* GetSectionSeenData(int sectionX, int sectionY);
};

struct MusicMarker
{
	TESObjectREFR* markerRef;
	ExtraAudioMarkerData* markerData;

	MusicMarker(TESObjectREFR* _markerRef, ExtraAudioMarkerData* data) : markerRef(_markerRef), markerData(data)
	{
	}

	bool operator <(const MusicMarker& rhs) const
	{
		return markerData->mediaLocCtrlID < rhs.markerData->mediaLocCtrlID;
	}
};


// 48
struct VATSCameraData
{
	tList<VATSTargetInfo> targetsList; // 00
	UInt32 mode; // 08
	UInt32 cameraShots; // 0C
	BGSCameraShot* camShot; // 10
	float flt14; // 14
	float flt18; // 18
	UInt32 unk1C; // 1C
	UInt32 unk20; // 20
	TESIdleForm* attackAnim; // 24
	ImageSpaceModifierInstanceForm* isModInstForm; // 28
	ImageSpaceModifierInstanceRB* isModInstRB; // 2C
	UInt32 unk30; // 30
	NiPointLight* niPointLight; // 34
	UInt8 byte38; // 38
	UInt8 pad39[3]; // 39
	UInt32 numKills; // 3C
	UInt32 unk40; // 40
	UInt32 unk44; // 44
};

STATIC_ASSERT(sizeof(VATSCameraData) == 0x48);

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
		virtual UInt32 GetColor();
		virtual void SetColor(UInt32 newColor);
		virtual bool IsHard();
		virtual bool IsSoft();

		BSString traitName;

		void SetColorRGB(UInt32 r, UInt32 g, UInt32 b)
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

		UInt32 color; // 0C
	};

	// 10
	class SoftSystemColor : public SystemColor
	{
	public:
		SoftSystemColor();
		~SoftSystemColor();

		UInt32* setting; // 0C
	};

	DList<SystemColor> sysColors;
	UInt32 unk0C;

	static SystemColorManager* GetSingleton() { return ThisCall<SystemColorManager*>(0x718B60, nullptr); }
	UInt32 GetColor(UInt32 type) { return ThisCall<UInt32>(0x7190A0, this, type); }
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
	BSSimpleArray<UInt16> unk078Arr;
	NiTMap<UInt16, NavMeshPOVData*> kPOVDatas;
	BSSimpleArray<UInt16> unk098Arr;
	UInt32 unk0A8;
	float unk0AC[8];
	BSSimpleArray<UInt16>* pArray0CC;
	BSSimpleArray<ObstacleUndoData*> kObstacleUndos;
	NiTMap<UInt16, NiPointer<ObstacleData>>* pObstacleDataMap;
	BSSimpleArray<UInt16> unk0E4Arr;
	BSSimpleArray<NavMeshStaticAvoidNode> kAvoidNodes;
	NavMeshInfo* pNavMeshInfo;
};

STATIC_ASSERT(sizeof(NavMesh) == 0x108);

typedef NiPointer<NavMesh> NavMeshPtr;


class NavMeshArray : public BSSimpleArray<NavMeshPtr>
{
public:
	inline NavMeshPtr& GetAt(UInt32 auiIndex)
	{
		NavMeshPtr kPtr;
		if (auiIndex >= uiSize)
			return kPtr;
		else
			return pBuffer[auiIndex];
	}
};

class NavMeshObstacleManager
{
	enum OBSTACLE_MANAGER_BACKGROUND_STATE : __int32
	{
		OBSTACLE_MANAGER_BACKGROUND_STATE_PROCESSING_OBSTACLES = 0x0,
		OBSTACLE_MANAGER_BACKGROUND_STATE_WAITING_FOR_PATH_MANAGER_PAUSE = 0x1,
		OBSTACLE_MANAGER_BACKGROUND_STATE_PAUSE_REQUESTED = 0x2,
		OBSTACLE_MANAGER_BACKGROUND_STATE_PAUSED = 0x3,
	};

	_RTL_CRITICAL_SECTION criticalSection;
	UInt8 byte018;
	UInt8 gap019[3];
	UInt32 formIDMap;
	UInt32 unk020;
	UInt32 unk024;
	UInt32 unk028;
	tList<TESObjectREFR> queuedRefsToAdd;
	tList<TESObjectREFR> queuedRefsToRemove;
	UInt32 unk03C;
	UInt32 unk040;
	UInt32 unk044;
	UInt32 unk048;
	UInt32 unk04C;
	UInt32 unk050;
	UInt32 unk054;
	UInt32 unk058;
	UInt32 unk05C;
	UInt32 unk060;
	UInt32 unk064;
	UInt32 unk068;
	UInt32 unk06C;
	UInt32 unk070;
	UInt32 unk074;
	UInt32 unk078;
	UInt32 unk07C;
	UInt32 unk080;
	UInt32 unk084;
	UInt32 unk088;
	UInt32 unk08C;
	UInt32 unk090;
	UInt32 unk094;
	UInt32 unk098;
	UInt32 unk09C;
	UInt32 unk0A0;
	UInt32 unk0A4;
	UInt32 unk0A8;
	UInt32 unk0AC;
	UInt32 unk0B0;
	UInt32 unk0B4;
	UInt32 unk0B8;
	UInt32 unk0BC;
	UInt32 unk0C0;
	UInt32 unk0C4;
	UInt32 unk0C8;
	UInt32 unk0CC;
	UInt32 unk0D0;
	UInt32 unk0D4;
	UInt32 unk0D8;
	UInt32 unk0DC;
	UInt32 unk0E0;
	UInt32 unk0E4;
	UInt32 unk0E8;
	UInt32 unk0EC;
	tList<void> queuedClosedDoors;
	tList<void> queuedOpenDoors;
	UInt32 openDoorMap;
	UInt32 unk104;
	UInt32 unk108;
	UInt32 unk10C;
	UInt32 closedDoorMap;
	UInt32 unk114;
	UInt32 unk118;
	UInt32 unk11C;
	UInt32 unk120;
	UInt32 unk124;
	UInt32 unk128;
	UInt32 unk12C;
	UInt32 unk130;
	UInt32 unk134;
	UInt32 unk138;
	BSSimpleArray<void> backgroundTasks;
	BSSimpleArray<void> processedTasks;
	UInt32 unk15C;
	RTL_CRITICAL_SECTION taskCS160;
	UInt32 unk178;
	UInt32 unk17C;
	UInt32 unk180;
	UInt32 unk184;
	UInt32 unk188;
	UInt32 unk18C;
	NavMeshObstacleManager::OBSTACLE_MANAGER_BACKGROUND_STATE eState;
	float fTimeToNextSwap;
	UInt8 byte198[4];
	UInt32 obstacleRootNode;
	UInt8 mainThreadPerformaceTimer;
	UInt8 backgroundThreadPerformanceTimer;
	UInt8 gap1A2[2];
};

STATIC_ASSERT(sizeof(NavMeshObstacleManager) == 0x1A4);

class BSArchiveHeader
{
public:
	BSArchiveHeader();
	~BSArchiveHeader();
};

// 70
class BSArchive : public BSArchiveHeader
{
public:
	BSArchive();
	~BSArchive();

	UInt32 unk00; // 00	160
	UInt32 unk04; // 04	164
	UInt32 unk08; // 08	168
	UInt32 unk0C; // 0C	16C
	UInt32 unk10; // 10	170
	UInt32 unk14; // 14	174
	UInt32 unk18; // 18	178
	UInt32 unk1C; // 1C	17C
	UInt16 fileTypesMask; // 20	180
	UInt16 word22; // 22	182
	UInt32 unk24[19]; // 24	184
};

STATIC_ASSERT(sizeof(BSArchive) == 0x70);

// 1D0
class Archive : public BSFile
{
public:
	Archive();
	~Archive();

	NiRefObject refObject; // 158
	BSArchive archive; // 160
};

STATIC_ASSERT(sizeof(Archive) == 0x1D0);

// 160
class ArchiveFile : public BSFile
{
public:
	ArchiveFile();
	~ArchiveFile();

	UInt32 unk158; // 158
	UInt32 unk15C; // 15C
};

STATIC_ASSERT(sizeof(ArchiveFile) == 0x160);

// 178
class CompressedArchiveFile : public ArchiveFile
{
public:
	CompressedArchiveFile();
	~CompressedArchiveFile();

	void* ptr160; // 160
	void* ptr164; // 164
	UInt32 streamLength; // 168
	UInt32 unk16C; // 16C
	UInt32 streamOffset; // 170
	UInt32 unk174; // 174
};

STATIC_ASSERT(sizeof(CompressedArchiveFile) == 0x178);


struct AnimGroupClassify
{
	UInt8 category; // 00
	UInt8 subType; // 01
	UInt8 flags; // 02
	UInt8 byte03; // 03
}
s_animGroupClassify[] =
{
	{1, 1, 0, 0}, {1, 1, 0, 0}, {1, 1, 0, 0}, {2, 1, 0, 0}, {2, 2, 0, 0}, {2, 3, 0, 0}, {2, 4, 0, 0}, {2, 1, 1, 0},
	{2, 2, 1, 0},
	{2, 3, 1, 0}, {2, 4, 1, 0}, {2, 1, 2, 0}, {2, 2, 2, 0}, {2, 3, 2, 0}, {2, 4, 2, 0}, {2, 3, 4, 0}, {2, 4, 4, 0},
	{3, 0, 0, 0},
	{3, 0, 1, 0}, {3, 0, 2, 0}, {3, 0, 4, 0}, {3, 0, 5, 0}, {3, 0, 6, 0}, {1, 2, 0, 0}, {1, 2, 0, 0}, {1, 2, 0, 0},
	{3, 1, 0, 0},
	{3, 1, 1, 0}, {3, 1, 2, 0}, {3, 1, 4, 0}, {3, 1, 5, 0}, {3, 1, 6, 0}, {3, 2, 0, 0}, {3, 2, 1, 0}, {3, 2, 2, 0},
	{3, 2, 4, 0},
	{3, 2, 5, 0}, {3, 2, 6, 0}, {3, 3, 0, 0}, {3, 3, 1, 0}, {3, 3, 2, 0}, {3, 3, 4, 0}, {3, 3, 5, 0}, {3, 3, 6, 0},
	{3, 4, 0, 0},
	{3, 4, 1, 0}, {3, 4, 2, 0}, {3, 4, 4, 0}, {3, 4, 5, 0}, {3, 4, 6, 0}, {3, 5, 0, 0}, {3, 5, 1, 0}, {3, 5, 2, 0},
	{3, 5, 4, 0},
	{3, 5, 5, 0}, {3, 5, 6, 0}, {3, 6, 0, 0}, {3, 6, 1, 0}, {3, 6, 2, 0}, {3, 6, 4, 0}, {3, 6, 5, 0}, {3, 6, 6, 0},
	{3, 7, 0, 0},
	{3, 7, 1, 0}, {3, 7, 2, 0}, {3, 7, 4, 0}, {3, 7, 5, 0}, {3, 7, 6, 0}, {3, 8, 0, 0}, {3, 8, 1, 0}, {3, 8, 2, 0},
	{3, 8, 4, 0},
	{3, 8, 5, 0}, {3, 8, 6, 0}, {3, 10, 0, 0}, {3, 10, 1, 0}, {3, 10, 2, 0}, {3, 10, 4, 0}, {3, 10, 5, 0},
	{3, 10, 6, 0}, {3, 11, 0, 0},
	{3, 11, 1, 0}, {3, 11, 2, 0}, {3, 11, 4, 0}, {3, 11, 5, 0}, {3, 11, 6, 0}, {3, 12, 0, 0}, {3, 12, 1, 0},
	{3, 12, 2, 0}, {3, 12, 4, 0},
	{3, 12, 5, 0}, {3, 12, 6, 0}, {3, 23, 0, 0}, {3, 23, 0, 0}, {3, 23, 0, 0}, {3, 23, 0, 0}, {3, 23, 0, 0},
	{3, 23, 0, 0}, {3, 23, 0, 0},
	{3, 23, 0, 0}, {3, 23, 0, 0}, {3, 23, 0, 0}, {3, 21, 0, 0}, {3, 21, 1, 0}, {3, 21, 2, 0}, {3, 21, 4, 0},
	{3, 21, 5, 0}, {3, 21, 6, 0},
	{3, 22, 0, 0}, {3, 22, 1, 0}, {3, 22, 2, 0}, {3, 22, 4, 0}, {3, 22, 5, 0}, {3, 22, 6, 0}, {3, 13, 0, 0},
	{3, 13, 1, 0}, {3, 13, 2, 0},
	{3, 13, 4, 0}, {3, 13, 5, 0}, {3, 13, 6, 0}, {3, 14, 0, 0}, {3, 14, 1, 0}, {3, 14, 2, 0}, {3, 14, 4, 0},
	{3, 14, 5, 0}, {3, 14, 6, 0},
	{3, 15, 0, 0}, {3, 15, 1, 0}, {3, 15, 2, 0}, {3, 15, 4, 0}, {3, 15, 5, 0}, {3, 15, 6, 0}, {3, 16, 0, 0},
	{3, 16, 1, 0}, {3, 16, 2, 0},
	{3, 16, 4, 0}, {3, 16, 5, 0}, {3, 16, 6, 0}, {3, 17, 0, 0}, {3, 17, 1, 0}, {3, 17, 2, 0}, {3, 17, 4, 0},
	{3, 17, 5, 0}, {3, 17, 6, 0},
	{3, 9, 0, 0}, {3, 9, 1, 0}, {3, 9, 2, 0}, {3, 9, 4, 0}, {3, 9, 5, 0}, {3, 9, 6, 0}, {3, 18, 0, 0}, {3, 18, 1, 0},
	{3, 18, 2, 0},
	{3, 18, 4, 0}, {3, 18, 5, 0}, {3, 18, 6, 0}, {3, 19, 0, 0}, {3, 19, 1, 0}, {3, 19, 2, 0}, {3, 19, 4, 0},
	{3, 19, 5, 0}, {3, 19, 6, 0},
	{3, 20, 0, 0}, {3, 20, 1, 0}, {3, 20, 2, 0}, {3, 20, 4, 0}, {3, 20, 5, 0}, {3, 20, 6, 0}, {1, 0, 0, 0},
	{1, 0, 0, 0}, {1, 3, 0, 0},
	{1, 3, 0, 0}, {1, 0, 0, 0}, {4, 0, 0, 0}, {4, 0, 0, 0}, {4, 0, 0, 0}, {4, 0, 0, 0}, {4, 0, 0, 0}, {4, 0, 0, 0},
	{4, 0, 0, 0}, {4, 0, 0, 0},
	{4, 0, 0, 0}, {4, 0, 0, 0}, {4, 0, 0, 0}, {4, 0, 0, 0}, {4, 0, 0, 0}, {4, 0, 0, 0}, {4, 0, 0, 0}, {4, 0, 0, 0},
	{4, 0, 0, 0}, {4, 0, 0, 0},
	{4, 0, 0, 0}, {4, 0, 0, 0}, {4, 0, 0, 0}, {4, 0, 0, 0}, {4, 0, 0, 0}, {4, 0, 0, 0}, {4, 0, 0, 0}, {4, 0, 0, 0},
	{4, 0, 0, 0}, {5, 0, 0, 0},
	{5, 0, 0, 0}, {5, 0, 0, 0}, {5, 0, 0, 0}, {5, 0, 0, 0}, {5, 0, 0, 0}, {5, 0, 0, 0}, {5, 0, 0, 0}, {5, 0, 0, 0},
	{5, 0, 0, 0}, {5, 0, 0, 0},
	{5, 0, 0, 0}, {5, 0, 0, 0}, {5, 0, 0, 0}, {5, 0, 0, 0}, {5, 0, 0, 0}, {5, 0, 0, 0}, {5, 0, 0, 0}, {5, 0, 0, 0},
	{5, 0, 0, 0}, {5, 0, 0, 0},
	{5, 0, 0, 0}, {5, 0, 0, 0}, {1, 0, 0, 0}, {1, 0, 0, 0}, {1, 0, 0, 0}, {1, 0, 0, 0}, {2, 5, 0, 0}, {2, 5, 0, 0},
	{2, 5, 0, 0}, {1, 4, 0, 0},
	{1, 4, 0, 0}, {1, 4, 0, 0}, {1, 4, 0, 0}, {1, 4, 0, 0}, {1, 4, 0, 0}, {2, 5, 0, 0}, {2, 5, 0, 0}, {2, 5, 0, 0},
	{2, 5, 0, 0}, {1, 0, 0, 0},
	{2, 5, 0, 0}, {2, 5, 0, 0}, {2, 5, 0, 0}, {2, 5, 0, 0}
};

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

enum PerkEntryPointID : UInt32
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

enum UpdateType
{
	QuestAdded = 0x0,
	QuestCompleted = 0x1,
	QuestFailed = 0x2,
	LocationDiscovered = 0x3,
};

struct QuestUpdateManager
{
	TESQuest* quest;
	UpdateType updateType;
	char title[260];
	char subtitle[260];
	UInt32 unk210;
	UInt32 queuePriority;
	UInt32 titleFont;
	UInt32 subtitleFont;
	char sound[260];
};

struct ItemEntryData
{
	TESForm* type;
	ContChangesEntry* entry;
	ExtraDataList* xData;

	ItemEntryData()
	{
	}

	ItemEntryData(TESForm* _type, ContChangesEntry* _entry, ExtraDataList* _xData) : type(_type), entry(_entry),
		xData(_xData)
	{
	}
};

class InventoryRef
{
public:
	ItemEntryData data;
	TESObjectREFR* containerRef;
	TESObjectREFR* tempRef;
	UInt32 deferredActions[6];
	bool doValidation;
	bool removed;

	bool CreateExtraData(BSExtraData* xBSData);
};

ExtraContainerChanges::EntryDataList* TESObjectREFR::GetContainerChangesList()
{
	ExtraContainerChanges* xChanges = (ExtraContainerChanges*)this->extraDataList.
	                                                                GetByType(kExtraData_ContainerChanges);
	if (xChanges && xChanges->data) return xChanges->data->objList;
	return nullptr;
}

bool InventoryRef::CreateExtraData(BSExtraData* xBSData)
{
	ExtraContainerChanges::EntryDataList* entryList = containerRef->GetContainerChangesList();
	if (!entryList) return false;
	ContChangesEntry* entry = entryList->FindForItem(data.type);
	if (!entry) return false;
	data.xData = ExtraDataList::Create(xBSData);
	if (!entry->extendData)
	{
		entry->extendData = (ExtraContainerChanges::ExtendDataList*)GameHeapAlloc(8);
		entry->extendData->Init();
	}
	entry->extendData->Insert(data.xData);
	return true;
}

InventoryRef* (*InventoryRefCreate)(TESObjectREFR* container, const ItemEntryData& data, bool bValidate);


struct NiPoint2
{
	float x;
	float y;

	NiPoint2() : x(0.f), y(0.f)
	{
	};

	NiPoint2(float _x, float _y) : x(_x), y(_y)
	{
	};
};

struct COORD_DATA
{
	COORD_DATA() : Blockpoint(), Cellpoint(), Vertcoord()
	{
	};

	NiPoint2 Cellpoint;
	NiPoint2 Blockpoint;
	tagPOINT Block;
	int iBlock;
	NiPoint2 Tilepoint;
	tagPOINT Tile;
	int iShape;
	NiPoint3 Vertcoord;
	int iVertidx;
	int iTrivertidx[3];
	bool bTriright;
	bool bTriupper;
};

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
	UInt8 byte000;
	UInt8 gap001[3];
	UInt32 flags;
	float fleeThreshold008;
	TESObjectWEAP* weaponsByCombatWeaponType[6];
	BSSimpleArray<void*> weapons_Array024;
	TESObjectWEAP* weap034;
	UInt32 availableCombatWeaponTypesFlags;
	float maxDPSPerWeaponType[7];
	float meleeDPS_58;
	float rangedDPS_5C;
	float unk060;
	float unk064;
	float distance068;
	UInt32 unk06C;
	UInt8 isInLineOfSight;
	UInt8 forceResetCombatLOSBufferTimer;
	UInt8 isTargetBlocked_dontIgnoreBlockedTarget072;
	UInt8 isTargetFlushed;
	UInt8 isTargetSpaceDifferent;
	UInt8 byte075;
	UInt8 byte076;
	UInt8 forceInventoryUpdate;
	BGSExplosion* dangerousExplosiveToThrow;
	UInt32 unk07C;
	float combatThreatScore;
	NiPoint3 pt084;
	UInt32 executionFlags090;
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
	UInt8 initialConfidence;
	UInt8 currentConfidence;
	UInt8 gap0CA[2];
	float combatConfidenceModifier;
	float ownerThreatLevel;
	float ownerDPS;
	UInt8 byte0D8;
	UInt8 gap0D9[3];
	UInt32 doorFleeRefID;
	UInt32 lastDoorFleeTime;
	void* ptr0E4[2];
	void* ptr0EC;
	UInt32 unk0F0;
	UInt32 unk0F4;
	UInt32 unk0F8;
	UInt32 unk0FC;
	UInt32 unk100;
	UInt32 unk104;
	float unk108;
	BSSimpleArray<void*> PathingCoverLocation_Array10C;
	UInt32 unk11C;
	UInt32 unk120;
	UInt32 unk124;
	void* ptr128;
	UInt32 unk12C;
	UInt32 unk130;
	UInt32 unk134;
	UInt32 unk138;
	UInt32 unk13C;
	UInt32 unk140;
	float unk144;
	BSSimpleArray<void*> PathingCoverLocation_Array148;
	UInt32 unk158;
	UInt32 unk15C;
	UInt32 unk160;
	BSSimpleArray<void*> UnreachableCoverLocation_Array164;
	BSSimpleArray<void*> UnreachableLocation_Array174;
	float timer184;
	UInt8 byte188;
	UInt8 gap189[3];
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
	UInt8 byte1C8_maybeInitializing;
	UInt8 byte1C9;
	UInt8 gap1CA[2];
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
	UInt32 ptr224;
	SInt32 unk228;
};

STATIC_ASSERT(sizeof(CombatState) == 0x22C);

class BSShaderBloodSplatterProperty : public BSShaderProperty
{
public:
	NiPointer<NiTexture> spTexture[2];
	DWORD dword68;
	float* pfFadeAlpha;

	static __forceinline UInt32 GetShapeCount() { return *(UInt32*)0x11FF0F0; };
	static __forceinline void SetShapeCount(UInt32 uiCount) { *(UInt32*)0x11FF0F0 = uiCount; };

	static void SetFadeSourceRecurse(NiAVObject* apObject, float* apfFadeAlpha)
	{
		CdeclCall(0xB81420, apObject, apfFadeAlpha);
	}

	void SetTexture(UInt32 auiIndex, NiTexture* apTexture)
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

STATIC_ASSERT(sizeof(BSShaderBloodSplatterProperty) == 0x70);

struct BSSplatterData
{
	float fAge;
	float fDuration;
	float fAlpha;
	UInt32 uiCount;
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

	static __forceinline NiNode* CreateGeometry(UInt32 auiCount, float afSizeMult, float afOpacityMult)
	{
		return CdeclCall<NiNode*>(0x4DF040, auiCount, afSizeMult, afOpacityMult);
	}

	static void ActivateAlt(UInt32 auiCount, float afDuration, float afSizeMult, float afOpacityMult,
	                        NiTexture* apAlphaTex, NiTexture* apColorTex, NiTexture* apFlareTex)
	{
#if 0
		CdeclCall(0x4DE8E0, auiCount, afDuration, 0, afSizeMult, afOpacityMult);
#else
		if (!IsEnabled() || auiCount == 0)
			return;

		NiNode* pNewNode = CreateGeometry(auiCount, afSizeMult, afOpacityMult);
		(*(UInt32*)0x11C77DC) += auiCount;

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
