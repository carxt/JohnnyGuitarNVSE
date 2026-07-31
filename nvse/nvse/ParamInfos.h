#pragma once

#include "CommandTable.h"
#include <ScriptUtils.h>
static ParamInfo kParams_OneInt_ThreeScriptVars[] =
{
	{	"int", kParamType_Integer, 0 },
	{	"int", kParamType_ScriptVariable, 0 },
	{	"int", kParamType_ScriptVariable, 0 },
	{	"int", kParamType_ScriptVariable, 0 },
};
static ParamInfo kParams_OneInt[] =
{
	{	"int", kParamType_Integer, 0 },
};

static ParamInfo kParams_TwoInts[] =
{
	{	"int", kParamType_Integer, 0 },
	{	"int", kParamType_Integer, 0 },
};

static ParamInfo kParams_OneRef_OneOptionalInt[] =
{
	{ "target",kParamType_ObjectRef, 0 },
	{	"int", kParamType_Integer, 1 },
};
static ParamInfo kParams_OneOptionalInt[] =
{
	{	"int", kParamType_Integer, 1 },
};

static ParamInfo kParams_OneInt_OneOptionalInt[] =
{
	{	"int", kParamType_Integer, 0 },
	{	"int", kParamType_Integer, 1 },
};

static ParamInfo kParams_OneFloat[] =
{
	{	"float", kParamType_Float,	0 },
};

static ParamInfo kParams_OneString[] =
{
	{	"string",	kParamType_String,	0 },
};

static ParamInfo kParams_OneOptionalString[] =
{
	{	"string",	kParamType_String,	1 },
};

static ParamInfo kParams_OneString_TwoInts[] =
{
	{	"string",	kParamType_String,	0 },
	{	"int", kParamType_Integer, 0 },
	{	"int", kParamType_Integer, 0 },
};

static ParamInfo kParams_OneString_OneFloat[] =
{
	{	"string",	kParamType_String,	0 },
	{	"float",	kParamType_Float,	0 },
};
static ParamInfo kParams_OneString_OneOptionalFloat[] =
{
	{	"string",	kParamType_String,	0 },
	{	"float",	kParamType_Float,	1 },
};

static ParamInfo kParams_OneString_OneOptionalObjectRef[] =
{
	{ "string", kParamType_String, 0 },
	{ "ref", kParamType_ObjectRef, 1 },
};

static ParamInfo kParams_OneString_OneOptionalFloat_TwoOptionalInts[] =
{
	{ "string",	kParamType_String,	0 },
	{ "float", kParamType_Float, 1 },
	{ "integer", kParamType_Integer, 1 },
	{ "integer", kParamType_Integer, 1 },
};
static ParamInfo kParams_OneString_OneOptionalFloat_ThreeOptionalInts[] =
{
	{ "string",	kParamType_String,	0 },
	{ "float", kParamType_Float, 1 },
	{ "integer", kParamType_Integer, 1 },
	{ "integer", kParamType_Integer, 1 },
	{ "integer", kParamType_Integer, 1 },
};
static ParamInfo kParams_OneString_OneOptionalFloat_FourOptionalInts[] =
{
	{ "string",	kParamType_String,	0 },
	{ "float", kParamType_Float, 1 },
	{ "integer", kParamType_Integer, 1 },
	{ "integer", kParamType_Integer, 1 },
	{ "integer", kParamType_Integer, 1 },
	{ "integer", kParamType_Integer, 1 },
};

static ParamInfo kParams_TwoFloats[] =
{
	{	"float",	kParamType_Float,	0 },
	{	"float",	kParamType_Float,	0 },
};

static ParamInfo kParams_TwoFloats_OneOptionalInt[] =
{
	{	"float",	kParamType_Float,	0 },
	{	"float",	kParamType_Float,	0 },
	{ 	"Integer",	kParamType_Integer,	1 },
};

static ParamInfo kParams_OneObjectID[] =
{
	{	"item", kParamType_ObjectID, 0},
};

static ParamInfo kParams_OneOptionalObjectID[] =
{
	{	"item", kParamType_ObjectID, 1},
};

static ParamInfo kParams_OneInt_OneOptionalObjectID[] =
{
	{	"path type",	kParamType_Integer,			0	},
	{	"item",			kParamType_ObjectID,	1	},
};

static ParamInfo kParams_OneObjectID_OneInt[] =
{
	{	"item",		kParamType_ObjectID,	0	},
	{	"integer",	kParamType_Integer,			0	},
};

static ParamInfo kParams_OneFloat_OneOptionalObjectID[] =
{
	{	"float",		kParamType_Float,			0	},
	{	"item",			kParamType_ObjectID,	1	},
};

static ParamInfo kParams_OneMagicItem_OneOptionalObjectID[] =
{
   {	"magic item",	kParamType_MagicItem,		0	},
   {	"item",			kParamType_ObjectID,	1	},
};

static ParamInfo kParams_OneInventoryItem_OneOptionalObjectID[] =
{
   {	"inv item",		kParamType_MagicItem,		0	},
   {	"target item",	kParamType_ObjectID,	1	},
};

static ParamInfo kParams_OneFormList_OneOptionalObjectID[] =
{
   {	"form list",	kParamType_FormList,		0	},
   {	"target item",	kParamType_ObjectID,	1	},
};

static ParamInfo kParams_OneActorValue[] =
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

static ParamInfo kParams_OneActorRef[] =
{
	{	"actor reference",	kParamType_Actor,	0	},
};

static ParamInfo kParams_OneOptionalActorRef[] =
{
	{	"actor reference",	kParamType_Actor,	1	},
};

static ParamInfo kParams_Axis[] =
{
	{	"axis",	kParamType_Axis,	0	},
};

static ParamInfo kParams_OneAxis_OneOptionalInt[] =
{
	{	"axis",	kParamType_Axis,	0	},
	{	"flag",	kParamType_Integer,	1	},
};

static ParamInfo kParams_FormList[] =
{
	{	"form list", kParamType_FormList,	0		},
};

static ParamInfo kParams_TwoStrings[] =
{
	{	"string",	kParamType_String,	0	},
	{	"string",	kParamType_String,	0	},
};

static ParamInfo kParams_OneObject[] =
{
	{	"target item",	kParamType_TESObject,	0	},
};

static ParamInfo kParams_OneOptionalObject[] =
{
   {	"target item",	kParamType_TESObject,	1	},
};

static ParamInfo kParams_OneString_OneOptionalObject[] =
{
	{	"string",		kParamType_String,			0	},
	{	"item",			kParamType_TESObject,	1	},
};

static ParamInfo kParams_OneObject_OneOptionalObject[] =
{
	{	"target item",	kParamType_TESObject,		0	},
	{	"object",		kParamType_TESObject,		1	},
};

static ParamInfo kParams_OneInt_OneOptionalObject[] =
{
	{	"int",	kParamType_Integer,			0	},
	{	"item",			kParamType_TESObject,	1	},
};

static ParamInfo kParams_SetEquippedFloat[] =
{
	{	"val", kParamType_Float, 0 },
	{	"slot", kParamType_Integer, 0 },
};

static ParamInfo kParams_FormList_Integer[] =
{
	{	"form list", kParamType_FormList,	0		},
	{	"index",	 kParamType_Integer,	0		}
};

static ParamInfo kParams_OneQuest[] =
{
	{	"quest", kParamType_Quest, 0 },
};

static ParamInfo kParams_OneNPC[] =
{
	{	"NPC",	kParamType_NPC,	1	},
};

static ParamInfo kParams_OneOptionalObjectRef[] =
{
	{	"ref", kParamType_ObjectRef, 1},
};

static ParamInfo kParams_OneInt_OneOptionalObjectRef[] =
{
	{	"flag",		kParamType_Integer,	0	},
	{	"ref",		kParamType_ObjectRef,	1	},
};

static ParamInfo kParams_OneIndex_OneOptionalObjectRef[] =
{
	{	"index",		kParamType_Integer,	0	},
	{	"ref",		kParamType_ObjectRef,	1	},
};

static ParamInfo kParams_OnePackage_OneIndex_OneOptionalObjectRef[] =
{
	{	"package",		kParamType_AnyForm,		0	},
	{	"index",		kParamType_Integer,		0	},
	{	"ref",			kParamType_ObjectRef,	1	},
};

static ParamInfo kParams_OneForm_OneOptionalObjectRef[] =
{
	{	"form",	kParamType_AnyForm,		0	},
	{	"ref",	kParamType_ObjectRef,	1	},
};

static ParamInfo kParams_OneForm_OneInt[] =
{
	{	"form",	kParamType_AnyForm,	0	},
	{	"int",	kParamType_Integer, 0	},
};

static ParamInfo kParams_TwoForms_OneInt[] =
{
	{	"form",	kParamType_AnyForm,	0	},
	{	"form",	kParamType_AnyForm,	0	},
	{	"int",	kParamType_Integer, 0	},
};
static ParamInfo kParams_TwoForms_OneOptionalFloat[] =
{
	{	"form",	kParamType_AnyForm,	0	},
	{	"form",	kParamType_AnyForm,	0	},
	{	"float",	kParamType_Float, 1	},
};
static ParamInfo kParams_OneForm[] =
{
	{	"form",	kParamType_AnyForm,	0	},
};

static ParamInfo kParams_OneForm_OneFloat[] =
{
	{	"form",		kParamType_AnyForm,	0	},
	{	"float",	kParamType_Float,	0	},
};
static ParamInfo kParams_OneForm_OneOptionalForm[] =
{
	{	"form",	kParamType_AnyForm,	0	},
	{	"form",	kParamType_AnyForm,	1	},
};
static ParamInfo kParams_OneOptionalForm[] =
{
	{	"form",	kParamType_AnyForm,	1	},
};

static ParamInfo kParams_EquipItem[] =
{
	{	"item",			kParamType_ObjectID,	0	},
	{	"silent",		kParamType_Integer,		1	},
	{	"lockEquip",	kParamType_Integer,		1	},
};

static ParamInfo kParams_OneFaction[] =
{
	{	"faction",	kParamType_Faction,	0	},
};

static ParamInfo kParams_OneOptionalActorBase[] =
{
	{	"base actor",	kParamType_ActorBase,	1	},
};

static ParamInfo kParams_OneInt_OneOptionalActorBase[] =
{
	{	"bool",			kParamType_Integer,		0	},
	{	"base actor",	kParamType_ActorBase,	1	},
};

static ParamInfo kParams_OneRace[] =
{
	{	"race",	kParamType_Race,	0	},
};

static ParamInfo kParams_GenericForm[] =
{
	{	"which",			kParamType_Integer,	0	},
	{	"containingForm",	kParamType_AnyForm,	0	},
	{	"form",				kParamType_AnyForm,	0	},
	{	"index",			kParamType_Integer,	0	},
};

static ParamInfo kParams_GenericDeleteForm[] =
{
	{	"which",			kParamType_Integer,	0	},
	{	"containingForm",	kParamType_AnyForm,	0	},
	{	"index",			kParamType_Integer,	0	},
};

static ParamInfo kParams_OneInt_OneForm[] =
{
	{	"index",	kParamType_Integer, 0	},
	{	"form",		kParamType_AnyForm,	0	},
};

static ParamInfo kParams_AnyExpr[] =
{
	{ "any expression", kNVSEParamType_BasicType, 0 },
};

static ParamInfo kParams_OneString_ThreeFloats[] =
{
	{ "String", kParamType_String, 0 },
	{ "float", kParamType_Float, 0 },
	{ "float", kParamType_Float, 0 },
	{ "float", kParamType_Float, 0 },
};

static ParamInfo kParams_FourStrings[] =
{
	{ "String", kParamType_String, 0 },
	{ "X_Out", kParamType_String, 0 },
	{ "Y_Out", kParamType_String, 0 },
	{ "Z_Out", kParamType_String, 0 },
};

static ParamInfo kParams_TwoRefs_TwoStrings[] =
{
	{ "ref", kParamType_ObjectRef, 0 },
	{ "ref", kParamType_ObjectRef, 0 },
	{ "String", kParamType_String, 0 },
	{ "String", kParamType_String, 0 },
};

static ParamInfo kParams_OneString_OneOptionalObjectID[] =
{
	{ "String", kParamType_String, 0 },
	{ "ObjectID",	kParamType_ObjectID, 1 },
};

static ParamInfo kParams_OneForm_OneString[] =
{
	{ "Form", kParamType_AnyForm, 0 },
	{ "String", kParamType_String, 0 },
};

static ParamInfo kParams_OneString_TwoOptionalInts[] =
{
	{"String", kParamType_String, 0},
	{"Integer", kParamType_Integer, 1},
	{"Integer", kParamType_Integer, 1},
};
static ParamInfo kParams_TwoOptionalInts[] =
{
	{"Integer", kParamType_Integer, 1},
	{"Integer", kParamType_Integer, 1},
};
static ParamInfo kParams_ThreeOptionalInts[] =
{
	{"Integer", kParamType_Integer, 1},
	{"Integer", kParamType_Integer, 1},
	{"Integer", kParamType_Integer, 1},
};
static ParamInfo kParams_ThreeOptionalFloats[] =
{
	{"Float", kParamType_Float, 1},
	{"Float", kParamType_Float, 1},
	{"Float", kParamType_Float, 1},
};
static ParamInfo kParams_ar_SortEditor[] =
{
	{	"array",		kNVSEParamType_Array,	0	},
	{	"bDescending",	kNVSEParamType_Number,	1	},
};

static ParamInfo kParams_TwoStrings_OneOptionalString_FourOptionalInts[] =
{
	{"String", kParamType_String, 0},
	{"String", kParamType_String, 0},
	{"String", kParamType_String, 1},
	{"Integer", kParamType_Integer, 1},
	{"Integer", kParamType_Integer, 1},
	{"Integer", kParamType_Integer, 1},
	{"Integer", kParamType_Integer, 1},
};

static ParamInfo kParams_OneString_OneInt[] =
{
	{ "string",	kParamType_String,	0 },
	{ "Integer", kParamType_Integer, 0 },
};

static ParamInfo kParams_OneInt_OneString[] =
{
	{ "Integer", kParamType_Integer, 0 },
	{ "string",	kParamType_String,	0 },
};

static ParamInfo kParams_OneString_OneOptionalInt[] =
{
	{ "string",	kParamType_String,	0 },
	{ "Integer", kParamType_Integer, 1 },
};
static ParamInfo kParams_OneString_ThreeOptionalInts[] =
{
	{ "string",	kParamType_String,	0 },
	{ "Integer", kParamType_Integer, 1 },
	{ "Integer", kParamType_Integer, 1 },
	{ "Integer", kParamType_Integer, 1 },
};
static ParamInfo kParams_OneString_TwoOptionalInts_OneOptionalFloat[] =
{
	{ "string",	kParamType_String,	0 },
	{ "Integer", kParamType_Integer, 1 },
	{ "Integer", kParamType_Integer, 1 },
	{ "Float", kParamType_Float, 1 },
};
static ParamInfo kParams_Event_OneForm[] =
{
	{ "setOrRemove", kParamType_Integer, 0 },
	{ "Script", kParamType_AnyForm, 0 },
	{ "flags", kParamType_Integer, 1 },
	{ "Form", kParamType_AnyForm, 1 }
};

static ParamInfo kParams_Event_TwoForms[] =
{
	{ "setOrRemove", kParamType_Integer, 0 },
	{ "Script", kParamType_AnyForm, 0 },
	{ "flags", kParamType_Integer, 1 },
	{ "Form", kParamType_AnyForm, 1 },
	{ "Form", kParamType_AnyForm, 1 }
};

static ParamInfo kParams_Event[] =
{
	{ "setOrRemove", kParamType_Integer, 0 },
	{ "Script", kParamType_AnyForm, 0 },
	{ "flags", kParamType_Integer, 1 },
};

static ParamInfo kParams_Event_OptionalFlag[] =
{
	{ "setOrRemove", kParamType_Integer, 0 },
	{ "Script", kParamType_AnyForm, 0 },
	{ "flags", kParamType_Integer, 1 },
	{ "optionalFlags", kParamType_Integer, 1 },
};

static ParamInfo kParams_Event_OneForm_OneInt[] =
{
	{ "setOrRemove", kParamType_Integer, 0 },
	{ "Script", kParamType_AnyForm, 0 },
	{ "flags", kParamType_Integer, 1 },
	{ "Form", kParamType_AnyForm, 1 },
	{ "Integer", kParamType_Integer, 1 },
};
static ParamInfo kParams_Event_OneInt[] =
{
	{ "setOrRemove", kParamType_Integer, 0 },
	{ "Script", kParamType_AnyForm, 0 },
	{ "flags", kParamType_Integer, 1 },
	{ "Integer", kParamType_Integer, 1 },
};
static ParamInfo kParams_OneString_OneForm_OneOptionalInt[] =
{
	{ "String", kParamType_String, 0 },
	{ "Form", kParamType_AnyForm, 0 },
	{ "Integer", kParamType_Integer, 1 },
};
static ParamInfo kParams_OneForm_TwoInts_OneForm[] =
{
	{ "Form", kParamType_AnyForm, 0 },
	{ "Integer", kParamType_Integer, 0 },
	{ "Integer", kParamType_Integer, 0 },
	{ "Form", kParamType_AnyForm, 0 }
};
static ParamInfo kParams_OneForm_OneInt_OneFloat[] =
{
	{ "Form", kParamType_AnyForm, 0 },
	{ "Integer", kParamType_Integer, 0 },
	{ "Float", kParamType_Float, 0 }
};

static ParamInfo kParams_OneActorBase[] =
{
	{ "ActorBase", kParamType_ActorBase, 0 },
};

static ParamInfo kParams_OneWorldSpace[] =
{
	{ "WorldSpace", kParamType_WorldSpace, 0 },
};


static ParamInfo kParams_OneForm_OneInt_OneForm[] =
{
	{ "Form", kParamType_AnyForm, 0 },
	{ "Integer", kParamType_Integer, 0 },
	{ "Form", kParamType_AnyForm, 0 }
};

static ParamInfo kParams_OneInt_OneForm_OneInt[] =
{
	{ "Integer", kParamType_Integer, 0 },
	{ "Form", kParamType_AnyForm, 0 },
	{ "Integer", kParamType_Integer, 0 }
};

static ParamInfo kParams_OneForm_OneInt_OneForm_OneInt[] =
{
	{ "Form", kParamType_AnyForm, 0 },
	{ "Integer", kParamType_Integer, 0 },
	{ "Form", kParamType_AnyForm, 0 },
	{ "Integer", kParamType_Integer, 0 }
};

static ParamInfo kParams_OneForm_OneInt_OneString[] =
{
	{ "Form", kParamType_AnyForm, 0 },
	{ "Integer", kParamType_Integer, 0 },
	{ "String", kParamType_String, 0 }
};

static ParamInfo kParams_OneOptionalFloat[] =
{
	{ "Float", kParamType_Float, 1 },
};

static ParamInfo kParams_ThreeFloats[] =
{
	{ "Float", kParamType_Float, 0 },
	{ "Float", kParamType_Float, 0 },
	{ "Float", kParamType_Float, 0 },
};

static ParamInfo kParams_ThreeFloats_OneInt_OneOptionalFloat[] =
{
	{ "Float", kParamType_Float, 0 },
	{ "Float", kParamType_Float, 0 },
	{ "Float", kParamType_Float, 0 },
	{ "Integer", kParamType_Integer, 0 },
	{ "Float", kParamType_Float, 1 }
};

static ParamInfo kParams_FiveFloats[] =
{
	{ "Float", kParamType_Float, 0 },
	{ "Float", kParamType_Float, 0 },
	{ "Float", kParamType_Float, 0 },
	{ "Float", kParamType_Float, 0 },
	{ "Float", kParamType_Float, 0 },
};

static ParamInfo kParams_OneInt_OneFloat[] =
{
	{ "int", kParamType_Integer, 0 },
	{ "Float", kParamType_Float, 0 },
};

static ParamInfo kParams_OneForm_OneOptionalInt[] =
{
	{ "form",	kParamType_AnyForm,	0 },
	{ "int",	kParamType_Integer, 1 },
};

static ParamInfo kParams_OneForm_OneInt_OneOptionalInt[] =
{
	{ "form",	kParamType_AnyForm,	0 },
	{ "int",	kParamType_Integer, 0 },
	{ "int",	kParamType_Integer, 1 },
};

static ParamInfo kParams_OneObjectID_OneOptionalInt[] =
{
	{ "item",		kParamType_ObjectID, 0 },
	{ "integer",	kParamType_Integer,	 1 },
};

static ParamInfo kParams_OneForm_TwoInts[] =
{
	{ "form",	kParamType_AnyForm,	0 },
	{ "int",	kParamType_Integer, 0 },
	{ "int",	kParamType_Integer, 0 },
};

static ParamInfo kParams_OneForm_TwoInts_OneString[] =
{
	{ "form",	kParamType_AnyForm,	0 },
	{ "int",	kParamType_Integer, 0 },
	{ "int",	kParamType_Integer, 0 },
	{ "string",	kParamType_String,	0 },
};

static ParamInfo kParams_SixFloats[] =
{
	{ "Float", kParamType_Float, 0 },
	{ "Float", kParamType_Float, 0 },
	{ "Float", kParamType_Float, 0 },
	{ "Float", kParamType_Float, 0 },
	{ "Float", kParamType_Float, 0 },
	{ "Float", kParamType_Float, 0 },
};

static ParamInfo kParams_OneForm_ThreeInts[] =
{
	{ "form",	kParamType_AnyForm,	0 },
	{ "int",	kParamType_Integer, 0 },
	{ "int",	kParamType_Integer, 0 },
	{ "int",	kParamType_Integer, 0 },
};

static ParamInfo kParams_OneForm_FourInts[] =
{
	{ "form",	kParamType_AnyForm,	0 },
	{ "int",	kParamType_Integer, 0 },
	{ "int",	kParamType_Integer, 0 },
	{ "int",	kParamType_Integer, 0 },
	{ "int",	kParamType_Integer, 0 },
};

static ParamInfo kParams_OneForm_FourInts_TwoOptionalForms_OneOptionalInt[] =
{
	{ "form",	kParamType_AnyForm,	0 },
	{ "int",	kParamType_Integer, 0 },
	{ "int",	kParamType_Integer, 0 },
	{ "int",	kParamType_Integer, 0 },
	{ "int",	kParamType_Integer, 0 },
	{ "form",	kParamType_AnyForm,	1 },
	{ "form",	kParamType_AnyForm,	1 },
	{ "int",	kParamType_Integer, 1 },

};

static ParamInfo kParams_TwoForms[] =
{
	{ "form",	kParamType_AnyForm,	0 },
	{ "form",	kParamType_AnyForm,	0 },
};

static ParamInfo kParams_OneString_OneInt_OneForm[] =
{
	{ "string",	kParamType_String,	0 },
	{ "int",	kParamType_Integer, 0 },
	{ "form",	kParamType_AnyForm,	0 },
};

static ParamInfo kParams_OneIMOD[] =
{
	{ "IMOD",	kParamType_ImageSpaceModifier,	0 },
};

static ParamInfo kParams_OneIMOD_OneInt[] =
{
	{ "IMOD",	kParamType_ImageSpaceModifier,	0 },
	{ "int",	kParamType_Integer, 0 },
};

static ParamInfo kParams_TwoStrings_OneInt[] =
{
	{ "string",	kParamType_String,	0 },
	{ "string",	kParamType_String,	0 },
	{ "Integer", kParamType_Integer, 0 },
};

static ParamInfo kParams_OneActorValue_OneOptionalInt[] =
{
	{ "AV",	kParamType_ActorValue,	0 },
	{ "Integer",	kParamType_Integer,	1 },
};

static ParamInfo kParams_BMP[] =
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

static ParamInfo kParams_OneRef_OneInt[] =
{
	{ "target",            kParamType_ObjectRef,    0    },
	{ "quantity",        kParamType_Integer,        1    },
};

static ParamInfo kParams_OneRef_OneForm_OneInt[] =
{
	{ "target",            kParamType_ObjectRef,    0    },
	{ "Form",			kParamType_AnyForm, 0		},
	{ "quantity",        kParamType_Integer,        1    },
};

static ParamInfo kParams_OneRef[] =
{
	{ "target",            kParamType_ObjectRef,    0    }
};

static ParamInfo kParams_OneActorBase_TwoInts_OneFloat[] =
{
	{ "target",         kParamType_ActorBase,    0    },
	{ "Property Type",	kParamType_Integer,			0},
	{ "Property",       kParamType_Integer,        0 },
	{ "value",       kParamType_Float,        0 },
};

static ParamInfo kParams_OneActorBase_TwoInts[] =
{
	{ "target",         kParamType_ActorBase,    0    },
	{ "Property Type",	kParamType_Integer,			0},
	{ "Property",       kParamType_Integer,        0 },
};

static ParamInfo kParams_SixScriptVars[] =
{
	{ "Script Var", kParamType_ScriptVariable , 0 },
	{ "Script Var", kParamType_ScriptVariable , 0 },
	{ "Script Var", kParamType_ScriptVariable , 0 },
	{ "Script Var", kParamType_ScriptVariable , 0 },
	{ "Script Var", kParamType_ScriptVariable , 0 },
	{ "Script Var", kParamType_ScriptVariable , 0 },
};

static ParamInfo kParams_TwoScriptVars_OneOptionalScriptVar[] =
{
	{ "Script Var", kParamType_ScriptVariable , 0 },
	{ "Script Var", kParamType_ScriptVariable , 0 },
	{ "Script Var", kParamType_ScriptVariable , 1 },
};

static ParamInfo kParams_OneForm_OneInt_OneOptionalForm[] =
{
	{ "Form", kParamType_AnyForm, 0 },
	{ "Integer", kParamType_Integer, 0 },
	{ "Form", kParamType_AnyForm, 1 }
};

static ParamInfo kParams_ThreeInts[] =
{
	{ "Integer", kParamType_Integer, 0 },
	{ "Integer", kParamType_Integer, 0 },
	{ "Integer", kParamType_Integer, 0 }
};


static ParamInfo kParams_OneDialogRes_OneTopic_OneInt_OneOptionalInt[] =
{
	{ "Dialog Response",	kParamType_AnyForm,		0},
	{ "Dialog Topic",		kParamType_Topic,		0},
	{ "Integer",			kParamType_Integer,			0},
	{ "Integer",			kParamType_Integer,		1}

};


static ParamInfo kParams_OneInt_OneOptionalForm[] =
{
	{	"index",	kParamType_Integer, 0	},
	{	"form",		kParamType_AnyForm,	1	},
};

static ParamInfo kSplatterParams[] = {
	{ "Count",			kParamType_Integer, 0 },
	{ "Duration",		kParamType_Float,	0 },
	{ "Size mult",		kParamType_Float,	0 },
	{ "Opacity mult",	kParamType_Float,	0 },
	{ "Alpha Texture",	kParamType_String,	0 },
	{ "Color Texture",	kParamType_String,	0 },
	{ "Flare Texture",	kParamType_String,	0 },
	{ "No fade",		kParamType_Integer,	1 }
};

static ParamInfo kTransformParams[] =
{
	{	"Block name",	kParamType_String, 0	},
	{	"X",			kParamType_Float, 0	},
	{	"Y",			kParamType_Float, 0	},
	{	"Z",			kParamType_Float, 0	},
	{	"W",			kParamType_Float, 0	},
	{	"Is Rotation",	kNVSEParamType_Boolean, 0	},
	{	"World Data",	kNVSEParamType_Boolean, 0	},
	{	"Update",		kNVSEParamType_Boolean, 0	},
};
static ParamInfo kParams_OneForm_OneInt_OneOptionalInt_OneOptionalForm[] =
{
	{	"form",	kParamType_AnyForm,	0	},
	{	"int",	kParamType_Integer, 0	},
	{	"int",	kParamType_Integer, 1	},
	{	"form",	kParamType_AnyForm,	1	},

};
static ParamInfo kParams_OneActorRef_OneInt[] =
{
	{	"actor reference",	kParamType_Actor,	0	},
	{	"int",	kParamType_Integer,				0	},

};


static ParamInfo kParams_OneFloat_OneOptionalForm[] =
{
	{	"float", kParamType_Float,	0 },
	{   "form", kParamType_AnyForm, 1 }
};

static ParamInfo kParams_EjectCasing[] =
{
	{	"Target Node",			kParamType_String,	1	},
	{	"Custom Casing Path",	kParamType_String,  1	},
};

static ParamInfo kParams_OneCasino[] =
{
	{	"Casino",	kParamType_Casino,	1	},
};

static ParamInfo kParams_OneCasinoOneInt[] =
{
	{	"Casino",	kParamType_Casino,	1	},
	{	"int",		kParamType_Integer,	1	},
};

static ParamInfo kParams_OneCasinoOneIntOneString[] =
{
	{	"Casino",	kParamType_Casino,	1	},
	{	"int",		kParamType_Integer,	1	},
	{	"string",	kParamType_String,	1	},
};

static ParamInfo kParams_OneCasinoOneForm[] =
{
	{	"Casino",	kParamType_Casino,	1	},
	{	"form",		kParamType_AnyForm,	1	},
};



static ParamInfo kParams_OneCell[] =
{
	{	"cell",	kParamType_Cell,	0	},
};

static ParamInfo kParams_OneCell_OneOptionalForm[] =
{
	{	"cell",	kParamType_Cell,	0	},
	{	"form",	kParamType_AnyForm,	1	}
};

static ParamInfo kParams_OneBoolThreeFloats[] =
{
	{	"Enable",		kParamType_Integer, 0	},
	{	"X",			kParamType_Float, 0	},
	{	"Y",			kParamType_Float, 0	},
	{	"Z",			kParamType_Float, 0	},
};

static ParamInfo kParams_OneBoolOneIntOneFloat[] =
{
	{	"Enable",		kParamType_Integer, 0	},
	{	"Axis/Mode",	kParamType_Integer, 0	},
	{	"Angle",		kParamType_Float, 0	},
	{	"Ref To Track",	kParamType_ObjectRef, 1 },
};

static ParamInfo kParams_OneRefOneOptionalFloatOneOptionalInt[] =
{
	{	"Target Reference",		kParamType_ObjectRef, 0 },
	{	"Target Radius",		kParamType_Float, 1	},
	{ 	"Face Target",			kParamType_Integer, 1 },
};

static ParamInfo kParams_IsNiSequenceActive[] =
{
	{ "Sequence Name",	kParamType_String,	0 },
	{ "Block Name", kParamType_String, 1 },
	{ "First Person", kParamType_Integer, 1 },
};

static ParamInfo kParams_StopNiSequence[] =
{
	{ "Sequence Name",	kParamType_String,	0 },
	{ "Ease Out Time",	kParamType_Float,	1 },
	{ "Block Name", kParamType_String, 1 },
	{ "First Person", kParamType_Integer, 1 },
};

static ParamInfo kParams_GetTopicInfo[] =
{
	{	"form",	kParamType_AnyForm,	0	},
	{	"int",	kParamType_Quest, 1	},
};

static ParamInfo kParams_ThreeFloatsTwoOptionalFloats[] =
{
	{ 	"X",				kParamType_Float, 0	},
	{	"Y",				kParamType_Float, 0	},
	{	"Z",				kParamType_Float, 0	},
	{	"Target Radius",	kParamType_Float, 1	},
	{	"Target Angle",		kParamType_Float, 1	},
};

static ParamInfo kParams_SetPropertyValue[] =
{
	{ "Property Name",	kParamType_String,	0 },
	{ "Item",			kParamType_Integer, 0 },
	{ "Value",			kParamType_Integer, 0 },
	{ "First Person",	kParamType_Integer, 1 },
};

static ParamInfo kParams_GetPropertyValue[] =
{
	{ "Property Name",	kParamType_String,	0 },
	{ "Item",			kParamType_Integer, 0 },
	{ "First Person",	kParamType_Integer, 1 },
};

static ParamInfo kParams_SetNiLightValue[] =
{
	{ "Property Name",	kParamType_String,	0 },
	{ "Item",			kParamType_Integer, 0 },
	{ "Value",			kParamType_Float,   0 },
	{ "First Person",	kParamType_Integer, 1 },
};

static ParamInfo kParams_SetNiLightColor[] =
{
	{ "Property Name",	kParamType_String,	0 },
	{ "Item",			kParamType_Integer, 0 },
	{ "Red",			kParamType_Float,   0 },
	{ "Green",			kParamType_Float,   0 },
	{ "Blue",			kParamType_Float,   0 },
	{ "First Person",	kParamType_Integer, 1 },
};

static ParamInfo kParams_GetNiLightColor[] =
{
	{ "Property Name",	kParamType_String,	0 },
	{ "Item",			kParamType_Integer, 0 },
	{ "Red",			kParamType_ScriptVariable,   0 },
	{ "Green",			kParamType_ScriptVariable,   0 },
	{ "Blue",			kParamType_ScriptVariable,   0 },
	{ "First Person",	kParamType_Integer, 1 },
};

static ParamInfo kParams_SetSwitchNodeIndex[] =
{
	{ "Block Name",		kParamType_String,	0 },
	{ "Index",			kParamType_Integer,	0 },
	{ "First Person",	kParamType_Integer,	1 },
};

static ParamInfo kParams_GetSwitchNodeIndex[] =
{
	{ "Block Name",		kParamType_String,	0 },
	{ "First Person",	kParamType_Integer,	1 },
};

static ParamInfo kParams_ScenegraphUpdate[] =
{
	{ "Type",				kParamType_Integer, 0 },
	{ "Time",				kParamType_Float,	1 },
	{ "Update Controllers",	kParamType_Integer, 1 },
	{ "Block Name",			kParamType_String,	1 },
	{ "First Person",		kParamType_Integer, 1 }
};

static ParamInfo kParams_GetNiBound[] =
{
	{ "Block Name",		kParamType_String,	1 },
	{ "First Person",	kParamType_Integer,	1 },
};

static ParamInfo kParamsProjectionArgsLegacy[] =
{
	{ "X_Out", kParamType_String, 0 },
	{ "Y_Out", kParamType_String, 0 },
	{ "Z_Out", kParamType_String, 0 },
	{ "Float", kParamType_Float, 0 },
	{ "Float", kParamType_Float, 0 },
	{ "Float", kParamType_Float, 0 },
	{ "HandleMode", kParamType_Integer, 0 },
	{ "Object Ref", kParamType_ObjectRef, 1 }
};

static ParamInfo kParamsProjectionArgs[] =
{
	{ "X_Out", kParamType_ScriptVariable , 0 },
	{ "Y_Out", kParamType_ScriptVariable , 0 },
	{ "Z_Out", kParamType_ScriptVariable , 0 },
	{ "Float", kParamType_Float, 0 },
	{ "Float", kParamType_Float, 0 },
	{ "Float", kParamType_Float, 0 },
	{ "HandleMode", kParamType_Integer, 0 },
	{ "Object Ref", kParamType_ObjectRef, 1 }
};

static ParamInfo kParamsCallPerRef[] =
{
	{ "Script", kParamType_AnyForm, 0 },
	{ "Type Filter", kParamType_Integer , 1 },
	{ "Distance Filter", kParamType_Float, 1 },
	{ "Angle Filter", kParamType_Float, 1 },
	{ "Cell", kParamType_AnyForm , 1 }
};

static ParamInfo kParamsCallPerRefEx[] =
{
	{ "Script", kNVSEParamType_Form, 0 },
	{ "Type Filter Array", kNVSEParamType_Array , 0 },
	{ "Distance Filter", kNVSEParamType_Number, 1 },
	{ "Angle Filter", kNVSEParamType_Number, 1 },
	{ "Cell", kNVSEParamType_Form , 1 }
};

static ParamInfo kParamsCallPerMobileObject[] =
{
	{ "Script", kParamType_AnyForm, 0 },
	{ "Process Level", kParamType_Integer , 0 },
	{ "Type Filter", kParamType_Integer , 1 },
};

static ParamInfo kParamsCallPerMobileObjectEx[] =
{
	{ "Script", kNVSEParamType_Form, 0 },
	{ "Process Level", kNVSEParamType_Number , 0 },
	{ "Type Filter Array", kNVSEParamType_Array , 0 },
};

static ParamInfo kParams_OneArray[] =
{

	{	"array",	kNVSEParamType_Array,	0	}
};

static ParamInfo kParams_SetNiPSysModifierValue[] =
{
	{ "Block Name", kParamType_String, 0 },
	{ "Item", kParamType_Integer, 0 },
	{ "Value", kParamType_Float, 0 },
	{ "First Person", kParamType_Integer, 1 },
};

static ParamInfo kParams_GetNiPSysModifierValue[] =
{
	{ "Block Name", kParamType_String, 0 },
	{ "Item", kParamType_Integer, 0 },
	{ "First Person", kParamType_Integer, 1 },
};

static ParamInfo kParams_SetParticleEmitterSpawnRate[] =
{
	{ "Block Name", kParamType_String, 0 },
	{ "Value", kParamType_Float, 0 },
	{ "First Person", kParamType_Integer, 1 },
};

static ParamInfo kParamsRemapLand[] =
{
	{ "Target Land FormID", kParamType_Integer , 0 },
	{ "Source WorldSpace", kParamType_WorldSpace, 1 },
	{ "Source Cell X", kParamType_Integer, 1 },
	{ "Source Cell Y", kParamType_Integer, 1 },
};

static ParamInfo kParamsApplyModelTextureSwap[] =
{
	{ "Base Form", kParamType_TESObject , 0 },
	{ "Block Name", kParamType_String, 1 },
	{ "Reference", kParamType_ObjectRef, 1 },
	{ "First Person", kParamType_Integer, 1 },
};