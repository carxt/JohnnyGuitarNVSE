#include "NavMeshInfo.hpp"
#include "NavMesh.hpp"
#ifdef EDITOR
#include "TESObjectCELL.hpp"
#include "TESWorldSpace.hpp"
#endif

bool NavMeshInfo::GetFlag(Flags aeFlag) const {
	return uiFlags.Get(aeFlag);
}

// GAME - 0x68F320
bool NavMeshInfo::GetDisabled() const {
	return uiFlags.bDisabled;
}

// GAME - 0x690830
TESForm* NavMeshInfo::GetParentSpace() const {
#ifdef GAME
	return ThisCall<TESForm*>(0x690830, this);
#else
	if (pParentSpace)
		return pParentSpace;
	return TESForm::GetFormByNumericID(uiParentSpaceID);
#endif
}

// GAME - 0x6B77B0
TESObjectCELL* NavMeshInfo::GetInteriorCell() const {
#ifdef GAME
	return ThisCall<TESObjectCELL*>(0x6B77B0, this);
#else
	TESForm* pForm = GetParentSpace();
	if (pForm && pForm->GetFormType() == FORM_TYPE::TESObjectCELL)
		return static_cast<TESObjectCELL*>(pForm);
	return nullptr;
#endif
}

// GAME - 0x690800
TESWorldSpace* NavMeshInfo::GetWorldSpace() const {
#ifdef GAME
	return ThisCall<TESWorldSpace*>(0x690800, this);
#else
	TESForm* pForm = GetParentSpace();
	if (pForm && pForm->GetFormType() == FORM_TYPE::TESWorldSpace)
		return static_cast<TESWorldSpace*>(pForm);
	return nullptr;
#endif
}

// GAME - 0x7DF1F0
float NavMeshInfo::GetPreferredPercent() const {
	return fPreferredPercent;
}

// GAME - 0x69DFB0
bool NavMeshInfo::HasNavMesh() const {
	return pNavMesh != nullptr;
}

// GAME - 0x69AD00
// GECK - 0x41FB60
bool NavMeshInfo::GetNavMesh(NavMeshPtr& arNavMesh) const {
	if (GetDisabled())
		return false;

	NavMeshPtr::MakeNavMeshPtr(arNavMesh, pNavMesh);
	return arNavMesh != nullptr;
}

// GAME - 0x690860
bool NavMeshInfo::GetNavMeshEvenDisabled(NavMeshPtr& arNavMesh) const {
	NavMeshPtr::MakeNavMeshPtr(arNavMesh, pNavMesh);
	return pNavMesh != nullptr;
}

// GAME - 0x68F2E0
bool NavMeshInfo::GetNavMesh(NavMesh*& arNavMesh) const {
	if (GetDisabled()) {
		arNavMesh = nullptr;
		return false;
	}
	else {
		arNavMesh = pNavMesh;
		return arNavMesh != nullptr;
	}
}
