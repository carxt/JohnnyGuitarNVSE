#include "UniqueProperties.hpp"
#include <shared/SafeWrite/SafeWrite.hpp>

namespace UniqueProperties {

	// TLDR:
	// Stencil, alpha and material properties default to being shared, unless they have controllers
	// Abusing free flag space in stencil and alpha properties to have this be toggleable on a per instance bassis
	// TODO:
	// Decide how to handle material properties

	namespace Stencil {

#ifdef GAME
		static constexpr inline uint32_t uiCloneHookAddr = 0xA6F393;
#else
		static constexpr inline uint32_t uiCloneHookAddr = 0x829A53;
#endif

		SPEC_NAKED void NiStencilPropertyClone_Asm() {
			static constexpr uint32_t uiCopyUnique = uiCloneHookAddr + 0x6;
			static constexpr uint32_t uiCopyShared = uiCloneHookAddr + 0x67;
			__asm {
				test	byte ptr [edi + 0x1A], 1
				jne		UNIQUE

				cmp     dword ptr [edi + 0xC], 0
				jne		UNIQUE

				jmp		uiCopyShared

				UNIQUE:
				jmp		uiCopyUnique
			}
		}

		void InitHooks() {
			// Init flags to 0 as DWORD instead of WORD
#ifdef GAME
			HookUtils::SafeWriteBuf(0x49ECC3, "\x89\x4A\x18\x90"); // NiStencilProperty::NiStencilProperty
			HookUtils::SafeWriteBuf(0xA6F3CA, "\x89\x46\x18\x90"); // NiStencilProperty::CreateClone
			HookUtils::SafeWriteBuf(0xA6F3DF, "\x8B\x57\x18\x89\x56\x18\x90\x90"); // NiStencilProperty::CreateClone
			HookUtils::SafeWriteBuf(0xA6F42D, "\x89\x46\x18\x90"); // NiStencilProperty::CreateObject
			HookUtils::SafeWriteBuf(0xA6F481, "\x89\x46\x18\x90"); // NiStencilProperty::_SDMInit
#else
			HookUtils::SafeWriteBuf(0x5124BD, "\x89\x46\x18\x90"); // NiStencilProperty::NiStencilProperty
			HookUtils::SafeWriteBuf(0x5138C2, "\x89\x46\x18\x90"); // BGSAutoWater::GeneratePlaceableWater
			HookUtils::SafeWriteBuf(0x829A8A, "\x89\x46\x18\x90"); // NiStencilProperty::CreateClone
			HookUtils::SafeWriteBuf(0x829A9F, "\x8B\x57\x18\x89\x56\x18\x90\x90"); // NiStencilProperty::CreateClone
			HookUtils::SafeWriteBuf(0x829AED, "\x89\x46\x18\x90"); // NiStencilProperty::CreateObject
			HookUtils::SafeWriteBuf(0x829B41, "\x89\x46\x18\x90"); // NiStencilProperty::_SDMInit
#endif

			HookUtils::WriteRelJump(uiCloneHookAddr, NiStencilPropertyClone_Asm);
		}

	}

	namespace Alpha {

#ifdef GAME
		static constexpr inline uint32_t uiCloneHookAddr = 0xA5CE33;
#else
		static constexpr inline uint32_t uiCloneHookAddr = 0x81B9F3;
#endif

		SPEC_NAKED void NiAlphaPropertyClone_Asm() {
			static constexpr uint32_t uiCopyUnique = uiCloneHookAddr + 0x20;
			static constexpr uint32_t uiCopyShared = uiCloneHookAddr + 0x6;
			__asm {
				bt		word ptr [edi + 0x18], 14
				jb		UNIQUE

				cmp     dword ptr [edi + 0xC], 0
				jne		UNIQUE

				jmp		uiCopyShared

				UNIQUE:
				jmp		uiCopyUnique
			}
		}

		void InitHooks() {
			HookUtils::WriteRelJump(uiCloneHookAddr, NiAlphaPropertyClone_Asm);
		}

	}

	void Install() {
		Stencil::InitHooks();
		Alpha::InitHooks();
	}

}