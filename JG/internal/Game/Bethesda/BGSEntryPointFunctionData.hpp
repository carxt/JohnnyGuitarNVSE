#pragma once

class TESFile;
class TESForm;

class BGSEntryPointFunctionData {
public:
	BGSEntryPointFunctionData();
	virtual								~BGSEntryPointFunctionData();
	virtual uint32_t					GetType() const;
	virtual BGSEntryPointFunctionData*	Copy() const;
	virtual bool						Compare(BGSEntryPointFunctionData* apOther);
	virtual void						Save(TESFile* apFile);
	virtual void						Load(TESFile* apFile);
	virtual void						InitItem(TESForm* apOwner);
};

ASSERT_SIZE(BGSEntryPointFunctionData, 0x4);