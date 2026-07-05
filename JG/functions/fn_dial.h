#pragma once
#include "fn_common.h"
// Functions that operate on dialog
DEFINE_COMMAND_PLUGIN(DialogResponseAddRelatedTopic, , false, kParams_OneDialogRes_OneTopic_OneInt_OneOptionalInt);
DEFINE_COMMAND_PLUGIN(DialogResponseRelatedGetAll, , false, kParams_OneForm_OneInt);
DEFINE_COMMAND_PLUGIN(SetDialogResponseOverrideValues, , false, kParams_OneForm_FourInts_TwoOptionalForms_OneOptionalInt);
DEFINE_CMD_COND_PLUGIN(GetSaidOnce, , false, kParams_OneForm);
DEFINE_COMMAND_PLUGIN(SetSaidOnce, , false, kParams_OneForm_TwoInts);
DEFINE_COMMAND_PLUGIN(GetTopicInfo, , false, kParams_GetTopicInfo);
DEFINE_COMMAND_PLUGIN(GetParentTopic, , false, kParams_OneForm);






