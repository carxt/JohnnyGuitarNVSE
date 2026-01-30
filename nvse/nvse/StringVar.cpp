#include <string>
#include "StringVar.h"
#include "GameForms.h"
#include <algorithm>
#include "GameScript.h"
#include "Hooks_Script.h"
#include "ScriptUtils.h"
#include "GameData.h"
#include "GameApi.h"

StringVar::StringVar(const char* in_data, uint32_t in_refID)
{
	data = std::string(in_data);
	owningModIndex = in_refID >> 24;
}

const char* StringVar::GetCString()
{
	return data.c_str();
}

void StringVar::Set(const char* newString)
{
	data = std::string(newString);
}

int32_t StringVar::Compare(char* rhs, bool caseSensitive)
{
	int32_t cmp = 0;
	if (!caseSensitive)
	{
		cmp = _stricmp(data.c_str(), rhs);
		if (cmp > 0)
			return -1;
		else if (cmp < 0)
			return 1;
		else
			return 0;
	}
	else
	{
		std::string str2(rhs);
		if (data == str2)
			return 0;
		else if (data > str2)
			return -1;
		else
			return 1;
	}
}

void StringVar::Insert(const char* subString, uint32_t insertionPos)
{
	if (insertionPos < GetLength())
		data.insert(insertionPos, subString);
	else if (insertionPos == GetLength())
		data.append(subString);
}

#pragma warning(disable : 4996)	// disable checked iterator warning for std::transform with char*
uint32_t StringVar::Find(char* subString, uint32_t startPos, uint32_t numChars, bool bCaseSensitive)
{
	uint32_t pos = -1;

	if (numChars + startPos >= GetLength())
		numChars = GetLength() - startPos;

	if (startPos < GetLength())
	{
		std::string source = data.substr(startPos, numChars);
		if (!bCaseSensitive)
		{
			std::transform(source.begin(), source.end(), source.begin(), tolower);
			std::transform(subString, subString + strlen(subString), subString, tolower);
		}

		 //pos = data.substr(startPos, numChars).find(subString);	//returns -1 if not found
		pos = source.find(subString);
		if (pos != -1)
			pos += startPos;
	}

	return pos;
}

uint32_t StringVar::Count(char* subString, uint32_t startPos, uint32_t numChars, bool bCaseSensitive)
{
	if (numChars + startPos >= GetLength())
		numChars = GetLength() - startPos;

	if (startPos >= GetLength())
		return 0;

	std::string source = data.substr(startPos, numChars);	//only count occurences beginning before endPos
	uint32_t subStringLen = strlen(subString);
	if (!subStringLen)
		return 0;

	if (!bCaseSensitive)
	{
		std::transform(source.begin(), source.end(), source.begin(), tolower);
		std::transform(subString, subString + strlen(subString), subString, tolower);
	}

	uint32_t strIdx = 0;
	uint32_t count = 0;
	while (strIdx < GetLength() && ((strIdx = source.find(subString, strIdx)) != -1))
	{
		count++;
		strIdx += subStringLen;
	}

	return count;
}
#pragma warning(default : 4996)

uint32_t StringVar::GetLength()
{
	return data.length();
}

uint32_t StringVar::Replace(char* toReplace, char* replaceWith, uint32_t startPos, uint32_t numChars, bool bCaseSensitive, uint32_t numToReplace)
{
	// calc length of substring
	if (startPos >= GetLength())
		return 0;
	else if (numChars + startPos > GetLength())
		numChars = GetLength() - startPos;

	uint32_t numReplaced = 0;
	uint32_t replacementLen = strlen(replaceWith);
	uint32_t toReplaceLen = strlen(toReplace);

	// create substring
	std::string srcStr = data.substr(startPos, numChars);

	// remove substring from original string
	data.erase(startPos, numChars);

	uint32_t strIdx = 0;
	while (numReplaced < numToReplace)// && (strIdx = srcStr.find(toReplace, strIdx)) != -1)
	{
		if (bCaseSensitive)
		{
			strIdx = srcStr.find(toReplace, strIdx);
			if (strIdx == -1)
				break;
		}
		else
		{
			std::string strToReplace = toReplace;
			std::string::iterator iter = std::search(srcStr.begin() + strIdx, srcStr.end(), strToReplace.begin(), strToReplace.end(), ci_equal);
			if (iter != srcStr.end())
				strIdx = iter - srcStr.begin();
			else
				break;
		}

		numReplaced++;
		srcStr.erase(strIdx, toReplaceLen);
		if (strIdx == srcStr.length())
		{
			srcStr.append(replaceWith);
			break;						// reached end of string so all done
		}
		else
		{
			srcStr.insert(strIdx, replaceWith);
			strIdx += replacementLen;
		}
	}

	// paste altered string back into original string
	if (startPos == GetLength())
		data.append(srcStr);
	else
		data.insert(startPos, srcStr);

	return numReplaced;
}

void StringVar::Erase(uint32_t startPos, uint32_t numChars)
{
	if (numChars + startPos >= GetLength())
		numChars = GetLength() - startPos;

	if (startPos < GetLength())
		data.erase(startPos, numChars);
}

std::string StringVar::SubString(uint32_t startPos, uint32_t numChars)
{
	if (numChars + startPos >= GetLength())
		numChars = GetLength() - startPos;

	if (startPos < GetLength())
		return data.substr(startPos, numChars);
	else
		return "";
}

uint8_t StringVar::GetOwningModIndex()
{
	return owningModIndex;
}

uint32_t StringVar::GetCharType(char ch)
{
	uint32_t charType = 0;
	if (isalpha(ch))
		charType |= kCharType_Alphabetic;
	if (isdigit(ch))
		charType |= kCharType_Digit;
	if (ispunct(ch))
		charType |= kCharType_Punctuation;
	if (isprint(ch))
		charType |= kCharType_Printable;
	if (isupper(ch))
		charType |= kCharType_Uppercase;

	return charType;
}

char StringVar::At(uint32_t charPos)
{
	if (charPos < GetLength())
		return data[charPos];
	else
		return -1;
}

void StringVarMap::Save(NVSESerializationInterface* intfc)
{
	Clean();

	intfc->OpenRecord('STVS', 0);

	if (m_state) {
		for (std::map<uint32_t, StringVar*>::iterator iter = m_state->vars.begin();
				iter != m_state->vars.end();
				iter++)
		{
			if (IsTemporary(iter->first))	// don't save temp strings
				continue;

			intfc->OpenRecord('STVR', 0);
			uint8_t modIndex = iter->second->GetOwningModIndex();

			intfc->WriteRecordData(&modIndex, sizeof(uint8_t));
			intfc->WriteRecordData(&iter->first, sizeof(uint32_t));
			uint16_t len = iter->second->GetLength();
			intfc->WriteRecordData(&len, sizeof(len));
			intfc->WriteRecordData(iter->second->GetCString(), len);
		}
	}
	intfc->OpenRecord('STVE', 0);
}

void StringVarMap::Load(NVSESerializationInterface* intfc)
{
	_MESSAGE("Loading strings");
	uint32_t type, length, version, stringID, tempRefID;
	uint16_t strLength;
	uint8_t modIndex;
	char buffer[kMaxMessageLength] = { 0 };

	Clean();

	// do some basic checking to weed out potential bloat caused by scripts creating large
	// numbers of string variables
	uint32_t modVarCounts[0x100] = {0};				// for each mod, # of string vars loaded
	static const uint32_t varCountThreshold = 100;	// what we'll consider a "large number" of vars; 
													// obviously a few mods may require more than this without it being a problem
	std::set<uint8_t> exceededMods;

	bool bContinue = true;
	while (bContinue && intfc->GetNextRecordInfo(&type, &version, &length))
	{
		switch (type)
		{
		case 'STVE':			//end of block
			bContinue = false;

			if (exceededMods.size()) {
				_MESSAGE("  WARNING: substantial numbers of string variables exist for the following files (may indicate savegame bloat):");
				for (std::set<uint8_t>::iterator iter = exceededMods.begin(); iter != exceededMods.end(); ++iter) {
					_MESSAGE("    %s (%d strings)", DataHandler::Get()->GetNthModName(*iter), modVarCounts[*iter]);
				}
			}

			break;
		case 'STVR':
			intfc->ReadRecordData(&modIndex, sizeof(modIndex));
			if (!intfc->ResolveRefID(modIndex << 24, &tempRefID))
			{
				// owning mod is no longer loaded so discard
				continue;
			}
			else
				modIndex = tempRefID >> 24;

			intfc->ReadRecordData(&stringID, sizeof(stringID));
			intfc->ReadRecordData(&strLength, sizeof(strLength));
			
			intfc->ReadRecordData(buffer, strLength);
			buffer[strLength] = 0;

			Insert(stringID, new StringVar(buffer, tempRefID));
			modVarCounts[modIndex] += 1;
			if (modVarCounts[modIndex] == varCountThreshold) {
				exceededMods.insert(modIndex);
			}
					
			break;
		default:
			_MESSAGE("Error loading string map: unhandled chunk type %d", type);
			break;
		}
	}
}

uint32_t	StringVarMap::Add(uint8_t varModIndex, const char* data, bool bTemp)
{
	uint32_t varID = GetUnusedID();
	Insert(varID, new StringVar(data, varModIndex << 24));
	if (bTemp)
		MarkTemporary(varID, true);

	return varID;
}

StringVarMap g_StringMap;

bool AssignToStringVarLong(COMMAND_ARGS, const char* newValue)
{
	double strID = 0;
	uint8_t modIndex = 0;
	bool bTemp = ExpressionEvaluator::Active();
	StringVar* strVar = NULL;

	uint32_t len = (newValue) ? strlen(newValue) : 0;
	if (!newValue || len >= kMaxMessageLength)		//if null pointer or too long, assign an empty string
		newValue = "";

	if (ExtractSetStatementVar(scriptObj, eventList, scriptData, &strID, &modIndex)) {
		strVar = g_StringMap.Get(strID);
		bTemp = false;
	}
	else if (!bTemp) {
		_WARNING("Function must be used within a Set statement or NVSE expression");
		return false;
	}

	if (!modIndex)
		modIndex = scriptObj->GetModIndex();

	if (strVar)
	{
		strVar->Set(newValue);
		g_StringMap.MarkTemporary(strID, false);
	}
	else
		strID = g_StringMap.Add(modIndex, newValue, bTemp);

	*result = strID;

#if _DEBUG	// console feedback disabled in release by request (annoying when called from batch scripts)
	if (IsConsoleMode() && !bTemp)
	{
		if (len < 480)
			Console_Print("Assigned string >> \"%s\"", newValue);
		else
			Console_Print("Assigned string (too long to print)");
	}
#endif

	return true;
}

bool AssignToStringVar(COMMAND_ARGS, const char* newValue) {	// Adds another call so ExtractSetStatementVar has a fixed number of calls to unwrap
	return AssignToStringVarLong(PASS_COMMAND_ARGS, newValue);
}

void StringVarMap::Clean()		// clean up any temporary vars
{
	if (m_state) {
		while (m_state->tempVars.size())
		{
			uint32_t idToDelete = *(m_state->tempVars.begin());
			Delete(idToDelete);
		}
	}
}

namespace PluginAPI
{
	const char* GetString(uint32_t stringID)
	{
		StringVar* var = g_StringMap.Get(stringID);
		if (var)
			return var->GetCString();
		else
			return NULL;
	}

	void SetString(uint32_t stringID, const char* newVal)
	{
		StringVar* var = g_StringMap.Get(stringID);
		if (var)
			var->Set(newVal);
	}

	uint32_t CreateString(const char* strVal, void* owningScript)
	{
		Script* script = (Script*)owningScript;
		if (script)
			return g_StringMap.Add(script->GetModIndex(), strVal);
		else
			return 0;
	}
}
