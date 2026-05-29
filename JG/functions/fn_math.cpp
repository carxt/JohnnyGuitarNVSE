#include "fn_math.h"
#include <GameObjects.h>
#include <GameProcess.h>
#include <misc/misc.h>
#include <misc/WorldToScreen.h>
#include "netimmerse.h"
#include "Bethesda/TESMain.hpp"

void Cmd_GetPlayerCamFOV(uint32_t worldOr1stOrScene, double* result) {
	if (!PlayerCharacter::GetSingleton()) return;
	*result = worldOr1stOrScene ? PlayerCharacter::GetSingleton()->firstPersonFOV : PlayerCharacter::GetSingleton()->worldFOV;
	if (worldOr1stOrScene > 1) {
		auto g_sceneGraph = TESMain::GetWorldSceneGraph();
		*result = g_sceneGraph ? g_sceneGraph->fCurrentFOV : 0;
	}
}

bool Cmd_GetPlayerCamFOV_Execute(COMMAND_ARGS)
{
	*result = 0;
	uint32_t worldOr1stOrScene = 0;
	if (!ExtractArgsEx(EXTRACT_ARGS_EX, &worldOr1stOrScene)) return true;
	Cmd_GetPlayerCamFOV(worldOr1stOrScene, result);
	return true;
}

bool Cmd_GetPlayerCamFOV_Eval(COMMAND_ARGS_EVAL)
{
	*result = 0;
	Cmd_GetPlayerCamFOV((uint32_t)arg1, result);
	return true;
}

bool Cmd_GetPackedPlayerFOV_Execute(COMMAND_ARGS)
{
	*result = 0;
	ScriptVar* worldOut, * firstPersonOut, * scenegraphOut = nullptr;
	if (!ExtractArgsEx(EXTRACT_ARGS_EX, &worldOut, &firstPersonOut, &scenegraphOut) || !PlayerCharacter::GetSingleton()) return true;
	*result = 1;
	worldOut->data = PlayerCharacter::GetSingleton()->firstPersonFOV;
	firstPersonOut->data = PlayerCharacter::GetSingleton()->worldFOV;
	if (scenegraphOut) {
		auto g_sceneGraph = TESMain::GetWorldSceneGraph();
		scenegraphOut->data = g_sceneGraph ? g_sceneGraph->fCurrentFOV : 0;

	}
	return true;
}

bool Cmd_GetRGBColor_Execute(COMMAND_ARGS) {
	*result = 0;
	uint32_t r, g, b;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &r, &g, &b) && r <= 255 && g <= 255 && b <= 255) {
		*result = ((r & 0xFF) << 16) + ((g & 0xFF) << 8) + (b & 0xFF);
		if (IsConsoleMode()) Console_Print("0x%X", (uint32_t)*result);
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

// lmao
bool Cmd_Sign_Execute(COMMAND_ARGS) {
	float fValue = 0.f;
	*result = 0;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &fValue) && fValue != 0.f) {
		*result = fValue > 0.f ? 1.f : -1.f;
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
	float fValue = 0.f, fMin = 0.f, fMax = 0.f;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &fValue, &fMin, &fMax)) {
		*result = fValue;
		if (fValue < fMin)
			*result = fMin;
		else if (fValue > fMax)
			*result = fMax;
	}
	return true;
}

bool Cmd_GetVector3DDistance_Execute(COMMAND_ARGS) {
	*result = 0;
	NiPoint3 kPosA;
	NiPoint3 kPosB;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &kPosA.x, &kPosA.y, &kPosA.z, &kPosB.x, &kPosB.y, &kPosB.z)) {
		*result = kPosA.Distance(kPosB);
		if (IsConsoleMode()) 
			Console_Print("Get3DDistance >> %f", *result);
	}
	return true;
}

bool Cmd_Get3DDistanceFromHitToNiNode_Execute(COMMAND_ARGS) {
	Actor* pActor = static_cast<Actor*>(thisObj);
	char cObjectName[MAX_PATH] = {};
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &cObjectName) && pActor->IsActor() && pActor->baseProcess) {
		NiAVObject* pObject = thisObj->GetNiBlock(cObjectName);
		if (!pObject)
			return true;

		HitData* pHitData = pActor->baseProcess->GetLastHitData();
		if (!pHitData)
			return true;
		
		*result = pObject->m_kWorld.m_kTranslate.Distance(pHitData->kImpactPos);
	}

	return true;
}

bool Cmd_Get3DDistanceToNiNode_Execute(COMMAND_ARGS) {
	*result = 0;
	char cObjectName[MAX_PATH] = {};
	NiPoint3 kPos;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &cObjectName, &kPos.x, &kPos.y, &kPos.z)) {
		NiAVObject* pObject = thisObj->GetNiBlock(cObjectName);
		if (!pObject) 
			return true;

		*result = pObject->m_kWorld.m_kTranslate.Distance(kPos);

		if (IsConsoleMode()) 
			Console_Print("Get3DDistanceToNiNode >> %f", *result);
	}
	return true;
}

bool Cmd_Get3DDistanceBetweenNiNodes_Execute(COMMAND_ARGS) {
	*result = 0;
	char cObjectAName[MAX_PATH] = {};
	char cObjectBName[MAX_PATH] = {};
	TESObjectREFR* pRefA = nullptr;
	TESObjectREFR* pRefB = nullptr;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &pRefA, &pRefB, &cObjectAName, &cObjectBName)) {
		NiAVObject* pObjectA = pRefA->GetNiBlock(cObjectAName);
		NiAVObject* pObjectB = pRefB->GetNiBlock(cObjectBName);
		if (!pObjectA || !pObjectB)
			return true;
		
		*result = pObjectA->m_kWorld.m_kTranslate.Distance(pObjectB->m_kWorld.m_kTranslate);
		
		if (IsConsoleMode()) 
			Console_Print("Get3DDistanceBetweenNiNodes >> %f", *result);
	}
	return true;
}

bool Cmd_JGLegacyWorldToScreen_Execute(COMMAND_ARGS) {
	*result = 0;
	NiPoint3 kPoint;
	uint32_t eHandleType = 0;
	char cOutX[VAR_NAME_SIZE], cOutY[VAR_NAME_SIZE], cOutZ[VAR_NAME_SIZE];
	TESObjectREFR* pRef = nullptr;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &cOutX, &cOutY, &cOutZ, &kPoint.x, &kPoint.y, &kPoint.z, &eHandleType, &pRef)) {
		if (pRef)
			kPoint += pRef->pos;

		float xOut = 0, yOut = 0, zOut = 0, outOfX = 0, outOfY = 0;
		*result = (WorldToScreen(&kPoint, xOut, yOut, zOut, eHandleType) ? 1 : 0);
		setVarByName(PASS_VARARGS, cOutX, xOut);
		setVarByName(PASS_VARARGS, cOutY, yOut);
		setVarByName(PASS_VARARGS, cOutZ, zOut);
	}
	return true;
}

bool Cmd_WorldToScreen_Execute(COMMAND_ARGS) {
	*result = 0;
	float xIn = 0, yIn = 0, zIn = 0;
	uint32_t eHandleType = 0;
	NiPoint3 kPoint = { 0,0,0 };
	TESObjectREFR* pRef = nullptr;
	ScriptVar* pOutX, * pOutY, * pOutZ;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &pOutX, &pOutY, &pOutZ, &kPoint.x, &kPoint.y, &kPoint.z, &eHandleType, &pRef)) {
		if (pRef)
			kPoint += pRef->pos;

		NiPoint3 kOut = { 0, 0, 0 };
		*result = (WorldToScreen(&kPoint, kOut.x, kOut.y, kOut.z, eHandleType) ? 1 : 0);
		pOutX->data = kOut.x;
		pOutY->data = kOut.y;
		pOutZ->data = kOut.z;
	}
	return true;
}

bool Cmd_GetCameraTranslation_Execute(COMMAND_ARGS) {
	*result = 0;
	float xIn = 0, yIn = 0, zIn = 0;
	uint32_t doGetLocal = 0;
	char X_outS[VAR_NAME_SIZE], Y_outS[VAR_NAME_SIZE], Z_outS[VAR_NAME_SIZE];
	TESObjectREFR* refr = nullptr;

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