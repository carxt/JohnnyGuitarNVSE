#pragma once

#include "TESBoundObject.hpp"
#include "TESModelTextureSwap.hpp"
#ifdef EDITOR
#include "BSMap.hpp"

class NiProperty;
#endif

class BGSStaticCollection : public TESBoundObject, public TESModelTextureSwap {
public:
    BGSStaticCollection();
    ~BGSStaticCollection();

#ifdef EDITOR
	struct REF_COL_DATA {
		NiPoint3	kPoint30;
		DWORD		dwordC;
		DWORD		dword10;
		float		float14;
		float		float18;
	};

	BSMap<TESObjectSTAT*, BSSimpleList<REF_COL_DATA>*>* pObjects;
#endif

    TESFORM_TYPE(BGSStaticCollection);
};

#ifdef GAME
ASSERT_SIZE(BGSStaticCollection, 0x50);
#else
ASSERT_SIZE(BGSStaticCollection, 0x88);
#endif