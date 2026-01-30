#pragma once

#include "ScriptUtils.h"

struct UserFunctionParam
{
	uint16_t	varIdx;
	uint8_t	varType;

	UserFunctionParam(uint16_t _idx, uint16_t _type) : varIdx(_idx), varType(_type) { }
	UserFunctionParam() : varIdx(-1), varType(Script::eVarType_Invalid) { }
};

#if RUNTIME

struct FunctionContext;

// base class for Template Method-ish objects to execute function scripts
// derive from it to allow function scripts to be invoked from script or internal code
class FunctionCaller
{
public:
	virtual ~FunctionCaller() { }

	virtual uint8_t ReadCallerVersion() = 0;
	virtual Script * ReadScript() = 0;
	virtual bool PopulateArgs(ScriptEventList* eventList, FunctionInfo* info) = 0;

	virtual TESObjectREFR* ThisObj() = 0;
	virtual TESObjectREFR* ContainingObj() = 0;
	virtual Script* GetInvokingScript() { return NULL; }
};

// stores info about function script (params, etc). generated once per function script and cached
struct FunctionInfo
{
private:
	DynamicParamInfo	m_dParamInfo;
	std::vector<UserFunctionParam> m_userFunctionParams;
	Script				* m_script;			// function script
	uint16_t				* m_destructibles;	// dynamic array of var indexes of local array vars to be destroyed on function return
	uint8_t				m_numDestructibles;
	uint8_t				m_functionVersion;	// bytecode version of Function statement
	bool				m_bad;
	uint8_t				m_instanceCount;
	ScriptEventList		* m_eventList;		// cached for quicker construction of function script, but requires care when dealing with recursive function calls

public:
	FunctionInfo(Script* script);
	~FunctionInfo();

	FunctionContext	* CreateContext(uint8_t version, Script* invokingScript);
	bool IsGood() { return !m_bad; }
	bool IsActive() { return m_instanceCount ? true : false; }
	Script* GetScript() { return m_script; }
	ParamInfo* Params() { return m_dParamInfo.Params(); }
	DynamicParamInfo& ParamInfo() { return m_dParamInfo; }
	UserFunctionParam* GetParam(uint32_t paramIndex);
	bool CleanEventList(ScriptEventList* eventList);
	bool Execute(FunctionCaller& caller, FunctionContext* context);
	ScriptEventList* GetEventList() { return m_eventList; }
	uint32_t GetParamVarTypes(uint8_t* out) const;	// returns count, if > 0 returns types as array
};

// represents a function executing on the stack
struct FunctionContext
{
private:
	FunctionInfo	* m_info;
	ScriptEventList	* m_eventList;		// temporary eventlist generated for function script
	ScriptToken		* m_result;
	Script			* m_invokingScript;
	uint8_t			m_callerVersion;
	bool			m_bad;
public:
	FunctionContext(FunctionInfo* info, uint8_t version, Script* invokingScript);
	~FunctionContext();

	bool Execute(FunctionCaller & caller);
	bool Return(ExpressionEvaluator* eval);
	bool IsGood() { return !m_bad; }
	ScriptToken*  Result() { return m_result; }
	FunctionInfo* Info() { return m_info; }
	Script* InvokingScript() { return m_invokingScript; }
};

// controls user function calls.
// Manages a stack of function contexts
// Function args in Call bytecode. FunctionInfo encoded in Begin Function data. Return value from SetFunctionValue.
class UserFunctionManager
{
	static UserFunctionManager	* GetSingleton();

	UserFunctionManager();

	static const uint32_t	kMaxNestDepth = 30;	// arbitrarily low; have seen 180+ nested calls execute w/o problems
	
	uint32_t								m_nestDepth;
	std::stack<FunctionContext*>		m_functionStack;
	std::map<Script*, FunctionInfo*>	m_functionInfos;

	// these take a ptr to the function script to check that it matches executing script
	FunctionContext* Top(Script* funcScript);
	bool Pop(Script* funcScript);
	void Push(FunctionContext* context) { m_functionStack.push(context); }
	FunctionInfo* GetFunctionInfo(Script* funcScript);

public:
	~UserFunctionManager();

	enum { kVersion = 1 };	// increment when bytecode representation changes

	static ScriptToken* Call(ExpressionEvaluator* eval);
	static bool	Return(ExpressionEvaluator* eval);
	static bool Enter(Script* funcScript);
	static ScriptToken* Call(FunctionCaller & caller);
	static uint32_t GetFunctionParamTypes(Script* fnScript, uint8_t* typesOut);

	// return script that called fnScript
	static Script* GetInvokingScript(Script* fnScript);
};

// allows us to call function scripts directly
class InternalFunctionCaller : public FunctionCaller
{
public:
	InternalFunctionCaller(Script* script, TESObjectREFR* callingObj = NULL, TESObjectREFR* container = NULL)
		: m_callerVersion(UserFunctionManager::kVersion), m_numArgs(0), m_script(script), m_thisObj(callingObj), m_container(container) { }

	virtual ~InternalFunctionCaller() { }
	virtual uint8_t ReadCallerVersion() {	return m_callerVersion; }
	virtual Script * ReadScript() {	return m_script; }
	virtual bool PopulateArgs(ScriptEventList* eventList, FunctionInfo* info);
	virtual TESObjectREFR* ThisObj() { return m_thisObj; }
	virtual TESObjectREFR* ContainingObj() { return m_container; }
	
	bool SetArgs(uint8_t numArgs, ...);
	bool vSetArgs(uint8_t numArgs, va_list args);

protected:
	enum { kMaxArgs = 5 };	

	uint8_t			m_callerVersion;
	uint8_t			m_numArgs;
	Script			* m_script;
	void			* m_args[kMaxArgs];
	TESObjectREFR	* m_thisObj;
	TESObjectREFR	* m_container;

	virtual bool ValidateParam(UserFunctionParam* param, uint8_t paramIndex) { return true; }
}; 

namespace PluginAPI {
	bool CallFunctionScript(Script* fnScript, TESObjectREFR* callingObj, TESObjectREFR* container,
		NVSEArrayVarInterface::Element* result, uint8_t numArgs, ...);
}

#endif