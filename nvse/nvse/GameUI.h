#pragma once

#include "GameExtraData.h"
#include "GameForms.h"
#include "GameTiles.h"
#include "GameTypes.h"
#include "GameSound.h"

struct BGSSaveLoadFileEntry;
struct PerkRank;
struct VATSHighlightData;
class Menu;
class SceneGraph;
class FOPipboyManager;
class NiObject;
class TESObjectREFR;
class NiNode;
class BSShaderAccumulator;
class ShadowSceneNode;
class NiSourceTexture;
class FORenderedMenu;
typedef Menu* (*_TempMenuByType)(uint32_t menuType);
extern const _TempMenuByType TempMenuByType;

// 584
class InterfaceManager {
public:
	InterfaceManager();
	~InterfaceManager();

	static InterfaceManager* GetSingleton(void);
	static bool					IsMenuVisible(uint32_t menuType);
	static Menu* GetMenuByType(uint32_t menuType);
	static Menu* TempMenuByType(uint32_t menuType);
	//static TileMenu *			GetMenuByPath(const char * componentPath, const char ** slashPos);
	//static Tile::Value *		GetMenuComponentValue(const char * componentPath);
	//static Tile *				GetMenuComponentTile(const char * componentPath);

	uint32_t GetTopVisibleMenuID();
	Tile* GetActiveTile();
	VATSHighlightData* GetVATSHighlightData() {
		return ThisCall<VATSHighlightData*>(0x602170, this);
	}

	uint32_t					flags;				// 000
	SceneGraph* sceneGraph004;		// 004
	SceneGraph* sceneGraph008;		// 008
	uint32_t					currentMode;		// 00C	1 = GameMode; 2 = MenuMode
	uint32_t					unk010;				// 010
	uint32_t					unk014;				// 014
	uint32_t					pickLength;			// 018
	uint32_t					unk01C;				// 01C
	uint8_t					byte020;			// 020
	uint8_t					byte021;			// 021
	uint8_t					byte022;			// 022
	uint8_t					byte023;			// 023
	uint32_t					unk024;				// 024
	TileImage* cursor;			// 028
	float					flt02C;				// 02C
	float					flt030;				// 030
	float					flt034;				// 034
	float					cursorX;			// 038
	float					flt03C;				// 03C
	float					cursorY;			// 040
	float					mouseWheel;			// 044	-120.0 = down; 120.0 = up
	float					flt048;				// 048
	Tile* draggedTile;		// 04C
	int						unk050;				// 050
	float					flt054;				// 054
	float					flt058;				// 058
	int						unk05C;				// 05C
	int						unk060;				// 060
	int						unk064;				// 064
	uint32_t					unk068[2];			// 068
	tList<TESObjectREFR>	selectableRefs;		// 070
	uint32_t					unk078;				// 078
	bool					debugText;			// 07C
	uint8_t					byte07D;			// 07D
	uint8_t					byte07E;			// 07E
	uint8_t					byte07F;			// 07F
	NiNode* niNode080;			// 080
	NiNode* niNode084;			// 084
	uint32_t					unk088;				// 088
	BSShaderAccumulator* shaderAccum08C;	// 08C
	BSShaderAccumulator* shaderAccum090;	// 090
	ShadowSceneNode* shadowScene094;	// 094
	ShadowSceneNode* shadowScene098;	// 098
	Tile* menuRoot;			// 09C
	Tile* globalsTile;		// 0A0	globals.xml
	NiNode* unk0A4;			// 0A4 saw Tile? seen NiNode
	uint32_t					unk0A8;				// 0A8
	NiObject* unk0AC;			// 0AC seen NiAlphaProperty
	uint32_t					unk0B0[3];			// 0B0
	Tile* activeTileAlt;		// 0BC
	uint32_t					unk0C0;				// 0C0
	uint32_t					unk0C4;				// 0C4
	uint8_t					byte0C8;			// 0C8
	uint8_t					byte0C9;			// 0C9
	uint8_t					byte0CA;			// 0CA
	uint8_t					byte0CB;			// 0CB
	Tile* activeTile;		// 0CC
	Menu* activeMenu;		// 0D0
	Tile* tile0D4;			// 0D4
	Menu* menu0D8;			// 0D8
	uint32_t					unk0DC[2];			// 0DC
	uint8_t					msgBoxButton;		// 0E4 -1 if no button pressed
	uint8_t					byte0E5;			// 0E5
	uint8_t					byte0E6;			// 0E6
	uint8_t					byte0E7;			// 0E7
	uint32_t					unk0E8;				// 0E8
	uint8_t					byte0EC;			// 0EC
	uint8_t					byte0ED;			// 0ED
	uint8_t					byte0EE;			// 0EE
	uint8_t					byte0EF;			// 0EF
	TESObjectREFR* debugSelection;	// 0F0	compared to activated object during Activate
	uint32_t					unk0F4;				// 0F4
	uint32_t					unk0F8;				// 0F8
	TESObjectREFR* crosshairRef;		// 0FC
	uint32_t					unk100[4];			// 100
	uint8_t					byte110;			// 110
	uint8_t					pad111[3];			// 111
	uint32_t					menuStack[10];		// 114
	void* ptr13C;			// 13C	Points to a struct, possibly. First member is *bhkSimpleShapePhantom
	uint32_t					unk140[5];			// 140
	uint32_t					unk154;				// 154
	uint32_t					unk158;				// 158
	uint32_t					unk15C;
	uint32_t					time160;
	uint32_t					ptr164;
	uint8_t					isRenderedMenuSet;
	uint8_t					gap169[3];
	FORenderedMenu* renderedMenu;
	uint8_t					isMovedMouseInRenderedMenu;
	uint8_t					byte171;			// 171
	uint8_t					byte172;			// 172
	uint8_t					byte173;			// 173
	FOPipboyManager* pipboyManager;		// 174
	uint32_t* unk178;				// 178
	NiTArray<uint32_t>		array17C;			// 17C NiTPrimitiveArray@PackedMenu@BGSMenuPacker
	uint32_t					unk18C[130];		// 18C
	NiObject* unk394;			// 394 seen NiSourceTexture
	uint32_t					unk398[47];			// 398
	NiTArray<uint32_t>		array454;			// 454 NiTPrimitiveArray@TextureType@BSTextureManager
	NiTArray<uint32_t>		array464;			// 464 NiTPrimitiveArray@FilterMode@NiTexturingProperty
	uint32_t					unk474[16];			// 474
	uint8_t					byte4B4;			// 4B4
	uint8_t					byte4B5;			// 4B5
	uint8_t					byte4B6;			// 4B6
	uint8_t					byte4B7;			// 4B7
	uint32_t					unk4B8;				// 4B8
	uint32_t					pipBoyMode;			// 4BC
	uint32_t					unk4C0[48];			// 4C0
};
static_assert(sizeof(InterfaceManager) == 0x580);

struct HighlightedRef {
	TESObjectREFR* refr;
	NiNode* node;
};

struct VATSHighlightData {
	uint32_t highlightState;
	HighlightedRef highlightMain;
	uint32_t numHighlighted;
	int32_t flashingRefIndex;
	HighlightedRef highlightedRefs[32];
};

void Debug_DumpMenus(void);

enum {
	kMenuType_Min = 0x3E9,
	kMenuType_Message = kMenuType_Min,
	kMenuType_Inventory,
	kMenuType_Stats,
	kMenuType_HUDMain,
	kMenuType_Loading = 0x3EF,
	kMenuType_Container,
	kMenuType_Dialog,
	kMenuType_SleepWait = 0x3F4,
	kMenuType_Start,
	kMenuType_LockPick,
	kMenuType_Quantity = 0x3F8,
	kMenuType_Map = 0x3FF,
	kMenuType_Book = 0x402,
	kMenuType_LevelUp,
	kMenuType_Repair = 0x40B,
	kMenuType_RaceSex,
	kMenuType_Credits = 0x417,
	kMenuType_CharGen,
	kMenuType_TextEdit = 0x41B,
	kMenuType_Barter = 0x41D,
	kMenuType_Surgery,
	kMenuType_Hacking,
	kMenuType_VATS,
	kMenuType_Computers,
	kMenuType_RepairServices,
	kMenuType_Tutorial,
	kMenuType_SpecialBook,
	kMenuType_ItemMod,
	kMenuType_LoveTester = 0x432,
	kMenuType_CompanionWheel,
	kMenuType_TraitSelect,
	kMenuType_Recipe,
	kMenuType_SlotMachine = 0x438,
	kMenuType_Blackjack,
	kMenuType_Roulette,
	kMenuType_Caravan,
	kMenuType_Trait = 0x43C,
	kMenuType_Max = kMenuType_Trait,
};

struct EventCallbackScripts;

class Menu {
public:
	Menu();
	~Menu();

	virtual Menu* Destructor(bool doFree);
	virtual void	SetField(uint32_t idx, Tile* value);
	virtual void	Unk_02(uint32_t arg0, uint32_t arg1);
	virtual void	HandleClick(int32_t tileID, Tile* clickedTile);
	virtual void	HandleMouseover(uint32_t arg0, Tile* activeTile);	//	Called on mouseover, activeTile is moused-over Tile
	virtual void	Unk_05(uint32_t arg0, uint32_t arg1);
	virtual void	Unk_06(uint32_t arg0, uint32_t arg1, uint32_t arg2);
	virtual void	Unk_07(uint32_t arg0, uint32_t arg1, uint32_t arg2);
	virtual void	Unk_08(uint32_t arg0, uint32_t arg1);
	virtual void	Unk_09(uint32_t arg0, uint32_t arg1);
	virtual void	Unk_0A(uint32_t arg0, uint32_t arg1);
	virtual void	Unk_0B(void);	// Called every frame while the menu is active
	virtual bool	HandleKeyboardInput(uint32_t inputChar);	// Return false for handling keyboard shortcuts
	virtual uint32_t	GetID(void);
	virtual bool	Unk_0E(uint32_t arg0, uint32_t arg1);
	virtual void	Unk_0F(void);
	virtual void	Unk_10(void);
	virtual void	Unk_11(void);

	TileMenu* tile;		// 04
	uint32_t			unk08;		// 08
	uint32_t			unk0C;		// 0C
	uint32_t			unk10;		// 10
	uint32_t			unk14;		// 14
	uint32_t			unk18;		// 18
	uint32_t			unk1C;		// 1C
	uint32_t			id;			// 20
	uint32_t			unk24;		// 24

	Menu* HandleMenuInput(int tileID, Tile* clickedTile);
	Tile* AddTileFromTemplate(Tile* destTile, const char* templateName, uint32_t arg3);
};

// 170
class TESNPC;
class RaceSexMenu : public Menu		// 1036
{
public:
	RaceSexMenu();
	~RaceSexMenu();

	uint32_t				unk028[44];		// 028
	TESNPC* npc;			// 0D8
	uint32_t				unk0DC[37];		// 0DC

	void UpdatePlayerHead(void);
};

class LevelUpMenu : public Menu {
public:
	LevelUpMenu();
	~LevelUpMenu();
	uint32_t isPerkMenu;
	TileText* tile2C;
	TileImage* tile30;
	TileImage* tile34;
	TileImage* tile38;
	TileText* tile3C;
	TileText* tile40;
	TileImage* tile44;
	TileImage* tile48;
	TileImage* tileBackBtn;
	TileImage* tile50;
	uint32_t unk54;
	uint32_t unk58;
	uint32_t unk5C;
	uint32_t unk60;
	uint32_t listBoxActorValue[12];
	uint32_t listBoxPerk[12];
	uint32_t unkC4[2];
};

template <typename Item> struct ListBoxItem
{
	Tile* tile;
	Item  object;
	uint8_t byte08;
	uint8_t pad09[3];
};

// 30
template <typename Item> class ListBox : public BSSimpleList<ListBoxItem<Item*>*>
{
public:
	virtual bool	SetSelectedTile(Tile* tile) { return false; };
	virtual Tile*	GetSelectedTile(void) { return nullptr; };
	virtual Tile*	HandleKeyboardInput(int code) { return nullptr; };
	virtual bool	IsMenuEqual(void* that) { return false; };
	virtual void	ScrollToHighlight(void) {};
	virtual Tile*	GetTileByIndex(int index, char isNotTileListIndex) { return nullptr; };
	virtual void	Destructor(bool doFree) {};
	virtual void	FreeAllTiles(void) {};
	virtual void	Sort(signed int(__cdecl*)(Item*, Item*)) {};

	enum
	{
		kFlag_RecalculateHeightsOnInsert = 1,
		kFlag_FreeContChangeOnListItemDestruction = 2, // assumes the object is a ContChangesEntry - do not set this if the object isn't one...
	};

	Tile* parentTile;	// 0C
	Tile* selected;		// 10
	Tile* scrollBar;		// 14
	const char* templateName;	// 18
	uint16_t			itemCount;		// 1C
	uint16_t			pad1E;			// 1E
	float			unk20;			// 20
	float			storedListIndex;// 24
	float			storedScrollbarPos;	// 28
	uint16_t			flags;			// 2C
	uint16_t			pad2E;			// 2E

	Item* GetSelected()
	{
		BSSimpleList<ListBoxItem<Item*>*>* iter = this->GetHead();
		ListBoxItem<Item*>* item;
		do
		{
			item = iter->GetItem();
			if (item && (item->tile == selected))
				return item->object;
		} while (iter = iter->GetNext());
		return NULL;
	}

	Tile* GetNthTile(int32_t index)
	{
		if (index >= 0)
		{
			BSSimpleList<ListBoxItem<Item*>*>* iter = this->GetHead();
			do
			{
				if (!index)
				{
					return iter->GetItem() ? iter->GetItem()->tile : NULL;
				}
				index--;
			} while (iter = iter->GetNext());
		}
		return NULL;
	}

	typedef bool(__cdecl* FilterFunction)(Item* form);
	void Filter(FilterFunction callback)
	{
		ThisCall(0x729FE0, this, callback);
	}

	// identical to Filter, but hooked by InventorySortButton for filtering contchanges
	void FilterAlt(FilterFunction callback)
	{
		ThisCall(0x730BB0, this, callback);
	}

	// Identical to Filter, but passing a value instead of a pointer
	void FilterVal(bool(__cdecl* callback)(Item))
	{
		ThisCall(0x730BB0, this, callback);
	}

	typedef void(__cdecl* ForEachFunc)(Tile*, Item*);
	void ForEach(ForEachFunc func, int maxIndex1 = -1, int maxIndex2 = 0x7FFFFFFF)
	{
		ThisCall(0x7314C0, this, func, maxIndex1, maxIndex2);
	}

	Tile* GetTileFromItem(Item** item)
	{
		return ThisCall<Tile*>(0x7A22D0, this, item);
	}

	Item* GetItemForTile(Tile* tile)
	{
		BSSimpleList<ListBoxItem<Item*>*>* iter = this->GetHead();
		ListBoxItem<Item*>* item;
		do
		{
			item = iter->GetItem();
			if (item && (item->tile == tile))
				return item->object;
		} while (iter = iter->GetNext());
		return NULL;
	}

	void SaveScrollPosition()
	{
		ThisCall(0x7312E0, this);
	}

	int GetNumVisibleItems()
	{
		return ThisCall<int>(0x71AE60, this);
	}

	void RestorePosition(bool playSound = false)
	{
		ThisCall(0x731360, this, playSound);
	}

	//int32_t(__cdecl* apCompare)(const T& aItem1, const T& aItem2)
	Tile* Insert(Item* item, const char* text, int32_t(*sortingFunction)(const ListBoxItem<Item>*& aItem1, const ListBoxItem<Item>*& aItem2) = nullptr, const char* _templateName = nullptr)
	{
		if (!this->parentTile) return nullptr;
		auto _template = _templateName ? _templateName : this->templateName;
		if (!_template) return nullptr;

		auto menu = ThisCall<Menu*>(0xA03C90, this->parentTile);
		Tile* newTile = ThisCall<Tile*>(0xA1DDB0, menu, this->parentTile, _template, nullptr);
		if (!newTile->GetValue(kTileValue_id))
		{
			newTile->SetFloat(kTileValue_id, -1);
		}
		if (text)
		{
			newTile->SetString(kTileValue_string, text);
		}

		auto listItem = (ListBoxItem<Item*>*)GameHeapAlloc(sizeof(ListBoxItem<Item*>));
		listItem->tile = newTile;
		listItem->object = item;
		listItem->byte08 = 0;
		if (sortingFunction)
		{
			this->InsertSorted(listItem, sortingFunction);
			if (this->flags & kFlag_RecalculateHeightsOnInsert)
			{
				ThisCall(0x71A670, this);
			}
		}
		else
		{
			this->AddHead(listItem);
			if (this->flags & kFlag_RecalculateHeightsOnInsert)
			{
				ThisCall(0x7269D0, this, newTile);
				ThisCall(0x71AD30, this);
			}
			newTile->SetFloat(kTileValue_listindex, this->itemCount++);
		}

		if (this->itemCount == 1)
		{
			auto numVisibleItemsTrait = TraitNameToID("_number_of_visible_items");
			if (this->parentTile->GetValueFloat(numVisibleItemsTrait) > 0)
			{
				auto valPtr = ThisCall<Tile::Value*>(0xA00E90, this->parentTile, kTileValue_height);
				ThisCall(0xA09200, valPtr);
				ThisCall(0xA09130, valPtr, kTileValue_Copy, newTile, kTileValue_height);

				auto numVisible = this->parentTile->GetValueFloat(numVisibleItemsTrait);
				ThisCall(0xA09080, valPtr, kTileValue_Mul, numVisible);
				ThisCall(0xA09410, valPtr, 0);
			}
		}

		return newTile;
	}

	Tile* InsertVal(Item item, const char* text, signed int (*sortingFunction)(ListBoxItem<Item>* a1, ListBoxItem<Item>* a2) = nullptr, const char* _templateName = nullptr)
	{
		return ThisCall<Tile*>(0x754690, this, item, text, sortingFunction, _templateName);
	}

	void HighlightLastItem()
	{
		int lastIndex = this->itemCount - 1;
		Tile* tile = this->GetNthTile(lastIndex);

		this->SetSelectedTile(tile);
		this->ScrollToHighlight();
	}

	void ScrollToTop()
	{
		this->storedScrollbarPos = 0;
		this->storedListIndex = 0;
		this->RestorePosition();
	}

	void SetParentEnabled(bool isEnabled)
	{
		static uint32_t enabledTrait = TraitNameToID("_enabled");
		parentTile->SetFloat(enabledTrait, isEnabled);
	}

	bool IsEnabled()
	{
		static uint32_t enabledTrait = TraitNameToID("_enabled");
		return parentTile && parentTile->GetValueFloat(enabledTrait);
	}

	void Init()
	{
		// initialises the fields and appends the menu list to the global listbox array
		ThisCall(0x723750, this);
	}

	void Destroy()
	{
		ThisCall(0x723820, this);
	}
};

// 230
class MapMenu : public Menu
{
public:
	MapMenu();
	~MapMenu();

	enum MapMenuTabs
	{
		kLocalMap = 0x20,
		kWorldMap = 0x21,
		kQuests = 0x22,
		kMisc = 0x23,
		kRadio = 0x24,
	};

	enum TileIDs
	{
		kTile_MM_Headline_LocationInfo = 0x0,
		kTile_MM_Headline_TimeDateInfo = 0x1,
		kTile_MM_LocalMap_ParentImage = 0x2,
		kTile_MM_LocalMapCursor = 0x3,
		kTile_MM_WorldMap_ParentImage = 0x4,
		kTile_MM_WorldMapCursor = 0x5,
		kTile_MM_MapHighlightBox = 0x6,
		kTile_MM_QuestsList = 0x7,
		kTile_MM_NotesList = 0x8,
		kTile_MM_Notes_SelectedNoteHighlight = 0x9,
		kTile_MM_RadioStationList = 0xA,
		kTile_MM_Headline_ChallengeType = 0x15,
		kTile_MM_ChallengeList = 0x13,
		kTile_MM_Challenge_SelectedHighlight = 0x14,
		kTile_MM_ButtonA = 0xB,
		kTile_MM_ButtonX = 0xC,
		kTile_MM_ButtonY = 0x12,
		kTile_MM_DataRect = 0xD,
		kTile_MM_DataTextRect = 0xE,
		kTile_MM_QuestObjectivesList = 0xF,
		kTile_MM_Waveform = 0x10,
		kTile_MM_Tabline = 0x11,
		kTile_MM_LocationMarker = 0x1A,
		kTile_MM_PlayerPlacedMarker = 0x1C,
	};

	union
	{
		Tile* tiles[21];
		struct
		{
			TileText* MM_Headline_LocationInfo;			// 028	MM_MainRect\MM_HeadlineRect\MM_Headline_LocationInfo
			TileText* MM_Headline_TimeDateInfo;			// 02C	MM_MainRect\MM_HeadlineRect\MM_Headline_TimeDateInfo
			TileImage* MM_LocalMap_ParentImage;			// 030	MM_MainRect\MM_LocalMap_ClipWindow\MM_LocalMap_ParentImage
			TileImage* MM_LocalMapCursor;				// 034	MM_MainRect\MM_LocalMap_ClipWindow\MM_LocalMapCursor
			TileImage* MM_WorldMap_ParentImage;			// 038	MM_MainRect\MM_WorldMap_ClipWindow\MM_WorldMap_ParentImage
			TileImage* MM_WorldMapCursor;				// 03C	MM_MainRect\MM_WorldMap_ClipWindow\MM_WorldMapCursor
			TileRect* MM_MapHighlightBox;				// 040	MM_MainRect\MM_Highlight_ClipWindow\MM_MapHighlightBox
			TileImage* MM_QuestsList;					// 044	MM_MainRect\MM_QuestsList
			TileImage* MM_NotesList;					// 048	MM_MainRect\MM_NotesList
			TileImage* MM_Notes_SelectedNoteHighlight;	// 04C	MM_MainRect\MM_NotesList\MM_Notes_SelectedNoteHighlight
			TileImage* MM_RadioStationList;				// 050	MM_MainRect\MM_RadioStationList
			TileImage* MM_ButtonA;						// 054	MM_MainRect\MM_ButtonRect\MM_ButtonA
			TileImage* MM_ButtonX;						// 058	MM_MainRect\MM_ButtonRect\MM_ButtonX
			TileRect* MM_DataRect;						// 05C	MM_MainRect\MM_DataRect
			TileImage* MM_DataTextRect;					// 060	MM_MainRect\MM_DataRect\MM_DataTextRect
			TileImage* MM_QuestObjectivesList;			// 064	MM_MainRect\MM_DataRect\MM_QuestObjectivesList
			TileImage* MM_Waveform;						// 068	MM_MainRect\MM_WaveformRect\MM_Waveform
			TileRect* MM_Tabline;						// 06C	MM_Tabline
			TileImage* MM_ButtonY;						// 070	MM_MainRect\MM_ButtonRect\MM_ButtonY
			TileImage* MM_ChallengeList;				// 074	MM_MainRect\MM_ChallengeList
			TileImage* MM_Challenge_SelectedHighlight;	// 078	MM_MainRect\MM_ChallengeList\MM_Challenge_SelectedHighlight
			TileText* MM_Headline_ChallengeType;		// 07C	MM_MainRect\MM_Headline_ChallengeType
		};
	};

	uint8_t							currentTab;		// 080
	uint8_t							pad081[3];		// 081
	TileImage* tileWorldMap;	// 084
	float							lastRadioAnimationUpdateTime;// 088
	uint8_t							isShowAllNotes;	// 08C
	uint8_t							gap08D[3];
	BGSNote* currentNote;
	uint32_t							timeNoteViewed;
	SoundList						holotapeDialogues;
	BSSimpleArray<char>				holotapeSubtitles;	// 0A8
	SoundList*				currentHolotapeDialogueSound;
	uint8_t							isHolotapeVoicePlaying;
	uint8_t							pad0BD[3];
	float							holotapeTotalTime;
	uint32_t							holotapePlayStartTime;
	float							radioVolume;
	TESQuest* selectedQuest;
	BGSQuestObjective* currentObjective;
	TileImage* mapMarker;		// 0D4
	tList<TESObjectREFR>			mapMarkerList;	// 0D8
	tList<TESObjectREFR>			doorList;		// 0E0
	float						CornerNWPos[2];	// 0E8
	float						CornerSEPos[2];	// 0F0
	TESForm* markerForm;	// 0F8
	float						markerPos[3];		// 0FC
	TESObjectCELL* currentCellOrWorldspace;// 108
	TESWorldSpace* parentmostLastExtDoorWorldspace;// 10C
	uint8_t							currentWorldspaceHasNoParent;// 110
	uint8_t							gap111[3];
	TESObjectREFR* lastExtDoor;	// 114
	TESObjectREFR* selectedMarker;// 118
	TESObjectCELL* localMapInteriorCell;		// 11C
	float						clickStartPos[2];	// 120
	uint32_t							unk128;			// 128
	bool							fogOfWar;		// 12C
	uint8_t							pad12D[3];		// 12D
	ListBox<TESQuest>				questList;		// 130
	ListBox<BGSNote>				noteList;		// 160
	ListBox<TESObjectREFR>			radioRefList;	// 190
	ListBox<BGSQuestObjective>		objectiveList;	// 1C0
	ListBox<TESChallenge>			challengeList;	// 1F0
	BSSimpleArray<Tile>				arr220;			// 220

	static MapMenu* GetSingleton() { return *(MapMenu**)0x11DA368; };

	void PlayHolotape(BGSNote* note, bool playStartSound);

	void StopHolotape();


};
static_assert(sizeof(MapMenu) == 0x230);
extern bool noHolotapeStopSound;

// 94
class MessageMenu : public Menu			// 1001
{
public:
	MessageMenu();
	~MessageMenu();

	TileRect* tile28;		// 28
	TileText* tile2C;		// 2C
	TileImage* tile30;		// 30
	TileText* tile34;		// 34
	TileImage* tile38;		// 38
	TileImage* tile3C;		// 3C
	ListBox<int>		buttonList;		// 40
	uint8_t				unk70;			// 70
	uint8_t				pad71[3];		// 71
	float				unk74[3];		// 74
	uint32_t				unk80[2];		// 80
	uint32_t				tickCount;		// 88
	uint8_t				unk8C;			// 8C
	uint8_t				unk8D;			// 8D
	uint8_t				pad8E[2];		// 8E
	uint32_t				unk90;			// 90
};

typedef ListBox<ContChangesEntry> MenuItemEntryList;

// 124
class InventoryMenu : public Menu		// 1002
{
public:
	InventoryMenu();
	~InventoryMenu();

	TileRect* tile028;		// 028	IM_Headline_PlayerCapsInfo
	TileRect* tile02C;		// 02C	IM_Headline_PlayerHPInfo
	TileRect* tile030;		// 030	IM_Headline_PlayerDRInfo
	TileRect* tile034;		// 034	IM_Headline_PlayerWGInfo
	TileImage* tile038;		// 038	IM_InventoryList
	TileRect* tile03C;		// 03C	IM_HotKeyWheel
	TileImage* tile040;		// 040	IM_EquipButton
	TileImage* tile044;		// 044	IM_DropButton
	TileImage* tile048;		// 048	IM_RepairButton
	TileImage* tile04C;		// 04C	IM_HotkeyButton
	TileImage* tile050;		// 050	IM_CancelButton
	TileImage* tile054;		// 054	IM_ItemIcon
	TileRect* tile058;		// 058	IM_ItemInfoRect
	TileRect* tile05C;		// 05C	IM_Tabline
	TileRect* tile060;		// 060	DAMInfo
	TileRect* tile064;		// 064	DPSInfo
	TileRect* tile068;		// 068	StrengthReqInfo
	TileRect* tile06C;		// 06C	DamageResistInfo
	TileRect* tile070;		// 070	DamageThresholdInfo
	TileImage* tile074;		// 074	IM_ModButton
	TileImage* tile078;		// 078	IM_ItemIconBadge
	TileRect* tile07C;		// 07C	IM_Headline_PlayerDTInfo
	TileText* tile080;		// 080	IM_StrReq
	uint32_t				filter;			// 084
	uint32_t				unk088[12];		// 088
	MenuItemEntryList	itemList;		// 0B8
	TileRect* tile0E8;		// 0E8
	TileRect* tile0EC;		// 0EC
	TileRect* tile0F0;		// 0F0
	TileRect* tile0F4;		// 0F4
	TileRect* tile0F8;		// 0F8
	TileRect* tile0FC;		// 0FC
	TileRect* tile100;		// 100
	TileRect* tile104;		// 104
	TileRect* tile108;		// 108
	uint32_t				unk10C[6];		// 10C
};

// 2A4
class StatsMenu : public Menu			// 1003
{
public:
	StatsMenu();
	~StatsMenu();

	struct AlchItemData {
		AlchemyItem* alchItem;
		TileImage* tileImg;
		void* dataPtr;
		bool			(*callback)(void* arg);
	};

	struct StatusEffect;

	struct NamedEffectsList : BSSimpleList<EffectSetting*> {
		virtual ~NamedEffectsList();
	};

	struct StatusEffectList : BSSimpleList<StatusEffect*> {
		virtual ~StatusEffectList() {};
	};

	AlchItemData					alchItemData[4];	// 028	0: Stimpak, 1: Rad-X, 2: RadAway, 3: Doctor's Bag
	NamedEffectsList				effectList;			// 068
	StatusEffect*					pRadEffects;
	StatusEffect*					pH20Effects;
	StatusEffect*					pHungerEffects;
	StatusEffect*					pSleepEffects;
	StatusEffectList				statusEffList;		// 084
	TileImage* tile090;			// 090
	TileImage* tile094;			// 094
	TileImage* tile098;			// 098
	TileImage* tile09C;			// 09C
	TileImage* tile0A0;			// 0A0
	TileImage* tile0A4;			// 0A4
	TileImage* tile0A8;			// 0A8
	TileImage* tile0AC;			// 0AC
	TileImage* tile0B0;			// 0B0
	TileImage* tile0B4;			// 0B4
	TileImage* tile0B8;			// 0B8
	TileImage* tile0BC;			// 0BC
	TileImage* tile0C0;			// 0C0
	TileRect* tile0C4;			// 0C4
	TileImage* tile0C8;			// 0C8
	TileRect* tile0CC;			// 0CC
	TileImage* tile0D0;			// 0D0
	TileRect* tile0D4;			// 0D4
	TileImage* tile0D8;			// 0D8
	TileRect* tile0DC;			// 0DC
	TileImage* tile0E0;			// 0E0
	TileRect* tile0E4;			// 0E4
	TileImage* tile0E8;			// 0E8
	TileRect* tile0EC;			// 0EC
	TileImage* tile0F0;			// 0F0
	TileImage* tile0F4;			// 0F4
	TileImage* tile0F8;			// 0F8
	TileText* tile0FC;			// 0FC
	TileImage* tile100;			// 100
	TileImage* tile104;			// 104
	TileImage* tile108;			// 108
	TileImage* tile10C;			// 10C
	TileImage* tile110;			// 110
	TileImage* tile114;			// 114
	TileImage* tile118;			// 118
	TileText* tile11C;			// 11C
	TileImage* tile120;			// 120
	TileText* tile124;			// 124
	TileText* tile128;			// 128
	TileText* tile12C;			// 12C
	TileRect* tile130;			// 130
	TileRect* tile134;			// 134
	TileRect* tile138;			// 138
	TileRect* tile13C;			// 13C
	TileText* tile140;			// 140
	TileText* tile144;			// 144
	TileImage* tile148;			// 148
	TileImage* tile14C;			// 14C
	TileText* tile150;			// 150
	TileImage* tile154;			// 154
	TileImage* tile158;			// 158
	TileText* tile15C;			// 15C
	TileImage* tile160;			// 160
	TileImage* tile164;			// 164
	TileImage* tile168;			// 168
	TileImage* tile16C;			// 16C
	TileImage* tile170;			// 170
	TileImage* tile174;			// 174
	TileImage* tile178;			// 178
	TileImage* tile17C;			// 17C
	ListBox<uint32_t>					avIndexList180;		// 180
	ListBox<uint32_t>					avIndxeList1B0;		// 1B0
	ListBox<PerkRank>				perkRankList;		// 1E0
	ListBox<uint32_t>					miscStatIDList;		// 210
	ListBox<StatusEffect>			statusEffListBox;	// 240
	ListBox<TESReputation>			reputationList;		// 270
	uint32_t							unk2A0;				// 2A0

	__forceinline static StatsMenu* Get() { return *(StatsMenu**)0x11DACE0; }
};

// 50
class Tile3D : public Tile {
public:
	Tile3D();
	~Tile3D();

	uint32_t			unk38[6];
};

// 278
class HUDMainMenu : public Menu			// 1004
{
public:
	HUDMainMenu();
	~HUDMainMenu();

	struct QueuedMessage {
		char	msgText[0x204];			// 000
		char	iconPate[MAX_PATH];		// 204
		char	soundPath[MAX_PATH];	// 308
		float	displayTime;			// 40C
	};

	struct SubtitleData;

	struct Struct224 {
		uint8_t		byte00;		// 00
		uint8_t		pad01[3];	// 01
		float		flt04;		// 04
		float		flt08;		// 08
		float		flt0C;		// 0C
		float		flt10;		// 10
		uint32_t		unk14;		// 14
		uint32_t		tickCount;	// 18
		uint8_t		byte1C;		// 1C
		uint8_t		byte1D;		// 1D
		uint8_t		pad1E[2];	// 1E
	};
	enum VisibilityFlags {
		kActionPoints = 0x1,
		kHitPoints = 0x2,
		kRadiationMeter = 0x4,
		kEnemyHealth = 0x8,
		kQuestReminder = 0x10,
		kRegionLocation = 0x20,
		kReticleCenter = 0x40,
		kSneakMeter = 0x80,
		kMessages = 0x100,
		kInfo = 0x200,
		kSubtitles = 0x400,
		kHotkeys = 0x800,
		kXpMeter = 0x1000,
		kBreathMeter = 0x2000,
		kExplosivePositioning = 0x4000,
		kCrippledLimbIndicator = 0x8000,
		kHardcoreMode = 0x10000,
	};
	enum HUDStates {
		kHUDState_RECALCULATE = 0x1,
		kHUDState_Normal = 0x2,
		kHUDState_PipBoy = 0x3,
		kHUDState_Pause = 0x4,
		kHUDState_Loading = 0x5,
		kHUDState_Dialog = 0x6,
		kHUDState_VATSMenu = 0x7,
		kHUDState_VATSPlayback = 0x8,
		kHUDState_Container = 0x9,
		kHUDState_BeginSit = 0xA,
		kHUDState_SleepWait = 0xB,
		kHUDState_PlayerDisabledControls = 0xC,
		kHUDState_D = 0xD,
		kHUDState_LevelUpMenu = 0xE,
		kHUDState_Hacking = 0xF,
		kHUDState_Computers = 0x10,
		kHUDState_Message = 0x11,
		kHUDState_SpecialBook = 0x12,
		kHUDState_LoveTester = 0x13,
		kHUDState_VanityCam = 0x14,
		kHUDState_15 = 0x15,
		kHUDState_Aiming = 0x16,
		kHUDState_AimingScope = 0x17,
		kHUDState_IntroMovie = 0x18,
		kHUDState_Gambling = 0x19,
	};

	uint32_t							unk028;			// 028
	TileImage* tile02C;		// 02C	HitPoints\meter
	TileText* tile030;		// 030	HitPoints\justify_right_text
	TileRect* tile034;		// 034	HitPoints\compass_window\compass_icon_group
	TileRect* tile038;		// 038	HitPoints\compass_window\compass_icon_group
	TileRect* tile03C;		// 03C	HitPoints\compass_window\compass_icon_group
	TileImage* tile040;		// 040	HitPoints\compass_window
	TileImage* tile044;		// 044	ActionPoints\meter
	TileText* tile048;		// 048	ActionPoints\justify_right_text
	TileText* tile04C;		// 04C	ActionPoints\justify_right_text
	TileImage* tile050;		// 050	ActionPoints\meter
	TileImage* tile054;		// 054	ActionPoints\MeterBackground
	TileText* tile058;		// 058	ActionPoints\justify_right_text
	TileRect* tile05C;		// 05C	QuestReminder\QuestStages
	TileRect* tile060;		// 060	QuestReminder\QuestAdded
	TileText* tile064;		// 064	Region_Location\justify_left_text
	TileText* tile068;		// 068	Region_Location\justify_left_text
	TileImage* tile06C;		// 06C	RadiationMeter\radiation_bracket
	TileImage* tile070;		// 070	RadiationMeter\radiation_pointer
	TileText* tile074;		// 074	RadiationMeter\radiation_text_value
	TileText* tile078;		// 078	RadiationMeter\radiation_text
	TileImage* tile07C;		// 07C	EnemyHealth\enemy_health_bracket
	TileImage* tile080;		// 080	EnemyHealth\meter
	TileText* tile084;		// 084	EnemyHealth\justify_center_text
	TileText* sneakLabel;	// 088	SneakMeter\sneak_nif
	TileImage* tile08C;		// 08C	Messages\message_icon
	TileText* tile090;		// 090	Messages\justify_left_text
	TileImage* tile094;		// 094	Messages\message_bracket
	TileText* tile098;		// 098	Subtitles\justify_center_text
	TileRect* tile09C;		// 09C	Info\justify_center_hotrect
	TileText* tile0A0;		// 0A0	Info\justify_center_hotrect\PCShortcutLabel
	TileImage* tile0A4;		// 0A4	Info\justify_center_hotrect\xbox_button
	TileText* tile0A8;		// 0A8	Info\justify_center_text
	TileText* tile0AC;		// 0AC	Info\justify_center_text
	TileText* tile0B0;		// 0B0	Info\justify_center_text
	TileText* tile0B4;		// 0B4	Info\justify_right_text
	TileText* tile0B8;		// 0B8	Info\justify_left_text
	TileText* tile0BC;		// 0BC	Info\justify_right_text
	TileText* tile0C0;		// 0C0	Info\justify_left_text
	TileImage* tile0C4;		// 0C4	Info\info_seperator
	TileRect* tile0C8;		// 0C8	Hokeys\hotkey_selector
	TileText* tile0CC;		// 0CC	Hokeys\justify_center_text
	TileImage* tile0D0;		// 0D0	HitPoints\left_bracket
	TileImage* tile0D4;		// 0D4	ActionPoints\right_bracket
	TileImage* tile0D8;		// 0D8	XPMeter\XPBracket
	TileText* tile0DC;		// 0DC	XPMeter\XPAmount
	TileText* tile0E0;		// 0E0	XPMeter\XPLabel
	TileImage* tile0E4;		// 0E4	XPMeter\XPPointer
	TileText* tile0E8;		// 0E8	XPMeter\XPLastLevel
	TileText* tile0EC;		// 0EC	XPMeter\XPNextLevel
	TileText* tile0F0;		// 0F0	XPMeter\XPLevelUp
	TileImage* tile0F4;		// 0F4	ReticleCenter\reticle_center
	TileImage* tile0F8;		// 0F8	crippled_limb_indicator\Face
	TileImage* tile0FC;		// 0FC	crippled_limb_indicator\Head
	TileImage* tile100;		// 100	crippled_limb_indicator\Torso
	TileImage* tile104;		// 104	crippled_limb_indicator\Left_Arm
	TileImage* tile108;		// 108	crippled_limb_indicator\Right_Arm
	TileImage* tile10C;		// 10C	crippled_limb_indicator\Left_Leg
	TileImage* tile110;		// 110	crippled_limb_indicator\Right_Leg
	TileRect* tile114;		// 114	ActionPoints
	TileRect* tile118;		// 118	HitPoints
	TileRect* tile11C;		// 11C	RadiationMeter
	TileRect* tile120;		// 120	EnemyHealth
	TileRect* tile124;		// 124	QuestReminder
	TileRect* tile128;		// 128	Region_Location
	TileRect* tile12C;		// 12C	ReticleCenter
	TileRect* tile130;		// 130	SneakMeter
	TileRect* tile134;		// 134	Messages
	TileRect* tile138;		// 138	Info
	TileRect* tile13C;		// 13C	Subtitles
	TileRect* tile140;		// 140	Hokeys
	TileRect* tile144;		// 144	XPMeter
	Tile3D* tile148;		// 148	BreathMeter
	TileRect* tile14C;		// 14C	Explosive_positioning_rect
	TileRect* tile150;		// 150	crippled_limb_indicator
	TileImage* tile154;		// 154	DDTIcon
	TileImage* tile158;		// 158	DDTIconEnemy
	TileText* tile15C;		// 15C	AmmoTypeLabel
	TileRect* tile160;		// 160	HardcoreMode
	TileText* tile164;		// 164	HardcoreMode\Dehydration
	TileText* tile168;		// 168	HardcoreMode\Sleep
	TileText* tile16C;		// 16C	HardcoreMode\Hunger
	TileImage* tile170;		// 170	DDTIcon
	TileImage* tile174;		// 174	DDTIconEnemyAP
	TileText* tile178;		// 178	HardcoreMode\Rads
	TileText* tile17C;		// 17C	HardcoreMode\LMBs
	TileImage* tile180;		// 180	CNDArrows
	uint32_t							unk184;			// 184
	float							flt188;			// 188
	tList<QueuedMessage>			queuedMessages;	// 18C
	uint32_t							currMsgKey;		// 194
	BSSimpleArray<SubtitleData>		subtitlesArr;	// 198
	uint32_t							unk1A8[4];		// 1A8
	TESObjectREFR* crosshairRef;	// 1B8
	uint32_t							unk1BC;			// 1BC
	uint32_t							visibilityOverrides;	// 1C0
	uint32_t							unk1C4;			// 1C4
	TileRect* tile1C8;		// 1C8	Hokeys\hotkey_selector
	TileRect* tile1CC;		// 1CC	Hokeys\hotkey_selector\HK_Item_0
	uint32_t							unk1D0;			// 1D0
	TileRect* tile1D4;		// 1D4	Hokeys\hotkey_selector\HK_Item_2
	TileRect* tile1D8;		// 1D8	Hokeys\hotkey_selector\HK_Item_3
	TileRect* tile1DC;		// 1DC	Hokeys\hotkey_selector\HK_Item_4
	TileRect* tile1E0;		// 1E0	Hokeys\hotkey_selector\HK_Item_5
	TileRect* tile1E4;		// 1E4	Hokeys\hotkey_selector\HK_Item_6
	TileRect* tile1E8;		// 1E8	Hokeys\hotkey_selector\HK_Item_7
	uint32_t							unk1EC[5];		// 1EC
	NiControllerSequence* niContSeq;		// 200
	uint8_t							byte204;		// 204
	uint8_t							byte205;		// 205
	uint8_t							pad206[2];		// 206
	uint32_t							unk208[5];		// 208
	Actor* healthTarget;	// 21C
	uint32_t							unk220;			// 220
	Struct224						unk224;			// 224
	uint32_t							unk244;			// 244
	uint32_t							unk248[4];		// 248
	tList<uint32_t>					list258;		// 258
	uint8_t							byte260;		// 260
	uint8_t							byte261;		// 261
	uint8_t							pad262[2];		// 262
	tList<uint32_t>					list264;		// 264
	tList<uint32_t>					list26C;		// 26C
	float							flt274;			// 274

	static HUDMainMenu* GetSingleton() { return *(HUDMainMenu**)0x11D96C0; }
};
static_assert(sizeof(HUDMainMenu) == 0x278);

// 5C0
class LoadingMenu : public Menu			// 1007
{
public:
	LoadingMenu();
	~LoadingMenu();

	Tile3D* tile028;		// 028
	TileText* tile02C;		// 02C
	TileText* tile030;		// 030
	TileText* tile034;		// 034
	TileText* tile038;		// 038
	TileText* tile03C;		// 03C
	TileText* tile040;		// 040
	TileText* tile044;		// 044
	TileText* tile048;		// 048
	TileText* tile04C;		// 04C
	TileImage* tile050;		// 050
	Tile3D* tile054;		// 054
	TileImage* tile058;		// 058
	TileText* tile05C;		// 05C
	TileText* tile060;		// 060
	TileText* tile064;		// 064
	TileRect* tile068;		// 068
	TileText* tile06C;		// 06C
	TileRect* tile070;		// 070
	TileText* tile074;		// 074
	TileText* tile078;		// 078
	TileText* tile07C;		// 07C
	TileText* tile080;		// 080
	TileText* tile084;		// 084
	TileText* tile088;		// 088
	TileText* tile08C;		// 08C
	TileText* tile090;		// 090
	TileRect* tile094;		// 094
	TileText* tile098;		// 098
	TileText* tile09C;		// 09C
	TileText* tile0A0;		// 0A0
	TileRect* tile0A4;		// 0A4
	TileImage* tile0A8;		// 0A8
	TileImage* tile0AC;		// 0AC
	TileText* tile0B0;		// 0B0
	TileText* tile0B4;		// 0B4
	TileImage* tile0B8;		// 0B8
	TileImage* tile0BC;		// 0BC
	uint32_t				unk0C0;			// 0C0
	uint32_t				unk0C4;			// 0C4
	uint32_t				unk0C8;			// 0C8
	uint32_t				unk0CC;			// 0CC
	DList<Tile>			list0D0;		// 0D0
	DList<Tile>			list0DC;		// 0DC
	DList<Tile>			list0E8;		// 0E8
	DList<Tile>			list0F4;		// 0F4
	DList<Tile>			list100;		// 100
	uint32_t				unk10C[49];		// 10C
	TESLoadScreen* loadScr1D0;	// 1D0
	void* ptr1D4;		// 1D4
	void* ptr1D8;		// 1D8
	TESLoadScreen* loadScr1DC;	// 1DC
	uint32_t				unk1E0;			// 1E0
	uint32_t				unk1E4;			// 1E4
	TESWorldSpace* worldspace;	// 1E8
	uint32_t				unk1EC[8];		// 1EC
	NiSourceTexture* srcTexture[4];	// 20C
	uint32_t				unk21C;			// 21C
	uint8_t				byte220[2];		// 220
	uint16_t				flags;			// 222
	uint32_t				unk224[231];	// 224
};
static_assert(sizeof(LoadingMenu) == 0x5C0);

// 10C
class ContainerMenu : public Menu		// 1008
{
public:
	ContainerMenu();
	~ContainerMenu();

	TileImage* tile028;		// 028
	TileText* tile02C;		// 02C
	TileImage* tile030;		// 030
	TileText* tile034;		// 034
	TileImage* tile038;		// 038
	TileImage* tile03C;		// 03C
	TileText* tile040;		// 040
	TileImage* tile044;		// 044
	TileImage* tile048;		// 048
	TileImage* tile04C;		// 04C
	TileImage* tile050;		// 050
	TileImage* tile054;		// 054
	TileImage* tile058;		// 058
	TileRect* tile05C;		// 05C
	TileRect* tile060;		// 060
	TileRect* tile064;		// 064
	TileRect* tile068;		// 068
	TileRect* tile06C;		// 06C
	TileRect* tile070;		// 070
	TESObjectREFR* containerRef;	// 074
	tList<void>			list078;		// 078
	uint32_t				unk080;			// 080
	uint32_t				unk084;			// 084
	uint32_t				unk088;			// 088
	uint32_t				leftFilter;		// 08C
	uint32_t				rightFilter;	// 090
	uint32_t				unk094;			// 094
	MenuItemEntryList	leftItems;		// 098
	MenuItemEntryList	rightItems;		// 0C8
	MenuItemEntryList* currentItems;	// 0F8
	uint32_t				unk0FC[4];		// 0FC
};
static_assert(sizeof(ContainerMenu) == 0x10C);

// 13C
class DialogMenu : public Menu			// 1009
{
public:
	DialogMenu();
	~DialogMenu();

	uint32_t				unk028[2];		// 028
	TileImage* tile030;		// 030
	TileText* tile034;		// 034
	TileText* tile038;		// 038
	TileImage* tile03C;		// 03C
	ListBox<int>		topicList;		// 040
	void* unk070;		// 070
	uint32_t				unk074;			// 074
	TESTopicInfo* info078;		// 078
	uint32_t				unk07C;			// 07C
	TESObjectREFR* partnerRef;	// 080
	float				unk084[2];		// 084
	void* unk08C;		// 08C
	void* unk090;		// 090
	TESTopicInfo* infos094[16];	// 094
	void* unk0D4;		// 0D4
	uint32_t				unk0D8[3];		// 0D8
	TESTopicInfo* infos0E4[8];	// 0E4
	uint32_t				unk104[3];		// 104
	TESTopicInfo* infos110[6];	// 110
	float				unk128;			// 128
	void* unk12C;		// 12C	ImageSpaceModifierInstanceDOF
	uint32_t				unk130[3];		// 130
};

// 4C
class SleepWaitMenu : public Menu		// 1012
{
public:
	SleepWaitMenu();
	~SleepWaitMenu();

	TileText* tile28;		// 28
	TileImage* tile2C;		// 2C
	TileText* tile30;		// 30
	TileText* tile34;		// 34
	TileImage* tile38;		// 38
	TileImage* tile3C;		// 3C
	uint32_t				unk40;			// 40
	uint8_t				isStarted;      //44
	bool				isRest;         //45
	uint8_t				restKeyDebounce; //46
	uint8_t				pad47;           //47
	float				selectedHours;	// 48

	__forceinline static SleepWaitMenu *Get() {return *(SleepWaitMenu**)0x11DA920;}

};
static_assert(sizeof(SleepWaitMenu) == 0x4C);

// 1D4
class StartMenu : public Menu			// 1013
{
public:
	StartMenu();
	~StartMenu();

	// 10
	class Option {
	public:
		Option();
		~Option();

		virtual void	Destructor(bool doFree);

		const char* optionName;				// 04
		void			(*followupOption)(void);	// 08
		uint32_t			unk0C;						// 0C
	};

	// 30
	class UserOption : public Option {
	public:
		UserOption();
		~UserOption();

		const char* templateName;					// 10
		uint32_t			currValue;						// 14
		uint32_t			unk18[4];						// 18
		const char** currValueName;				// 28
		void			(*onSelection)(UserOption*);	// 2C
	};

	TileImage* tile028;		// 028
	TileImage* tile02C;		// 02C
	TileImage* tile030;		// 030
	TileImage* tile034;		// 034
	TileImage* tile038;		// 038
	TileImage* tile03C;		// 03C
	TileImage* tile040;		// 040
	TileImage* tile044;		// 044
	TileText* tile048;		// 048
	TileText* tile04C;		// 04C
	TileText* tile050;		// 050
	TileImage* tile054;		// 054
	TileText* tile058;		// 058
	Tile3D* tile05C;		// 05C
	TileImage* tile060;		// 060
	TileImage* tile064;		// 064
	TileText* tile068;		// 068
	TileImage* tile06C;		// 06C
	TileText* tile070;		// 070
	TileText* tile074;		// 074
	TileText* tile078;		// 078
	TileImage* tile07C;		// 07C
	TileText* tile080;		// 080
	ListBox<Option>					options084;		// 084
	ListBox<Option>					options0B4;		// 0B4
	ListBox<Option>					options0E4;		// 0E4
	ListBox<Option>					options114;		// 114
	ListBox<int>					listBox144;		// 144
	ListBox<BGSSaveLoadFileEntry>	listBox174;		// 174
	uint32_t							unk1A4;			// 1A4
	uint32_t							flags;			// 1A8
	uint32_t							unk1AC;			// 1AC
	uint32_t							unk1B0;			// 1B0
	Option* option1B4;		// 1B4
	NiSourceTexture* texture1B8;	// 1B8
	uint32_t							unk1BC;			// 1BC
	TileImage* tile1C0;		// 1C0
	TileImage* tile1C4;		// 1C4
	uint32_t							unk1C8;			// 1C8
	uint32_t							unk1CC;			// 1CC
	uint32_t							unk1D0;			// 1D0
};
static_assert(sizeof(StartMenu) == 0x1D4);

// E4
class LockPickMenu : public Menu		// 1014
{
public:
	LockPickMenu();
	~LockPickMenu();

	uint32_t					unk28;			// 28
	TileRect* tile2C;		// 2C
	TileRect* tile30;		// 30
	TileRect* tile34;		// 34
	TileImage* tile38;		// 38
	TileText* tile3C;		// 3C
	TileImage* tile40;		// 40
	TileImage* tile44;		// 44
	TileText* tile48;		// 48
	TileImage* tile4C;		// 4C
	TileImage* tile50;		// 50
	TileImage* tile54;		// 54
	TileText* tile58;		// 58
	TileText* tile5C;		// 5C
	TileImage* tile60;		// 60
	TileImage* tile64;		// 64
	TileImage* tile68;		// 68
	TESObjectREFR* targetRef;		// 6C
	uint32_t					lockLevel;		// 70
	uint32_t					skillLevel;		// 74
	float					fSkillLevel;	// 78
	uint32_t					unk7C;			// 7C
	uint32_t					unk80;			// 80
	float					flt84;			// 84
	uint32_t					sweetSpotLen;	// 88
	float					cylinderAngle;	// 8C
	float					pickAngle;		// 90
	float					pickHealth;		// 94
	uint8_t					byte98;			// 98
	uint8_t					byte99;			// 99
	uint8_t					pad9A[2];		// 99
	NiControllerSequence* ctrlSeq9C;		// 9C
	NiControllerSequence* ctrlSeqA0;		// A0
	NiControllerManager* ctrlManager;	// A4
	NiControllerSequence* ctrlSeqA8;		// A8
	NiControllerSequence* ctrlSeqAC;		// AC
	NiControllerSequence* ctrlSeqB0;		// B0
	NiQuaternion			quaternionB4;	// B4
	NiQuaternion			quaternionC4;	// C4
	NiQuaternion			quaternionD4;	// D4
};
static_assert(sizeof(LockPickMenu) == 0xE4);

// 44
class QuantityMenu : public Menu		// 1016
{
public:
	QuantityMenu();
	~QuantityMenu();

	virtual void		Unk_12(void);

	TileRect* tile28;		// 28
	TileImage* tile2C;		// 2C	QM_DecreaseArrow
	TileImage* tile30;		// 30	QM_IncreaseArrow
	TileText* tile34;		// 34
	TileImage* tile38;		// 38
	TileImage* tile3C;		// 3C
	float				currentQtt;		// 40
};


// 8C
class RepairMenu : public Menu			// 1035
{
public:
	RepairMenu();
	~RepairMenu();

	TileRect* tile28;		// 28
	TileImage* tile2C;		// 2C
	TileRect* tile30;		// 30
	TileImage* tile34;		// 34
	TileRect* tile38;		// 38
	TileRect* tile3C;		// 3C
	TileText* tile40;		// 40
	TileText* tile44;		// 44
	TileText* tile48;		// 48
	TileRect* tile4C;		// 4C
	TileRect* tile50;		// 50
	TileImage* tile54;		// 54
	TileImage* tile58;		// 58
	MenuItemEntryList		repairItems;	// 5C
};

// 5C
class TextEditMenu : public Menu		// 1051
{
public:
	TextEditMenu();
	~TextEditMenu();

	virtual void		Unk_12(void);

	TileText* currTextTile;			// 28
	TileImage* okButton;				// 2C
	TileText* messageTitle;			// 30
	BSString				currentText;			// 34
	BSString				displayedText;			// 3C	Copy of currentText + cursor
	uint32_t				cursorIndex;			// 44
	union {
		uint32_t			maxPixelLength;			// 48
		struct {
			uint16_t		minLength;				// 48
			uint16_t		maxLength;				// 4A
		};
	};
	union {
		uint32_t			fontID;					// 4C
		TileRect* inputRect;				// 4C
	};
	uint32_t				cursorBlink;			// 50	Value used for the cursor blink cycles (every 500ms)
	uint8_t				cursorVisible;			// 54
	uint8_t				isActive;				// 55
	uint8_t				byte56;					// 56
	uint8_t				miscFlags;				// 57
	union {
		bool			(*menuCallback)(char*);	// 58
		Script* scriptCallback;		// 58
	};
};
static_assert(sizeof(TextEditMenu) == 0x5C);

typedef tList<ContChangesEntry> BarterItemList;

// 120
class BarterMenu : public Menu			// 1053
{
public:
	BarterMenu();
	~BarterMenu();

	TileImage* tile028;		// 028
	TileImage* tile02C;		// 02C
	TileImage* tile030;		// 030
	TileText* tile034;		// 034
	TileImage* tile038;		// 038
	TileText* tile03C;		// 03C
	TileImage* tile040;		// 040
	TileImage* tile044;		// 044
	TileText* tile048;		// 048
	TileImage* tile04C;		// 04C
	TileText* tile050;		// 050
	TileImage* tile054;		// 054
	TileRect* tile058;		// 058
	TileImage* tile05C;		// 05C
	TileRect* tile060;		// 060
	TileRect* tile064;		// 064
	TileRect* tile068;		// 068
	TileRect* tile06C;		// 06C
	TileRect* tile070;		// 070
	TileImage* tile074;		// 074
	TileImage* tile078;		// 078
	TileRect* tile07C;		// 07C
	TESObjectREFR* merchantRef;	// 080
	float				barterTotalSum;	// 084
	uint32_t				unk088;			// 088
	uint32_t				playerGold;		// 08C
	uint32_t				merchantGold;	// 090
	float				buyValueMult;	// 094
	float				sellValueMult;	// 098
	uint32_t				leftFilter;		// 09C
	uint32_t				rightFilter;	// 0A0
	uint32_t				unk0A4;			// 0A4
	MenuItemEntryList	leftItems;		// 0A8
	MenuItemEntryList	rightItems;		// 0D8
	MenuItemEntryList* currentItems;	// 108
	BarterItemList		leftBarter;		// 10C
	BarterItemList		rightBarter;	// 114
	uint32_t				unk11C;			// 11C
};

// 1DC
class HackingMenu : public Menu			// 1055
{
public:
	HackingMenu();
	~HackingMenu();

	uint32_t				unk028[85];		// 028
	uint32_t				attemptsLeft;	// 17C
	uint32_t				unk180[6];		// 180
	TESObjectREFR* targetRef;		// 198
	uint32_t				unk19C[16];		// 19C
};
static_assert(sizeof(HackingMenu) == 0x1DC);

struct ActorHitData;
struct VATSTargetInfo {
	uint32_t actionType;
	uint8_t isSuccess;
	uint8_t byte05;
	uint8_t isMysteriousStrangerVisit;
	uint8_t byte07;
	uint8_t remainingShotsToFire_Burst;
	uint8_t count09;
	uint8_t gap0A[2];
	TESObjectREFR* ref;
	uint32_t avCode;
	ActorHitData* hitData;
	float unk18;
	float unk1C;
	float apCost;
	uint8_t isMissFortuneVisit;
	uint8_t gap25[3];
};
static_assert(sizeof(VATSTargetInfo) == 0x28);
// 144
class VATSMenu : public Menu			// 1056
{
public:
	VATSMenu();
	~VATSMenu();

	virtual void		Unk_12(void);

	uint32_t				unk028;			// 028
	TileImage* tile02C;		// 02C
	TileImage* tile030;		// 030
	TileImage* tile034;		// 034
	TileImage* tile038;		// 038
	TileImage* tile03C;		// 03C
	TileImage* tile040;		// 040
	TileImage* tile044;		// 044
	TileImage* tile048;		// 048
	TileImage* tile04C;		// 04C
	TileImage* tile050;		// 050
	TileText* tile054;		// 054
	TileText* tile058;		// 058
	TileText* tile05C;		// 05C
	TileText* tile060;		// 060
	TileImage* tile064;		// 064
	TileImage* tile068;		// 068
	TileImage* tile06C;		// 06C
	TileImage* tile070;		// 070
	TileText* tile074;		// 074
	TileRect* tile078;		// 078
	TileRect* tile07C;		// 07C
	TileRect* tile080;		// 080
	TileImage* tile084;		// 084
	TileRect* tile088;		// 088
	TileImage* tile08C;		// 08C
	TileImage* tile090;		// 090
	TileImage* tile094;		// 094
	TileImage* tile098;		// 098
	TileText* tile09C;		// 09C
	TileImage* tile0A0;		// 0A0
	TileImage* tile0A4;		// 0A4
	uint32_t				unk0A8[2];		// 0A8
	ListBox<uint32_t>		queuedActions;	// 0B0
	uint32_t				unk0E0[18];		// 0E0
	TESObjectREFR* targetRef;		// 128
	uint32_t				unk12C;			// 12C
	void* ptr130;		// 130
	float				unk134[3];		// 134
	uint8_t				unk140;			// 140
	uint8_t				pad141[3];		// 141
};

// FC
class ComputersMenu : public Menu		// 1057
{
public:
	ComputersMenu();
	~ComputersMenu();

	uint32_t				unk28[33];		// 28
	TESObjectREFR* targetRef;		// AC
	uint32_t				unkB0[19];		// B0
};

// A0
class RepairServicesMenu : public Menu	// 1058
{
public:
	RepairServicesMenu();
	~RepairServicesMenu();

	TileText* tile28;		// 28
	TileText* tile2C;		// 2C
	TileImage* tile30;		// 30
	TileImage* tile34;		// 34
	TileRect* tile38;		// 38
	TileRect* tile3C;		// 3C
	TileRect* tile40;		// 40
	TileText* tile44;		// 44
	TileText* tile48;		// 48
	TileText* tile4C;		// 4C
	TileRect* tile50;		// 50
	TileRect* tile54;		// 54
	TileText* tile58;		// 58
	TileImage* tile5C;		// 5C
	TileImage* tile60;		// 60
	TileImage* tile64;		// 64
	MenuItemEntryList	itemList;		// 68
	uint32_t				unk98;			// 98
	uint8_t				skill;			// 9C
	uint8_t				pad9D[3];		// 9D
};

// 90
class ItemModMenu : public Menu			// 1061
{
public:
	ItemModMenu();
	~ItemModMenu();

	TileRect* tile28;		// 28
	TileImage* tile2C;		// 2C
	TileRect* tile30;		// 30
	TileImage* tile34;		// 34
	TileRect* tile38;		// 38
	TileRect* tile3C;		// 3C
	TileText* tile40;		// 40
	TileText* tile44;		// 44
	TileText* tile48;		// 48
	TileRect* tile4C;		// 4C
	TileRect* tile50;		// 50
	TileImage* tile54;		// 54
	TileImage* tile58;		// 58
	TileText* tile5C;		// 5C
	MenuItemEntryList	itemModList;	// 60
};

// 88
class CompanionWheelMenu : public Menu	// 1075
{
public:
	CompanionWheelMenu();
	~CompanionWheelMenu();

	virtual void		Unk_12(void);

	uint32_t				unk28[16];		// 28
	Actor* companionRef;	// 68
	uint32_t				unk6C[7];		// 6C
};

// 88
class TraitSelectMenu : public Menu		// 1076
{
public:
	TraitSelectMenu();
	~TraitSelectMenu();

	uint32_t				unk28[24];		// 28
};

// 104
class RecipeMenu : public Menu			// 1077
{
public:
	RecipeMenu();
	~RecipeMenu();

	TileImage* tile028;		// 028	RM_Items_LeftFilterArrow
	TileText* tile02C;		// 02C	RM_ItemsTitle
	TileImage* tile030;		// 030	RM_Items_RightFilterArrow
	TileImage* tile034;		// 034	RM_Items_InventoryList
	TileText* tile038;		// 038	RM_MadeAtVariable
	TileText* tile03C;		// 03C	RM_SkillRequirement
	TileImage* tile040;		// 040	RM_Items_IngredientList
	TileImage* tile044;		// 044	RM_ButtonX
	TileImage* tile048;		// 048	RM_ButtonB
	TileImage* tile04C;		// 04C	RM_ItemIcon
	TileRect* tile050;		// 050	RM_ItemData
	TileText* tile054;		// 054	RM_Items_IngredientList
	TileText* tile058;		// 058	RM_ContainerTitle
	TileText* tile05C;		// 05C	RM_SkillRequirementHeader
	TESObjectREFR* sourceRef;		// 060
	TESRecipeCategory* category;		// 064
	uint32_t						unk068;			// 068
	ListBox<TESRecipe>			recipeList;		// 06C
	ListBox<TESRecipe>* unk09C;		// 09C
	ListBox<RecipeComponent>	componentList;	// 0A0
	ListBox<Condition>			conditionList;	// 0D0
	uint32_t						unk100;			// 100
};

// E88
class CaravanMenu : public Menu			// 1083
{
public:
	CaravanMenu();
	~CaravanMenu();

	uint32_t					unk028[54];		// 028
	TESObjectREFR* opponentRef;	// 100
	uint32_t					unk104[865];	// 104
};

// 8C
class TraitMenu : public Menu			// 1084
{
public:
	TraitMenu();
	~TraitMenu();

	virtual void		Unk_12(void);

	TileText* tile28;		// 28	LUM_Headline_Title
	TileImage* tile2C;		// 2C	LUM_PerkList
	TileImage* tile30;		// 30	LUM_SelectionIcon
	TileText* tile34;		// 34	TM_DescriptionText
	TileText* tile38;		// 38	LUM_PointCounter
	TileImage* tile3C;		// 3C	LUM_ResetButton
	TileImage* tile40;		// 40	LUM_ContinueButton
	TileImage* tile44;		// 44	stats_icon_badge
	TileImage* tile48;		// 48	TM_DescriptionScrollbar
	uint32_t				numSelected;	// 4C
	uint32_t				maxSelect;		// 50
	ListBox<BGSPerk>	perkListBox;	// 54
	tList<BGSPerk>		perkList;		// 84
};


// D8
class FORenderedMenu {
public:
	FORenderedMenu();
	~FORenderedMenu();

	virtual void    Destructor(bool doFree);
	virtual void    Unk_01(void);
	virtual void    Unk_02(void);
	virtual void    Unk_03(void);
	virtual void    Unk_04(void);
	virtual void    Unk_05(void);
	virtual void    Unk_06(void);
	virtual void    Unk_07(void);
	virtual void    Unk_08(void);
	virtual void    Unk_09(void);
	virtual void    Unk_0A(void);
	virtual void    Unk_0B(void);
	virtual void    Unk_0C(void);
	virtual void    Unk_0D(void);
	virtual void    Unk_0E(void);
	virtual void    Unk_0F(void);
	virtual void    Unk_10(void);
	virtual void    Unk_11(void);
	virtual void    Unk_12(void);
	virtual void    Unk_13(void);
	virtual void    Unk_14(void);

	NiAVObject* unk04;
	BSFadeNode* node08;
	uint32_t unk0C;
	NiSourceTexture* srcTexture;
	NiNode* node14;
	TileMenu* tileMenu;
	uint32_t unk1C[2];
	NiCamera* camera;
	uint8_t byte028;
	uint8_t gap028[3];
	uint32_t unk02C[5];
	uint32_t blurRadius;
	uint32_t blurIntensity;
	uint32_t unk048;
	uint8_t byte04C;
	uint8_t byte04D;
	uint8_t gap04E[2];
	float time050;
	float burstDuration;
	float burstIntensity2;
	float burstIntensity;
	uint32_t unk060[30];
};

// 70
class FORenderedTerminal : public FORenderedMenu {
public:
	FORenderedTerminal();
	~FORenderedTerminal();

	NiVector3 localTranslate;
	NiAVObject* powerButton;
	float fltE8;
	uint8_t bytEC;
};
//static_assert(sizeof(FORenderedTerminal) == 0x70); FIXME

class FOPipboyManager : public FORenderedMenu {
public:
	FOPipboyManager();
	~FOPipboyManager();

	NiNode* pipboyScreenNode0D8;
	NiNode* unk0DC;
	NiTriStrips* unk0C0;
	NiRefObject* unk0C4;
	NiTriStrips* pipboyLightButton[3];
	NiNode* pipboyLightGlow[3];
	NiTriStrips* scrollKnobs[3];
	float unk10C[3];
	float pipboyKnobScrollPositions[3];
	float pipboyKnobScrollRates[3];
	float tabKnobMinPosition;
	uint32_t unk134;
	uint32_t unk138;
	uint32_t unk13C;
	float tabKnobMaxPosition;
	uint8_t byte144;
	uint8_t gap145[3];
	uint32_t unk148;
	uint32_t unk14C;
	uint8_t byte150;
	uint8_t gap151[3];
	BSSoundHandle sound154;
	uint8_t byte160;
	uint8_t byte161;
	uint8_t byte162;
	uint8_t gap163;
	float time164;
	float lightEffectFadeDuration;
	uint32_t unk16C;
};
static_assert(sizeof(FOPipboyManager) == 0x170);