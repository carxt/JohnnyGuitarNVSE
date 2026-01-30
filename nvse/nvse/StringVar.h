#pragma once
#include "Serialization.h"
#include "GameAPI.h"
#include "VarMap.h"

// String changes layout:
//
//	STVS - empty chunk indicating start of strings block
//		STVR
//			uint8_t modIndex
//			uint32_t stringID
//			uint16_t length
//			char data[length]
//		[STVR]
//		...
//	STVE - empty chunk indicating end of strings block
//
// Strings are discarded on load if the mod which created them is no longer present.

class StringVar
{
	std::string data;
	uint8_t		owningModIndex;
public:
	StringVar(const char* in_data, uint32_t in_refID);

	void		Set(const char* newString);
	int32_t		Compare(char* rhs, bool caseSensitive);
	void		Insert(const char* subString, uint32_t insertionPos);
	uint32_t		Find(char* subString, uint32_t startPos, uint32_t numChars, bool bCaseSensitive = false);	//returns position of substring
	uint32_t		Count(char* subString, uint32_t startPos, uint32_t numChars, bool bCaseSensitive = false);
	uint32_t		Replace(char* toReplace, char* replaceWith, uint32_t startPos, uint32_t numChars, bool bCaseSensitive, uint32_t numToReplace = -1);	//returns num replaced
	void		Erase(uint32_t startPos, uint32_t numChars);
	std::string	SubString(uint32_t startPos, uint32_t numChars);
	double*		ToFloat(uint32_t startPos, uint32_t numChars);
	char		At(uint32_t charPos);
	static uint32_t	GetCharType(char ch);

	std::string String()					{	return data;	}
	const char*	GetCString();
	uint32_t		GetLength();
	uint8_t		GetOwningModIndex();	
};

enum {
	kCharType_Alphabetic	= 1 << 0,
	kCharType_Digit			= 1 << 1,
	kCharType_Punctuation	= 1 << 2,
	kCharType_Printable		= 1 << 3,
	kCharType_Uppercase		= 1 << 4,
};

class StringVarMap : public VarMap<StringVar>
{
public:
	void Save(NVSESerializationInterface* intfc);
	void Load(NVSESerializationInterface* intfc);
	void Clean();

	uint32_t Add(uint8_t varModIndex, const char* data, bool bTemp = false);
};

extern StringVarMap g_StringMap;

bool AssignToStringVar(COMMAND_ARGS, const char* newValue);
bool AssignToStringVarLong(COMMAND_ARGS, const char* newValue);	// Increase the call count in the stack

namespace PluginAPI
{
	const char* GetString(uint32_t stringID);
	void SetString(uint32_t stringID, const char* newVal);
	uint32_t CreateString(const char* strVal, void* owningScript);
}