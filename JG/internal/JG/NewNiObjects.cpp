#include "NewNiObjects.hpp"

namespace NewNiObjects {

	STACK_FRAME_OPT_ENABLE

	NiLightRadiusController* NiLightRadiusController::CreateObject() {
		NiLightRadiusController* pController = reinterpret_cast<NiLightRadiusController*>(NiLightDimmerController::CreateObject());
		pController->BuildVTable<NiFloatInterpController, 60>({
			{ 2, &NiLightRadiusController::_GetRTTI },
			{ 18, &NiLightRadiusController::_CreateClone },
			{ 37, &NiLightRadiusController::_Update }
			});

		return pController;
	}

	NiLightRadiusController* NiLightRadiusController::_CreateClone(NiCloningProcess& arCloneProc) {
		NiLightRadiusController* pClone = CreateObject();
#ifdef GAME
		ThisCall(0xA57620, this, pClone, &arCloneProc); // NiFloatInterpController::CopyMembers
#else
		ThisCall(0x8083E0, this, pClone, &arCloneProc); // NiFloatInterpController::CopyMembers
#endif
		return pClone;
	}

	void NiLightRadiusController::_Update(NiUpdateData& arUpdateData) {
		if (GetManagerControlled())
			m_fScaledTime = INVALID_TIME;
		else if (DontDoUpdate(arUpdateData.fTime) && (!m_spInterpolator || !m_spInterpolator->AlwaysUpdate()))
			return;

		if (!m_spInterpolator)
			return;

		float fValue;
		if (m_spInterpolator->UpdateFloat(m_fScaledTime, m_pkTarget, fValue) && m_pkTarget) {
			NiLight* pLight = static_cast<NiLight*>(m_pkTarget);
			if (pLight)
				pLight->SetLightRadius(fValue);
		}
	}

	void InitNewLoaders() {
		_MESSAGE("Registering new NiObjects...");
		NiStream::RegisterLoader("NiLightRadiusController", NiLightRadiusController::CreateObject);
	}

	HookUtils::CallDetour kInitLoadersDetour;
	void __cdecl InitLoadersHook() {
		CdeclCall(kInitLoadersDetour);
		InitNewLoaders();
	}

	STACK_FRAME_OPT_RESET

	void Install() {
#ifdef GAME
		kInitLoadersDetour.ReplaceCall(0x86AA47, InitLoadersHook);
#else
		kInitLoadersDetour.ReplaceCall(0x445FEF, InitLoadersHook);
#endif
	}

}