#include "GameObjects.h"
#include "GameData.h"
#include "JohnnyExtraData.hpp"
#include "misc/misc.h"

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
		0x1012834,	//	EffectSetting
		0x1012EA4,	//	EnchantmentItem
		0x1013F8C,	//	SpellItem
		0x102397C,	//	TESRegion
		0x1024214,	//	BGSAddonNode
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
		0x1029D5C,	//	TESObjectACTI
		0x102A0A4,	//	TESObjectANIO
		0x102A31C,	//	TESObjectARMA
		0x102A62C,	//	TESObjectARMO
		0x102A9C4,	//	TESObjectBOOK
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
		0x102F55C,  //  TESObjectREFR
		0x103140C,	//	TESWaterForm
		0x103168C,	//	TESWeather
		0x10320FC,	//	BGSAcousticSpace
		0x103245C,	//	BGSCameraPath
		0x10327F4,	//	BGSCameraShot
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
		0x10366CC,	//	TESLoadScreen
		0x1036854,	//	TESLoadScreenType
		0x10369DC,	//	TESRecipeCategory
		0x1036B2C,	//	TESRecipe
		0x1037094,	//	Script
		0x1045504,	//	BGSBodyPartData
		0x10464B4,	//	BGSHeadPart
		0x104664C,	//	BGSIdleMarker
		0x1046874,	//	BGSNote
		0x1046EC4,	//	BGSPerk
		0x10470EC,	//	BGSRagdoll
		0x104891C,	//	TESChallenge
		0x1048BB4,	//	TESClass
		0x1048F5C,	//	TESCreature
		0x104973C,	//	TESEyes
		0x10498DC,	//	TESFaction
		0x1049B9C,	//	TESHair
		0x104A2F4,	//	TESNPC
		0x104AC44,  //	TESQuest
		0x104BA24,	//	TESReputation
		0x104CC0C,	//	TESSkill
		0x104D5B4,	//	TESTopicInfo
		0x1067A2C,  //  ActorValueInfo
		0x106847C,	//	TESPackage
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
		0x108EA64,  //  ContinuousBeamProjectile
		0x108EE04,  //  Explosion
		0x108F2F4,  //  FlameProjectile
		0x108F674,  //  GrenadeProjectile
		0x108FA44,  //  MissileProjectile
		0x10900DC,  //  Projectile
	};

	namespace Map {
		void __fastcall Set(const char* apEDID, TESForm* apForm) {
			SRWUniqueLock kLock(kEDIDMapLock);
			TESForm::pAllFormsByEditorID->SetAt(apEDID, apForm);
		}

		bool __fastcall Remove(const char* apEDID) {
			SRWUniqueLock kLock(kEDIDMapLock);
			return TESForm::pAllFormsByEditorID->RemoveAt(apEDID);
		}

		TESForm* __fastcall Get(const char* apEDID) {
			SRWSharedLock kLock(kEDIDMapLock);
			TESForm* pForm = nullptr;
			TESForm::pAllFormsByEditorID->GetAt(apEDID, pForm);
			return pForm;
		}
	}

	namespace ExtraData {
		JohnnyExtraData::EDIDResult __fastcall AddEDID(const char* apEDID, TESForm* apForm) {
			JohnnyExtraData* pData = JohnnyExtraData::GetOrCreate(apForm);
			if (!pData) [[unlikely]] {
				char cText[96];
				sprintf_s(cText, "Failed to create JohnnyExtraData for form %08X (%s)!\nSomething is very wrong!", apForm->GetFormID(), apEDID);
				MessageBoxA(nullptr, cText, "JohnnyGuitar", MB_OK | MB_ICONERROR);
				return JohnnyExtraData::EDIDResult::FAILURE;
			}

			return pData->SetEditorID(apEDID);
		}

		JohnnyExtraData::EDIDResult __fastcall RemoveEDID(const char* apEDID, TESForm* apForm) {
			JohnnyExtraData* pData = JohnnyExtraData::Find(apForm);
			if (!pData) [[unlikely]]
				return JohnnyExtraData::EDIDResult::FAILURE;

			return pData->RemoveEditorID(apEDID);
		}

		const char* __fastcall GetEDID(TESForm* apForm) {
			JohnnyExtraData* pData = JohnnyExtraData::Find(apForm);
			if (!pData) [[unlikely]]
				return nullptr;

			return pData->GetEditorID().c_str();
		}
	}

	void __fastcall AddToGameMap(TESForm* apForm, const char* apEDID) {
		TESForm* pExistingForm = Map::Get(apEDID); 
		if (pExistingForm) [[unlikely]] {
			if (pExistingForm == apForm) [[likely]] {
				DEBUG_MSG("Form %08X already has EDID \"%s\" in the map, skipping!", apForm->GetFormID(), apEDID);
				return;
			}
			// Ignore 0x18E because Obsidian had a skill issue
			else if (pExistingForm->GetFormID() != 0x18E) [[likely]] {
				const TESFile* pFileA = apForm->GetFile(0);
				const TESFile* pFileB = pExistingForm->GetFile(0);
				char cText[512];
				if (pExistingForm->GetFormType() == apForm->GetFormType()) {
					sprintf_s(cText, "%08X (\"%s\") steals EDID \"%s\" from %08X (\"%s\")",
						apForm->GetFormID(), pFileA ? pFileA->GetName() : "", apEDID,
						pExistingForm->GetFormID(), pFileB ? pFileB->GetName() : "");
				}
				else {
					sprintf_s(cText, "%08X (\"%s\") steals EDID \"%s\" from %08X (\"%s\") + changes type from %s to %s",
						apForm->GetFormID(), pFileA ? pFileA->GetName() : "", apEDID,
						pExistingForm->GetFormID(), pFileB ? pFileB->GetName() : "",
						pExistingForm->GetFormTypeName(), apForm->GetFormTypeName());
				}
				bHadEDIDConflicts = true;
				_MESSAGE(cText);
				ExtraData::RemoveEDID(apEDID, pExistingForm);
			}
		}

		Map::Set(apEDID, apForm);
		DEBUG_MSG("Added EDID \"%s\" for form %08X to map", apEDID, apForm->GetFormID());
	}

	// exported
	uint32_t __cdecl JGNVSE_GetFormIDFromEDID(char* apEDID) {
		if (apEDID && apEDID[0]) {
			TESForm* pForm = Map::Get(apEDID);
			if (pForm)
				return pForm->GetFormID();
		}
		return 0;
	}

	CallDetour kRemoveFromDataStructures[2];
	class TESFormEx : public TESForm {
	public:
		// vftable + 0x130
		const char* hk_GetFormEditorID() {
			const char* pEDID = ExtraData::GetEDID(this);
			return pEDID ? pEDID : "";
		}

		// vftable + 0x134
		bool hk_SetFormEditorID(const char* apEDID) {
			DEBUG_MSG("\nForm %08X: Attempting to set EDID to \"%s\"...", GetFormID(), apEDID ? apEDID : "!!NULL!!");
			if (apEDID && apEDID[0]) [[likely]] {
				if (apEDID[0] == 'S' && strcmp(apEDID + 1, "ysWindowCompileAndRun") == 0) [[unlikely]] {
					apEDID = "Console Command";
				}

				const JohnnyExtraData::EDIDResult eAdded = ExtraData::AddEDID(apEDID, this);
				const bool bSuccess = eAdded == JohnnyExtraData::EDIDResult::SUCCESS;
				if (bSuccess) [[likely]] {
					DEBUG_MSG("Added EDID \"%s\" to form %08X", apEDID, GetFormID());
					if (!GetTemporary() && GetFormID())
						AddToGameMap(this, apEDID);
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
		void hk_DetachEditorIDs() {
			ThisCall(kRemoveFromDataStructures[INDEX].GetOverwrittenAddr(), this);
			JohnnyExtraData* pData = JohnnyExtraData::Find(this);
			if (pData) [[likely]]
				pData->DetachEditorIDs();
		}

		static TESForm* hk_GetFormByEditorID(const char* apEDID) {
			if (apEDID && apEDID[0]) [[likely]]
				return Map::Get(apEDID);
			return nullptr;
		}
	};

	class TESObjectREFREx : public TESObjectREFR {
	public:
		const char* GetNameForConsole() {
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
		static inline VirtFuncDetour kDetour;

		bool SetFormEditorID(const char* apEDID) {
			bool bResult = ThisCall<bool>(kDetour.GetOverwrittenAddr(), this, apEDID);
			if (bResult)
				return reinterpret_cast<TESFormEx*>(this)->hk_SetFormEditorID(apEDID);
			return bResult;
		}

	public:
		CustomSetReplacer() {
			kDetour.ReplaceVirtualFuncEx(VTABLE_ADDR, &CustomSetReplacer::SetFormEditorID);
		}
		~CustomSetReplacer() {
		}
	};

	void InitHooks() {
		WriteRelJump(0x483A00, TESFormEx::hk_GetFormByEditorID);

		kRemoveFromDataStructures[0].ReplaceCallEx(0x48449A, &TESFormEx::hk_DetachEditorIDs<0>); // TESForm::SetTemporary
		kRemoveFromDataStructures[1].ReplaceCallEx(0x8680A4, &TESFormEx::hk_DetachEditorIDs<1>); // GarbageCollector::Add(TESObjectREFR)

		ReplaceCallEx(0x486903, &TESFormEx::hk_GetFormEditorID); // TESForm::GetFormDetailedString
		ReplaceCallEx(0x451CBA, &TESFormEx::hk_GetFormEditorID); // TESObjectCELL::GetCellName
		ReplaceCallEx(0x55D498, &TESFormEx::hk_GetFormEditorID); // TESObjectREFR::GetFormEditorID
		
		ReplaceCallEx(0x71B748, &TESObjectREFREx::GetNameForConsole); // replaces empty string with editor id in selected ref name in console
		ReplaceCallEx(0x710BFC, &TESObjectREFREx::GetNameForConsole);

		ReplaceCallEx(0x66FF57, &TESFormEx::hk_SetFormEditorID); // ActorValueInfo::ActorValueInfo
		
		SafeWrite16(0x467A12, 0x3AEB); // loads more types in game's editor:form map

		for (uint32_t i = 0; i < ARRAYSIZE(TESForm_Vtables); i++) {
			if (*reinterpret_cast<uintptr_t*>(TESForm_Vtables[i] + 0x130) == 0x00401280)
				ReplaceVirtualFuncEx(TESForm_Vtables[i] + 0x130, &TESFormEx::hk_GetFormEditorID);

			if (*reinterpret_cast<uintptr_t*>(TESForm_Vtables[i] + 0x134) == 0x00401290)
				ReplaceVirtualFuncEx(TESForm_Vtables[i] + 0x134, &TESFormEx::hk_SetFormEditorID);
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
			float fRandom01 = CdeclCall<float>(0x5C5420);
			if (fRandom01 < 0.001f)
				pName = "slop";
			Console_Print("Some EDIDs are conflicting! Check JohnnyGuitarNVSE.log for details. (Ignore this message if you are not a %s author.)", pName);
		}
	}
}