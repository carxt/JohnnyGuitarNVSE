#pragma once

#include "TESForm.hpp"
#include "BSStringT.hpp"

class ExtraDataList;
class ScriptLocals;
class ScriptVariable;
class TESQuest;
class ScriptReferencedObject;
class ScriptCompiler;
class ScriptCompileData;
struct ScriptOperator;

class Script : public TESForm {
public:
	Script();
	~Script();

	struct Header {
		uint32_t	uiVariableCount;
		uint32_t	uiReferenceCount;
		uint32_t	uiDataSize;
		uint32_t	uiLastVariableID;
		bool		bIsQuestScript;
		bool		bIsMagicEffectScript;
		bool		bIsCompiled;
	};

	Header										kHeader;
	char*										pText;
	uint8_t*									pData;
#ifdef GAME
	float										fProfilerTimer;
	float										fQuestScriptDelay;
	float										fQuestScriptSeconds;
	TESQuest*									pQuest;
#endif
	BSSimpleList<ScriptReferencedObject*>		kReferences;
	BSSimpleList<ScriptVariable*>				kVariables;

	TESFORM_TYPE(Script);

	const Header* GetHeader() const;
	Header* GetHeader();

	bool GetIsCompiled() const;

	char* GetText() const;

#ifdef GAME
	float GetProfilerTimer() const;

	float GetQuestScriptSeconds() const;
#endif

	BSSimpleList<ScriptVariable*>* GetVariableList();

	BSSimpleList<ScriptReferencedObject*>* GetReferencedObjectList();

	bool IsUserDefinedFunction() const;

	ScriptLocals* CreateLocalsList();

	void Init(ScriptCompileData* apData);

#ifdef GAME
	void CompileAndRun(ScriptCompiler* apCompiler, SCRIPT_COMPILER_NAME aeCompilerName, TESObjectREFR* apOwnerRef);

	bool Run(TESObjectREFR* apOwner, ScriptLocals* apLocals, TESObjectREFR* apOwnerContainer, bool abIsPartialScript);

	static bool SetActionFlag(TESForm* apForm, ExtraDataList* apList, uint32_t aeEvent);
#endif
};

#ifdef GAME
ASSERT_SIZE(Script, 0x54);
#else
ASSERT_SIZE(Script, 0x58);
#endif