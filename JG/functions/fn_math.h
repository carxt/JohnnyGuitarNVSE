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
DEFINE_COMMAND_PLUGIN(RGBtoHSV, , 0, 6, kParams_SixScriptVars);
DEFINE_COMMAND_PLUGIN(HSVtoRGB, , 0, 6, kParams_SixScriptVars);
DEFINE_COMMAND_PLUGIN(GetRGBColor, , 0, 3, kParams_ThreeInts);
DEFINE_COMMAND_PLUGIN(GetPackedPlayerFOV, , 0, 3, kParams_TwoScriptVars_OneOptionalScriptVar);
DEFINE_CMD_ALT_COND_PLUGIN(GetPlayerCamFOV, , 0, 1, kParams_OneInt);






void Cmd_GetPlayerCamFOV(UInt32 worldOr1stOrScene, double* result) {
	if (!g_thePlayer) return;
	*result = worldOr1stOrScene ? g_thePlayer->firstPersonFOV : g_thePlayer->worldFOV;
	if (worldOr1stOrScene > 1) {
		auto g_sceneGraph = *(SceneGraph**)0x11DEB7C;
		*result = g_sceneGraph ? g_sceneGraph->cameraFOV : 0;
	}
}


bool Cmd_GetPlayerCamFOV_Execute(COMMAND_ARGS)
{
	*result = 0;
	UInt32 worldOr1stOrScene = 0;
	if (!ExtractArgsEx(EXTRACT_ARGS_EX, &worldOr1stOrScene)) return true;
	Cmd_GetPlayerCamFOV(worldOr1stOrScene, result);
	return true;
}


bool Cmd_GetPlayerCamFOV_Eval(COMMAND_ARGS_EVAL)
{
	*result = 0;
	Cmd_GetPlayerCamFOV((UInt32) arg1, result);
	return true;
}



bool Cmd_GetPackedPlayerFOV_Execute(COMMAND_ARGS)
{
	*result = 0;
	ScriptVar *worldOut, *firstPersonOut, *scenegraphOut = NULL;
	if (!ExtractArgsEx(EXTRACT_ARGS_EX, &worldOut, &firstPersonOut, &scenegraphOut) || !g_thePlayer) return true;
	*result = 1;
	worldOut->data = g_thePlayer->firstPersonFOV;
	firstPersonOut->data = g_thePlayer->worldFOV;
	if (scenegraphOut) {
		auto g_sceneGraph = *(SceneGraph**)0x11DEB7C;
		scenegraphOut->data = g_sceneGraph ? g_sceneGraph->cameraFOV : 0;
		
	}
	return true;
}




bool Cmd_GetRGBColor_Execute(COMMAND_ARGS) {
	*result = 0;
	UInt32 r, g, b;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &r, &g, &b) && r <= 255 && g <= 255 && b <= 255) {
		*result = ((r & 0xFF) << 16) + ((g & 0xFF) << 8) + (b & 0xFF);
		if (IsConsoleMode()) Console_Print("0x%X", (UInt32)*result);
	}
	return true;
}

bool Cmd_HSVtoRGB_Execute(COMMAND_ARGS) {
	*result = 0;
	double r = 0, g = 0, b = 0, h = 0, s = 0, v = 0;
	ScriptVar* rOut, * gOut, * bOut, * hIn, * sIn, * vIn;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &hIn, &sIn, &vIn, &rOut, &gOut, &bOut)) {
		double      hh, p, q, t, ff;
		long        i;
		h = hIn->data;
		s = sIn->data;
		v = vIn->data;
		if (s <= 0.0) {       // < is bogus, just shuts up warnings
			r = v;
			g = v;
			b = v;
		}
		else {
			hh = h;
			if (hh >= 360.0) hh = 0.0;
			hh /= 60.0;
			i = (long)hh;
			ff = hh - i;
			p = v * (1.0 - s);
			q = v * (1.0 - (s * ff));
			t = v * (1.0 - (s * (1.0 - ff)));

			switch (i) {
				case 0:
					r = v;
					g = t;
					b = p;
					break;
				case 1:
					r = q;
					g = v;
					b = p;
					break;
				case 2:
					r = p;
					g = v;
					b = t;
					break;
				case 3:
					r = p;
					g = q;
					b = v;
					break;
				case 4:
					r = t;
					g = p;
					b = v;
					break;
				default:
					r = v;
					g = p;
					b = q;
					break;
			}
		}
		rOut->data = round(r * 255);
		gOut->data = round(g * 255);
		bOut->data = round(b * 255);
	}
	return true;
}

bool Cmd_RGBtoHSV_Execute(COMMAND_ARGS) {
	*result = 0;
	double r = 0, g = 0, b = 0, h = 0, s = 0, v = 0;
	ScriptVar* rIn, * gIn, * bIn, * hOut, * sOut, * vOut;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &rIn, &gIn, &bIn, &hOut, &sOut, &vOut)) {
		r = (rIn->data) / 255;
		g = (gIn->data) / 255;
		b = (bIn->data) / 255;
		double min, max, delta;

		min = r < g ? r : g;
		min = min < b ? min : b;

		max = r > g ? r : g;
		max = max > b ? max : b;

		v = max;
		delta = max - min;
		if (delta < 0.00001) {
			s = 0;
			h = 0;
			hOut->data = h;
			sOut->data = s;
			vOut->data = v;
			return true;
		}
		if (max > 0.0) {
			s = (delta / max);
		}
		else {
			s = 0.0;
			h = 0;
			hOut->data = h;
			sOut->data = s;
			vOut->data = v;
			return true;
		}
		if (r >= max) {
			h = (g - b) / delta;
		}
		else {
			if (g >= max) {
				h = 2.0 + (b - r) / delta;
			}
			else {
				h = 4.0 + (r - g) / delta;
			}
		}

		h *= 60.0;
		if (h < 0.0) h += 360.0;

		hOut->data = h;
		sOut->data = s;
		vOut->data = v;
		return true;
	}
	return true;
}
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

bool Cmd_Get3DDistanceFromHitToNiNode_Execute(COMMAND_ARGS) {
	Actor* actor = (Actor*)thisObj;
	char NiName[MAX_PATH];
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &NiName) && actor->IsActor() && actor->baseProcess) {
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
	TESObjectREFR* ref1, * ref2;
	if (!(ExtractArgsEx(EXTRACT_ARGS_EX, &ref1, &ref2, &NiName1, &NiName2))) return true;
	NiAVObject* Node1 = ref1->GetNiBlock(NiName1);
	NiAVObject* Node2 = ref2->GetNiBlock(NiName2);
	if (!Node1 || !Node2) return true;
	*result = NiNodeComputeDistance(&(Node1->m_worldTranslate), &(Node2->m_worldTranslate));
	if (IsConsoleMode()) Console_Print("Get3DDistanceBetweenNiNodes >> %f", *result);
	return true;
}

bool Cmd_JGLegacyWorldToScreen_Execute(COMMAND_ARGS) {
	*result = 0;
	float xIn = 0, yIn = 0, zIn = 0;
	UInt32 HandleType = 0;
	char X_outS[VarNameSize], Y_outS[VarNameSize], Z_outS[VarNameSize];
	TESObjectREFR* refr = NULL;

	if (ExtractArgsEx(EXTRACT_ARGS_EX, &X_outS, &Y_outS, &Z_outS, &xIn, &yIn, &zIn, &HandleType, &refr)) {
		if (refr) {
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

bool Cmd_WorldToScreen_Execute(COMMAND_ARGS) {
	*result = 0;
	float xIn = 0, yIn = 0, zIn = 0;
	UInt32 HandleType = 0;
	NiPoint3 NiPosIn = { 0,0,0 };
	TESObjectREFR* refr = NULL;
	ScriptVar* X_outS, * Y_outS, * Z_outS;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &X_outS, &Y_outS, &Z_outS, &NiPosIn.x, &NiPosIn.y, &NiPosIn.z, &HandleType, &refr)) {
		if (refr) {
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

bool Cmd_GetCameraTranslation_Execute(COMMAND_ARGS) {
	*result = 0;
	float xIn = 0, yIn = 0, zIn = 0;
	UInt32 doGetLocal = 0;
	char X_outS[VarNameSize], Y_outS[VarNameSize], Z_outS[VarNameSize];
	TESObjectREFR* refr = NULL;

	if (ExtractArgsEx(EXTRACT_ARGS_EX, &X_outS, &Y_outS, &Z_outS, &doGetLocal)) {
		if (auto m_GameCameraPos = JGGameCamera.CamPos) {
			if (doGetLocal) {
				setVarByName(PASS_VARARGS, X_outS, m_GameCameraPos->m_localTranslate.x);
				setVarByName(PASS_VARARGS, Y_outS, m_GameCameraPos->m_localTranslate.y);
				setVarByName(PASS_VARARGS, Z_outS, m_GameCameraPos->m_localTranslate.z);
			}
			else {
				setVarByName(PASS_VARARGS, X_outS, m_GameCameraPos->m_worldTranslate.x);
				setVarByName(PASS_VARARGS, Y_outS, m_GameCameraPos->m_worldTranslate.y);
				setVarByName(PASS_VARARGS, Z_outS, m_GameCameraPos->m_worldTranslate.z);
			}
		}
	}
	return true;
}