#pragma once

#include "nvse/GameTypes.h"
#include "Gamebryo/NiTList.hpp"

typedef uint32_t(*_TraitNameToID)(const char* traitName);
extern const _TraitNameToID TraitNameToID;

const char* TraitIDToName(int id);	// slow

//	Tile
//		TileRect		3C
//			TileMenu	40
//		TileImage		48
//		TileText		4C
//		Tile3D			50

class NiNode;
class Menu;

enum {
	kTileValue_Copy = 0x7D0,
	kTileValue_Add = 0x7D1,
	kTileValue_Sub = 0x7D2,
	kTileValue_Mul = 0x7D3,
	kTileValue_Div = 0x7D4,
	kTileValue_Min = 0x7D5,
	kTileValue_Max = 0x7D6,
	kTileValue_Mod = 0x7D7,
	kTileValue_x = 0xFA1,
	kTileValue_y,
	kTileValue_visible,
	kTileValue_class,
	kTileValue_clipwindow = 0xFA6,
	kTileValue_stackingtype,
	kTileValue_locus,
	kTileValue_alpha,
	kTileValue_id,
	kTileValue_disablefade,
	kTileValue_listindex,
	kTileValue_depth,
	kTileValue_clips,
	kTileValue_target,
	kTileValue_height,
	kTileValue_width,
	kTileValue_red,
	kTileValue_green,
	kTileValue_blue,
	kTileValue_tile,
	kTileValue_childcount,
	kTileValue_child_count = kTileValue_childcount,
	kTileValue_justify,
	kTileValue_zoom,
	kTileValue_font,
	kTileValue_wrapwidth,
	kTileValue_wraplimit,
	kTileValue_wraplines,
	kTileValue_pagenum,
	kTileValue_ishtml,
	kTileValue_cropoffsety,
	kTileValue_cropy = kTileValue_cropoffsety,
	kTileValue_cropoffsetx,
	kTileValue_cropx = kTileValue_cropoffsetx,
	kTileValue_menufade,
	kTileValue_explorefade,
	kTileValue_mouseover,
	kTileValue_string,
	kTileValue_shiftclicked,
	kTileValue_clicked = 0xFC7,
	kTileValue_clicksound = 0xFCB,
	kTileValue_filename,
	kTileValue_filewidth,
	kTileValue_fileheight,
	kTileValue_repeatvertical,
	kTileValue_repeathorizontal,
	kTileValue_animation = 0xFD2,
	kTileValue_linecount = 0xDD4,
	kTileValue_pagecount,
	kTileValue_xdefault,
	kTileValue_xup,
	kTileValue_xdown,
	kTileValue_xleft,
	kTileValue_xright,
	kTileValue_xbuttona = 0xFDD,
	kTileValue_xbuttonb,
	kTileValue_xbuttonx,
	kTileValue_xbuttony,
	kTileValue_xbuttonlt,
	kTileValue_xbuttonrt,
	kTileValue_xbuttonlb,
	kTileValue_xbuttonrb,
	kTileValue_xbuttonstart = 0xFE7,
	kTileValue_mouseoversound,
	kTileValue_draggable,
	kTileValue_dragstartx,
	kTileValue_dragstarty,
	kTileValue_dragoffsetx,
	kTileValue_dragoffsety,
	kTileValue_dragdeltax,
	kTileValue_dragdeltay,
	kTileValue_dragx,
	kTileValue_dragy,
	kTileValue_wheelable,
	kTileValue_wheelmoved,
	kTileValue_systemcolor,
	kTileValue_brightness,
	kTileValue_linegap = 0xFF7,
	kTileValue_resolutionconverter,
	kTileValue_texatlas,
	kTileValue_rotateangle,
	kTileValue_rotateaxisx,
	kTileValue_rotateaxisy,

	kTileValue_user0 = 0x1004,
	kTileValue_user1,
	kTileValue_user2,
	kTileValue_user3,
	kTileValue_user4,
	kTileValue_user5,
	kTileValue_user6,
	kTileValue_user7,
	kTileValue_user8,
	kTileValue_user9,
	kTileValue_user10,
	kTileValue_user11,
	kTileValue_user12,
	kTileValue_user13,
	kTileValue_user14,
	kTileValue_user15,
	kTileValue_user16,

	kTileValue_max
};

// 38+
class Tile {
public:
	Tile();

	enum eTileID {
		kTileID_rect = 0x0385,
		kTileID_image,
		kTileID_text,
		kTileID_3D,
		kTileID_nif = kTileID_3D,
		kTileID_menu,

		// Not a Tile descendend
		kTileID_hotrect,
		kTileID_window,
		// This one descend from TileImage
		kTileID_radial,

		kTileID_max
	};

	MEMBER_FN_PREFIX(Tile);
#if 1
	DEFINE_MEMBER_FN(SetStringValue, void, 0x00A01350, uint32_t valueID, const char* str, bool bPropagate);
	DEFINE_MEMBER_FN(SetFloatValue, void, 0x00A012D0, uint32_t valueID, float num, bool bPropagate);
#elif EDITOR
#else
#error
#endif

	virtual ~Tile();
	virtual void		Init(Tile* parent, const char* name, Tile* replacedChild);
	virtual NiNode* CalcNode(void);
	virtual uint32_t		GetType(void);		// returns one of kTileValue_XXX
	virtual const char* GetTypeStr(void);	// 4-byte id
	virtual bool		Unk_05(uint32_t arg0, uint32_t arg1);
	virtual uint32_t		UpdateField(uint32_t valueID, float floatValue, const char* strValue);
	virtual void		Unk_07(void);
	virtual uint32_t		Unk_08(void);
	virtual void		Unk_09(uint32_t arg0, uint32_t arg1, uint32_t arg2);

	struct Value;

	enum ActionType {
		kAction_copy = 0x7D0,
		kAction_add,
		kAction_sub,
		kAction_mul,
		kAction_div,
		kAction_min,
		kAction_max,
		kAction_mod,
		kAction_floor,
		kAction_ceil,
		kAction_abs,
		kAction_round,
		kAction_gt,
		kAction_gte,
		kAction_eq,
		kAction_neq,
		kAction_lt,
		kAction_lte,
		kAction_and,
		kAction_or,
		kAction_not,
		kAction_onlyif,
		kAction_onlyifnot,
		kAction_ref,
		kAction_begin,
		kAction_end,
	};

	// 0C
	class Action {
	public:
		Action();
		~Action();

		virtual float	GetFloat();
		virtual Value* GetValue();

		uint32_t		type;		// 04
		Action* next;		// 08
	};

	// 10
	class RefValueAction : public Action {
	public:
		RefValueAction();
		~RefValueAction();

		Value* tileVal;	// 0C
	};

	// 10
	class FloatAction : public Action {
	public:
		FloatAction();
		~FloatAction();

		float		value;		// 0C
	};

	// 14
	struct Value {
		uint32_t		id;			// 00
		Tile* parent;	// 04
		float		num;		// 08
		char* str;		// 0C
		Action* action;	// 10

		void SetFloat(float fltVal, bool bPropagate = true);
		void SetString(const char* strVal, bool bPropagate = true);
	};

	NiTList<Tile*>				children;		// 04
	BSSimpleArray<Value*>		values;			// 10
	BSString						name;			// 20
	Tile* parent;		// 28
	NiNode* node;			// 2C
	uint32_t						flags;			// 30
	uint8_t						unk34;			// 34
	uint8_t						unk35;			// 35
	uint8_t						pad35[2];		// 36

	static uint32_t	TraitNameToID(const char* traitName);
	static uint32_t	TraitNameToIDAdd(const char* traitName);
	Value* GetValue(uint32_t typeID);
	Value* GetValueName(const char* valueName);
	float			GetFloat(uint32_t id);
	Tile* GetChild(const char* childName);
	Tile* GetComponent(const char* componentTile, const char*& trait);
	Tile* GetComponentTile(const char* componentTile);
	Value* GetComponentValue(const char* componentPath);
	Tile* ReadXML(const char* xmlPath);
	char* GetComponentFullName(char* resStr);
	void			SetFloat(uint32_t id, float fltVal, bool bPropagate = true) { ThisCall(0xA012D0, this, id, fltVal, bPropagate); }
	void			SetString(uint32_t id, const char* strVal, bool bPropagate = true) { ThisCall(0xA01350, this, id, strVal, bPropagate); }
	Menu* GetParentMenu();
	void			DeleteChildren();
	void			PokeValue(uint32_t valueID);
	void			FakeClick();

	void			Dump();

	static void Lock() {
		CdeclCall(0xA044F0);
	}

	static void Unlock() {
		CdeclCall(0xA04500);
	}
};

class AutoTileLock {
public:
	AutoTileLock() { Tile::Lock(); };
	~AutoTileLock() { Tile::Unlock(); };
};

// 3C
class TileRect : public Tile {
public:
	uint32_t	unk38;	// 38
};

// 40
class TileMenu : public TileRect {
public:
	Menu* menu;	// 3C
};

class TileShaderProperty;

// 48
class TileImage : public Tile {
public:
	float				flt038;			// 38
	uint32_t				unk03C;			// 3C
	TileShaderProperty* shaderProp;	// 40
	uint8_t				byt044;			// 44
	uint8_t				fill[3];		// 45-47
};

class TileText : public Tile {
public:
};

void Debug_DumpTraits(void);
