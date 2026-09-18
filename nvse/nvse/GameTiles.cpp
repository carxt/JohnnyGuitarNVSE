#include "nvse/GameTiles.h"

uint32_t Tile::TextToTrait(const char* traitName) {
	return CdeclCall<uint32_t>(0xA01860, traitName);
}

Tile::Value* Tile::GetValue(uint32_t typeID) {
	return ThisCall<Value*>(0xA00E90, this, typeID);
}

// GAME - 0xA011B0
float Tile::GetFloat(uint32_t auiTrait) {
	return ThisCall<float>(0xA011B0, this, auiTrait);
}