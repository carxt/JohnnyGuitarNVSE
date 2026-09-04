#include "GameAPI.h"
#include "GameScript.h"
#include "GameForms.h"
#include "GameObjects.h"
#include "CommandTable.h"
#include "GameRTTI.h"
#include "internal/utility.h"

//uint32_t GetDeclaredVariableType(const char* varName, const char* scriptText)
//{
//	Tokenizer scriptLines(scriptText, "\n\r");
//	std::string curLine;
//	while (scriptLines.NextToken(curLine) != -1)
//	{
//		Tokenizer tokens(curLine.c_str(), " \t\n\r");
//		std::string curToken;
//
//		if (tokens.NextToken(curToken) != -1)
//		{
//			uint32_t varType = -1;
//
//			// variable declaration?
//			if (!_stricmp(curToken.c_str(), "string_var"))
//				varType = Script::eVarType_String;
//			else if (!_stricmp(curToken.c_str(), "array_var"))
//				varType = Script::eVarType_Array;
//			else if (!_stricmp(curToken.c_str(), "float"))
//				varType = Script::eVarType_Float;
//			else if (!_stricmp(curToken.c_str(), "long") || !_stricmp(curToken.c_str(), "int") || !_stricmp(curToken.c_str(), "short"))
//				varType = Script::eVarType_Integer;
//			else if (!_stricmp(curToken.c_str(), "ref") || !_stricmp(curToken.c_str(), "reference"))
//				varType = Script::eVarType_Ref;
//
//			if (varType != -1 && tokens.NextToken(curToken) != -1 && !_stricmp(curToken.c_str(), varName))
//			{
//				return varType;
//			}
//		}
//	}
//
//	return Script::eVarType_Invalid;
//}

//Script* GetScriptFromForm(TESForm* form)
//{
//	TESObjectREFR* refr =  DYNAMIC_CAST(form, TESForm, TESObjectREFR);
//	if (refr)
//		form = refr->baseForm;
//
//	TESScriptableForm* scriptable = DYNAMIC_CAST(form, TESForm, TESScriptableForm);
//	return scriptable ? scriptable->script : NULL;
//}

//uint32_t Script::GetVariableType(VariableInfo *varInfo)
//{
//	if (text)
//		return GetDeclaredVariableType(varInfo->name.m_data, text);
//	else
//	{
//		// if it's a ref var a matching varIdx will appear in RefList
//		ListNode<RefVariable> *varIter = refList.Head();
//		RefVariable	*refVar;
//		do
//		{
//			refVar = varIter->data;
//			if (refVar && (refVar->varIdx == varInfo->idx))
//				return eVarType_Ref;
//		}
//		while (varIter = varIter->next);
//		return varInfo->type;
//	}
//}

#if RUNTIME

void Script::RefVariable::Resolve(ScriptLocals* eventList) {
	if (varIdx && eventList) {
		ScriptVar* var = eventList->GetVariable(varIdx);
		if (var) form = LookupFormByID(*(uint32_t*)&var->data);
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

#endif

uint32_t ScriptBuffer::GetRefIdx(Script::RefVariable* refVar) {
	return refVars.GetIndex(refVar);
}

//uint32_t ScriptBuffer::GetVariableType(VariableInfo* varInfo, Script::RefVariable* refVar)
//{
//	const char* scrText = scriptText;
//	if (refVar)
//	{
//		if (refVar->form)
//		{
//			TESScriptableForm* scriptable = NULL;
//			switch (refVar->form->GetFormType())
//			{
//			case kFormType_TESObjectREFR:
//				{
//					TESObjectREFR* refr = DYNAMIC_CAST(refVar->form, TESForm, TESObjectREFR);
//					scriptable = DYNAMIC_CAST(refr->baseForm, TESForm, TESScriptableForm);
//					break;
//				}
//			case kFormType_TESQuest:
//				scriptable = DYNAMIC_CAST(refVar->form, TESForm, TESScriptableForm);
//			}
//
//			if (scriptable && scriptable->script)
//			{
//				if (scriptable->script->text)
//					scrText = scriptable->script->text;
//				else
//					return scriptable->script->GetVariableType(varInfo);
//			}
//		}
//		else			// this is a ref variable, not a literal form - can't look up script vars
//			return Script::eVarType_Invalid;
//	}
//
//	return GetDeclaredVariableType(varInfo->name.m_data, scrText);
//}

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