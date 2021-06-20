#pragma once
// Functions that perform mathematical calculations
DEFINE_COMMAND_PLUGIN(JGLegacyWorldToScreen, , 0, 8, kParamsProjectionArgsLegacy);
DEFINE_COMMAND_PLUGIN(Get3DDistanceBetweenNiNodes, , 0, 4, kParams_TwoRefs_TwoStrings);
DEFINE_COMMAND_PLUGIN(Get3DDistanceToNiNode, , 1, 4, kParams_OneString_ThreeFloats);
DEFINE_COMMAND_PLUGIN(Get3DDistanceFromHitToNiNode, , 1, 1, kParams_OneString);
DEFINE_COMMAND_PLUGIN(GetVector3DDistance, , 0, 6, kParams_SixFloats);
DEFINE_COMMAND_PLUGIN(Clamp, , 0, 3, kParams_ThreeFloats);
DEFINE_COMMAND_PLUGIN(Remap, , 0, 5, kParams_FiveFloats);
DEFINE_COMMAND_PLUGIN(Lerp, , 0, 3, kParams_ThreeFloats);
DEFINE_COMMAND_PLUGIN(Sign, , 0, 1, kParams_OneFloat);
DEFINE_COMMAND_PLUGIN(GetCameraTranslation, , FALSE, 4, kParams_ThreeStrings_OneInt);
DEFINE_COMMAND_PLUGIN(WorldToScreen, , 0, 8, kParamsProjectionArgs);
bool Cmd_Sign_Execute(COMMAND_ARGS) {
	float value;
	*result = 0;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &value) && value != 0) {
		*result = value > 0 ? 1 : -1;
	}
	return true;
}
bool Cmd_Lerp_Execute(COMMAND_ARGS) {
	float v0 = 0, v1 = 0, t = 0;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &v0, &v1, &t)) {
		*result = (1 - t) * v0 + t * v1;
	}
	return true;
}
bool Cmd_Remap_Execute(COMMAND_ARGS) {
	float v1current = 0, v1min = 0, v1max = 0, v2min = 0, v2max = 0;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &v1current, &v1min, &v1max, &v2min, &v2max)) {
		*result = (v1current - v1min) / (v1max - v1min) * (v2max - v2min) + v2min;
	}
	return true;
}
bool Cmd_Clamp_Execute(COMMAND_ARGS) {
	float value = 0, min = 0, max = 0;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &value, &min, &max)) {
		*result = value;
		if (value < min) {
			*result = min;
		}
		else if (value > max) {
			*result = max;
		}

	}
	return true;

}

bool Cmd_GetVector3DDistance_Execute(COMMAND_ARGS) {
	*result = 0;
	NiVector3 pos1;
	NiVector3 pos2;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &(pos1.x), &(pos1.y), &(pos1.z), &(pos2.x), &(pos2.y), &(pos2.z))) {
		*result = NiNodeComputeDistance(&pos1, &pos2);
		if (IsConsoleMode()) Console_Print("Get3DDistance >> %f", *result);
	}
	return true;
}

bool Cmd_Get3DDistanceFromHitToNiNode_Execute(COMMAND_ARGS)
{
	Actor* actor = (Actor*)thisObj;
	char NiName[MAX_PATH];
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &NiName) && actor->IsActor() && actor->baseProcess)
	{
		NiAVObject* t_Node = thisObj->GetNiBlock(NiName);
		ActorHitData* hitData = actor->baseProcess->GetHitData();
		if (!hitData || !t_Node) return true;
		*result = NiNodeComputeDistance(&(t_Node->m_worldTranslate), &(hitData->impactPos));

	}

	return true;
}
bool Cmd_Get3DDistanceToNiNode_Execute(COMMAND_ARGS) {
	*result = 0;
	char NiName[MAX_PATH];
	NiVector3 Coord;
	if (!thisObj || !(ExtractArgsEx(EXTRACT_ARGS_EX, &NiName, &(Coord.x), &(Coord.y), &(Coord.z)))) return true;
	NiAVObject* t_Node = thisObj->GetNiBlock(NiName);
	if (!t_Node) return true;
	*result = NiNodeComputeDistance(&(t_Node->m_worldTranslate), &Coord);
	if (IsConsoleMode()) Console_Print("Get3DDistanceToNiNode >> %f", *result);
	return true;
}

bool Cmd_Get3DDistanceBetweenNiNodes_Execute(COMMAND_ARGS) {
	*result = 0;
	char NiName1[MAX_PATH], NiName2[MAX_PATH];
	TESObjectREFR *ref1, *ref2;
	if (!(ExtractArgsEx(EXTRACT_ARGS_EX, &ref1, &ref2, &NiName1, &NiName2))) return true;
	NiAVObject* Node1 = ref1->GetNiBlock(NiName1);
	NiAVObject* Node2 = ref2->GetNiBlock(NiName2);
	if (!Node1 || !Node2) return true;
	*result = NiNodeComputeDistance(&(Node1->m_worldTranslate), &(Node2->m_worldTranslate));
	if (IsConsoleMode()) Console_Print("Get3DDistanceBetweenNiNodes >> %f", *result);
	return true;
}

bool Cmd_JGLegacyWorldToScreen_Execute(COMMAND_ARGS)
{

	*result = 0;
	float xIn = 0, yIn = 0, zIn = 0;
	UInt32 HandleType = 0;
	char X_outS[VarNameSize], Y_outS[VarNameSize], Z_outS[VarNameSize];
	TESObjectREFR* refr = NULL;

	if (ExtractArgsEx(EXTRACT_ARGS_EX, &X_outS, &Y_outS, &Z_outS, &xIn, &yIn, &zIn, &HandleType, &refr))
	{
		if (refr)
		{
			xIn += refr->posX; yIn += refr->posY; zIn += refr->posZ;
		}
		NiPoint3 NiPointBuffer = { 0,0,0 };
		NiPointAssign(&NiPointBuffer, xIn, yIn, zIn);
		float xOut = 0, yOut = 0, zOut = 0, outOfX = 0, outOfY = 0;
		*result = (WorldToScreen(&NiPointBuffer, xOut, yOut, zOut, HandleType) ? 1 : 0);
		setVarByName(PASS_VARARGS, X_outS, xOut);
		setVarByName(PASS_VARARGS, Y_outS, yOut);
		setVarByName(PASS_VARARGS, Z_outS, zOut);
	}
	return true;
}

bool Cmd_WorldToScreen_Execute(COMMAND_ARGS)
{

	*result = 0;
	float xIn = 0, yIn = 0, zIn = 0;
	UInt32 HandleType = 0;
	NiPoint3 NiPosIn = { 0,0,0 };
	TESObjectREFR* refr = NULL;
	ScriptVar* X_outS, *Y_outS, *Z_outS;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &X_outS, &Y_outS, &Z_outS, &NiPosIn.x, &NiPosIn.y, &NiPosIn.z, &HandleType, &refr))
	{
		if (refr)
		{
			NiPosIn.x += refr->posX; NiPosIn.y += refr->posY; NiPosIn.z += refr->posZ;
		}
		NiPoint3 NiPosOut = { 0, 0, 0 };
		*result = (WorldToScreen(&NiPosIn, NiPosOut.x, NiPosOut.y, NiPosOut.z, HandleType) ? 1 : 0);
		X_outS->data = NiPosOut.x;
		Y_outS->data = NiPosOut.y;
		Z_outS->data = NiPosOut.z;
	}
	return true;
}

bool Cmd_GetCameraTranslation_Execute(COMMAND_ARGS)
{

	*result = 0;
	float xIn = 0, yIn = 0, zIn = 0;
	UInt32 doGetLocal = 0;
	char X_outS[VarNameSize], Y_outS[VarNameSize], Z_outS[VarNameSize];
	TESObjectREFR* refr = NULL;

	if (ExtractArgsEx(EXTRACT_ARGS_EX, &X_outS, &Y_outS, &Z_outS, &doGetLocal))
	{
		if (auto m_GameCameraPos = JGGameCamera.CamPos) {
			if (doGetLocal)
			{
				setVarByName(PASS_VARARGS, X_outS, m_GameCameraPos->m_localTranslate.x);
				setVarByName(PASS_VARARGS, Y_outS, m_GameCameraPos->m_localTranslate.y);
				setVarByName(PASS_VARARGS, Z_outS, m_GameCameraPos->m_localTranslate.z);
			}
			else
			{
				setVarByName(PASS_VARARGS, X_outS, m_GameCameraPos->m_worldTranslate.x);
				setVarByName(PASS_VARARGS, Y_outS, m_GameCameraPos->m_worldTranslate.y);
				setVarByName(PASS_VARARGS, Z_outS, m_GameCameraPos->m_worldTranslate.z);
			}
		}


	}
	return true;
}