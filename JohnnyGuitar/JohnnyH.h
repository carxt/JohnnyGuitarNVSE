#pragma once

static SInt32 s_parserDepth = 0;

bool Cmd_JohnnyTestExpr_Parse(UInt32 numParams, ParamInfo* paramInfo, ScriptLineBuffer* lineBuf, ScriptBuffer* scriptBuf)
{

	ExpressionParser parser(scriptBuf, lineBuf);
	return (parser.ParseArgs(paramInfo, numParams));
}

double *ExpressionEvaluator::ExtractReturn()
{
	return m_result;
}

bool ExpressionParser::ParseArgs(ParamInfo* params, UInt32 numParams, bool bUsesNVSEParamTypes)
{
	// reserve space for UInt8 numargs at beginning of compiled code
	UInt8* numArgsPtr = m_lineBuf->dataBuf + m_lineBuf->dataOffset;
	m_lineBuf->dataOffset += 1;

	// see if args are enclosed in {braces}, if so don't parse beyond closing brace
	UInt32 argsEndPos = m_len;
	char ch = 0;
	UInt32 i = 0;

	while ((ch = Peek(Offset())))
	{
		if (!isspace(ch))
			break;

		Offset()++;
	}
	UInt32 offset = Offset();
	UInt32 endOffset = argsEndPos;

	if ('{' == Peek(Offset())) // restrict parsing to the enclosed text
		while ((ch = Peek(Offset())))
		{
			if (ch == '{')
			{
				offset++;
				Offset()++;

				UInt32 bracketEndPos = MatchOpenBracket(&s_operators[kOpType_LeftBrace]);
				if (bracketEndPos == -1)
				{
					Message(kError_MismatchedBrackets);
					return false;
				}
				else
					Offset() = bracketEndPos;
			}
			else if (ch == '}')
			{
				endOffset = Offset();
				argsEndPos = endOffset - 1;
				break;
			}
			else
				Offset()++;
		}
	Offset() = offset;

	while ((ch = Peek(Offset())))
	{
		if (!isspace(ch))
			break;

		Offset()++;
	}

	UInt8* dataStart = m_lineBuf->dataBuf + m_lineBuf->dataOffset;

	while (m_numArgsParsed < numParams && Offset() < argsEndPos)
	{
		// reserve space to store expr length
		m_lineBuf->dataOffset += 2;

		Token_Type argType = ParseSubExpression(argsEndPos - Offset());
		if (argType == kTokenType_Invalid)
			return false;
		else if (argType == kTokenType_Empty) {
			// reached end of args
			break;
		}
		else 		// is arg of expected type(s)?
		{
			if (!ValidateArgType(params[m_numArgsParsed].typeID, argType, bUsesNVSEParamTypes))
			{
#if RUNTIME
				ShowCompilerError(m_lineBuf, "Invalid expression for parameter %d. Expected %s.", m_numArgsParsed + 1, params[m_numArgsParsed].typeStr);
#else
				ShowCompilerError(m_scriptBuf, "Invalid expression for parameter %d. Expected %s.", m_numArgsParsed + 1, params[m_numArgsParsed].typeStr);
#endif
				return false;
			}
		}

		m_argTypes[m_numArgsParsed++] = argType;

		// store expr length for this arg
		*((UInt16*)dataStart) = (m_lineBuf->dataBuf + m_lineBuf->dataOffset) - dataStart;
		dataStart = m_lineBuf->dataBuf + m_lineBuf->dataOffset;
	}

	if (Offset() < argsEndPos && s_parserDepth == 1)	// some leftover stuff in text
	{
		// when parsing commands as args to other commands or components of larger expressions, we expect to have some leftovers
		// so this check is not necessary unless we're finished parsing the entire line
		Message(kError_TooManyArgs);
		return false;
	}
	else
		Offset() = endOffset + 1;

	// did we get all required args?
	UInt32 numExpectedArgs = 0;
	for (UInt32 i = 0; i < numParams && !params[i].isOptional; i++)
		numExpectedArgs++;

	if (numExpectedArgs > m_numArgsParsed)
	{
		ParamInfo* missingParam = &params[m_numArgsParsed];
		Message(kError_MissingParam, missingParam->typeStr, m_numArgsParsed + 1);
		return false;
	}

	*numArgsPtr = m_numArgsParsed;
	//PrintCompiledCode(m_lineBuf);
	return true;
}
