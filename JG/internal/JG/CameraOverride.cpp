#include "CameraOverride.hpp"
#include <GameObjects.h>

namespace CameraOverride {

	NiVector3 kCameraPos;
	NiMatrix3 kCameraRot = NiMatrix3::IDENTITY;
	NiMatrix3 kCameraIdentity = NiMatrix3(0, 0, 1,
		1, 0, 0,
		0, 1, 0);
	uint32_t uiReferenceToTrack = 0;
	bool bOverrideCameraPos = false;
	bool bOverrideCameraRot = false;
	int eAxis = -3;

	void __fastcall SetCameraTranslateHook(NiNode* apThis, void*, NiVector3& arPos) {
		PlayerCharacter* pPlayer = PlayerCharacter::GetSingleton();
		if (bOverrideCameraPos && pPlayer->IsThirdPerson())
			arPos = kCameraPos;

		apThis->SetLocalTranslate(arPos);
	}

	void __fastcall SetCameraRotateHook(NiNode* apThis, void*, NiMatrix3& arRot) {
		PlayerCharacter* pPlayer = PlayerCharacter::GetSingleton();
		NiCamera* pCamera = (NiCamera*)apThis->GetAt(0);
		if (eAxis == kCameraRotationType_Reset) {
			kCameraRot = arRot;
		}
		else if (bOverrideCameraRot && pPlayer->IsThirdPerson()) {
			if (eAxis == kCameraRotationType_TrackTarget) {
				TESForm* pForm = TESForm::GetFormByNumericID(uiReferenceToTrack);
				if (pForm->IsReference() && pCamera) {
					TESObjectREFR* pTrackRef = (TESObjectREFR*)pForm;
					NiNode* pRootNode = pTrackRef->Get3D();
					NiVector3 kPos;
					if (pRootNode && pRootNode->m_pWorldBound && pRootNode->m_pWorldBound->iRadius) {
						kPos = pRootNode->m_pWorldBound->kCenter;
					}
					else {
						kPos = *(NiVector3*)pTrackRef->GetPos();
					}

					pCamera->m_parent = nullptr;
					pCamera->LookAtWorldPoint(kPos, NiVector3(0, 0, 1));
					pCamera->m_parent = apThis;
					apThis->SetLocalRotate(pCamera->m_local.rotate);
					pCamera->SetLocalRotate(NiMatrix3::IDENTITY);
				}
			}
			else {
				apThis->SetLocalRotate(kCameraRot);
			}
			return;
		}
		else {
			pCamera->SetLocalRotate(kCameraIdentity);
		}

		apThis->SetLocalRotate(arRot);
	}

	void Reset() {
		bOverrideCameraPos = false;
		bOverrideCameraRot = false;
		kCameraPos = NiVector3(0, 0, 0);
		kCameraRot = NiMatrix3::IDENTITY;
	}

	void Install()
	{
		WriteRelCall(0x94AD8A, uint32_t(SetCameraTranslateHook));
		WriteRelCall(0x94AD9D, uint32_t(SetCameraRotateHook));

		WriteRelCall(0x94BDC2, uint32_t(SetCameraTranslateHook));
		WriteRelCall(0x94BDD5, uint32_t(SetCameraRotateHook));
	}

	void OverridePos(bool override)
	{
		bOverrideCameraPos = override;
	}

	void OverrideRot(bool override)
	{
		bOverrideCameraRot = override;
	}

}