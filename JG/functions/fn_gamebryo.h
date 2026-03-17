#pragma once

#include "Bethesda/BSUtilities.hpp"
#include "Bethesda/AILinearTaskThreadManager.hpp"

DEFINE_COMMAND_PLUGIN(SetAlphaPropertyValue, , true, kParams_OneString_TwoInts);
DEFINE_COMMAND_PLUGIN(GetAlphaPropertyValue, , true, kParams_OneString_OneInt);
DEFINE_COMMAND_PLUGIN(SetStencilPropertyValue, , true, kParams_OneString_TwoInts);
DEFINE_COMMAND_PLUGIN(GetStencilPropertyValue, , true, kParams_OneString_OneInt);
DEFINE_COMMAND_PLUGIN(SetSwitchNodeIndex, , true, kParams_OneString_OneInt);
DEFINE_COMMAND_PLUGIN(GetSwitchNodeIndex, , true, kParams_OneString);
DEFINE_COMMAND_PLUGIN(SetNiLODLevel, , false, kParams_OneInt);
DEFINE_COMMAND_PLUGIN(GetNiLODLevel, , false, nullptr);
DEFINE_COMMAND_PLUGIN(UpdateScenegraph, , true, kParams_ScenegraphUpdate);
DEFINE_COMMAND_PLUGIN(GetNiBound, , true, kParams_OneOptionalString);

namespace {
	enum class AlphaPropertyItem  : int32_t {
		NONE				= -1,
		BLEND_TOGGLE,		
		SOURCE_BLEND_MODE,
		DEST_BLEND_MODE,
		TEST_TOGGLE,
		TEST_FUNC,
		TEST_REF,
		COUNT
	};

	enum class StencilPropertyItem : int32_t {
		NONE				= -1,
		ENABLED_TOGGLE,
		DRAW_MODE,
		REF_VALUE,
		MASK_VALUE,
		FAIL_ACTION,
		ZFAIL_ACTION,
		PASS_ACTION,
		TEST_FUNC,
		COUNT
	};

	enum class NiUpdateType : int32_t {
		NONE		= -1,
		FULL,
		SELECTED,
		TRANSFORMS_AND_BOUNDS,
		PROPERTIES,
		CONTROLLERS,
		COUNT
	};

	template<typename T>
	inline bool InRange(volatile T value) {
		return value > T::NONE && value < T::COUNT;
	}

	NiProperty* __fastcall GetPropertyByName(NiAVObject* apRoot, const NiFixedString& arObjectName, uint32_t aeType) {
		if (!apRoot)
			return nullptr;

		NiAVObject* pObject = BSUtilities::GetObjectByName(apRoot, arObjectName);
		if (!pObject)
			return nullptr;

		return pObject->GetProperty(aeType);
	}
}

bool Cmd_SetAlphaPropertyValue_Execute(COMMAND_ARGS) {
	*result = 0;
	AlphaPropertyItem eItem = AlphaPropertyItem::NONE;
	uint32_t uiValue = 0;
	char cObjectName[MAX_PATH] = {};
	if (ExtractArgsEx(EXTRACT_ARGS_EX, cObjectName, &eItem, &uiValue) && cObjectName[0] && InRange(eItem)) {
		NiAlphaProperty* pAlpha = static_cast<NiAlphaProperty*>(GetPropertyByName(thisObj->Get3D(), cObjectName, NiProperty::kPropertyType_Alpha));
		if (!pAlpha)
			return true;

		switch (eItem) {
			case AlphaPropertyItem::BLEND_TOGGLE:
				pAlpha->SetAlphaBlending(uiValue != 0);
				break;
			case AlphaPropertyItem::SOURCE_BLEND_MODE:
				pAlpha->SetSrcBlendMode(static_cast<NiAlphaProperty::AlphaFunction>(uiValue));
				break;
			case AlphaPropertyItem::DEST_BLEND_MODE:
				pAlpha->SetDestBlendMode(static_cast<NiAlphaProperty::AlphaFunction>(uiValue));
				break;
			case AlphaPropertyItem::TEST_TOGGLE:
				pAlpha->SetAlphaTesting(uiValue != 0);
				break;
			case AlphaPropertyItem::TEST_FUNC:
				pAlpha->SetTestMode(static_cast<NiAlphaProperty::TestFunction>(uiValue));
				break;
			case AlphaPropertyItem::TEST_REF:
				pAlpha->SetTestRef(static_cast<uint8_t>(uiValue));
				break;
			default:
				__assume(0);
		}
		*result = 1;
	}
	return true;
}

bool Cmd_GetAlphaPropertyValue_Execute(COMMAND_ARGS) {
	*result = 0;
	AlphaPropertyItem eItem = AlphaPropertyItem::NONE;
	char cObjectName[MAX_PATH] = {};
	if (ExtractArgsEx(EXTRACT_ARGS_EX, cObjectName, &eItem) && cObjectName[0] && InRange(eItem)) {
		NiAlphaProperty* pAlpha = static_cast<NiAlphaProperty*>(GetPropertyByName(thisObj->Get3D(), cObjectName, NiProperty::kPropertyType_Alpha));
		if (!pAlpha)
			return true;

		switch (eItem) {
			case AlphaPropertyItem::BLEND_TOGGLE:
				*result = pAlpha->GetAlphaBlending() ? 1 : 0;
				break;
			case AlphaPropertyItem::SOURCE_BLEND_MODE:
				*result = pAlpha->GetSrcBlendMode();
				break;
			case AlphaPropertyItem::DEST_BLEND_MODE:
				*result = pAlpha->GetDestBlendMode();
				break;
			case AlphaPropertyItem::TEST_TOGGLE:
				*result = pAlpha->GetAlphaTesting() ? 1 : 0;
				break;
			case AlphaPropertyItem::TEST_FUNC:
				*result = pAlpha->GetTestMode();
				break;
			case AlphaPropertyItem::TEST_REF:
				*result = pAlpha->GetTestRef();
				break;
			default:
				__assume(0);
		}
	}
	return true;
}

bool Cmd_SetStencilPropertyValue_Execute(COMMAND_ARGS) {
	*result = 0;
	StencilPropertyItem eItem = StencilPropertyItem::NONE;
	uint32_t uiValue = 0;
	char cObjectName[MAX_PATH] = {};
	if (ExtractArgsEx(EXTRACT_ARGS_EX, cObjectName, &eItem, &uiValue) && cObjectName[0] && InRange(eItem)) {
		NiStencilProperty* pStencil = static_cast<NiStencilProperty*>(GetPropertyByName(thisObj->Get3D(), cObjectName, NiProperty::kPropertyType_Stencil));
		if (!pStencil)
			return true;

		switch (eItem) {
			case StencilPropertyItem::ENABLED_TOGGLE:
				pStencil->SetStencilOn(uiValue != 0);
				break;
			case StencilPropertyItem::DRAW_MODE:
				pStencil->SetDrawMode(static_cast<NiStencilProperty::DrawMode>(uiValue));
				break;
			case StencilPropertyItem::REF_VALUE:
				pStencil->SetStencilReference(static_cast<uint8_t>(uiValue));
				break;
			case StencilPropertyItem::MASK_VALUE:
				pStencil->SetStencilMask(static_cast<uint8_t>(uiValue));
				break;
			case StencilPropertyItem::FAIL_ACTION:
				pStencil->SetStencilFailAction(static_cast<NiStencilProperty::Action>(uiValue));
				break;
			case StencilPropertyItem::ZFAIL_ACTION:
				pStencil->SetStencilZFailAction(static_cast<NiStencilProperty::Action>(uiValue));
				break;
			case StencilPropertyItem::PASS_ACTION:
				pStencil->SetStencilPassAction(static_cast<NiStencilProperty::Action>(uiValue));
				break;
			case StencilPropertyItem::TEST_FUNC:
				pStencil->SetStencilFunction(static_cast<NiStencilProperty::TestFunc>(uiValue));
				break;
			default:
				__assume(0);
		}
		*result = 1;
	}
	return true;
}

bool Cmd_GetStencilPropertyValue_Execute(COMMAND_ARGS) {
	*result = 0;
	StencilPropertyItem eItem = StencilPropertyItem::NONE;
	char cObjectName[MAX_PATH] = {};
	if (ExtractArgsEx(EXTRACT_ARGS_EX, cObjectName, &eItem) && cObjectName[0] && InRange(eItem)) {
		NiStencilProperty* pStencil = static_cast<NiStencilProperty*>(GetPropertyByName(thisObj->Get3D(), cObjectName, NiProperty::kPropertyType_Stencil));
		if (!pStencil)
			return true;

		switch (eItem) {
			case StencilPropertyItem::ENABLED_TOGGLE:
				*result = pStencil->GetStencilOn() ? 1 : 0;
				break;
			case StencilPropertyItem::DRAW_MODE:
				*result = pStencil->GetDrawMode();
				break;
			case StencilPropertyItem::REF_VALUE:
				*result = pStencil->GetStencilReference();
				break;
			case StencilPropertyItem::MASK_VALUE:
				*result = pStencil->GetStencilMask();
				break;
			case StencilPropertyItem::FAIL_ACTION:
				*result = pStencil->GetStencilFailAction();
				break;
			case StencilPropertyItem::ZFAIL_ACTION:
				*result = pStencil->GetStencilZFailAction();
				break;
			case StencilPropertyItem::PASS_ACTION:
				*result = pStencil->GetStencilPassAction();
				break;
			case StencilPropertyItem::TEST_FUNC:
				*result = pStencil->GetStencilFunction();
				break;
			default:
				__assume(0);
		}
	}
	return true;
}

bool Cmd_SetSwitchNodeIndex_Execute(COMMAND_ARGS) {
	*result = 0;
	char cObjectName[MAX_PATH] = {};
	int32_t iIndex = 0;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, cObjectName, &iIndex) && cObjectName[0]) {
		NiAVObject* pObject = BSUtilities::GetObjectByName(thisObj->Get3D(), cObjectName);
		if (pObject && pObject->IsExactKindOf<NiSwitchNode>()) {
			static_cast<NiSwitchNode*>(pObject)->SetIndex(iIndex);
			*result = 1;
		}
	}
	return true;
}

bool Cmd_GetSwitchNodeIndex_Execute(COMMAND_ARGS) {
	*result = 0;
	char cObjectName[MAX_PATH] = {};
	if (ExtractArgsEx(EXTRACT_ARGS_EX, cObjectName) && cObjectName[0]) {
		NiAVObject* pObject = BSUtilities::GetObjectByName(thisObj->Get3D(), cObjectName);
		if (pObject && pObject->IsExactKindOf<NiSwitchNode>())
			*result = static_cast<NiSwitchNode*>(pObject)->GetIndex();
	}
	return true;
}

bool Cmd_SetNiLODLevel_Execute(COMMAND_ARGS) {
	*result = 0;
	int32_t iLevel = -1;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &iLevel)) {
		NiLODNode::ms_iGlobalLOD = iLevel;
		*result = 1;
	}
	return true;
}

bool Cmd_GetNiLODLevel_Execute(COMMAND_ARGS) {
	*result = NiLODNode::ms_iGlobalLOD;
	return true;
}

bool Cmd_UpdateScenegraph_Execute(COMMAND_ARGS) {
	*result = 0;
	NiUpdateType eType = NiUpdateType::NONE;
	float fTime = FLT_MAX;
	BOOL bUpdateControllers = FALSE;
	char cName[MAX_PATH] = {};
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &eType, &fTime, &bUpdateControllers, &cName) && InRange<NiUpdateType>(eType)) {
		NiAVObject* pRoot = thisObj->Get3D();

		NiAVObject* pTarget = nullptr;
		if (cName[0])
			pTarget = BSUtilities::GetObjectByName(pRoot, cName);
		else
			pTarget = pRoot;

		if (pTarget) {
			NiUpdateData kData(fTime != FLT_MAX ? fTime : 0.f, bUpdateControllers, AILinearTaskThreadManager::ShouldQueue3DTask());
			switch (eType) {
				case NiUpdateType::FULL:
					pTarget->Update(kData);
					break;
				case NiUpdateType::SELECTED:
					pTarget->UpdateSelected(kData);
					break;
				case NiUpdateType::TRANSFORMS_AND_BOUNDS:
					pTarget->UpdateTransformAndBounds(kData);
					break;
				case NiUpdateType::PROPERTIES:
					pTarget->UpdateProperties();
					break;
				case NiUpdateType::CONTROLLERS:
					pTarget->UpdateControllers(kData);
					break;
				default:
					__assume(0);
			}
			*result = 1;
		}
	}
	return true;
}

bool Cmd_GetNiBound_Execute(COMMAND_ARGS) {
	*result = 0;
	char cName[MAX_PATH] = {};
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &cName)) {
		NiAVObject* pRoot = thisObj->Get3D();

		NiAVObject* pTarget = nullptr;
		if (cName[0])
			pTarget = BSUtilities::GetObjectByName(pRoot, cName);
		else
			pTarget = pRoot;

		NVSEArrayElement kElements[4];
		NVSEArrayVar* pOutArray;
		if (pTarget) {
			const NiBound& rBound = pTarget->GetWorldBound();
			kElements[0] = rBound.kCenter.x;
			kElements[1] = rBound.kCenter.y;
			kElements[2] = rBound.kCenter.z;
			kElements[3] = rBound.fRadius;
			pOutArray = g_arrInterface->CreateArray(kElements, 4, scriptObj);
		}
		else {
			kElements[0] = 0.f;
			kElements[1] = 0.f;
			kElements[2] = 0.f;
			kElements[3] = 0.f;
			pOutArray = g_arrInterface->CreateArray(kElements, 4, scriptObj);
		}
		g_arrInterface->AssignCommandResult(pOutArray, result);
	}
	return true;
}