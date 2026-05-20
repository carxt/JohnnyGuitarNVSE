#pragma once
#include "fn_common.h"

#include "Bethesda/BSUtilities.hpp"
#include "Bethesda/AILinearTaskThreadManager.hpp"
#include <GameObjects.h>

DEFINE_COMMAND_PLUGIN(SetAlphaPropertyValue, , true, kParams_SetPropertyValue);
DEFINE_COMMAND_PLUGIN(GetAlphaPropertyValue, , true, kParams_GetPropertyValue);
DEFINE_COMMAND_PLUGIN(SetStencilPropertyValue, , true, kParams_SetPropertyValue);
DEFINE_COMMAND_PLUGIN(GetStencilPropertyValue, , true, kParams_GetPropertyValue);
DEFINE_COMMAND_PLUGIN(SetSwitchNodeIndex, , true, kParams_SetSwitchNodeIndex);
DEFINE_COMMAND_PLUGIN(GetSwitchNodeIndex, , true, kParams_GetSwitchNodeIndex);
DEFINE_COMMAND_PLUGIN(SetNiLODLevel, , false, kParams_OneInt);
DEFINE_COMMAND_PLUGIN(GetNiLODLevel, , false, nullptr);
DEFINE_COMMAND_PLUGIN(UpdateScenegraph, , true, kParams_ScenegraphUpdate);
DEFINE_COMMAND_PLUGIN(GetNiBound, , true, kParams_GetNiBound);
DEFINE_COMMAND_PLUGIN(IsNiSequenceActive, , true, kParams_IsNiSequenceActive);
DEFINE_COMMAND_PLUGIN(SetNiPSysModifierValue, , true, kParams_SetNiPSysModifierValue);
DEFINE_COMMAND_PLUGIN(GetNiPSysModifierValue, , true, kParams_GetNiPSysModifierValue);

namespace {
	
	template<typename T>
	inline bool InRange(volatile T value) {
		return value > T::NONE && value < T::COUNT;
	}
	
}

