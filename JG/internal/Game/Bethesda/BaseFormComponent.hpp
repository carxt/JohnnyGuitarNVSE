#pragma once

#include "BSEnums.hpp"

class BaseFormComponent {
public:
	BaseFormComponent();
	~BaseFormComponent();

	virtual void	InitializeDataComponent();
	virtual void	ClearDataComponent();
	virtual void	CopyComponent(BaseFormComponent* apSource);
	virtual bool	CompareComponent(BaseFormComponent* apOther);
};

ASSERT_SIZE(BaseFormComponent, 0x4);