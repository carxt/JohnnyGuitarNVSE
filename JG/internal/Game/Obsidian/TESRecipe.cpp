#include "TESRecipe.hpp"

// GAME - 0x59BB30
ActorValue::Index TESRecipe::GetRequiredSkill() const {
    return static_cast<ActorValue::Index>(kData.eReqSkill);
}

// GAME - 0x7037C0
void TESRecipe::SetRequiredSkill(ActorValue::Index aeSkill) {
    kData.eReqSkill = aeSkill;
}

// GAME - 0x45CD60
int32_t TESRecipe::GetRequiredSkillLevel() const {
    return kData.iReqSkillLevel;
}

// GAME - 0x61CC40
void TESRecipe::SetRequiredSkillLevel(int32_t aiLevel) {
    kData.iReqSkillLevel = aiLevel;
}

// GAME - 0x6A1B60
TESRecipeCategory* TESRecipe::GetCategory() const {
    return pCategory;
}

// GAME - 0x5A8040
void TESRecipe::SetCategory(TESRecipeCategory* apCategory) {
    pCategory = apCategory;
}

// GAME - 0x6286D0
TESRecipeCategory* TESRecipe::GetSubCategory() const {
    return pSubCategory;
}

// GAME - 0x5A8060
void TESRecipe::SetSubCategory(TESRecipeCategory* apSubCategory) {
    pSubCategory = apSubCategory;
}

// GAME - 0x6A9540
TESCondition* TESRecipe::GetConditions() {
    return &kConditions;
}

// GAME - 0x6A9540
const TESCondition* TESRecipe::GetConditions() const {
    return &kConditions;
}

// GAME - 0x5A8080
BSSimpleList<TESRecipeComponent*>* TESRecipe::GetIngredientsList() {
    return &kIngredients;
}

// GAME - 0x5A8080
const BSSimpleList<TESRecipeComponent*>* TESRecipe::GetIngredientsList() const {
    return &kIngredients;
}

// GAME - 0x5D43C0
BSSimpleList<TESRecipeComponent*>* TESRecipe::GetOutputList() {
    return &kOutputs;
}

// GAME - 0x5D43C0
const BSSimpleList<TESRecipeComponent*>* TESRecipe::GetOutputList() const {
    return &kOutputs;
}

// GAME - 0x5D43E0
BSSimpleList<TESRecipeComponent*>* TESRecipe::GetGarbageList() {
    return &kGarbageCollection;
}

// GAME - 0x5D43E0
const BSSimpleList<TESRecipeComponent*>* TESRecipe::GetGarbageList() const {
    return &kGarbageCollection;
}
