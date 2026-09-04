#pragma once

#include "BSEnums.hpp"

class TESForm;

class BaseFormComponent {
public:
	BaseFormComponent();
	~BaseFormComponent();

	virtual void	InitializeDataComponent();
	virtual void	ClearDataComponent();
	virtual void	CopyComponent(BaseFormComponent* apSource);
	virtual bool	CompareComponent(BaseFormComponent* apOther);
#ifdef EDITOR
	virtual void	Func_04();
	virtual bool	Func_05(TESForm*);
	virtual void	Func_06();
	virtual bool	Func_07(HWND, int, int, int, int*);
	virtual bool	Func_08(HWND) const;
	virtual void	Func_09(HWND);
	virtual void	Func_10(HWND);
	virtual void	Func_11(HWND);
#endif
};

ASSERT_SIZE(BaseFormComponent, 0x4);