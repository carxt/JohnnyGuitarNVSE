#include "CameraOverride.hpp"
#include <GameObjects.h>

namespace CameraOverride {

	NiPoint3 kCameraPos;
	NiMatrix3 kCameraRot = NiMatrix3::IDENTITY;
	NiMatrix3 kCameraIdentity = NiMatrix3(0, 0, 1,
										  1, 0, 0,
										  0, 1, 0);
	uint32_t uiReferenceToTrack = 0;
	bool bOverrideCameraPos = false;
	bool bOverrideCameraRot = false;
	int32_t eAxis = -3;

	static SPEC_NOINLINE void __fastcall SetCameraTranslate(NiNode* apThis, uint32_t auiAddress, NiPoint3& arPos) {
		PlayerCharacter* pPlayer = PlayerCharacter::GetSingleton();
		if (bOverrideCameraPos && pPlayer->IsThirdPerson())
			arPos = kCameraPos;

		ThisCall(auiAddress, apThis, &arPos);
	}

	static SPEC_NOINLINE void __fastcall SetCameraRotate(NiNode* apThis, uint32_t auiAddress, const NiMatrix3& arRot) {
		NiCamera* pCamera = static_cast<NiCamera*>(apThis->GetAt(0));
		if (eAxis == CameraRotationType::ROTATE_RESET) {
			kCameraRot = arRot;
		}
		else if (bOverrideCameraRot && PlayerCharacter::GetSingleton()->IsThirdPerson()) {
			if (eAxis == CameraRotationType::ROTATE_TO_TARGET) {
				const TESForm* pForm = TESForm::GetFormByNumericID(uiReferenceToTrack);
				if (pForm->IsReference() && pCamera) {
					const TESObjectREFR* pTrackRef = static_cast<const TESObjectREFR*>(pForm);
					const NiNode* pRootNode = pTrackRef->Get3D();
					NiPoint3 kPos;
					if (pRootNode && pRootNode->m_pWorldBound && pRootNode->m_pWorldBound->iRadius) {
						kPos = pRootNode->m_pWorldBound->kCenter;
					}
					else {
						kPos = pTrackRef->GetPos();
					}

					pCamera->m_pkParent = nullptr;
					pCamera->LookAtWorldPoint(kPos, NiPoint3::UNIT_Z);
					pCamera->m_pkParent = apThis;
					apThis->SetLocalRotate(pCamera->m_kLocal.m_kRotate);
					pCamera->SetLocalRotate(NiMatrix3::IDENTITY);
				}
			}
			else {
				ThisCall(auiAddress, apThis, &kCameraRot);
			}
			return;
		}
		else {
			pCamera->SetLocalRotate(kCameraIdentity);
		}

		ThisCall(auiAddress, apThis, &arRot);
	}

	template<uint32_t uiAddress>
	class SetCameraTranslateHook {
		static inline HookUtils::CallDetour kDetour;

		static void __fastcall Hook(NiNode* apThis, void*, NiPoint3& arPos) {
			SetCameraTranslate(apThis, kDetour, arPos);
		}

	public:
		SetCameraTranslateHook() {
			kDetour.ReplaceCall(uiAddress, Hook);
		}
	};

	template<uint32_t uiAddress>
	class SetCameraRotateHook {
		static inline HookUtils::CallDetour kDetour;

		static void __fastcall Hook(NiNode* apThis, void*, const NiMatrix3& arRot) {
			SetCameraRotate(apThis, kDetour, arRot);
		}

	public:
		SetCameraRotateHook() {
			kDetour.ReplaceCall(uiAddress, Hook);
		}
	};

	void Reset() {
		bOverrideCameraPos = false;
		bOverrideCameraRot = false;
		kCameraPos = NiPoint3::ZERO;
		kCameraRot = NiMatrix3::IDENTITY;
	}

	void Install() {
		// PlayerCharacter::HandleFlycamMovement
		SetCameraTranslateHook<0x94AD8A>();
		SetCameraRotateHook<0x94AD9D>();

		// PlayerCharacter::UpdateCamera
		SetCameraTranslateHook<0x94BDC2>();
		SetCameraRotateHook<0x94BDD5>();
	}

	void OverridePos(bool abOverride, const NiPoint3& arNewPos) {
		bOverrideCameraPos = abOverride;
		if (abOverride)
			kCameraPos = arNewPos;
	}

	void OverrideRot(bool abOverride, CameraRotationType aeRotType, float afAngle, const TESObjectREFR* apRef) {
		bOverrideCameraRot = abOverride;
		eAxis = aeRotType;

		afAngle = afAngle * 0.01745329252; // PI / 180

		NiMatrix3 kNewRot;
		switch (aeRotType) {
			case CameraRotationType::ROTATE_NONE:
				kCameraRot = NiMatrix3::IDENTITY;
				break;
			case CameraRotationType::ROTATE_X:
				kNewRot.MakeXRotation(afAngle);
				break;
			case CameraRotationType::ROTATE_Y:
				kNewRot.MakeYRotation(afAngle);
				break;
			case CameraRotationType::ROTATE_Z:
				kNewRot.MakeZRotation(afAngle);
				break;
		}

		if (eAxis > CameraRotationType::ROTATE_NONE)
			kCameraRot = kCameraRot * kNewRot;

		if (apRef)
			uiReferenceToTrack = apRef->GetFormID();
	}

}