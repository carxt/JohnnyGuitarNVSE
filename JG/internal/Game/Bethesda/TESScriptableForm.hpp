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
	void SetFormScript(Script* apScript);

	const char* GetFormScriptEditorID() const;

	static Script* GetFormScript(const TESForm* apForm);
	static void SetFormScript(TESForm* apForm, Script* apScript);

	static const char* GetFormScriptEditorID(const TESForm* apForm);
};

ASSERT_SIZE(TESScriptableForm, 0xC);