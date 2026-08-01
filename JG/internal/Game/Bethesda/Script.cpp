#include "Script.hpp"

// GAME - 0x500940
const SCRIPT_HEADER* Script::GetHeader() const {
	return &kHeader;
}

// GAME - 0x500940
SCRIPT_HEADER* Script::GetHeader() {
	return &kHeader;
}

// GAME - 0x55B9A0
bool Script::GetIsCompiled() const {
	return kHeader.bIsCompiled;
}

// GAME - 0x55B980
char* Script::GetText() const {
	return pText;
}

// GAME - 0x5D43E0
float Script::GetProfilerTimer() const {
	return fProfilerTimer;
}

// GAME - 0x598040
float Script::GetQuestScriptGetSecondsBuffer() const {
	return fQuestScriptGetSecondsBuffer;
}

BSSimpleList<ScriptVariable*>* Script::GetVariableList() {
	return &kVariables;
}

// GAME - 0x5D43C0
BSSimpleList<SCRIPT_REFERENCED_OBJECT*>* Script::GetReferencedObjectList() {
	return &kReferences;
}

bool Script::IsUserDefinedFunction() const {
	return *(pData + 8) == 0x0D;
}

// GAME - 0x5ABF60
ScriptLocals* Script::CreateLocalsList() {
	return ThisCall<ScriptLocals*>(0x5ABF60, this);
}

// GAME - 0x5AAF20
void Script::Init(ScriptCompileData* apData) {
	ThisCall(0x5AAF20, this, apData);
}

// GAME - 0x5AC400
void Script::CompileAndRun(ScriptCompiler* apCompiler, SCRIPT_COMPILER_NAME aeCompilerName, TESObjectREFR* apOwnerRef) {
	ThisCall(0x5AC400, this, apCompiler, aeCompilerName, apOwnerRef);
}

// GAME - 0x5AC1E0
bool Script::Run(TESObjectREFR* apOwner, ScriptLocals* apLocals, TESObjectREFR* apOwnerContainer, bool abIsPartialScript) {
	return ThisCall<bool>(0x5AC1E0, this, apOwner, apLocals, apOwnerContainer, abIsPartialScript);
}

// GAME - 0x5AC750
bool Script::SetActionFlag(TESForm* apForm, ExtraDataList* apList, uint32_t aeEvent) {
	return CdeclCall<bool>(0x5AC750, apForm, apList, aeEvent);
}