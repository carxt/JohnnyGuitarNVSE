#include "SkyUpdateFixes.hpp"
#include "GameForms.h"
#include "GameAPI.h"
#include "decoding.h"
#include "JIP/JIPUtils.hpp"

namespace SkyUpdateFixes {

	// Game does not update sky elements properly
	// 
	// Clouds can disappear randomly when exiting interiors
	// They are also not culled when they should be, due to wrong checks
	//
	// Precipitation sounds do not play after loading a save
	//
	// Resets are handled incompletely, leaving leftovers
	//
	// These patches are inspired by fixes done in Creation Engine versions

#define THIS_OBJ(X) [[maybe_unused]]X* const pThis = reinterpret_cast<X*>(this);

	namespace CloudUpdateHooks {

		namespace {
			constexpr const char cEmptyCloudPath[] = "Sky\\Alpha.dds";
			constexpr uint32_t uiEmptyCloudPathLength = sizeof(cEmptyCloudPath) - 1;

			static bool __fastcall IsEmptyTexture(const BSString& arTexturePath) {
				const uint32_t uiLength = arTexturePath.GetLength();
				return !uiLength || (uiLength == uiEmptyCloudPathLength && arTexturePath.StrCmp(cEmptyCloudPath, true) == 0);
			}

			static void __fastcall CullCloudLayer(uint32_t auiLayer) {
				Clouds* pClouds = Sky::GetSingleton()->pClouds;
				NiGeometry* pCloud = pClouds->spClouds[auiLayer];
				if (!pCloud) [[unlikely]]
					return;

				pCloud->SetAppCulled(true);

				NiProperty* pProperty = pCloud->GetProperty(NiProperty::kPropertyType_Shade);
				if (!pProperty) [[unlikely]]
					return;

				ThisCall(0x6348E0, pProperty, nullptr); // SkyShaderProperty::SetTexture
			}

			static SPEC_NOINLINE TESTexture* __fastcall HandleCloudTexture(TESTexture* apTexture, uint32_t auiLayer, bool abCull) {
				if (!apTexture || IsEmptyTexture(apTexture->strTextureName)) {
					if (abCull)
						CullCloudLayer(auiLayer);
					return nullptr;
				}
				return apTexture;
			}
		}

		HookUtils::CallDetour kClearTransTexturesDetour;

		class Hook {
		public:
			void ClearAllTextures() {
				THIS_OBJ(Clouds);
				pThis->RemoveTextures();
				ThisCall(kClearTransTexturesDetour, this);
			}
		};

		template<uint32_t uiAddress>
		class GetCloudTextureHook {
			static inline HookUtils::CallDetour kDetour;

			TESTexture* Hook(uint32_t auiLayer) {
				THIS_OBJ(TESWeather);
				const TESWeather* pLastWeather = Sky::GetSingleton()->pLastWeather;

				// Last weather takes priority
				const TESWeather* pWeather = pLastWeather ? pLastWeather : pThis;

				if (pWeather)
					return ThisCall<TESTexture*>(kDetour, pWeather, auiLayer);
				return nullptr;
			}

		public:
			GetCloudTextureHook() {
				kDetour.ReplaceCall(uiAddress, &GetCloudTextureHook::Hook);
			}
		};

		template<uint32_t uiAddress, bool bCullLayer>
		class IsEmptyTextureHook {
			static inline HookUtils::CallDetour kDetour;

			TESTexture* Hook(uint32_t auiLayer) {
				TESTexture* pTexture = ThisCall<TESTexture*>(kDetour, this, auiLayer);
				return HandleCloudTexture(pTexture, auiLayer, bCullLayer);
			}

		public:
			IsEmptyTextureHook() {
				kDetour.ReplaceCall(uiAddress, &IsEmptyTextureHook::Hook);
			}
		};
	
		SPEC_NAKED void ClearCloudTextures_Asm() {
			static constexpr uint32_t uiReturnAddr = 0x63D40B;
			__asm {
				mov     dword ptr[ecx + 0x14], 0 // Overwritten code

				cmp		[ecx + 0x2C], 0			 // Check pClouds
				jz		EXIT

				mov     ecx, [ecx + 0x2C]
				call	Clouds::ClearTransTextures
				
				EXIT:
				jmp		uiReturnAddr
			}
		}

		void InitHooks() {
			// Clear current textures in Sky::ResetWeather
			kClearTransTexturesDetour.ReplaceCall(0x63D0B3, &Hook::ClearAllTextures);

			// Call Clouds::ClearTransTextures when resetting weather in Sky::UpdateWeather
			HookUtils::WriteRelJump(0x63D404, ClearCloudTextures_Asm);

			// Skip pCurrentWather nullcheck in Sky::ReloadAllTextures - we handle it ourselves
			HookUtils::PatchMemoryNop(0x63E349, 6);

			// Use pLastWeather first in Sky::ReloadAllTextures
			GetCloudTextureHook<0x63E395>();
			GetCloudTextureHook<0x63E3AC>();
			GetCloudTextureHook<0x63E3D6>();
			GetCloudTextureHook<0x63E3E8>();

			// Don't load empty textures
			// Game skips textures with empty paths... except forms just use "Sky\Alpha.dds" instead
			// So game loads and renders fully empty textures :)
			IsEmptyTextureHook<0x634438, false>(); // Clouds::Update
			IsEmptyTextureHook<0x634547, true>();  // Clouds::Update
			IsEmptyTextureHook<0x63E395, true>();  // Sky::ReloadAllTextures
		}
	}

	namespace ResetAndUpdateHooks {

		HookUtils::CallDetour kUpdateHDRValues_SetModeDetour;
		HookUtils::CallDetour kUpdateHDRValues_ResetWeatherDetour;
		HookUtils::CallDetour kSetAccelerationDetour;

		class Hook {
		private:
			void ClearSkySounds() {
				THIS_OBJ(Sky);
				auto pIter = pThis->pSkySoundList;
				while (pIter && !pIter->IsEmpty()) {
					SkySound* pSound = pIter->GetItem();
					if (pSound) {
						if (pSound->kHandle.IsPlaying())
							pSound->kHandle.Stop();

						pSound->kHandle.Release();

						delete pSound;
					}
					pIter->RemoveHead();
				}
				SkySound::ucThunderCount = 0;
			}

		public:
			void ActivateSounds() {
				THIS_OBJ(Sky);
				ClearSkySounds();
				const bool bHasSky = pThis->eMode == Sky::Mode::FULL || pThis->eMode == Sky::Mode::FAKE_EXTERIOR;
				if (bHasSky) {
					pThis->ActivateWeatherSounds(pThis->pCurrentWeather);
					pThis->ActivateWeatherSounds(pThis->pLastWeather);
				}
				ThisCall(kUpdateHDRValues_SetModeDetour, this);
			}

			void ResetWeatherClears() {
				THIS_OBJ(Sky)
				pThis->pDefaultWeather = nullptr;
				ThisCall(kUpdateHDRValues_ResetWeatherDetour, this);
				ClearSkySounds();
			}
		};

		SPEC_NAKED void ResetInForceWeather_Asm() {
			static constexpr uint32_t uiReturnAddr = 0x63D0EB;
			__asm {
				mov		[ebp - 0x4], ecx
				call	Sky::ResetWeather
				movzx   eax, byte ptr[ebp + 0xC]
				jmp		uiReturnAddr
			}
		}

		void InitHooks() {
			// Call Sky::ResetWeather at the start of Sky::ForceWeather
			HookUtils::WriteRelJump(0x63D0E4, ResetInForceWeather_Asm);

			// Reset pDefaultWeather in Sky::ResetWeather
			// Call Sky::ClearSkySounds in Sky::ResetWeather
			kUpdateHDRValues_ResetWeatherDetour.ReplaceCall(0x63D0CF, &Hook::ResetWeatherClears);

			// Skip Sky::ActivateWeatherSounds in TES::LeaveInterior
			// Handled by our hook in SetMode below
			HookUtils::SafeWrite8(0x45489C, 0xEB);

			// Activate weather sounds in Sky::SetMode
			kUpdateHDRValues_SetModeDetour.ReplaceCall(0x63A5F8, &Hook::ActivateSounds);
			// Skip SkySound flush in Sky::SetMode, reimplemented by us (made mode agnostic)
			HookUtils::WriteRelJump(0x63A51D, 0x63A5B8);

			// Remove JIP's patch
			// It nulls-out pLastWeather on interior exit
			// We reset pDefaultWeather in ResetWeather
			if (JIPUtils::IsValid())
				HookUtils::PatchMemoryNopRange(JIPUtils::GetAddress(0x10012777), JIPUtils::GetAddress(0x10012786));
		}
	}

	namespace SaveLoadHooks {

		HookUtils::CallDetour kGetWeatherUpdateFlagDetour;

		uintptr_t uiLoadGame_SkyUpdate;
		uintptr_t uiLoadGame_UpdateHDRValues;

		class Hook {
		public:
			bool GetWeatherUpdateFlagOrSaveLoad() {
				THIS_OBJ(Sky);
				const bool bSaveLoad = BGSSaveLoadGame::GetSingleton()->GetSaveGameLoading();
				if (bSaveLoad)
					pThis->ActivateWeatherSounds(pThis->pLastWeather);
				return ThisCall<bool>(kGetWeatherUpdateFlagDetour, this) || bSaveLoad;
			}

			static void RevertSky() {
				Sky* pSky = Sky::GetSingleton();
				pSky->ResetWeather();
				pSky->uiFlags.bRefreshWeather = false;
			}

			static void SkyFinishLoadGame() {
				Sky* pSky = Sky::GetSingleton();
				const bool bHasSky = pSky->eMode == Sky::Mode::FULL || pSky->eMode == Sky::Mode::FAKE_EXTERIOR;
				if (pSky->pClouds && bHasSky) {
					pSky->pClouds->ForceTransTextureUpdate();
#if 1
					// Bethesda I hate you so much
					// (Save loading is single threaded so this is fine)
					const bool bSaveGameLoading = BGSSaveLoadGame::GetSingleton()->uiGlobalFlags.bSaveGameLoading;
					Sun* pSun = pSky->pSun;
					Stars* pStars = pSky->pStars;
					Moon* pMasser = pSky->pMasser;
					Moon* pSecunda = pSky->pSecunda;

					BGSSaveLoadGame::GetSingleton()->uiGlobalFlags.bSaveGameLoading = false;
					pSky->pSun = nullptr;
					pSky->pStars = nullptr;
					pSky->pMasser = nullptr;
					pSky->pSecunda = nullptr;

					pSky->ReloadAllTextures();

					BGSSaveLoadGame::GetSingleton()->uiGlobalFlags.bSaveGameLoading = bSaveGameLoading;
					pSky->pSun = pSun;
					pSky->pStars = pStars;
					pSky->pMasser = pMasser;
					pSky->pSecunda = pSecunda;
#else
					pSky->pClouds->Update(pSky, 0.f);
#endif
				}
				
				ThisCall(uiLoadGame_SkyUpdate, pSky, 0.f);  // Sky::Update
				ThisCall(uiLoadGame_UpdateHDRValues, pSky); // Sky::UpdateHDRValues
			}
		};

		SPEC_NAKED void RevertSky_Asm() {
			static constexpr uint32_t uiReturnAddr = 0x84C44E;
			__asm {
				call	Hook::RevertSky
				mov		al, 1
				jmp		uiReturnAddr
			}
		}

		SPEC_NAKED void FinishLoadGame_Asm() {
			static constexpr uint32_t uiReturnAddr = 0x84C23B;
			__asm {
				call	Hook::SkyFinishLoadGame
				mov		al, 1
				jmp		uiReturnAddr
			}
		}

		void InitHooks() {
			// Skip Update calls in Sky::LoadGame, handled by FinishLoadGame
			HookUtils::WriteRelJump(0x63EEDC, 0x63EEF2);

			// Store skipped call addresses in case someone hooks them
			uiLoadGame_SkyUpdate = HookUtils::GetRelJumpAddr(0x63EEE5);
			uiLoadGame_UpdateHDRValues = HookUtils::GetRelJumpAddr(0x63EEED);

			// Implement Sky::Revert, resets the weather data 
			HookUtils::SafeWrite32(0x84C474, uint32_t(RevertSky_Asm));

			// Implement Sky::FinishLoadGame, handle updates here
			HookUtils::SafeWrite32(0x84C260, uint32_t(FinishLoadGame_Asm));

			// Add GetSaveGameLoading check for ActivateWeatherSounds in Sky::UpdateSound
			// Also call ActivateWeatherSounds for pLastWeather on saveload
			kGetWeatherUpdateFlagDetour.ReplaceCall(0x63D874, &Hook::GetWeatherUpdateFlagOrSaveLoad);
		}
	}

	void Install() {
		CloudUpdateHooks::InitHooks();

		ResetAndUpdateHooks::InitHooks();

		SaveLoadHooks::InitHooks();
	}

#undef THIS_OBJ

}