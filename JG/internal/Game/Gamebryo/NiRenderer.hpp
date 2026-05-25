#pragma once

#include "NiObject.hpp"
#include "NiCriticalSection.hpp"
#include "NiRect.hpp"
#include "NiAccumulator.hpp"

class NiShader;
class NiDynamicEffectState;
class NiRenderedCubeMap;
class NiDX9Renderer;
class NiPropertyState;
class NiRenderTargetGroup;
class NiFrustum;
class NiCamera;
class NiPoint3;

class NiRenderer : public NiObject {
public:
	NiRenderer();
	virtual ~NiRenderer();

	enum ClearFlags {
		CLEAR_NONE			= 0,
		CLEAR_BACKBUFFER	= 1 << 0,
		CLEAR_STENCIL		= 1 << 1,
		CLEAR_ZBUFFER		= 1 << 2,
		CLEAR_ALL = CLEAR_BACKBUFFER | CLEAR_STENCIL | CLEAR_ZBUFFER
	};

	struct _FrameState {
		enum State {
			OUTSIDE_FRAME			= 0,
			INSIDE_FRAME			= 1,
			INSIDE_OFFSCREEN_FRAME	= 2,
			WAITING_FOR_DISPLAY		= 3,
			INTERNAL_FRAME			= 4,
		};
	};
	using FrameState = _FrameState::State;

	virtual void	DoMinimalFlip();

	NiPointer<NiAccumulator>		m_spAccum;
	NiPropertyState*				m_pkCurrProp;
	NiDynamicEffectState*			m_pkCurrEffects;
	NiPointer<NiShader>				m_spErrorShader;
	NiCriticalSection				m_kRendererLock;
	NiCriticalSection				m_kPrecacheCriticalSection;
	NiCriticalSection				m_kSourceDataCriticalSection;
	FrameState						m_eFrameState;
	uint32_t						m_uiFrameID;
	bool							m_bRenderTargetGroupActive;
	bool							m_bBatchRendering;

	NIRTTI_ADDRESS(0x11F4758);

	static NiRenderer* GetRenderer();

	NiAccumulator* GetSorter() const;
	void SetSorter(NiAccumulator* apAccumulator);

	bool GetInsideFrameState() const;

	void LockRenderer();
	void UnlockRenderer();

	void SetCameraData(const NiCamera* apCamera);

	void SetCameraData(const NiPoint3& arWorldLoc, const NiPoint3& arWorldDir, const NiPoint3& arWorldUp, const NiPoint3& arWorldRight, const NiFrustum& arFrustum, const NiRect<float>& arPort);
};

ASSERT_SIZE(NiRenderer, 0x280)