#include "WorldToScreen.hpp"
#include "GameObjects.h"
#include "netimmerse.h"

#include "Bethesda/TESMain.hpp"

namespace WorldToScreen {

	CameraParams kCameraData;

	bool __fastcall WorldToScreenPoint3(const CameraParams& arCamera, const NiPoint3& arPos, NiPoint3& arOut, float afZeroTolerance, int aeOffscreenHandleType) {
		bool st = false;
		// project a world space point to screen space
		float fW = arPos.x * arCamera.m_aafWorldToCam[3][0] +
			arPos.y * arCamera.m_aafWorldToCam[3][1] +
			arPos.z * arCamera.m_aafWorldToCam[3][2] +
			arCamera.m_aafWorldToCam[3][3];

		arOut.x = arPos.x * arCamera.m_aafWorldToCam[0][0] +
			arPos.y * arCamera.m_aafWorldToCam[0][1] +
			arPos.z * arCamera.m_aafWorldToCam[0][2] +
			arCamera.m_aafWorldToCam[0][3];

		arOut.y = arPos.x * arCamera.m_aafWorldToCam[1][0] +
			arPos.y * arCamera.m_aafWorldToCam[1][1] +
			arPos.z * arCamera.m_aafWorldToCam[1][2] +
			arCamera.m_aafWorldToCam[1][3];
		if (fW == 0.f)
			return false;

		float fInvW = 1.f / fW;
		// Transform Z, not entirely sure if it works. This indicates whether you're in front or behind the camera.
		arOut.z = arPos.x * arCamera.m_aafWorldToCam[2][0] +
			arPos.y * arCamera.m_aafWorldToCam[2][1] +
			arPos.z * arCamera.m_aafWorldToCam[2][2] +
			arCamera.m_aafWorldToCam[2][3];

		arOut.z = arOut.z * fInvW;

		if (!(fW > afZeroTolerance)) {
			st = true;
			fInvW *= -1.f;
		}

		arOut.x = arOut.x * fInvW;
		arOut.y = arOut.y * fInvW;

		arOut.x *= (arCamera.m_kPort.r - arCamera.m_kPort.l) * 0.5f;
		arOut.y *= (arCamera.m_kPort.t - arCamera.m_kPort.b) * 0.5f;

		arOut.x += (arCamera.m_kPort.r + arCamera.m_kPort.l) * 0.5f;
		arOut.y += (arCamera.m_kPort.t + arCamera.m_kPort.b) * 0.5f;

		arOut.y = arCamera.m_kPort.t - arOut.y;
		if (arOut.x >= arCamera.m_kPort.l && arOut.x <= arCamera.m_kPort.r &&
			arOut.y >= arCamera.m_kPort.b && arOut.y <= arCamera.m_kPort.t && st == 0) {
			return true;
		}
		else {
			if (aeOffscreenHandleType < 2) {
				float x2 = arCamera.m_kPort.r / 2, y2 = arCamera.m_kPort.t / 2;
				float d = std::sqrt((((arOut.x - x2) * (arOut.x - x2))) + ((arOut.y - y2) * (arOut.y - y2))); // Distance
				float r = y2 / d; // Segment ratio
				arOut.x = (((r * arOut.x + (1 - r) * x2)));// find point that divides the segment
				arOut.y = (((r * arOut.y + (1 - r) * y2)));// into the ratio (1-r):r, this yields circle coordinates

				if (!aeOffscreenHandleType) // We get square coordinates, since the circle we got is actually a circle inside the square.
				{
					x2 = arOut.x - 0.5f; y2 = arOut.y - 0.5f;
					float Divider = ((y2 * y2) > 0.125f) ? fabs(y2) : fabs(x2);
					arOut.x = 0.5f * ((x2 / Divider) + 1.f);
					arOut.y = 0.5f * ((y2 / Divider) + 1.f);
				}
				// Next two lines of code are not actually necessary at all, I'm just a paranoid fuck
				arOut.x = arOut.x > 0.f ? (arOut.x < 1.f ? arOut.x : 1.f) : 0.f;
				arOut.y = arOut.y > 0.f ? (arOut.y < 1.f ? arOut.y : 1.f) : 0.f;
			}
			return false;
		}
		arOut.z = arCamera.kWorld.Distance(arPos);
	}

	bool __fastcall WorldToScreen(const NiPoint3& arPos, NiPoint3& arOut, int aeOffscreenHandleType, float afZeroTolerance) {
		return WorldToScreenPoint3(kCameraData, arPos, arOut, afZeroTolerance, aeOffscreenHandleType);
	}

	void __stdcall CopyNiCamera(const NiCamera* apCamera, float afFOV) {
		const SceneGraph* pSceneGraph = TESMain::GetWorldSceneGraph();
		const PlayerCharacter* pPlayer = PlayerCharacter::GetSingleton();
		if (!pSceneGraph || !pPlayer)
			return;

		if (apCamera != pSceneGraph->spCamera || fabs(afFOV - pPlayer->worldFOV) > ZERO_TOLERANCE)
			return;

		kCameraData.kLocal = apCamera->m_kLocal.m_kTranslate;
		kCameraData.kWorld = apCamera->m_kWorld.m_kTranslate;
		memcpy(&kCameraData.m_aafWorldToCam, &apCamera->m_aafWorldToCam, sizeof(apCamera->m_aafWorldToCam));
		kCameraData.m_kPort = apCamera->m_kPort;
	}

	SPEC_NAKED void NiCameraGetAltHook() {
		__asm
		{
			push	dword ptr ss : [ebp + 8]
			push	dword ptr ss : [ebp - 8]
			call	CopyNiCamera
			leave
			retn	0x10
		}
	}

	void Install() {
		HookUtils::WriteRelJump(0xC5244A, NiCameraGetAltHook);
	}

}

// exports
extern "C" {
	bool __cdecl JG_WorldToScreen(const NiPoint3* apPos, NiPoint3& arOut, int aeOffscreenHandleType) {
		return WorldToScreen::WorldToScreenPoint3(WorldToScreen::kCameraData, *apPos, arOut, WorldToScreen::ZERO_TOLERANCE, aeOffscreenHandleType);
	}
}