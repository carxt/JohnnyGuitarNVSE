#pragma once

#include "BaseFormComponent.hpp"

class Script;
class TESForm;

class TESScriptableForm : public BaseFormComponent {
public:
	TESScriptableForm();
	~TESScriptableForm();

	Script* pScript;
	bool	bResolved;

	Script* GetFormScript() const;

	static Script* GetFormScript(TESForm* apForm);
};

ASSERT_SIZE(TESScriptableForm, 0xC);