#pragma once

#include "CommandTable.h"
static ParamInfo kParams_OneInt_ThreeScriptVars[4] =
{
	{	"int", kParamType_Integer, 0 },
	{	"int", kParamType_ScriptVariable, 0 },
	{	"int", kParamType_ScriptVariable, 0 },
	{	"int", kParamType_ScriptVariable, 0 },
};
static ParamInfo kParams_OneInt[1] =
{
	{	"int", kParamType_Integer, 0 },
};

static ParamInfo kParams_TwoInts[2] =
{
	{	"int", kParamType_Integer, 0 },
	{	"int", kParamType_Integer, 0 },
};

static ParamInfo kParams_OneRef_OneOptionalInt[2] =
{
	{ "target",kParamType_ObjectRef, 0 },
	{	"int", kParamType_Integer, 1 },
};
static ParamInfo kParams_OneOptionalInt[1] =
{
	{	"int", kParamType_Integer, 1 },
};

static ParamInfo kParams_OneInt_OneOptionalInt[2] =
{
	{	"int", kParamType_Integer, 0 },
	{	"int", kParamType_Integer, 1 },
};

static ParamInfo kParams_OneFloat[1] =
{
	{	"float", kParamType_Float,	0 },
};

static ParamInfo kParams_OneString[1] =
{
	{	"string",	kParamType_String,	0 },
};

static ParamInfo kParams_OneString_OneFloat[] =
{
	{	"string",	kParamType_String,	0 },
	{	"float",	kParamType_Float,	0 },
};

static ParamInfo kParams_TwoFloats[2] =
{
	{	"float",	kParamType_Float,	0 },
	{	"float",	kParamType_Float,	0 },
};

static ParamInfo kParams_OneObjectID[1] =
{
	{	"item", kParamType_ObjectID, 0},
};

static ParamInfo kParams_OneOptionalObjectID[1] =
{
	{	"item", kParamType_ObjectID, 1},
};

static ParamInfo kParams_OneInt_OneOptionalObjectID[2] =
{
	{	"path type",	kParamType_Integer,			0	},
	{	"item",			kParamType_ObjectID,	1	},
};

static ParamInfo kParams_OneObjectID_OneInt[2] =
{
	{	"item",		kParamType_ObjectID,	0	},
	{	"integer",	kParamType_Integer,			0	},
};

static ParamInfo kParams_OneFloat_OneOptionalObjectID[2] =
{
	{	"float",		kParamType_Float,			0	},
	{	"item",			kParamType_ObjectID,	1	},
};

static ParamInfo kParams_OneMagicItem_OneOptionalObjectID[2] =
{
   {	"magic item",	kParamType_MagicItem,		0	},
   {	"item",			kParamType_ObjectID,	1	},
};

static ParamInfo kParams_OneInventoryItem_OneOptionalObjectID[2] =
{
   {	"inv item",		kParamType_MagicItem,		0	},
   {	"target item",	kParamType_ObjectID,	1	},
};

static ParamInfo kParams_OneFormList_OneOptionalObjectID[2] =
{
   {	"form list",	kParamType_FormList,		0	},
   {	"target item",	kParamType_ObjectID,	1	},
};

static ParamInfo kParams_OneActorValue[1] =
{
	{	"actor value", kParamType_ActorValue, 0},
};

#define FORMAT_STRING_PARAMS 	\
	{"format string",	kParamType_String, 0}, \
	{"variable",		kParamType_Float, 1}, \
	{"variable",		kParamType_Float, 1}, \
	{"variable",		kParamType_Float, 1}, \
	{"variable",		kParamType_Float, 1}, \
	{"variable",		kParamType_Float, 1}, \
	{"variable",		kParamType_Float, 1}, \
	{"variable",		kParamType_Float, 1}, \
	{"variable",		kParamType_Float, 1}, \
	{"variable",		kParamType_Float, 1}, \
	{"variable",		kParamType_Float, 1}, \
	{"variable",		kParamType_Float, 1}, \
	{"variable",		kParamType_Float, 1}, \
	{"variable",		kParamType_Float, 1}, \
	{"variable",		kParamType_Float, 1}, \
	{"variable",		kParamType_Float, 1}, \
	{"variable",		kParamType_Float, 1}, \
	{"variable",		kParamType_Float, 1}, \
	{"variable",		kParamType_Float, 1}, \
	{"variable",		kParamType_Float, 1}, \
	{"variable",		kParamType_Float, 1}

static ParamInfo kParams_FormatString[21] =
{
	FORMAT_STRING_PARAMS
};

#define SIZEOF_FMT_STRING_PARAMS 21
#define NUM_PARAMS(paramInfoName) SIZEOF_ARRAY(paramInfoName, ParamInfo)

static ParamInfo kParams_OneActorRef[1] =
{
	{	"actor reference",	kParamType_Actor,	0	},
};

static ParamInfo kParams_OneOptionalActorRef[1] =
{
	{	"actor reference",	kParamType_Actor,	1	},
};

static ParamInfo kParams_Axis[1] =
{
	{	"axis",	kParamType_Axis,	0	},
};

static ParamInfo kParams_FormList[1] =
{
	{	"form list", kParamType_FormList,	0		},
};

static ParamInfo kParams_TwoStrings[2] =
{
	{	"string",	kParamType_String,	0	},
	{	"string",	kParamType_String,	0	},
};

static ParamInfo kParams_OneObject[1] =
{
	{	"target item",	kParamType_TESObject,	0	},
};

static ParamInfo kParams_OneOptionalObject[1] =
{
   {	"target item",	kParamType_TESObject,	1	},
};

static ParamInfo kParams_OneString_OneOptionalObject[2] =
{
	{	"string",		kParamType_String,			0	},
	{	"item",			kParamType_TESObject,	1	},
};

static ParamInfo kParams_OneObject_OneOptionalObject[2] =
{
	{	"target item",	kParamType_TESObject,		0	},
	{	"object",		kParamType_TESObject,		1	},
};

static ParamInfo kParams_OneInt_OneOptionalObject[2] =
{
	{	"int",	kParamType_Integer,			0	},
	{	"item",			kParamType_TESObject,	1	},
};

static ParamInfo kParams_SetEquippedFloat[2] =
{
	{	"val", kParamType_Float, 0 },
	{	"slot", kParamType_Integer, 0 },
};

static ParamInfo kParams_FormList_Integer[2] =
{
	{	"form list", kParamType_FormList,	0		},
	{	"index",	 kParamType_Integer,	0		}
};

static ParamInfo kParams_OneQuest[1] =
{
	{	"quest", kParamType_Quest, 0 },
};

static ParamInfo kParams_OneNPC[1] =
{
	{	"NPC",	kParamType_NPC,	1	},
};

static ParamInfo kParams_OneOptionalObjectRef[1] =
{
	{	"ref", kParamType_ObjectRef, 1},
};

static ParamInfo kParams_OneInt_OneOptionalObjectRef[2] =
{
	{	"flag",		kParamType_Integer,	0	},
	{	"ref",		kParamType_ObjectRef,	1	},
};

static ParamInfo kParams_OneIndex_OneOptionalObjectRef[2] =
{
	{	"index",		kParamType_Integer,	0	},
	{	"ref",		kParamType_ObjectRef,	1	},
};

static ParamInfo kParams_OnePackage_OneIndex_OneOptionalObjectRef[3] =
{
	{	"package",		kParamType_AnyForm,		0	},
	{	"index",		kParamType_Integer,		0	},
	{	"ref",			kParamType_ObjectRef,	1	},
};

static ParamInfo kParams_OneForm_OneOptionalObjectRef[2] =
{
	{	"form",	kParamType_AnyForm,		0	},
	{	"ref",	kParamType_ObjectRef,	1	},
};

static ParamInfo kParams_OneForm_OneInt[2] =
{
	{	"form",	kParamType_AnyForm,	0	},
	{	"int",	kParamType_Integer, 0	},
};

static ParamInfo kParams_TwoForms_OneInt[3] =
{
	{	"form",	kParamType_AnyForm,	0	},
	{	"form",	kParamType_AnyForm,	0	},
	{	"int",	kParamType_Integer, 0	},
};

static ParamInfo kParams_OneForm[1] =
{
	{	"form",	kParamType_AnyForm,	0	},
};

static ParamInfo kParams_OneForm_OneFloat[2] =
{
	{	"form",		kParamType_AnyForm,	0	},
	{	"float",	kParamType_Float,	0	},
};
static ParamInfo kParams_OneForm_OneOptionalForm[2] =
{
	{	"form",	kParamType_AnyForm,	0	},
	{	"form",	kParamType_AnyForm,	1	},
};
static ParamInfo kParams_OneOptionalForm[1] =
{
	{	"form",	kParamType_AnyForm,	1	},
};

static ParamInfo kParams_EquipItem[3] =
{
	{	"item",			kParamType_ObjectID,	0	},
	{	"silent",		kParamType_Integer,		1	},
	{	"lockEquip",	kParamType_Integer,		1	},
};

static ParamInfo kParams_OneFaction[1] =
{
	{	"faction",	kParamType_Faction,	0	},
};

static ParamInfo kParams_OneOptionalActorBase[1] =
{
	{	"base actor",	kParamType_ActorBase,	1	},
};

static ParamInfo kParams_OneInt_OneOptionalActorBase[2] =
{
	{	"bool",			kParamType_Integer,		0	},
	{	"base actor",	kParamType_ActorBase,	1	},
};

static ParamInfo kParams_OneRace[1] =
{
	{	"race",	kParamType_Race,	0	},
};

static ParamInfo kParams_GenericForm[4] =
{
	{	"which",			kParamType_Integer,	0	},
	{	"containingForm",	kParamType_AnyForm,	0	},
	{	"form",				kParamType_AnyForm,	0	},
	{	"index",			kParamType_Integer,	0	},
};

static ParamInfo kParams_GenericDeleteForm[3] =
{
	{	"which",			kParamType_Integer,	0	},
	{	"containingForm",	kParamType_AnyForm,	0	},
	{	"index",			kParamType_Integer,	0	},
};

static ParamInfo kParams_OneInt_OneForm[2] =
{
	{	"index",	kParamType_Integer, 0	},
	{	"form",		kParamType_AnyForm,	0	},
};

static ParamInfo kParams_AnyExpr[1] =
{
	{ "any expression", kNVSEParamType_BasicType, 0 },
};

static ParamInfo kParams_OneString_ThreeFloats[4] =
{
	{ "String", kParamType_String, 0 },
	{ "float", kParamType_Float, 0 },
	{ "float", kParamType_Float, 0 },
	{ "float", kParamType_Float, 0 },
};

static ParamInfo kParams_FourStrings[4] =
{
	{ "String", kParamType_String, 0 },
	{ "X_Out", kParamType_String, 0 },
	{ "Y_Out", kParamType_String, 0 },
	{ "Z_Out", kParamType_String, 0 },
};

static ParamInfo kParams_TwoRefs_TwoStrings[4] =
{
	{ "ref", kParamType_ObjectRef, 0 },
	{ "ref", kParamType_ObjectRef, 0 },
	{ "String", kParamType_String, 0 },
	{ "String", kParamType_String, 0 },
};

static ParamInfo kParams_OneString_OneOptionalObjectID[2] =
{
	{ "String", kParamType_String, 0 },
	{ "ObjectID",	kParamType_ObjectID, 1 },
};

static ParamInfo kParams_OneForm_OneString[2] =
{
	{ "Form", kParamType_AnyForm, 0 },
	{ "String", kParamType_String, 0 },
};

static ParamInfo kParams_OneString_TwoOptionalInts[3] =
{
	{"String", kParamType_String, 0},
	{"Integer", kParamType_Integer, 1},
	{"Integer", kParamType_Integer, 1},
};
static ParamInfo kParams_TwoOptionalInts[2] =
{
	{"Integer", kParamType_Integer, 1},
	{"Integer", kParamType_Integer, 1},
};
static ParamInfo kParams_ThreeOptionalInts[3] =
{
	{"Integer", kParamType_Integer, 1},
	{"Integer", kParamType_Integer, 1},
	{"Integer", kParamType_Integer, 1},
};
static ParamInfo kParams_ar_SortEditor[] =
{
	{	"array",		kNVSEParamType_Array,	0	},
	{	"bDescending",	kNVSEParamType_Number,	1	},
};

static ParamInfo kParams_TwoStrings_OneOptionalString_FourOptionalInts[7] =
{
	{"String", kParamType_String, 0},
	{"String", kParamType_String, 0},
	{"String", kParamType_String, 1},
	{"Integer", kParamType_Integer, 1},
	{"Integer", kParamType_Integer, 1},
	{"Integer", kParamType_Integer, 1},
	{"Integer", kParamType_Integer, 1},
};

static ParamInfo kParams_OneString_OneInt[2] =
{
	{ "string",	kParamType_String,	0 },
	{ "Integer", kParamType_Integer, 0 },
};

static ParamInfo kParams_OneInt_OneString[2] =
{
	{ "Integer", kParamType_Integer, 0 },
	{ "string",	kParamType_String,	0 },
};

static ParamInfo kParams_OneString_OneOptionalInt[2] =
{
	{ "string",	kParamType_String,	0 },
	{ "Integer", kParamType_Integer, 1 },
};
static ParamInfo kParams_OneString_TwoOptionalInts_OneOptionalFloat[4] =
{
	{ "string",	kParamType_String,	0 },
	{ "Integer", kParamType_Integer, 1 },
	{ "Integer", kParamType_Integer, 1 },
	{ "Float", kParamType_Float, 1 },
};
static ParamInfo kParams_Event_OneForm[4] =
{
	{ "setOrRemove", kParamType_Integer, 0 },
	{ "Script", kParamType_AnyForm, 0 },
	{ "flags", kParamType_Integer, 1 },
	{ "Form", kParamType_AnyForm, 1 }
};

static ParamInfo kParams_Event[3] =
{
	{ "setOrRemove", kParamType_Integer, 0 },
	{ "Script", kParamType_AnyForm, 0 },
	{ "flags", kParamType_Integer, 1 },
};

static ParamInfo kParams_Event_OptionalFlag[4] =
{
	{ "setOrRemove", kParamType_Integer, 0 },
	{ "Script", kParamType_AnyForm, 0 },
	{ "flags", kParamType_Integer, 1 },
	{ "optionalFlags", kParamType_Integer, 1 },
};

static ParamInfo kParams_Event_OneForm_OneInt[5] =
{
	{ "setOrRemove", kParamType_Integer, 0 },
	{ "Script", kParamType_AnyForm, 0 },
	{ "flags", kParamType_Integer, 1 },
	{ "Form", kParamType_AnyForm, 1 },
	{ "Integer", kParamType_Integer, 1 },
};
static ParamInfo kParams_Event_OneInt[4] =
{
	{ "setOrRemove", kParamType_Integer, 0 },
	{ "Script", kParamType_AnyForm, 0 },
	{ "flags", kParamType_Integer, 1 },
	{ "Integer", kParamType_Integer, 1 },
};
static ParamInfo kParams_OneString_OneForm_OneOptionalInt[3] =
{
	{ "String", kParamType_String, 0 },
	{ "Form", kParamType_AnyForm, 0 },
	{ "Integer", kParamType_Integer, 1 },
};
static ParamInfo kParams_OneForm_TwoInts_OneForm[4] =
{
	{ "Form", kParamType_AnyForm, 0 },
	{ "Integer", kParamType_Integer, 0 },
	{ "Integer", kParamType_Integer, 0 },
	{ "Form", kParamType_AnyForm, 0 }
};
static ParamInfo kParams_OneForm_OneInt_OneFloat[3] =
{
	{ "Form", kParamType_AnyForm, 0 },
	{ "Integer", kParamType_Integer, 0 },
	{ "Float", kParamType_Float, 0 }
};

static ParamInfo kParams_OneActorBase[1] =
{
	{ "ActorBase", kParamType_ActorBase, 0 },
};

static ParamInfo kParams_OneForm_OneInt_OneForm[3] =
{
	{ "Form", kParamType_AnyForm, 0 },
	{ "Integer", kParamType_Integer, 0 },
	{ "Form", kParamType_AnyForm, 0 }
};

static ParamInfo kParams_OneInt_OneForm_OneInt[3] =
{
	{ "Integer", kParamType_Integer, 0 },
	{ "Form", kParamType_AnyForm, 0 },
	{ "Integer", kParamType_Integer, 0 }
};

static ParamInfo kParams_OneForm_OneInt_OneForm_OneInt[4] =
{
	{ "Form", kParamType_AnyForm, 0 },
	{ "Integer", kParamType_Integer, 0 },
	{ "Form", kParamType_AnyForm, 0 },
	{ "Integer", kParamType_Integer, 0 }
};

static ParamInfo kParams_OneForm_OneInt_OneString[3] =
{
	{ "Form", kParamType_AnyForm, 0 },
	{ "Integer", kParamType_Integer, 0 },
	{ "String", kParamType_String, 0 }
};

static ParamInfo kParams_OneOptionalFloat[1] =
{
	{ "Float", kParamType_Float, 1 },
};

static ParamInfo kParams_ThreeFloats[3] =
{
	{ "Float", kParamType_Float, 0 },
	{ "Float", kParamType_Float, 0 },
	{ "Float", kParamType_Float, 0 },
};

static ParamInfo kParams_FiveFloats[5] =
{
	{ "Float", kParamType_Float, 0 },
	{ "Float", kParamType_Float, 0 },
	{ "Float", kParamType_Float, 0 },
	{ "Float", kParamType_Float, 0 },
	{ "Float", kParamType_Float, 0 },
};

static ParamInfo kParams_OneInt_OneFloat[2] =
{
	{ "int", kParamType_Integer, 0 },
	{ "Float", kParamType_Float, 0 },
};

static ParamInfo kParams_OneForm_OneOptionalInt[2] =
{
	{ "form",	kParamType_AnyForm,	0 },
	{ "int",	kParamType_Integer, 1 },
};

static ParamInfo kParams_OneObjectID_OneOptionalInt[2] =
{
	{ "item",		kParamType_ObjectID,	0 },
	{ "integer",	kParamType_Integer,		1 },
};

static ParamInfo kParams_OneForm_TwoInts[3] =
{
	{ "form",	kParamType_AnyForm,	0 },
	{ "int",	kParamType_Integer, 0 },
	{ "int",	kParamType_Integer, 0 },
};

static ParamInfo kParams_OneForm_TwoInts_OneString[4] =
{
	{ "form",	kParamType_AnyForm,	0 },
	{ "int",	kParamType_Integer, 0 },
	{ "int",	kParamType_Integer, 0 },
	{ "string",	kParamType_String,	0 },
};

static ParamInfo kParams_SixFloats[6] =
{
	{ "Float", kParamType_Float, 0 },
	{ "Float", kParamType_Float, 0 },
	{ "Float", kParamType_Float, 0 },
	{ "Float", kParamType_Float, 0 },
	{ "Float", kParamType_Float, 0 },
	{ "Float", kParamType_Float, 0 },
};

static ParamInfo kParams_OneForm_ThreeInts[4] =
{
	{ "form",	kParamType_AnyForm,	0 },
	{ "int",	kParamType_Integer, 0 },
	{ "int",	kParamType_Integer, 0 },
	{ "int",	kParamType_Integer, 0 },
};

static ParamInfo kParams_TwoForms[2] =
{
	{ "form",	kParamType_AnyForm,	0 },
	{ "form",	kParamType_AnyForm,	0 },
};

static ParamInfo kParams_OneString_OneInt_OneForm[3] =
{
	{ "string",	kParamType_String,	0 },
	{ "int",	kParamType_Integer, 0 },
	{ "form",	kParamType_AnyForm,	0 },
};

static ParamInfo kParams_OneIMOD[1] =
{
	{ "IMOD",	kParamType_ImageSpaceModifier,	0 },
};

static ParamInfo kParams_OneIMOD_OneInt[2] =
{
	{ "IMOD",	kParamType_ImageSpaceModifier,	0 },
	{ "int",	kParamType_Integer, 0 },
};

static ParamInfo kParams_TwoStrings_OneInt[3] =
{
	{ "string",	kParamType_String,	0 },
	{ "string",	kParamType_String,	0 },
	{ "Integer", kParamType_Integer, 0 },
};

static ParamInfo kParams_OneActorValue_OneOptionalInt[2] =
{
	{ "AV",	kParamType_ActorValue,	0 },
	{ "Integer",	kParamType_Integer,	1 },
};

static ParamInfo kParams_BMP[6] =
{
	{ "filename", kParamType_String, 0 },
	{ "R_Out", kParamType_String, 0 },
	{ "G_Out", kParamType_String, 0 },
	{ "B_Out", kParamType_String, 0 },
	{ "INT", kParamType_Integer, 0 },
	{ "INT", kParamType_Integer, 0 },
};

static ParamInfo kParams_OneForm_OneWeatherID_OneInt_OneOptionalGlobal[] =
{
	{ "Form", kParamType_AnyForm, 0 },
	{ "Weather ID", kParamType_WeatherID, 0 },
	{ "Integer", kParamType_Integer, 0 },
	{ "Global", kParamType_Global, 1 }
};

static ParamInfo kParams_ThreeStrings_OneInt[] =
{
	{ "string", kParamType_String, 0 },
	{ "string", kParamType_String, 0 },
	{ "string", kParamType_String, 0 },
	{ "Integer", kParamType_Integer, 0 }
};

static ParamInfo kParams_OneRef_OneInt[2] =
{
	{ "target",            kParamType_ObjectRef,    0    },
	{ "quantity",        kParamType_Integer,        1    },
};

static ParamInfo kParams_OneRef_OneForm_OneInt[3] =
{
	{ "target",            kParamType_ObjectRef,    0    },
	{ "Form",			kParamType_AnyForm, 0		},
	{ "quantity",        kParamType_Integer,        1    },
};

static ParamInfo kParams_OneRef[1] =
{
	{ "target",            kParamType_ObjectRef,    0    }
};

static ParamInfo kParams_OneActorBase_TwoInts_OneFloat[4] =
{
	{ "target",         kParamType_ActorBase,    0    },
	{ "Property Type",	kParamType_Integer,			0},
	{ "Property",       kParamType_Integer,        0 },
	{ "value",       kParamType_Float,        0 },
};

static ParamInfo kParams_OneActorBase_TwoInts[3] =
{
	{ "target",         kParamType_ActorBase,    0    },
	{ "Property Type",	kParamType_Integer,			0},
	{ "Property",       kParamType_Integer,        0 },
};

static ParamInfo kParams_SixScriptVars[6] =
{
	{ "Script Var", kParamType_ScriptVariable , 0 },
	{ "Script Var", kParamType_ScriptVariable , 0 },
	{ "Script Var", kParamType_ScriptVariable , 0 },
	{ "Script Var", kParamType_ScriptVariable , 0 },
	{ "Script Var", kParamType_ScriptVariable , 0 },
	{ "Script Var", kParamType_ScriptVariable , 0 },
};

static ParamInfo kParams_TwoScriptVars_OneOptionalScriptVar[3] =
{
	{ "Script Var", kParamType_ScriptVariable , 0 },
	{ "Script Var", kParamType_ScriptVariable , 0 },
	{ "Script Var", kParamType_ScriptVariable , 1 },
};

static ParamInfo kParams_OneForm_OneInt_OneOptionalForm[3] =
{
	{ "Form", kParamType_AnyForm, 0 },
	{ "Integer", kParamType_Integer, 0 },
	{ "Form", kParamType_AnyForm, 1 }
};

static ParamInfo kParams_ThreeInts[3] =
{
	{ "Integer", kParamType_Integer, 0 },
	{ "Integer", kParamType_Integer, 0 },
	{ "Integer", kParamType_Integer, 0 }
};


static ParamInfo kParams_OneDialogRes_OneTopic_OneInt_OneOptionalInt[4] =
{
	{ "Dialog Response",	kParamType_AnyForm,		0},
	{ "Dialog Topic",		kParamType_Topic,		0},
	{ "Integer",			kParamType_Integer,			0},
	{ "Integer",			kParamType_Integer,		1}

};


static ParamInfo kParams_OneInt_OneOptionalForm[2] =
{
	{	"index",	kParamType_Integer, 0	},
	{	"form",		kParamType_AnyForm,	1	},
};

static ParamInfo kSplatterParams[8] = {
	{ "Count",			kParamType_Integer, 0 },
	{ "Duration",		kParamType_Float,	0 },
	{ "Size mult",		kParamType_Float,	0 },
	{ "Opacity mult",	kParamType_Float,	0 },
	{ "Alpha Texture",	kParamType_String,	0 },
	{ "Color Texture",	kParamType_String,	0 },
	{ "Flare Texture",	kParamType_String,	0 },
	{ "No fade",		kParamType_Integer,	1 }
};