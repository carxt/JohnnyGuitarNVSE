#pragma once

#include "Bethesda/TESForm.hpp"
#include "Bethesda/TESCondition.hpp"
#include "Bethesda/TESFullName.hpp"
#include "Bethesda/ActorValue.hpp"
#include "TESRecipeCategory.hpp"
#include "TESRecipeComponent.hpp"

class TESRecipe : public TESForm, public TESFullName {
public:
	TESRecipe();
	~TESRecipe();

	struct Data {
		uint32_t	eReqSkill;
		int32_t		iReqSkillLevel;
		uint32_t	uiCategoryID;
		uint32_t	uiSubCategoryID;
	};

	Data								kData;
	TESCondition						kConditions;
	BSSimpleList<TESRecipeComponent*>	kIngredients;
	BSSimpleList<TESRecipeComponent*>	kOutputs;
	BSSimpleList<TESRecipeComponent*>	kGarbageCollection;
	TESRecipeCategory*					pCategory;
	TESRecipeCategory*					pSubCategory;

	TESFORM_TYPE(TESRecipe);

	ActorValue::Index GetRequiredSkill() const;
	void SetRequiredSkill(ActorValue::Index aeSkill);

	int32_t GetRequiredSkillLevel() const;
	void SetRequiredSkillLevel(int32_t aiLevel);

	TESRecipeCategory* GetCategory() const;
	void SetCategory(TESRecipeCategory* apCategory);

	TESRecipeCategory* GetSubCategory() const;
	void SetSubCategory(TESRecipeCategory* apSubCategory);

	TESCondition* GetConditions();
	const TESCondition* GetConditions() const;

	BSSimpleList<TESRecipeComponent*>* GetIngredientsList();
	const BSSimpleList<TESRecipeComponent*>* GetIngredientsList() const;

	BSSimpleList<TESRecipeComponent*>* GetOutputList();
	const BSSimpleList<TESRecipeComponent*>* GetOutputList() const;

	BSSimpleList<TESRecipeComponent*>* GetGarbageList();
	const BSSimpleList<TESRecipeComponent*>* GetGarbageList() const;
};

ASSERT_SIZE(TESRecipe, 0x5C);