#pragma once

#include "InventoryReference.h"
#include "GameAPI.h"
#include "CommandTable.h"
#include "ArrayVar.h"

#include "Commands_Scripting.h"

#include <stack>
#include <vector>

struct ScriptRunner;
struct ForEachContext;

// abstract base for Loop classes
class Loop
{
public:
	Loop() { }
	virtual ~Loop() { }

	virtual bool Update(COMMAND_ARGS) = 0;
};

// continues until test expression evaluates false
class WhileLoop : public Loop
{
	uint32_t		m_exprOffset;		// offset of test expression in script data
public:
	WhileLoop(uint32_t exprOffset) : m_exprOffset(exprOffset) { }
	virtual ~WhileLoop() { }

	virtual bool Update(COMMAND_ARGS);
};

// iterates over contents of some collection
class ForEachLoop : public Loop
{
public:
	virtual bool Update(COMMAND_ARGS) = 0;
	virtual bool IsEmpty() = 0;
};

// iterates over elements of an Array
class ArrayIterLoop : public ForEachLoop
{
	ArrayID					m_srcID;
	ArrayID					m_iterID;
	ArrayKey				m_curKey;
	ScriptEventList::Var	* m_iterVar;

	void UpdateIterator(const ArrayElement* elem);
public:
	ArrayIterLoop(const ForEachContext* context, uint8_t modIndex);
	virtual ~ArrayIterLoop();

	virtual bool Update(COMMAND_ARGS);
	bool IsEmpty() { return (g_ArrayMap.SizeOf(m_srcID) == -1 || g_ArrayMap.SizeOf(m_srcID) == 0);	}
};

// iterates over characters in a string
class StringIterLoop : public ForEachLoop
{
	std::string		m_src;
	uint32_t			m_curIndex;
	uint32_t			m_iterID;

public:
	StringIterLoop(const ForEachContext* context);
	virtual ~StringIterLoop() { }

	virtual bool Update(COMMAND_ARGS);
	bool IsEmpty() { return m_src.length() == 0; }
};

// iterates over contents of a container, creating temporary reference for each item in turn
class ContainerIterLoop : public ForEachLoop
{
	typedef InventoryReference::Data	IRefData;

	InventoryReference			* m_invRef;
	ScriptEventList::Var		* m_refVar;
	uint32_t						m_iterIndex;
	std::vector<IRefData>		m_elements;

	bool SetIterator();
	bool UnsetIterator();
public:
	ContainerIterLoop(const ForEachContext* context);
	virtual ~ContainerIterLoop();

	virtual bool Update(COMMAND_ARGS);
	virtual bool IsEmpty() { return m_elements.size() == 0; }
};

class LoopManager
{
	LoopManager() { }

	struct LoopInfo 
	{
		Loop*		loop;
		SavedIPInfo	ipInfo;		// stack depth, ip of loop start
		uint32_t		endIP;		// ip of instruction following loop end
	};

	std::stack<LoopInfo>	m_loops;
	
	void RestoreStack(ScriptRunner* state, SavedIPInfo* info);

public:
	static LoopManager* GetSingleton();

	void Add(Loop* loop, ScriptRunner* state, uint32_t startOffset, uint32_t endOffset, COMMAND_ARGS);
	bool Break(ScriptRunner* state, COMMAND_ARGS);
	bool Continue(ScriptRunner* state, COMMAND_ARGS);
};