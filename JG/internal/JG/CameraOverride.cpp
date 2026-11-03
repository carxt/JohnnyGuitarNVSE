#include "CameraOverride.hpp"
#include "Bethesda/PlayerCharacter.hpp"
#include "Gamebryo/NiNode.hpp"
#include "Gamebryo/NiBound.hpp"
#include "Gamebryo/NiCamera.hpp"

#include "Shared/SafeWrite/SafeWrite.hpp"

namespace CameraOverride {

	// Stack frame optimizations are enabled in file's properties! Macros are symbolic
	STACK_FRAME_OPT_ENABLE

	static NiPoint3 kCameraPos;
	static NiMatrix3 kCameraRot = NiMatrix3::IDENTITY;
	static NiMatrix3 kCameraIdentity = NiMatrix3(0, 0, 1,
										  1, 0, 0,
										  0, 1, 0);
	static FormID uiReferenceToTrack = 0;
	static bool bOverrideCameraPos = false;
	static bool bOverrideCameraRot = false;
	static int32_t eAxis = -3;

	namespace Hooks {

		static SPEC_NOINLINE void __fastcall SetCameraTranslate(NiNode* apThis, uint32_t auiAddress, NiPoint3& arPos) {
			if (bOverrideCameraPos && PlayerCharacter::GetSingleton()->Is3rdPerson())
				arPos = kCameraPos;

			ThisCall(auiAddress, apThis, &arPos);
		}

		static SPEC_NOINLINE void __fastcall SetCameraRotate(NiNode* apThis, uint32_t auiAddress, const NiMatrix3& arRot) {
			NiCamera* pCamera = static_cast<NiCamera*>(apThis->GetAt(0));
			if (eAxis == CameraRotationType::ROTATE_RESET) {
				kCameraRot = arRot;
			}
			else if (bOverrideCameraRot && PlayerCharacter::GetSingleton()->Is3rdPerson()) {
				if (eAxis == CameraRotationType::ROTATE_TO_TARGET) {
					const TESForm* pForm = TESForm::GetFormByNumericID(uiReferenceToTrack);
					if (pForm->IsReference() && pCamera) {
						const TESObjectREFR* pTrackRef = static_cast<const TESObjectREFR*>(pForm);
						const NiAVObject* pRefRoot = pTrackRef->Get3D();
						NiPoint3 kPos;
						if (pRefRoot && pRefRoot->IsVisualObject()) {
							kPos = pRefRoot->m_pWorldBound->GetCenter();
						}
						else {
							kPos = pTrackRef->GetLocationOnReference();
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

			void Hook(NiPoint3& arPos) {
				SetCameraTranslate(reinterpret_cast<NiNode*>(this), kDetour, arPos);
			}

		public:
			SetCameraTranslateHook() {
				kDetour.ReplaceCall(uiAddress, &SetCameraTranslateHook::Hook);
			}
		};

		template<uint32_t uiAddress>
		class SetCameraRotateHook {
			static inline HookUtils::CallDetour kDetour;

			void Hook(const NiMatrix3& arRot) {
				SetCameraRotate(reinterpret_cast<NiNode*>(this), kDetour, arRot);
			}

		public:
			SetCameraRotateHook() {
				kDetour.ReplaceCall(uiAddress, &SetCameraRotateHook::Hook);
			}
		};

		static void Init() {
			// PlayerCharacter::HandleFlycamMovement
			SetCameraTranslateHook<0x94AD8A>();
			SetCameraRotateHook<0x94AD9D>();

			// PlayerCharacter::UpdateCamera
			SetCameraTranslateHook<0x94BDC2>();
			SetCameraRotateHook<0x94BDD5>();
		}
	}

	void Reset() {
		bOverrideCameraPos = false;
		bOverrideCameraRot = false;
		kCameraPos = NiPoint3::ZERO;
		kCameraRot = NiMatrix3::IDENTITY;
	}

	void Install() {
		Hooks::Init();
	}

	void __fastcall OverridePos(bool abOverride, const NiPoint3& arNewPos) {
		bOverrideCameraPos = abOverride;
		if (abOverride)
			kCameraPos = arNewPos;
	}

	void __fastcall OverrideRot(bool abOverride, CameraRotationType aeRotType, float afAngle, const TESObjectREFR* apRef) {
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

	STACK_FRAME_OPT_RESET

}