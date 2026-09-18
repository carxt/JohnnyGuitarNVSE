#include "FileFixes.hpp"
#include <GameAPI.h>

#include "Shared/SafeWrite/SafeWrite.hpp"

namespace FileFixes {

	// Betheda allocates a fixed-size buffer, then proceeds to read file data into it
	// ...using file size for the read amount
	// naturally, this means it can overflow, mainly with decompressed vanilla BSAs or loose files
	SPEC_NAKED void FontFileSizeFix_Asm() {
		static constexpr uint32_t uiReturnAddr = 0xA154E3;
		__asm {
			// Get file size
			mov     ecx, [ebp - 0x18]
			mov     eax, [ecx]
			mov     edx, [eax + 0x28]
			call	edx					// BSFile::GetSize
			mov		[ebp - 0x1B0], eax

			// Allocate a buffer using that size
			push	eax
			mov     ecx, 0x11F6238
			mov		edx, 0xAA3E40
			call	edx

			// Assign the buffer to the Font
			mov		[ebp - 0x15C], eax
			mov     edx, [ebp - 0x218]
			mov		[edx + 0x38], eax

			jmp		uiReturnAddr
		}
	}

	HookUtils::CallDetour kGetFileDetour;
	ArchiveFile* __cdecl GetFileByFileEntry(ARCHIVE_TYPE_INDEX aeArchiveTypeIndex, BSFileEntry* apFileEntry, uint32_t auiBufferSize, const char* apName) {
		ArchiveFile* pFile = CdeclCall<ArchiveFile*>(kGetFileDetour, aeArchiveTypeIndex, apFileEntry, auiBufferSize, apName);
		if (pFile && pFile->spArchive) {
			if (!pFile->cFileName[0] && aeArchiveTypeIndex == ARCHIVE_TYPE_INDEX::TEXTURES) {
				const char* pFileName = pFile->spArchive->GetFileNameForFileEntry(apFileEntry);
				if (pFileName && pFileName[0])
					strcpy_s(pFile->cFileName, pFileName);
			}
		}
		return pFile;
	}

	void Install() {
#ifdef GAME
		// Fix buffer overflow during Fonts file load
		HookUtils::WriteRelJump(0xA154AC, FontFileSizeFix_Asm);
#endif

		// Forcibly read texture filename if there's no embedded one
		// Names are required for queued cubemaps to load properly
#ifdef GAME
		kGetFileDetour.ReplaceCall(0xC3D02E, GetFileByFileEntry);
#else
		kGetFileDetour.ReplaceCall(0x9E777E, GetFileByFileEntry);
#endif

		// Fix ArchiveManager::GetArchiveForFileEntry skipping a critical section unlock on return
#ifdef GAME
		HookUtils::WriteRelJump(0xAF6A6A, 0xAF6B82);
#else
		HookUtils::WriteRelJump(0x8A544A, 0x8A5562);
#endif

		// Fix ArchiveManager::GetFileByFileEntry not using the archive index argument
#ifdef GAME
		HookUtils::SafeWriteBuf(0xAF6378, "\x8B\x4D\x08\xBA\x01\x00\x00\x00\xD3\xE2\x52");
#else
		HookUtils::SafeWriteBuf(0x8A4D58, "\x8B\x4D\x08\xBA\x01\x00\x00\x00\xD3\xE2\x52");
#endif
	}

}