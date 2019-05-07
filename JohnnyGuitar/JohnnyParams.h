#pragma once

#include "nvse/ParamInfos.h"
ParamInfo kParamsJohnnyAnyExpr[1] =
{
	{ "any expression", kNVSEParamType_BasicType, 0 },
};


ParamInfo kParamsJohnnyOneStringOneOptionalObjectID[2] =
{
	{ "String", kParamType_String, 0},
	{ "ObjectID",	kParamType_ObjectID, 1 },
};


 ParamInfo kParamsJohnny_OneString_OneInt[2] =
{
	{ "string",	kParamType_String,	0 },
	{ "Integer", kParamType_Integer, 0 },
};

ParamInfo kParamsJohnnyOneForm_OneInt_OneFloat[3] =
{
	{ "Form", kParamType_AnyForm, 0 },
	{ "Integer", kParamType_Integer, 0 },
	{ "Float", kParamType_Float, 0 }
};
ParamInfo kParamsJohnnyOneOptionalFloat[1] =
{
	{ "Float", kParamType_Float, 1 },
};

ParamInfo kParamsJohnnyThreeFloats[3] =
{
	{ "Float", kParamType_Float, 0 },
	{ "Float", kParamType_Float, 0 },
	{ "Float", kParamType_Float, 0 },
};

ParamInfo kParamsJohnny_OneForm_OneOptionalInt[2] =
{
	{ "form",	kParamType_AnyForm,	0 },
	{ "int",	kParamType_Integer, 0 },
};
ParamInfo kParamsJohnny_OneObjectID_OneOptionalInt[2] =
{
	{ "item",		kParamType_ObjectID,	0 },
	{ "integer",	kParamType_Integer,		1 },
};

ParamInfo kParamsJohnny_OneForm_TwoInts[3] =
{
	{ "form",	kParamType_AnyForm,	0 },
	{ "int",	kParamType_Integer, 0 },
	{ "int",	kParamType_Integer, 0 },
};

ParamInfo kParamsJohnny_TwoForms[2] =
{
	{ "form",	kParamType_AnyForm,	0 },
	{ "form",	kParamType_AnyForm,	0 },
};
