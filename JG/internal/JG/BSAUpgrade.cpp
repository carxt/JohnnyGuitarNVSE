#include "BSAUpgrade.hpp"
#include <GameAPI.h>

namespace BSAUpgrade {

	inline void __fastcall SeekFile(NiFile* apFile, int32_t aiOffset, int32_t aiMode) {
		ThisCall(0xAA16D0, apFile, aiOffset, aiMode);
	}

	void __fastcall SeekArchive(ArchiveFile* apFile, uint32_t auiTargetFilePos) {
		const int64_t llTargetFilePos = auiTargetFilePos;
		const int64_t llCurrentPos = apFile->spArchive->m_uiCurrentFilePos;

		int64_t llSeekOffset = llTargetFilePos - llCurrentPos;

		while (llSeekOffset > INT32_MAX) {
			SeekFile(apFile->spArchive, INT32_MAX, FILE_CURRENT);
			llSeekOffset -= INT32_MAX;
		}
		while (llSeekOffset < INT32_MIN) {
			SeekFile(apFile->spArchive, INT32_MIN, FILE_CURRENT);
			llSeekOffset -= INT32_MIN;
		}

		SeekFile(apFile->spArchive, int32_t(llSeekOffset), FILE_CURRENT);

		assert(apFile->spArchive->m_uiCurrentFilePos == auiTargetFilePos);
	}

	SPEC_NAKED void SeekArchive_Asm() {
		static constexpr uint32_t uiReturnAddr = 0xAFB9BD;
		__asm {
			mov     ecx, [ebp - 0xA8]
			mov     edx, [ebp - 0xC]
			call	SeekArchive
			jmp		uiReturnAddr
		}
	}

	void Install() {
		// Handle 64-bit seek offsets in BSA files
		HookUtils::WriteRelJump(0xAFB99B, SeekArchive_Asm);

		// Following patches remove the use of the "Secondary archive" flag from file entry offsets
		// It's unused on PC, so it just blocks us from using full 32-bit range for file offsets
		// The patches are basically removing the "& 0x80000000" from offset getters (which are inlined sadly)
		// The archive invalidation logic is kept the same - 0'd offset continues to mean an invalidated file
		// The word "offset" no longer feels real

		// Archive::CheckValidFile
		HookUtils::SafeWriteBuf(0xAFB2A6, "\x8B\x4D\x08\x8B\x49\x0C\x85\xC9\x0F\x95\xC0\xEB\x43");

		// Archive::CheckInvalidateFile
		HookUtils::WriteRelJump(0xAFB221, 0xAFB234);

		// Archive::InvalidateFile
		HookUtils::WriteRelJump(0xAFAC68, 0xAFAC7B);

		// Archive::InvalidateFile (another one)
		HookUtils::WriteRelJump(0xAFACD6, 0xAFACE9);

		// Archive::FindNewerAndInvalidate
		HookUtils::WriteRelJump(0xAFAEB6, 0xAFAECC);
		HookUtils::WriteRelJump(0xAFB0F0, 0xAFB106);

		// BSFileEntry::GetEntryOffset
		HookUtils::PatchMemoryNop(0x43C3BD, 5);

		// Archive::GetFileByFileEntry
		HookUtils::PatchMemoryNop(0xAFA804, 6);
		HookUtils::PatchMemoryNop(0xAFA87E, 5);

		// Archive::GetFile
		HookUtils::PatchMemoryNop(0xAFA5C0, 6);

		// QueuedFileEntry::GetDescription
		HookUtils::PatchMemoryNop(0xC3D171, 6);
		HookUtils::PatchMemoryNop(0xC3D21A, 6);

		// QueuedFileEntry::GenerateKey
		HookUtils::PatchMemoryNop(0xC3D483, 6);
	}

}
