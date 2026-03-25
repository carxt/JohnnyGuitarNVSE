#pragma once

#include "BSExtraData.hpp"

class BaseExtraList {
public:
	BaseExtraList();
	virtual ~BaseExtraList();

	BSExtraData*	pHead;
#if !JIP_CHANGES
	Bitfield8		ucPresenceBitfield[21];
#else
	Bitfield8		ucPresenceBitfield[19];
	Bitfield8		ucJIPRefFlags; // TESObjectREFR only
	union
	{
		class NPCPerksInfo* __restrict pPerksInfo;
		class TESAmmo*		__restrict pAmmo;		//	For Projectile refs
	};
#endif

	bool HasExtra(uint8_t aucType) const;

	template<class T>
	inline bool HasExtra() const noexcept {
		return HasExtra(T::_TYPE);
	}

	BSExtraData* GetExtraData(uint8_t aucType) const;

	template <class T>
	inline T* GetExtraData() const noexcept {
		return static_cast<T*>(GetExtraData(T::_TYPE));
	}

	void RemoveExtra(BSExtraData* apExtra, bool abDelete);

	void RemoveExtra(uint8_t aucType);

	BSExtraData* AddExtra(BSExtraData* apExtra);

	void RemoveAll(bool abDelete);

	void RemoveAllDefault(bool abDelete);
};


ASSERT_SIZE(BaseExtraList, 0x20);