#pragma once

#include "BaseFormComponent.hpp"
#include "BSStringT.hpp"
#include "BSSimpleList.hpp"
#include "TESFile.hpp"
#include "FormID.hpp"
#include "BSTCaseInsensitiveStringMap.hpp"
#include "Gamebryo/NiTLargeArray.hpp"

#define IS_ID(form, type) (form->GetFormType() == FORM_TYPE::##type)
#define NOT_ID(form, type) (form->GetFormType() != FORM_TYPE::##type)

class NiColor;
class BGSSaveGameBuffer;
class BGSLoadFormBuffer;
class TESObjectREFR;
class TESBoundObject;
class Script;

struct FORM_ENUM_STRING {
	uint8_t			ucFormID;
	const char*		pFormString;
	uint32_t		uiFormString;
};

class TESForm : public BaseFormComponent {
public:
	TESForm();
	
	virtual					~TESForm();
	virtual void			InitializeData();
	virtual void			ClearData();
	virtual bool			ProcessBeforeSave(); // NavMesh returns false, rest 1, NavMeshInfoMap does shit
	virtual bool			Load(TESFile* apFile);
	virtual bool			LoadPartial(TESFile* apFile);
	virtual bool			Save(TESFile* apFile);
	virtual void			SaveAlt();					// Writes data
	virtual bool			LoadEdit(TESFile* apFile);
	virtual bool			SaveEdit(TESFile* apFile);
	virtual bool			SavesBefore(FORM* apForm) const;
	virtual bool			SavesBeforeAlt(TESForm* apForm) const;
	virtual TESForm*		CreateDuplicateForm(bool abCreateEditorID, NiTPointerMap<TESForm*, TESForm*>* apCopyMap);
	virtual void			PostDuplicateProcess(NiTPointerMap<TESForm*, TESForm*>* apCopyMap);
	virtual void			AddChange(uint32_t auiChangedFlags);
	virtual void			RemoveChange(uint32_t auiChangedFlags);
	virtual uint32_t		GetSaveSize(uint32_t auiChangedFlags) const;
	virtual void			SaveGameBGS(BGSSaveGameBuffer* apBuffer);
	virtual void			SaveGameTES(uint32_t auiChangedFlags);
	virtual void			LoadGameBGS(BGSSaveGameBuffer* apBuffer);
	virtual void			LoadGameTES(uint32_t auiChangedFlags, uint32_t auiCurrentFlags);
	virtual void			InitLoadGameBGS(BGSSaveGameBuffer* apBuffer);
	virtual void			InitLoadGameTES(uint32_t auiFlags, uint32_t auiOldFlags);
	virtual void			FinishInitLoadGameTES(uint32_t auiFlags, uint32_t auiOldFlags);
	virtual void			RevertBGS(BGSLoadFormBuffer* apBuffer);
	virtual void			RevertTES(uint32_t auiChangedFlags);
	virtual void			LoadQueuedFormData(uint16_t ausSize);
	virtual bool			FindInFileFast(TESFile* apFile);
	virtual void			CheckSaveGame(BGSLoadFormBuffer* apBuffer);
	virtual void			FinishLoadGameBGS(BGSLoadFormBuffer* apBuffer);
	virtual void			InitItem();
	virtual uint32_t		GetSavedFormType() const;
	virtual void			GetFormDetailedString(BSString& arDest) const;
	virtual bool			GetQuestObject() const;
	virtual bool			GetHasSpokenFlag() const;
	virtual bool			GetHavokDeath() const;
	virtual bool			GetRandomAnim() const;
	virtual bool			GetNeedtoChangeProcess() const;
	virtual bool			GetDangerous() const;
	virtual bool			GetHasPLSpecTex() const;
	virtual bool			GetObstacle() const;
	virtual bool			GetContinuousBroadcast() const;
	virtual bool			GetOnLocalMap() const;
	virtual void			SetCastsShadows(bool abShadowCaster);
	virtual NiColor*		GetEmittanceColor();
	virtual void			SetDelete(bool abDeleted);
	virtual void			SetAltered(bool abAltered);
	virtual void			SetQuestObject(bool abQuestObject);
	virtual void			SetHasSpokenFlag(bool abTalkedTo);
	virtual void			SetHavokDeath(bool abDied);
	virtual void			SetNeedToChangeProcess(bool abChange);
	virtual void			SaveObjectBound() const;
	virtual void			LoadObjectBound(TESFile* apFile);
	virtual bool			IsBoundObject() const;
	virtual bool			IsObject() const;
	virtual bool			IsMagicItem() const;
	virtual bool			IsReference() const;
	virtual bool			IsArmorAddon() const;
	virtual bool			IsActorBase() const;
	virtual bool			IsMobileObject() const;
	virtual bool			IsActor() const;
	virtual uint32_t		GetRefCount() const;
	virtual void			Copy(TESForm* apCopy);
	virtual bool			Compare(TESForm* apForm);
	virtual bool			BelongsInGroup(FORM* apGroupFORM, bool abAllowParentGroups, bool abCurrentOnly) const;
	virtual void			CreateGroupData(FORM* apForm, FORM* apOutGroupFORM) const;
	virtual bool			IsParentForm() const;
	virtual bool			IsParentFormTree() const;
	virtual bool			IsFormTypeChild(uint8_t aucFormType) const;
	virtual bool			Activate(TESObjectREFR* apItemActivated, TESObjectREFR* apActionRef, bool abSound, TESBoundObject* apObjectToGet, int32_t aiCount);
	virtual void			SetFormID(uint32_t auiID, bool abUpdateFile);
	virtual const char*		GetObjectTypeName() const;
	virtual const char*		GetFormEditorID() const;
	virtual bool			SetFormEditorID(const char* apID);

	struct EditorData {
		BSString	strEditorID;
		uint32_t	uiVCMasterFormID;
		uint32_t	uiVCRevision;
	};

	struct ALIGN4 _FormFlags {
		enum Flags : uint32_t {
			MASTER					= 1u << 0, // TESForm
			ALTERED					= 1u << 1, // TESForm

			INITIALIZED				= 1u << 3, // TESForm
			NO_COLLISION			= 1u << 4, // TESForm
			DELETED					= 1u << 5, // TESForm
			TREE_LOD				= 1u << 6, // TESBoundObject
			HAS_SPOKEN				= 1u << 6, // Actor
			IN_PLACEABLE_WATER		= 1u << 6, // TESBoundObject (!TESObjectDOOR)
			HIDDEN_DOOR				= 1u << 6, // TESObjectDOOR
			BORDER_REGION			= 1u << 6, // TESRegion
			CONSTANT				= 1u << 6, // TESGlobal
			FIRE_OFF				= 1u << 7, // TESForm
			DROPPED					= 1u << 8, // TESObjectREFR (!TESObjectDOOR)
			INACCESSIBLE			= 1u << 8, // TESObjectREFR (TESObjectDOOR)
			ON_LOCAL_MAP			= 1u << 9, // TESBoundObject
			CASTS_SHADOWS			= 1u << 9,  // TESObjectREFR (TESObjectLIGH)
			MOTION_BLUR				= 1u << 9,  // TESObjectREFR (BGSMovableStatic)
			QUEST_ITEM				= 1u << 10, // TESBoundObject
			PERSISTENT				= 1u << 10, // TESObjectREFR
			PERSISTENT_CELL			= 1u << 10, // TESObjectCELL
			DISPLAY_ON_MAIN_MENU	= 1u << 10, // TESLoadScreen
			DISABLED				= 1u << 11, // TESObjectREFR, NavMesh

			EMPTY					= 1u << 13, // TESFlora
			RESET_DESTRUCT			= 1u << 13, // BGSDestructibleObjectForm
			NO_VOICE_FILTER			= 1u << 13, // BGSTalkingActivator
			HAS_RESULTS				= 1u << 13, // TESTopicInfo, TESTopic
			TEMPORARY				= 1u << 14, // TESForm
			VISIBLE_DISTANT			= 1u << 15, // TESForm
			RANDOM_ANIM_START		= 1u << 16, // TESObjectACTI, TESObjectLIGH, TESObjectCONT, TESObjectDOOR, TESFurniture, BGSTalkingActivator, BGSTerminal, BGSMovableStatic
			HIGH_PRIORITY_LOD		= 1u << 16, // TESObjectREFR
			HAVOK_DEATH				= 1u << 16, // Actor
			NEED_TO_CHANGE_PROCESS	= 1u << 17, // MobileObject
			DANGEROUS				= 1u << 17, // TESObjectACTI
			RADIO_STATION			= 1u << 17, // BGSTalkingActivator
			OFF_LIMITS				= 1u << 17, // TESObjectCELL
			COMPRESSED				= 1u << 18, // TESForm (TESFile)
			TARGETED				= 1u << 18, // TESObjectREFR
			STARTS_DEAD				= 1u << 19, // TESActorBase
			HAS_TEMP_3D				= 1u << 19, // TESObjectREFR
			SPECIFIC_TEXTURES		= 1u << 19, // TESBoundObject (!TESActorBase)
			CANT_WAIT				= 1u << 19, // TESWorldSpace, TESObjectCELL
			CENTER_ON_CREATION		= 1u << 20, // TESObjectREFR (!Actor)
			IGNORE_FRIENDLY_HITS	= 1u << 20, // Actor
			STILL_LOADING			= 1u << 21, // TESForm
			BEING_DROPPED			= 1u << 22, // TESOBjectREFR
			DESTROYED				= 1u << 23, // TESObjectREFR
			DESTRUCTIBLE			= 1u << 24, // TESObjectREFR
			OBSTACLE				= 1u << 25, // TESBoundObject
			NO_AI_ACQUIRE			= 1u << 25, // TESObjectREFR
			VATS_TARGET_OVERRIDE	= 1u << 26, // TESObjectREFR
			NAVMESH_GEN_FILTER		= 1u << 26, // GECK - TESObjectREFR, TESObjectACTI, TESObjectCONT, BGSStaticCollection 
			DISABLE_FADE			= 1u << 27, // TESObjectREFR
			NAVMESH_GEN_BOUND_BOX	= 1u << 27, // GECK - TESObjectREFR, TESObjectACTI, TESObjectCONT, BGSStaticCollection 
			NON_PIPBOY_RADIO		= 1u << 28, // TESObjectACTI
			REFLECTED_BY_AUTO_WATER = 1u << 28, // TESObjectREFR
			CHILD_CAN_USE			= 1u << 29, // TESObjectACTI, TESFurniture, BGSIdleMarker
			REFRACTED_BY_AUTO_WATER = 1u << 29, // TESObjectREFR
			CONTINUOUS_BROADCAST	= 1u << 30, // BGSTalkingActivator
			NAVMESH_GEN_GROUND		= 1u << 30, // GECK - TESObjectREFR, TESObjectACTI, TESObjectCONT, BGSStaticCollection 

			TAKEN = DELETED | ALTERED,
		};
	};
	using FormFlags = _FormFlags::Flags;

	uint8_t					eFormType;
#if JIP_CHANGES
	Bitfield8				ucJIPFormFlags5;
	Bitfield16				usJIPFormFlags6;
#endif
	Bitfield<_FormFlags>	uiFormFlags;
	FormID					uiFormID;
	BSSimpleList<TESFile*>	kFiles;

	uint32_t	GetFormID() const;
	FORM_TYPE	GetFormType() const;
	uint8_t		GetCompileIndex() const;

	static const char* GetFormTypeName(uint32_t auiFormType);
	const char* GetFormTypeName() const;

	static const char* GetFormTypeString(uint32_t auiFormType);
	const char* GetFormTypeString() const;

#ifdef GAME
	static constexpr AddressPtr<NiTPointerMap<uint32_t, TESForm*>*, 0x11C54C0>		pAllForms;
	static constexpr AddressPtr<BSTCaseInsensitiveStringMap<TESForm*>*, 0x11C54C8>	pAllFormsByEditorID;
#else
	static constexpr AddressPtr<NiTPointerMap<uint32_t, TESForm*>*, 0xED56CC>		pAllForms;
	static constexpr AddressPtr<BSTCaseInsensitiveStringMap<TESForm*>*, 0xED56D4>	pAllFormsByEditorID;
#endif

	bool IsWeapon() const { return eFormType == FORM_TYPE::TESObjectWEAP; }
	bool IsArmor() const { return eFormType == FORM_TYPE::TESObjectARMO; }

	bool GetMaster() const;
	void SetMaster(bool abVal);

	bool GetAltered() const;
	// Set is virtual

	bool GetInitialized() const;
	void SetInitialized(bool abVal);

	bool GetNoCollision() const;
	void SetNoCollision(bool abVal);

	bool GetDeleted() const;
	// Set is virtual

	bool GetTreeLOD() const;
	void SetTreeLOD(bool abVal);

	bool GetInPlaceableWater() const;
	void SetInPlaceableWater(bool abVal);

	bool GetBorderRegion() const;
	void SetBorderRegion(bool abVal);

	bool GetFireOff() const;
	void SetFireOff(bool abVal);

	bool GetDisabled() const;
	void SetDisabled(bool abVal);

	bool GetEmpty() const;
	void SetEmpty(bool abVal);

	bool GetResetDestruct() const;
	void SetResetDestruct(bool abVal);

	bool GetHasResults() const;
	void SetHasResults(bool abVal);

	bool GetTemporary() const;
	void SetTemporary();

	bool GetMustBeVisibleDistant() const;
	void SetMustBeVisibleDistant(bool abVal);

	bool IsStillLoading() const;
	void SetStillLoading(bool abVal);

	bool GetBeingDropped() const;
	void SetBeingDropped(bool abVal);

	bool GetDestroyed() const;
	void SetDestroyed(bool abVal);

	bool GetDestructible() const;
	void SetDestructible(bool abVal);

	bool GetNoAIAcquire() const;
	void SetNoAIAcquire(bool abVal);

	bool GetVATSTarget() const;
	void SetVATSTarget(bool abVal);

	bool GetDisableFade() const;
	void SetDisableFade(bool abVal);

	bool GetReflectedByAutoWater() const;
	void SetReflectedByAutoWater(bool abVal);

	bool GetRefractedByAutoWater() const;
	void SetRefractedByAutoWater(bool abVal);

	bool GetChildCanUse() const;
	void SetChildCanUse(bool abVal);

	// Get is virtual
	void SetContinuousBroadcast(bool abVal);

	TESFile* GetFile(int32_t aiIndex) const;
	TESFile* GetOwnerMaster() const;
	uint32_t GetFormIDWithoutIndex() const;
	uint32_t GetLoadFormID() const;
	uint32_t GetFileCount() const;

	static TESForm* GetFormByNumericID(uint32_t auID);
	static TESForm* GetFormByEditorID(const char* apEDID);

	static const FORM_ENUM_STRING* GetFormEnumString(uint8_t aucFormID);

	static uint32_t GetFormTypeFromFormString(uint32_t auiFormString);
};

ASSERT_SIZE(TESForm, 0x18);
