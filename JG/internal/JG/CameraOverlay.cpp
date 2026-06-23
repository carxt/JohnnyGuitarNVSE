#include "CameraOverlay.hpp"
#include <GameObjects.h>
#include <GameUI.h>
#include <GameSettings.h>

#include "Bethesda/BSRenderedTexture.hpp"
#include "Bethesda/BSShaderUtil.hpp"
#include "Bethesda/BSShaderManager.hpp"
#include "Bethesda/TESMain.hpp"
#include "Bethesda/TimeGlobal.hpp"

#pragma comment(lib, "d3d9.lib")

namespace Utils {
	class AutoLightOffset {
		ShadowSceneNode* pSceneNode;
		NiPoint3 kOrgEyePos;
	public:
		AutoLightOffset(ShadowSceneNode* apSceneNode) {
			pSceneNode = apSceneNode;
			NiNode* pCameraRoot = TESMain::GetWorldSceneGraph()->GetCameraRoot();
			if (pCameraRoot) {
				kOrgEyePos = apSceneNode->kEyePos;
				apSceneNode->kEyePos = NiPoint3::ZERO;
				apSceneNode->kLightingOffset = -pCameraRoot->m_kWorld.m_kTranslate;
			}
		}
		~AutoLightOffset() {
			pSceneNode->kEyePos = kOrgEyePos;
			pSceneNode->kLightingOffset = NiPoint3::ZERO;
		}
	};

	class AutoObjectOffset {
		NiAVObject* pObject;
		NiMatrix3	kLocalRot;
	public:
		AutoObjectOffset(NiAVObject* apObject) : pObject(apObject) {
			kLocalRot = pObject->m_kLocal.m_kRotate;

			NiNode* pParent = pObject->GetParent();
			if (pParent) {
				const NiMatrix3 kWorldRot = pObject->m_kWorld.m_kRotate;

				pParent->DetachChild(pObject);

				pObject->m_kLocal.m_kRotate = kWorldRot;

				NiUpdateData kData;
				pObject->UpdateTransformAndBounds(kData);
			}
		}
		~AutoObjectOffset() {
			pObject->m_kLocal.m_kRotate = kLocalRot;
		}
	};

	void __fastcall RenderScene(NiAVObject* apScene, NiCamera* apCamera, BSShaderAccumulator* apAccumulator) {
		BSCullingProcess* pCuller = TESMain::GetWorldSceneGraph()->pCuller;

		pCuller->PushCullMode(BS_CULLING_TYPE::ALL_PASS);
		pCuller->SetCamera(apCamera);
		pCuller->SetAccumulator(apAccumulator);

		BSShaderUtil::AccumulateScene(apCamera, apScene, pCuller);
		BSShaderUtil::RenderScene(apCamera, apAccumulator);

		pCuller->SetAccumulator(nullptr);
		pCuller->SetCamera(nullptr);
		pCuller->PopCullMode();
	}

	void __fastcall UpdateAnimManager(NiControllerManager* apManager, TESObjectREFR* apOwner) {
		uint32_t uiPlayingAnims = 0;
		for (uint32_t i = 0; i < apManager->GetSequenceCount(); ++i) {
			NiControllerSequence* pSequence = apManager->GetSequenceAt(i);
			if (pSequence && pSequence->GetState() != NiControllerSequence::AnimState::INACTIVE) {
				if (BSAnimGroupSequence::PlaySounds(pSequence, apOwner))
					apManager->DeactivateSequence(pSequence, 0.f);
				else
					++uiPlayingAnims;
			}
		}

		if (!uiPlayingAnims)
			apManager->SetActive(false);
	}

	void __fastcall UpdateAnimsRecurse(NiAVObject* apObject, TESObjectREFR* apRef) {
		NiControllerManager* pManager = apObject->GetController<NiControllerManager>();
		if (pManager && pManager->GetActive()) [[unlikely]] {
			UpdateAnimManager(pManager, apRef);
		}

		if (apObject->IsNode()) [[likely]] {
			const NiNode* pNode = static_cast<NiNode*>(apObject);
			if (pNode->GetChildCount()) {
				for (uint32_t i = 0; i < pNode->GetArrayCount(); ++i) {
					NiAVObject* pChild = pNode->GetAt(i);
					if (pChild)
						UpdateAnimsRecurse(pChild, apRef);
				}
			}
		}
	}
}

namespace CameraOverlay {

	// TODO: Render to a dedicated MSAA RT for PostIS, PreUI/PostUI

#pragma region Enums
	struct _OverlayTypes {
		enum Types {
			PRE_IMAGESPACE,
			POST_IMAGESPACE,
			PRE_INTERFACE,
			POST_INTERFACE,
			COUNT,
		};
	};
	using OverlayTypes = _OverlayTypes::Types;

	struct _CameraVariants {
		enum Variants {
			NORMAL,
			ORTHO,
			COUNT,
		};
	};
	using CameraVariants = _CameraVariants::Variants;
#pragma endregion

	static float fUpdateTime = 0.f;
	static NiPointer<NiNode>	spSceneOverlayRoot;
	static NiPointer<BSShaderAccumulator> spAccumulator;
	static NiPointer<NiCamera>  spCameras[CameraVariants::COUNT];

	CustomGameSetting kJG_OverrideLighting;
	CustomGameSetting kJG_OverrideLightingValues;
	CustomGameSetting kJG_SunlightColor_R;
	CustomGameSetting kJG_SunlightColor_G;
	CustomGameSetting kJG_SunlightColor_B;
	CustomGameSetting kJG_SunlightDir_X;
	CustomGameSetting kJG_SunlightDir_Y;
	CustomGameSetting kJG_SunlightDir_Z;
	CustomGameSetting kJG_AmbientColor_R;
	CustomGameSetting kJG_AmbientColor_G;
	CustomGameSetting kJG_AmbientColor_B;
	
	static constexpr const char cBaseRefName[] = "JG_CameraOverlayRef";

	static constexpr const char* pOverlaySuffixes[OverlayTypes::COUNT] = {
		"PreIS",
		"PostIS",
		"PreUI",
		"PostUI",
	};

	struct Overlay {
		TESObjectREFR*		pReference = nullptr;

		NiNode* GetRoot() const {
			return static_cast<NiNode*>(pReference->Get3DSimple());
		}

		NiNode* __fastcall Initialize(const char* apName) {
			pReference = BSMemory::create<TESObjectREFR, 0x55A2F0>();
			pReference->SetFormEditorID(apName);

			// Pseudo temporary
			// We avoid calling SetTemporary as it removes the form from EDID and FormID maps, and invalides the FormID
			// Having the flag is enough to prevent it from saving
			pReference->uiFormFlags.Set(TESForm::FormFlags::TEMPORARY);

			char cRootName[256];
			strcpy_s(cRootName, apName);
			strcat_s(cRootName, "_RootNode");

			BSFadeNode* pRoot = BSFadeNode::CreateObject();
			pRoot->SetName(cRootName);
			pRoot->pLinkedObj = pReference;
			pRoot->TurnFadeNodeOn();
			pRoot->SetAlwaysDraw(true);
			pRoot->SetIgnoreFade(true);

			pReference->Set3DVerySimple(pRoot);

			return pRoot;
		}

		void __fastcall Reset() {
			if (pReference) {
				NiAVObject* pRoot = GetRoot();
				if (pRoot) {
					NiNode* pParent = pRoot->GetParent();
					if (pParent)
						pParent->DetachChild(pRoot);
				}

				pReference->Set3DVerySimple(nullptr);
				pReference->uiFormFlags.Clear(TESForm::FormFlags::TEMPORARY);
				delete pReference;
				pReference = nullptr;
			}
		}

		void __fastcall Update(NiNode* apParent, float afTime) {
			if (!pReference)
				return;

			NiNode* pScene = static_cast<NiNode*>(GetRoot());
			if (!pScene)
				return;

			const bool bHasChildren = pScene->GetChildCount();

			NiUpdateData kData(afTime, bHasChildren);
			pScene->Update(kData);

			if (bHasChildren) {
				Utils::UpdateAnimsRecurse(pScene, pReference);
				BSShaderManager::GetShadowSceneNode(0)->UpdateObjectLighting(pScene, false);
			}
		}
	
		bool __fastcall Render(NiRenderTargetGroup* apRenderTarget, NiCamera* apCamera, BSShaderAccumulator* apAccumulator, uint32_t aeClearFlags) const {
			if (!pReference || !apCamera) [[unlikely]]
				return false;

			NiNode* pScene = static_cast<NiNode*>(GetRoot());
			if (!pScene || !pScene->GetChildCount())
				return false;

			const bool bEmptyFrame = BSRenderedTexture::IsOutsideFrame();
			
#ifdef _DEBUG
			D3DPERF_BeginEvent(0, L"Overlay Render");
#endif

			if (bEmptyFrame)
				BSRenderedTexture::StartOffscreen(aeClearFlags, apRenderTarget);
			else
				BSRenderedTexture::Begin(apRenderTarget, aeClearFlags);

			Utils::RenderScene(pScene, apCamera, apAccumulator);

			if (bEmptyFrame)
				BSRenderedTexture::StopOffscreen();
			else
				BSRenderedTexture::End();

#ifdef _DEBUG
			D3DPERF_EndEvent();
#endif

			return true;
		}
	};

	static Overlay kOverlays[OverlayTypes::COUNT][CameraVariants::COUNT];

	bool __fastcall RenderOverlay(BSRenderedTexture* apTexture, uint32_t aeOverlay) {
		bool bRendered = false;
		if (spSceneOverlayRoot && spSceneOverlayRoot->GetChildCount()) [[likely]] {
			{
				bool bHasChildren = false;
				for (uint32_t i = 0; i < CameraVariants::COUNT; ++i) {
					auto& rOverlay = kOverlays[aeOverlay][i];
					if (rOverlay.pReference) {
						NiNode* pRoot = rOverlay.GetRoot();
						if (pRoot)
							bHasChildren |= pRoot->GetChildCount() != 0;
					}
				}

				if (!bHasChildren)
					return bRendered;
			}

			ShadowSceneNode* pSceneNode = BSShaderManager::GetShadowSceneNode(BSShaderManager::SceneGraphType::WORLD);

			spAccumulator->pActiveShadowSceneNode = pSceneNode;

			NiDirectionalLight* pSunLight = static_cast<NiDirectionalLight*>(pSceneNode->pSunLight->spLight.m_pObject);
			NiColor& rDiff = pSunLight->m_kDiff;
			NiColor& rAmbient = pSunLight->m_kAmb;
			NiMatrix3 kSunRot = pSunLight->m_kLocal.m_kRotate;

			const NiColor kOrgDiffuse = rDiff;
			const NiColor kOrgAmbient = rAmbient;
			const NiMatrix3 kOrgSunRot = kSunRot;
			const bool bOverrideLight = kJG_OverrideLighting.Bitfield().GetBit(aeOverlay);
			if (bOverrideLight) {
				const Bitfield32& rFlags = kJG_OverrideLightingValues.Bitfield();
				if (rFlags.GetBit(0)) {
					rDiff.r = kJG_SunlightColor_R.Float();
					rDiff.g = kJG_SunlightColor_G.Float();
					rDiff.b = kJG_SunlightColor_B.Float();
				}

				if (rFlags.GetBit(1)) {
					rAmbient.r = kJG_AmbientColor_R.Float();
					rAmbient.g = kJG_AmbientColor_G.Float();
					rAmbient.b = kJG_AmbientColor_B.Float();
				}

				if (rFlags.GetBit(2)) {
					NiPoint3 kSunDir;
					kSunDir.x = kJG_SunlightDir_X.Float();
					kSunDir.y = kJG_SunlightDir_Y.Float();
					kSunDir.z = kJG_SunlightDir_Z.Float();

					kSunDir.Unitize();

					pSunLight->m_kLocal.m_kRotate.SetCol(0, kSunDir);

					NiUpdateData kData;
					pSunLight->UpdateWorldData(kData);
				}
			}

			Utils::AutoObjectOffset kCamMover(spSceneOverlayRoot);
			Utils::AutoLightOffset kOffset(pSceneNode);

			NiRenderTargetGroup* pRenderTarget = apTexture ? apTexture->GetGroup() : nullptr;

			constexpr uint32_t uiClearFlags = NiRenderer::CLEAR_ZBUFFER | NiRenderer::CLEAR_STENCIL;
			for (uint32_t i = 0; i < CameraVariants::COUNT; ++i) {
				bRendered |= kOverlays[aeOverlay][i].Render(pRenderTarget, spCameras[i], spAccumulator, uiClearFlags);
			}

			if (bOverrideLight) {
				pSunLight->m_kDiff = kOrgDiffuse;
				pSunLight->m_kAmb = kOrgAmbient;
				pSunLight->m_kLocal.m_kRotate = kOrgSunRot;
				NiUpdateData kData;
				pSunLight->UpdateWorldData(kData);
			}
		}
		return bRendered;
	}

	template <uint32_t auiAddress, int32_t aiOffset>
	class RenderHookDetour {
	public:
		static inline HookUtils::CallDetour kDetour;

		template <int32_t aiOffset>
		static bool __cdecl RenderHook() {
			uint8_t* pEBP = GetParentBasePtr(_AddressOfReturnAddress());
			BSRenderedTexture* pTexture = *reinterpret_cast<BSRenderedTexture**>(pEBP + aiOffset);
			RenderOverlay(pTexture, OverlayTypes::PRE_IMAGESPACE);
			return CdeclCall<bool>(kDetour);
		}

		RenderHookDetour() {
			kDetour.ReplaceCall(auiAddress, RenderHook<aiOffset>);
		}	
	};

	HookUtils::CallDetour kPostISRenderDetour;
	bool __cdecl PostISRenderHook() {
		RenderOverlay(nullptr, OverlayTypes::POST_IMAGESPACE);
		return CdeclCall<bool>(kPostISRenderDetour);
	}

	HookUtils::CallDetour kRenderUIDetour;
	class InterfaceRender : public InterfaceManager {
	public:
		void RenderUIHook(BSCullingProcess* apCuller, bool abPipboyVisible) {
			if (BSRenderedTexture::IsOutsideFrame() || Interface::IsLoadingMenuVisible()) [[unlikely]] {
				ThisCall(kRenderUIDetour, this, apCuller, abPipboyVisible);
			}
			else [[likely]] {
				RenderOverlay(nullptr, OverlayTypes::PRE_INTERFACE);

				const bool bCursorCulled = pCursorRoot->GetAppCulled();
				if (pCursorRoot)
					pCursorRoot->SetAppCulled(true);

				ThisCall(kRenderUIDetour, this, apCuller, abPipboyVisible);

				RenderOverlay(nullptr, OverlayTypes::POST_INTERFACE);

				if (pCursorRoot) {
					pCursorRoot->SetAppCulled(bCursorCulled);

					Utils::RenderScene(pCursorRoot, spSceneGraph->spCamera, spInterfaceAccum);
				}
			}
		}
	};


	static NiCamera* CreateCamera(bool abOrtho) {
		constexpr float fFOV = 85.f;

		NiCamera* pCamera = NiCamera::CreateObject();
		pCamera->SetName(abOrtho ? "JG_OverlayOrthoCamera" : "JG_OverlayCamera");

		const NiDX9Renderer* pRenderer = BSShaderManager::GetRenderer();
		const uint32_t uiHeight = pRenderer->GetScreenHeight();
		const uint32_t uiWidth = pRenderer->GetScreenWidth();

		const float fAspectRatio = static_cast<float>(uiHeight) / static_cast<float>(uiWidth);
		const float fAspectMult = 0.75f / fAspectRatio;
		const float fTan = tan(fFOV * 0.01745329238474369f * 0.5f);

		NiFrustum kFrustum;
		kFrustum.m_fLeft = -fTan * fAspectMult;
		kFrustum.m_fRight = fTan * fAspectMult;
		kFrustum.m_fTop = fTan * fAspectRatio * fAspectMult;
		kFrustum.m_fBottom = -fTan * fAspectRatio * fAspectMult;
		kFrustum.m_fNear = 0.001f;
		kFrustum.m_fFar = 10000.f;
		kFrustum.m_bOrtho = abOrtho;
		pCamera->m_fMaxFarNearRatio = kFrustum.m_fFar / kFrustum.m_fNear;
		pCamera->SetViewFrustum(kFrustum);

		pCamera->LookAtWorldPoint(NiPoint3::UNIT_Y, NiPoint3::UNIT_Z);

		return pCamera;
	}

	void InitializeAccumulator() {
		spAccumulator = BSShaderAccumulator::Create();

		// Free unused data
		BSMemory::free(spAccumulator->ppOcclusionQueries);
		spAccumulator->ppOcclusionQueries = nullptr;
		spAccumulator->usQuerySize = 0;

		BSMemory::free(spAccumulator->pInstanceRenderer);
		spAccumulator->pInstanceRenderer = nullptr;
	}

	void __fastcall InitializeCameras(NiNode* apRoot) {
		for (uint32_t i = 0; i < CameraVariants::COUNT; ++i) {
			spCameras[i] = CreateCamera(i == CameraVariants::ORTHO);
			apRoot->AttachChild(spCameras[i], true);
		}
	}

	void __fastcall InitializeReferences(NiNode* apRoot) {
		char cNameBuffer[256];
		for (uint32_t i = 0; i < OverlayTypes::COUNT; ++i) {
			for (uint32_t j = 0; j < CameraVariants::COUNT; ++j) {
				our_snprintf(cNameBuffer, sizeof(cNameBuffer), "%s_%s%s", cBaseRefName, pOverlaySuffixes[i], j ? "_O" : "");
				apRoot->AttachChild(kOverlays[i][j].Initialize(cNameBuffer), true);
			}
		}
	}

	void __fastcall InitializeGameSettings() {
		kJG_OverrideLighting.Initialize("iJG_Overlay_OverrideLighting", 0);
		kJG_OverrideLightingValues.Initialize("iJG_OverrideLightingValues", 0);
		kJG_SunlightColor_R.Initialize("fJG_Overlay_SunlightColor_R", 1.f);
		kJG_SunlightColor_G.Initialize("fJG_Overlay_SunlightColor_G", 1.f);
		kJG_SunlightColor_B.Initialize("fJG_Overlay_SunlightColor_B", 1.f);
		kJG_SunlightDir_X.Initialize("fJG_Overlay_SunlightDir_X", 0.f);
		kJG_SunlightDir_Y.Initialize("fJG_Overlay_SunlightDir_Y", 0.f);
		kJG_SunlightDir_Z.Initialize("fJG_Overlay_SunlightDir_Z", 0.f);
		kJG_AmbientColor_R.Initialize("fJG_Overlay_AmbientColor_R", 1.f);
		kJG_AmbientColor_G.Initialize("fJG_Overlay_AmbientColor_G", 1.f);
		kJG_AmbientColor_B.Initialize("fJG_Overlay_AmbientColor_B", 1.f);
	}

	void Install() {
		InitializeGameSettings();

		RenderHookDetour<0x8710C4, -0x28>(); // Normal
		RenderHookDetour<0x870B69, -0x1C>(); // Wireframe
		RenderHookDetour<0x87096C, -0x14>(); // PipBoy

		kPostISRenderDetour.ReplaceCall(0x8703F1, PostISRenderHook);
		kRenderUIDetour.ReplaceCall(0x7144D3, &InterfaceRender::RenderUIHook);
	}

	void Init() {
		constexpr uint32_t uiChildCount = (OverlayTypes::COUNT * CameraVariants::COUNT) + CameraVariants::COUNT;
		spSceneOverlayRoot = NiNode::Create(uiChildCount);
		spSceneOverlayRoot->SetName("JG_CameraOverlaySceneRoot");
		spSceneOverlayRoot->SetAlwaysDraw(true);
		spSceneOverlayRoot->SetFixedBound(true);
		spSceneOverlayRoot->SetAppCulled(true);

		InitializeCameras(spSceneOverlayRoot);

		InitializeAccumulator();

		spSceneOverlayRoot->Update();
	}

	void ReInit() {
		InitializeReferences(spSceneOverlayRoot);

		spSceneOverlayRoot->Update();
	}

	void Update() {
		if (spSceneOverlayRoot) {
			NiNode* pCameraRoot = TESMain::GetWorldSceneGraph()->GetCameraRoot();
			if (pCameraRoot && !spSceneOverlayRoot->GetParent())
				pCameraRoot->AttachChild(spSceneOverlayRoot, true);

			fUpdateTime += TimeGlobal::GetSingleton()->fDelta;

			for (uint32_t i = 0; i < OverlayTypes::COUNT; ++i) {
				for (uint32_t j = 0; j < CameraVariants::COUNT; ++j) {
					kOverlays[i][j].Update(spSceneOverlayRoot, fUpdateTime);
				}
			}
		}
	}

	void Reset() {
		for (uint32_t i = 0; i < OverlayTypes::COUNT; ++i) {
			for (uint32_t j = 0; j < CameraVariants::COUNT; ++j) {
				kOverlays[i][j].Reset();
			}
		}

		spSceneOverlayRoot->Update();
	}
}