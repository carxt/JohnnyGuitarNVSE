#pragma once

#include "GameTiles.h"
#include "GameTypes.h"

class Menu;
class SceneGraph;
class FOPipboyManager;
class NiObject;
class TESObjectREFR;
class NiNode;
class BSShaderAccumulator;
class ShadowSceneNode;
class NiSourceTexture;

typedef Menu* (*_TempMenuByType)(UInt32 menuType);
extern const _TempMenuByType TempMenuByType;


// 584
class InterfaceManager
{
public:
	InterfaceManager();
	~InterfaceManager();

	static InterfaceManager *	GetSingleton(void);
	static bool					IsMenuVisible(UInt32 menuType);
	static Menu *				GetMenuByType(UInt32 menuType);
	static Menu *				TempMenuByType(UInt32 menuType);
	//static TileMenu *			GetMenuByPath(const char * componentPath, const char ** slashPos);
	//static Tile::Value *		GetMenuComponentValue(const char * componentPath);
	//static Tile *				GetMenuComponentTile(const char * componentPath);

	UInt32 GetTopVisibleMenuID();
	Tile *GetActiveTile();

	UInt32					flags;				// 000
	SceneGraph				*sceneGraph004;		// 004
	SceneGraph				*sceneGraph008;		// 008
	UInt32					currentMode;		// 00C	1 = GameMode; 2 = MenuMode
	UInt32					unk010;				// 010
	UInt32					unk014;				// 014
	UInt32					pickLength;			// 018
	UInt32					unk01C;				// 01C
	UInt8					byte020;			// 020
	UInt8					byte021;			// 021
	UInt8					byte022;			// 022
	UInt8					byte023;			// 023
	UInt32					unk024;				// 024
	TileImage				*cursor;			// 028
	float					flt02C;				// 02C
	float					flt030;				// 030
	float					flt034;				// 034
	float					cursorX;			// 038
	float					flt03C;				// 03C
	float					cursorY;			// 040
	float					mouseWheel;			// 044	-120.0 = down; 120.0 = up
	float					flt048;				// 048
	Tile					*draggedTile;		// 04C
	int						unk050;				// 050
	float					flt054;				// 054
	float					flt058;				// 058
	int						unk05C;				// 05C
	int						unk060;				// 060
	int						unk064;				// 064
	UInt32					unk068[2];			// 068
	tList<TESObjectREFR>	selectableRefs;		// 070
	UInt32					unk078;				// 078
	bool					debugText;			// 07C
	UInt8					byte07D;			// 07D
	UInt8					byte07E;			// 07E
	UInt8					byte07F;			// 07F
	NiNode					*niNode080;			// 080
	NiNode					*niNode084;			// 084
	UInt32					unk088;				// 088
	BSShaderAccumulator		*shaderAccum08C;	// 08C
	BSShaderAccumulator		*shaderAccum090;	// 090
	ShadowSceneNode			*shadowScene094;	// 094
	ShadowSceneNode			*shadowScene098;	// 098
	Tile					*menuRoot;			// 09C
	Tile					*globalsTile;		// 0A0	globals.xml
	NiNode					*unk0A4;			// 0A4 saw Tile? seen NiNode
	UInt32					unk0A8;				// 0A8
	NiObject				*unk0AC;			// 0AC seen NiAlphaProperty
	UInt32					unk0B0[3];			// 0B0
	Tile					*activeTileAlt;		// 0BC
	UInt32					unk0C0;				// 0C0
	UInt32					unk0C4;				// 0C4
	UInt8					byte0C8;			// 0C8
	UInt8					byte0C9;			// 0C9
	UInt8					byte0CA;			// 0CA
	UInt8					byte0CB;			// 0CB
	Tile					*activeTile;		// 0CC
	Menu					*activeMenu;		// 0D0
	Tile					*tile0D4;			// 0D4
	Menu					*menu0D8;			// 0D8
	UInt32					unk0DC[2];			// 0DC
	UInt8					msgBoxButton;		// 0E4 -1 if no button pressed
	UInt8					byte0E5;			// 0E5
	UInt8					byte0E6;			// 0E6
	UInt8					byte0E7;			// 0E7
	UInt32					unk0E8;				// 0E8
	UInt8					byte0EC;			// 0EC
	UInt8					byte0ED;			// 0ED
	UInt8					byte0EE;			// 0EE
	UInt8					byte0EF;			// 0EF
	TESObjectREFR			*debugSelection;	// 0F0	compared to activated object during Activate
	UInt32					unk0F4;				// 0F4
	UInt32					unk0F8;				// 0F8
	TESObjectREFR			*crosshairRef;		// 0FC
	UInt32					unk100[4];			// 100
	UInt8					byte110;			// 110
	UInt8					pad111[3];			// 111
	UInt32					menuStack[10];		// 114
	void					*ptr13C;			// 13C	Points to a struct, possibly. First member is *bhkSimpleShapePhantom
	UInt32					unk140[5];			// 140
	UInt32					unk154;				// 154
	UInt32					unk158;				// 158
	UInt32					unk15C[5];			// 15C
	UInt8					byte170;			// 170
	UInt8					byte171;			// 171
	UInt8					byte172;			// 172
	UInt8					byte173;			// 173
	FOPipboyManager			*pipboyManager;		// 174
	UInt32					*unk178;				// 178
	NiTArray<UInt32>		array17C;			// 17C NiTPrimitiveArray@PackedMenu@BGSMenuPacker
	UInt32					unk18C[130];		// 18C
	NiObject				*unk394;			// 394 seen NiSourceTexture
	UInt32					unk398[47];			// 398
	NiTArray<UInt32>		array454;			// 454 NiTPrimitiveArray@TextureType@BSTextureManager
	NiTArray<UInt32>		array464;			// 464 NiTPrimitiveArray@FilterMode@NiTexturingProperty
	UInt32					unk474[16];			// 474
	UInt8					byte4B4;			// 4B4
	UInt8					byte4B5;			// 4B5
	UInt8					byte4B6;			// 4B6
	UInt8					byte4B7;			// 4B7
	UInt32					unk4B8;				// 4B8
	UInt32					pipBoyMode;			// 4BC
	UInt32					unk4C0[48];			// 4C0
};
STATIC_ASSERT(sizeof(InterfaceManager) == 0x580);

void Debug_DumpMenus(void);

enum
{
	kMenuType_Min =				0x3E9,
	kMenuType_Message =			kMenuType_Min,
	kMenuType_Inventory,
	kMenuType_Stats,
	kMenuType_HUDMain,
	kMenuType_Loading =			0x3EF,
	kMenuType_Container,
	kMenuType_Dialog,
	kMenuType_SleepWait =		0x3F4,
	kMenuType_Start,
	kMenuType_LockPick,
	kMenuType_Quantity =		0x3F8,
	kMenuType_Map =				0x3FF,
	kMenuType_Book =			0x402,
	kMenuType_LevelUp,
	kMenuType_Repair =			0x40B,
	kMenuType_RaceSex,
	kMenuType_Credits =			0x417,
	kMenuType_CharGen,
	kMenuType_TextEdit =		0x41B,
	kMenuType_Barter =			0x41D,
	kMenuType_Surgery,
	kMenuType_Hacking,
	kMenuType_VATS,
	kMenuType_Computers,
	kMenuType_RepairServices,
	kMenuType_Tutorial,
	kMenuType_SpecialBook,
	kMenuType_ItemMod,
	kMenuType_LoveTester =		0x432,
	kMenuType_CompanionWheel,
	kMenuType_TraitSelect,
	kMenuType_Recipe,
	kMenuType_SlotMachine =		0x438,
	kMenuType_Blackjack,
	kMenuType_Roulette,
	kMenuType_Caravan,
	kMenuType_Trait =			0x43C,
	kMenuType_Max =				kMenuType_Trait,
};

struct EventCallbackScripts;

class Menu
{
public:
	Menu();
	~Menu();

	virtual Menu	*Destructor(bool doFree);
	virtual void	SetField(UInt32 idx, Tile *value);
	virtual void	Unk_02(UInt32 arg0, UInt32 arg1);
	virtual void	HandleClick(SInt32 tileID, Tile *clickedTile);
	virtual void	HandleMouseover(UInt32 arg0, Tile *activeTile);	//	Called on mouseover, activeTile is moused-over Tile
	virtual void	Unk_05(UInt32 arg0, UInt32 arg1);
	virtual void	Unk_06(UInt32 arg0, UInt32 arg1, UInt32 arg2);
	virtual void	Unk_07(UInt32 arg0, UInt32 arg1, UInt32 arg2);
	virtual void	Unk_08(UInt32 arg0, UInt32 arg1);
	virtual void	Unk_09(UInt32 arg0, UInt32 arg1);
	virtual void	Unk_0A(UInt32 arg0, UInt32 arg1);
	virtual void	Unk_0B(void);	// Called every frame while the menu is active
	virtual bool	HandleKeyboardInput(UInt32 inputChar);	// Return false for handling keyboard shortcuts
	virtual UInt32	GetID(void);
	virtual bool	Unk_0E(UInt32 arg0, UInt32 arg1);
	virtual void	Unk_0F(void);
	virtual void	Unk_10(void);
	virtual void	Unk_11(void);

	TileMenu		*tile;		// 04
	UInt32			unk08;		// 08
	UInt32			unk0C;		// 0C
	UInt32			unk10;		// 10
	UInt32			unk14;		// 14
	UInt32			unk18;		// 18
	UInt32			unk1C;		// 1C
	UInt32			id;			// 20
	UInt32			unk24;		// 24

	Menu *HandleMenuInput(int tileID, Tile *clickedTile);
	Tile *AddTileFromTemplate(Tile *destTile, const char *templateName, UInt32 arg3);
};

// 170
class RaceSexMenu : public Menu		// 1036
{
public:
	RaceSexMenu();
	~RaceSexMenu();

	UInt32				unk028[44];		// 028
	TESNPC				*npc;			// 0D8
	UInt32				unk0DC[37];		// 0DC

	void UpdatePlayerHead(void);
};