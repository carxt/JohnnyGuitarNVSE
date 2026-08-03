#pragma once

#include "BSSimpleArray.hpp"
#include "BSSimpleList.hpp"
#include "BSStringT.hpp"
#include "BSEnums.hpp"
#include "Gamebryo/NiNode.hpp"
#include "Gamebryo/NiTList.hpp"

class TileShaderProperty;
class Menu;
class NiColorA;

class Tile {
public:
	Tile();

	virtual						~Tile();
	virtual void				Init(Tile* apParent, const char* apName, Tile* apReplacedTile);
	virtual NiNode*				MakeNode();
	virtual TILE_TYPE			GetType() const;
	virtual const char*			GetTypeName() const;
	virtual bool				SpecialBoundsCheck(float afX, float afY);
	virtual uint32_t			PostParse(int32_t aiTrait, float afValue, char const* apString);
	virtual void				ForceTextureRelease();
	virtual TileShaderProperty*	GetShaderProperty() const;
	virtual void				SetAlphaAndColor(NiNode* apNode, float afAlpha, const NiColorA& arColor);

	struct Value;

	class Action {
	public:
		virtual float	GetFloat() const;
		virtual Value*	GetRefValue() const;

		TILE_VALUE_ACTION	eActionType;
		Action*				pNext;
	};

	class RefValueAction : public Action {
	public:
		RefValueAction();
		~RefValueAction();

		Value* pTileValue;
	};

	class FloatAction : public Action {
	public:
		FloatAction();
		~FloatAction();

		float	fValue;
	};

	struct Value {
		TILE_TRAIT	eIndex;	
		Tile*		pParent;
		float		fValue;	
		char*		pTextValue;	
		Action*		pActions;
	};

	struct TileTemplate;

	struct BuildStorage {
		TileTemplate*				pTemplate;
		BSSimpleList<TileTemplate*>	kSubTemplates;
		TileTemplate*				pCurrentTemplate;
		bool						bDeleteTemplates;
	};

	struct TileTemplateItem {
		int32_t		iCmd;
		float		fVal;
		BSString	strTileName;
		union {
			int32_t			iTA;
			Tile*			pTile;
			TileTemplate*	pTemplate;
		};
	};

	struct TileTemplate {
		NiFixedString					kName;
		BuildStorage*					pParent;
		NiTList<TileTemplateItem*>		kItems;
	};

	enum Flags {
		CHANGE_POSITION			= 0x1,
		CHANGE_CREATE			= 0x2,
		CHANGE_VISIBILITY		= 0x4,
		CHANGE_COLOR			= 0x8,
		CHANGE_GEOMETRY			= 0x10,
		CHANGE_TEXTURE			= 0x20,
		CHANGE_NIF_FILE			= 0x40,
		CHANGE_SCISSOR_WINDOW	= 0x80,
		CHANGE_SCISSOR			= 0x100,
		CHANGE_LOCUS			= 0x200,
		CHANGE_MASK				= 0x3FF,

		DIRTY					= 0x400,
		HIBERNATED				= 0x800,
		PROMOTED				= 0x1000,
		RELEASED				= 0x2000,
		MENU_DELETING			= 0x4000,
		MANUAL_UPDATE_TRIS		= 0x8000,
		LOADING					= 0x10000,
		BORROWED_MODEL			= 0x20000,
	};

	NiTList<Tile*>				kChildren;
	BSSimpleArray<Value*, 8>	kTraits;
	BSString					strName;
	Tile*						pParent;
	NiNodePtr					spModel;
	Bitfield32					uiFlags;
	bool						bNeedsNiUpdate;
	bool						bSpeechChallengeFailure;

	const char* GetName() const;
	void SetName(const char* apName);
	void SetName(const BSString& arName);

	Tile* GetParent() const;

	NiNode* GetModel() const;
	NiNode* GetParentModel() const;

	void Set(int32_t aiTrait, const char* apString, bool abClearActions = true);
	void Set(int32_t aiTrait, float afValue, bool abClearActions = true);
	void Set(int32_t aiTrait, uint32_t auiValue);
	void Set(int32_t aiTrait, int32_t aiValue);

	Tile::Value* GetValue(int32_t aiTrait) const;

	const char* GetString(int32_t aiTrait) const;

	float GetFloat(int32_t aiTrait) const;

	Menu* GetMenu() const;

	Tile* ReadFile(const char* apFilePath);

	bool IsVisible() const;

	bool IsValueSet(int32_t aiTrait) const;

	void AddFadeControl(int32_t aiTrait, float afStart, float afEnd, float afLength, uint32_t aeType);

	static Menu* GetMenuByClass(uint32_t auiClass);

	static Tile* GetTileByName(Tile* apTile, const char* apName);

	static int32_t TextToTrait(const char* apTraitName);

	static int32_t AddUserTrait(const char* apTraitName, int32_t aiIndex);

	static float GetMaximumDepth();

	static void Lock();
	static void Unlock();
};

ASSERT_SIZE(Tile, 0x38);


class AutoTileLock {
public:
	AutoTileLock() { Tile::Lock(); };
	~AutoTileLock() { Tile::Unlock(); };
};