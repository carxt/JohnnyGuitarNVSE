#pragma once

#include "TESCondition.hpp"
#include "TESForm.hpp"
#include "TESPackageData.hpp"
#include "PackageSchedule.hpp"
#include "PackageTarget.hpp"
#include "PackageLocation.hpp"
#include "PackageEventAction.hpp"

class BGSIdleCollection;
class TESCombatStyle;
class TESObjectREFR;
class TESIdleForm;
class TESTopic;
class Actor;
class NiPoint3;
class PackageTarget;
class PackageLocation;

class TESPackage : public TESForm {
public:
	TESPackage();
	~TESPackage();

#ifdef GAME
	virtual bool		IsReadyToRun(Actor* apActor);
	virtual bool		IsActorAtLocation(Actor* apActor, bool abIgnoreDistance, float afExtraRadius, bool abInFurniture);
	virtual bool		IsActorAtSecondLocation(Actor* apMobileObject, Actor* apPackageowner, bool abIgnoreDistance, float afExtraRadius, bool abInFurniture);
	virtual bool		IsActorAtRefTarget(Actor* apActor, int32_t aiExtraRadius);
	virtual bool		IsTargetAtLocation(Actor* apActor, int32_t aiExtraRadius);
	virtual uint16_t	GetSaveSize();
	virtual uint16_t	SaveGameTESAlt();
	virtual uint16_t	LoadGameTESAlt();
	virtual void		InitLoadGameTES();
#endif
	virtual bool		IsPackageOwner(Actor* apActor = nullptr);

	struct ALIGN4 _PackageFlags {
		enum Flags : uint32_t {
			OFFERS_SERVICES				= 1u << 0,
			MUST_REACH_LOCATION			= 1u << 1,
			MUST_COMPLETE				= 1u << 2,
			LOCK_DOORS_AT_START			= 1u << 3,
			LOCK_DOORS_AT_END			= 1u << 4,
			LOCK_DOORS_AT_LOCATION		= 1u << 5,
			UNLOCK_DOORS_AT_START		= 1u << 6,
			UNLOCK_DOORS_AT_END			= 1u << 7,
			UNLOCK_DOORS_AT_LOCATION	= 1u << 8,
			CONTINUE_IF_PC_NEAR			= 1u << 9,
			ONCE_PER_DAY				= 1u << 10,
			CREATED						= 1u << 11,
			SKIP_FALLOUT_BEHAVIOR		= 1u << 12,
			ALWAYS_RUN					= 1u << 13,
			SCRIPT_PACKAGE				= 1u << 14,
			NEVER_RUN					= 1u << 15,
			WAITING						= 1u << 16,
			ALWAYS_SNEAK				= 1u << 17,
			ALLOW_SWIMMING				= 1u << 18,
			ALLOW_FALLS					= 1u << 19,
			NO_HEAD_TRACK				= 1u << 20,
			FORCE_UNEQUIP_WEAPON		= 1u << 21,
			DEFENSIVE_COMBAT			= 1u << 22,
			FORCE_DRAW_WEAPON			= 1u << 23,
			NO_IDLE_ANIMS				= 1u << 24,
			PRETEND_IN_COMBAT			= 1u << 25,
			CONTINUE_DURING_COMBAT		= 1u << 26,
			NO_COMBAT_ALERT				= 1u << 27,
			NO_WARN_ATTACK_BEHAVIOR		= 1u << 28,
		};

		bool bOffersServices		: 1;
		bool bMustReachLocation		: 1;
		bool bMustComplete			: 1;
		bool bLockDoorsAtStart		: 1;
		bool bLockDoorsAtEnd		: 1;
		bool bLockDoorsAtLocation	: 1;
		bool bUnlockDoorsAtStart	: 1;
		bool bUnlockDoorsAtEnd		: 1;
		bool bUnlockDoorsAtLocation : 1;
		bool bContinueIfPCNear		: 1;
		bool bOncePerDay			: 1;
		bool bCreated				: 1;
		bool bSkipFalloutBehavior	: 1;
		bool bAlwaysRun				: 1;
		bool bScriptPackage			: 1;
		bool bNeverRun				: 1;
		bool bWaiting				: 1;
		bool bAlwaysSneak			: 1;
		bool bAllowSwimming			: 1;
		bool bAllowFalls			: 1;
		bool bNoHeadTrack			: 1;
		bool bForceUnequipWeapon	: 1;
		bool bDefensiveCombat		: 1;
		bool bForceDrawWeapon		: 1;
		bool bNoIdleAnims			: 1;
		bool bPretendInCombat		: 1;
		bool bContinueDuringCombat	: 1;
		bool bNoCombatAlert			: 1;
		bool bNoWarnAttackBehavior	: 1;
	};
	using PackageFlags = _PackageFlags::Flags;

	struct ALIGN2 _FOBehaviorFlags {
		enum Flags : uint16_t {
			HELLOS_TO_PLAYER			= 1u << 0,
			RANDOM_CONVERSATIONS		= 1u << 1,
			OBSERVE_COMBAT_BEHAVIOR		= 1u << 2,
			GREET_CORPSES_BEHAVIOR		= 1u << 3,
			REACTION_TO_PLAYER_ACTIONS	= 1u << 4,
			FRIENDLY_FIRE_COMMENTS		= 1u << 5,
			AGGRO_RADIUS_BEHAVIOR		= 1u << 6,
			IDLE_CHATTER_BEHAVIOR		= 1u << 7,
			AVOID_RADIATION				= 1u << 8,
		};

		bool bHellosToPlayer			: 1;
		bool bRandomConversations		: 1;
		bool bObserveCombatBehavior		: 1;
		bool bGreetCorpsesBehavior		: 1;
		bool bReactionToPlayerActions	: 1;
		bool bFriendlyFireComments		: 1;
		bool bAggroRadiusBehavior		: 1;
		bool bIdleChatterBehavior		: 1;
		bool bAvoidRadiation			: 1;
	};
	using FOBehaviorFlags = _FOBehaviorFlags::Flags;

	struct ALIGN2 _PackageSpecificFlags {
		enum Flags : uint16_t {
			GUARD_TARGET_IS_LINKED_REF		= 1u << 1,
			GUARD_REMAIN_NEAR_TARGET		= 1u << 2,

			SANDBOX_NO_EATING				= 1u << 0,
			SANDBOX_NO_SLEEPING				= 1u << 1,
			SANDBOX_NO_CONVERSATION			= 1u << 2,
			SANDBOX_NO_IDLE_MARKERS			= 1u << 3,
			SANDBOX_NO_FURNITURE			= 1u << 4,
			SANDBOX_NO_WANDERING			= 1u << 5,
			SANDBOX_LOCATION_IS_LINKED_REF	= 1u << 6,

			USE_ITEM_SIT_DOWN				= 1u << 1,

			SEARCH_ALLOW_BUYING				= 1u << 8,
			SEARCH_ALLOW_KILLING			= 1u << 9,
			SEARCH_ALLOW_STEALING			= 1u << 10,
		};

		struct ALIGN2 _GuardFlags {
			bool bTargetIsLinkedRef		: 1;
			bool bRemainNearTarget		: 1;
		};

		struct ALIGN2 _SandboxFlags {
			bool bNoEating				: 1;
			bool bNoSleeping			: 1;
			bool bNoConversation		: 1;
			bool bNoIdleMarkers			: 1;
			bool bNoFurniture			: 1;
			bool bNoWandering			: 1;
			bool bLocationIsLinkedRef	: 1;
		};
		
		struct ALIGN2 _UseItemFlags {
			bool						: 1;
			bool bSitDown				: 1;
		};

		struct ALIGN2 _AmbushFlags {
			bool bHide					: 1;
			bool bLocationIsAtLinkedRef : 1;
		};

		struct ALIGN2 _SearchFlags {
			bool						: 7;
			bool bAllowBuying			: 1;
			bool bAllowKilling			: 1;
			bool bAllowStealing			: 1;
		};

		union {
			_GuardFlags		usGuard;
			_SandboxFlags	usSandbox;
			_UseItemFlags	usUseItem;
			_AmbushFlags	usAmbush;
			_SearchFlags	usSearch;
		};
	};
	using PackageSpecificFlags	= _PackageSpecificFlags::Flags;
	using _GuardPackageFlags	= _PackageSpecificFlags::_GuardFlags;
	using _SandboxPackageFlags	= _PackageSpecificFlags::_SandboxFlags;
	using _UseItemPackageFlags	= _PackageSpecificFlags::_UseItemFlags;
	using _AmbushPackageFlags	= _PackageSpecificFlags::_AmbushFlags;
	using _SearchPackageFlags	= _PackageSpecificFlags::_SearchFlags;

	struct _TargetType {
		enum Type {
			REFERENCE	= 0,
			OBJECT		= 1,
			TYPE		= 2,
			LINKED_REF	= 3,
		};
	};
	using TargetType = _TargetType::Type;

	struct Data {
		Bitfield<_PackageFlags>				uiPackageFlags;
		int8_t								eType;
		Bitfield<_FOBehaviorFlags>			usFOBehaviorFlags;
		Bitfield<_PackageSpecificFlags>		usSpecificFlags;
	};

#ifdef GAME
	int32_t				eProcedureType;
#endif
	Data				kData;
	TESPackageData*		pPackageData;
	PackageLocation*	pPackageLocation;
	PackageTarget*		pPackageTarget;
	BGSIdleCollection*	pIdleCollection;
	PackageSchedule		kPackSched;
	TESCondition		kConditions;
	TESCombatStyle*		pCombatStyle;
	PackageEventAction	kOnBegin;
	PackageEventAction	kOnEnd;
	PackageEventAction	kOnChange;
#ifdef GAME
	uint32_t			uiRefCount;
#endif

	TESFORM_TYPE(TESPackage);

#ifdef GAME
	PACKAGE_PROCEDURE_TYPE GetProcedureType() const;
	void SetProcedureType(PACKAGE_PROCEDURE_TYPE aeProcedure);
	void CalculateProcedureType(TESObjectREFR* apLinkedRef);

	const char* GetCurrentActionName(int32_t aiIndex) const;

	static PROCEDURE GetProcedureAction(PACKAGE_PROCEDURE_TYPE aeProcedure, int32_t aiIndex);
	static const char* GetProcedureName(PROCEDURE aeProcedure);

	void CopyAllFlags(const TESPackage* apSource);
#endif

	PACKAGE_TYPE GetPackType() const;

	const _PackageFlags& GetPackageFlags() const;
	_PackageFlags& GetPackageFlags();

	bool GetServicesEnabled() const;
	void SetServicesEnabled(bool abVal);

	bool GetMustReachLocation() const;
	void SetMustReachLocation(bool abVal);

	bool GetMustComplete() const;
	void SetMustComplete(bool abVal);

	bool GetLockDoorsAtStart() const;
	void SetLockDoorsAtStart(bool abVal);

	bool GetLockDoorsAtEnd() const;
	void SetLockDoorsAtEnd(bool abVal);

	bool GetLockDoorsAtLocation() const;
	void SetLockDoorsAtLocation(bool abVal);

	bool GetUnlockDoorsAtStart() const;
	void SetUnlockDoorsAtStart(bool abVal);

	bool GetUnlockDoorsAtEnd() const;
	void SetUnlockDoorsAtEnd(bool abVal);

	bool GetUnlockDoorsAtLocation() const;
	void SetUnlockDoorsAtLocation(bool abVal);

	bool GetPCContinue() const;
	void SetPCContinue(bool abVal);

	bool GetOncePerDay() const;
	void SetOncePerDay(bool abVal);

#ifdef GAME
	bool GetIsCreated() const;
	void SetIsCreated(bool abVal);
#endif

	bool GetSelectiveFalloutBehavior() const;
	void SetSelectiveFalloutBehavior(bool abVal);

	bool GetAlwaysRun() const;
	void SetAlwaysRun(bool abVal);

	bool GetIsScriptPackage() const;
	void SetIsScriptPackage(bool abVal);

	bool GetNeverRun() const;
	void SetNeverRun(TESObjectREFR* apRef, bool abVal);

	bool GetWaiting() const;
	void SetWaiting(bool abVal);

	bool GetAlwaysSneak() const;
	void SetAlwaysSneak(bool abVal);

	bool GetAllowsSwim() const;
	void SetAllowsSwim(bool abVal);

	bool GetAllowFalls() const;
	void SetAllowFalls(bool abVal);

	bool GetNoHeadTrack() const;
	void SetNoHeadTrack(bool abVal);

	bool GetForceUnequipWeapon() const;
	void SetForceUnequipWeapon(bool abVal);

	bool GetDefensive() const;
	void SetDefensive(bool abVal);

	bool GetForceDrawWeapon() const;
	void SetForceDrawWeapon(bool abVal);

	bool GetNoIdles() const;
	void SetNoIdles(bool abVal);

	bool GetPretendInCombat() const;
	void SetPretendInCombat(bool abVal);

	bool GetContinueDuringCombat() const;
	void SetContinueDuringCombat(bool abVal);

	bool GetCombatAlert() const;
	void SetCombatAlert(bool abVal);

	bool GetGuardWarnBehavior() const;
	void SetGuardWarnBehavior(bool abVal);

	const _FOBehaviorFlags& GetFOBehaviorFlags() const;
	_FOBehaviorFlags& GetFOBehaviorFlags();

	bool GetFOEnableHellosToPlayer() const;
	void SetFOEnableHellosToPlayer(bool abVal);

	bool GetFOEnableRandomConversations() const;
	void SetFOEnableRandomConversations(bool abVal);

	bool GetFOEnableObserveCombatBehavior() const;
	void SetFOEnableObserveCombatBehavior(bool abVal);

	bool GetFOEnableGreetCorpseBehavior() const;
	void SetFOEnableGreetCorpseBehavior(bool abVal);

	bool GetFOEnableReactionToPlayerActions() const;
	void SetFOEnableReactionToPlayerActions(bool abVal);

	bool GetFOEnableFriendlyFireComments() const;
	void SetFOEnableFriendlyFireComments(bool abVal);

	bool GetFOEnableAggroRadiusBehavior() const;
	void SetFOEnableAggroRadiusBehavior(bool abVal);

	bool GetFOEnableIdleChatterBehavior() const;
	void SetFOEnableIdleChatterBehavior(bool abVal);

	bool GetFOEnableAvoidRadiationBehavior() const;
	void SetFOEnableAvoidRadiationBehavior(bool abVal);

	const _PackageSpecificFlags& GetPackageSpecificFlags() const;
	_PackageSpecificFlags& GetPackageSpecificFlags();
	
	const _GuardPackageFlags& GetGuardFlags() const;
	_GuardPackageFlags& GetGuardFlags();
	
	bool GuardGetContinueInCombatAtTarget() const;
	bool GuardGetContinueInCombatAtLocation() const;
	void GuardSetContinueInCombatAtTarget(bool abVal);

	bool GuardGetTargetIsLinkedRef() const;
	void GuardSetTargetIsLinkedRef(bool abVal);
	
	const _SandboxPackageFlags& GetSandboxFlags() const;
	_SandboxPackageFlags& GetSandboxFlags();

	bool SandboxGetAllowEating() const;
	void SandboxSetAllowEating(bool abVal);

	bool SandboxGetAllowSleeping() const;
	void SandboxSetAllowSleeping(bool abVal);

	bool SandboxGetAllowConversation() const;
	void SandboxSetAllowConversation(bool abVal);

	bool SandboxGetAllowIdleMarkers() const;
	void SandboxSetAllowIdleMarkers(bool abVal);

	bool SandboxGetAllowFurniture() const;
	void SandboxSetAllowFurniture(bool abVal);

	bool SandboxGetAllowWandering() const;
	void SandboxSetAllowWandering(bool abVal);

	bool SandboxGetLocationIsLinkedRef() const;
	void SandboxSetLocationIsLinkedRef(bool abVal);
	
	const _UseItemPackageFlags& GetUseItemFlags() const;
	_UseItemPackageFlags& GetUseItemFlags();

	bool UseItemGetSitDown() const;
	void UseItemSetSitDown(bool abVal);

	const _AmbushPackageFlags& GetAmbushFlags() const;
	_AmbushPackageFlags& GetAmbushFlags();
	
	bool AmbushGetHideWhileAmbushing() const;
	void AmbushSetHideWhileAmbushing(bool abVal);
	
	bool AmbushGetLocationAtLinkedRef() const;
	void AmbushSetLocationAtLinkedRef(bool abVal);
	
	const _SearchPackageFlags& GetSearchFlags() const;
	_SearchPackageFlags& GetSearchFlags();

	bool SearchGetAllowBuying() const;
	void SearchSetAllowBuying(bool abVal);
	
	bool SearchGetAllowKilling() const;
	void SearchSetAllowKilling(bool abVal);
	
	bool SearchGetAllowStealing() const;
	void SearchSetAllowStealing(bool abVal);

	PackageLocation* GetPackageLocation() const;
	void SetPackageLocation(const PackageLocation* apLocation);

	PackageLocation* GetPackageSecondLocation() const;
	PackageLocation* GetPackageSearchLocation() const;

	PackageTarget* GetPackageTarget() const;
	void SetPackageTarget(const PackageTarget* apTarget);

	BGSIdleCollection* GetPackageIdles() const;
	void SetPackageIdles(const BGSIdleCollection* apCollection);

	const PackageSchedule* GetPackageSchedule() const;
	PackageSchedule* GetPackageSchedule();

	const TESCondition* GetPackageConditions() const;
	TESCondition* GetPackageConditions();

	TESCombatStyle* GetCombatStyle() const;
	void SetCombatStyle(TESCombatStyle* apStyle);

#ifdef GAME
	TESTopic* GetDialogueTopic() const;

	NiPoint3 GetLocationCoord(Actor* apActor) const;

	static TESPackage* CreatePackage(PACKAGE_TYPE aeType);
#endif
};

#ifdef GAME
ASSERT_SIZE(TESPackage, 0x80);
#else
ASSERT_SIZE(TESPackage, 0x90);
#endif