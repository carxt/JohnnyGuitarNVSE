#pragma once

#ifdef TRANSPARENT
#undef TRANSPARENT
#endif

struct ColLayer {
	enum Layer {
		STATIC					= 1,
		ANIM_STATIC				= 2,
		TRANSPARENT				= 3,
		CLUTTER					= 4,
		WEAPON					= 5,
		PROJECTILE				= 6,
		SPELL					= 7,
		BIPED					= 8,
		TREES					= 9,
		PROPS					= 10,
		WATER					= 11,
		TRIGGER					= 12,
		TERRAIN					= 13,
		TRAP					= 14,
		NONCOLLIDABLE			= 15,
		CLOUD_TRAP				= 16,
		GROUND					= 17,
		PORTAL					= 18,
		DEBRIS_SMALL			= 19,
		DEBRIS_LARGE			= 20,
		ACOUSTIC_SPACE			= 21,
		ACTOR_ZONE				= 22,
		PROJECTILE_ZONE			= 23,
		GAS_TRAP				= 24,
		SHELL_CASING			= 25,
		TRANSPARENT_SMALL		= 26,
		INVISIBLE_WALL			= 27,
		TRANSPARENT_SMALL_ANIM	= 28,
		DEAD_BIP				= 29,
		CHAR_CONTROLLER			= 30,
		AVOID_BOX				= 31,
		COLLISION_BOX			= 32,
		CAMERA_SPHERE			= 33,
		DOOR_DETECTION			= 34,
		CAMERA_PICK				= 35,
		ITEM_PICK				= 36,
		LINE_OF_SIGHT			= 37,
		PATH_PICK				= 38,
		CUSTOM_PICK1			= 39,
		CUSTOM_PICK2			= 40,
		SPELL_EXPLOSION			= 41,
		DROPPING_PICK			= 42,
		MAX						= 43,
	};
};
using COL_LAYER = ColLayer::Layer;

enum COL_LAYER_BIT : uint64_t {
	LAYER_B_STATIC					= 1ull << 1,
	LAYER_B_ANIM_STATIC				= 1ull << 2,
	LAYER_B_TRANSPARENT				= 1ull << 3,
	LAYER_B_CLUTTER					= 1ull << 4,
	LAYER_B_WEAPON					= 1ull << 5,
	LAYER_B_PROJECTILE				= 1ull << 6,
	LAYER_B_SPELL					= 1ull << 7,
	LAYER_B_BIPED					= 1ull << 8,
	LAYER_B_TREES					= 1ull << 9,
	LAYER_B_PROPS					= 1ull << 10,
	LAYER_B_WATER					= 1ull << 11,
	LAYER_B_TRIGGER					= 1ull << 12,
	LAYER_B_TERRAIN					= 1ull << 13,
	LAYER_B_TRAP					= 1ull << 14,
	LAYER_B_NONCOLLIDABLE			= 1ull << 15,
	LAYER_B_CLOUD_TRAP				= 1ull << 16,
	LAYER_B_GROUND					= 1ull << 17,
	LAYER_B_PORTAL					= 1ull << 18,
	LAYER_B_DEBRIS_SMALL			= 1ull << 19,
	LAYER_B_DEBRIS_LARGE			= 1ull << 20,
	LAYER_B_ACOUSTIC_SPACE			= 1ull << 21,
	LAYER_B_ACTORZONE				= 1ull << 22,
	LAYER_B_PROJECTILEZONE			= 1ull << 23,
	LAYER_B_GASTRAP					= 1ull << 24,
	LAYER_B_SHELLCASING				= 1ull << 25,
	LAYER_B_TRANSPARENT_SMALL		= 1ull << 26,
	LAYER_B_INVISIBLE_WALL			= 1ull << 27,
	LAYER_B_TRANSPARENT_SMALL_ANIM	= 1ull << 28,
	LAYER_B_DEADBIP					= 1ull << 29,
	LAYER_B_CHARCONTROLLER			= 1ull << 30,
	LAYER_B_AVOIDBOX				= 1ull << 31,
	LAYER_B_COLLISIONBOX			= 1ull << 32,
	LAYER_B_CAMERASPHERE			= 1ull << 33,
	LAYER_B_DOORDETECTION			= 1ull << 34,
	LAYER_B_CAMERAPICK				= 1ull << 35,
	LAYER_B_ITEMPICK				= 1ull << 36,
	LAYER_B_LINEOFSIGHT				= 1ull << 37,
	LAYER_B_PATHPICK				= 1ull << 38,
	LAYER_B_CUSTOMPICK1				= 1ull << 39,
	LAYER_B_CUSTOMPICK2				= 1ull << 40,
	LAYER_B_SPELLEXPLOSION			= 1ull << 41,
	LAYER_B_DROPPINGPICK			= 1ull << 42,
};

struct _BipedPart {
	enum Part {
		OTHER			= 0,
		HEAD			= 1,
		BODY			= 2,
		SPINE1			= 3,
		SPINE2			= 4,
		LUPPERARM		= 5,
		LFOREARM		= 6,
		LHAND			= 7,
		LTHIGH			= 8,
		LCALF			= 9,
		LFOOT			= 10,
		RUPPERARM		= 11,
		RFOREARM		= 12,
		RHAND			= 13,
		RTHIGH			= 14,
		RCALF			= 15,
		RFOOT			= 16,
		TAIL			= 17,
		SHIELD			= 18,
		QUIVER			= 19,
		WEAPON			= 20,
		PONYTAIL		= 21,
		WING			= 22,
		PACK			= 23,
		CHAIN			= 24,
		ADDON_HEAD		= 25,
		ADDON_CHEST		= 26,
		ADDON_LEG		= 27,
		ADDON_ARM		= 28,
		NUMFILTERPARTS	= 32,
	};
};
using BIPED_PART = _BipedPart::Part;

enum COL_GROUP : uint32_t {
	GROUP_LANDSCAPE = 1,
	GROUP_PATH_PICK = 3,
	GROUP_TREES		= 4,
};

class CFilter {
public:
	enum : uint32_t {
		LAYER_MASK		= 0x7F,
		PART_MASK		= 0x1F00,
		GROUP_MASK		= 0xFFFF0000,
		MOPP_SCALED		= 0x2000,
		DISABLED		= 0x4000,
		LINKED_GROUP	= 0x8000,
	};

	CFilter() = default;
	CFilter(uint32_t auiFilter);
	CFilter(COL_LAYER aeLayer, uint32_t auiGroup, BIPED_PART aePart);
	~CFilter() = default;

	uint32_t uiFilter;

	void Init(COL_LAYER aeLayer, uint32_t auiGroup, BIPED_PART aePart);

	COL_LAYER GetLayer() const;
	void SetLayer(COL_LAYER auiLayer);

	uint32_t GetGroup() const;
	void SetGroup(uint32_t auiGroup);

	BIPED_PART GetPart() const;
	void SetPart(BIPED_PART aePart);

	uint32_t GetBipedPart() const;

	bool IsMoppScaled() const;
	void SetMopScaled(bool abScaled);

	bool IsDisabled() const;
	void SetDisabled(bool abDisabled);

	bool IsLinkedGroup() const;
	void SetLinkedGroup(bool abLinked);

	bool IsBipLayer() const;

	bool IsLinked(CFilter aInfo) const;

	bool IsDifferentGroup(CFilter aInfo) const;
};

ASSERT_SIZE(CFilter, 0x4);