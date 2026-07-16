#include "fn_math.h"
#include "GameObjects.h"
#include "GameProcess.h"
#include "misc/misc.h"
#include "netimmerse.h"
#include "JG/WorldToScreen.hpp"

#include "Bethesda/TESMain.hpp"

enum FOVType {
	VIEWMODEL	= 0,
	WORLD		= 1,
	CURRENT		= 2,
};

SPEC_NOINLINE bool Cmd_GetPlayerCamFOV_Eval(COMMAND_ARGS_EVAL) {
	*result = 0;
	const FOVType eFOV = *reinterpret_cast<FOVType*>(&arg1);
	switch (eFOV) {
		case FOVType::VIEWMODEL:
			*result = PlayerCharacter::GetSingleton()->firstPersonFOV;
			break;
		case FOVType::WORLD:
			*result = PlayerCharacter::GetSingleton()->worldFOV;
			break;
		default:
			*result = TESMain::GetWorldSceneGraph()->fCurrentFOV;
			break;
	}
	return true;
}

bool Cmd_GetPlayerCamFOV_Execute(COMMAND_ARGS) {
	FOVType eFOV = FOVType::VIEWMODEL;
	ExtractArgsEx(EXTRACT_ARGS_EX, &eFOV);
	return Cmd_GetPlayerCamFOV_Eval(thisObj, reinterpret_cast<void*>(eFOV), nullptr, result);
}

bool Cmd_GetPackedPlayerFOV_Execute(COMMAND_ARGS) {
	*result = 0;
	ScriptVar* pViewmodelFOV = nullptr;
	ScriptVar* pWorldFOV = nullptr;
	ScriptVar* pCurrentFOV = nullptr;
	if (!ExtractArgsEx(EXTRACT_ARGS_EX, &pViewmodelFOV, &pWorldFOV, &pCurrentFOV) || !PlayerCharacter::GetSingleton())
		return true;

	ASSUME_ASSERT(pViewmodelFOV && pWorldFOV);

	pViewmodelFOV->data = PlayerCharacter::GetSingleton()->firstPersonFOV;
	pWorldFOV->data = PlayerCharacter::GetSingleton()->worldFOV;
	if (pCurrentFOV)
		pCurrentFOV->data = TESMain::GetWorldSceneGraph()->fCurrentFOV;

	*result = 1;
	return true;
}

bool Cmd_GetRGBColor_Execute(COMMAND_ARGS) {
	*result = 0;
	uint32_t uiR, uiG, uiB;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &uiR, &uiG, &uiB) && uiR <= UINT8_MAX && uiG <= UINT8_MAX && uiB <= UINT8_MAX) {
		*result = uint32_t(((uiR & UINT8_MAX) << 16) + ((uiG & UINT8_MAX) << 8) + (uiB & UINT8_MAX));
		if (IsConsoleMode()) 
			Console_Print("0x%X", (uint32_t)*result);
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
	*result = 0;
	float fValue = 0.f;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &fValue) && fValue != 0.f) {
		*result = fValue > 0.f ? 1.0 : -1.0;
	}
	return true;
}

bool Cmd_Lerp_Execute(COMMAND_ARGS) {
	*result = 0;
	float fStart = 0.f, fEnd = 0.f, fValue = 0.f;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &fStart, &fEnd, &fValue)) {
		*result = (1.f - fValue) * fStart + fValue * fEnd;
	}
	return true;
}

bool Cmd_Remap_Execute(COMMAND_ARGS) {
	*result = 0;
	float fValue = 0.f, fMinA = 0.f, fMaxA = 0.f, fMinB = 0.f, fMaxB = 0.f;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &fValue, &fMinA, &fMaxA, &fMinB, &fMaxB)) {
		*result = (fValue - fMinA) / (fMaxA - fMinA) * (fMaxB - fMinB) + fMinB;
	}
	return true;
}

bool Cmd_Clamp_Execute(COMMAND_ARGS) {
	*result = 0;
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
	*result = 0;
	const Actor* pActor = static_cast<Actor*>(thisObj);
	char cObjectName[MAX_PATH];
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &cObjectName) && pActor->IsMobileObject() && pActor->baseProcess) {
		const NiAVObject* pObject = thisObj->GetNiBlock(cObjectName);
		const ActorHitData* pHitData = pActor->baseProcess->GetHitData();
		if (!pHitData || !pObject) 
			return true;
		
		*result = pObject->m_kWorld.m_kTranslate.Distance(pHitData->impactPos);
	}

	return true;
}

bool Cmd_Get3DDistanceToNiNode_Execute(COMMAND_ARGS) {
	*result = 0;
	NiPoint3 kPos;
	char cObjectName[MAX_PATH] = {};
	if (!thisObj || !(ExtractArgsEx(EXTRACT_ARGS_EX, &cObjectName, &kPos.x, &kPos.y, &kPos.z))) 
		return true;

	const NiAVObject* pObject = thisObj->GetNiBlock(cObjectName);
	if (!pObject) 
		return true;
	
	*result = pObject->m_kWorld.m_kTranslate.Distance(kPos);
	
	if (IsConsoleMode()) 
		Console_Print("Get3DDistanceToNiNode >> %f", *result);
	return true;
}

bool Cmd_Get3DDistanceBetweenNiNodes_Execute(COMMAND_ARGS) {
	*result = 0;
	TESObjectREFR* pRefA = nullptr;
	TESObjectREFR* pRefB = nullptr;
	char cObjectNameA[MAX_PATH];
	char cObjectNameB[MAX_PATH];
	if (!ExtractArgsEx(EXTRACT_ARGS_EX, &pRefA, &pRefB, &cObjectNameA, &cObjectNameB)) 
		return true;

	const NiAVObject* pObjectA = pRefA->GetNiBlock(cObjectNameA);
	const NiAVObject* pObjectB = pRefB->GetNiBlock(cObjectNameB);
	if (!pObjectA || !pObjectB) 
		return true;

	*result = pObjectA->m_kWorld.m_kTranslate.Distance(pObjectB->m_kWorld.m_kTranslate);

	if (IsConsoleMode()) 
		Console_Print("Get3DDistanceBetweenNiNodes >> %f", *result);
	return true;
}

bool Cmd_JGLegacyWorldToScreen_Execute(COMMAND_ARGS) {
	*result = 0;
	uint32_t eHandleType = 0;
	TESObjectREFR* pRef = nullptr;
	NiPoint3 kPos;
	char cOutX[VAR_NAME_SIZE];
	char cOutY[VAR_NAME_SIZE];
	char cOutZ[VAR_NAME_SIZE];
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &cOutX, &cOutY, &cOutZ, &kPos.x, &kPos.y, &kPos.z, &eHandleType, &pRef)) {
		if (pRef)
			kPos += pRef->pos;

		NiPoint3 kResult = { 0.f, 0.f, 0.f };
		*result = (WorldToScreen::WorldToScreen(kPos, kResult, eHandleType) ? 1.0 : 0.0);

		setVarByName(PASS_VARARGS, cOutX, kResult.x);
		setVarByName(PASS_VARARGS, cOutY, kResult.y);
		setVarByName(PASS_VARARGS, cOutZ, kResult.z);
	}
	return true;
}

bool Cmd_WorldToScreen_Execute(COMMAND_ARGS) {
	*result = 0;
	uint32_t eHandleType = 0;
	TESObjectREFR* pRef = nullptr;
	ScriptVar* pOutX = nullptr;
	ScriptVar* pOutY = nullptr;
	ScriptVar* pOutZ = nullptr;
	NiPoint3 kPos;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &pOutX, &pOutY, &pOutZ, &kPos.x, &kPos.y, &kPos.z, &eHandleType, &pRef)) {
		ASSUME_ASSERT(pOutX && pOutY && pOutZ);
		if (pRef)
			kPos += pRef->pos; 

		NiPoint3 kResult = { 0.f, 0.f, 0.f };
		*result = (WorldToScreen::WorldToScreen(kPos, kResult, eHandleType) ? 1.0 : 0.0);

		pOutX->data = kResult.x;
		pOutY->data = kResult.y;
		pOutZ->data = kResult.z;
	}
	return true;
}

bool Cmd_GetCameraTranslation_Execute(COMMAND_ARGS) {
	*result = 0;
	BOOL bLocal = FALSE;
	TESObjectREFR* pRef = nullptr;
	char cOutX[VAR_NAME_SIZE]; 
	char cOutY[VAR_NAME_SIZE];
	char cOutZ[VAR_NAME_SIZE];
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &cOutX, &cOutY, &cOutZ, &bLocal)) {
		if (bLocal) {
			setVarByName(PASS_VARARGS, cOutX, WorldToScreen::kCameraData.kLocal.x);
			setVarByName(PASS_VARARGS, cOutY, WorldToScreen::kCameraData.kLocal.y);
			setVarByName(PASS_VARARGS, cOutZ, WorldToScreen::kCameraData.kLocal.z);
		}
		else {
			setVarByName(PASS_VARARGS, cOutX, WorldToScreen::kCameraData.kWorld.x);
			setVarByName(PASS_VARARGS, cOutY, WorldToScreen::kCameraData.kWorld.y);
			setVarByName(PASS_VARARGS, cOutZ, WorldToScreen::kCameraData.kWorld.z);
		}
	}
	return true;
}