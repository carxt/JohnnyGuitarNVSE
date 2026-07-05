#pragma once

#include "nvse/GameTiles.h"
#include "nvse/Utilities.h"
#include "nvse/GameAPI.h"
#include "internal/utility.h"

typedef NiTStringPointerMap<int> TraitNameMap;
TraitNameMap* g_traitNameMap = (TraitNameMap*)0x11F32F4;
const _TraitNameToID TraitNameToID = (_TraitNameToID)0xA01860;
uint32_t(*TraitNameToIDAdd)(const char*, uint32_t) = (uint32_t(*)(const char*, uint32_t))0xA00940;

uint32_t Tile::TraitNameToID(const char* traitName) {
	return ::TraitNameToID(traitName);
}

uint32_t Tile::TraitNameToIDAdd(const char* traitName) {
	return ::TraitNameToIDAdd(traitName, 0xFFFFFFFF);
}

__declspec(naked) Tile::Value* Tile::GetValue(uint32_t typeID)
{
	__asm
	{
		push	ebx
		push	esi
		push	edi
		mov		ebx, [ecx + 0x14]
		xor esi, esi
		mov		edi, [ecx + 0x18]
		mov		edx, [esp + 0x10]
		iterHead:
		cmp		esi, edi
			jz		iterEnd
			lea		ecx, [esi + edi]
			shr		ecx, 1
			mov		eax, [ebx + ecx * 4]
			cmp[eax], edx
			jz		done
			jb		isLT
			mov		edi, ecx
			jmp		iterHead
			isLT :
		lea		esi, [ecx + 1]
			jmp		iterHead
			iterEnd :
		xor eax, eax
			done :
		pop		edi
			pop		esi
			pop		ebx
			retn	4
	}
}

Tile::Value* Tile::GetValueName(const char* valueName) {
	return GetValue(TraitNameToID(valueName));
}

// GAME - 0xA011B0
float Tile::GetFloat(uint32_t auiTrait) {
	return ThisCall<float>(0xA011B0, this, auiTrait);
}

char* Tile::GetComponentFullName(char* resStr) {
	if IS_TYPE(this, TileMenu)
		return StrCopy(resStr, name.pString);

	AutoTileLock kLock;
	char* fullName = parent->GetComponentFullName(resStr);
	*fullName++ = '/';
	fullName = StrCopy(fullName, name.pString);
	NiTListItem<Tile*>* node = reinterpret_cast<NiTListItem<Tile*>*>(parent->children.GetTailPos());
	while (node->m_element != this)
		node = node->m_pkPrev;

	int index = 0;
	while ((node = node->m_pkPrev) && StrEqualCS(name.pString, node->m_element->name.pString))
		index++;

	if (index) {
		*fullName++ = ':';
		fullName = IntToStr(index, fullName);
	}
	return fullName;
}

Menu* Tile::GetParentMenu() {
	Tile* tile = this;
	do {
		if IS_TYPE(tile, TileMenu)
			return ((TileMenu*)tile)->menu;
	} while (tile = tile->parent);
	return NULL;
}

__declspec(naked) void Tile::PokeValue(uint32_t valueID) {
	__asm
	{
		push	esi
		mov		esi, ecx
		mov		eax, [esp + 8]
		push	1
		push	0x3F800000
		push	eax
		mov		eax, 0xA012D0
		call	eax
		mov		eax, [esp + 8]
		push	1
		push	0
		push	eax
		mov		ecx, esi
		mov		eax, 0xA012D0
		call	eax
		pop		esi
		retn	4
	}
}

__declspec(naked) void Tile::FakeClick() {
	__asm
	{
		push	esi
		mov		esi, ecx
		push	1
		push	0x3F800000
		push	kTileValue_clicked
		mov		eax, 0xA012D0
		call	eax
		push	1
		push	0
		push	kTileValue_clicked
		mov		ecx, esi
		mov		eax, 0xA012D0
		call	eax
		pop		esi
		retn
	}
}

void Tile::DeleteChildren() {
	ThisCall(0xA04150, this);
}

Tile* Tile::GetChild(const char* childName) {
	AutoTileLock kLock;
	int childIndex = 0;
	char* colon = FindChr(childName, ':');
	if (colon) {
		if (colon == childName) return NULL;
		*colon = 0;
		childIndex = StrToInt(colon + 1);
	}
	Tile* result = NULL;
	auto kIter = children.GetHeadPos();
	while (kIter) {
		Tile* pTile = children.GetNext(kIter);
		if (pTile && ((*childName == '*') || StrEqualCI(pTile->name.pString, childName)) && !childIndex--) {
			result = pTile;
			break;
		}
	}
	if (colon) *colon = ':';
	return result;
}

Tile* Tile::GetComponent(const char* componentPath, const char*& trait) {
	AutoTileLock kLock;
	Tile* parentTile = this;
	char* slashPos;
	while (slashPos = SlashPos(componentPath)) {
		*slashPos = 0;
		parentTile = parentTile->GetChild(componentPath);
		if (!parentTile) return NULL;
		componentPath = slashPos + 1;
	}
	if (*componentPath) {
		Tile* result = parentTile->GetChild(componentPath);
		if (result) return result;
		trait = componentPath;
	}
	return parentTile;
}

Tile::Value* Tile::GetComponentValue(const char* componentPath) {
	const char* trait = NULL;
	Tile* tile = GetComponent(componentPath, trait);
	return (tile && trait) ? tile->GetValueName(trait) : NULL;
}

Tile* Tile::GetComponentTile(const char* componentPath) {
	const char* trait = NULL;
	Tile* tile = GetComponent(componentPath, trait);
	return (tile && !trait) ? tile : NULL;
}

void Tile::Dump() {
	/*PrintDebug("%08X\t%s", this, name.m_data);
	s_debug.Indent();

	PrintDebug("Values:");

	s_debug.Indent();

	Value* value;
	const char* traitName;
	char traitID[9];
	for (BSSimpleArray<Value*>::Iterator iter(values); !iter.End(); ++iter) {
		value = *iter;
		traitName = TraitIDToName(value->id);

		if (!traitName) {
			UIntToHex(value->id, traitID);
			traitName = traitID;
		}
		if (value->str)
			PrintDebug("%d  %s: %s", value->id, traitName, value->str);
		/*else if (value->action)
			PrintDebug("%d  %s: Action %08X", value->id, traitName, value->action);
		else
			PrintDebug("%d  %s: %.4f", value->id, traitName, value->num);
	}

	s_debug.Outdent();

	for (DListNode<Tile>* traverse = children.Tail(); traverse; traverse = traverse->prev)
		if (traverse->data) traverse->data->Dump();

	s_debug.Outdent();*/
}

// not a one-way mapping, so we just return the first
// also this is slow and sucks
const char* TraitIDToName(int id) {
	return CdeclCall<const char*>(0xA01A70, id);
}