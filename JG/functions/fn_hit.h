#pragma once
#include "fn_common.h"

DEFINE_COMMAND_PLUGIN(ApplyHitData, , true, kParams_ApplyHitData);
DEFINE_COMMAND_PLUGIN(GetObjectMaterial, , true, kParams_GetObjectMaterial);
DEFINE_COMMAND_PLUGIN(ApplyObjectImpact, , true, kParams_ApplyObjectImpact);
DEFINE_COMMAND_PLUGIN(InterruptWeaponAnim, , true, nullptr);
DEFINE_COMMAND_PLUGIN(ApplyRagdollForce, , true, kParams_FourFloats);
DEFINE_COMMAND_PLUGIN(Set3rdPersonOverlay, , false, kParams_OneInt_OneOptionalInt);
DEFINE_COMMAND_PLUGIN(Set3rdPersonOverlayCullParts, , false, kParams_Set3rdPersonOverlayCullParts);
