#pragma once

#include "NiProperty.hpp"
#include "NiTPointerList.hpp"
#include "NiTransform.hpp"
#include "Bethesda/NiUpdateData.hpp"

class NiCullingProcess;
class NiNode;
class NiCamera;
class bhkNiCollisionObject;
class NiFixedString;
class NiBound;
class NiPropertyState;
class NiRenderer;
class NiDynamicEffectState;

NiSmartPointer(NiAVObject);
NiSmartPointer(NiProperty);

class NiAVObject : public NiObjectNET {
public:
	NiAVObject();
	virtual ~NiAVObject();

	virtual void			UpdateControllers(NiUpdateData& arData);
	virtual void			ApplyTransform(const NiMatrix3& arRotation, const NiPoint3& arPosition, bool abOnLeft);
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
	virtual void			OnVisible(NiCullingProcess& arCuller);
	virtual void			PurgeRendererData(NiRenderer* apRenderer);

	// Used in Update calls
	struct _UpdateFlags {
		enum Flags : uint32_t {
			PARENT_IS_CULLED	= 1u << 0,
		};

		bool bParentIsCulled : 1;
	};
	using UpdateFlags = struct _UpdateFlags;

	struct _Flags {
		enum Flags : uint32_t {
		    APP_CULLED                              = 1u <<  0, // Forces culled state
			SELECTIVE_UPDATE						= 1u <<  1, // Allows selective updates - see flags below
		    SELECTIVE_UPDATE_TRANSFORMS             = 1u <<  2, // Allows transform controller update
			SELECTIVE_UPDATE_CONTROLLER				= 1u <<  3, // Allows controller update
		    SELECTIVE_UPDATE_RIGID                  = 1u <<  4, // Forces the use of UpdateRigidDownwardPass
		    DISPLAY_OBJECT                          = 1u <<  5, // Used only by sky objects
		    DISABLE_SORTING                         = 1u <<  6,	// Unused, just like Gamebryo's sorter
			SELECTIVE_UPDATE_TRANSFORMS_OVERRIDE	= 1u <<  7, // Forces UPDATE_TRANSFORMS even if node has no transform controllers
			OBJECT_PREPARED							= 1u <<  8, // Unused; Xbox 360, used to mark prepared objects by BSShaderManager::PrepareGeometry
		    TRANS_IS_IDENTITY						= 1u <<  9, // Assumes local transform is an identity one, skipping transformations
			NO_DECALS								= 1u << 10,	// Disables decals for this object
		    ALWAYS_DRAW                             = 1u << 11, // Forces light inclusion, and skips culling
			PREPROCESSED_NODE						= 1u << 12, // Used to mark actor nodes, for actor culling
		    FIXED_BOUND                             = 1u << 13, // Prevents bound updates
			FADED_IN								= 1u << 14, // BSFadeNode only; Marks the fade state
			IGNORE_FADE								= 1u << 15, // BSFadeNode only; Disables fading
			LOD_FADING_OUT							= 1u << 16, // BSFadeNode only; Looks unused
			HAS_MOVING_SOUND						= 1u << 17, // Used for sound updates
			HAS_PROPERTY_CONTROLLER					= 1u << 18, // Marks the presence of a property controller
			ORPHANED_BOUND							= 1u << 19, // Marks lack of a bound
		    NOT_VISIBLE                             = 1u << 20, // Used for actor culling
			IGNORES_PICKING							= 1u << 21, // Disables picking for this object
			WORLD_BOUND_CHANGE						= 1u << 22,	// Forces multibound update/attachment
			NOT_SHADOW_RECEIVER						= 1u << 23, // Set if bActorSelfShadowing == false, checks for it look broken (maybe why the setting doesn't work?)
		    HIGH_DETAIL	                            = 1u << 24, // BSFadeNode only; Unused, meant for actors 0x936F75
			ALREADY_TRAVERSED						= 1u << 25, // Unused; Xbox 360, used for texture streaming
			UNK_26									= 1u << 26, // ??
		    PLAYER_BONE                             = 1u << 27,	// Marks player's bones, not read anywhere?
			RELEVANT_IMPOSTER						= 1u << 28, // BSFadeNode only; Marks the imposter state to override fading
		    IS_POINTLIGHT                           = 1u << 29, // Added by JIP
		    DONE_INIT_LIGHTS                        = 1u << 30, // Added by JIP
		    IS_INSERTED                             = 1u << 31  // Added by JIP
		};

        bool bAppCulled                     : 1;
		bool bSelUpdate						: 1;
        bool bSelUpdateTransforms           : 1;
		bool bSelUpdateController			: 1;
        bool bSelUpdateRigid                : 1;
        bool bDisplayObject                 : 1;
        bool bDisableSorting                : 1;
		bool bSelUpdateTransformsOverride	: 1;
		bool								: 1; // OBJECT_PREPARED on Xbox 360
        bool bTransIsIdentity				: 1;
		bool bNoDecals						: 1;
        bool bAlwaysDraw                    : 1;
		bool bPreprocessedNode				: 1;
        bool bFixedBound                    : 1;
		bool bFadedIn						: 1;
		bool bIgnoreFade					: 1;
		bool bLODFadingOut					: 1;
		bool bHasMovingSound				: 1;
		bool bHasPropertyController			: 1;
		bool bOrphanedBound					: 1;
        bool bNotVisible                    : 1;
		bool bIgnoresPicking				: 1;
		bool bWorldBoundChange				: 1;
		bool bNoShadows						: 1;
        bool bHighDetail	                : 1;
		bool								: 1; // ALREADY_TRAVERSED on Xbox 360
		bool								: 1;
        bool bPlayerBone                    : 1;
		bool bRelevantImposter				: 1;
        bool bIsPointlight                  : 1;
        bool bDoneInitLights                : 1;
        bool bIsInserted                    : 1;
	};
	using NiFlags = _Flags::Flags;

	NiNode*							m_pkParent;
	NiPointer<bhkNiCollisionObject> m_spCollisionObject;
	NiBound*						m_pWorldBound;
	NiTPointerList<NiPropertyPtr>	m_kPropertyList;
	Bitfield<_Flags>				m_uiFlags;
	NiTransform						m_kLocal;
	NiTransform						m_kWorld;

	NIRTTI_ADDRESS(0x11F4280);

#ifdef GAME
	static constexpr AddressPtr<BSSpinLock, 0x11F42A0> kPropertyStateLock;
	static constexpr AddressPtr<NiBound, 0x11F4288> kNullBound;
#else
	static constexpr AddressPtr<BSSpinLock, 0xF1FDA0> kPropertyStateLock;
	static constexpr AddressPtr<NiBound, 0xF1FD88> kNullBound;
#endif

	const NiTransform& GetLocalTransform() const;

	const NiTransform& GetWorldTransform() const;

	const float GetLocalScale() const;
	void SetLocalScale(float afScale);

	const float GetWorldScale() const;
	void SetWorldScale(float afScale);

	const NiPoint3& GetLocalTranslate() const;
	void SetLocalTranslate(const NiPoint3& arPos);
	void SetLocalTranslate(float afX, float afY, float afZ);

	const NiPoint3& GetWorldTranslate() const;
	void SetWorldTranslate(const NiPoint3& arPos);

	const NiMatrix3& GetLocalRotate() const;
	void SetLocalRotate(const NiMatrix3& arRot);
	void SetLocalRotate(float afX, float afY, float afZ);
	void SetLocalRotate(float afAngle, float afX, float afY, float afZ);
	void SetLocalRotateDeg(float afX, float afY, float afZ);
	void SetRotateAboutCenter(const NiMatrix3& arRot, const NiPoint3& arCenter, const NiPoint3& arTranslate);

	const NiMatrix3& GetWorldRotate() const;
	void SetWorldRotate(const NiMatrix3& arRot);

	NiNode* GetParent();
	const NiNode* GetParent() const;

	void AttachParent(NiNode* apParent);
	void DetachParent();

	NiProperty* GetProperty(NiProperty::PropertyType aePropertyType) const;

	void AttachProperty(NiProperty* apProperty);
	void DetachProperty(NiProperty* apProperty);

	void RemoveProperty(NiProperty::PropertyType aePropertyType);
	void RemoveProperty(NiProperty::PropertyType aePropertyType, NiPointer<NiProperty>& arRemovedProperty);

	void UpdateProperties();

	void PushLocalProperties(NiPropertyState* apParentState, bool abCopyOnChange, NiPropertyState*& apOut);

	bool HasPropertyController() const;
	bool HasTransformController() const;

	const NiBound& GetWorldBound() const;
	void CreateBoundIfNone();

	bhkNiCollisionObject* GetCollisionObject() const;
	void SetCollisionObject(bhkNiCollisionObject* apCollisionObject);

	void Update(NiUpdateData& arData);
	SPEC_INLINE void Update() { NiUpdateData kData; Update(kData); }

	void UpdateSelected(NiUpdateData& arData);
	SPEC_INLINE void UpdateSelected() { NiUpdateData kData; UpdateSelected(kData); }

	void DoSelectedUpdate(NiUpdateData& arData, uint32_t auiFlags);

	void UpdateWorldLoc();

	void UpdateObjectControllers(NiUpdateData& arData, bool abUpdateProperties);

	void Cull(NiCullingProcess& arCuller);

	bool IsVisualObject() const;

	bool IsUnCulledVisualObject() const;

	// FLAGS

	void SetBit(uint32_t auiData, bool abVal);
	bool GetBit(uint32_t auiData) const;

	void SetAppCulled(bool abVal);
	bool GetAppCulled() const;

	void SetSelectiveUpdate(bool abVal);
	bool GetSelectiveUpdate() const;

	void SetSelectiveUpdateTransforms(bool abVal);
	bool GetSelectiveUpdateTransforms() const;

	void SetSelectiveUpdateControllers(bool abVal);
	bool GetSelectiveUpdateControllers() const;

	void SetSelectiveUpdateRigid(bool abVal);
	bool GetSelectiveUpdateRigid() const;

	void SetDisplayObject(bool abVal);
	bool GetDisplayObject() const;

	void SetDisableSorting(bool abVal);
	bool GetDisableSorting() const;

	void SetSelUpdTransformsOverride(bool abVal);
	bool GetSelUpdTransformsOverride() const;

	void SetTransIsIdentity(bool abVal);
	bool GetTransIsIdentity() const;

	void SetNoDecals(bool abVal);
	bool GetNoDecals() const;

	void SetAlwaysDraw(bool abVal);
	bool GetAlwaysDraw() const;

	void SetPreProcessedNode(bool abVal);
	bool GetPreProcessedNode() const;

	void SetFixedBound(bool abVal);
	bool GetFixedBound() const;

	void SetFadedIn(bool abVal);
	bool GetFadedIn() const;

	void SetIgnoreFade(bool abVal);
	bool GetIgnoreFade() const;

	void SetLODFadingOut(bool abVal);
	bool GetLODFadingOut() const;

	void SetHasMovingSound(bool abVal);
	bool GetHasMovingSound() const;

	void SetHasPropertyController(bool abVal);
	bool GetHasPropertyController() const;

	void SetHasOrphanedBound(bool abVal);
	bool GetHasOrphanedBound() const;

	void SetNotVisible(bool abVal);
	bool GetNotVisible() const;

	void SetIgnoresPicking(bool abVal);
	bool GetIgnoresPicking() const;

	void SetWorldBoundChange(bool abVal);
	bool GetWorldBoundChange() const;

	void SetNoShadows(bool abVal);
	bool GetNoShadows() const;

	void SetPlayerBone(bool abVal);
	bool GetIsPlayerBone() const;

	void SetRelevantImposter(bool abVal);
	bool GetRelevantImposter() const;

	void AddGarbageMark();
	void RemoveGarbageMark();
};

ASSERT_OFFSET(NiAVObject, m_pkParent, 0x18);
ASSERT_OFFSET(NiAVObject, m_spCollisionObject, 0x1C);
ASSERT_OFFSET(NiAVObject, m_pWorldBound, 0x20);
ASSERT_OFFSET(NiAVObject, m_kPropertyList, 0x24);
ASSERT_SIZE(NiTPointerList<NiPointer<NiProperty>>, 0xC);
ASSERT_OFFSET(NiAVObject, m_uiFlags, 0x30);
ASSERT_OFFSET(NiAVObject, m_kLocal, 0x34);
ASSERT_OFFSET(NiAVObject, m_kWorld, 0x68);
ASSERT_SIZE(NiAVObject, 0x9C);