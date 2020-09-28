#pragma once

#include "nvse/GameTiles.h"
#include "nvse/Utilities.h"
#include "nvse/GameAPI.h"
#include "internal/utility.h"

typedef NiTMapBase<const char*, int> TraitNameMap;
TraitNameMap *g_traitNameMap = (TraitNameMap*)0x11F32F4;
const _TraitNameToID TraitNameToID = (_TraitNameToID)0xA01860;
UInt32 (*TraitNameToIDAdd)(const char*, UInt32) = (UInt32 (*)(const char*, UInt32))0xA00940;

UInt32 Tile::TraitNameToID(const char *traitName)
{
	return ::TraitNameToID(traitName);
}

UInt32 Tile::TraitNameToIDAdd(const char *traitName)
{
	return ::TraitNameToIDAdd(traitName, 0xFFFFFFFF);
}

Tile::Value *Tile::GetValue(UInt32 typeID)
{
	Value *value;
	for (BSSimpleArray<Value*>::Iterator iter(values); !iter.End(); ++iter)
	{
		value = *iter;
		if (!value || (value->id > typeID)) break;
		if (value->id == typeID) return value;
	}
	return NULL;
}

Tile::Value *Tile::GetValueName(const char *valueName)
{
	return GetValue(TraitNameToID(valueName));
}

DListNode<Tile> *Tile::GetNthChild(UInt32 index)
{
	return children.Tail()->Regress(index);
}

char *Tile::GetComponentFullName(char *resStr)
{
	if IS_TYPE(this, TileMenu)
		return StrCopy(resStr, name.m_data);
	char *fullName = parent->GetComponentFullName(resStr);
	*fullName++ = '/';
	fullName = StrCopy(fullName, name.m_data);
	DListNode<Tile> *node = parent->children.Tail();
	while (node->data != this)
		node = node->prev;
	int index = 0;
	while ((node = node->prev) && StrEqualCS(name.m_data, node->data->name.m_data))
		index++;
	if (index)
	{
		*fullName++ = ':';
		fullName = IntToStr(index, fullName);
	}
	return fullName;
}

Menu *Tile::GetParentMenu()
{
	Tile *tile = this;
	do
	{
		if IS_TYPE(tile, TileMenu)
			return ((TileMenu*)tile)->menu;
	}
	while (tile = tile->parent);
	return NULL;
}

__declspec(naked) void Tile::PokeValue(UInt32 valueID)
{
	__asm
	{
		push	esi
		mov		esi, ecx
		mov		eax, [esp+8]
		push	1
		push	0x3F800000
		push	eax
		mov		eax, 0xA012D0
		call	eax
		mov		eax, [esp+8]
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

__declspec(naked) void Tile::FakeClick()
{
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

void Tile::DestroyAllChildren()
{
	DListNode<Tile> *node = children.Tail();
	Tile *child;
	while (node)
	{
		child = node->data;
		node = node->prev;
		if (child) child->Destroy(true);
	}
}

Tile *Tile::GetChild(const char *childName)
{
	int childIndex = 0;
	char *colon = FindChr(childName, ':');
	if (colon)
	{
		if (colon == childName) return NULL;
		*colon = 0;
		childIndex = StrToInt(colon + 1);
	}
	Tile *result = NULL;
	for (DListNode<Tile> *node = children.Head(); node; node = node->next)
	{
		if (node->data && ((*childName == '*') || StrEqualCI(node->data->name.m_data, childName)) && !childIndex--)
		{
			result = node->data;
			break;
		}
	}
	if (colon) *colon = ':';
	return result;
}

Tile *Tile::GetComponent(const char *componentPath, const char *&trait)
{
	Tile *parentTile = this;
	char *slashPos;
	while (slashPos = SlashPos(componentPath))
	{
		*slashPos = 0;
		parentTile = parentTile->GetChild(componentPath);
		if (!parentTile) return NULL;
		componentPath = slashPos + 1;
	}
	if (*componentPath)
	{
		Tile *result = parentTile->GetChild(componentPath);
		if (result) return result;
		trait = componentPath;
	}
	return parentTile;
}

Tile::Value *Tile::GetComponentValue(const char *componentPath)
{
	const char *trait = NULL;
	Tile *tile = GetComponent(componentPath, trait);
	return (tile && trait) ? tile->GetValueName(trait) : NULL;
}

Tile *Tile::GetComponentTile(const char *componentPath)
{
	const char *trait = NULL;
	Tile *tile = GetComponent(componentPath, trait);
	return (tile && !trait) ? tile : NULL;
}

void Tile::Dump()
{
	_MESSAGE("%08X\t%s", this, name.m_data);
	gLog.Indent();

	_MESSAGE("Values:");

	gLog.Indent();
	
	Value *value;
	const char *traitName;
	char traitID[9];
	for (BSSimpleArray<Value*>::Iterator iter(values); !iter.End(); ++iter)
	{
		value = *iter;
		traitName = TraitIDToName(value->id);

		if (!traitName)
		{
			UIntToHex(value->id, traitID);
			traitName = traitID;
		}
		if (value->str)
			_MESSAGE("%d  %s: %s", value->id, traitName, value->str);
		/*else if (value->action)
			_MESSAGE("%d  %s: Action %08X", value->id, traitName, value->action);*/
		else
			_MESSAGE("%d  %s: %.4f", value->id, traitName, value->num);
	}

	gLog.Outdent();

	for (DListNode<Tile> *traverse = children.Tail(); traverse; traverse = traverse->prev)
		if (traverse->data) traverse->data->Dump();

	gLog.Outdent();
}

void Debug_DumpTraits(void)
{
	for(UInt32 i = 0; i < g_traitNameMap->numBuckets; i++)
	{
		for (TraitNameMap::Entry * bucket = g_traitNameMap->buckets[i]; bucket; bucket = bucket->next)
		{
			_MESSAGE("%s %d", bucket->key, bucket->data);
		}
	}
}

// not a one-way mapping, so we just return the first
// also this is slow and sucks
const char *TraitIDToName(int id)
{
	for (UInt32 i = 0; i < g_traitNameMap->numBuckets; i++)
		for (TraitNameMap::Entry * bucket = g_traitNameMap->buckets[i]; bucket; bucket = bucket->next)
			if(bucket->data == id)
				return bucket->key;

	return NULL;
}
