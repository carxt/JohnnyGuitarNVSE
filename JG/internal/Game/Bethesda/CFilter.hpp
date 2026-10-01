#pragma once

#ifdef TRANSPARENT
#undef TRANSPARENT
#endif

struct ColLayer {
	enum Layer {
		NONE					= 0,
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
		COUNT					= 43,
	};
};
using COL_LAYER = ColLayer::Layer;

struct _ColLayerBit {
	enum Bit : uint64_t {
		STATIC					= 1ull << COL_LAYER::STATIC,
		ANIM_STATIC				= 1ull << COL_LAYER::ANIM_STATIC,
		TRANSPARENT				= 1ull << COL_LAYER::TRANSPARENT,
		CLUTTER					= 1ull << COL_LAYER::CLUTTER,
		WEAPON					= 1ull << COL_LAYER::WEAPON,
		PROJECTILE				= 1ull << COL_LAYER::PROJECTILE,
		SPELL					= 1ull << COL_LAYER::SPELL,
		BIPED					= 1ull << COL_LAYER::BIPED,
		TREES					= 1ull << COL_LAYER::TREES,
		PROPS					= 1ull << COL_LAYER::PROPS,
		WATER					= 1ull << COL_LAYER::WATER,
		TRIGGER					= 1ull << COL_LAYER::TRIGGER,
		TERRAIN					= 1ull << COL_LAYER::TERRAIN,
		TRAP					= 1ull << COL_LAYER::TRAP,
		NONCOLLIDABLE			= 1ull << COL_LAYER::NONCOLLIDABLE,
		CLOUD_TRAP				= 1ull << COL_LAYER::CLOUD_TRAP,
		GROUND					= 1ull << COL_LAYER::GROUND,
		PORTAL					= 1ull << COL_LAYER::PORTAL,
		DEBRIS_SMALL			= 1ull << COL_LAYER::DEBRIS_SMALL,
		DEBRIS_LARGE			= 1ull << COL_LAYER::DEBRIS_LARGE,
		ACOUSTIC_SPACE			= 1ull << COL_LAYER::ACOUSTIC_SPACE,
		ACTOR_ZONE				= 1ull << COL_LAYER::ACTOR_ZONE,
		PROJECTILE_ZONE			= 1ull << COL_LAYER::PROJECTILE_ZONE,
		GAS_TRAP				= 1ull << COL_LAYER::GAS_TRAP,
		SHELL_CASING			= 1ull << COL_LAYER::SHELL_CASING,
		TRANSPARENT_SMALL		= 1ull << COL_LAYER::TRANSPARENT_SMALL,
		INVISIBLE_WALL			= 1ull << COL_LAYER::INVISIBLE_WALL,
		TRANSPARENT_SMALL_ANIM	= 1ull << COL_LAYER::TRANSPARENT_SMALL_ANIM,
		DEAD_BIP				= 1ull << COL_LAYER::DEAD_BIP,
		CHAR_CONTROLLER			= 1ull << COL_LAYER::CHAR_CONTROLLER,
		AVOID_BOX				= 1ull << COL_LAYER::AVOID_BOX,
		COLLISION_BOX			= 1ull << COL_LAYER::COLLISION_BOX,
		CAMERA_SPHERE			= 1ull << COL_LAYER::CAMERA_SPHERE,
		DOOR_DETECTION			= 1ull << COL_LAYER::DOOR_DETECTION,
		CAMERA_PICK				= 1ull << COL_LAYER::CAMERA_PICK,
		ITEM_PICK				= 1ull << COL_LAYER::ITEM_PICK,
		LINE_OF_SIGHT			= 1ull << COL_LAYER::LINE_OF_SIGHT,
		PATH_PICK				= 1ull << COL_LAYER::PATH_PICK,
		CUSTOM_PICK1			= 1ull << COL_LAYER::CUSTOM_PICK1,
		CUSTOM_PICK2			= 1ull << COL_LAYER::CUSTOM_PICK2,
		SPELL_EXPLOSION			= 1ull << COL_LAYER::SPELL_EXPLOSION,
		DROPPING_PICK			= 1ull << COL_LAYER::DROPPING_PICK,
	};
};
using COL_LAYER_BIT = _ColLayerBit::Bit;

struct _ColBipedPart {
	enum Part {
		OTHER			= 0,
		HEAD			= 1,
		BODY			= 2,
		SPINE1			= 3,
		SPINE2			= 4,
		LEFT_UPPERARM	= 5,
		LEFT_FOREARM	= 6,
		LEFT_HAND		= 7,
		LEFT_THIGH		= 8,
		LEFT_CALF		= 9,
		LEFT_FOOT		= 10,
		RIGHT_UPPERARM	= 11,
		RIGHT_FOREARM	= 12,
		RIGHT_HAND		= 13,
		RIGHT_THIGH		= 14,
		RIGHT_CALF		= 15,
		RIGHT_FOOT		= 16,
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
	};
};
using COL_BIPED_PART = _ColBipedPart::Part;

class CFilter {
public:
	struct ALIGN4 _Flags {
		enum Flags : uint32_t {
			LAYER_MASK		= 0x7F,
			PART_MASK		= 0x1F00,
			GROUP_MASK		= 0xFFFF0000,

			MOPP_SCALED		= 1u << 13,
			DISABLED		= 1u << 14,
			LINKED_GROUP	= 1u << 15,
		};

		uint16_t eLayer			: 7;
		uint16_t				: 1;
		uint16_t ePart			: 5;
		uint16_t bMoppScaled	: 1;
		uint16_t bDisabled		: 1;
		uint16_t bLinkedGroup	: 1;
		uint16_t usGroup		: 16;
	};
	using Flags = _Flags::Flags;

	CFilter() = default;
	CFilter(uint32_t auiFilter);
	CFilter(COL_LAYER aeLayer, uint32_t auiGroup, COL_BIPED_PART aePart);
	~CFilter() = default;

	Bitfield<_Flags> uiFilter;

	void Init(COL_LAYER aeLayer, uint32_t auiGroup, COL_BIPED_PART aePart);

	COL_LAYER GetLayer() const;
	void SetLayer(COL_LAYER aeLayer);

	uint32_t GetGroup() const;
	void SetGroup(uint32_t auiGroup);

	COL_BIPED_PART GetPart() const;
	void SetPart(COL_BIPED_PART aePart);

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