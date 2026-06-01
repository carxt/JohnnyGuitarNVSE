#pragma once

class TESObjectCELL;

class TESChildCell {
public:
	virtual TESObjectCELL* GetSaveParentCell() const;
};

ASSERT_SIZE(TESChildCell, 0x4);