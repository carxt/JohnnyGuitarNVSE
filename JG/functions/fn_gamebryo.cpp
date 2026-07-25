#include "fn_gamebryo.h"

#include "Gamebryo/NiParticleSystem.hpp"
#include "Gamebryo/NiPSysBoxEmitter.hpp"
#include "Gamebryo/NiPSysEmitter.hpp"
#include "Gamebryo/NiPSysModifier.hpp"
#include "Bethesda/BSWindModifier.hpp"

#include <JG/TaskQueue.hpp>
#include <GameTasks.h>

#include "JG/ScriptUtils.hpp"
using namespace ScriptUtils;

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
	SHADER_PROPERTIES,
	HAVOK_SYNC_BOTH,
	HAVOK_SYNC_TO,
	HAVOK_SYNC_FROM,
	COUNT
};

enum class ParticleModifierItem : int32_t {
	NONE = -1,

	// NiPSysModifier
	ORDER,
	ACTIVE,

	// NiPSysEmitter
	EMITTER_SPEED,
	EMITTER_SPEED_VAR,
	EMITTER_DECLINATION,
	EMITTER_DECLINATION_VAR,
	EMITTER_PLANAR_ANGLE,
	EMITTER_PLANAR_ANGLE_VAR,
	EMITTER_INITIAL_COLOR_RED,
	EMITTER_INITIAL_COLOR_GREEN,
	EMITTER_INITIAL_COLOR_BLUE,
	EMITTER_INITIAL_COLOR_ALPHA,
	EMITTER_INITIAL_RADIUS,
	EMITTER_RADIUS_VAR,
	EMITTER_LIFESPAN,
	EMITTER_LIFESPAN_VAR,
	EMITTER_SCALE,

	// NiPSysBoxEmitter
	BOX_EMITTER_WIDTH,
	BOX_EMITTER_HEIGHT,
	BOX_EMITTER_DEPTH,

	// BSWindModifier

	WIND_MODIFIER_STRENGTH,

	COUNT
};

enum class LightItem : int32_t {
	NONE = -1,
	DIMMER,
	RADIUS,
	OUTER_SPOT_ANGLE,
	INNER_SPOT_ANGLE,
	SPOT_EXPONENT,
	COUNT
};

enum class LightColorItem : int32_t {
	NONE = -1,
	DIFFUSE,
	AMBIENT,
	COUNT
};

static std::pair<NiProperty*, NiAVObject*> __fastcall GetPropertyByName(const NiAVObject* apRoot, const char* apObjectName, uint32_t aeType) {
	NiAVObject* pObject = BSUtilities::GetObjectByName(apRoot, apObjectName);
	if (!pObject)
		return { nullptr, nullptr };

	return { pObject->GetProperty(aeType), pObject };
}

static NiParticleSystem* __fastcall GetParticleSystemByName(const NiAVObject* apRoot, const char* apObjectName) {
	NiAVObject* pObject = BSUtilities::GetObjectByName(apRoot, apObjectName);
	if (!pObject)
		return nullptr;

	return pObject->NiDynamicCast<NiParticleSystem>();
}

static void __fastcall InvalidateRenderPassesRecurse(const NiAVObject* apObject) {
	BSShaderProperty* pShaderProp = static_cast<BSShaderProperty*>(apObject->GetProperty(NiProperty::kPropertyType_Shade));
	if (pShaderProp)
		pShaderProp->InvalidateState();

	if (apObject->IsNode()) {
		const NiNode* pNode = static_cast<const NiNode*>(apObject);
		for (uint32_t i = 0; i < pNode->GetArrayCount(); ++i) {
			const NiAVObject* pChild = pNode->GetAt(i);
			if (pChild)
				InvalidateRenderPassesRecurse(pChild);
		}
	}
}

static void __fastcall InvalidateRenderPasses(NiAVObject* apObject, bool abQueue = AILinearTaskThreadManager::ShouldQueue3DTask()) {
	if (abQueue) [[unlikely]] {
		QueuedTask kTask;
		kTask.kItems[0].p = apObject;
		apObject->IncRefCount();
		kTask.pFunction = QUEUED_TASK{
			NiAVObject* pObject = reinterpret_cast<NiAVObject*>(arTask.kItems[0].p);
			InvalidateRenderPassesRecurse(pObject);
			pObject->DecRefCount();
		};
		TaskQueue::QueueTask(kTask);
	}
	else {
		InvalidateRenderPassesRecurse(apObject);
	}
}

static void __fastcall SynchronizeHavok(NiAVObject* apObject, bhkNiCollisionObject::SyncMode aeSyncMode, bool abQueue = AILinearTaskThreadManager::ShouldQueue3DTask()) {
	if (abQueue) [[unlikely]] {
		QueuedTask kTask;
		kTask.kItems[0].p = apObject;
		kTask.kItems[1].ui = aeSyncMode;
		apObject->IncRefCount();
		kTask.pFunction = QUEUED_TASK{
			NiAVObject * pObject = reinterpret_cast<NiAVObject*>(arTask.kItems[0].p);
			const bhkNiCollisionObject::SyncMode eSyncMode = static_cast<bhkNiCollisionObject::SyncMode>(arTask.kItems[1].ui);
			bhkNiCollisionObject::Synchronize(pObject, eSyncMode);
			pObject->DecRefCount();
		};
		TaskQueue::QueueTask(kTask);
	}
	else {
		bhkNiCollisionObject::Synchronize(apObject, aeSyncMode);
	}
}

bool Cmd_SetAlphaPropertyValue_Execute(COMMAND_ARGS) {
	*result = 0;
	AlphaPropertyItem eItem = AlphaPropertyItem::NONE;
	uint32_t uiValue = 0;
	char cObjectName[MAX_PATH] = {};
	BOOL bFirstPerson = FALSE;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, cObjectName, &eItem, &uiValue, &bFirstPerson) && cObjectName[0] && InRange(eItem)) {
		auto kObjects = GetPropertyByName(GetReferenceScene(thisObj, bFirstPerson), cObjectName, NiProperty::kPropertyType_Alpha);
		NiAlphaProperty* pAlpha = static_cast<NiAlphaProperty*>(kObjects.first);
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

		InvalidateRenderPasses(kObjects.second);

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
		auto kObjects = GetPropertyByName(GetReferenceScene(thisObj, bFirstPerson), cObjectName, NiProperty::kPropertyType_Alpha);
		const NiAlphaProperty* pAlpha = static_cast<NiAlphaProperty*>(kObjects.first);
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
		auto kObjects = GetPropertyByName(GetReferenceScene(thisObj, bFirstPerson), cObjectName, NiProperty::kPropertyType_Stencil);
		NiStencilProperty* pStencil = static_cast<NiStencilProperty*>(kObjects.first);
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

		InvalidateRenderPasses(kObjects.second);

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
		auto kObjects = GetPropertyByName(GetReferenceScene(thisObj, bFirstPerson), cObjectName, NiProperty::kPropertyType_Stencil);
		const NiStencilProperty* pStencil = static_cast<NiStencilProperty*>(kObjects.first);
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
		NiAVObject* pObject = BSUtilities::GetObjectByName(GetReferenceScene(thisObj, bFirstPerson), cObjectName);
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
		const NiAVObject* pObject = BSUtilities::GetObjectByName(GetReferenceScene(thisObj, bFirstPerson), cObjectName);
		if (pObject && pObject->IsExactKindOf<NiSwitchNode>())
			*result = static_cast<const NiSwitchNode*>(pObject)->GetIndex();
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
	BOOL bFirstPerson = FALSE;
	char cName[MAX_PATH] = {};
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &eType, &fTime, &bUpdateControllers, &cName, &bFirstPerson) && InRange<NiUpdateType>(eType)) {
		NiAVObject* pRoot = GetReferenceScene(thisObj, bFirstPerson);

		NiAVObject* pTarget = nullptr;
		if (cName[0])
			pTarget = BSUtilities::GetObjectByName(pRoot, cName);
		else
			pTarget = pRoot;

		if (pTarget) {
			const bool bQueue = AILinearTaskThreadManager::ShouldQueue3DTask();
			NiUpdateData kData(fTime != FLT_MAX ? fTime : 0.f, bUpdateControllers, bQueue);
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
			case NiUpdateType::SHADER_PROPERTIES:
				InvalidateRenderPasses(pTarget, bQueue);
				break;
			case NiUpdateType::HAVOK_SYNC_BOTH:
				SynchronizeHavok(pTarget, bhkNiCollisionObject::SYNC_BOTH, bQueue);
				break;
			case NiUpdateType::HAVOK_SYNC_TO:
				SynchronizeHavok(pTarget, bhkNiCollisionObject::SYNC_TO_HAVOK, bQueue);
				break;
			case NiUpdateType::HAVOK_SYNC_FROM:
				SynchronizeHavok(pTarget, bhkNiCollisionObject::SYNC_FROM_HAVOK, bQueue);
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
		const NiAVObject* pRoot = GetReferenceScene(thisObj, bFirstPerson);

		const NiAVObject* pTarget = nullptr;
		if (cName[0])
			pTarget = BSUtilities::GetObjectByName(pRoot, cName);
		else
			pTarget = pRoot;

		if (pTarget && pTarget->m_pWorldBound) {
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
	*result = 0;
	char cSequenceName[MAX_PATH] = { 0 };
	char cObjectName[MAX_PATH] = { 0 };
	BOOL bFirstPerson = FALSE;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &cSequenceName, &cObjectName, &bFirstPerson) && cSequenceName[0]) {
		const NiAVObject* pRoot = GetReferenceScene(thisObj, bFirstPerson);
		if (pRoot) {
			const NiAVObject* pTarget = pRoot;
			if (cObjectName[0])
				pTarget = BSUtilities::GetObjectByName(pRoot, cObjectName);

			if (pTarget) {
				NiControllerManager* pCtrlMgr = pTarget->GetController<NiControllerManager>();
				if (pCtrlMgr) {
					*result = pCtrlMgr->IsSequenceActive(cSequenceName);
					if (IsConsoleMode())
						Console_Print("IsNiSequenceActive >> %s: %s", cSequenceName, *result ? "true" : "false");
				}
				else if (IsConsoleMode()) {
					Console_Print("Controller not found");
				}
			}
			else if (IsConsoleMode()) {
				Console_Print("Block not found: %s", cObjectName);
			}
		}
		else if (IsConsoleMode()) {
			Console_Print("Root node not found");
		}
	}
	return true;
}

bool Cmd_StopNiSequence_Execute(COMMAND_ARGS) {
	*result = 0;
	char cSequenceName[MAX_PATH] = { 0 };
	float fEaseOutTime = 0.f;
	char cObjectName[MAX_PATH] = { 0 };
	BOOL bFirstPerson = FALSE;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &cSequenceName, &fEaseOutTime, &cObjectName, &bFirstPerson) && cSequenceName[0]) {
		const NiAVObject* pRoot = GetReferenceScene(thisObj, bFirstPerson);
		if (pRoot) {
			const NiAVObject* pTarget = pRoot;
			if (cObjectName[0])
				pTarget = BSUtilities::GetObjectByName(pRoot, cObjectName);

			if (pTarget) {
				NiControllerManager* pCtrlMgr = pTarget->GetController<NiControllerManager>();
				if (pCtrlMgr) {
					NiControllerSequence* pSequence = pCtrlMgr->GetSequenceByName(cSequenceName);
					if (pSequence)
						*result = pCtrlMgr->DeactivateSequence(pSequence, fEaseOutTime);
				}
			}
		}
	}
	return true;
}

bool Cmd_SetNiPSysModifierValue_Execute(COMMAND_ARGS) {
	*result = 0;
	char cObjectName[MAX_PATH] = { 0 };
	ParticleModifierItem eItem = ParticleModifierItem::NONE;
	float fValue = FLT_MAX;
	BOOL bFirstPerson = FALSE;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &cObjectName, &eItem, &fValue, &bFirstPerson) && cObjectName[0] && InRange(eItem)) {
		NiParticleSystem* pSys = GetParticleSystemByName(GetReferenceScene(thisObj, bFirstPerson), cObjectName);
		if (!pSys)
			return true;
			
		pSys->m_kModifierList.ForEach([=](const NiPSysModifierPtr& spModifier, int) {
			switch (eItem) {
				case ParticleModifierItem::ORDER:
					// TODO: Should we edit the list?
					return;
				case ParticleModifierItem::ACTIVE:
					spModifier->SetActive(fValue > 0.f);
					return;
				default:
					break;
			}

			if (auto pEmitter = spModifier->NiDynamicCast<NiPSysEmitter>()) {
				switch (eItem) {
					case ParticleModifierItem::EMITTER_SPEED:
						pEmitter->m_fSpeed = fValue;
						return;
					case ParticleModifierItem::EMITTER_SPEED_VAR:
						pEmitter->m_fSpeedVar = fValue;
						return;
					case ParticleModifierItem::EMITTER_DECLINATION:
						pEmitter->m_fDeclination = fValue;
						return;
					case ParticleModifierItem::EMITTER_DECLINATION_VAR:
						pEmitter->m_fDeclinationVar = fValue;
						return;
					case ParticleModifierItem::EMITTER_PLANAR_ANGLE:
						pEmitter->m_fPlanarAngle = fValue;
						return;
					case ParticleModifierItem::EMITTER_PLANAR_ANGLE_VAR:
						pEmitter->m_fPlanarAngleVar = fValue;
						return;
					case ParticleModifierItem::EMITTER_INITIAL_COLOR_RED:
						pEmitter->m_kInitialColor.r = fValue;
						return;
					case ParticleModifierItem::EMITTER_INITIAL_COLOR_GREEN:
						pEmitter->m_kInitialColor.g = fValue;
						return;
					case ParticleModifierItem::EMITTER_INITIAL_COLOR_BLUE:
						pEmitter->m_kInitialColor.b = fValue;
						return;
					case ParticleModifierItem::EMITTER_INITIAL_COLOR_ALPHA:
						pEmitter->m_kInitialColor.a = fValue;
						return;
					case ParticleModifierItem::EMITTER_INITIAL_RADIUS:
						pEmitter->m_fInitialRadius = fValue;
						return;
					case ParticleModifierItem::EMITTER_RADIUS_VAR:
						pEmitter->m_fRadiusVar = fValue;
						return;
					case ParticleModifierItem::EMITTER_LIFESPAN:
						pEmitter->m_fLifeSpan = fValue;
						return;
					case ParticleModifierItem::EMITTER_LIFESPAN_VAR:
						pEmitter->m_fLifeSpanVar = fValue;
						return;
					case ParticleModifierItem::EMITTER_SCALE:
						pEmitter->m_fScale = fValue;
						return;
					default:
						break;
				}
			}

			if (auto pBoxEmitter = spModifier->NiDynamicCast<NiPSysBoxEmitter>()) {
				switch (eItem) {
					case ParticleModifierItem::BOX_EMITTER_WIDTH:
						pBoxEmitter->m_fEmitterWidth = fValue;
						return;
					case ParticleModifierItem::BOX_EMITTER_HEIGHT:
						pBoxEmitter->m_fEmitterHeight = fValue;
						return;
					case ParticleModifierItem::BOX_EMITTER_DEPTH:
						pBoxEmitter->m_fEmitterDepth = fValue;
						return;
					default:
						break;
				}
			}

			if (const auto pWindModifier = spModifier->NiDynamicCast<BSWindModifier>()) {
				switch (eItem) {
					case ParticleModifierItem::WIND_MODIFIER_STRENGTH:
						pWindModifier->fStrength = fValue;
						return;
					default:
						break;
				}
			}
		});
	}
	return true;
}

bool Cmd_GetNiPSysModifierValue_Execute(COMMAND_ARGS) {
	char cObjectName[MAX_PATH] = { 0 };
	ParticleModifierItem eItem = ParticleModifierItem::NONE;
	BOOL bFirstPerson = FALSE;
	*result = 0.0;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &cObjectName, &eItem, &bFirstPerson) && cObjectName[0] && InRange(eItem)) {
		NiParticleSystem* pSys = GetParticleSystemByName(GetReferenceScene(thisObj, bFirstPerson), cObjectName);
		if (!pSys)
			return true;

		pSys->m_kModifierList.ForEach([=](const NiPSysModifierPtr& spModifier, int) {
			switch (eItem) {
				case ParticleModifierItem::ORDER:
					*result = spModifier->m_uiOrder;
					return;
				case ParticleModifierItem::ACTIVE:
					*result = spModifier->m_bActive;
					return;
				default:
					break;
			}

			if (const auto pEmitter = spModifier->NiDynamicCast<NiPSysEmitter>()) {
				switch (eItem) {
					case ParticleModifierItem::EMITTER_SPEED:
						*result = pEmitter->m_fSpeed;
						return;
					case ParticleModifierItem::EMITTER_SPEED_VAR:
						*result = pEmitter->m_fSpeedVar;
						return;
					case ParticleModifierItem::EMITTER_DECLINATION:
						*result = pEmitter->m_fDeclination;
						return;
					case ParticleModifierItem::EMITTER_DECLINATION_VAR:
						*result = pEmitter->m_fDeclinationVar;
						return;
					case ParticleModifierItem::EMITTER_PLANAR_ANGLE:
						*result = pEmitter->m_fPlanarAngle;
						return;
					case ParticleModifierItem::EMITTER_PLANAR_ANGLE_VAR:
						*result = pEmitter->m_fPlanarAngleVar;
						return;
					case ParticleModifierItem::EMITTER_INITIAL_COLOR_RED:
						*result = pEmitter->m_kInitialColor.r;
						return;
					case ParticleModifierItem::EMITTER_INITIAL_COLOR_GREEN:
						*result = pEmitter->m_kInitialColor.g;
						return;
					case ParticleModifierItem::EMITTER_INITIAL_COLOR_BLUE:
						*result = pEmitter->m_kInitialColor.b;
						return;
					case ParticleModifierItem::EMITTER_INITIAL_COLOR_ALPHA:
						*result = pEmitter->m_kInitialColor.a;
						return;
					case ParticleModifierItem::EMITTER_INITIAL_RADIUS:
						*result = pEmitter->m_fInitialRadius;
						return;
					case ParticleModifierItem::EMITTER_RADIUS_VAR:
						*result = pEmitter->m_fRadiusVar;
						return;
					case ParticleModifierItem::EMITTER_LIFESPAN:
						*result = pEmitter->m_fLifeSpan;
						return;
					case ParticleModifierItem::EMITTER_LIFESPAN_VAR:
						*result = pEmitter->m_fLifeSpanVar;
						return;
					case ParticleModifierItem::EMITTER_SCALE:
						*result = pEmitter->m_fScale;
						return;
					default:
						break;
				}
			}

			if (const auto pBoxEmitter = spModifier->NiDynamicCast<NiPSysBoxEmitter>()) {
				switch (eItem) {
					case ParticleModifierItem::BOX_EMITTER_WIDTH:
						*result = pBoxEmitter->m_fEmitterWidth;
						return;
					case ParticleModifierItem::BOX_EMITTER_HEIGHT:
						*result = pBoxEmitter->m_fEmitterHeight;
						return;
					case ParticleModifierItem::BOX_EMITTER_DEPTH:
						*result = pBoxEmitter->m_fEmitterDepth;
						return;
					default:
						break;
				}
			}

			if (const auto pWindModifier = spModifier->NiDynamicCast<BSWindModifier>()) {
				switch (eItem) {
					case ParticleModifierItem::WIND_MODIFIER_STRENGTH:
						*result = pWindModifier->fStrength;
						return;
					default:
						break;
				}
			}
		});
	}
	return true;
}

bool Cmd_SetBlockTransform_Execute(COMMAND_ARGS) {
	float x, y, z, w;
	BOOL bRotate = FALSE;
	BOOL bWorld = FALSE;
	BOOL bFirstPerson = FALSE;
	uint32_t eModifier = 0;
	char cBlockName[128] = {};

	*result = false;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &cBlockName, &x, &y, &z, &w, &bRotate, &bWorld, &eModifier, &bFirstPerson)) {
		NiAVObject* pObject = BSUtilities::GetObjectByName(GetReferenceScene(thisObj, bFirstPerson), cBlockName);
		if (bWorld) {
			if (bRotate) {
				pObject->m_kWorld.m_kRotate.FromEulerAnglesXYZ(x, y, z);
			}
			else {
				pObject->m_kWorld.m_kTranslate.x = x;
				pObject->m_kWorld.m_kTranslate.y = y;
				pObject->m_kWorld.m_kTranslate.z = z;
			}

			if (w >= 0.f)
				pObject->m_kWorld.m_fScale = w;
		}
		else {
			if (bRotate) {
				pObject->m_kLocal.m_kRotate.FromEulerAnglesXYZ(x, y, z);
			}
			else {
				pObject->m_kLocal.m_kTranslate.x = x;
				pObject->m_kLocal.m_kTranslate.y = y;
				pObject->m_kLocal.m_kTranslate.z = z;
			}
			
			if (w >= 0.f)
				pObject->m_kLocal.m_fScale = w;
		}

		*result = true;
	}
	return true;
}

bool Cmd_SetParticleEmitterSpawnRate_Execute(COMMAND_ARGS) {
	*result = 0;
	char cObjectName[MAX_PATH] = {};
	float fValue = 1.f;
	BOOL bFirstPerson = FALSE;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, cObjectName, &fValue, &bFirstPerson)) {
		NiParticleSystem* pSys = GetParticleSystemByName(GetReferenceScene(thisObj, bFirstPerson), cObjectName);
		if (pSys) {
			NiPSysEmitterCtlr* pEmitterCtrl = pSys->GetController<NiPSysEmitterCtlr>();
			if (pEmitterCtrl) {
				NiFloatInterpolator* pInterp = pEmitterCtrl->GetBirthRateInterpolator();
				if (pInterp) {
					pInterp->m_fFloatValue = fValue;
					*result = 1;
				}
			}
		}
	}
	return true;
}

bool Cmd_GetParticleEmitterSpawnRate_Execute(COMMAND_ARGS) {
	*result = 0;
	char cObjectName[MAX_PATH] = {};
	BOOL bFirstPerson = FALSE;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, cObjectName, &bFirstPerson)) {
		NiParticleSystem* pSys = GetParticleSystemByName(GetReferenceScene(thisObj, bFirstPerson), cObjectName);
		if (pSys) {
			NiPSysEmitterCtlr* pEmitterCtrl = pSys->GetController<NiPSysEmitterCtlr>();
			if (pEmitterCtrl) {
				NiFloatInterpolator* pInterp = pEmitterCtrl->GetBirthRateInterpolator();
				if (pInterp)
					*result = pInterp->m_fFloatValue;
			}
		}
	}
	return true;
}

bool Cmd_SetNiLightValue_Execute(COMMAND_ARGS) {
	*result = 0;
	LightItem eItem = LightItem::NONE;
	float fValue = 0;
	char cObjectName[MAX_PATH] = {};
	BOOL bFirstPerson = FALSE;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, cObjectName, &eItem, &fValue, &bFirstPerson) && cObjectName[0] && InRange(eItem)) {
		NiObject* pObject = BSUtilities::GetObjectByName(GetReferenceScene(thisObj, bFirstPerson), cObjectName);
		if (!pObject)
			return true;

		NiLight* pLight = pObject->NiDynamicCast<NiLight>();
		if (!pLight)
			return true;

		NiSpotLight* pSpotLight = nullptr;
		if (eItem >= LightItem::OUTER_SPOT_ANGLE && eItem <= LightItem::SPOT_EXPONENT) {
			pSpotLight = pLight->NiDynamicCast<NiSpotLight>();
			if (!pSpotLight)
				return true;
		}

		switch (eItem) {
			case LightItem::DIMMER:
				pLight->SetDimmer(fValue);
				break;
			case LightItem::RADIUS:
				pLight->SetLightRadius(fValue);
				break;
			case LightItem::OUTER_SPOT_ANGLE:
				pSpotLight->SetOuterSpotAngle(fValue);
				break;
			case LightItem::INNER_SPOT_ANGLE:
				pSpotLight->SetInnerSpotAngle(fValue);
				break;
			case LightItem::SPOT_EXPONENT:
				pSpotLight->SetSpotExponent(fValue);
				break;
			default:
				__assume(0);
		}

		*result = 1;
	}
	return true;
}

bool Cmd_GetNiLightValue_Execute(COMMAND_ARGS) {
	*result = 0;
	LightItem eItem = LightItem::NONE;
	char cObjectName[MAX_PATH] = {};
	BOOL bFirstPerson = FALSE;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, cObjectName, &eItem, &bFirstPerson) && cObjectName[0] && InRange(eItem)) {
		NiObject* pObject = BSUtilities::GetObjectByName(GetReferenceScene(thisObj, bFirstPerson), cObjectName);
		if (!pObject)
			return true;

		NiLight* pLight = pObject->NiDynamicCast<NiLight>();
		if (!pLight)
			return true;

		NiSpotLight* pSpotLight = nullptr;
		if (eItem >= LightItem::OUTER_SPOT_ANGLE && eItem <= LightItem::SPOT_EXPONENT) {
			pSpotLight = pLight->NiDynamicCast<NiSpotLight>();
			if (!pSpotLight)
				return true;
		}

		switch (eItem) {
			case LightItem::DIMMER:
				*result = pLight->GetDimmer();
				break;
			case LightItem::RADIUS:
				*result = pLight->GetLightRadius();
				break;
			case LightItem::OUTER_SPOT_ANGLE:
				*result = pSpotLight->GetOuterSpotAngle();
				break;
			case LightItem::INNER_SPOT_ANGLE:
				*result = pSpotLight->GetInnerSpotAngle();
				break;
			case LightItem::SPOT_EXPONENT:
				*result = pSpotLight->GetSpotExponent();
				break;
			default:
				__assume(0);
		}
	}
	return true;
}

bool Cmd_SetNiLightColor_Execute(COMMAND_ARGS) {
	*result = 0;
	LightColorItem eItem = LightColorItem::NONE;
	NiColor kColor;
	char cObjectName[MAX_PATH] = {};
	BOOL bFirstPerson = FALSE;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, cObjectName, &eItem, &kColor.r, &kColor.g, &kColor.b, &bFirstPerson) && cObjectName[0] && InRange(eItem)) {
		NiObject* pObject = BSUtilities::GetObjectByName(GetReferenceScene(thisObj, bFirstPerson), cObjectName);
		if (!pObject)
			return true;

		NiLight* pLight = pObject->NiDynamicCast<NiLight>();
		if (!pLight)
			return true;

		switch (eItem) {
			case LightColorItem::DIFFUSE:
				pLight->SetDiffuseColor(kColor);
				break;
			case LightColorItem::AMBIENT:
				pLight->SetAmbientColor(kColor);
				break;
			default:
				__assume(0);
		}

		*result = 1;
	}

	return true;
}

bool Cmd_GetNiLightColor_Execute(COMMAND_ARGS) {
	*result = 0;

	ScriptVar* pRed = nullptr;
	ScriptVar* pGreen = nullptr;
	ScriptVar* pBlue = nullptr;

	LightColorItem eItem = LightColorItem::NONE;
	char cObjectName[MAX_PATH] = {};
	BOOL bFirstPerson = FALSE;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, cObjectName, &eItem, &pRed, &pGreen, &pBlue, &bFirstPerson) && cObjectName[0] && InRange(eItem)) {
		ASSUME_ASSERT(pRed && pGreen && pBlue);
		NiObject* pObject = BSUtilities::GetObjectByName(GetReferenceScene(thisObj, bFirstPerson), cObjectName);
		if (!pObject)
			return true;

		NiLight* pLight = pObject->NiDynamicCast<NiLight>();
		if (!pLight)
			return true;

		NiColor kColor;
		switch (eItem) {
			case LightColorItem::DIFFUSE:
				kColor = pLight->GetDiffuseColor();
				break;
			case LightColorItem::AMBIENT:
				kColor = pLight->GetAmbientColor();
				break;
			default:
				__assume(0);
		}

		pRed->data = kColor.r;
		pGreen->data = kColor.g;
		pBlue->data = kColor.b;

		if (IsConsoleMode())
			Console_Print("GetNiLightColor %i >> %f %f %f", eItem, kColor.r, kColor.g, kColor.b);

		*result = 1;
	}

	return true;
}