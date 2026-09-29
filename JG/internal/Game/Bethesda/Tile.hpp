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
	virtual bool				SpecialBoundsCheck(float afX, float afY) const;
	virtual uint32_t			PostParse(int32_t aiTrait, float afValue, char const* apString);
	virtual void				ForceTextureRelease();
	virtual TileShaderProperty*	GetShaderProperty() const;
	virtual void				SetAlphaAndColor(NiNode* apNode, float afAlpha, const NiColorA& arColor);

	class Value;

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

	class Value {
	public:
		TILE_TRAIT	eIndex;	
		Tile*		pParent;
		float		fValue;	
		char*		pTextValue;	
		Action*		pActions;

		void AddAction(TILE_VALUE_ACTION aeActionType, Tile* apSourceTile, int32_t aiSourceTrait);
		void AddAction(TILE_VALUE_ACTION aeActionType, float afValue);
		void ClearActions();

		void CalculateValue(bool abForceUpdate);
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

	struct ALIGN4 _Flags {
		enum Flags {
			CHANGE_POSITION			= 1u << 0,
			CHANGE_CREATE			= 1u << 1,
			CHANGE_VISIBILITY		= 1u << 2,
			CHANGE_COLOR			= 1u << 3,
			CHANGE_GEOMETRY			= 1u << 4,
			CHANGE_TEXTURE			= 1u << 5,
			CHANGE_NIF_FILE			= 1u << 6,
			CHANGE_SCISSOR_WINDOW	= 1u << 7,
			CHANGE_SCISSOR			= 1u << 8,
			CHANGE_LOCUS			= 1u << 9,
			CHANGE_MASK				= 0x3FF,

			DIRTY					= 1u << 10,
			HIBERNATED				= 1u << 11,
			PROMOTED				= 1u << 12,
			RELEASED				= 1u << 13,
			MENU_DELETING			= 1u << 14,
			MANUAL_UPDATE_TRIS		= 1u << 15,
			LOADING					= 1u << 16,
			BORROWED_MODEL			= 1u << 17,
		};

		bool bChangePosition			: 1;
		bool bChangeCreate				: 1;
		bool bChangeVisibility			: 1;
		bool bChangeColor				: 1;
		bool bChangeGeometry			: 1;
		bool bChangeTexture				: 1;
		bool bChangeNifFile				: 1;
		bool bChangeScissorWindow		: 1;
		bool bChangeScissor				: 1;
		bool bChangeLocus				: 1;
		bool bDirty						: 1;
		bool bHibernated				: 1;
		bool bPromoted					: 1;
		bool bReleased					: 1;
		bool bMenuDeleting				: 1;
		bool bManualUpdateTris			: 1;
		bool bLoading					: 1;
		bool bBorrowedModel				: 1;
	};
	using Flags = _Flags::Flags;

	NiTList<Tile*>				kChildren;
	BSSimpleArray<Value*, 8>	kTraits;
	BSString					strName;
	Tile*						pParent;
	NiNodePtr					spModel;
	Bitfield<_Flags>			uiFlags;
	bool						bNeedsNiUpdate;
	bool						bSpeechChallengeFailure;

	const char* GetName() const;
	void SetName(const char* apName);
	void SetName(const BSString& arName);

	Tile* GetParent() const;

	Tile* GetChildByID(uint32_t auiID) const;
	Tile* GetChildByName(const char* apName) const;

	NiNode* GetModel() const;
	NiNode* GetParentModel() const;

	void SetString(int32_t aiTrait, const char* apString, bool abClearActions = true);
	void SetFloat(int32_t aiTrait, float afValue, bool abClearActions = true);
	void SetUInt(int32_t aiTrait, uint32_t auiValue);
	void SetInt(int32_t aiTrait, int32_t aiValue);

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
ASSERT_SIZE(Tile::Action, 0xC);
ASSERT_SIZE(Tile::Value, 0x14);

struct AutoTileLock {
	AutoTileLock() { Tile::Lock(); };
	~AutoTileLock() { Tile::Unlock(); };
	AutoTileLock(const AutoTileLock&) = delete;
	AutoTileLock& operator=(const AutoTileLock&) = delete;
};