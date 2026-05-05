#include "fn_gamebryo.h"

#include "Gamebryo/NiParticleSystem.hpp"
#include "Gamebryo/NiPSysBoxEmitter.hpp"
#include "Gamebryo/NiPSysEmitter.hpp"
#include "Gamebryo/NiPSysModifier.hpp"

enum class AlphaPropertyItem : int32_t {
	NONE = -1,
	BLEND_TOGGLE,
	SOURCE_BLEND_MODE,
	DEST_BLEND_MODE,
	TEST_TOGGLE,
	TEST_FUNC,
	TEST_REF,
	COUNT
};

enum class StencilPropertyItem : int32_t {
	NONE = -1,
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
	NONE = -1,
	FULL,
	SELECTED,
	BOUNDS,
	TRANSFORMS_AND_BOUNDS,
	PROPERTIES,
	CONTROLLERS,
	COUNT
};

NiAVObject* __fastcall GetRoot(TESObjectREFR* apRef, bool abFirstPerson) {
	if (apRef == PlayerCharacter::GetSingleton())
		return static_cast<PlayerCharacter*>(apRef)->Get3D(abFirstPerson);
	else
		return apRef->Get3D();
}

NiProperty* __fastcall GetPropertyByName(NiAVObject* apRoot, const NiFixedString& arObjectName, uint32_t aeType) {
	NiAVObject* pObject = BSUtilities::GetObjectByName(apRoot, arObjectName);
	if (!pObject)
		return nullptr;

	return pObject->GetProperty(aeType);
}

bool Cmd_SetAlphaPropertyValue_Execute(COMMAND_ARGS) {
	*result = 0;
	AlphaPropertyItem eItem = AlphaPropertyItem::NONE;
	uint32_t uiValue = 0;
	char cObjectName[MAX_PATH] = {};
	BOOL bFirstPerson = FALSE;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, cObjectName, &eItem, &uiValue, &bFirstPerson) && cObjectName[0] && InRange(eItem)) {
		NiAlphaProperty* pAlpha = static_cast<NiAlphaProperty*>(GetPropertyByName(GetRoot(thisObj, bFirstPerson), cObjectName, NiProperty::kPropertyType_Alpha));
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
	BOOL bFirstPerson = FALSE;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, cObjectName, &eItem, &bFirstPerson) && cObjectName[0] && InRange(eItem)) {
		NiAlphaProperty* pAlpha = static_cast<NiAlphaProperty*>(GetPropertyByName(GetRoot(thisObj, bFirstPerson), cObjectName, NiProperty::kPropertyType_Alpha));
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
	BOOL bFirstPerson = FALSE;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, cObjectName, &eItem, &uiValue, &bFirstPerson) && cObjectName[0] && InRange(eItem)) {
		NiStencilProperty* pStencil = static_cast<NiStencilProperty*>(GetPropertyByName(GetRoot(thisObj, bFirstPerson), cObjectName, NiProperty::kPropertyType_Stencil));
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
	BOOL bFirstPerson = FALSE;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, cObjectName, &eItem, &bFirstPerson) && cObjectName[0] && InRange(eItem)) {
		NiStencilProperty* pStencil = static_cast<NiStencilProperty*>(GetPropertyByName(GetRoot(thisObj, bFirstPerson), cObjectName, NiProperty::kPropertyType_Stencil));
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
	BOOL bFirstPerson = FALSE;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, cObjectName, &iIndex, &bFirstPerson) && cObjectName[0]) {
		NiAVObject* pObject = BSUtilities::GetObjectByName(GetRoot(thisObj, bFirstPerson), cObjectName);
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
	BOOL bFirstPerson = FALSE;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, cObjectName, &bFirstPerson) && cObjectName[0]) {
		NiAVObject* pObject = BSUtilities::GetObjectByName(GetRoot(thisObj, bFirstPerson), cObjectName);
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
	BOOL bFirstPerson = FALSE;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &eType, &fTime, &bUpdateControllers, &cName, &bFirstPerson) && InRange<NiUpdateType>(eType)) {
		NiAVObject* pRoot = GetRoot(thisObj, bFirstPerson);

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
			case NiUpdateType::BOUNDS:
				pTarget->UpdateWorldBound();
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
	BOOL bFirstPerson = FALSE;

	NVSEArrayElement kElements[4];
	NVSEArrayVar* pOutArray;

	bool bValid = false;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &cName, &bFirstPerson)) {
		NiAVObject* pRoot = GetRoot(thisObj, bFirstPerson);

		NiAVObject* pTarget = nullptr;
		if (cName[0])
			pTarget = BSUtilities::GetObjectByName(pRoot, cName);
		else
			pTarget = pRoot;

		if (pTarget) {
			const NiBound& rBound = pTarget->GetWorldBound();
			kElements[0] = rBound.kCenter.x;
			kElements[1] = rBound.kCenter.y;
			kElements[2] = rBound.kCenter.z;
			kElements[3] = rBound.fRadius;
			pOutArray = g_arrInterface->CreateArray(kElements, 4, scriptObj);
			bValid = true;
		}
	}

	if (!bValid) {
		kElements[0] = 0.f;
		kElements[1] = 0.f;
		kElements[2] = 0.f;
		kElements[3] = 0.f;
		pOutArray = g_arrInterface->CreateArray(kElements, 4, scriptObj);
	}

	g_arrInterface->AssignCommandResult(pOutArray, result);
	return true;
}

bool Cmd_IsNiSequenceActive_Execute(COMMAND_ARGS) {
	char sequenceName[MAX_PATH] = { 0 };
	char blockName[MAX_PATH] = { 0 };
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &sequenceName, &blockName)) {
		NiNode* root = thisObj->Get3D();
		if (root) {
			NiAVObject* target = root;
			if (blockName[0])
				target = BSUtilities::GetObjectByName(root, blockName);

			if (target) {
				const NiRTTI* NiControllerManager_ms_RTTI = reinterpret_cast<NiRTTI*>(0x11F36AC);
				NiControllerManager* controller = static_cast<NiControllerManager*>(target->GetController(NiControllerManager_ms_RTTI));
				if (controller) {
					*result = controller->IsSequenceActive(sequenceName);
					if (IsConsoleMode())
						Console_Print("IsNiSequenceActive >> %s: %s", sequenceName, *result ? "true" : "false");
				}
				else if (IsConsoleMode()) {
					Console_Print("Controller not found");
				}
			}
			else if (IsConsoleMode()) {
				Console_Print("Block not found: %s", blockName);
			}
		}
		else if (IsConsoleMode()) {
			Console_Print("Root node not found");
		}
	}
	return true;
}

bool Cmd_SetNiPSysEmitterValue_Execute(COMMAND_ARGS) {
	char blockName[MAX_PATH] = { 0 };
	uint32_t valueId{};
	float newValue{};
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &blockName, &valueId, &newValue)) {
		const auto root = thisObj->Get3D();
		if (!root) {
			if (IsConsoleMode()) {
				Console_Print("Root node not found");
			}

			return true;
		}

		const NiAVObject* target = root;
		if (blockName[0]) {
			target = BSUtilities::GetObjectByName(root, blockName);
		}

		if (!target) {
			if (IsConsoleMode()) {
				Console_Print("Block not found: %s", blockName);
			}

			return true;
		}

		const auto pSys = target->NiDynamicCast<NiParticleSystem>();
		if (!pSys) {
			if (IsConsoleMode()) {
				Console_Print("Particle system not found");
			}

			return true;
		}

		pSys->m_kModifierList.ForEach([=](const NiPSysModifierPtr& pModifier, int) {
			if (const auto pEmitter = pModifier->NiDynamicCast<NiPSysEmitter>()) {
				switch (valueId) {
				case 1:
					pEmitter->m_fSpeed = newValue;
					break;
				case 2:
					pEmitter->m_fSpeedVar = newValue;
					break;
				case 3:
					pEmitter->m_fDeclination = newValue;
					break;
				case 4:
					pEmitter->m_fDeclinationVar = newValue;
					break;
				case 5:
					pEmitter->m_fPlanarAngle = newValue;
					break;
				case 6:
					pEmitter->m_fPlanarAngleVar = newValue;
					break;
				case 7:
					pEmitter->m_kInitialColor.r = newValue;
					break;
				case 8:
					pEmitter->m_kInitialColor.g = newValue;
					break;
				case 9:
					pEmitter->m_kInitialColor.b = newValue;
					break;
				case 10:
					pEmitter->m_kInitialColor.a = newValue;
					break;
				case 11:
					pEmitter->m_fInitialRadius = newValue;
					break;
				case 12:
					pEmitter->m_fRadiusVar = newValue;
					break;
				case 13:
					pEmitter->m_fLifeSpan = newValue;
					break;
				case 14:
					pEmitter->m_fLifeSpanVar = newValue;
					break;
				case 15:
					pEmitter->m_fScale = newValue;
					break;
				default:
					if (const auto pBoxEmitter = pModifier->NiDynamicCast<NiPSysBoxEmitter>()) {
						if (valueId == 16) {
							pBoxEmitter->m_fEmitterWidth = newValue;
							return;
						}

						if (valueId == 17) {
							pBoxEmitter->m_fEmitterHeight = newValue;
							return;
						}

						if (valueId == 18) {
							pBoxEmitter->m_fEmitterDepth = newValue;
							return;
						}
					}

					if (IsConsoleMode()) {
						Console_Print("Unknown value id: %d", valueId);
					}

					break;
				}
			}
			});
	}
	return true;
}

bool Cmd_GetNiPSysEmitterValue_Execute(COMMAND_ARGS) {
	char blockName[MAX_PATH] = { 0 };
	uint32_t valueId{};
	*result = 0.0;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &blockName, &valueId)) {
		const auto root = thisObj->Get3D();
		if (!root) {
			if (IsConsoleMode()) {
				Console_Print("Root node not found");
			}

			return true;
		}

		const NiAVObject* target = root;
		if (blockName[0]) {
			target = BSUtilities::GetObjectByName(root, blockName);
		}

		if (!target) {
			if (IsConsoleMode()) {
				Console_Print("Block not found: %s", blockName);
			}

			return true;
		}

		const auto pSys = target->NiDynamicCast<NiParticleSystem>();
		if (!pSys) {
			if (IsConsoleMode()) {
				Console_Print("Particle system not found");
			}

			return true;
		}

		pSys->m_kModifierList.ForEach([=](const NiPSysModifierPtr& pModifier, int) {
			if (const auto pEmitter = pModifier->NiDynamicCast<NiPSysEmitter>()) {
				switch (valueId) {
				case 1:
					*result = pEmitter->m_fSpeed;
					break;
				case 2:
					*result = pEmitter->m_fSpeedVar;
					break;
				case 3:
					*result = pEmitter->m_fDeclination;
					break;
				case 4:
					*result = pEmitter->m_fDeclinationVar;
					break;
				case 5:
					*result = pEmitter->m_fPlanarAngle;
					break;
				case 6:
					*result = pEmitter->m_fPlanarAngleVar;
					break;
				case 7:
					*result = pEmitter->m_kInitialColor.r;
					break;
				case 8:
					*result = pEmitter->m_kInitialColor.g;
					break;
				case 9:
					*result = pEmitter->m_kInitialColor.b;
					break;
				case 10:
					*result = pEmitter->m_kInitialColor.a;
					break;
				case 11:
					*result = pEmitter->m_fInitialRadius;
					break;
				case 12:
					*result = pEmitter->m_fRadiusVar;
					break;
				case 13:
					*result = pEmitter->m_fLifeSpan;
					break;
				case 14:
					*result = pEmitter->m_fLifeSpanVar;
					break;
				case 15:
					*result = pEmitter->m_fScale;
					break;
				default:
					if (const auto pBoxEmitter = pModifier->NiDynamicCast<NiPSysBoxEmitter>()) {
						if (valueId == 16) {
							*result = pBoxEmitter->m_fEmitterWidth;
							return;
						}

						if (valueId == 17) {
							*result = pBoxEmitter->m_fEmitterHeight;
							return;
						}

						if (valueId == 18) {
							*result = pBoxEmitter->m_fEmitterDepth;
							return;
						}
					}

					if (IsConsoleMode()) {
						Console_Print("Unknown value id: %d", valueId);
					}

					break;
				}
			}
			});
	}
	return true;
}