#pragma once
#include "CommandTable.h"
#include "ParamInfos.h"

extern bool (*ExtractArgsEx)(COMMAND_ARGS_EX, ...);
extern NVSEArrayVarInterface* g_arrInterface;
extern NVSEStringVarInterface* g_strInterface;