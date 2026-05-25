#pragma once

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
	virtual void						ApplyPerkEntry(Actor* apActor, bool abAlt);
	virtual void						RemovePerkEntry(Actor* apActor, bool abAlt);

	uint8_t		ucRank;
	uint8_t		ucPriority;

	uint8_t GetRank() const;

	uint8_t GetPriority() const;
};

ASSERT_SIZE(BGSPerkEntry, 0x8);