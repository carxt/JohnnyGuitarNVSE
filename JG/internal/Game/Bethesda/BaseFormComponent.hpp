#pragma once

#include "BSEnums.hpp"
#ifdef EDITOR
#include "BSStringT.hpp"
#endif

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
	virtual void	Func_04(TESForm* apForm); // Clears form if found
	virtual bool	Func_05(void*);
	virtual void	Func_06(void*, BSString& arString);
	virtual bool	Func_07(HWND, int, int, int, int*); // Callback
	virtual bool	Func_08(HWND) const; // Checks if has dialog items
	virtual void	LoadDialog(HWND);
	virtual void	Func_10(HWND); // Sets data from drialog
	virtual void	Func_11(HWND);
#endif
};

ASSERT_SIZE(BaseFormComponent, 0x4);