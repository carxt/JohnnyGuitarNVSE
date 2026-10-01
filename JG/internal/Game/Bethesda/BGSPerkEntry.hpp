#pragma once

#ifdef EDITOR
#include "BSStringT.hpp"
#endif

class TESFile;
class TESForm;
class Actor;
class BGSEntryPointFunctionData;

class BGSPerkEntry {
public:
	BGSPerkEntry();

	virtual bool						CheckConditionFilters(uint32_t auiNumFilterForms, TESForm** appFilterForms);
	virtual uint8_t						GetFunction() const;
	virtual BGSEntryPointFunctionData*	GetFunctionData() const;
	virtual								~BGSPerkEntry();
	virtual uint32_t					GetType() const;
	virtual void						ClearData();
	virtual void						InitItem(TESForm* apOwner);
	virtual BGSPerkEntry*				Copy();
	virtual void						CopyData(BGSPerkEntry* apSource);
	virtual bool						Compare(BGSPerkEntry* apOther) const;
	virtual void						Save() const;
	virtual bool						Load(TESFile* apFile);
#ifdef GAME
	virtual void						ApplyPerkEntry(Actor* apActor, bool abAlt);
	virtual void						RemovePerkEntry(Actor* apActor, bool abAlt);
#else
	virtual bool						Func_12(int, int, int, int);
	virtual void						LoadDialog(HWND, uint32_t);
	virtual void						Func_14(HWND);
	virtual void						Func_15(void*);
	virtual bool						Func_16(uint32_t aeDataType, char* apBuffer, size_t auiBufferSize);
	virtual void						Func_17(HWND, bool);
	virtual bool						Func_18(TESForm*, void*);
	virtual void						Func_19(uint32_t);
	virtual void						Func_20(TESForm*, void*, BSString& arString);
#endif

	uint8_t		ucRank;
	uint8_t		ucPriority;

	uint8_t GetRank() const;

	uint8_t GetPriority() const;
};

ASSERT_SIZE(BGSPerkEntry, 0x8);