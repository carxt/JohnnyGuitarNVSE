#pragma once

#include "nvse/ParamInfos.h"
ParamInfo kParamsJohnnyAnyExpr[1] =
{
	{ "any expression", kNVSEParamType_BasicType, 0 },
};
ParamInfo kParamsJohnnyOneStringThreeFloats[4] =
{
	{ "String", kParamType_String, 0 },
	{ "float", kParamType_Float, 0 },
	{ "float", kParamType_Float, 0 },
	{ "float", kParamType_Float, 0 },

};
ParamInfo kParamsJohnnyFourStrings[4] =
{
	{ "String", kParamType_String, 0 },
	{ "X_Out", kParamType_String, 0 },
	{ "Y_Out", kParamType_String, 0 },
	{ "Z_Out", kParamType_String, 0 },

};
ParamInfo kParamsJohnnyTwoRefsTwoStrings[4] =
{
	{ "ref", kParamType_ObjectRef, 0 },
	{ "ref", kParamType_ObjectRef, 0 },
	{ "String", kParamType_String, 0 },
	{ "String", kParamType_String, 0 },

};

ParamInfo kParamsJohnnyOneStringOneOptionalObjectID[2] =
{
	{ "String", kParamType_String, 0 },
	{ "ObjectID",	kParamType_ObjectID, 1 },
};
ParamInfo kParamsJohnny_OneForm_OneString[2] =
{
	{ "Form", kParamType_AnyForm, 0 },
	{ "String", kParamType_String, 0 },
};

ParamInfo kParamsJohnny_OneString_OneInt[2] =
{
	{ "string",	kParamType_String,	0 },
	{ "Integer", kParamType_Integer, 0 },
};

ParamInfo kParamsJohnnyEventOneFormFilter[4] =
{
	{ "setOrRemove", kParamType_Integer, 0 },
	{ "Script", kParamType_AnyForm, 0 },
	{ "flags", kParamType_Integer, 1 },
	{ "Form", kParamType_AnyForm, 1 }

};

ParamInfo kParamsJohnnyEventOneFormOneIntFilter[5] =
{
	{ "setOrRemove", kParamType_Integer, 0 },
	{ "Script", kParamType_AnyForm, 0 },
	{ "flags", kParamType_Integer, 1 },
	{ "Form", kParamType_AnyForm, 1 },
	{ "Integer", kParamType_Integer, 1 },

};
ParamInfo kParamsJohnnyOneForm_OneInt_OneFloat[3] =
{
	{ "Form", kParamType_AnyForm, 0 },
	{ "Integer", kParamType_Integer, 0 },
	{ "Float", kParamType_Float, 0 }
};
ParamInfo kParamsJohnny_OneActorBase[1] =
{
	{ "ActorBase", kParamType_ActorBase, 0 },
};
ParamInfo kParamsJohnnyOneForm_OneInt_OneForm[3] =
{
	{ "Form", kParamType_AnyForm, 0 },
	{ "Integer", kParamType_Integer, 0 },
	{ "Form", kParamType_AnyForm, 0 }
};
ParamInfo kParamsJohnnyOneForm_OneInt_OneForm_OneInt[4] =
{
	{ "Form", kParamType_AnyForm, 0 },
	{ "Integer", kParamType_Integer, 0 },
	{ "Form", kParamType_AnyForm, 0 },
	{ "Integer", kParamType_Integer, 0 }
};
ParamInfo kParamsJohnnyOneForm_OneInt_OneString[3] =
{
	{ "Form", kParamType_AnyForm, 0 },
	{ "Integer", kParamType_Integer, 0 },
	{ "String", kParamType_String, 0 }
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
ParamInfo kParamsJohnnyFiveFloats[5] =
{
	{ "Float", kParamType_Float, 0 },
	{ "Float", kParamType_Float, 0 },
	{ "Float", kParamType_Float, 0 },
	{ "Float", kParamType_Float, 0 },
	{ "Float", kParamType_Float, 0 },
};
ParamInfo kParamsJohnny_OneForm_OneOptionalInt[2] =
{
	{ "form",	kParamType_AnyForm,	0 },
	{ "int",	kParamType_Integer, 1 },
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
ParamInfo kParamsJohnny_OneForm_TwoInts_OneString[4] =
{
	{ "form",	kParamType_AnyForm,	0 },
	{ "int",	kParamType_Integer, 0 },
	{ "int",	kParamType_Integer, 0 },
	{ "string",	kParamType_String,	0 },
};
ParamInfo kParamsJohnny_SixFloats[6] =
{
	{ "Float", kParamType_Float, 0 },
	{ "Float", kParamType_Float, 0 },
	{ "Float", kParamType_Float, 0 },
	{ "Float", kParamType_Float, 0 },
	{ "Float", kParamType_Float, 0 },
	{ "Float", kParamType_Float, 0 },
};
ParamInfo kParamsJohnny_OneForm_ThreeInts[4] =
{
	{ "form",	kParamType_AnyForm,	0 },
	{ "int",	kParamType_Integer, 0 },
	{ "int",	kParamType_Integer, 0 },
	{ "int",	kParamType_Integer, 0 },
};
ParamInfo kParamsJohnny_TwoForms[2] =
{
	{ "form",	kParamType_AnyForm,	0 },
	{ "form",	kParamType_AnyForm,	0 },
};
ParamInfo kParamsJohnny_OneString_OneInt_OneForm[3] =
{
	{ "string",	kParamType_String,	0 },
	{ "int",	kParamType_Integer, 0 },
	{ "form",	kParamType_AnyForm,	0 },
};
ParamInfo kParamsJohnny_OneIMOD[1] =
{
	{ "IMOD",	kParamType_ImageSpaceModifier,	0 },
};

ParamInfo kParamsJohnny_OneIMOD_OneInt[2] =
{
	{ "IMOD",	kParamType_ImageSpaceModifier,	0 },
	{ "int",	kParamType_Integer, 0 },
};
ParamInfo kParamsJohnny_TwoStrings_OneInt[3] =
{
	{ "string",	kParamType_String,	0 },
	{ "string",	kParamType_String,	0 },
	{ "Integer", kParamType_Integer, 0 },
};
ParamInfo kParamsJohnny_OneActorValue_OneOptionalInt[2] =
{
	{ "AV",	kParamType_ActorValue,	0 },
	{ "Integer",	kParamType_Integer,	1 },
};
ParamInfo kParamsBMPArgs[6] =
{
	{ "filename", kParamType_String, 0 },
	{ "R_Out", kParamType_String, 0 },
	{ "G_Out", kParamType_String, 0 },
	{ "B_Out", kParamType_String, 0 },
	{ "INT", kParamType_Integer, 0 },
	{ "INT", kParamType_Integer, 0 },

};

ParamInfo kParams_Johnny_OneForm_OneWeatherID_OneInt_OneOptionalGlobal[] =
{
	{ "Form", kParamType_AnyForm, 0 },
	{ "Weather ID", kParamType_WeatherID, 0 },
	{ "Integer", kParamType_Integer, 0 },
	{ "Global", kParamType_Global, 1 }
};
