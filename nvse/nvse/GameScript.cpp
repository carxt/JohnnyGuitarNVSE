#include "GameAPI.h"
#include "GameScript.h"
#include "GameForms.h"
#include "GameObjects.h"
#include "CommandTable.h"
#include "GameRTTI.h"
#include "internal/utility.h"

#if RUNTIME

void Script::RefVariable::Resolve(ScriptLocals* eventList) {
	if (varIdx && eventList) {
		ScriptVar* var = eventList->GetVariable(varIdx);
		if (var) form = TESForm::GetFormByNumericID(*(uint32_t*)&var->data);
	}
}

ScriptLocals* Script::CreateEventList(void) {
#if 1
	return ThisCall<ScriptLocals*>(0x005ABF60, this);	// 4th sub above Script::Execute (was 1st above in Oblivion) Execute is the second to last call in Run
#else
#error
#endif
}

Script::RefVariable* ScriptBuffer::ResolveRef(const char* refName) {
	// ###TODO: Handle player, ref vars, quests, globals
	return NULL;
}

bool Script::RunScriptLine2(const char* text, TESObjectREFR* object, bool bSuppressOutput) {
	//ToggleConsoleOutput(!bSuppressOutput);

	ConsoleManager* consoleManager = ConsoleManager::GetSingleton();

	uint8_t	scriptBuf[sizeof(Script)];
	Script* script = (Script*)scriptBuf;

	CALL_MEMBER_FN(script, Constructor)();
	script->SetTemporary();
	CALL_MEMBER_FN(script, SetText)(text);
	bool bResult = CALL_MEMBER_FN(script, Run)(consoleManager->scriptContext, true, object);
	CALL_MEMBER_FN(script, Destructor)();

	//ToggleConsoleOutput(true);
	return bResult;
}

bool Script::RunScriptLine(const char* text, TESObjectREFR* object) {
	return RunScriptLine2(text, object, false);
}

#else		// CS-stuff below
#endif

uint32_t ScriptBuffer::GetRefIdx(Script::RefVariable* refVar) {
	return refVars.GetIndex(refVar);
}

/******************************
 Script
******************************/

class ScriptVarFinder {
	const char* m_varName;

public:
	ScriptVarFinder(const char* varName) : m_varName(varName) {}

	bool Accept(VariableInfo* varInfo) {
		return StrEqualCI(varInfo->name.pString, m_varName);
	}
};

VariableInfo* Script::GetVariableByName(const char* varName) {
	ListNode<VariableInfo>* varIter = varList.Head();
	VariableInfo* varInfo;
	do {
		varInfo = varIter->data;
		if (varInfo && StrEqualCI(varName, varInfo->name.pString))
			return varInfo;
	} while (varIter = varIter->next);
	return NULL;
}

Script::RefVariable* Script::GetVariable(uint32_t reqIdx) {
	uint32_t idx = 1;	// yes, really starts at 1
	if (reqIdx) {
		ListNode<RefVariable>* varIter = refList.Head();
		do {
			if (idx == reqIdx)
				return varIter->data;
			idx++;
		} while (varIter = varIter->next);
	}
	return NULL;
}

VariableInfo* Script::GetVariableInfo(uint32_t idx) {
	ListNode<VariableInfo>* varIter = varList.Head();
	VariableInfo* varInfo;
	do {
		varInfo = varIter->data;
		if (varInfo && (varInfo->idx == idx))
			return varInfo;
	} while (varIter = varIter->next);
	return NULL;
}

uint32_t Script::AddVariable(TESForm* form) {
	RefVariable* refVar = BSMemory::malloc<RefVariable>();
	refVar->name.Set("");
	refVar->form = form;
	refVar->varIdx = 0;

	uint32_t resultIdx = refList.Append(refVar) + 1;
	info.numRefs = resultIdx + 1;
	return resultIdx;
}

void Script::CleanupVariables() {
	refList.RemoveAll();
}

uint32_t Script::RefVarList::GetIndex(RefVariable* refVar) {
	uint32_t idx = 0;
	ListNode<RefVariable>* varIter = Head();
	do {
		idx++;
		if (varIter->data == refVar)
			return idx;
	} while (varIter = varIter->next);
	return 0;
}

/***********************************
 ScriptLineBuffer
***********************************/

//const char	* ScriptLineBuffer::kDelims_Whitespace = " \t\n\r";
//const char  * ScriptLineBuffer::kDelims_WhitespaceAndBrackets = " \t\n\r[]";

bool ScriptLineBuffer::Write(const void* buf, uint32_t bufsize) {
	if ((dataOffset + bufsize) >= kBufferSize) return false;
	memcpy(dataBuf + dataOffset, buf, bufsize);
	dataOffset += bufsize;
	return true;
}

bool ScriptLineBuffer::Write32(uint32_t buf) {
	if ((dataOffset + 4) >= kBufferSize) return false;
	*(uint32_t*)(dataBuf + dataOffset) = buf;
	dataOffset += 4;
	return true;
}

bool ScriptLineBuffer::WriteString(const char* buf) {
	uint32_t len = StrLen(buf);
	if ((dataOffset + 2 + len) >= kBufferSize) return false;
	uint8_t* dataPtr = dataBuf + dataOffset;
	*(uint16_t*)dataPtr = len;
	memcpy(dataPtr + 2, buf, len);
	dataOffset += 2 + len;
	return true;
}

bool ScriptLineBuffer::Write16(uint16_t buf) {
	if ((dataOffset + 2) >= kBufferSize) return false;
	*(uint16_t*)(dataBuf + dataOffset) = buf;
	dataOffset += 2;
	return true;
}

bool ScriptLineBuffer::WriteByte(uint8_t buf) {
	if ((dataOffset + 1) >= kBufferSize) return false;
	*(dataBuf + dataOffset) = buf;
	dataOffset++;
	return true;
}

bool ScriptLineBuffer::WriteFloat(double buf) {
	if ((dataOffset + 8) >= kBufferSize) return false;
	memcpy(dataBuf + dataOffset, &buf, 8);
	dataOffset += 8;
	return true;
}