#pragma once

#include "BSSoundHandle.hpp"
#include "ExtraContainerChanges.hpp"
#include "ExtraDataList.hpp"
#include "Gamebryo/NiAVObject.hpp"
#include "TESBoundObject.hpp"
#include "TESChildCell.hpp"

class LockData;
class DoorTeleportData;
class ExtraScript;
class ActorCause;
class ScriptLocals;
class TESContainer;
class TESSound;
class Animation;
class BipedAnim;
class NiGeometry;
class ExtraDroppedItemList;
class BSFaceGenNiNode;
class BSFaceGenAnimationData;
class BSAnimNoteReceiver;
class TESWorldSpace;
class MagicCaster;
class MagicTarget;
class TrapEntry;
class TargetEntry;
class TESActorBase;
class TESObjectWEAP;
class TESTopic;
class bhkPhantom;
class BGSPrimitive;
class BGSWorldLocation;
class TESModel;
class BGSLoadGameBuffer;
class TESTopicInfo;
class NiAVObject;

struct LoadedRefData;

struct ReferenceData {
	TESBoundObject* pObjectReference;
	NiPoint3		kRotation;
	NiPoint3		kPosition;
};

ASSERT_SIZE(ReferenceData, 0x1C);

class TESObjectREFR : public TESForm, public TESChildCell {
public:
	TESObjectREFR();
	~TESObjectREFR();

#ifdef GAME
	virtual bool					GetEditorLocation(NiPoint3& arPos, NiPoint3& arRot, TESForm*& apParentLocation, TESObjectCELL* apCell);
	virtual BSSoundHandle			VoiceSoundFunction(TESTopic* apTopic, Actor* apTarget, bool ab2DSound, bool abAlwaysPlay, bool abForceCorrectDuration, bool abSayTo, bool abForceSubtitles);
	virtual void					UpdateSoundCallBack();
	virtual void					DamageObject(float afDamage, bool abForce);
#endif
	virtual bool					GetCastShadows() const;
	virtual void					SetCastShadows(bool abVal);
	virtual bool					GetMotionBlur() const;
	virtual void					SetMotionBlur(bool abVal);
	virtual void					IsDangerous();
	virtual bool					IsObstacle() const;
#ifdef EDITOR
	virtual uint32_t				GetRefNavMeshGenType() const;
#endif
	virtual bool					IsQuestObject() const;
	virtual void					SetActorCause(ActorCause* apActorCause);
	virtual ActorCause*				GetActorCause() const;
	virtual NiPoint3				GetStartingAngle() const;
	virtual NiPoint3				GetStartingLocation() const;
	virtual void					SetStartingPosition(NiPoint3 akPos);
	virtual void					UpdateRefLight();
	virtual TESObjectREFR*			RemoveItem(TESBoundObject* apObject, ExtraDataList* apExtraList, uint32_t auiCount, bool abStealing, bool abDropWorld, TESObjectREFR* apOtherContainer, NiPoint3* apPoint, NiPoint3* apRotate, bool abDelete, bool abPreferStolen);
	virtual void					RemoveItemType(uint32_t auiTypeID, bool abStealing, uint32_t auiCount);
	virtual bool					AddWornItem(TESBoundObject* apObject, uint32_t auiCount, ExtraDataList* apExtraList, bool abForceEquip = false);
	virtual bool					RemoveWornItem(TESBoundObject* apObject, uint32_t auiCount, ExtraDataList* apExtraList);
	virtual void					DoTrap(TrapEntry*, TargetEntry*);
#ifdef GAME
	virtual void					AddObjecttoContainer(TESBoundObject* apObject, ExtraDataList* apExtraList, uint32_t auiCount);
	virtual NiPoint3				GetLookingAtLocation() const;
	virtual MagicCaster*			GetMagicCaster() const;
	virtual MagicTarget*			GetMagicTarget() const;
#endif
	virtual bool					IsChild(bool abCheckHeight);
	virtual TESActorBase*			GetTemplateActorBase() const;
	virtual void					SetTemplateActorBase(TESActorBase* apBase);
	virtual NiNode*					GetFaceNodeBiped(NiNode* apNode = nullptr) const;
	virtual BSFaceGenNiNode*		GetFaceNodeSkinned(NiNode* apNode = nullptr) const;
	virtual BSFaceGenNiNode*		GetFaceNode(NiNode* apNode = nullptr) const;
	virtual BSFaceGenAnimationData* GetFaceAnimationData(NiNode* apNode = nullptr) const;
	virtual bool					ClampToGround();
	virtual bool					DetachHavok();
	virtual void					InitHavok();
	virtual NiAVObject*				Load3D(bool abBackgroundLoading);
	virtual void					Set3D(NiAVObject* apObject, bool abDebugPrint);
	virtual NiAVObject*				Get3D() const;
	virtual bool					HasRandomAnim() const;
	virtual NiPoint3				GetBoundMin() const;
	virtual NiPoint3				GetBoundMax() const;
	virtual void					UpdateAnimation();
	virtual Animation*				GetAnimation() const;
	virtual BipedAnim*				GetBiped() const;
	virtual BipedAnim*				GetCurrentBiped() const;
	virtual void					SetBiped(BipedAnim* apBiped);
	virtual const NiPoint3&			GetLocationOnReference() const;
	virtual void					SetRunsInLow(bool abVal);
	virtual void					MoveHavok(bool abRecursive);
	virtual void					SetActionComplete(bool abVal);
	virtual void					SetMovementComplete(bool abVal);
#ifdef GAME
	virtual void					ResetInventory(bool abLeveledOnly);
	virtual NiNode*					GetFireNode() const;
	virtual void					SetFireNode(NiNode* apNode);
	virtual SIT_SLEEP_STATE			GetSitSleepState() const;
	virtual bool					IsCharacter() const;
	virtual bool					IsCreature() const;
	virtual bool					IsExplosion() const;
#endif
	virtual bool					IsProjectile() const;
	virtual void					SetParentCell(TESObjectCELL* apCell);
	virtual bool					IsDead(bool abNotEssential) const;
	virtual bool					IsKnockedOut() const;
	virtual bool					IsParalyzed() const;
	virtual BSAnimNoteReceiver*		CreateAnimNoteReceiver();
	virtual BSAnimNoteReceiver*		GetAnimNoteReceiever() const;

	TESSound*		pRandomSound;
	ReferenceData	kData;
	float			fRefScale;
	TESObjectCELL*	pParentCell;
	ExtraDataList	kExtraList;
#ifdef EDITOR
	void*			pUnk78;
	float			fTestRadius;
#endif
	LoadedRefData*	pLoadedData;

	TESFORM_TYPE(TESObjectREFR);

	TESBoundObject* GetObjectReference() const;
	void SetObjectReference(TESBoundObject* apObject);

	TESBoundObject* GetOriginalObjectReference() const;
#ifdef GAME
	TESBoundObject* GetTemplateObjectReference() const;
#endif

	bool GetIsOfType(const TESBoundObject* apObject) const;

	const NiPoint3& GetLocationOnReferenceSimple() const;
	inline const NiPoint3& GetPosition() const noexcept { return GetLocationOnReferenceSimple(); }
	void SetLocationOnReference(const NiPoint3& arPos);
	inline void SetPosition(const NiPoint3& arPos) noexcept { SetLocationOnReference(arPos); }

	const NiPoint3& GetAngleOnReference() const;
	inline const NiPoint3& GetRotation() const noexcept { return GetAngleOnReference(); }
	void SetAngleOnReference(NiPoint3 akRot);
	inline void SetRotation(const NiPoint3& arRot) noexcept { SetAngleOnReference(arRot); }

	NiMatrix3 GetOrientation() const;
	bool SetOrientation(const NiMatrix3& arRot);

	float GetRawScale() const;
	float GetScale() const;
	void SetScale(float afScale);

	TESObjectCELL* GetParentCell() const;

	TESObjectCELL* GetInterior() const;

	TESWorldSpace* GetWorldSpace() const;

	TESForm* GetSpace() const;

	ExtraDataList* GetExtra();
	const ExtraDataList* GetExtra() const;

	BSExtraData* GetExtraData(uint8_t aucType) const;

	template <class T>
	inline T* GetExtraData() const noexcept { return static_cast<T*>(GetExtraData(T::_TYPE)); }

	bool HasExtra(uint8_t aucType) const;

	template<class T>
	inline bool HasExtra() const noexcept { return HasExtra(T::_TYPE); }

	float GetRelevantWaterHeight() const;

	TESObjectREFR* GetCurrentWaterObject() const;

	NiAVObject* Get3DSimple() const;
	NiAVObject* Get3DVerySimple() const;
	void Set3DSimple(NiAVObject* apScene);
	void Set3DVerySimple(NiAVObject* apScene);

	bool GetPersistFlagValue() const;

	bool MustRefPersist() const;

	bool GetRefPersists() const;
	void SetRefPersists(bool abPersists);

	const char* GetFullName() const;

	void Update3DPosition();

	void ReplaceModel();

	bool GetVisibleDistant() const;
	void SetVisibleDistant(bool abVal);

	bool HasTemp3D() const;
	void SetHasTemp3D(bool abVal);

	bool Is3DCritical() const;

	bool Is3DHighPriority() const;

	bool IsMarker() const;

	bool IsMultiBoundRef() const;

	bool IsPortalOrRoomMarker() const;

	bool IsBoundOrRoomMarker() const;

	bool IsPlane() const;

	bool IsMapMarker() const;

	bool IsFurniture() const;

	bool GetIgnoredBySandbox() const;
	void SetIgnoredBySandbox(bool abVal);

	bool GetIsImposter() const;
	void SetIsImposter(bool abVal);

	bool IsCrimeToActivate() const;

	bool IsPartofEvilFaction() const;

#ifdef GAME
	bool IsCellLoaded() const;

	bool CanBeMoved() const;
#endif

	float GetModelBoundSize() const;

	float GetRadius();

	const char* GetModel() const;

	TESModel* GetTESModel() const;

#ifdef GAME
	float GetDistanceFromReference(TESObjectREFR* apTarget, bool abDisabled, bool abSharedSpace) const;
#endif
	float GetDistanceFromPoint(const NiPoint3& arPoint) const;

	bool GetIsHiddenDoor() const;
	void SetIsHiddenDoor(bool abVal);

	bool GetTargeted() const;
	void SetTargeted(bool abVal);

#ifdef GAME
	bool GetDismembered(BODY_PART_TYPE aeLimb);
#endif

	TESContainer* HasContainer() const;

	TESObjectREFR* GetLinkedRef() const;

#ifdef GAME
	bool IsActivatingChildren() const;

	bool IsLeveledCreature() const;

	void SetLeveledCreature(TESActorBase* apOriginalBase, TESActorBase* apTemplate);
#endif

	bool HasLeveledCreatureCalced() const;

#ifdef GAME
	uint32_t GetCalcLevel(bool abAllowShift) const;
#endif

	void AddLight(bool abMagic);
	void RemoveLight(bool abMagic);

	float GetHealth() const;

	bool HasRandomSound() const;

#ifdef GAME
	bool CanHaveSound() const;

	bool HasQuestObject() const;

	bool HasFreeMarker(bool abIgnoreReservations) const;

	bool IsAnOwner(Actor* apActor, bool abCheckFaction) const;

	bool IsOwnerEvil(TESForm* apOwner) const;
#endif

	TESForm* GetMyOwner() const;
	TESForm* GetOwner() const;

	TESForm* GetEmittanceSource() const;
	void SetEmittanceSource(TESForm* apSource);

#ifdef GAME
	bool GetRespawn() const;
#endif

	DoorTeleportData* GetTeleport() const;

	LockData* GetMyLock() const;
	LockData* GetLock() const;

	bool HasScript() const;

#ifdef GAME
	ScriptLocals* GetScriptLocals() const;

	bool RunScript();

	bool HasSaidTopicInfo(TESTopicInfo* apTopicInfo) const;

	bool MoveToEditorLocation(TESForm* apLocationForm);

	TESObjectCELL* GetNearbyWaterContainingCell(float afRadius) const;
#endif

	void AddBoundObjectItem(TESBoundObject* apObject, ExtraDataList* apExtra, int32_t aiCount);

	int32_t GetInventoryObjectCount(TESBoundObject* apObject) const;
#ifdef GAME
	int32_t GetInventoryCount(bool abBarter, bool abIncludeNonPlayable) const;
	[[nodiscard]] ItemChange* GetInventoryItem(uint32_t auiIndex, bool abBarter) const;
	[[nodiscard]] ItemChange* GetInventoryItem(TESBoundObject* apObject, FormID auiFormID = 0) const;

	void SaveAnimation(BGSSaveFormBuffer* apBuffer);
	void LoadAnimation(BGSLoadFormBuffer* apBuffer);
#endif

	static TESObjectREFR* FindReferenceFor3D(NiAVObject* apObject);

	static bool HasAddonNodes(NiNode* apNode);

	static bool HasAddonFlags(NiNode* apNode);

	static bool AddAddonNodes(NiNode* apNode);
	static bool RemoveAddonNodes(NiNode* apNode);

	static bool AddMasterParticleAddonNodes(NiNode* apNode);
#ifdef GAME
	static bool RemoveMasterParticleAddonNodes(NiNode* apNode);
#endif

	static bool IsReferenceFormType(FORM_TYPE aeFormType);
};

#ifdef GAME
ASSERT_SIZE(TESObjectREFR, 0x68);
#else
ASSERT_SIZE(TESObjectREFR, 0x84);
#endif

struct LoadedRefData {
	struct ALIGN4 _LoadedRefFlags {
		enum Flags : uint32_t {
			HAS_HAVOK		= 1u << 0,
			HAS_ADDONS		= 1u << 1,
			HAS_PRIMITIVE	= 1u << 2,
		};

		bool bHasHavok		: 1;
		bool bHasAddons		: 1;
		bool bHasPrimitive	: 1;
	};
	using LoadedRefFlags = _LoadedRefFlags::Flags;

	TESObjectREFR*				pCurrentWaterObject;
	int32_t						iUnderwaterCount;
	float						fRelevantWaterHeight;
	float						fCachedRadius;
	Bitfield<_LoadedRefFlags>	uiFlags;
	NiPointer<NiAVObject>		spSceneRoot;
	NiPointer<bhkPhantom>		spPhantom;
};

ASSERT_SIZE(LoadedRefData, 0x1C);