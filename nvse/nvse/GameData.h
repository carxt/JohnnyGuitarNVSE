#pragma once

#include "GameForms.h"
#include "GameExtraData.h"
#include "Utilities.h"

class TESCaravanDeck;
class MediaSet;
class TESRegionManager;
class BSFile;

struct ChunkAndFormType {
	uint32_t		chunkType;	// ie
	uint32_t		formType;	// ie 0x2A
	const char* formName;	// ie 'NPC_'
};

#if 1
static const uint32_t _ModInfo_GetNextChunk = 0x004726B0; // args: none retn: uint32_t subrecordType (third call in TESObjectARMO_LoadForm)
static const uint32_t _ModInfo_GetChunkData = 0x00472890;	// args: void* buf, uint32_t bufSize retn: bool readSucceeded (fifth call in TESObjectARMO_LoadForm)
static const uint32_t _ModInfo_Read32 = 0x004727F0;	// args: void* buf retn: void (find 'LPER', then next call, still in TESObjectARMO_LoadForm)
static const uint32_t _ModInfo_HasMoreSubrecords = 0x004726F0;	// Last call before "looping" to GetNextChunk in TESObjectARMO_LoadForm.
static const uint32_t _ModInfo_InitializeForm = 0x00472F60;	// args: TESForm* retn: void (second call in TESObjectARMO_LoadForm)

// addresses of static ModInfo members holding type info about currently loading form
static uint32_t* s_ModInfo_CurrentChunkTypeCode = (uint32_t*)0x011C54F4;
static uint32_t* s_ModInfo_CurrentFormTypeEnum = (uint32_t*)0x011C54F0;
// in last call (SetStaticFieldsAndGetFormTypeEnum) of first call (ModInfo__GetFormInfoTypeID) from _ModInfo_InitializeForm
		//		s_ModInfo_CurrentChunkTypeCode is first cmp
		//		s_ModInfo_CurrentChunkTypeEnum is next mov
static const ChunkAndFormType* s_ModInfo_ChunkAndFormTypes = (const ChunkAndFormType*)0x01187008;	// Array used in the loop in SetStaticFieldsAndGetFormTypeEnum, starts under dd offset aNone

static uint8_t** g_CreatedObjectData = (uint8_t**)0x011C54CC;	// pointer to FormInfo + form data, filled out by TESForm::SaveForm()
static uint32_t* g_CreatedObjectSize = (uint32_t*)0x011C54D0;
// in first call (Form_startSaveForm) in TESObjectARMO__SaveForm:
//		g_CreatedObjectSize is set to 18h
//		g_CreatedObjectData is set to the eax result of the next call
#elif EDITOR
#else
#error
#endif

// 10
class BoundObjectListHead {
public:
	BoundObjectListHead();
	~BoundObjectListHead();

	uint32_t			boundObjectCount;	// 0
	TESBoundObject* first;			// 4
	TESBoundObject* last;				// 8
	uint32_t			unkC;				// C
};

struct FormRecordData {
	uint8_t		typeID;		// corresponds to kFormType_XXX
	uint32_t		typeCode;	// i.e. 'GMST', 'FACT'
	uint32_t		unk08;		// only seen zero
};

struct ChunkHeader {
	uint32_t	type : 4;	// i.e. 'XGRD', 'DATA'
	uint16_t	size : 2;
};

struct ModInfo		// referred to by game as TESFile
{
	ModInfo();
	~ModInfo();

	// 18 info about currently loading form
	struct FormInfo  // Record Header in FNVEdit
	{
		uint32_t		recordType;			// 00 i.e. 'FACT', 'GMST'						Signature
		uint32_t		dataSize;			// 04 looks like size of entire record			Data Size
		uint32_t		formFlags;			// 08 copied to TESForm->flags					Record Flags
		uint32_t		formID;				// 0C											FormID
		uint32_t		unk10;				// 10											Version Control Info 1
		uint16_t		formVersion;		// 14 always initialized to 0F on SaveForm.		Form Version
		uint16_t		unk16;				// 16                                           Version Control Info 2
	};

	// 18 info about current group of form
	struct GroupInfo  // Record Header in FNVEdit
	{
		uint32_t		recordType;			// 00 'GRUP'									Signature
		uint32_t		groupSize;			// 04 Size of entire record						Size
		uint32_t		groupLabel;			// 08 copied to TESForm->flags					Label
		uint32_t		groupType;			// 0C forms, dialog, cell...					Type
		uint32_t		unk10;				// 10											Stamp
		uint16_t		unk14;				// 14											Part of Unknown
		uint16_t		unk16;				// 16                                           Part of Unknown
	};

	struct FileHeader	// File header in FNVEdit Signature 'HEDR'
	{
		float version;			//	00
		uint32_t	recordCount;	//	04
		uint32_t	nextObectID;	//	08
	};

	struct	MasterSize	// Data member of the master list in WIN32_FIND_DATA format
	{
		uint32_t	low;
		uint32_t	high;
	};

	tList<uint32_t>						unkList;			// 000 treated as ModInfo during InitializeForm, looks to be a linked list of modInfo
	uint32_t /*NiTPointerMap<TESFile*>*/* pointerMap;		// 008
	uint32_t								unk00C;				// 00C
	BSFile* unkFile;			// 010
	uint32_t								unk014;				// 014
	void* unk018;			// 018 seen all zeroes. size unknown, seen not valid pointer in FalloutNV.esm
	void* unk01C;			// 01C as above
	char								name[0x104];		// 020
	char								filepath[0x104];	// 124
	uint32_t								unk228;				// 228
	uint32_t								unk22C;				// Masters are init'd to dword_1186740 (0x2800) same val as BSFile+10? Buffer size ?
	uint32_t								unk230;				// 230
	uint32_t								unk234;				// 234
	uint32_t								unk238;				// 238
	uint32_t								unk23C;				// 23C
	FormInfo							formInfo;			// 240
	ChunkHeader							subRecordHeader;	// 258
	uint32_t								unk260;				// 260 could be file size, has it is compared with fileOffset during load module. But filesize would be an Int64 !
	uint32_t								fileOffset;			// 264
	uint32_t								dataOffset;			// 268 index into dataBuf
	uint32_t								subrecordBytesRead;	// 26C generates error on Read if != expected length
	FormInfo							writeInfo;			// 270 "used" to add record to the plugin.
	uint32_t								writeOffset;		// 288
	uint32_t								subrecordBytesToWrite;	// 28C
	tList<uint32_t>						tList290;			// 290 looks to be a list of form or a list of formInfo. referenced from TESForm::WriteForm
	uint8_t								unk298;				// 298
	uint8_t								bIsBigEndian;		// 299
	uint8_t								unk29A;				// 29A
	uint8_t								pad29B;
	WIN32_FIND_DATA						fileData;			// 29C
	FileHeader							header;				// 3DC
	uint8_t								flags;				// 3E8	Bit 0 is ESM . Runtime: Bit 2 is Valid, Bit 3 is Unselected Editor: 2 is selected, 3 is active, 4 may be invalid, 6 is endian, 14 controls VCI.
	uint8_t								pad3E9[3];
	tList<char*>* refModNames;		// 3EC	paired with 3F0
	uint32_t								unk3F0;				// 3F0
	tList<MasterSize*>* refModData;		// 3F4 most likely full of 0
	uint32_t								unk3F8;				// 3F8
	uint32_t								numRefMods;			// 3FC related to modindex; see 4472D0
																// formIDs in mod are as saved in GECK, must fix up at runtime
	ModInfo** refModInfo;		// 400 used to look up modInfo based on fixed mod index, double-check
	uint32_t								unk404;				// 404
	uint32_t								unk408;				// 408
	uint8_t								modIndex;			// 40C init to 0xFF
	uint8_t								pad40D[3];
	BSString								author;				// 410
	BSString								description;		// 418
	void* dataBuf;			// 420
	uint32_t								dataBufSize;		// 424 looks like size of entire record
	uint8_t								unk428;				// 428 decide if forms needs to be reloaded on LoadFiles
	uint8_t								pad429[3];

	// In Editor: 430 = ONAM array and 434 ONAM array count. Allocated at 0438

	bool IsLoaded() const { return true; }

	const char* GetName() const { return name; }

#if !EDITOR
	/*** used by TESForm::LoadForm() among others ***/
	MEMBER_FN_PREFIX(ModInfo);
	DEFINE_MEMBER_FN(GetNextChunk, uint32_t, _ModInfo_GetNextChunk);	// returns chunk type
	DEFINE_MEMBER_FN(GetChunkData, bool, _ModInfo_GetChunkData, uint8_t* buf, uint32_t bufSize); // max size, not num to read
	DEFINE_MEMBER_FN(Read32, void, _ModInfo_Read32, void* out);
	DEFINE_MEMBER_FN(HasMoreSubrecords, bool, _ModInfo_HasMoreSubrecords);
#endif
};

static_assert(sizeof(WIN32_FIND_DATA) == 0x140);
static_assert(sizeof(ModInfo) == 0x42C);

struct ModList {
	tList<ModInfo>		modInfoList;		// 00
	uint32_t				loadedModCount;		// 08
	ModInfo* loadedMods[0xFF];	// 0C
};
static_assert(sizeof(ModList) == 0x408);

// 5B8
class DataHandler {
public:
	DataHandler();
	~DataHandler();

	uint32_t							unk00;					// 000
	BoundObjectListHead* boundObjectList;		// 004
	tList<TESPackage>				packageList;			// 008
	tList<TESWorldSpace>			worldSpaceList;			// 010
	tList<TESClimate>				climateList;			// 018
	tList<TESImageSpace>			imageSpaceList;			// 020
	tList<TESImageSpaceModifier>	imageSpaceModList;		// 028
	tList<TESWeather>				weatherList;			// 030
	tList<EnchantmentItem>			enchantmentItemList;	// 038
	tList<SpellItem>				spellItemList;			// 040
	tList<BGSHeadPart>				headPartList;			// 048
	tList<TESHair>					hairList;				// 050
	tList<TESEyes>					eyeList;				// 058
	tList<TESRace>					raceList;				// 060
	tList<BGSEncounterZone>			encounterZoneList;		// 068
	tList<TESLandTexture>			landTextureList;		// 070
	tList<BGSCameraShot>			cameraShotList;			// 078
	tList<TESClass>					classList;				// 080
	tList<TESFaction>				factionList;			// 088
	tList<TESReputation>			reputationList;			// 090
	tList<TESChallenge>				challengeList;			// 098
	tList<TESRecipe>				recipeList;				// 0A0
	tList<TESRecipeCategory>		recipeCategoryList;		// 0A8
	tList<TESAmmoEffect>			ammoEffectList;			// 0B0
	tList<TESCasino>				casinoList;				// 0B8
	tList<TESCaravanDeck>			caravanDeckList;		// 0C0
	tList<Script>					scriptList;				// 0C8
	tList<TESSound>					soundList;				// 0D0
	tList<BGSAcousticSpace>			acousticSpaceList;		// 0D8
	tList<BGSRagdoll>				ragdollList;			// 0E0
	tList<TESGlobal>				globalList;				// 0E8
	tList<BGSVoiceType>				voiceTypeList;			// 0F0
	tList<BGSImpactData>			impactDataList;			// 0F8
	tList<BGSImpactDataSet>			impactDataSetList;		// 100
	tList<TESTopic>					topicList;				// 108
	tList<TESTopicInfo>				topicInfoList;			// 110
	tList<TESQuest>					questList;				// 118
	tList<TESCombatStyle>			combatStyleList;		// 120
	tList<TESLoadScreen>			loadScreenList;			// 128
	tList<TESWaterForm>				waterFormList;			// 130
	tList<TESEffectShader>			effectShaderList;		// 138
	tList<BGSProjectile>			projectileList;			// 140
	tList<BGSExplosion>				explosionList;			// 148
	tList<BGSRadiationStage>		radiationStageList;		// 150
	tList<BGSDehydrationStage>		dehydrationStageList;	// 158
	tList<BGSHungerStage>			hungerStageList;		// 160
	tList<BGSSleepDeprevationStage>	sleepDepriveStageList;	// 168
	tList<BGSDebris>				debrisList;				// 170
	tList<BGSPerk>					perkList;				// 178
	tList<BGSBodyPartData>			bodyPartDataList;		// 180
	tList<BGSNote>					noteList;				// 188
	tList<BGSListForm>				listFormList;			// 190
	tList<BGSMenuIcon>				menuIconList;			// 198
	tList<TESObjectANIO>			anioList;				// 1A0
	tList<BGSMessage>				messageList;			// 1A8
	tList<BGSLightingTemplate>		lightingTemplateList;	// 1B0
	tList<BGSMusicType>				musicTypeList;			// 1B8
	tList<TESLoadScreenType>		loadScreenTypeList;		// 1C0
	tList<MediaSet>					mediaSetList;			// 1C8
	tList<MediaLocationController>	mediaLocControllerList;	// 1D0
	TESRegionList* regionList;			// 1D8
	NiTArray<TESObjectCELL*>		cellArray;				// 1DC
	NiTArray<BGSAddonNode*>			addonArray;				// 1EC

	uint32_t							unk1FC[3];				// 1FC	208 looks like next created refID
	uint32_t							nextCreatedRefID;		// 208	Init'd to FF000800
	uint32_t							unk20C;					// 20C	last unselected mod in modList. GECK: active ESM
	ModList							modList;				// 210
	uint8_t							unk618;					// 618
	uint8_t							unk619;					// 619
	uint8_t							unk61A;					// 61A	referenced during LoadForm (ie TESSpellList). bit 1 might mean refID to pointer conversion not done. For GECK means save in progress
	uint8_t							unk61B;					// 61B
	uint32_t							unk61C;					// 61C
	uint8_t							unk620;					// 620
	uint8_t							loading;				// 621	Init'd to 0 after loadForms
	uint8_t							unk622;					// 622	referenced during loading of modules
	uint8_t							unk623;					// 623
	TESRegionManager* regionManager;			// 624
	ExtraContainerChanges::Data* vendorContainer;		// 628
	uint32_t							unk62C;					// 62C
	uint32_t							unk630;					// 630
	uint32_t							unk634;					// 634
	uint32_t							unk638;					// 638

	static DataHandler* Get();
	const ModInfo** GetActiveModList();		// returns array of modEntry* corresponding to loaded mods sorted by mod index
	const ModInfo* LookupModByName(const char* modName);
	uint8_t GetModIndex(const char* modName);
	uint8_t GetActiveModCount() const;
	const char* GetNthModName(uint32_t modIndex);

	MEMBER_FN_PREFIX(DataHandler);
#if 1
	DEFINE_MEMBER_FN(DoAddForm, uint32_t, 0x004603B0, TESForm* pForm);	// stupid name is because AddForm is redefined in windows header files
#elif EDITOR
#else
#error
#endif

	TESQuest* GetQuestByName(const char* questName);
};

static_assert(sizeof(DataHandler) == 0x63C);
