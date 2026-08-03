#include "Tile.hpp"

// GAME - 0x700300
const char* Tile::GetName() const {
	return strName.GetString();
}

// GAME - 0x707E10
void Tile::SetName(const char* apName) {
	ThisCall(0x707E10, this, apName);
}

// GAME - 0x7DF120
void Tile::SetName(const BSString& arName) {
	ThisCall(0x7DF120, this, &arName);
}

// GAME - 0x45CD60
Tile* Tile::GetParent() const {
	return pParent;
}

// GAME - 0xA01350
void Tile::Set(int32_t aiTrait, const char* apString, bool abClearActions) {
	ThisCall(0xA01350, this, aiTrait, apString, abClearActions);
}

// GAME - 0xA012D0
void Tile::Set(int32_t aiTrait, float afValue, bool abClearActions) {
	ThisCall(0xA012D0, this, aiTrait, afValue, abClearActions);
}

// GAME - 0x700320
void Tile::Set(int32_t aiTrait, uint32_t auiValue) {
	ThisCall(0x700320, this, aiTrait, auiValue);
}

// GAME - 0x700320
void Tile::Set(int32_t aiTrait, int32_t aiValue) {
	ThisCall(0x700320, this, aiTrait, aiValue);
}

// GAME - 0xA00E90
Tile::Value* Tile::GetValue(int32_t aiTrait) const {
	return ThisCall<Tile::Value*>(0xA00E90, this, aiTrait);
}

// GAME - 0xA011F0
const char* Tile::GetString(int32_t aiTrait) const {
	return ThisCall<const char*>(0xA011F0, this, aiTrait);
}

// GAME - 0xA011B0
float Tile::GetFloat(int32_t aiTrait) const {
	return ThisCall<float>(0xA011B0, this, aiTrait);
}

// GAME - 0x56C7F0
NiNode* Tile::GetModel() const {
	return spModel;
}

// GAME - 0xA089C0
NiNode* Tile::GetParentModel() const {
	return ThisCall<NiNode*>(0xA089C0, this);
}

// GAME - 0xA03C90
Menu* Tile::GetMenu() const {
	return ThisCall<Menu*>(0xA03C90, this);
}

// GAME - 0xA01B00
Tile* Tile::ReadFile(const char* apFileName) {
	return ThisCall<Tile*>(0xA01B00, this, apFileName);
}

// GAME - 0xA040A0
bool Tile::IsVisible() const {
	return ThisCall<bool>(0xA040A0, this);
}

// GAME - 0xBECF80
bool Tile::IsValueSet(int32_t aiTrait) const {
	return ThisCall<bool>(0xBECF80, this, aiTrait);
}

// GAME - 0xA07C60
void Tile::AddFadeControl(int32_t aiTrait, float afStart, float afEnd, float afLength, uint32_t aeType) {
	ThisCall(0xA07C60, this, aiTrait, afStart, afEnd, afLength, aeType);
}

// GAME - 0xA09030
Menu* Tile::GetMenuByClass(uint32_t auiClass) {
	return CdeclCall<Menu*>(0xA09030, auiClass);
}

// GAME - 0xA08B20
Tile* Tile::GetTileByName(Tile* apTile, const char* apName) {
	return CdeclCall<Tile*>(0xA08B20, apTile, apName);
}

// GAME - 0xA01860
int32_t Tile::TextToTrait(const char* apTraitName) {
	return CdeclCall<uint32_t>(0xA01860, apTraitName);
}

// GAME - 0xA00940
int32_t Tile::AddUserTrait(const char* apTraitName, int32_t aiIndex) {
	return CdeclCall<uint32_t>(0xA00940, apTraitName, aiIndex);
}

// GAME - 0xA01530
float Tile::GetMaximumDepth() {
	return CdeclCall<float>(0xA01530);
}

// GAME - 0xA044F0
void Tile::Lock() {
	CdeclCall(0xA044F0);
}

// GAME - 0xA04500
void Tile::Unlock() {
	CdeclCall(0xA04500);
}
