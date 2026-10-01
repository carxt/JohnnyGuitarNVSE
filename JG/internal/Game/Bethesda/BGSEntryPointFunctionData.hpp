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
#ifdef EDITOR
	virtual void						LoadDialog(HWND, uint32_t);
	virtual void						Func_08(HWND, uint32_t);
	virtual void						Func_09(int, char* apBuffer, uint32_t auiBufferSize, uint32_t);;
	virtual bool						Func_10(void*, void*);
	virtual void						Func_11(void*);
	virtual void						Func_12(void*, void*, void*);
#endif
};

ASSERT_SIZE(BGSEntryPointFunctionData, 0x4);