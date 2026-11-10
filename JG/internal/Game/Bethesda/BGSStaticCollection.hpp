#pragma once

#include "TESBoundObject.hpp"
#include "TESModelTextureSwap.hpp"
#ifdef EDITOR
#include "BSMap.hpp"
#include "Gamebryo/NiPoint3.hpp"

class TESObjectSTAT;
#endif

class BGSStaticCollection : public TESBoundObject, public TESModelTextureSwap {
public:
    BGSStaticCollection();
    ~BGSStaticCollection();

#ifdef EDITOR
	struct REF_COL_DATA {
		REF_COL_DATA() = default;
		REF_COL_DATA(nullptr_t) {};
		REF_COL_DATA(const REF_COL_DATA& arOther) = default;

		NiPoint3	kPos = NiPoint3::ZERO;
		NiPoint3	kRot = NiPoint3::ZERO;
		float		fScale = -1.f;

		bool operator==(const REF_COL_DATA& arOther) const { return memcmp(this, &arOther, sizeof(*this)) == 0; }
	};
	static_assert(NiC::NiItemBase<REF_COL_DATA>);

	BSMap<TESObjectSTAT*, BSSimpleList<REF_COL_DATA>*>* pObjects;
#endif

    TESFORM_TYPE(BGSStaticCollection);
};

#ifdef GAME
ASSERT_SIZE(BGSStaticCollection, 0x50);
#else
ASSERT_SIZE(BGSStaticCollection, 0x88);
#endif