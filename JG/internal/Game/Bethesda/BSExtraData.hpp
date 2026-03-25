#pragma once

#include "BSEnums.hpp"

class BSExtraData {
public:
	BSExtraData();
	virtual			~BSExtraData();
	virtual bool	Differs(const BSExtraData* apExtra) const;

	uint8_t			eType;
	BSExtraData*	pNext;

	EXTRA_DATA_TYPE GetExtraType() const;
	BSExtraData* GetNext() const;

	template <class T>
	inline bool IsType() const {
		return GetExtraType() == T::_TYPE;
	}
};

ASSERT_SIZE(BSExtraData, 0xC);