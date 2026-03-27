#pragma once

#include "BaseFormComponent.hpp"
#include "TESTextureListArray.hpp"
#include "BSSimpleList.hpp"

class TESModelList : public BaseFormComponent {
public:
	TESModelList();
	virtual ~TESModelList();

	BSSimpleList<const char*>	kModels;
	TESTextureListArray			kTextures;

	const TESTextureListArray* GetTextureListArray() const;
	TESTextureListArray* GetTextureListArray();

	void AddModel(const char* apPath);

	bool IsModelInList(const char* apPath) const;
};

ASSERT_SIZE(TESModelList, 0x14);