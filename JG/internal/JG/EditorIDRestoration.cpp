#include "GameObjects.h"
#include "GameData.h"
#include "JohnnyExtraData.hpp"
#include "misc/misc.h"

STACK_FRAME_OPT_ENABLE

namespace EDIDRestoration {

#define DEBUG_PRINTS 0

#if DEBUG_PRINTS
#define DEBUG_MSG(...) _MESSAGE(__VA_ARGS__)
#else
#define DEBUG_MSG(...) __noop(__VA_ARGS__)
#endif

	bool bHadEDIDConflicts = false;
	SRWLOCK kEDIDMapLock = SRWLOCK_INIT;

	static constexpr uint32_t TESForm_Vtables[] = {
		0x101144C,	//	BGSDehydrationStage
		0x10115B4,  //	BGSHungerStage
		0x10116FC,	//	BGSSleepDeprevationStage
		0x1011964,	//	AlchemyItem
		0x1011B4C,	//	MagicItemObject	
		0x1012834,	//	EffectSetting	
		0x1012EA4,	//	EnchantmentItem
		0x1013044,	//	MagicItemForm
		0x1013284,	//	IngredientItem
		0x1013F8C,	//	SpellItem
		0x101C794,	//	TESForm
		0x102397C,	//	TESRegion
		0x1024214,	//	BGSAddonNode
		0x10245A4,	//	BGSConstructibleObject
		0x1024834,	//	BGSDebris
		0x1024A94,	//	BGSExplosion
		0x1024CEC,  //  BGSMovableStatic
		0x1024F4C,	//	BGSPlaceableWater
		0x10251AC,	//	BGSProjectile
		0x102535C,	//	BGSStaticCollection
		0x1025594,	//	BGSTalkingActivator
		0x1025914,	//	BGSTerminal
		0x1026064,	//	TESAmmo
		0x10263DC,	//	TESCasinoChips
		0x1026574,	//	TESCasino
		0x10266E4,	//	TESCombatStyle
		0x102685C,	//	TESEffectShader
		0x1026A4C,	//	TESFlora
		0x1026D0C,	//	TESFurniture
		0x102814C,	//	TESGrass
		0x1028444,	//	TESKey
		0x102864C,	//	TESLevCharacter
		0x102886C,	//	TESLevCreature
		0x1028A64,	//	TESLevItem
		0x1028C5C,	//	TESLevSpell
		0x1028EE4,	//	TESObjectLIGH
		0x102960C,	//	TESBoundObject
		0x102980C,	//	TESBoundAnimObject
		0x1029994,	//	TESBoundTreeObject
		0x1029B1C,	//	TESObject
		0x1029D5C,	//	TESObjectACTI
		0x102A0A4,	//	TESObjectANIO
		0x102A31C,	//	TESObjectARMA
		0x102A62C,	//	TESObjectARMO
		0x102A9C4,	//	TESObjectBOOK
		0x102AC0C,	//	TESObjectCLOT
		0x102AEB4,	//	TESObjectCONT
		0x102B1FC,	//	TESObjectDOOR
		0x102B5AC,	//	TESObjectIMOD
		0x102B844,	//	TESObjectMISC
		0x102BA2C,	//	TESObjectSTAT
		0x102BC94,	//	TESObjectTREE
		0x102C51C,	//	TESObjectWEAP
		0x102CBBC,	//	BGSEncounterZone
		0x102CD94,	//	BGSLightingTemplate
		0x102D5C4,	//	TESClimate
		0x102D7F4,	//	TESImageSpace
		0x102D97C,	//	TESImageSpaceModifier
		0x102DCD4,	//	TESObjectLAND
		0x102E6C4,	//	TESLandTexture
		0x102E9B4,  //  TESObjectCELL
		0x102F55C,  //  TESObjectREFR
		0x103140C,	//	TESWaterForm
		0x103168C,	//	TESWeather
		0x103195C,	//	TESWorldSpace
		0x10320FC,	//	BGSAcousticSpace
		0x103245C,	//	BGSCameraPath
		0x10327F4,	//	BGSCameraShot
		0x1032DC4,	//	BGSDefaultObjectManager
		0x1032F6C,	//	BGSImpactData
		0x103323C,	//	BGSImpactDataSet
		0x10334B4,	//	BGSListForm
		0x1033654,	//	BGSMenuIcon
		0x10337C4,	//	BGSMessage
		0x103397C,	//	BGSMusicType
		0x1033B34,	//	BGSRadiationStage
		0x1033D1C,	//	BGSTextureSet
		0x10340C4,	//	MediaLocationController
		0x10342EC,	//	MediaSet
		0x103449C,	//	TESAmmoEffect
		0x103478C,	//	TESCaravanCard
		0x10349B4,	//	TESCaravanMoney
		0x1034B4C,	//	TESCaravanDeck
		0x1036524,	//	TESGlobal
		0x10366CC,	//	TESLoadScreen
		0x1036854,	//	TESLoadScreenType
		0x10369DC,	//	TESRecipeCategory
		0x1036B2C,	//	TESRecipe
		0x1037094,	//	Script
		0x1044FFC,	//	TESSound
		0x1045504,	//	BGSBodyPartData
		0x10464B4,	//	BGSHeadPart
		0x104664C,	//	BGSIdleMarker
		0x1046874,	//	BGSNote
		0x1046EC4,	//	BGSPerk
		0x10470EC,	//	BGSRagdoll
		0x104733C,	//	BGSVoiceType
		0x104891C,	//	TESChallenge
		0x1048BB4,	//	TESClass
		0x1048F5C,	//	TESCreature
		0x10492AC,	//	TESActorBase
		0x104973C,	//	TESEyes
		0x10498DC,	//	TESFaction
		0x1049B9C,	//	TESHair
		0x1049D0C,	//	TESIdleForm
		0x104A2F4,	//	TESNPC
		0x104AC44,  //	TESQuest
		0x104B4BC,  //	TESRace
		0x104BA24,	//	TESReputation
		0x104CC0C,	//	TESSkill
		0x104D19C,	//	TESTopic
		0x104D5B4,	//	TESTopicInfo
		0x1067A2C,  //  ActorValueInfo
		0x106847C,	//	TESPackage
		0x106A0B4,  //  NavMesh
		0x106BB8C,  //  NavMeshInfoMap
		0x107A554,  //  MagicBallProjectile
		0x107A8F4,  //  MagicBoltProjectile
		0x107AD84,  //  MagicFogProjectile
		0x107B394,  //  MagicProjectile
		0x107B8C4,  //  MagicSprayProjectile
		0x1084254,  //  Actor
		0x1085954,  //  ArrowProjectile
		0x1086A6C,  //  Character
		0x10870AC,  //  Creature
		0x108A49C,  //  MobileObject
		0x108AA3C,  //  PlayerCharacter
		0x108C3C4,  //  BeamProjectile
		0x108CE74,  //  CombatController
		0x108EA64,  //  ContinuousBeamProjectile
		0x108EE04,  //  Explosion
		0x108F2F4,  //  FlameProjectile
		0x108F674,  //  GrenadeProjectile
		0x108FA44,  //  MissileProjectile
		0x10900DC,  //  Projectile
		0x1092BDC,  //  AlarmPackage	
		0x1092D84,  //  BackUpPackage	
		0x1092F6C,  //  DialoguePackage	
		0x10931E4,  //  FleePackage	
		0x1093674,  //  SearchPackage	
		0x109381C,  //  SpectatorPackage
		0x10939EC,  //  TrespassPackage
	};

	namespace Map {

		SPEC_INLINE char tolower_game(int32_t c) {
			return CdeclCall<int32_t>(0xEC67AA, c);
		}

		class CIFixedStringFormMap : public BSTCaseInsensitiveStringMap<TESForm*> {
		public:
			bool _IsKeysEqual(const char* __restrict apKey1, const char* __restrict apKey2) const noexcept {
				if (!apKey1 || !apKey2) [[unlikely]]
					return false;

				do {
					if (*apKey1 != *apKey2) [[likely]] {
						const char c1 = tolower_game(*apKey1);
						if (c1 != *apKey2) [[likely]] {
							const char c2 = tolower_game(*apKey2);
							if (c1 != c2) [[likely]] {
								return false;
							}
						}
					}
					++apKey1;
					++apKey2;
				} while (*apKey1 && *apKey2);

				return (*apKey1 | *apKey2) == 0;
			}
		};

		static void InitHooks() noexcept {
			// Replace map's function
			HookUtils::ReplaceVirtualFunc(0x101CAC0, &CIFixedStringFormMap::_IsKeysEqual);

			// Don't copy strings to the map
			// This means memory ownership belongs to us (JohnnyExtraData)
			// Pray no one adds forms into the map without using SetFormEditorID
			// Why? Memory
			HookUtils::SafeWrite8(0x483AEA + 1, 0);

			// Increase the bucket count (same as the main form map)
			HookUtils::SafeWrite32(0x483AEC + 1, 0x2008D);

			// Skip manual EDID insertion, as we handle it in SetFormEditorID
			HookUtils::WriteRelJump(0x4679F8, 0x467A84);

			// Game registers some default forms manually, right after calling SetFormEditorID
			// SetFormEditorID already registers them in the map, why do it twice?
			HookUtils::PatchMemoryNop(0x46CA2B, 5); // GameYear
			HookUtils::PatchMemoryNop(0x46CB0D, 5); // GameMonth
			HookUtils::PatchMemoryNop(0x46CBEF, 5); // GameDay
			HookUtils::PatchMemoryNop(0x46CCD1, 5); // GameHour
			HookUtils::PatchMemoryNop(0x46CDAF, 5); // GameDaysPassed
			HookUtils::PatchMemoryNop(0x46CE91, 5); // TimeScale
			HookUtils::PatchMemoryNop(0x46DC77, 5); // PlayCredits

			// Same thing for default topics
			HookUtils::PatchMemoryNop(0x61A243, 5);
		}

		static void __fastcall Set(const NiFixedString& arEDID, TESForm* apForm) noexcept {
			SRWUniqueLock kLock(kEDIDMapLock);
			TESForm::pAllFormsByEditorID->SetAt(arEDID, apForm);
		}

		static bool __fastcall Remove(const NiFixedString& arEDID) noexcept {
			SRWUniqueLock kLock(kEDIDMapLock);
			return TESForm::pAllFormsByEditorID->RemoveAt(arEDID);
		}

		static TESForm* __fastcall Get(const char* apEDID) noexcept {
			SRWSharedLock kLock(kEDIDMapLock);
			TESForm* pForm = nullptr;
			TESForm::pAllFormsByEditorID->GetAt(apEDID, pForm);
			return pForm;
		}

	}

	namespace ExtraData {

		static JohnnyExtraData::EDIDResult __fastcall AddEDID(TESForm* apForm, const NiFixedString& arEDID) noexcept {
			JohnnyExtraData* pData = JohnnyExtraData::GetOrCreate(apForm);
			if (!pData) [[unlikely]]
				return JohnnyExtraData::EDIDResult::FAILURE;

			return pData->SetEditorID(arEDID);
		}

		static JohnnyExtraData::EDIDResult __fastcall RemoveEDID(const TESForm* apForm, const NiFixedString& arEDID) noexcept {
			JohnnyExtraData* pData = JohnnyExtraData::Find(apForm);
			if (!pData) [[unlikely]]
				return JohnnyExtraData::EDIDResult::FAILURE;

			return pData->RemoveEditorID(arEDID);
		}

		static JohnnyExtraData::EDIDResult __fastcall GetEDID(const TESForm* apForm, NiFixedString& arOutEDID) noexcept {
			const JohnnyExtraData* pData = JohnnyExtraData::Find(apForm);
			if (pData && pData->GetEditorID()) [[likely]] {
				arOutEDID = pData->GetEditorID();
				return JohnnyExtraData::EDIDResult::SUCCESS;
			}
			return JohnnyExtraData::EDIDResult::FAILURE;
		}

		static const char* __fastcall GetEDIDString(const TESForm* apForm) noexcept {
			const JohnnyExtraData* pData = JohnnyExtraData::Find(apForm);
			if (pData && pData->GetEditorID()) [[likely]]
				return pData->GetEditorID().c_str();
			return "";
		}

		static uint32_t __fastcall GetEDIDLength(const TESForm* apForm) noexcept {
			const JohnnyExtraData* pData = JohnnyExtraData::Find(apForm);
			if (pData && pData->GetEditorID()) [[likely]]
				return pData->GetEditorID().GetLength();
			return 0;
		}

	}

	namespace IgnoredConflicts {

		static NiFixedString strWilderness;

		static SPEC_NOINLINE bool __fastcall IsIgnored(const TESForm* apExistingForm, const NiFixedString& arEDID) noexcept {
			// Ignore 0x18E because Obsidian had a skill issue
			if (apExistingForm->GetFormID() == 0x18E) [[unlikely]]
				return true;

			if (arEDID == strWilderness) [[unlikely]]
				return true;

			return false;
		}

		static void InitializeStrings() noexcept {
			strWilderness = "Wilderness";
		}

	}

	static SPEC_NOINLINE void __fastcall LogEDIDConflict(const TESForm* apExistingForm, const NiFixedString& arEDID, const TESForm* apForm) noexcept {
		const TESFile* pFileA = apForm->GetFile(0);
		const TESFile* pFileB = apExistingForm->GetFile(0);

		const char* pFileAName = pFileA ? pFileA->GetName() : "";
		const char* pFileBName = pFileB ? pFileB->GetName() : "";

		if (apExistingForm->GetFormType() == apForm->GetFormType()) [[likely]] {
			_MESSAGE("%08X (\"%s\") steals EDID \"%s\" from %08X (\"%s\")",
				apForm->GetFormID(), pFileAName, 
				arEDID.c_str(),
				apExistingForm->GetFormID(), pFileBName);
		}
		else [[unlikely]] {
			_MESSAGE("%08X (\"%s\") steals EDID \"%s\" from %08X (\"%s\") + changes type from %s to %s",
				apForm->GetFormID(), pFileAName, 
				arEDID.c_str(),
				apExistingForm->GetFormID(), pFileBName,
				apExistingForm->GetFormTypeName(), apForm->GetFormTypeName());
		}
		bHadEDIDConflicts = true;
	}

	static SPEC_NOINLINE void __fastcall AddToGameMap(TESForm* apForm, const NiFixedString& arEDID) noexcept {
		const TESForm* pExistingForm = Map::Get(arEDID);
		if (pExistingForm) [[unlikely]] {
			if (pExistingForm == apForm) [[likely]] {
				DEBUG_MSG("Form %08X already has EDID \"%s\" in the map, skipping!", apForm->GetFormID(), arEDID.c_str());
				return;
			}
			else if (!IgnoredConflicts::IsIgnored(pExistingForm, arEDID)) [[unlikely]] {
				LogEDIDConflict(pExistingForm, arEDID, apForm);
				ExtraData::RemoveEDID(pExistingForm, arEDID);
			}
		}

		Map::Set(arEDID, apForm);
		DEBUG_MSG("Added EDID \"%s\" for form %08X to map", arEDID, apForm->GetFormID());
	}

	// exported
	uint32_t __cdecl JGNVSE_GetFormIDFromEDID(const char* apEDID) noexcept {
		if (apEDID && apEDID[0]) [[likely]] {
			const TESForm* pForm = Map::Get(apEDID);
			if (pForm)
				return pForm->GetFormID();
		}
		return 0;
	}

	HookUtils::CallDetour kRemoveFromDataStructures[2];
	class TESFormEx : public TESForm {
	public:
		uint32_t hk_GetFormEditorIDLength() const noexcept {
			return ExtraData::GetEDIDLength(this);
		}

		// vftable + 0x130
		const char* hk_GetFormEditorID() const noexcept {
			return ExtraData::GetEDIDString(this);
		}

		// vftable + 0x134
		bool hk_SetFormEditorID(const char* apEDID) noexcept {
			DEBUG_MSG("\nForm %08X: Attempting to set EDID to \"%s\"...", GetFormID(), apEDID ? apEDID : "!!NULL!!");
			if (apEDID && apEDID[0]) [[likely]] {
				if (apEDID[0] == 'S' && strcmp(apEDID + 1, "ysWindowCompileAndRun") == 0) [[unlikely]] {
					apEDID = "Console Command";
				}

				const NiFixedString strEDID(apEDID);
				const JohnnyExtraData::EDIDResult eAdded = ExtraData::AddEDID(this, strEDID);
				const bool bSuccess = eAdded == JohnnyExtraData::EDIDResult::SUCCESS;
				if (bSuccess) [[likely]] {
					DEBUG_MSG("Added EDID \"%s\" to form %08X", apEDID, GetFormID());
					if (!GetTemporary() && GetFormID()) [[likely]] {
						AddToGameMap(this, strEDID);
					}
				}
#if DEBUG_PRINTS
				else if (eAdded == JohnnyExtraData::EDIDResult::ALREADY_EXISTS) {
					TESForm* pMapForm = Map::Get(apEDID);
					if (pMapForm == this) [[unlikely]] {
						DEBUG_MSG("EDID \"%s\" is already set for form %08X, skipping adding to game map!", apEDID, GetFormID());
					}
					else if (pMapForm) {
						DEBUG_MSG("EDID \"%s\" is already set for form %08X, but map entry uses form %08X!", apEDID, GetFormID(), pMapForm->GetFormID());
					}
					else {
						DEBUG_MSG("EDID \"%s\" is already set for form %08X, but no map entry exists!", apEDID, GetFormID());
					}
				}
				else if (eAdded == JohnnyExtraData::EDIDResult::FAILURE) {
					DEBUG_MSG("Failed to add EDID \"%s\" to form %08X!", apEDID, GetFormID());
				}
#endif

				return bSuccess;
			}
			return false;
		}

		// Removes EDIDs from the map when form is marked as temporary, or added to the garbage collector
		template<uint32_t INDEX>
		void hk_DetachEditorIDs() noexcept {
			ThisCall(kRemoveFromDataStructures[INDEX], this);
			JohnnyExtraData* pData = JohnnyExtraData::Find(this);
			if (pData) [[likely]]
				pData->DetachEditorIDs();
		}

		static TESForm* hk_GetFormByEditorID(const char* apEDID) noexcept {
			if (apEDID && apEDID[0]) [[likely]]
				return Map::Get(apEDID);
			return nullptr;
		}
	};

	class TESObjectREFREx : public TESObjectREFR {
	public:
		const char* GetNameForConsole() noexcept {
			// TESObjectREFR::GetFullName calls TESFullName::GetFullName on baseform + JIP's ref name override
			const char* pName = GetFullName();
			if (!pName || !pName[0])
				pName = GetFormEditorID();

			if (!pName || !pName[0])
				pName = baseForm->GetFormEditorID();

			return pName;
		}
	};

	template<uint32_t VTABLE_ADDR>
	class CustomSetReplacer {
	private:
		static inline HookUtils::VirtFuncDetour kDetour;

		bool SetFormEditorID(const char* apEDID) noexcept {
			const bool bResult = ThisCall<bool>(kDetour, this, apEDID);
			if (bResult)
				return reinterpret_cast<TESFormEx*>(this)->hk_SetFormEditorID(apEDID);
			return bResult;
		}

	public:
		CustomSetReplacer() noexcept {
			kDetour.ReplaceVirtualFunc(VTABLE_ADDR, &CustomSetReplacer::SetFormEditorID);
		}
	};

	void InitHooks() {
		Map::InitHooks();
		IgnoredConflicts::InitializeStrings();

		kRemoveFromDataStructures[0].ReplaceCall(0x48449A, &TESFormEx::hk_DetachEditorIDs<0>); // TESForm::SetTemporary
		kRemoveFromDataStructures[1].ReplaceCall(0x8680A4, &TESFormEx::hk_DetachEditorIDs<1>); // GarbageCollector::Add(TESObjectREFR)

		HookUtils::WriteRelJump(0x483A00, TESFormEx::hk_GetFormByEditorID); // TESForm::GetFormByEditorID - adds a lock

		HookUtils::WriteRelJump(0x474CB0, &TESFormEx::hk_GetFormEditorIDLength); // TESForm::GetFormEditorIDLength

		HookUtils::ReplaceCall(0x486903, &TESFormEx::hk_GetFormEditorID); // TESForm::GetFormDetailedString
		HookUtils::ReplaceCall(0x451CBA, &TESFormEx::hk_GetFormEditorID); // TESObjectCELL::GetCellName
		HookUtils::ReplaceCall(0x558796, &TESFormEx::hk_GetFormEditorID); // TESObjectCELL::SaveRenderFailureData
		HookUtils::ReplaceCall(0x55D498, &TESFormEx::hk_GetFormEditorID); // TESObjectREFR::GetFormEditorID
		HookUtils::ReplaceCall(0x55D683, &TESFormEx::hk_GetFormEditorID); // TESObjectREFR::GetFormDetailedString
		HookUtils::ReplaceCall(0x55DF83, &TESFormEx::hk_GetFormEditorID); // TESObjectREFR::InitItem
		HookUtils::ReplaceCall(0x55E076, &TESFormEx::hk_GetFormEditorID); // TESObjectREFR::InitItem
		HookUtils::ReplaceCall(0x55E0CC, &TESFormEx::hk_GetFormEditorID); // TESObjectREFR::InitItem
		HookUtils::ReplaceCall(0x61DA92, &TESFormEx::hk_GetFormEditorID); // TESTopicInfo::GetFormDetailedString
		
		HookUtils::ReplaceCall(0x71B748, &TESObjectREFREx::GetNameForConsole); // replaces empty string with editor id in selected ref name in console
		HookUtils::ReplaceCall(0x710BFC, &TESObjectREFREx::GetNameForConsole);

		HookUtils::ReplaceCall(0x66FF57, &TESFormEx::hk_SetFormEditorID); // ActorValueInfo::ActorValueInfo
		HookUtils::ReplaceCall(0x58D7BC, &TESFormEx::hk_SetFormEditorID); // BGSDefaultObjectManager::BGSDefaultObjectManager

		for (uint32_t i = 0; i < ARRAYSIZE(TESForm_Vtables); i++) {
			if (*reinterpret_cast<uintptr_t*>(TESForm_Vtables[i] + 0x130) == 0x00401280)
				HookUtils::ReplaceVirtualFunc(TESForm_Vtables[i] + 0x130, &TESFormEx::hk_GetFormEditorID);

			if (*reinterpret_cast<uintptr_t*>(TESForm_Vtables[i] + 0x134) == 0x00401290)
				HookUtils::ReplaceVirtualFunc(TESForm_Vtables[i] + 0x134, &TESFormEx::hk_SetFormEditorID);
		}

		// These forms already have SetFormEditorID that stores EDID in ExtraData, or a member variable
		// We wrap these functions to ensure the EDID is also stored in JohnnyExtraData, and updated in the game map
		CustomSetReplacer<0x102EAE8> kTESObjectCELL;
		CustomSetReplacer<0x1031A90> kTESWorldSpace;
		CustomSetReplacer<0x1036658> kTESGlobal;
		CustomSetReplacer<0x1045130> kTESSound;
		CustomSetReplacer<0x1047470> kBGSVoiceType;
		CustomSetReplacer<0x1049E40> kTESIdleForm;
		CustomSetReplacer<0x104AD78> kTESQuest;
		CustomSetReplacer<0x104B5F0> kTESRace;
		CustomSetReplacer<0x104D2D0> kTESTopic;
	}

	void PrintErrors() {
		if (bHadEDIDConflicts) {
			// This is crucial for my sanity
			const char* pName = "mod";
			const float fRandom01 = CdeclCall<float>(0x5C5420);
			if (fRandom01 < 0.001f)
				pName = "slop";
			Console_Print("Some EDIDs are conflicting! Check JohnnyGuitarNVSE.log for details. (Ignore this message if you are not a %s author.)", pName);
		}
	}

}

STACK_FRAME_OPT_RESET