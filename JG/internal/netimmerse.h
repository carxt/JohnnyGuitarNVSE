#pragma once

#include "NiTypes.h"
#include "GameTypes.h"

#include "Gamebryo/NiObjectNET.hpp"
#include "Gamebryo/NiRTTI.hpp"
#include "Gamebryo/NiCullingProcess.hpp"
#include "Gamebryo/NiAlphaAccumulator.hpp"
#include "Gamebryo/NiRenderer.hpp"
#include "Bethesda/NiUpdateData.hpp"
#include "Bethesda/BSRenderedTexture.hpp"
#include "Bethesda/BSCullingProcess.hpp"

struct NavMeshInfo;
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

// 44
class LoadedAreaBound : public NiRefObject
{
public:
	LoadedAreaBound();
	~LoadedAreaBound();

	bhkPhantom* phantoms[6]; // 08	Seen bhkAabbPhantom
	TESObjectCELL* cell; // 20
	NiTMap<bhkRigidBody*, uint16_t> boundsMap; // 24
	float flt34; // 34
	float flt38; // 38
	float flt3C; // 3C
	float flt40; // 40
};

static_assert(sizeof(LoadedAreaBound) == 0x44);

// 8C
class ObstacleData : public NiRefObject
{
public:
	ObstacleData();
	~ObstacleData();

	uint32_t unk08; // 08
	NiRefObject* object0C; // 0C
	uint32_t unk10[25]; // 10
	uint8_t byte74; // 74
	uint8_t byte75[3]; // 75
	BSSimpleArray<NavMeshInfo*> navMeshInfos; // 78
	NiRefObject* object88; // 88
};

// 40
struct QuaternionKey {
	float			time;			// 00
	NiQuaternion	value;			// 04
	NiPoint3		TBC;			// 14
	NiQuaternion	quaternion20;	// 20
	NiQuaternion	quaternion30;	// 30
};
static_assert(sizeof(QuaternionKey) == 0x40);

// 2C
class NiTransformData : public NiObject {
public:
	NiTransformData();
	~NiTransformData();

	enum {
		kKeyType_Linear = 1,
		kKeyType_Quadratic,
		kKeyType_TBC,
		kKeyType_XYZ,
		kKeyType_Const,
	};

	uint16_t		numRotationKeys;	// 08
	uint16_t		numTranslationKeys;	// 0A
	uint16_t		numScaleKeys;		// 0C
	uint16_t		pad0E;				// 0E
	uint32_t		rotationKeyType;	// 10
	uint32_t		translationKeyType;	// 14
	uint32_t		scaleKeyType;		// 18
	uint8_t		rotationKeySize;	// 1C
	uint8_t		translationKeySize;	// 1D
	uint8_t		scaleKeySize;		// 1E
	uint8_t		pad1F;				// 1F
	void* rotationKeys;		// 20
	void* translationKeys;	// 24
	void* scaleKeys;			// 28
};
static_assert(sizeof(NiTransformData) == 0x2C);

// 08
struct FloatData {
	uint32_t		unk00;
	float		value;
};

// 18
class NiFloatData : public NiObject {
public:
	NiFloatData();
	~NiFloatData();

	uint32_t			unk08;		// 08
	FloatData* fltData;	// 0C
	uint32_t			unk10;		// 10
	uint8_t			byte14;		// 14
	uint8_t			pad15[3];	// 15
};

// 14
struct ColorData {
	uint32_t		unk00;
	float		value[4];
};

// 18
class NiColorData : public NiObject {
public:
	NiColorData();
	~NiColorData();

	uint32_t			unk08;		// 08
	ColorData* clrData;	// 0C
	uint32_t			unk10;		// 10
	uint32_t			unk14;		// 14
};

class NiBoolInterpolator;
class NiQuatTransform;

// 0C
class NiInterpolator : public NiObject {
public:
	NiInterpolator();
	~NiInterpolator();

	virtual bool				UpdateTransform(float afTime, NiObjectNET* apTarget, NiQuatTransform& arValue);
	virtual bool				UpdateColorA(float afTime, NiObjectNET* apTarget, NiColorA& arValue);
	virtual bool				UpdatePoint3(float afTime, NiObjectNET* apTarget, NiPoint3& arValue);
	virtual bool				UpdateQuaternion(float afTime, NiObjectNET* apTarget, NiQuaternion& arValue);
	virtual bool				UpdateFloat(float afTime, NiObjectNET* apTarget, float& arValue);
	virtual bool				UpdateBool(float afTime, NiObjectNET* apTarget, bool& arValue);
	virtual bool				IsBoolValueSupported() const;
	virtual bool				IsFloatValueSupported() const;
	virtual bool				IsQuaternionValueSupported() const;
	virtual bool				IsPoint3ValueSupported() const;
	virtual bool				IsColorAValueSupported() const;
	virtual bool				IsTransformValueSupported() const;
	virtual void				Collapse();
	virtual void				GetActiveTimeRange(float& arBeginKeyTime, float& arEndKeyTime) const;
	virtual void				GuaranteeTimeRange(float afStartTime, float afEndTime);
	virtual NiInterpolator*		GetSequenceInterpolator(float afStartTime, float afEndTime);
	virtual bool				ResolveDependencies();
	virtual bool				SetUpDependencies();
	virtual bool				AlwaysUpdate() const;
	virtual NiBoolInterpolator* IsNiBoolInterpolator() const;

	float m_fLastTime;
};

// 0C
class NiKeyBasedInterpolator : public NiInterpolator {
public:
	NiKeyBasedInterpolator();
	~NiKeyBasedInterpolator();

	virtual void	Unk_37(void);
	virtual void	Unk_38(void);
	virtual void	Unk_39(void);
	virtual void	Unk_3A(void);
	virtual void	Unk_3B(void);
	virtual void	Unk_3C(void);
	virtual void	Unk_3D(void);
};

// 18
class NiFloatInterpolator : public NiKeyBasedInterpolator {
public:
	NiFloatInterpolator();
	~NiFloatInterpolator();

	float					m_fFloatValue;
	NiPointer<NiFloatData>	m_spFloatData;
	uint32_t				m_uiLastIdx;
};

// 24
class NiColorInterpolator : public NiKeyBasedInterpolator {
public:
	NiColorInterpolator();
	~NiColorInterpolator();

	float				value[4];	// 0C
	NiColorData* data;		// 1C
	uint32_t				unk20;		// 20
};

// 48
class NiTransformInterpolator : public NiKeyBasedInterpolator {
public:
	NiTransformInterpolator();
	~NiTransformInterpolator();

	virtual void	Unk_3E(void);

	float			flt0C;		// 0C
	float			flt10;		// 10
	float			flt14;		// 14
	float			flt18;		// 18
	float			flt1C;		// 1C
	float			flt20;		// 20
	float			flt24;		// 24
	float			flt28;		// 28
	NiTransformData* transData;	// 2C
	uint16_t			unk30;		// 30
	uint16_t			unk32;		// 32
	uint16_t			unk34;		// 34
	uint8_t			pad36[2];	// 36
	float			flt38;		// 38
	float			flt3C;		// 3C
	float			flt40;		// 40
	uint8_t			byte44;		// 44
	uint8_t			pad45[3];	// 45

	static NiTransformInterpolator* Create();
};
static_assert(sizeof(NiTransformInterpolator) == 0x48);

// 74
class NiControllerSequence : public NiObject {
public:
	NiControllerSequence();
	~NiControllerSequence();

	virtual bool Deactivate(float afEaseOutTime, bool);

	enum AnimState : uint32_t {
		INACTIVE,
		ANIMATING,
		EASEIN,
		EASEOUT,
		TRANSSOURCE,
		TRANSDEST,
		MORPHSOURCE
	};

	struct ControlledBlock {
		NiInterpolator* interpolator;
		NiMultiTargetTransformController* multiTargetCtrl;
		// More
	};

	NiFixedString	 sequenceName;			// 08
	uint32_t				numControlledBlocks;	// 0C
	uint32_t				arrayGrowBy;			// 10
	ControlledBlock** controlledBlocks;		// 14
	const char** unkNodeName;			// 18
	float				weight;					// 1C
	NiTextKeyExtraData* textKeyData;			// 20
	uint32_t				cycleType;				// 24
	float				frequency;				// 28
	float				startTime;				// 2C
	float				stopTime;				// 30
	float				flt34;					// 34
	float				flt38;					// 38
	float				flt3C;					// 3C
	NiControllerManager* manager;				// 40
	AnimState				m_eState;					// 44
	uint32_t				unk48;					// 48
	float				flt4C;					// 4C
	float				flt50;					// 50
	float				flt54;					// 54
	uint32_t				unk58;					// 58
	const char* rootNodeName;			// 5C
	uint32_t				unk60[5];				// 60

	AnimState GetState() const {
		return m_eState;
	}
};
static_assert(sizeof(NiControllerSequence) == 0x74);

class NiObjectNET;

// 34
class NiTimeController : public NiObject {
public:
	NiTimeController();
	~NiTimeController();

	virtual void	Start(float afTime = INFINITY);			// 35
	virtual void	Stop();									// 36
	virtual void	Update(NiUpdateData& arUpdateData);		// 37
	virtual void	SetTarget(NiObjectNET* apTarget);		// 38
	virtual bool	IsTransformController() const;			// 39
	virtual bool	IsVertexController() const;				// 40
	virtual float	ComputeScaledTime(float fTime);			// 41
	virtual void	OnPreDisplay() const;					// 42
	virtual bool	IsStreamable() const;					// 43
	virtual bool	TargetIsRequiredType() const;			// 44

	Bitfield16						m_usFlags;
	float							m_fFrequency;
	float							m_fPhase;
	float							m_fLoKeyTime;
	float							m_fHiKeyTime;
	float							m_fStartTime;
	float							m_fLastTime;
	float							m_fWeightedLastTime;
	float							m_fScaledTime;
	NiObjectNET*					m_pkTarget;
	NiPointer<NiTimeController>		m_spNext;

	bool GetActive() const {
		return m_usFlags.GetBit(3);
	}
	
	void SetActive(bool abVal){
		m_usFlags.Set(8, abVal);
	}

	bool GetManagerControlledBit() const {
		return m_usFlags.GetBit(5);
	}

	bool DontDoUpdate(float afTime) {
#ifdef GAME
		return ThisCall<bool>(0xA36250, this, afTime);
#else
		return ThisCall<bool>(0x7E75E0, this, afTime);
#endif
	}
};

class BSAnimNoteListener;

// 7C
class NiControllerManager : public NiTimeController {
public:
	NiControllerManager();
	~NiControllerManager();

	NiTObjectArray<NiPointer<NiControllerSequence>>		m_kSequenceArray;
	NiTPrimitiveSet<NiControllerSequence*>				m_kActiveSequences;
	NiTStringPointerMap<NiControllerSequence*>			m_kIndexMap;
	BSAnimNoteListener*									pListener;
	bool												m_bCumulative;
	NiTObjectSet<NiPointer<NiControllerSequence> >		m_kTempBlendSeqs;
	NiPointer<NiDefaultAVObjectPalette>					m_spObjectPalette;

	CREATE_OBJECT(NiControllerManager, 0xA2F6C0);
	NIRTTI_ADDRESS(0x11F36AC);

	NiControllerSequence* GetSequenceByName(const NiFixedString& arName) const {
		return ThisCall<NiControllerSequence*>(0x47A520, this, &arName);
	}

	uint32_t GetSequenceCount() const {
		return m_kSequenceArray.GetSize();
	}

	NiControllerSequence* GetSequenceAt(uint32_t auiIndex) const {
		return m_kSequenceArray.GetAt(auiIndex);
	};

	bool DeactivateSequence(NiControllerSequence* apSequence, float afEaseOutTime) {
		return apSequence->Deactivate(afEaseOutTime, 0);
	}

	bool IsSequenceActive(const NiFixedString& arName) const {
		const uint32_t uiSize = m_kActiveSequences.GetSize();
		if (uiSize) {
			for (uint32_t i = 0; i < uiSize; i++) {
				NiControllerSequence* pSequence = m_kActiveSequences.GetAt(i);
				if (pSequence->sequenceName == arName) {
					return pSequence->GetState() != NiControllerSequence::AnimState::INACTIVE;
				}
			}
		}
		return false;
	}
};
static_assert(sizeof(NiControllerManager) == 0x7C);

class NiBlendInterpolator;

// 34
class NiInterpController : public NiTimeController {
public:
	NiInterpController();
	~NiInterpController();

	virtual uint16_t				GetInterpolatorCount() const;
	virtual const char*				GetInterpolatorID(uint16_t ausIndex = 0) const;
	virtual uint16_t				GetInterpolatorIndex(const char* apID) const;
	virtual uint16_t				GetInterpolatorIndexFx(uint16_t ausIndex = 0) const;
	virtual NiInterpolator*			GetInterpolator(uint16_t ausIndex = 0) const;
	virtual void					SetInterpolator(NiInterpolator* apInterpolator, uint16_t ausIndex = 0);
	virtual void					ResetTimeExtrema();
	virtual uint32_t				GetCtlrID() const;
	virtual NiInterpolator*			CreatePoseInterpolator(uint16_t ausIndex = 0);
	virtual void					SynchronizePoseInterpolator(NiInterpolator* apInterpolator, uint16_t ausIndex = 0);
	virtual NiBlendInterpolator*	CreateBlendInterpolator(uint16_t ausIndex = 0, bool abManagerControlled = false, bool abAccumulateAnimations = false, float afWeightThreshold = 0.0f, uint8_t aucArraySize = 2);
	virtual void					GuaranteeTimeRange(float afStartTime, float afEndTime);
	virtual bool					InterpolatorIsCorrectType(NiInterpolator* apInterpolator, uint16_t ausIndex = 0) const;

	NIRTTI_ADDRESS(0x11F36B4);

	static inline constexpr uint16_t	INVALID_INDEX	= UINT16_MAX;
	static inline constexpr float		INVALID_TIME	= -FLT_MAX;

	bool GetManagerControlled() const {
		return GetManagerControlledBit();
	}
};

// 38
class NiSingleInterpController : public NiInterpController {
public:
	NiSingleInterpController();
	~NiSingleInterpController();

	virtual bool InterpTargetIsCorrectType(NiObjectNET* apObject) const;

	NiPointer<NiInterpolator> m_spInterpolator;

	CREATE_OBJECT(NiSingleInterpController, 0xC5C9D0);
	NIRTTI_ADDRESS(0x11F3714);
};

class NiFloatInterpController : public NiSingleInterpController {
public:
	NiFloatInterpController();
	virtual ~NiFloatInterpController();

	virtual void GetTargetFloatValue(float& arValue);

	NIRTTI_ADDRESS(0x11F4220);
};

class NiLightDimmerController : public NiFloatInterpController {
public:
	CREATE_OBJECT(NiLightDimmerController, 0xA4D0D0);
	NIRTTI_ADDRESS(0x11F3FA0);
};

// 38
class NiTransformController : public NiSingleInterpController {
public:
	NiTransformController();
	~NiTransformController();

	static NiTransformController* __stdcall Create(NiNode* pTarget, NiTransformInterpolator* pInterpolator);
};
static_assert(sizeof(NiTransformController) == 0x38);

class NiPSysModifier;

class NiPSysModifierCtlr : public NiSingleInterpController {
public:
	NiPSysModifierCtlr();
	virtual ~NiPSysModifierCtlr();

	NiFixedString	m_kModifierName;
	NiPSysModifier* m_pkModifier;

	NIRTTI_ADDRESS(0x12027C8);
};

class NiPSysEmitterCtlr : public NiPSysModifierCtlr {
public:
	NiPSysEmitterCtlr();
	virtual ~NiPSysEmitterCtlr();

	NiPointer<NiInterpolator>	m_spEmitterActiveInterpolator;
	NiInterpolator*				m_pkLastBirthRateInterpolator;
	float						m_fLastScaledTime;
	bool						m_bLastActive;
	NiTPrimitiveSet<float>		m_kParticleAges;

	CREATE_OBJECT(NiPSysEmitterCtlr, 0xC1C5E0);
	NIRTTI_ADDRESS(0x12024E8);

	// GAME - 0x639B60
	NiFloatInterpolator* GetBirthRateInterpolator() const {
		return ThisCall<NiFloatInterpolator*>(0x639B60, this);
	}
};

// 0C
class NiExtraData : public NiObject {
public:
	NiExtraData();
	~NiExtraData();

	virtual void	Unk_23(void);
	virtual void	Unk_24(void);

	uint32_t			unk08;		// 08
};

// 10
class BSXFlags : public NiExtraData {
public:
	BSXFlags();
	~BSXFlags();

	enum {
		kBSXFlag_Animated = 1 << 0,
		kBSXFlag_Havok = 1 << 1,
		kBSXFlag_Ragdoll = 1 << 2,
		kBSXFlag_Complex = 1 << 3,
		kBSXFlag_Addon = 1 << 4,
		kBSXFlag_EditorMarker = 1 << 5,
		kBSXFlag_Dynamic = 1 << 6,
		kBSXFlag_Articulated = 1 << 7,
		kBSXFlag_NeedsTransformUpdates = 1 << 8,
		kBSXFlag_ExternalEmit = 1 << 9,
	};

	uint32_t			flags;		// 0C
};

// 14
class TileExtra : public NiExtraData {
public:
	TileExtra();
	~TileExtra();

	Tile* parentTile;	// 0C
	NiNode* parentNode;	// 10
};

// 18
class NiProperty : public NiObjectNET {
public:
	NiProperty();
	~NiProperty();

	virtual uint32_t	GetPropertyType();
	virtual void	UpdateController(float arg);

	enum {
		kPropertyType_Alpha = 0,
		kPropertyType_Culling = 1,
		kPropertyType_Material = 2,
		kPropertyType_Shade = 3,
		kPropertyType_TileShader = kPropertyType_Shade,
		kPropertyType_Stencil = 4,
		kPropertyType_Texturing = 5,
		kPropertyType_Dither = 8,
		kPropertyType_Specular = 9,
		kPropertyType_VertexColor = 10,
		kPropertyType_ZBuffer = 11,
		kPropertyType_Fog = 13,
	};
};

// 4C
class NiMaterialProperty : public NiProperty {
public:
	NiMaterialProperty();
	~NiMaterialProperty();

	int32_t		m_iIndex;
	NiColor		m_kSpec;
	NiColor		m_kEmit;
	NiColor*	m_pExternalEmittance;
	float		m_fShine;
	float		m_fAlpha;
	float		m_fEmitMult;
	uint32_t	m_uiRevID;
	void*		m_pvRendererData;

	const NiColor& GetSpecularColor() const {
		return m_kSpec;
	}

	void SetSpecularColor(const NiColor& arSpecular) {
		m_kSpec = arSpecular;
	}

	const NiColor& GetEmittanceColor() const {
		return m_kEmit;
	}

	void SetEmittanceColor(const NiColor& arEmittance) {
		m_kEmit = arEmittance;
	}

	float GetShineness() const {
		return m_fShine;
	}

	void SetShineness(float afShine) {
		m_fShine = afShine;
	}

	float GetAlpha() const {
		return m_fAlpha;
	}

	void SetAlpha(float afAlpha) {
		m_fAlpha = afAlpha;
	}

	float GetEmittanceMult() const {
		return m_fEmitMult;
	}

	void SetEmittanceMult(float afEmitMult) {
		m_fEmitMult = afEmitMult;
	}
};

// 1C
class NiAlphaProperty : public NiProperty {
public:
	NiAlphaProperty();
	~NiAlphaProperty();

	struct ALIGN2 _Flags {
		bool	bAlphaBlending	: 1;
		uint8_t ucSrcBlend		: 4;
		uint8_t					: 3; // Dest blend is split due to padding issues
		uint8_t					: 1; 
		bool	bAlphaTesting	: 1;
		uint8_t ucTestFunc		: 3;
		bool	bNoSorter		: 1;
	};
	using Flags = _Flags;

	enum AlphaFlags {
		ALPHA_BLEND_MASK	= 0x0001,
		SRC_BLEND_MASK		= 0x001E,
		SRC_BLEND_POS		= 1,
		DEST_BLEND_MASK		= 0x01E0,
		DEST_BLEND_POS		= 5,

		TEST_ENABLE_MASK	= 0x0200,
		TEST_FUNC_MASK		= 0x1C00,
		TEST_FUNC_POS		= 10,
		ALPHA_NOSORTER_MASK = 0x2000
	};

	enum AlphaFunction {
		ALPHA_ONE			= 0,
		ALPHA_ZERO			= 1,
		ALPHA_SRCCOLOR		= 2,
		ALPHA_INVSRCCOLOR	= 3,
		ALPHA_DESTCOLOR		= 4,
		ALPHA_INVDESTCOLOR	= 5,
		ALPHA_SRCALPHA		= 6,
		ALPHA_INVSRCALPHA	= 7,
		ALPHA_DESTALPHA		= 8,
		ALPHA_INVDESTALPHA	= 9,
		ALPHA_SRCALPHASAT	= 10,
		ALPHA_MAX_MODES
	};

	enum TestFunction {
		TEST_ALWAYS			= 0,
		TEST_LESS			= 1,
		TEST_EQUAL			= 2,
		TEST_LESSEQUAL		= 3,
		TEST_GREATER		= 4,
		TEST_NOTEQUAL		= 5,
		TEST_GREATEREQUAL	= 6,
		TEST_NEVER			= 7,
		TEST_MAX_MODES
	};


	Bitfield<_Flags>	m_usFlags;
	uint8_t				m_ucAlphaTestRef;

	bool GetAlphaBlending() const {
		return m_usFlags.bAlphaBlending;
	}

	void SetAlphaBlending(bool abBlend) {
		m_usFlags.bAlphaBlending = abBlend;
	}

	bool GetAlphaTesting() const {
		return m_usFlags.bAlphaTesting;
	}

	void SetAlphaTesting(bool abTest) {
		m_usFlags.bAlphaTesting = abTest;
	}

	uint8_t GetTestRef() const {
		return m_ucAlphaTestRef;
	}

	void SetTestRef(uint8_t aucRef) {
		m_ucAlphaTestRef = aucRef;
	}

	AlphaFunction GetSrcBlendMode() const {
		return static_cast<AlphaFunction>(m_usFlags.ucSrcBlend);
	}

	void SetSrcBlendMode(AlphaFunction aeSrcBlend) {
		m_usFlags.ucSrcBlend = aeSrcBlend;
	}

	AlphaFunction GetDestBlendMode() const {
		return static_cast<AlphaFunction>(m_usFlags.Get(DEST_BLEND_MASK, DEST_BLEND_POS));
	}

	void SetDestBlendMode(AlphaFunction aeDestBlend) {
		m_usFlags.Set(aeDestBlend, DEST_BLEND_MASK, DEST_BLEND_POS);
	}

	TestFunction GetTestMode() const {
		return static_cast<TestFunction>(m_usFlags.ucTestFunc);
	}

	void SetTestMode(TestFunction aeTestFunc) {
		m_usFlags.ucTestFunc = aeTestFunc;
	}
};

// 30
class NiTexturingProperty : public NiProperty {
public:
	NiTexturingProperty();
	~NiTexturingProperty();

	uint32_t				unk18[6];	// 18
};

// 24
class NiStencilProperty : public NiProperty {
public:
	NiStencilProperty();
	~NiStencilProperty();

	enum TestFunc {
		TEST_NEVER,
		TEST_LESS,
		TEST_EQUAL,
		TEST_LESSEQUAL,
		TEST_GREATER,
		TEST_NOTEQUAL,
		TEST_GREATEREQUAL,
		TEST_ALWAYS,
		TEST_MAX
	};

	enum Action {
		ACTION_KEEP,
		ACTION_ZERO,
		ACTION_REPLACE,
		ACTION_INCREMENT,
		ACTION_DECREMENT,
		ACTION_INVERT,
		ACTION_MAX
	};

	enum {
		ENABLE_MASK			= 0x1,
		FAILACTION_MASK		= 0xE,
		FAILACTION_POS		= 0x1,
		ZFAILACTION_MASK	= 0x70,
		ZFAILACTION_POS		= 0x4,
		PASSACTION_MASK		= 0x380,
		PASSACTION_POS		= 0x7,
		DRAWMODE_MASK		= 0xC00,
		DRAWMODE_POS		= 0xA,
		TESTFUNC_MASK		= 0xF000,
		TESTFUNC_POS		= 0xC,
	};

	enum DrawMode {
		DRAW_CCW_OR_BOTH	= 0,
		DRAW_CCW			= 1,
		DRAW_CW				= 2,
		DRAW_BOTH			= 3,
		DRAW_MAX,
	};

	struct ALIGN2 _Flags {
		bool	bEnabled		: 1;
		uint8_t ucFailAction	: 3;
		uint8_t ucZFailAction	: 3;
		uint8_t					: 1; // Pass action is split due to padding issues
		uint8_t					: 2;
		uint8_t ucDrawMode		: 2;
		uint8_t ucTestFunc		: 4;
	};
	using Flags = _Flags;

	Bitfield<_Flags>	m_usFlags;
	uint32_t			m_uiRef;
	uint32_t			m_uiMask;

	bool GetStencilOn() const {
		return m_usFlags.bEnabled;
	}

	void SetStencilOn(bool abEnabled) {
		m_usFlags.bEnabled = abEnabled;
	}

	uint32_t GetStencilReference() const {
		return m_uiRef;
	}

	void SetStencilReference(uint32_t auiRef) {
		m_uiRef = auiRef;
	}

	uint32_t GetStencilMask() const {
		return m_uiMask;
	}

	void SetStencilMask(uint32_t auiMask) {
		m_uiMask = auiMask;
	}

	Action GetStencilFailAction() const {
		return static_cast<Action>(m_usFlags.ucFailAction);
	}

	void SetStencilFailAction(Action aeAction) {
		m_usFlags.ucFailAction = aeAction;
	}

	Action GetStencilZFailAction() const {
		return static_cast<Action>(m_usFlags.ucZFailAction);
	}

	void SetStencilZFailAction(Action aeAction) {
		m_usFlags.ucZFailAction = aeAction;
	}

	Action GetStencilPassAction() const {
		return static_cast<Action>((m_usFlags.Get(PASSACTION_MASK, PASSACTION_POS)));
	}

	void SetStencilPassAction(Action aeAction) {
		m_usFlags.Set(aeAction, PASSACTION_MASK, PASSACTION_POS);
	}

	void SetDrawMode(NiStencilProperty::DrawMode aeDraw) {
		m_usFlags.ucDrawMode = aeDraw;
	}

	NiStencilProperty::DrawMode GetDrawMode() const {
		return static_cast<NiStencilProperty::DrawMode>(m_usFlags.ucDrawMode);
	}

	void SetStencilFunction(NiStencilProperty::TestFunc aeFunc) {
		m_usFlags.ucTestFunc = aeFunc;
	}

	NiStencilProperty::TestFunc GetStencilFunction() const {
		return static_cast<NiStencilProperty::TestFunc>(m_usFlags.ucTestFunc);
	}
};
static_assert(sizeof(NiStencilProperty) == 0x24);

// 1C
class NiCullingProperty : public NiProperty {
public:
	NiCullingProperty();
	~NiCullingProperty();

	uint32_t				unk18;		// 18
};

class NiShadeProperty : public NiProperty {
public:
	Bitfield16	m_usFlags;
	int32_t		iShaderPropertyType;
};
ASSERT_SIZE(NiShadeProperty, 0x20);

class ShadowSceneLight;
class BSShaderAccumulator;

// 60
class BSShaderProperty : public NiShadeProperty {
public:
	BSShaderProperty();
	~BSShaderProperty();

	class RenderPass {
	public:
		NiGeometry*			pGeometry;
		uint16_t			usPassEnum;
		uint8_t				eAccumulationHint;
		bool				bFirstPass;
		bool				bLastPass;
		uint8_t				ucNumLights;
		uint8_t				ucMaxNumLights;
		uint8_t				ucExtraParam;
		ShadowSceneLight**	ppSceneLights;
	};

	class RenderPassArray : public NiTObjectArray<RenderPass*> {
	public:
		uint32_t uiPassCount;
	};

	virtual void						CopyTo(BSShaderProperty* apTarget);
	virtual void						CopyToMembers(BSShaderProperty* apTarget);
	virtual void						SetupGeometry(NiGeometry* apGeometry);
	virtual RenderPassArray*			GetRenderPasses(const NiGeometry* apGeometry, const uint32_t auiEnabledPasses, uint16_t* apusPassCount, const uint32_t aeRenderMode, BSShaderAccumulator* apAccumulator, bool abAddPass);
	virtual uint16_t					GetNumberofPasses(NiGeometry* apGeometry);
	virtual RenderPassArray*			GetSIBlockRenderPasses() const;
	virtual RenderPass*					GetRenderDepthPass(NiGeometry* apGeometry);
	virtual BSShaderProperty*			ClarifyShader(NiGeometry* apGeometry, bool unk0 = 0, bool unk2 = 1);
	virtual NiSourceTexture*			GetBaseTexture() const;
	virtual RenderPassArray*			GetWaterFogPassList(NiGeometry* apGeometry);
	virtual void						GetTextureUse(void* apCountFunc, class BGSTextureUseMap* apTexMap) const;
	virtual void						PrecacheTextures() const;

	Bitfield32			ulFlags[2];
	float				fAlpha;
	float				fFadeAlpha;
	float				fEnvMapScale;
	float				fCameraDistance;
	int32_t				iLastRenderPassState;
	RenderPassArray*	pRenderPassArray;
	RenderPassArray*	pDepthMapRenderPassArray;
	RenderPassArray*	pConstAlphaRenderPassArray;
	RenderPassArray*	pLocalMapRenderPassArray;
	RenderPassArray*	pSIBlockRenderPassArray;
	RenderPassArray*	pWaterFogRenderPassArray;
	RenderPassArray*	pSilhouettePassArray;
	int32_t				iShader;
	float				fDepthBias;

	void ClearRenderPasses() {
		if (pRenderPassArray)
			pRenderPassArray->uiPassCount = 0;
	}

	void InvalidateState() {
		iLastRenderPassState = -1;
	}
};
static_assert(sizeof(BSShaderProperty) == 0x60);

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

class NiDynamicEffectState;

// 9C
class NiAVObject : public NiObjectNET {
public:
	NiAVObject();
	~NiAVObject();

	virtual void			UpdateControllers(NiUpdateData& arData);
	virtual void			ApplyTransform(NiMatrix3& arMat, NiPoint3& arTrn, bool abOnLeft);
	virtual void			SetMaterialNeedsUpdate(bool abNeedsUpdate);
	virtual void			SetDefaultMaterialNeedsUpdateFlag(bool abNeedsUpdate);
	virtual NiAVObject*		GetObjectByName(const NiFixedString& arName) const;
	virtual void			SetSelectiveUpdateFlags(bool& arSelectiveUpdate, bool abSelectiveUpdateTransforms, bool& arRigid);
	virtual void			UpdateDownwardPass(NiUpdateData& arData, uint32_t auiFlags);
	virtual void			UpdateSelectedDownwardPass(NiUpdateData& arData, uint32_t auiFlags);
	virtual void			UpdateRigidDownwardPass(NiUpdateData& arData, uint32_t auiFlags);
	virtual void			UpdatePropertiesDownward(NiPropertyState* apParentState);
	virtual void			UpdateEffectsDownward(NiDynamicEffectState* apEffectState);
	virtual void			UpdateWorldData(NiUpdateData& arData);
	virtual void			UpdateWorldBound();
	virtual void			UpdateTransformAndBounds(NiUpdateData& arData);
	virtual void			PreAttachUpdate(NiNode* apEventualParent, NiUpdateData& arData);
	virtual void			PreAttachUpdateProperties(NiNode* apEventualParent);
	virtual void			PreAttachUpdateEffects(NiNode* apEventualParent);
	virtual void			PostAttachUpdate();
	virtual void			OnVisible(NiCullingProcess* apCuller);
	virtual void			PurgeRendererData(NiDX9Renderer* apRenderer);

	NiNode*							m_pkParent;				// 18
	NiPointer<bhkNiCollisionObject>	m_spCollisionObject;		// 1C
	NiBound*						m_pWorldBound;			// 20
	DList<NiProperty>				m_propertyList;			// 24
	Bitfield32						m_uiFlags;				// 30
	NiTransform						m_kLocal;
	NiTransform						m_kWorld;

#ifdef GAME
	static constexpr AddressPtr<NiBound, 0x11F4288> kNullBound;
#else
	static constexpr AddressPtr<NiBound, 0xF1FD88> kNullBound;
#endif

	NiProperty* GetProperty(uint32_t auiType) const;

	void SetAppCulled(bool abCulled) {
		m_uiFlags.Set(1, abCulled);
	}

	bool GetAppCulled() const {
		return m_uiFlags.GetBit(0);
	}

	void SetAlwaysDraw(bool abVal) {
		ThisCall(0x546780, this, abVal);
	}

	void SetFixedBound(bool abVal) {
		m_uiFlags.Set(0x2000, abVal);
	}

	void SetIgnoreFade(bool abVal) {
		m_uiFlags.Set(0x8000, abVal);
	}

	void DumpProperties();
	void DumpParents();

	void Update(NiUpdateData& arData) {
		ThisCall(0xA59C60, this, &arData);
	}

	void Update() {
		NiUpdateData kData;
		Update(kData);
	}

	void UpdateSelected(NiUpdateData& arData) {
		ThisCall(0xA59C90, this, &arData);
	}

	void UpdateSelected() {
		NiUpdateData kData;
		Update(kData);
	}

	void UpdateProperties() {
		ThisCall(0xA5A040, this);
	}

	void SetLocalRotate(const NiMatrix3& arMat) {
		m_kLocal.m_kRotate = arMat;
	}

	void SetLocalTranslate(const NiPoint3& arTrn) {
		m_kLocal.m_kTranslate = arTrn;
	}

	void SetLocalScale(float afScale) {
		m_kLocal.m_fScale = afScale;
	}

	NiTimeController* GetController(const NiRTTI* apRTTI) const {
		return ThisCall<NiTimeController*>(0xA5C570, this, apRTTI);
	}

	template <class ControllerType>
	ControllerType* GetController() const {
		return static_cast<ControllerType*>(GetController(&ControllerType::ms_RTTI));
	}

	const NiBound& GetWorldBound() const {
		return m_pWorldBound ? *m_pWorldBound : kNullBound;
	}

	NiNode* GetParent() const {
		return m_pkParent;
	}
};

// AC
class NiNode : public NiAVObject {
public:
	NiNode();
	~NiNode();

	virtual void	AttachChild(NiAVObject* apChild, bool abFirstAvail);
	virtual void	InsertChildAt(uint32_t i, NiAVObject* apChild);
	virtual void	DetachChildAlt(NiAVObject* apChild, NiPointer<NiAVObject>& arResult);
	virtual void	DetachChild(NiAVObject* apChild);
	virtual void	DetachChildAtAlt(uint32_t i, NiPointer<NiAVObject>& arResult);
	virtual void	DetachChildAt(uint32_t i);
	virtual void	SetAtAlt(uint32_t i, NiAVObject* apChild, NiPointer<NiAVObject>& arResult);
	virtual void	SetAt(uint32_t i, NiAVObject* apChild);
	virtual void	UpdateUpwardPass();

	NiTObjectArray<NiPointer<NiAVObject>>	m_kChildren;		// 9C

	static NiNode* Create(uint16_t ausChildCount = 0);

	NiAVObject* GetBlock(const char* blockName);
	NiNode* GetNode(const char* nodeName);

	uint32_t GetArrayCount() const {
		return m_kChildren.GetSize();
	}

	uint32_t GetChildCount() const {
		return m_kChildren.GetEffectiveSize();
	}

	NiAVObject* GetAt(uint32_t auiIndex) const {
		return m_kChildren.GetAt(auiIndex);
	}

	NiAVObject* GetAtChecked(uint32_t auiIndex) const {
		if (GetArrayCount() <= auiIndex)
			return nullptr;

		return GetAt(auiIndex);
	}

	void RemoveChildren() {
		m_kChildren.RemoveAll();
	}
};
static_assert(sizeof(NiNode) == 0xAC);

class NiSwitchNode : public NiNode {
public:
	struct ALIGN2 _SwitchFlags {
		enum Flags : uint16_t {
			UPDATE_ONLY_ACTIVE_CHILD	= 1u << 0,
			UPDATE_CONTROLLERS			= 1u << 1,
		};

		bool bUpdateOnlyActiveChild : 1;
		bool bUpdateControllers		: 1;
	};
	using SwitchFlags = _SwitchFlags::Flags;

	Bitfield<_SwitchFlags>		m_usFlags;
	int32_t						m_iIndex;
	float						m_fSavedTime;
	uint32_t					m_uiRevID;
	NiTPrimitiveArray<uint32_t>	m_kChildRevID;

	NIRTTI_ADDRESS(0x11F5EB4);

	void SetIndex(int32_t aiIndex) {
		if (aiIndex >= -1 && aiIndex < static_cast<int32_t>(m_kChildren.GetSize()))
			m_iIndex = aiIndex;
	}

	int32_t GetIndex() const {
		return m_iIndex;
	}
};

class NiCamera;
class NiLODNode;

class NiLODData : public NiObject {
public:
	NiLODData();
	virtual ~NiLODData();

	virtual int32_t		GetLODLevel(const NiCamera* apCamera, NiLODNode* apLOD);
	virtual void		UpdateWorldData(NiLODNode* apLOD);
	virtual NiLODData*	Duplicate();
	virtual int32_t		GetLODIndex(int32_t aiLODLevel);

	NIRTTI_ADDRESS(0x11F6050);
};

class NiLODNode : public NiSwitchNode {
public:
	NiLODNode();
	virtual ~NiLODNode();

	NiPointer<NiLODData>	m_spLODData;
	bool					m_bLODActive;

	NIRTTI_ADDRESS(0x11F5F1C);

#ifdef GAME
	static constexpr AddressPtr<int32_t, 0x11ABDF4> ms_iGlobalLOD;
#else
	static constexpr AddressPtr<int32_t, 0xEB6E44> ms_iGlobalLOD;
#endif
};

// E4
class BSFadeNode : public NiNode {
public:
	BSFadeNode();
	~BSFadeNode();

	float									fNearDistSqr;
	float									fFarDistSqr;
	float									fLastFade;
	float									fCurrentFade;
	float									fBoundRadius;
	float									fTimeSinceUpdate;
	uint32_t								eMultType;
	uint32_t								uiFrameCounter;
	TESObjectREFR*							pLinkedObj;
	void*									pBoundArray;
	BSSimpleList<class BSMultiBoundRoom*>	kParentRoomList;
	BSSimpleList<class BSPortal*>			kParentPortalList;

	CREATE_OBJECT(BSFadeNode, 0xB4EAA0);

	void TurnFadeNodeOn() {
		ThisCall(0x476AB0, this);
	};
};

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

// B4
class NiBillboardNode : public NiNode {
public:
	NiBillboardNode();
	~NiBillboardNode();

	virtual void	Unk_40(void);

	uint32_t			unkAC[2];		// AC
};

// 64
class BSFogProperty : public NiObjectNET {
public:
	BSFogProperty();
	~BSFogProperty();

	uint16_t				unk18;		// 18
	uint16_t				unk1A;		// 1A
	float				flt1C;		// 1C
	NiColor				color;		// 20
	float				distNear;	// 2C
	float				distFar;	// 30
	uint32_t				unk34;		// 34
	uint32_t				unk38;		// 38
	float				flt3C;		// 3C
	float				flt40;		// 40
	float				flt44;		// 44
	float				flt48;		// 48
	uint32_t				unk4C;		// 4C
	uint32_t				unk50;		// 50
	float				flt54;		// 54
	float				flt58;		// 58
	float				flt5C;		// 5C
	float				power;		// 60
};
static_assert(sizeof(BSFogProperty) == 0x64);


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

// 114
class NiCamera : public NiAVObject {
public:
	NiCamera();
	~NiCamera();

	float			m_aafWorldToCam[4][4];	// 09C
	NiFrustum		m_kViewFrustum;			// 0DC
	float			m_fMinNearPlaneDist;	// 0F8
	float			m_fMaxFarNearRatio;		// 0FC
	NiViewport		m_kPort;				// 100
	float			m_fLODAdjust;			// 110

	CREATE_OBJECT(NiCamera, 0xA71430);

	bool LookAtWorldPoint(const NiPoint3& arWorldPt, const NiPoint3& arWorldUp) {
		return ThisCall<bool>(0xA701B0, this, &arWorldPt, &arWorldUp);
	}

	void SetViewFrustum(const NiFrustum& arFrustum) {
		ThisCall(0xA6FAF0, this, &arFrustum);
	}
};
static_assert(sizeof(NiCamera) == 0x114);

// C4
class NiDynamicEffect : public NiAVObject {
public:
	NiDynamicEffect();
	~NiDynamicEffect();

	bool					m_bOn;
	uint8_t					m_ucEffectType;
#if JIP_LIGHTS
	bool					bResetTraits;
	Bitfield8				ucExtraFlags;
#endif
	int32_t					m_iIndex;
	uint32_t				m_uiPushCount;
	uint32_t				m_uiRevID;
	NiTPointerList<NiNode*>	m_kAffectedNodeList;
	NiTPointerList<NiNode*>	m_kUnaffectedNodeList;

	void IncRevisionID() { ++m_uiRevID; }
};

ASSERT_SIZE(NiDynamicEffect, 0xC4)

// F0
class NiLight : public NiDynamicEffect {
public:
	NiLight();
	~NiLight();

	float	m_fDimmer;
	NiColor m_kAmb;
	NiColor m_kDiff;
	union { // Bethesda reuses red specular color for light radius, JIP adds a pointer to the light object
		NiColor	 m_kSpec;
		struct {
			float			m_fRadius;
			float			_empty;
#if JIP_LIGHTS
			TESObjectLIGH*	pLightForm;
#else
			float			_empty2;
#endif
		};
	};
	void*	m_pvRendererData;

	NIRTTI_ADDRESS(0x11F4A28);

	float GetDimmer() const { return m_fDimmer; };

	// GAME - 0x50DD20
	void SetDimmer(float afDimmer) {
		m_fDimmer = afDimmer;
		IncRevisionID();
	}

	const NiColor& GetAmbientColor() const { return m_kAmb; };
	void SetAmbientColor(const NiColor& arColor) {
		m_kAmb = arColor;
		IncRevisionID();
	}

	const NiColor& GetDiffuseColor() const { return m_kDiff; };
	void SetDiffuseColor(const NiColor& arColor) {
		m_kDiff = arColor;
		IncRevisionID();
	}

	float GetLightRadius() const { return m_fRadius; };

	void SetLightRadius(float afRadius) {
		m_fRadius = afRadius;
		IncRevisionID();
	}
};

ASSERT_SIZE(NiLight, 0xF0)

// FC
class NiPointLight : public NiLight {
public:
	NiPointLight();
	~NiPointLight();

	union {
		struct {
			float m_fAtten0;
			float m_fAtten1;
			float m_fAtten2;
		};
		NiPoint3 m_kLightOffset;
	};

	CREATE_OBJECT(NiPointLight, 0xA7D6E0);
	NIRTTI_ADDRESS(0x11F4A98);
};

class NiSpotLight : public NiPointLight {
public:
	NiSpotLight();
	~NiSpotLight();

	NiPoint3	m_kWorldDir;
	float		m_fOuterSpotAngle;
	float		m_fInnerSpotAngle;
	float		m_fSpotExponent;

	CREATE_OBJECT(NiSpotLight, 0xA94E20);
	NIRTTI_ADDRESS(0x11F5EC4);

	float GetOuterSpotAngle() const { return m_fOuterSpotAngle; };
	void SetOuterSpotAngle(float afAngle) {
		m_fOuterSpotAngle = afAngle;
		IncRevisionID();
	};

	float GetInnerSpotAngle() const { return m_fInnerSpotAngle; };
	void SetInnerSpotAngle(float afAngle) {
		m_fInnerSpotAngle = afAngle;
		IncRevisionID();
	};

	float GetSpotExponent() const { return m_fSpotExponent; };
	void SetSpotExponent(float afExponent) {
		m_fSpotExponent = afExponent;
		IncRevisionID();
	};
};

// FC
class NiDirectionalLight : public NiLight {
public:
	NiDirectionalLight();
	~NiDirectionalLight();

	NiPoint3		m_kWorldDir;
};

class BSCullingProcess;

class BSSceneGraph : public NiNode {
public:
	BSSceneGraph();
	~BSSceneGraph();

	virtual float	GetFarDistance();
	virtual void	SetViewDistanceBasedOnFrameRate(float afTime);

	NiPointer<NiCamera> spCamera;
	NiVisibleArray*		pVisArray;
	BSCullingProcess*	pCuller;
	bool				bMenuSceneGraph;
	float				fCurrentFOV;

	NiNode* GetCameraRoot() const {
		return static_cast<NiNode*>(GetAtChecked(0));
	}
};

// C0
class SceneGraph : public BSSceneGraph {
public:
	SceneGraph();
	~SceneGraph();
};

// 3C
class TESAnimGroup : public NiRefObject {
public:
	TESAnimGroup();
	~TESAnimGroup();

	uint32_t			unk08[2];	// 08
	uint8_t			index;		// 10
	uint8_t			unk11;		// 11
	uint8_t			unk12[1];	// 12
	uint32_t			unk14[10];	// 14
};

// 78
class BSAnimGroupSequence : public NiControllerSequence {
public:
	BSAnimGroupSequence();
	~BSAnimGroupSequence();

	TESAnimGroup* animGroup;		// 74

	static bool PlaySounds(NiControllerSequence* apSequence, TESObjectREFR* apRef) {
		return CdeclCall<bool>(0x4EEF00, apSequence, apRef);
	}
};

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

// 30
class NiTexture : public NiObjectNET {
public:
	NiTexture();
	~NiTexture();

	virtual void	Unk_23(void);
	virtual void	Unk_24(void);
	virtual void	Unk_25(void);
	virtual void	Unk_26(void);
	virtual void	Unk_27(void);
	virtual void	Unk_28(void);

	enum {
		kPxlLayout_Palette8BPP = 0,
		kPxlLayout_Raw16BPP,
		kPxlLayout_Raw32BPP,
		kPxlLayout_Compressed,
		kPxlLayout_Bumpmap,
		kPxlLayout_Palette4BPP,
		kPxlLayout_Default,

		kAlphaFmt_None = 0,
		kAlphaFmt_Binary1BPP,
		kAlphaFmt_Smooth8BPP,
		kAlphaFmt_Default,

		kMipMapFmt_Disabled = 0,
		kMipMapFmt_Enabled,
		kMipMapFmt_Default,
	};

	uint32_t				pixelLayout;	// 18
	uint32_t				alphaFormat;	// 1C
	uint32_t				mipmapFormat;	// 20
	NiDX9TextureData* textureData;	// 24
	NiTexture* prev;			// 28
	NiTexture* next;			// 2C
};

// 48
class NiSourceTexture : public NiTexture {
public:
	NiSourceTexture();
	~NiSourceTexture();

	virtual void	Unk_29(void);
	virtual void	Unk_2A(void);
	virtual void	Unk_2B(void);

	char* ddsPath1;		// 30
	char* ddsPath2;		// 34
	uint32_t			unk38;			// 38
	uint32_t			unk3C;			// 3C
	uint8_t			byte40;			// 40
	uint8_t			byte41;			// 41
	uint8_t			byte42;			// 42
	uint8_t			byte43;			// 43
	uint32_t			unk44;			// 44
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

struct NiTriangle {
	uint16_t		point1;
	uint16_t		point2;
	uint16_t		point3;
};

// 54
class RendererData		//	010F017C
{
public:
	RendererData();
	~RendererData();

	virtual RendererData* Destructor(bool doFree);
	virtual bool			Unk_01(uint32_t arg1);

	uint32_t						flags;			// 04
	NiUnsharedGeometryGroup* unsharedGeom;	// 08
	uint32_t						unk0C;			// 0C
	void* ptr10;			// 10
	uint32_t						unk14;			// 14
	uint32_t						unk18;			// 18	Vertices/Normals count
	uint32_t						unk1C;			// 1C		"			"
	uint32_t						finished;		// 20
	void* ptr24;			// 24
	void* ptr28;			// 28
	uint32_t						trianglePoints;	// 2C
	uint32_t						unk30;			// 30	Byte size of triangles array
	void* ptr34;			// 34
	uint32_t						unk38;			// 38
	uint32_t						unk3C;			// 3C
	uint32_t						unk40;			// 40	Triangle count
	uint32_t						unk44;			// 44		"
	uint32_t						unk48;			// 48
	uint32_t						unk4C;			// 4C
	NiTriangle* triangles;		// 50	Same ptr as in NiTriShapeData
};
static_assert(sizeof(RendererData) == 0x54);

// 40
class NiGeometryData : public NiObject {
public:
	NiGeometryData();
	~NiGeometryData();

	virtual void	Unk_23(uint32_t arg);
	virtual void	Unk_24(void);
	virtual void	Unk_25(void);
	virtual void	Unk_26(void);
	virtual bool	Unk_27(uint32_t arg);
	virtual void	Unk_28(void);

	uint16_t			numVertices;	// 08
	uint16_t			word0A;			// 0A
	uint16_t			word0C;			// 0C
	uint16_t			word0E;			// 0E
	NiBound		bounds;			// 10
	NiPoint3* vertices;		// 20
	NiPoint3* normals;		// 24
	NiColorA* vertexColors;	// 28
	UVCoord* uvCoords;		// 2C
	uint32_t			unk30;			// 30
	RendererData* rendererData;	// 34
	uint8_t			byte38;			// 38
	uint8_t			byte39;			// 39
	uint8_t			byte3A;			// 3A
	uint8_t			byte3B;			// 3B
	uint32_t			unk3C;			// 3C
};
static_assert(sizeof(NiGeometryData) == 0x40);

// 44
class NiTriBasedGeomData : public NiGeometryData {
public:
	NiTriBasedGeomData();
	~NiTriBasedGeomData();

	virtual void	Unk_29(uint32_t arg);
	virtual void	Unk_2A(void);
	virtual void	Unk_2B(uint32_t arg1, uint32_t arg2, uint32_t arg3, uint32_t arg4);
	virtual void	Unk_2C(uint32_t arg1, uint32_t arg2, uint32_t arg3, uint32_t arg4);

	uint16_t			numTriangles;		// 40
	uint8_t			pad42[2];			// 42
};

// 58
class NiTriShapeData : public NiTriBasedGeomData {
public:
	NiTriShapeData();
	~NiTriShapeData();

	uint32_t			trianglePoints;	// 44
	NiTriangle* triangles;		// 48
	uint16_t* points;		// 4C
	uint32_t			unk50;			// 50
	uint32_t			unk54;			// 54
};
static_assert(sizeof(NiTriShapeData) == 0x58);

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

// C4
class NiGeometry : public NiAVObject {
public:
	NiGeometry();
	~NiGeometry();

	virtual void	Unk_37(uint32_t arg1);
	virtual void	Unk_38(uint32_t arg1);
	virtual void	Unk_39(void);
	virtual void	Unk_3A(void);
	virtual void	Unk_3B(uint32_t arg1);

	NiAlphaProperty*		alphaProp;		// 9C	Seen NiAlphaProperty
	NiProperty*				niPropA0;		// A0	Seen NiCullingProperty
	NiMaterialProperty*		materialProp;		// A4	Seen NiMaterialProperty
	BSShaderProperty*		shaderProp;		// A8	Seen TileShaderProperty
	NiStencilProperty*		stencilProp;		// AC	Seen NiStencilProperty
	NiTexturingProperty*	texturingProp;		// B0	Seen NiTexturingProperty
	uint32_t					unkB4;			// B4
	NiGeometryData*			geometryData;	// B8	Seen NiTriShapeData
	uint32_t					unkBC;			// BC
	NiShader*				shader;		// C0
};
static_assert(sizeof(NiGeometry) == 0xC4);

// C4
class NiTriBasedGeom : public NiGeometry {
public:
	NiTriBasedGeom();
	~NiTriBasedGeom();

	virtual void	Unk_3C(uint32_t arg1, uint32_t arg2, uint32_t arg3, uint32_t arg4);
};

// C4
class NiTriShape : public NiTriBasedGeom {
public:
	NiTriShape();
	~NiTriShape();
};

// D4
class BSScissorTriShape : public NiTriShape {
public:
	BSScissorTriShape();
	~BSScissorTriShape();

	uint32_t			unkC4;			// C4
	uint32_t			unkC8;			// C8
	uint32_t			width;			// CC
	uint32_t			height;			// D0
};
static_assert(sizeof(BSScissorTriShape) == 0xD4);

// 14C
class ParticleShaderProperty : public BSShaderProperty {
public:
	ParticleShaderProperty();
	~ParticleShaderProperty();

	uint32_t			unk060[59];		// 060
};
static_assert(sizeof(ParticleShaderProperty) == 0x14C);

class BSCompoundFrustum;

class NiTreeCtrl
{
public:
	static NiTreeCtrl* Create(NiNode* apNode)
	{
		NiTreeCtrl* pAlloc = CdeclCall<NiTreeCtrl*>(0x401000, 0x30U);

		DWORD* pTESMain = *(DWORD**)0x11DEA0C;
		return ThisCall<NiTreeCtrl*>(0x4D61B0, pAlloc, pTESMain[3], pTESMain[2], apNode, "Test", 0x80000000,
			0x80000000, 800, 600);
	}

	void CreateTree(NiNode* apNode, const char* apName)
	{
		ThisCall(0x4D64C0, this, apNode, apName);
	}
};

class NiRenderTargetGroup : public NiObject {
public:
	// has more data but not needed atm
};

class NiStream {
public:
	static void RegisterLoader(const char* apName, void* apFunction) {
#if GAME
		CdeclCall(0xA64900, apName, apFunction);
#else
		CdeclCall(0x81D570, apName, apFunction);
#endif
	}
};