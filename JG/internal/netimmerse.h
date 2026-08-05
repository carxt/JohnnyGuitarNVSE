#pragma once

#include "GameTypes.h"

#include "Gamebryo/NiCamera.hpp"
#include "Gamebryo/NiNode.hpp"
#include "Gamebryo/NiRTTI.hpp"
#include "Gamebryo/NiColorA.hpp"
#include "Gamebryo/NiPoint4.hpp"
#include "Gamebryo/NiCullingProcess.hpp"
#include "Gamebryo/NiAlphaAccumulator.hpp"
#include "Gamebryo/NiRenderer.hpp"
#include "Gamebryo/NiSourceTexture.hpp"
#include "Gamebryo/NiControllerManager.hpp"
#include "Gamebryo/NiAlphaProperty.hpp"
#include "Gamebryo/NiMaterialProperty.hpp"
#include "Gamebryo/NiStencilProperty.hpp"
#include "Gamebryo/NiGeometryData.hpp"
#include "Gamebryo/NiSpotLight.hpp"
#include "Gamebryo/NiDirectionalLight.hpp"
#include "Gamebryo/NiPSysEmitterCtlr.hpp"
#include "Gamebryo/NiFloatInterpolator.hpp"
#include "Gamebryo/NiColorInterpolator.hpp"
#include "Gamebryo/NiLODNode.hpp"
#include "Bethesda/NiUpdateData.hpp"
#include "Bethesda/BSStream.hpp"
#include "Bethesda/BSShaderProperty.hpp"
#include "Bethesda/BSRenderedTexture.hpp"
#include "Bethesda/BSCullingProcess.hpp"
#include "Bethesda/BSFadeNode.hpp"
#include "Bethesda/BSFogProperty.hpp"
#include "Bethesda/SceneGraph.hpp"
#include "Bethesda/BSAnimGroupSequence.hpp"

class NavMeshInfo;
class TESAnimGroup;
class bhkRigidBody;
class TESObjectCELL;
class bhkPhantom;
class BSFadeNode;
class NiMultiTargetTransformController;
class NiTextKeyExtraData;
class NiControllerManager;
class NiDefaultAVObjectPalette;
class NiSourceTexture;
class bhkNiCollisionObject;
class hkpWorldObject;
struct hkVector4;
class NiLight;
class BSCubeMapCamera;
class NiFrustumPlanes;
class NiCullingProcess;
class NiTexture;
class NiSkinPartition;
class NiSkinInstance;
class NiSourceCubeMap;
class NiRenderedCubeMap;
class NiDepthStencilBuffer;
class NiRenderTargetGroup;
class NiGeometryData;
class NiRenderedTexture;
class NiTriStrips;
class NiParticles;
class NiLines;
class NiDX9RenderState;
class NiUnsharedGeometryGroup;
class NiNode;
class TESObjectREFR;
class Tile;
class BSPortalGraph;
class NiTriShape;
class NiPropertyState;
class NiDX9Renderer;

class ShadowSceneLight;
class BSShaderAccumulator;

// 150
class WaterShaderProperty : public BSShaderProperty {
public:
	WaterShaderProperty();
	~WaterShaderProperty();

	struct VarAmounts {
		float fSunSpecularPower;
		float fWaterReflectivityAmt;
		float fWaterOpacity;
		float fWaterDistortionAmt;
	};

	bool							bDisplacement;
	bool							bLOD;
	bool							bFullReflections;
	bool							bDepth;
	int32_t							iTexOffsetX;
	int32_t							iTexOffsetY;
	float							fBlendRadius;
	float							fBlendNormalsAmount;
	float							fFogFar;
	float							fFogRange;
	bool							bIsMoving;
	bool							bInWater;
	bool							bIsUnderwater;
	bool							bUpdateConstants;
	bool							bReflections;
	bool							bRefractions;
	bool							bObjectTexCoords;
	bool							bSpecularLighting;
	DWORD							uiStencilMask;
	NiColorA						kShallowColor;
	NiColorA						kDeepColor;
	NiColorA						kReflectionColor;
	VarAmounts						kVarAmounts;
	NiPoint4						kBlendRadius;
	NiPoint4						kDepthFalloff;
	NiPoint4						kDepthOffset;
	NiPoint4						kFresnelRI;
	NiColorA						kTile;
	float							fFresnelAmount;
	float							fNoiseScale;
	float							fFogAmount;
	float							fUVScale;
	NiTPointerList<NiLight*>		kLights;
	NiPointer<NiTexture>			spNoiseHeightMap;
	NiPointer<BSRenderedTexture>	spNoiseNormalMap;
	NiPointer<BSRenderedTexture>	spReflectionMap;
	NiPointer<BSRenderedTexture>	spRefractionMap;
	NiPointer<BSRenderedTexture>	spDepthMap;
	NiPointer<NiTexture>			spDisplacementNormalMap;
	RenderPass*						pWaterPass;
};
static_assert(sizeof(WaterShaderProperty) == 0x150);

class NiCamera;

// B4
class BSMultiBoundNode : public NiNode {
public:
	BSMultiBoundNode();
	~BSMultiBoundNode();

	virtual void	Unk_40(uint32_t arg1, uint32_t arg2);
	virtual void	Unk_41(void);
	virtual void	Unk_42(uint32_t arg1);
	virtual void	Unk_43(uint32_t arg1);
	virtual void	Unk_44(uint32_t arg1);

	uint32_t			unkAC[2];		// AC
};

// B8
class BSParticleSystemManager : public NiNode {
public:
	BSParticleSystemManager();
	~BSParticleSystemManager();

	virtual void	Unk_40(void);

	uint32_t			unkAC[3];		// AC
};

class BSOcclusionPlane;
class BSPortal;
class BSMultiBoundRoom;
class ShadowSceneLight;

// 78
class BSPortalGraph : public NiRefObject {
public:
	BSPortalGraph();
	~BSPortalGraph();

	NiTPointerList<BSOcclusionPlane*>			kOccluders;
	NiTPointerList<BSPortal*>					kPortals;
	NiTPointerList<NiPointer<BSMultiBoundRoom>>	kMultiBoundRooms;
	NiPointer<BSMultiBoundRoom>					spRoomRoot;
	NiTPointerList<NiPointer<BSMultiBoundRoom>>	kMultiBoundRoomAccumList;
	NiTObjectArray<NiPointer<NiAVObject>>		kAlwaysRenderChildren;
	NiPointer<NiNode>							spPortalNodeRoot;
	NiTPointerList<ShadowSceneLight*>			kAttachAlwaysRenderQueue;
	NiTPointerList<ShadowSceneLight*>			kDetachAlwaysRenderQueue;
	BSSimpleArray<NiPointer<NiNode>>			kUnboundNodes;
};
static_assert(sizeof(BSPortalGraph) == 0x78);

// 250
class ShadowSceneLight : public NiRefObject	//	010B7EB8
{
public:
	ShadowSceneLight();
	~ShadowSceneLight();

	uint32_t					unk008;			// 008
	float					flt00C[53];		// 00C
	DList<NiTriStrips>		lgtList0E0;		// 0E0
	uint8_t					byte0EC;		// 0EC
	uint8_t					byte0ED;		// 0ED
	uint8_t					byte0EE[2];		// 0EE
	uint32_t					unk0F0;			// 0F0
	uint32_t					unk0F4;			// 0F4
	NiPointer<NiLight> spLight;			// 0F8
	uint32_t					unk0FC;			// 0FC
	uint32_t					unk100[6];		// 100
	uint8_t					byte118;		// 118
	uint8_t					pad119[3];		// 119
	float					flt11C;			// 11C
	float					flt120;			// 120
	uint8_t					byte124;		// 124
	uint8_t					pad125[3];		// 125
	uint32_t					unk128[66];		// 128
	BSSimpleArray<NiNode>	array230;		// 230
	BSPortalGraph* portalGraph;	// 240
	uint32_t					unk244[3];		// 244
};
static_assert(sizeof(ShadowSceneLight) == 0x250);

class NiDirectionalLight;

// 200
class ShadowSceneNode : public NiNode {
public:
	ShadowSceneNode();
	~ShadowSceneNode();

	uint32_t							unk0AC[2];		// 0AC
	DList<ShadowSceneLight>				lgtList0B4;		// 0B4
	DList<ShadowSceneLight>				lgtList0C0;		// 0C0
	uint32_t							unk0CC;			// 0CC
	DListNode<ShadowSceneLight>* node0D0;		// 0D0
	DListNode<ShadowSceneLight>* node0D4;		// 0D4
	ShadowSceneLight* data0D8;		// 0D8
	ShadowSceneLight* data0DC;		// 0DC
	ShadowSceneLight* pSunLight;		// 0E0
	uint32_t							unk0E4[6];		// 0E4
	void* ptr0FC;		// 0FC
	void* ptr100;		// 100
	uint32_t							unk104;			// 104
	uint32_t							unk108[3];		// 108
	void* ptr114;		// 114
	void* ptr118;		// 118
	uint32_t							unk11C;			// 11C
	uint32_t							unk120;			// 120
	uint32_t							unk124;			// 124
	BSCubeMapCamera* cubeMapCam;	// 128
	uint32_t							unk12C;			// 12C
	uint8_t							byte130;		// 130
	uint8_t							byte131;		// 131
	uint8_t							pad132[2];		// 132
	BSFogProperty* fogProperty;	// 134
	uint32_t							unk138;			// 138
	BSSimpleArray<NiFrustumPlanes*>	array13C;		// 13C
	BSSimpleArray<void*>				array14C;		// 14C	010C1E9C
	uint32_t							unk15C[3];		// 15C
	NiPoint4						unk168;			// 168
	NiPoint4						unk178;			// 178
	NiPoint4						unk188;			// 188
	NiPoint4						unk198;			// 198
	NiPoint4						unk1A8;			// 1A8
	NiPoint4						unk1B8;			// 1B8
	uint32_t							lightingPasses;	// 1C8
	float							flt1CC[3];		// 1CC
	uint32_t							unk1D8;			// 1D8
	uint8_t							byte1DC;		// 1DC
	uint8_t							pad1DD[3];		// 1DD
	BSPortalGraph* portalGraph;	// 1E0
	NiPoint3						kLightingOffset;		// 1E4
	NiPoint3						kEyePos;		// 1F0
	uint8_t							byte1FC;		// 1FC
	uint8_t							pad1FD[3];		// 1FD

	NIRTTI_ADDRESS(0x11F9E80);

	void UpdateObjectLighting(NiAVObject* apObject, bool abActiveLightsOnly) {
		ThisCall(0xB5D9F0, this, apObject, abActiveLightsOnly);
	}

	void SetSunLight(NiDirectionalLight* apLight) {
		ThisCall(0xB5AAC0, this, apLight);
	}
};
static_assert(sizeof(ShadowSceneNode) == 0x200);

class BSCullingProcess;

class NiVBBlock;
class NiDX9LightManager;

class NiDX9Renderer : public NiRenderer {
public:
	NiDX9Renderer();
	~NiDX9Renderer();

	virtual void		Unk_24(void);
	virtual void		Unk_25(void);
	virtual void		Unk_26(void);
	virtual void		Unk_27(void);
	virtual void		Unk_28(void);
	virtual void		Unk_29(void);
	virtual void		Unk_2A(void);
	virtual void		SetBackgroundColorAlpha(const NiColorA& arColor);
	virtual void		SetBackgroundColor(const NiColor& arColor);
	virtual void		GetBackgroundColor(NiColorA& arColor) const;
	virtual void		SetStencilClear(uint32_t uiClear);
	virtual uint32_t	GetStencilClear() const;
	virtual void		Unk_30(void);
	virtual void		Unk_31(void);
	virtual NiRenderTargetGroup* GetDefaultRenderTargetGroup() const;	// get back buffer rt
	virtual NiRenderTargetGroup* GetCurrentRenderTargetGroup() const;	// get currentRTGroup
	virtual void		Unk_34(void);
	virtual void		Unk_35(void);
	virtual void		Unk_36(void);
	virtual void		Unk_37(void);
	virtual void 		Unk_38(void);
	virtual void 		Unk_39(void);
	virtual void		Unk_3A(void);
	virtual void		Unk_3B(void);
	virtual void		PurgeGeometry(NiGeometryData* geo);
	virtual void		PurgeMaterial(NiMaterialProperty* material);
	virtual void		PurgeEffect(NiDynamicEffect* effect);
	virtual void		PurgeScreenTexture();
	virtual void		PurgeSkinPartition(NiSkinPartition* skinPartition);
	virtual void		PurgeSkinInstance(NiSkinInstance* skinInstance);
	virtual void		Unk_42(void);
	virtual bool		Unk_43(void);
	virtual void		Unk_44(void);
	virtual bool		FastCopy(void* src, void* dst, RECT* srcRect, int32_t xOffset, int32_t yOffset);
	virtual bool		Copy(void* src, void* dst, RECT* srcRect, RECT* dstRect, uint32_t filterMode);
	virtual void		Unk_47(void);
	virtual bool		Unk_48(void* arg);
	virtual void		Unk_49(void);
	virtual void		Unk_4A(float arg);
	virtual void 		Unk_4B(uint32_t size);
	virtual void		Unk_4C(uint32_t arg0, uint32_t arg1);
	virtual void		Unk_4D(uint32_t arg0, uint32_t arg1);
	virtual void		Unk_4E(void* buf);
	virtual void		CreateSourceTexture(NiSourceTexture* texture);
	virtual bool		CreateRenderedTexture(NiRenderedTexture* arg);
	virtual bool		CreateSourceCubeMap(NiSourceCubeMap* arg);
	virtual bool		CreateRenderedCubeMap(NiRenderedCubeMap* arg);
	virtual bool		CreateDynamicTexture(void* arg);
	virtual void		Unk_54(void);
	virtual bool		CreateDepthStencil(NiDepthStencilBuffer* arg, void* textureFormat);
	virtual void		Unk_56(void);
	virtual void		Unk_57(void);
	virtual void		Unk_58(void);
	virtual void		Unk_59(void);
	virtual void		Unk_5A(void);
	virtual void		Unk_5B(void);
	virtual void		Unk_5C(void);
	virtual void		Unk_5D(void);
	virtual void		Unk_5E(void);
	virtual bool		BeginScene();
	virtual bool		EndScene();
	virtual void		DisplayScene();
	virtual void		Clear(float* rect, uint32_t flags);
	virtual void		SetupCamera(NiPoint3* pos, NiPoint3* at, NiPoint3* up, NiPoint3* right, NiFrustum* frustum, float* viewport);
	virtual void		SetupScreenSpaceCamera(float* viewport);
	virtual bool		BeginUsingRenderTargetGroup(NiRenderTargetGroup* renderTarget, ClearFlags clearFlags);
	virtual bool		EndUsingRenderTargetGroup();
	virtual void		BeginBatch(uint32_t arg0, uint32_t arg1);
	virtual void		EndBatch();
	virtual void		BatchRenderShape(void* arg);
	virtual void		BatchRenderStrips(void* arg);
	virtual void		RenderTriShape(NiTriShape* obj);
	virtual void		RenderTriStrips(NiTriStrips* obj);
	virtual void		RenderTriShape2(NiTriShape* obj);
	virtual void		RenderTriStrips2(NiTriStrips* obj);
	virtual void		RenderParticles(NiParticles* obj);
	virtual void		RenderLines(NiLines* obj);
	virtual void		RenderScreenTexture();

	class PrePackObject;

	enum FrameBufferFormat {
		FBFMT_UNKNOWN = 0,
		FBFMT_R8G8B8,
		FBFMT_A8R8G8B8,
		FBFMT_X8R8G8B8,
		FBFMT_R5G6B5,
		FBFMT_X1R5G5B5,
		FBFMT_A1R5G5B5,
		FBFMT_A4R4G4B4,
		FBFMT_R3G3B2,
		FBFMT_A8,
		FBFMT_A8R3G3B2,
		FBFMT_X4R4G4B4,
		FBFMT_R16F,
		FBFMT_G16R16F,
		FBFMT_A16B16G16R16F,
		FBFMT_R32F,
		FBFMT_G32R32F,
		FBFMT_A32B32G32R32F,
		FBFMT_NUM
	};

	enum DepthStencilFormat {
		DSFMT_UNKNOWN = 0,
		DSFMT_D16_LOCKABLE = 70,
		DSFMT_D32 = 71,
		DSFMT_D15S1 = 73,
		DSFMT_D24S8 = 75,
		DSFMT_D16 = 80,
		DSFMT_D24X8 = 77,
		DSFMT_D24X4S4 = 79,
	};

	enum PresentationInterval {
		PRESENT_INTERVAL_IMMEDIATE = 0,
		PRESENT_INTERVAL_ONE = 1,
		PRESENT_INTERVAL_TWO = 2,
		PRESENT_INTERVAL_THREE = 3,
		PRESENT_INTERVAL_FOUR = 4,
		PRESENT_INTERVAL_NUM
	};

	enum SwapEffect {
		SWAPEFFECT_DEFAULT,
		SWAPEFFECT_DISCARD,
		SWAPEFFECT_FLIP,
		SWAPEFFECT_COPY,
		SWAPEFFECT_NUM
	};

	enum FrameBufferMode {
		FBMODE_DEFAULT,
		FBMODE_LOCKABLE,
		FBMODE_MULTISAMPLES_2 = 0x00010000,
		FBMODE_MULTISAMPLES_3 = 0x00020000,
		FBMODE_MULTISAMPLES_4 = 0x00030000,
		FBMODE_MULTISAMPLES_5 = 0x00040000,
		FBMODE_MULTISAMPLES_6 = 0x00050000,
		FBMODE_MULTISAMPLES_7 = 0x00060000,
		FBMODE_MULTISAMPLES_8 = 0x00070000,
		FBMODE_MULTISAMPLES_9 = 0x00080000,
		FBMODE_MULTISAMPLES_10 = 0x00090000,
		FBMODE_MULTISAMPLES_11 = 0x000a0000,
		FBMODE_MULTISAMPLES_12 = 0x000b0000,
		FBMODE_MULTISAMPLES_13 = 0x000c0000,
		FBMODE_MULTISAMPLES_14 = 0x000d0000,
		FBMODE_MULTISAMPLES_15 = 0x000e0000,
		FBMODE_MULTISAMPLES_16 = 0x000f0000,
		FBMODE_MULTISAMPLES_NONMASKABLE = 0x80000000,
		FBMODE_QUALITY_MASK = 0x0000FFFF,
		FBMODE_NUM = 18
	};

	enum RefreshRate {
		REFRESHRATE_DEFAULT = 0
	};

	uint32_t								unk210[2];					// 210
	IDirect3DDevice9* device;					// 288
	uint32_t								unk28C[76];					// 28C
	HANDLE								deviceWindow;				// 3BC
	HANDLE								focusWindow;				// 3C0
	char								rendererInfo[0x200];		// 3C4
	uint32_t								adapterIdx;					// 5C4
	uint32_t								d3dDevType;					// 5C8 - D3DDEVTYPE
	uint32_t								d3dDevFlags;				// 5CC - D3DCREATE
	uint8_t								softwareVertexProcessing;	// 5D0 - !D3DCREATE_HARDWARE_VERTEXPROCESSING
	uint8_t								mixedVertexProcessing;		// 5D1 - D3DCREATE_MIXED_VERTEXPROCESSING
	uint8_t								pad5D2[2];					// 5D2
	uint32_t								unk5D4[3];					// 5D4
	uint32_t								backgroundColor;			// 5E0	ARGB
	uint32_t								unk5E4[11];					// 5E4
	NiTPointerMap<NiVBBlock*, PrePackObject*>		prePackObjects;				// 610 - NiTPointerMap <NiVBBlock *, NiDX9Renderer::PrePackObject *>
	uint32_t								unk620[153];				// 620
	NiRenderTargetGroup* defaultRTGroup;			// 884 - back buffer
	NiRenderTargetGroup* currentRTGroup;			// 888
	NiRenderTargetGroup* currentscreenRTGroup;		// 88C
	NiTPointerMap<HWND, NiRenderTargetGroup*>	screenRTGroups;				// 890 - NiTPointerMap <HWND *, NiPointer <NiRenderTargetGroup> >
	uint32_t								unk8A0[6];					// 8A0
	NiDX9RenderState* renderState;				// 8B8
	uint32_t								unk8BC[3];					// 8BC
	NiDX9LightManager* lightsMap;					// 8C8
	uint32_t								unk8CC[115];				// 8CC
	uint32_t								width;						// A98
	uint32_t								height;						// A9C
	uint32_t								flags;						// AA0
	uint32_t								windowDevice;				// AA4
	uint32_t								windowFocus;				// AA8
	uint32_t								adapterType;				// AAC
	uint32_t								deviceType;					// AB0
	FrameBufferFormat					frameBufferFormat;			// AB4
	DepthStencilFormat					depthStencilFormat;			// AB8
	PresentationInterval				presentationInterval;		// ABC
	SwapEffect							swapEffect;					// AC0
	FrameBufferMode						frameBufferMode;			// AC4
	uint32_t								backBufferCount;			// AC8
	RefreshRate							refreshRate;				// ACC
	uint32_t								unkAD0[44];					// 

	// GAME - 0x7148C0
	void ClearBuffer(const NiRect<float>* apRect, uint32_t auiClearFlags) {
		ThisCall(0x7148C0, this, apRect, auiClearFlags);
	};

	uint32_t GetScreenHeight() const {
		return ThisCall<uint32_t>(0xB6C1D0, this);
	};

	uint32_t GetScreenWidth() const {
		return ThisCall<uint32_t>(0xB6C1A0, this);
	};
};
static_assert(sizeof(NiDX9Renderer) == 0xB80);

// 70
class NiDX9TextureData : public NiObject {
public:
	NiDX9TextureData();
	~NiDX9TextureData();

	virtual void	Unk_23(void);
	virtual void	Unk_24(void);
	virtual void	Unk_25(void);
	virtual void	Unk_26(void);
	virtual void	Unk_27(void);
	virtual void	Unk_28(void);
	virtual void	Unk_29(void);
	virtual void	Unk_2A(void);
	virtual void	Unk_2B(void);
	virtual void	Unk_2C(void);

	NiTexture* owningTexture;	// 08
	uint32_t				unk0C[6];		// 0C
	uint32_t				unk24;			// 24
	uint32_t				unk28[14];		// 28
	NiDX9Renderer* renderer;		// 60
	uint32_t				unk64;			// 64
	uint32_t				unk68;			// 68
	uint32_t				unk6C;			// 6C
};

// 14
class Ni2DBuffer : public NiObject {
public:
	Ni2DBuffer();
	~Ni2DBuffer();

	virtual void	Unk_23(void);
	virtual void	Unk_24(void);
	virtual void	Unk_25(void);

	uint32_t		unk08[3];		// 08
};

// 48
class NiRenderedTexture : public NiTexture {
public:
	NiRenderedTexture();
	~NiRenderedTexture();

	virtual void	Unk_29(void);

	Ni2DBuffer* buffer;	// 30
	uint32_t				unk34;		// 34
	uint32_t				unk38;		// 38
	uint32_t				unk3C;		// 3C
	uint32_t				unk40;		// 40
	uint32_t				unk44;		// 44
};

// B0
class TileShaderProperty : public BSShaderProperty	//	vtbl = 010B9D28
{
public:
	TileShaderProperty();
	~TileShaderProperty();

	NiTexture* srcTexture;	// 60
	uint32_t				unk64;			// 64
	NiColorA		overlayColor;	// 68
	float				alpha;			// 78
	uint32_t				unk7C;			// 7C
	uint32_t				unk80;			// 80
	float				flt84;			// 84
	float				flt88;			// 88
	uint32_t				unk8C;			// 8C
	uint8_t				byte90;			// 90
	uint8_t				byte91;			// 91
	uint8_t				hasVtxColors;	// 92
	uint8_t				byte93;			// 93
	uint32_t				unk94[7];		// 94
};
static_assert(sizeof(TileShaderProperty) == 0xB0);

// 98
class BSBatchRenderer : public NiObject {
public:
	BSBatchRenderer();
	~BSBatchRenderer();

	virtual void	Unk_23(void);
	virtual void	Unk_24(void);

	uint32_t			unk08[36];		// 08
};
static_assert(sizeof(BSBatchRenderer) == 0x98);

class BSOcclusionQuery;

// 280
class BSShaderAccumulator : public NiAlphaAccumulator {
public:
	BSShaderAccumulator();
	~BSShaderAccumulator();

	virtual void	Unk_2A(void);
	virtual void	Unk_2B(void);
	virtual void	Unk_2C(uint32_t arg1, uint32_t arg2);

	struct AccumStruct	//	Temp name
	{
		void* _vtbl;	// 0x10B7DC0
		uint32_t		unk04;
		uint32_t		unk08;
		uint32_t		unk0C;
		uint32_t		unk10;
	};

	struct SunOcclusionTest {
		BSOcclusionQuery*	pOcclusionQuery;
		bool				bWaiting;
		float				fPercentOccluded;
		uint32_t			uiPixelCount;
		uint32_t			uiFrameCount;
	};

	uint32_t								eAccumulationMode;
	bool									bWorldGeometry;
	bool									bCacheGeometry;
	bool									bDoDepthPasses;
	uint32_t								uiSunPixelCount;
	bool									bWaitingForSunQuery;
	float									fPercentSunOccludedStored;
	SunOcclusionTest						kSunTests[3];
	bool									bAccumulate;
	bool									bIs1stPerson;
	bool									bRenderNoShader;
	uint16_t								usQueryCount;
	uint16_t								usQuerySize;
	BSOcclusionQuery**						ppOcclusionQueries;
	NiTPointerList<NiGeometry*>				kVolumetricFogGeometries;
	AccumStruct								accum09C[4];
	AccumStruct								accum0EC[4];
	uint32_t								unk13C[4];
	uint32_t								uiLastOcclusionRef;
	bool									bLastOcclusionResult;
	NiColorA								kSilhouetteColor;
	bool									bIsWaterReflection; // Ignores water shaders
	bool									bIsWaterRefraction;
	bool									bCellHasWater;
	bool									bIsUnderwater;
	int32_t									iCurrentWaterHeight;
	bool									bRenderDecals;
	void*									pInstanceRenderer;
	BSBatchRenderer*						pBatchRenderers[2];
	uint32_t*								pCurrentPasses;
	uint32_t*								pCurrentBuckets;
	bool*									pCurrentFirstPasses;
	bool*									pCurrentActivePasses;
	uint32_t								uiBatchRendererCount;
	uint32_t								uiBatchRendererPassCount;
	ShadowSceneNode*						pActiveShadowSceneNode;	// 194
	uint32_t								unk198;			// 198
	uint32_t								unk19C;			// 19C
	uint32_t								unk1A0[56];		// 1A0

	static BSShaderAccumulator* Create(uint32_t aeBatchRendererCreationType = 99, uint32_t auiBatchRendererCount = 1, uint32_t aeMaxPassCount = 759) {
		return NiCreate<BSShaderAccumulator, 0xB660D0>(aeBatchRendererCreationType, auiBatchRendererCount, aeMaxPassCount);
	}
};
static_assert(sizeof(BSShaderAccumulator) == 0x280);

struct UVCoord {
	float		x;
	float		y;

	UVCoord() {}
	UVCoord(float _x, float _y) : x(_x), y(_y) {}
};

// 14
class NiShader : public NiRefObject {
public:
	NiShader();
	~NiShader();

	virtual void	Unk_02(void);
	virtual void	Unk_03(void);
	virtual void	Unk_04(void);
	virtual void	Unk_05(void);
	virtual void	Unk_06(void);
	virtual void	Unk_07(void);
	virtual void	Unk_08(void);
	virtual void	Unk_09(void);
	virtual void	Unk_0A(void);
	virtual void	Unk_0B(void);
	virtual void	Unk_0C(void);
	virtual void	Unk_0D(void);
	virtual void	Unk_0E(void);
	virtual void	Unk_0F(void);
	virtual void	Unk_10(void);
	virtual void	Unk_11(void);
	virtual void	Unk_12(void);
	virtual void	Unk_13(void);
	virtual void	Unk_14(void);
	virtual void	Unk_15(void);
	virtual void	Unk_16(void);
	virtual void	Unk_17(void);
	virtual void	Unk_18(void);
	virtual void	Unk_19(void);
	virtual void	Unk_1A(void);
	virtual void	Unk_1B(void);
	virtual void	Unk_1C(void);
	virtual void	Unk_1D(void);
	virtual void	Unk_1E(void);
	virtual void	Unk_1F(void);
	virtual void	Unk_20(void);
	virtual void	Unk_21(void);
	virtual void	Unk_22(void);
	virtual void	Unk_23(void);
	virtual void	Unk_24(void);
	virtual void	Unk_25(void);
	virtual void	Unk_26(void);
	virtual void	Unk_27(void);
	virtual void	Unk_28(void);
	virtual void	Unk_29(void);
	virtual void	Unk_2A(void);
	virtual void	Unk_2B(void);
	virtual void	Unk_2C(void);
	virtual void	Unk_2D(void);
	virtual void	Unk_2E(void);

	uint32_t			unk08;		// 08
	uint32_t			unk0C;		// 0C
	uint32_t			unk10;		// 10
};

// 90
class TileShader : public NiShader {
public:
	TileShader();
	~TileShader();

	virtual void	Unk_2F(void);
	virtual void	Unk_30(void);
	virtual void	Unk_31(void);
	virtual void	Unk_32(void);
	virtual void	Unk_33(void);
	virtual void	Unk_34(void);
	virtual void	Unk_35(void);
	virtual void	Unk_36(void);
	virtual void	Unk_37(void);
	virtual void	Unk_38(void);
	virtual void	Unk_39(void);
	virtual void	Unk_3A(void);
	virtual void	Unk_3B(void);
	virtual void	Unk_3C(void);
	virtual void	Unk_3D(void);
	virtual void	Unk_3E(void);
	virtual void	Unk_3F(void);
	virtual void	Unk_40(void);
	virtual void	Unk_41(void);
	virtual void	Unk_42(void);
	virtual void	Unk_43(void);
	virtual void	Unk_44(void);
	virtual void	Unk_45(void);
	virtual void	Unk_46(void);
	virtual void	Unk_47(void);
	virtual void	Unk_48(void);
	virtual void	Unk_49(void);
	virtual void	Unk_4A(void);
	virtual void	Unk_4B(void);
	virtual void	Unk_4C(void);
	virtual void	Unk_4D(void);
	virtual void	Unk_4E(void);
	virtual void	Unk_4F(void);
	virtual void	Unk_50(void);
	virtual void	Unk_51(void);
	virtual void	Unk_52(void);
	virtual void	Unk_53(void);

	uint32_t			unk14[31];		// 14
};
static_assert(sizeof(TileShader) == 0x90);

// 14C
class ParticleShaderProperty : public BSShaderProperty {
public:
	ParticleShaderProperty();
	~ParticleShaderProperty();

	uint32_t			unk060[59];		// 060
};
static_assert(sizeof(ParticleShaderProperty) == 0x14C);

class BSCompoundFrustum;

class NiRenderTargetGroup : public NiObject {
public:
	// has more data but not needed atm
};