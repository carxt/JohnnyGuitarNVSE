#pragma once

#include "CommandTable.h"
#include <ScriptUtils.h>

static SCRIPT_PARAMETER kParams_OneInt_ThreeScriptVars[] =
{
	{ "Integer", SCRIPT_PARAMETER_TYPE::INTEGER, false },
	{ "Integer", SCRIPT_PARAMETER_TYPE::SCRIPT_VARIABLE, false },
	{ "Integer", SCRIPT_PARAMETER_TYPE::SCRIPT_VARIABLE, false },
	{ "Integer", SCRIPT_PARAMETER_TYPE::SCRIPT_VARIABLE, false },
};

static SCRIPT_PARAMETER kParams_OneInt[] =
{
	{ "Integer", SCRIPT_PARAMETER_TYPE::INTEGER, false },
};

static SCRIPT_PARAMETER kParams_TwoInts[] =
{
	{ "Integer", SCRIPT_PARAMETER_TYPE::INTEGER, false },
	{ "Integer", SCRIPT_PARAMETER_TYPE::INTEGER, false },
};

static SCRIPT_PARAMETER kParams_OneRef_OneOptionalInt[] =
{
	{ "Reference",SCRIPT_PARAMETER_TYPE::REFERENCE, false },
	{ "Integer (Optional)", SCRIPT_PARAMETER_TYPE::INTEGER, true },
};

static SCRIPT_PARAMETER kParams_OneOptionalInt[] =
{
	{ "Integer (Optional)", SCRIPT_PARAMETER_TYPE::INTEGER, true },
};

static SCRIPT_PARAMETER kParams_OneInt_OneOptionalInt[] =
{
	{ "Integer", SCRIPT_PARAMETER_TYPE::INTEGER, false },
	{ "Integer (Optional)", SCRIPT_PARAMETER_TYPE::INTEGER, true },
};

static SCRIPT_PARAMETER kParams_OneFloat[] =
{
	{ "Float", SCRIPT_PARAMETER_TYPE::FLOAT, false },
};

static SCRIPT_PARAMETER kParams_OneString[] =
{
	{ "String", SCRIPT_PARAMETER_TYPE::STRING, false },
};

static SCRIPT_PARAMETER kParams_OneOptionalString[] =
{
	{ "String (Optional)", SCRIPT_PARAMETER_TYPE::STRING, true },
};

static SCRIPT_PARAMETER kParams_OneString_TwoInts[] =
{
	{ "String", SCRIPT_PARAMETER_TYPE::STRING, false },
	{ "Integer", SCRIPT_PARAMETER_TYPE::INTEGER, false },
	{ "Integer", SCRIPT_PARAMETER_TYPE::INTEGER, false },
};

static SCRIPT_PARAMETER kParams_OneString_OneFloat[] =
{
	{ "String", SCRIPT_PARAMETER_TYPE::STRING, false },
	{ "Float", SCRIPT_PARAMETER_TYPE::FLOAT, false },
};

static SCRIPT_PARAMETER kParams_OneString_OneOptionalFloat[] =
{
	{ "String", SCRIPT_PARAMETER_TYPE::STRING, false },
	{ "Float (Optional)", SCRIPT_PARAMETER_TYPE::FLOAT, true },
};

static SCRIPT_PARAMETER kParams_OneString_OneOptionalObjectRef[] =
{
	{ "String", SCRIPT_PARAMETER_TYPE::STRING, false },
	{ "Reference (Optional)", SCRIPT_PARAMETER_TYPE::REFERENCE, true },
};

static SCRIPT_PARAMETER kParams_OneString_OneOptionalFloat_TwoOptionalInts[] =
{
	{ "String", SCRIPT_PARAMETER_TYPE::STRING, false },
	{ "Float (Optional)", SCRIPT_PARAMETER_TYPE::FLOAT, true },
	{ "Integer (Optional)", SCRIPT_PARAMETER_TYPE::INTEGER, true },
	{ "Integer (Optional)", SCRIPT_PARAMETER_TYPE::INTEGER, true },
};

static SCRIPT_PARAMETER kParams_OneString_OneOptionalFloat_ThreeOptionalInts[] =
{
	{ "String", SCRIPT_PARAMETER_TYPE::STRING, false },
	{ "Float (Optional)", SCRIPT_PARAMETER_TYPE::FLOAT, true },
	{ "Integer (Optional)", SCRIPT_PARAMETER_TYPE::INTEGER, true },
	{ "Integer (Optional)", SCRIPT_PARAMETER_TYPE::INTEGER, true },
	{ "Integer (Optional)", SCRIPT_PARAMETER_TYPE::INTEGER, true },
};

static SCRIPT_PARAMETER kParams_OneString_OneOptionalFloat_FourOptionalInts[] =
{
	{ "String", SCRIPT_PARAMETER_TYPE::STRING, false },
	{ "Float (Optional)", SCRIPT_PARAMETER_TYPE::FLOAT, true },
	{ "Integer (Optional)", SCRIPT_PARAMETER_TYPE::INTEGER, true },
	{ "Integer (Optional)", SCRIPT_PARAMETER_TYPE::INTEGER, true },
	{ "Integer (Optional)", SCRIPT_PARAMETER_TYPE::INTEGER, true },
	{ "Integer (Optional)", SCRIPT_PARAMETER_TYPE::INTEGER, true },
};

static SCRIPT_PARAMETER kParams_TwoFloats[] =
{
	{ "Float", SCRIPT_PARAMETER_TYPE::FLOAT, false },
	{ "Float", SCRIPT_PARAMETER_TYPE::FLOAT, false },
};

static SCRIPT_PARAMETER kParams_TwoFloats_OneOptionalInt[] =
{
	{ "Float", SCRIPT_PARAMETER_TYPE::FLOAT, false },
	{ "Float", SCRIPT_PARAMETER_TYPE::FLOAT, false },
	{ "Integer (Optional)", SCRIPT_PARAMETER_TYPE::INTEGER, true },
};

static SCRIPT_PARAMETER kParams_OneObjectID[] =
{
	{ "Item", SCRIPT_PARAMETER_TYPE::OBJECT_ID, false },
};

static SCRIPT_PARAMETER kParams_OneOptionalObjectID[] =
{
	{ "Item (Optional)", SCRIPT_PARAMETER_TYPE::OBJECT_ID, true },
};

static SCRIPT_PARAMETER kParams_OneObjectID_OneInt[] =
{
	{ "Item", SCRIPT_PARAMETER_TYPE::OBJECT_ID, false },
	{ "Integer", SCRIPT_PARAMETER_TYPE::INTEGER, false },
};

static SCRIPT_PARAMETER kParams_OneFloat_OneOptionalObjectID[] =
{
	{ "Float", SCRIPT_PARAMETER_TYPE::FLOAT, false },
	{ "Item (Optional)", SCRIPT_PARAMETER_TYPE::OBJECT_ID, true },
};

static SCRIPT_PARAMETER kParams_OneMagicItem_OneOptionalObjectID[] =
{
   { "Magic Item", SCRIPT_PARAMETER_TYPE::MAGIC_ITEM, false },
   { "Item (Optional)", SCRIPT_PARAMETER_TYPE::OBJECT_ID, true },
};

static SCRIPT_PARAMETER kParams_OneInventoryItem_OneOptionalObjectID[] =
{
   { "inv item", SCRIPT_PARAMETER_TYPE::MAGIC_ITEM, false },
   { "Object (Optional)", SCRIPT_PARAMETER_TYPE::OBJECT_ID, true },
};

static SCRIPT_PARAMETER kParams_OneFormList_OneOptionalObjectID[] =
{
   { "Form List", SCRIPT_PARAMETER_TYPE::FORM_LIST, false },
   { "Object (Optional)", SCRIPT_PARAMETER_TYPE::OBJECT_ID, true },
};

static SCRIPT_PARAMETER kParams_OneActorValue[] =
{
	{ "Actor Value", SCRIPT_PARAMETER_TYPE::ACTOR_VALUE, false },
};

#define FORMAT_STRING_PARAMS 	\
	{ "Format String", SCRIPT_PARAMETER_TYPE::STRING, false }, \
	{ "Variable (Optional)", SCRIPT_PARAMETER_TYPE::FLOAT, true }, \
	{ "Variable (Optional)", SCRIPT_PARAMETER_TYPE::FLOAT, true }, \
	{ "Variable (Optional)", SCRIPT_PARAMETER_TYPE::FLOAT, true }, \
	{ "Variable (Optional)", SCRIPT_PARAMETER_TYPE::FLOAT, true }, \
	{ "Variable (Optional)", SCRIPT_PARAMETER_TYPE::FLOAT, true }, \
	{ "Variable (Optional)", SCRIPT_PARAMETER_TYPE::FLOAT, true }, \
	{ "Variable (Optional)", SCRIPT_PARAMETER_TYPE::FLOAT, true }, \
	{ "Variable (Optional)", SCRIPT_PARAMETER_TYPE::FLOAT, true }, \
	{ "Variable (Optional)", SCRIPT_PARAMETER_TYPE::FLOAT, true }, \
	{ "Variable (Optional)", SCRIPT_PARAMETER_TYPE::FLOAT, true }, \
	{ "Variable (Optional)", SCRIPT_PARAMETER_TYPE::FLOAT, true }, \
	{ "Variable (Optional)", SCRIPT_PARAMETER_TYPE::FLOAT, true }, \
	{ "Variable (Optional)", SCRIPT_PARAMETER_TYPE::FLOAT, true }, \
	{ "Variable (Optional)", SCRIPT_PARAMETER_TYPE::FLOAT, true }, \
	{ "Variable (Optional)", SCRIPT_PARAMETER_TYPE::FLOAT, true }, \
	{ "Variable (Optional)", SCRIPT_PARAMETER_TYPE::FLOAT, true }, \
	{ "Variable (Optional)", SCRIPT_PARAMETER_TYPE::FLOAT, true }, \
	{ "Variable (Optional)", SCRIPT_PARAMETER_TYPE::FLOAT, true }, \
	{ "Variable (Optional)", SCRIPT_PARAMETER_TYPE::FLOAT, true }, \
	{ "Variable (Optional)", SCRIPT_PARAMETER_TYPE::FLOAT, true }

static SCRIPT_PARAMETER kParams_FormatString[21] =
{
	FORMAT_STRING_PARAMS
};

#define SIZEOF_FMT_STRING_PARAMS 21
#define NUM_PARAMS(paramInfoName) SIZEOF_ARRAY(paramInfoName, SCRIPT_PARAMETER)

static SCRIPT_PARAMETER kParams_OneActorRef[] =
{
	{ "Actor", SCRIPT_PARAMETER_TYPE::ACTOR, false },
};

static SCRIPT_PARAMETER kParams_OneOptionalActorRef[] =
{
	{ "Actor (Optional)", SCRIPT_PARAMETER_TYPE::ACTOR, true },
};

static SCRIPT_PARAMETER kParams_Axis[] =
{
	{ "Axis", SCRIPT_PARAMETER_TYPE::AXIS, false },
};

static SCRIPT_PARAMETER kParams_OneAxis_OneOptionalInt[] =
{
	{ "Axis", SCRIPT_PARAMETER_TYPE::AXIS, false },
	{ "Integer (Optional)", SCRIPT_PARAMETER_TYPE::INTEGER, true },
};

static SCRIPT_PARAMETER kParams_FormList[] =
{
	{ "Form List", SCRIPT_PARAMETER_TYPE::FORM_LIST, false },
};

static SCRIPT_PARAMETER kParams_TwoStrings[] =
{
	{ "String", SCRIPT_PARAMETER_TYPE::STRING, false },
	{ "String", SCRIPT_PARAMETER_TYPE::STRING, false },
};

static SCRIPT_PARAMETER kParams_OneObject[] =
{
	{ "Object", SCRIPT_PARAMETER_TYPE::TESOBJECT, false },
};

static SCRIPT_PARAMETER kParams_OneOptionalObject[] =
{
   { "Object (Optional)", SCRIPT_PARAMETER_TYPE::TESOBJECT, true },
};

static SCRIPT_PARAMETER kParams_OneString_OneOptionalObject[] =
{
	{ "String", SCRIPT_PARAMETER_TYPE::STRING, false },
	{ "Object (Optional)", SCRIPT_PARAMETER_TYPE::TESOBJECT, true },
};

static SCRIPT_PARAMETER kParams_OneObject_OneOptionalObject[] =
{
	{ "Object", SCRIPT_PARAMETER_TYPE::TESOBJECT, false },
	{ "Object (Optional)", SCRIPT_PARAMETER_TYPE::TESOBJECT, true },
};

static SCRIPT_PARAMETER kParams_OneInt_OneOptionalObject[] =
{
	{ "Integer", SCRIPT_PARAMETER_TYPE::INTEGER, false },
	{ "Object (Optional)", SCRIPT_PARAMETER_TYPE::TESOBJECT, true },
};

static SCRIPT_PARAMETER kParams_FormList_Integer[] =
{
	{ "Form List", SCRIPT_PARAMETER_TYPE::FORM_LIST, false },
	{ "Integer", SCRIPT_PARAMETER_TYPE::INTEGER, false }
};

static SCRIPT_PARAMETER kParams_OneQuest[] =
{
	{ "Quest", SCRIPT_PARAMETER_TYPE::QUEST, false },
};

static SCRIPT_PARAMETER kParams_OneNPC[] =
{
	{ "NPC (Optional)", SCRIPT_PARAMETER_TYPE::NPC, true },
};

static SCRIPT_PARAMETER kParams_OneOptionalObjectRef[] =
{
	{ "Reference (Optional)", SCRIPT_PARAMETER_TYPE::REFERENCE, true },
};

static SCRIPT_PARAMETER kParams_OneInt_OneOptionalObjectRef[] =
{
	{ "Flag", SCRIPT_PARAMETER_TYPE::INTEGER, false },
	{ "Reference (Optional)", SCRIPT_PARAMETER_TYPE::REFERENCE, true },
};

static SCRIPT_PARAMETER kParams_OneIndex_OneOptionalObjectRef[] =
{
	{ "Integer", SCRIPT_PARAMETER_TYPE::INTEGER, false },
	{ "Reference (Optional)", SCRIPT_PARAMETER_TYPE::REFERENCE, true },
};

static SCRIPT_PARAMETER kParams_OnePackage_OneIndex_OneOptionalObjectRef[] =
{
	{ "Package", SCRIPT_PARAMETER_TYPE::AI_PACKAGE, false },
	{ "Integer", SCRIPT_PARAMETER_TYPE::INTEGER, false },
	{ "Reference (Optional)", SCRIPT_PARAMETER_TYPE::REFERENCE, true },
};

static SCRIPT_PARAMETER kParams_OneForm_OneOptionalObjectRef[] =
{
	{ "Any Form", SCRIPT_PARAMETER_TYPE::ANY_FORM, false },
	{ "Reference (Optional)", SCRIPT_PARAMETER_TYPE::REFERENCE, true },
};

static SCRIPT_PARAMETER kParams_OneForm_OneInt[] =
{
	{ "Any Form", SCRIPT_PARAMETER_TYPE::ANY_FORM, false },
	{ "Integer", SCRIPT_PARAMETER_TYPE::INTEGER, false },
};

static SCRIPT_PARAMETER kParams_TwoForms_OneInt[] =
{
	{ "Any Form", SCRIPT_PARAMETER_TYPE::ANY_FORM, false },
	{ "Any Form", SCRIPT_PARAMETER_TYPE::ANY_FORM, false },
	{ "Integer", SCRIPT_PARAMETER_TYPE::INTEGER, false },
};

static SCRIPT_PARAMETER kParams_TwoForms_OneOptionalFloat[] =
{
	{ "Any Form", SCRIPT_PARAMETER_TYPE::ANY_FORM, false },
	{ "Any Form", SCRIPT_PARAMETER_TYPE::ANY_FORM, false },
	{ "Float (Optional)", SCRIPT_PARAMETER_TYPE::FLOAT, true },
};

static SCRIPT_PARAMETER kParams_OneForm[] =
{
	{ "Any Form", SCRIPT_PARAMETER_TYPE::ANY_FORM, false },
};

static SCRIPT_PARAMETER kParams_OneForm_OneFloat[] =
{
	{ "Any Form", SCRIPT_PARAMETER_TYPE::ANY_FORM, false },
	{ "Float", SCRIPT_PARAMETER_TYPE::FLOAT, false },
};

static SCRIPT_PARAMETER kParams_OneForm_OneOptionalForm[] =
{
	{ "Any Form", SCRIPT_PARAMETER_TYPE::ANY_FORM, false },
	{ "Any Form (Optional)", SCRIPT_PARAMETER_TYPE::ANY_FORM, true },
};

static SCRIPT_PARAMETER kParams_OneOptionalForm[] =
{
	{ "Any Form (Optional)", SCRIPT_PARAMETER_TYPE::ANY_FORM, true },
};

static SCRIPT_PARAMETER kParams_OneFaction[] =
{
	{ "Faction", SCRIPT_PARAMETER_TYPE::FACTION, false },
};

static SCRIPT_PARAMETER kParams_OneOptionalActorBase[] =
{
	{ "Actor Base (Optional)", SCRIPT_PARAMETER_TYPE::ACTOR_BASE, true },
};

static SCRIPT_PARAMETER kParams_OneInt_OneOptionalActorBase[] =
{
	{ "Integer", SCRIPT_PARAMETER_TYPE::INTEGER, false },
	{ "Actor Base (Optional)", SCRIPT_PARAMETER_TYPE::ACTOR_BASE, true },
};

static SCRIPT_PARAMETER kParams_OneRace[] =
{
	{ "Race", SCRIPT_PARAMETER_TYPE::RACE, false },
};

static SCRIPT_PARAMETER kParams_OneInt_OneForm[] =
{
	{ "Integer", SCRIPT_PARAMETER_TYPE::INTEGER, false },
	{ "Any Form", SCRIPT_PARAMETER_TYPE::ANY_FORM, false },
};

static SCRIPT_PARAMETER kParams_AnyExpr[] =
{
	{ "Any Expression", kNVSEParamType_BasicType, false },
};

static SCRIPT_PARAMETER kParams_OneString_ThreeFloats[] =
{
	{ "String", SCRIPT_PARAMETER_TYPE::STRING, false },
	{ "Float", SCRIPT_PARAMETER_TYPE::FLOAT, false },
	{ "Float", SCRIPT_PARAMETER_TYPE::FLOAT, false },
	{ "Float", SCRIPT_PARAMETER_TYPE::FLOAT, false },
};

static SCRIPT_PARAMETER kParams_FourStrings[] =
{
	{ "String", SCRIPT_PARAMETER_TYPE::STRING, false },
	{ "X (Out)", SCRIPT_PARAMETER_TYPE::STRING, false },
	{ "Y (Out)", SCRIPT_PARAMETER_TYPE::STRING, false },
	{ "Z (Out)", SCRIPT_PARAMETER_TYPE::STRING, false },
};

static SCRIPT_PARAMETER kParams_TwoRefs_TwoStrings[] =
{
	{ "Reference", SCRIPT_PARAMETER_TYPE::REFERENCE, false },
	{ "Reference", SCRIPT_PARAMETER_TYPE::REFERENCE, false },
	{ "String", SCRIPT_PARAMETER_TYPE::STRING, false },
	{ "String", SCRIPT_PARAMETER_TYPE::STRING, false },
};

static SCRIPT_PARAMETER kParams_OneString_OneOptionalObjectID[] =
{
	{ "String", SCRIPT_PARAMETER_TYPE::STRING, false },
	{ "ObjectID (Optional)", SCRIPT_PARAMETER_TYPE::OBJECT_ID, true },
};

static SCRIPT_PARAMETER kParams_OneForm_OneString[] =
{
	{ "Any Form", SCRIPT_PARAMETER_TYPE::ANY_FORM, false },
	{ "String", SCRIPT_PARAMETER_TYPE::STRING, false },
};

static SCRIPT_PARAMETER kParams_OneString_TwoOptionalInts[] =
{
	{ "String", SCRIPT_PARAMETER_TYPE::STRING, false },
	{ "Integer (Optional)", SCRIPT_PARAMETER_TYPE::INTEGER, true },
	{ "Integer (Optional)", SCRIPT_PARAMETER_TYPE::INTEGER, true },
};

static SCRIPT_PARAMETER kParams_TwoOptionalInts[] =
{
	{ "Integer (Optional)", SCRIPT_PARAMETER_TYPE::INTEGER, true },
	{ "Integer (Optional)", SCRIPT_PARAMETER_TYPE::INTEGER, true },
};

static SCRIPT_PARAMETER kParams_ThreeOptionalInts[] =
{
	{ "Integer (Optional)", SCRIPT_PARAMETER_TYPE::INTEGER, true },
	{ "Integer (Optional)", SCRIPT_PARAMETER_TYPE::INTEGER, true },
	{ "Integer (Optional)", SCRIPT_PARAMETER_TYPE::INTEGER, true },
};

static SCRIPT_PARAMETER kParams_ThreeOptionalFloats[] =
{
	{ "Float (Optional)", SCRIPT_PARAMETER_TYPE::FLOAT, true },
	{ "Float (Optional)", SCRIPT_PARAMETER_TYPE::FLOAT, true },
	{ "Float (Optional)", SCRIPT_PARAMETER_TYPE::FLOAT, true },
};

static SCRIPT_PARAMETER kParams_ar_SortEditor[] =
{
	{ "Array", kNVSEParamType_Array, false },
	{ "Descending (Optional)", kNVSEParamType_Number, true },
};

static SCRIPT_PARAMETER kParams_TwoStrings_OneOptionalString_FourOptionalInts[] =
{
	{ "String", SCRIPT_PARAMETER_TYPE::STRING, false },
	{ "String", SCRIPT_PARAMETER_TYPE::STRING, false },
	{ "String (Optional)", SCRIPT_PARAMETER_TYPE::STRING, true },
	{ "Integer (Optional)", SCRIPT_PARAMETER_TYPE::INTEGER, true },
	{ "Integer (Optional)", SCRIPT_PARAMETER_TYPE::INTEGER, true },
	{ "Integer (Optional)", SCRIPT_PARAMETER_TYPE::INTEGER, true },
	{ "Integer (Optional)", SCRIPT_PARAMETER_TYPE::INTEGER, true },
};

static SCRIPT_PARAMETER kParams_OneString_OneInt[] =
{
	{ "String", SCRIPT_PARAMETER_TYPE::STRING, false },
	{ "Integer", SCRIPT_PARAMETER_TYPE::INTEGER, false },
};

static SCRIPT_PARAMETER kParams_OneInt_OneString[] =
{
	{ "Integer", SCRIPT_PARAMETER_TYPE::INTEGER, false },
	{ "String", SCRIPT_PARAMETER_TYPE::STRING, false },
};

static SCRIPT_PARAMETER kParams_OneString_OneOptionalInt[] =
{
	{ "String", SCRIPT_PARAMETER_TYPE::STRING, false },
	{ "Integer (Optional)", SCRIPT_PARAMETER_TYPE::INTEGER, true },
};

static SCRIPT_PARAMETER kParams_OneString_ThreeOptionalInts[] =
{
	{ "String", SCRIPT_PARAMETER_TYPE::STRING, false },
	{ "Integer (Optional)", SCRIPT_PARAMETER_TYPE::INTEGER, true },
	{ "Integer (Optional)", SCRIPT_PARAMETER_TYPE::INTEGER, true },
	{ "Integer (Optional)", SCRIPT_PARAMETER_TYPE::INTEGER, true },
};

static SCRIPT_PARAMETER kParams_OneString_TwoOptionalInts_OneOptionalFloat[] =
{
	{ "String", SCRIPT_PARAMETER_TYPE::STRING, false },
	{ "Integer (Optional)", SCRIPT_PARAMETER_TYPE::INTEGER, true },
	{ "Integer (Optional)", SCRIPT_PARAMETER_TYPE::INTEGER, true },
	{ "Float (Optional)", SCRIPT_PARAMETER_TYPE::FLOAT, true },
};

static SCRIPT_PARAMETER kParams_Event_OneForm[] =
{
	{ "Set or Remove", SCRIPT_PARAMETER_TYPE::INTEGER, false },
	{ "Script", SCRIPT_PARAMETER_TYPE::ANY_FORM, false },
	{ "Flags (Optional)", SCRIPT_PARAMETER_TYPE::INTEGER, true },
	{ "Any Form (Optional)", SCRIPT_PARAMETER_TYPE::ANY_FORM, true }
};

static SCRIPT_PARAMETER kParams_Event_TwoForms[] =
{
	{ "Set or Remove", SCRIPT_PARAMETER_TYPE::INTEGER, false },
	{ "Script", SCRIPT_PARAMETER_TYPE::ANY_FORM, false },
	{ "Flags (Optional)", SCRIPT_PARAMETER_TYPE::INTEGER, true },
	{ "Any Form (Optional)", SCRIPT_PARAMETER_TYPE::ANY_FORM, true },
	{ "Any Form (Optional)", SCRIPT_PARAMETER_TYPE::ANY_FORM, true }
};

static SCRIPT_PARAMETER kParams_Event[] =
{
	{ "Set or Remove", SCRIPT_PARAMETER_TYPE::INTEGER, false },
	{ "Script", SCRIPT_PARAMETER_TYPE::ANY_FORM, false },
	{ "Flags (Optional)", SCRIPT_PARAMETER_TYPE::INTEGER, true },
};

static SCRIPT_PARAMETER kParams_Event_OptionalFlag[] =
{
	{ "Set or Remove", SCRIPT_PARAMETER_TYPE::INTEGER, false },
	{ "Script", SCRIPT_PARAMETER_TYPE::ANY_FORM, false },
	{ "Flags (Optional)", SCRIPT_PARAMETER_TYPE::INTEGER, true },
	{ "optionalFlags (Optional)", SCRIPT_PARAMETER_TYPE::INTEGER, true },
};

static SCRIPT_PARAMETER kParams_Event_OneForm_OneInt[] =
{
	{ "Set or Remove", SCRIPT_PARAMETER_TYPE::INTEGER, false },
	{ "Script", SCRIPT_PARAMETER_TYPE::ANY_FORM, false },
	{ "Flags (Optional)", SCRIPT_PARAMETER_TYPE::INTEGER, true },
	{ "Any Form (Optional)", SCRIPT_PARAMETER_TYPE::ANY_FORM, true },
	{ "Integer (Optional)", SCRIPT_PARAMETER_TYPE::INTEGER, true },
};

static SCRIPT_PARAMETER kParams_Event_OneInt[] =
{
	{ "Set or Remove", SCRIPT_PARAMETER_TYPE::INTEGER, false },
	{ "Script", SCRIPT_PARAMETER_TYPE::ANY_FORM, false },
	{ "Flags (Optional)", SCRIPT_PARAMETER_TYPE::INTEGER, true },
	{ "Integer (Optional)", SCRIPT_PARAMETER_TYPE::INTEGER, true },
};

static SCRIPT_PARAMETER kParams_OneString_OneForm_OneOptionalInt[] =
{
	{ "String", SCRIPT_PARAMETER_TYPE::STRING, false },
	{ "Any Form", SCRIPT_PARAMETER_TYPE::ANY_FORM, false },
	{ "Integer (Optional)", SCRIPT_PARAMETER_TYPE::INTEGER, true },
};

static SCRIPT_PARAMETER kParams_OneForm_TwoInts_OneForm[] =
{
	{ "Any Form", SCRIPT_PARAMETER_TYPE::ANY_FORM, false },
	{ "Integer", SCRIPT_PARAMETER_TYPE::INTEGER, false },
	{ "Integer", SCRIPT_PARAMETER_TYPE::INTEGER, false },
	{ "Any Form", SCRIPT_PARAMETER_TYPE::ANY_FORM, false }
};

static SCRIPT_PARAMETER kParams_OneForm_OneInt_OneFloat[] =
{
	{ "Any Form", SCRIPT_PARAMETER_TYPE::ANY_FORM, false },
	{ "Integer", SCRIPT_PARAMETER_TYPE::INTEGER, false },
	{ "Float", SCRIPT_PARAMETER_TYPE::FLOAT, false }
};

static SCRIPT_PARAMETER kParams_OneActorBase[] =
{
	{ "Actor Base", SCRIPT_PARAMETER_TYPE::ACTOR_BASE, false },
};

static SCRIPT_PARAMETER kParams_OneWorldSpace[] =
{
	{ "World Space", SCRIPT_PARAMETER_TYPE::WORLDSPACE, false },
};

static SCRIPT_PARAMETER kParams_OneForm_OneInt_OneForm[] =
{
	{ "Any Form", SCRIPT_PARAMETER_TYPE::ANY_FORM, false },
	{ "Integer", SCRIPT_PARAMETER_TYPE::INTEGER, false },
	{ "Any Form", SCRIPT_PARAMETER_TYPE::ANY_FORM, false }
};

static SCRIPT_PARAMETER kParams_OneInt_OneForm_OneInt[] =
{
	{ "Integer", SCRIPT_PARAMETER_TYPE::INTEGER, false },
	{ "Any Form", SCRIPT_PARAMETER_TYPE::ANY_FORM, false },
	{ "Integer", SCRIPT_PARAMETER_TYPE::INTEGER, false }
};

static SCRIPT_PARAMETER kParams_OneForm_OneInt_OneForm_OneInt[] =
{
	{ "Any Form", SCRIPT_PARAMETER_TYPE::ANY_FORM, false },
	{ "Integer", SCRIPT_PARAMETER_TYPE::INTEGER, false },
	{ "Any Form", SCRIPT_PARAMETER_TYPE::ANY_FORM, false },
	{ "Integer", SCRIPT_PARAMETER_TYPE::INTEGER, false }
};

static SCRIPT_PARAMETER kParams_OneForm_OneInt_OneString[] =
{
	{ "Any Form", SCRIPT_PARAMETER_TYPE::ANY_FORM, false },
	{ "Integer", SCRIPT_PARAMETER_TYPE::INTEGER, false },
	{ "String", SCRIPT_PARAMETER_TYPE::STRING, false }
};

static SCRIPT_PARAMETER kParams_OneOptionalFloat[] =
{
	{ "Float (Optional)", SCRIPT_PARAMETER_TYPE::FLOAT, true },
};

static SCRIPT_PARAMETER kParams_ThreeFloats[] =
{
	{ "Float", SCRIPT_PARAMETER_TYPE::FLOAT, false },
	{ "Float", SCRIPT_PARAMETER_TYPE::FLOAT, false },
	{ "Float", SCRIPT_PARAMETER_TYPE::FLOAT, false },
};

static SCRIPT_PARAMETER kParams_ThreeFloats_OneInt_OneOptionalFloat[] =
{
	{ "Float", SCRIPT_PARAMETER_TYPE::FLOAT, false },
	{ "Float", SCRIPT_PARAMETER_TYPE::FLOAT, false },
	{ "Float", SCRIPT_PARAMETER_TYPE::FLOAT, false },
	{ "Integer", SCRIPT_PARAMETER_TYPE::INTEGER, false },
	{ "Float (Optional)", SCRIPT_PARAMETER_TYPE::FLOAT, true }
};

static SCRIPT_PARAMETER kParams_FiveFloats[] =
{
	{ "Float", SCRIPT_PARAMETER_TYPE::FLOAT, false },
	{ "Float", SCRIPT_PARAMETER_TYPE::FLOAT, false },
	{ "Float", SCRIPT_PARAMETER_TYPE::FLOAT, false },
	{ "Float", SCRIPT_PARAMETER_TYPE::FLOAT, false },
	{ "Float", SCRIPT_PARAMETER_TYPE::FLOAT, false },
};

static SCRIPT_PARAMETER kParams_OneInt_OneFloat[] =
{
	{ "Integer", SCRIPT_PARAMETER_TYPE::INTEGER, false },
	{ "Float", SCRIPT_PARAMETER_TYPE::FLOAT, false },
};

static SCRIPT_PARAMETER kParams_OneForm_OneOptionalInt[] =
{
	{ "Any Form", SCRIPT_PARAMETER_TYPE::ANY_FORM, false },
	{ "Integer (Optional)", SCRIPT_PARAMETER_TYPE::INTEGER, true },
};

static SCRIPT_PARAMETER kParams_OneForm_OneInt_OneOptionalInt[] =
{
	{ "Any Form", SCRIPT_PARAMETER_TYPE::ANY_FORM, false },
	{ "Integer", SCRIPT_PARAMETER_TYPE::INTEGER, false },
	{ "Integer (Optional)", SCRIPT_PARAMETER_TYPE::INTEGER, true },
};

static SCRIPT_PARAMETER kParams_OneObjectID_OneOptionalInt[] =
{
	{ "Item", SCRIPT_PARAMETER_TYPE::OBJECT_ID, false },
	{ "Integer (Optional)", SCRIPT_PARAMETER_TYPE::INTEGER, true },
};

static SCRIPT_PARAMETER kParams_OneForm_TwoInts[] =
{
	{ "Any Form", SCRIPT_PARAMETER_TYPE::ANY_FORM, false },
	{ "Integer", SCRIPT_PARAMETER_TYPE::INTEGER, false },
	{ "Integer", SCRIPT_PARAMETER_TYPE::INTEGER, false },
};

static SCRIPT_PARAMETER kParams_OneForm_TwoInts_OneString[] =
{
	{ "Any Form", SCRIPT_PARAMETER_TYPE::ANY_FORM, false },
	{ "Integer", SCRIPT_PARAMETER_TYPE::INTEGER, false },
	{ "Integer", SCRIPT_PARAMETER_TYPE::INTEGER, false },
	{ "String", SCRIPT_PARAMETER_TYPE::STRING, false },
};

static SCRIPT_PARAMETER kParams_SixFloats[] =
{
	{ "Float", SCRIPT_PARAMETER_TYPE::FLOAT, false },
	{ "Float", SCRIPT_PARAMETER_TYPE::FLOAT, false },
	{ "Float", SCRIPT_PARAMETER_TYPE::FLOAT, false },
	{ "Float", SCRIPT_PARAMETER_TYPE::FLOAT, false },
	{ "Float", SCRIPT_PARAMETER_TYPE::FLOAT, false },
	{ "Float", SCRIPT_PARAMETER_TYPE::FLOAT, false },
};

static SCRIPT_PARAMETER kParams_OneForm_ThreeInts[] =
{
	{ "Any Form", SCRIPT_PARAMETER_TYPE::ANY_FORM, false },
	{ "Integer", SCRIPT_PARAMETER_TYPE::INTEGER, false },
	{ "Integer", SCRIPT_PARAMETER_TYPE::INTEGER, false },
	{ "Integer", SCRIPT_PARAMETER_TYPE::INTEGER, false },
};

static SCRIPT_PARAMETER kParams_OneForm_FourInts[] =
{
	{ "Any Form", SCRIPT_PARAMETER_TYPE::ANY_FORM, false },
	{ "Integer", SCRIPT_PARAMETER_TYPE::INTEGER, false },
	{ "Integer", SCRIPT_PARAMETER_TYPE::INTEGER, false },
	{ "Integer", SCRIPT_PARAMETER_TYPE::INTEGER, false },
	{ "Integer", SCRIPT_PARAMETER_TYPE::INTEGER, false },
};

static SCRIPT_PARAMETER kParams_OneForm_FourInts_TwoOptionalForms_OneOptionalInt[] =
{
	{ "Any Form", SCRIPT_PARAMETER_TYPE::ANY_FORM, false },
	{ "Integer", SCRIPT_PARAMETER_TYPE::INTEGER, false },
	{ "Integer", SCRIPT_PARAMETER_TYPE::INTEGER, false },
	{ "Integer", SCRIPT_PARAMETER_TYPE::INTEGER, false },
	{ "Integer", SCRIPT_PARAMETER_TYPE::INTEGER, false },
	{ "Any Form (Optional)", SCRIPT_PARAMETER_TYPE::ANY_FORM, true },
	{ "Any Form (Optional)", SCRIPT_PARAMETER_TYPE::ANY_FORM, true },
	{ "Integer (Optional)", SCRIPT_PARAMETER_TYPE::INTEGER, true },
};

static SCRIPT_PARAMETER kParams_TwoForms[] =
{
	{ "Any Form", SCRIPT_PARAMETER_TYPE::ANY_FORM, false },
	{ "Any Form", SCRIPT_PARAMETER_TYPE::ANY_FORM, false },
};

static SCRIPT_PARAMETER kParams_OneString_OneInt_OneForm[] =
{
	{ "String", SCRIPT_PARAMETER_TYPE::STRING, false },
	{ "Integer", SCRIPT_PARAMETER_TYPE::INTEGER, false },
	{ "Any Form", SCRIPT_PARAMETER_TYPE::ANY_FORM, false },
};

static SCRIPT_PARAMETER kParams_OneIMOD[] =
{
	{ "Imagespace Modifier", SCRIPT_PARAMETER_TYPE::IMAGESPACE_MODIFIER, false },
};

static SCRIPT_PARAMETER kParams_OneIMOD_OneInt[] =
{
	{ "Imagespace Modifier", SCRIPT_PARAMETER_TYPE::IMAGESPACE_MODIFIER, false },
	{ "Integer", SCRIPT_PARAMETER_TYPE::INTEGER, false },
};

static SCRIPT_PARAMETER kParams_TwoStrings_OneInt[] =
{
	{ "String", SCRIPT_PARAMETER_TYPE::STRING, false },
	{ "String", SCRIPT_PARAMETER_TYPE::STRING, false },
	{ "Integer", SCRIPT_PARAMETER_TYPE::INTEGER, false },
};

static SCRIPT_PARAMETER kParams_OneActorValue_OneOptionalInt[] =
{
	{ "Actor Value", SCRIPT_PARAMETER_TYPE::ACTOR_VALUE, false },
	{ "Integer (Optional)", SCRIPT_PARAMETER_TYPE::INTEGER, true },
};

static SCRIPT_PARAMETER kParams_BMP[] =
{
	{ "Filename", SCRIPT_PARAMETER_TYPE::STRING, false },
	{ "R (Out)", SCRIPT_PARAMETER_TYPE::STRING, false },
	{ "G (Out)", SCRIPT_PARAMETER_TYPE::STRING, false },
	{ "B (Out)", SCRIPT_PARAMETER_TYPE::STRING, false },
	{ "Integer", SCRIPT_PARAMETER_TYPE::INTEGER, false },
	{ "Integer", SCRIPT_PARAMETER_TYPE::INTEGER, false },
};

static SCRIPT_PARAMETER kParams_OneForm_OneWeatherID_OneInt_OneOptionalGlobal[] =
{
	{ "Any Form", SCRIPT_PARAMETER_TYPE::ANY_FORM, false },
	{ "Weather", SCRIPT_PARAMETER_TYPE::WEATHER, false },
	{ "Integer", SCRIPT_PARAMETER_TYPE::INTEGER, false },
	{ "Global (Optional)", SCRIPT_PARAMETER_TYPE::GLOBAL, true }
};

static SCRIPT_PARAMETER kParams_ThreeStrings_OneInt[] =
{
	{ "String", SCRIPT_PARAMETER_TYPE::STRING, false },
	{ "String", SCRIPT_PARAMETER_TYPE::STRING, false },
	{ "String", SCRIPT_PARAMETER_TYPE::STRING, false },
	{ "Integer", SCRIPT_PARAMETER_TYPE::INTEGER, false }
};

static SCRIPT_PARAMETER kParams_OneRef_OneInt[] =
{
	{ "Reference", SCRIPT_PARAMETER_TYPE::REFERENCE, false },
	{ "Integer (Optional)", SCRIPT_PARAMETER_TYPE::INTEGER, true },
};

static SCRIPT_PARAMETER kParams_OneRef_OneForm_OneInt[] =
{
	{ "Reference", SCRIPT_PARAMETER_TYPE::REFERENCE, false },
	{ "Any Form", SCRIPT_PARAMETER_TYPE::ANY_FORM, false },
	{ "Integer (Optional)", SCRIPT_PARAMETER_TYPE::INTEGER, true },
};

static SCRIPT_PARAMETER kParams_OneRef[] =
{
	{ "Reference", SCRIPT_PARAMETER_TYPE::REFERENCE, false }
};

static SCRIPT_PARAMETER kParams_OneActorBase_TwoInts_OneFloat[] =
{
	{ "Actor Base", SCRIPT_PARAMETER_TYPE::ACTOR_BASE, false },
	{ "Property Type", SCRIPT_PARAMETER_TYPE::INTEGER, false },
	{ "Property", SCRIPT_PARAMETER_TYPE::INTEGER, false },
	{ "value", SCRIPT_PARAMETER_TYPE::FLOAT, false },
};

static SCRIPT_PARAMETER kParams_OneActorBase_TwoInts[] =
{
	{ "Actor Base", SCRIPT_PARAMETER_TYPE::ACTOR_BASE, false },
	{ "Property Type", SCRIPT_PARAMETER_TYPE::INTEGER, false },
	{ "Property", SCRIPT_PARAMETER_TYPE::INTEGER, false },
};

static SCRIPT_PARAMETER kParams_SixScriptVars[] =
{
	{ "Script Var", SCRIPT_PARAMETER_TYPE::SCRIPT_VARIABLE, false },
	{ "Script Var", SCRIPT_PARAMETER_TYPE::SCRIPT_VARIABLE, false },
	{ "Script Var", SCRIPT_PARAMETER_TYPE::SCRIPT_VARIABLE, false },
	{ "Script Var", SCRIPT_PARAMETER_TYPE::SCRIPT_VARIABLE, false },
	{ "Script Var", SCRIPT_PARAMETER_TYPE::SCRIPT_VARIABLE, false },
	{ "Script Var", SCRIPT_PARAMETER_TYPE::SCRIPT_VARIABLE, false },
};

static SCRIPT_PARAMETER kParams_TwoScriptVars_OneOptionalScriptVar[] =
{
	{ "Script Var", SCRIPT_PARAMETER_TYPE::SCRIPT_VARIABLE, false },
	{ "Script Var", SCRIPT_PARAMETER_TYPE::SCRIPT_VARIABLE, false },
	{ "Script Var", SCRIPT_PARAMETER_TYPE::SCRIPT_VARIABLE, true },
};

static SCRIPT_PARAMETER kParams_OneForm_OneInt_OneOptionalForm[] =
{
	{ "Any Form", SCRIPT_PARAMETER_TYPE::ANY_FORM, false },
	{ "Integer", SCRIPT_PARAMETER_TYPE::INTEGER, false },
	{ "Any Form (Optional)", SCRIPT_PARAMETER_TYPE::ANY_FORM, true }
};

static SCRIPT_PARAMETER kParams_ThreeInts[] =
{
	{ "Integer", SCRIPT_PARAMETER_TYPE::INTEGER, false },
	{ "Integer", SCRIPT_PARAMETER_TYPE::INTEGER, false },
	{ "Integer", SCRIPT_PARAMETER_TYPE::INTEGER, false }
};

static SCRIPT_PARAMETER kParams_OneDialogRes_OneTopic_OneInt_OneOptionalInt[] =
{
	{ "Dialog Response", SCRIPT_PARAMETER_TYPE::ANY_FORM, false },
	{ "Dialog Topic", SCRIPT_PARAMETER_TYPE::TOPIC, false },
	{ "Integer", SCRIPT_PARAMETER_TYPE::INTEGER, false },
	{ "Integer (Optional)", SCRIPT_PARAMETER_TYPE::INTEGER, true }
};

static SCRIPT_PARAMETER kParams_OneInt_OneOptionalForm[] =
{
	{ "Integer", SCRIPT_PARAMETER_TYPE::INTEGER, false },
	{ "Any Form (Optional)", SCRIPT_PARAMETER_TYPE::ANY_FORM, true },
};

static SCRIPT_PARAMETER kSplatterParams[] = {
	{ "Count", SCRIPT_PARAMETER_TYPE::INTEGER, false },
	{ "Duration", SCRIPT_PARAMETER_TYPE::FLOAT, false },
	{ "Size mult", SCRIPT_PARAMETER_TYPE::FLOAT, false },
	{ "Opacity mult", SCRIPT_PARAMETER_TYPE::FLOAT, false },
	{ "Alpha Texture", SCRIPT_PARAMETER_TYPE::STRING, false },
	{ "Color Texture", SCRIPT_PARAMETER_TYPE::STRING, false },
	{ "Flare Texture", SCRIPT_PARAMETER_TYPE::STRING, false },
	{ "No fade (Optional)", SCRIPT_PARAMETER_TYPE::INTEGER, true }
};

static SCRIPT_PARAMETER kTransformParams[] =
{
	{ "Block name", SCRIPT_PARAMETER_TYPE::STRING, false },
	{ "X", SCRIPT_PARAMETER_TYPE::FLOAT, false },
	{ "Y", SCRIPT_PARAMETER_TYPE::FLOAT, false },
	{ "Z", SCRIPT_PARAMETER_TYPE::FLOAT, false },
	{ "W", SCRIPT_PARAMETER_TYPE::FLOAT, false },
	{ "Is Rotation", kNVSEParamType_Boolean, false },
	{ "World Data", kNVSEParamType_Boolean, false },
	{ "Update", kNVSEParamType_Boolean, false },
};

static SCRIPT_PARAMETER kParams_OneForm_OneInt_OneOptionalInt_OneOptionalForm[] =
{
	{ "Any Form", SCRIPT_PARAMETER_TYPE::ANY_FORM, false },
	{ "Integer", SCRIPT_PARAMETER_TYPE::INTEGER, false },
	{ "Integer (Optional)", SCRIPT_PARAMETER_TYPE::INTEGER, true },
	{ "Any Form (Optional)", SCRIPT_PARAMETER_TYPE::ANY_FORM, true },
};

static SCRIPT_PARAMETER kParams_OneActorRef_OneInt[] =
{
	{ "Actor", SCRIPT_PARAMETER_TYPE::ACTOR, false },
	{ "Integer", SCRIPT_PARAMETER_TYPE::INTEGER, false },
};

static SCRIPT_PARAMETER kParams_OneFloat_OneOptionalForm[] =
{
	{ "Float", SCRIPT_PARAMETER_TYPE::FLOAT, false },
	{ "Any Form (Optional)", SCRIPT_PARAMETER_TYPE::ANY_FORM, true }
};

static SCRIPT_PARAMETER kParams_EjectCasing[] =
{
	{ "Target Node (Optional)", SCRIPT_PARAMETER_TYPE::STRING, true },
	{ "Custom Casing Path (Optional)", SCRIPT_PARAMETER_TYPE::STRING, true },
};

static SCRIPT_PARAMETER kParams_OneCasino[] =
{
	{ "Casino", SCRIPT_PARAMETER_TYPE::CASINO, true },
};

static SCRIPT_PARAMETER kParams_OneCasinoOneInt[] =
{
	{ "Casino", SCRIPT_PARAMETER_TYPE::CASINO, true },
	{ "Integer (Optional)", SCRIPT_PARAMETER_TYPE::INTEGER, true },
};

static SCRIPT_PARAMETER kParams_OneCasinoOneIntOneString[] =
{
	{ "Casino", SCRIPT_PARAMETER_TYPE::CASINO, true },
	{ "Integer (Optional)", SCRIPT_PARAMETER_TYPE::INTEGER, true },
	{ "String (Optional)", SCRIPT_PARAMETER_TYPE::STRING, true },
};

static SCRIPT_PARAMETER kParams_OneCasinoOneForm[] =
{
	{ "Casino", SCRIPT_PARAMETER_TYPE::CASINO, true },
	{ "Any Form (Optional)", SCRIPT_PARAMETER_TYPE::ANY_FORM, true },
};

static SCRIPT_PARAMETER kParams_OneCell[] =
{
	{ "Cell", SCRIPT_PARAMETER_TYPE::CELL, false },
};

static SCRIPT_PARAMETER kParams_OneCell_OneOptionalForm[] =
{
	{ "Cell", SCRIPT_PARAMETER_TYPE::CELL, false },
	{ "Any Form (Optional)", SCRIPT_PARAMETER_TYPE::ANY_FORM, true }
};

static SCRIPT_PARAMETER kParams_OneBoolThreeFloats[] =
{
	{ "Enable", SCRIPT_PARAMETER_TYPE::INTEGER, false },
	{ "X", SCRIPT_PARAMETER_TYPE::FLOAT, false },
	{ "Y", SCRIPT_PARAMETER_TYPE::FLOAT, false },
	{ "Z", SCRIPT_PARAMETER_TYPE::FLOAT, false },
};

static SCRIPT_PARAMETER kParams_OneBoolOneIntOneFloat[] =
{
	{ "Enable", SCRIPT_PARAMETER_TYPE::INTEGER, false },
	{ "Axis/Mode", SCRIPT_PARAMETER_TYPE::INTEGER, false },
	{ "Angle", SCRIPT_PARAMETER_TYPE::FLOAT, false },
	{ "Ref To Track (Optional)", SCRIPT_PARAMETER_TYPE::REFERENCE, true },
};

static SCRIPT_PARAMETER kParams_OneRefOneOptionalFloatOneOptionalInt[] =
{
	{ "Target Reference", SCRIPT_PARAMETER_TYPE::REFERENCE, false },
	{ "Target Radius (Optional)", SCRIPT_PARAMETER_TYPE::FLOAT, true },
	{ "Face Target (Optional)", SCRIPT_PARAMETER_TYPE::INTEGER, true },
};

static SCRIPT_PARAMETER kParams_IsNiSequenceActive[] =
{
	{ "Sequence Name", SCRIPT_PARAMETER_TYPE::STRING, false },
	{ "Block Name (Optional)", SCRIPT_PARAMETER_TYPE::STRING, true },
	{ "First Person (Optional)", SCRIPT_PARAMETER_TYPE::INTEGER, true },
};

static SCRIPT_PARAMETER kParams_StopNiSequence[] =
{
	{ "Sequence Name", SCRIPT_PARAMETER_TYPE::STRING, false },
	{ "Ease Out Time (Optional)", SCRIPT_PARAMETER_TYPE::FLOAT, true },
	{ "Block Name (Optional)", SCRIPT_PARAMETER_TYPE::STRING, true },
	{ "First Person (Optional)", SCRIPT_PARAMETER_TYPE::INTEGER, true },
};

static SCRIPT_PARAMETER kParams_GetTopicInfo[] =
{
	{ "Any Form", SCRIPT_PARAMETER_TYPE::ANY_FORM, false },
	{ "Quest (Optional)", SCRIPT_PARAMETER_TYPE::QUEST, true },
};

static SCRIPT_PARAMETER kParams_ThreeFloatsTwoOptionalFloats[] =
{
	{ "X", SCRIPT_PARAMETER_TYPE::FLOAT, false },
	{ "Y", SCRIPT_PARAMETER_TYPE::FLOAT, false },
	{ "Z", SCRIPT_PARAMETER_TYPE::FLOAT, false },
	{ "Target Radius (Optional)", SCRIPT_PARAMETER_TYPE::FLOAT, true },
	{ "Target Angle (Optional)", SCRIPT_PARAMETER_TYPE::FLOAT, true },
};

static SCRIPT_PARAMETER kParams_SetPropertyValue[] =
{
	{ "Property Name", SCRIPT_PARAMETER_TYPE::STRING, false },
	{ "Item", SCRIPT_PARAMETER_TYPE::INTEGER, false },
	{ "Value", SCRIPT_PARAMETER_TYPE::INTEGER, false },
	{ "First Person (Optional)", SCRIPT_PARAMETER_TYPE::INTEGER, true },
};

static SCRIPT_PARAMETER kParams_GetPropertyValue[] =
{
	{ "Property Name", SCRIPT_PARAMETER_TYPE::STRING, false },
	{ "Item", SCRIPT_PARAMETER_TYPE::INTEGER, false },
	{ "First Person (Optional)", SCRIPT_PARAMETER_TYPE::INTEGER, true },
};

static SCRIPT_PARAMETER kParams_SetNiLightValue[] =
{
	{ "Property Name", SCRIPT_PARAMETER_TYPE::STRING, false },
	{ "Item", SCRIPT_PARAMETER_TYPE::INTEGER, false },
	{ "Value", SCRIPT_PARAMETER_TYPE::FLOAT, false },
	{ "First Person (Optional)", SCRIPT_PARAMETER_TYPE::INTEGER, true },
};

static SCRIPT_PARAMETER kParams_SetNiLightColor[] =
{
	{ "Property Name", SCRIPT_PARAMETER_TYPE::STRING, false },
	{ "Item", SCRIPT_PARAMETER_TYPE::INTEGER, false },
	{ "Red", SCRIPT_PARAMETER_TYPE::FLOAT, false },
	{ "Green", SCRIPT_PARAMETER_TYPE::FLOAT, false },
	{ "Blue", SCRIPT_PARAMETER_TYPE::FLOAT, false },
	{ "First Person (Optional)", SCRIPT_PARAMETER_TYPE::INTEGER, true },
};

static SCRIPT_PARAMETER kParams_GetNiLightColor[] =
{
	{ "Property Name", SCRIPT_PARAMETER_TYPE::STRING, false },
	{ "Item", SCRIPT_PARAMETER_TYPE::INTEGER, false },
	{ "Red", SCRIPT_PARAMETER_TYPE::SCRIPT_VARIABLE, false },
	{ "Green", SCRIPT_PARAMETER_TYPE::SCRIPT_VARIABLE, false },
	{ "Blue", SCRIPT_PARAMETER_TYPE::SCRIPT_VARIABLE, false },
	{ "First Person (Optional)", SCRIPT_PARAMETER_TYPE::INTEGER, true },
};

static SCRIPT_PARAMETER kParams_SetSwitchNodeIndex[] =
{
	{ "Block Name", SCRIPT_PARAMETER_TYPE::STRING, false },
	{ "Integer", SCRIPT_PARAMETER_TYPE::INTEGER, false },
	{ "First Person (Optional)", SCRIPT_PARAMETER_TYPE::INTEGER, true },
};

static SCRIPT_PARAMETER kParams_GetSwitchNodeIndex[] =
{
	{ "Block Name", SCRIPT_PARAMETER_TYPE::STRING, false },
	{ "First Person (Optional)", SCRIPT_PARAMETER_TYPE::INTEGER, true },
};

static SCRIPT_PARAMETER kParams_ScenegraphUpdate[] =
{
	{ "Type", SCRIPT_PARAMETER_TYPE::INTEGER, false },
	{ "Time (Optional)", SCRIPT_PARAMETER_TYPE::FLOAT, true },
	{ "Update Controllers (Optional)", SCRIPT_PARAMETER_TYPE::INTEGER, true },
	{ "Block Name (Optional)", SCRIPT_PARAMETER_TYPE::STRING, true },
	{ "First Person (Optional)", SCRIPT_PARAMETER_TYPE::INTEGER, true }
};

static SCRIPT_PARAMETER kParams_GetNiBound[] =
{
	{ "Block Name (Optional)", SCRIPT_PARAMETER_TYPE::STRING, true },
	{ "First Person (Optional)", SCRIPT_PARAMETER_TYPE::INTEGER, true },
};

static SCRIPT_PARAMETER kParams_ProjectionArgsLegacy[] =
{
	{ "X (Out)", SCRIPT_PARAMETER_TYPE::STRING, false },
	{ "Y (Out)", SCRIPT_PARAMETER_TYPE::STRING, false },
	{ "Z (Out)", SCRIPT_PARAMETER_TYPE::STRING, false },
	{ "Float", SCRIPT_PARAMETER_TYPE::FLOAT, false },
	{ "Float", SCRIPT_PARAMETER_TYPE::FLOAT, false },
	{ "Float", SCRIPT_PARAMETER_TYPE::FLOAT, false },
	{ "Handle Mode", SCRIPT_PARAMETER_TYPE::INTEGER, false },
	{ "Reference (Optional)", SCRIPT_PARAMETER_TYPE::REFERENCE, true }
};

static SCRIPT_PARAMETER kParams_ProjectionArgs[] =
{
	{ "X (Out)", SCRIPT_PARAMETER_TYPE::SCRIPT_VARIABLE, false },
	{ "Y (Out)", SCRIPT_PARAMETER_TYPE::SCRIPT_VARIABLE, false },
	{ "Z (Out)", SCRIPT_PARAMETER_TYPE::SCRIPT_VARIABLE, false },
	{ "Float", SCRIPT_PARAMETER_TYPE::FLOAT, false },
	{ "Float", SCRIPT_PARAMETER_TYPE::FLOAT, false },
	{ "Float", SCRIPT_PARAMETER_TYPE::FLOAT, false },
	{ "Handle Mode", SCRIPT_PARAMETER_TYPE::INTEGER, false },
	{ "Reference (Optional)", SCRIPT_PARAMETER_TYPE::REFERENCE, true }
};

static SCRIPT_PARAMETER kParams_CallPerRef[] =
{
	{ "Script", SCRIPT_PARAMETER_TYPE::ANY_FORM, false },
	{ "Type Filter (Optional)", SCRIPT_PARAMETER_TYPE::INTEGER, true },
	{ "Distance Filter (Optional)", SCRIPT_PARAMETER_TYPE::FLOAT, true },
	{ "Angle Filter (Optional)", SCRIPT_PARAMETER_TYPE::FLOAT, true },
	{ "Cell (Optional)", SCRIPT_PARAMETER_TYPE::ANY_FORM, true }
};

static SCRIPT_PARAMETER kParams_CallPerRefEx[] =
{
	{ "Script", kNVSEParamType_Form, false },
	{ "Type Filter Array", kNVSEParamType_Array, false },
	{ "Distance Filter (Optional)", kNVSEParamType_Number, true },
	{ "Angle Filter (Optional)", kNVSEParamType_Number, true },
	{ "Cell (Optional)", kNVSEParamType_Form, true }
};

static SCRIPT_PARAMETER kParams_CallPerMobileObject[] =
{
	{ "Script", SCRIPT_PARAMETER_TYPE::ANY_FORM, false },
	{ "Process Level", SCRIPT_PARAMETER_TYPE::INTEGER, false },
	{ "Type Filter (Optional)", SCRIPT_PARAMETER_TYPE::INTEGER, true },
};

static SCRIPT_PARAMETER kParams_CallPerMobileObjectEx[] =
{
	{ "Script", kNVSEParamType_Form, false },
	{ "Process Level", kNVSEParamType_Number, false },
	{ "Type Filter Array", kNVSEParamType_Array, false },
};

static SCRIPT_PARAMETER kParams_OneArray[] =
{
	{ "Array", kNVSEParamType_Array, false }
};

static SCRIPT_PARAMETER kParams_SetNiPSysModifierValue[] =
{
	{ "Block Name", SCRIPT_PARAMETER_TYPE::STRING, false },
	{ "Item", SCRIPT_PARAMETER_TYPE::INTEGER, false },
	{ "Value", SCRIPT_PARAMETER_TYPE::FLOAT, false },
	{ "First Person (Optional)", SCRIPT_PARAMETER_TYPE::INTEGER, true },
};

static SCRIPT_PARAMETER kParams_GetNiPSysModifierValue[] =
{
	{ "Block Name", SCRIPT_PARAMETER_TYPE::STRING, false },
	{ "Item", SCRIPT_PARAMETER_TYPE::INTEGER, false },
	{ "First Person (Optional)", SCRIPT_PARAMETER_TYPE::INTEGER, true },
};

static SCRIPT_PARAMETER kParams_SetParticleEmitterSpawnRate[] =
{
	{ "Block Name", SCRIPT_PARAMETER_TYPE::STRING, false },
	{ "Value", SCRIPT_PARAMETER_TYPE::FLOAT, false },
	{ "First Person (Optional)", SCRIPT_PARAMETER_TYPE::INTEGER, true },
};

static SCRIPT_PARAMETER kParams_RemapLand[] =
{
	{ "Target Land FormID", SCRIPT_PARAMETER_TYPE::INTEGER, false },
	{ "Source World Space", SCRIPT_PARAMETER_TYPE::WORLDSPACE, true },
	{ "Source Cell X (Optional)", SCRIPT_PARAMETER_TYPE::INTEGER, true },
	{ "Source Cell Y (Optional)", SCRIPT_PARAMETER_TYPE::INTEGER, true },
};

static SCRIPT_PARAMETER kParams_ApplyModelTextureSwap[] =
{
	{ "Base Form", SCRIPT_PARAMETER_TYPE::TESOBJECT, false },
	{ "Block Name (Optional)", SCRIPT_PARAMETER_TYPE::STRING, true },
	{ "Reference (Optional)", SCRIPT_PARAMETER_TYPE::REFERENCE, true },
	{ "First Person (Optional)", SCRIPT_PARAMETER_TYPE::INTEGER, true },
};