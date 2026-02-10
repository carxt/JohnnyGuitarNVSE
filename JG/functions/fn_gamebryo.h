#pragma once

#include "Bethesda/BSUtilities.hpp"

DEFINE_COMMAND_PLUGIN(SetAlphaPropertyValue, , true, kParams_OneString_TwoInts);
DEFINE_COMMAND_PLUGIN(GetAlphaPropertyValue, , true, kParams_OneString_OneInt);
DEFINE_COMMAND_PLUGIN(SetStencilPropertyValue, , true, kParams_OneString_TwoInts);
DEFINE_COMMAND_PLUGIN(GetStencilPropertyValue, , true, kParams_OneString_OneInt);

namespace {
	enum class AlphaPropertyItem  : uint32_t {
		NONE				= 0,
		BLEND_TOGGLE,		
		SOURCE_BLEND_MODE,
		DEST_BLEND_MODE,
		TEST_TOGGLE,
		TEST_FUNC,
		TEST_REF,
	};

	enum class StencilPropertyItem : uint32_t {
		NONE				= 0,
		ENABLED_TOGGLE,
		DRAW_MODE,
		REF_VALUE,
		MASK_VALUE,
		FAIL_ACTION,
		ZFAIL_ACTION,
		PASS_ACTION,
		TEST_FUNC,
	};

	enum class MaterialPropertyItem : uint32_t {
		NONE = 0,
		SPECULAR_COLOR,
		EMISSIVE_COLOR,
		SHINE_POWER,
		ALPHA,
		EMISSIVE_MULT,
	};

	NiProperty* __fastcall GetPropertyByName(NiAVObject* apRoot, const NiFixedString& apObjectName, uint32_t aeType) {
		if (!apRoot)
			return nullptr;

		NiAVObject* pObject = BSUtilities::GetObjectByName(apRoot, apObjectName);
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
	if (ExtractArgsEx(EXTRACT_ARGS_EX, cObjectName, &eItem, &uiValue)) {
		NiAlphaProperty* pAlpha = static_cast<NiAlphaProperty*>(GetPropertyByName(thisObj->GetNiNode(), cObjectName, NiProperty::kPropertyType_Alpha));
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
				return true;
		}
		*result = 1;
	}
	return true;
}

bool Cmd_GetAlphaPropertyValue_Execute(COMMAND_ARGS) {
	*result = 0;
	AlphaPropertyItem eItem = AlphaPropertyItem::NONE;
	char cObjectName[MAX_PATH] = {};
	if (ExtractArgsEx(EXTRACT_ARGS_EX, cObjectName, &eItem)) {
		NiAlphaProperty* pAlpha = static_cast<NiAlphaProperty*>(GetPropertyByName(thisObj->GetNiNode(), cObjectName, NiProperty::kPropertyType_Alpha));
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
				return true;
		}
	}
	return true;
}

bool Cmd_SetStencilPropertyValue_Execute(COMMAND_ARGS) {
	*result = 0;
	StencilPropertyItem eItem = StencilPropertyItem::NONE;
	uint32_t uiValue = 0;
	char cObjectName[MAX_PATH] = {};
	if (ExtractArgsEx(EXTRACT_ARGS_EX, cObjectName, &eItem, &uiValue)) {
		NiStencilProperty* pStencil = static_cast<NiStencilProperty*>(GetPropertyByName(thisObj->GetNiNode(), cObjectName, NiProperty::kPropertyType_Stencil));
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
				return true;
		}
		*result = 1;
	}
	return true;
}

bool Cmd_GetStencilPropertyValue_Execute(COMMAND_ARGS) {
	*result = 0;
	StencilPropertyItem eItem = StencilPropertyItem::NONE;
	char cObjectName[MAX_PATH] = {};
	if (ExtractArgsEx(EXTRACT_ARGS_EX, cObjectName, &eItem)) {
		NiStencilProperty* pStencil = static_cast<NiStencilProperty*>(GetPropertyByName(thisObj->GetNiNode(), cObjectName, NiProperty::kPropertyType_Stencil));
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
				return true;
		}
		*result = 1;
	}
	return true;
}