#include "BSAUpgrade.hpp"
#include "JG/JohnnyPluginData.hpp"
#include <GameAPI.h>
#include <PluginAPI.h>
#include <mutex>

extern NVSECommandTableInterface* g_cmdTableInterface;

namespace BSAUpgrade {

	namespace FullOffsetRange {

		inline void __fastcall SeekFile(NiFile* apFile, int32_t aiOffset, int32_t aiMode) {
#ifdef GAME
			ThisCall(0xAA16D0, apFile, aiOffset, aiMode);
#else
			ThisCall(0x852030, apFile, aiOffset, aiMode);
#endif
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
#ifdef GAME
			static constexpr uint32_t uiReturnAddr = 0xAFB9BD;
#else
			static constexpr uint32_t uiReturnAddr = 0x8AA39D;
#endif
			__asm {
				mov     ecx, [ebp - 0xA8]
				mov     edx, [ebp - 0xC]
				call	SeekArchive
				jmp		uiReturnAddr
			}
		}

		void InitHooks() {
#ifdef GAME
			constexpr uint32_t MLF_MIN_VER = 6;
#else
			constexpr uint32_t MLF_MIN_VER = 7;
#endif
			const PluginInfo* pMLF = g_cmdTableInterface->GetPluginInfoByDLLName("mlf");
			if (!pMLF) {
				MessageBoxA(nullptr, "Mod Limit Fix not found! Please install it in order to use 4GB BSAs.", JohnnyPluginData::JG_FULL_NAME, MB_OK | MB_ICONERROR);
				return;
			}
			else if (pMLF->version < MLF_MIN_VER) {
				char cBuffer[128];
				sprintf_s(cBuffer, "Outdated Mod Limit Fix found! Please update to version %i or higher in order to use 4GB BSAs. You current version is: %i", MLF_MIN_VER, pMLF->version);
				MessageBoxA(nullptr, cBuffer, JohnnyPluginData::JG_FULL_NAME, MB_OK | MB_ICONERROR);
				return;
			}

			// Handle 64-bit seek offsets in BSA files
#ifdef GAME
			HookUtils::WriteRelJump(0xAFB99B, SeekArchive_Asm);
#else
			HookUtils::WriteRelJump(0x8AA37B, SeekArchive_Asm);
#endif

			// Following patches remove the use of the "Secondary archive" flag from file entry offsets
			// It's unused on PC, so it just blocks us from using full 32-bit range for file offsets
			// The patches are basically removing the "& 0x80000000" from offset getters (which are inlined sadly)
			// The archive invalidation logic is kept the same - 0'd offset continues to mean an invalidated file
			// The word "offset" no longer feels real

			// Archive::CheckValidFile
#ifdef GAME
			HookUtils::SafeWriteBuf(0xAFB2A6, "\x8B\x4D\x08\x8B\x49\x0C\x85\xC9\x0F\x95\xC0\xEB\x43");
#else
			HookUtils::SafeWriteBuf(0x8A9C86, "\x8B\x4D\x08\x8B\x49\x0C\x85\xC9\x0F\x95\xC0\xEB\x43");
#endif

			// Archive::CheckInvalidateFile
#ifdef GAME
			HookUtils::WriteRelJump(0xAFB221, 0xAFB234);
#else
			HookUtils::WriteRelJump(0x8A9C01, 0x8A9C14);
#endif

			// Archive::InvalidateFile
#ifdef GAME
			HookUtils::WriteRelJump(0xAFAC68, 0xAFAC7B);
#else
			HookUtils::WriteRelJump(0x8A9648, 0x8A965B);
#endif

			// Archive::InvalidateFile (another one)
#ifdef GAME
			HookUtils::WriteRelJump(0xAFACD6, 0xAFACE9);
#else
			HookUtils::WriteRelJump(0x8A96B6, 0x8A96C9);
#endif

			// Archive::FindNewerAndInvalidate
#ifdef  GAME
			HookUtils::WriteRelJump(0xAFAEB6, 0xAFAECC);
			HookUtils::WriteRelJump(0xAFB0F0, 0xAFB106);
#else
			HookUtils::WriteRelJump(0x8A9896, 0x8A98AC);
			HookUtils::WriteRelJump(0x8A9AD0, 0x8A9AE6);
#endif

#ifdef GAME
			// BSFileEntry::GetEntryOffset
			HookUtils::PatchMemoryNop(0x43C3BD, 5);
#else
			// QueuedTexture::Run
			HookUtils::PatchMemoryNop(0x4BC8B6, 6);
#endif

			// Archive::GetFileByFileEntry
#ifdef GAME
			HookUtils::PatchMemoryNop(0xAFA804, 6);
			HookUtils::PatchMemoryNop(0xAFA87E, 5);
#else
			HookUtils::PatchMemoryNop(0x8A91E4, 6);
			HookUtils::PatchMemoryNop(0x8A925E, 5);
#endif

			// Archive::GetFile
#ifdef GAME
			HookUtils::PatchMemoryNop(0xAFA5C0, 6);
#else
			HookUtils::PatchMemoryNop(0x8A8FA0, 6);
#endif

			// QueuedFileEntry::GetDescription
#ifdef GAME
			HookUtils::PatchMemoryNop(0xC3D171, 6);
			HookUtils::PatchMemoryNop(0xC3D21A, 6);
#else
			HookUtils::PatchMemoryNop(0x9E78C1, 6);
			HookUtils::PatchMemoryNop(0x9E796A, 6);
#endif

			// QueuedFileEntry::GenerateKey
#ifdef GAME
			HookUtils::PatchMemoryNop(0xC3D483, 6);
#else
			HookUtils::PatchMemoryNop(0x9E7BD3, 6);
#endif
		}

	}

	namespace ArchiveCaching {
		// Every game has it, but not FNV/FO3. Always bugged me

		thread_local NiPointer<Archive> spLastArchive;

		void __fastcall CacheArchive(Archive* apArchive) {
			spLastArchive = apArchive;
		}

#pragma region GetArchiveForFile
		// GAME - 0xAF6160
		// GECK - 0x8A4B40
		Archive* __fastcall GetCachedArchiveForFile(const BSHash& arDirHash, const BSHash& arFileHash, ARCHIVE_TYPE aeArchiveType, const char* apFileName) {
			if (spLastArchive && spLastArchive->IsType(aeArchiveType)) {
				uint32_t uiDir = 0;
				uint32_t uiFile = 0;
				if (spLastArchive->FindFile(arDirHash, arFileHash, uiDir, uiFile, apFileName)) {
					return spLastArchive;
				}
			}
			return nullptr;
		}
		
		// GAME - 0xAF61D0
		// GECK - 0x8A4BB0
		SPEC_NAKED void GetCachedArchiveForFile_Asm() {
#ifdef  GAME
			static constexpr uint32_t uiReturnAddr = 0xAF6307;
			static constexpr uint32_t uiSearchAddr = 0xAF61DB;
#else
			static constexpr uint32_t uiReturnAddr = 0x8A4CE7;
			static constexpr uint32_t uiSearchAddr = 0x8A4BBB;
#endif
			__asm {
				push	[ebp + 0x8] // Filename
				push	[ebp + 0xC] // Archive type
				lea     edx, [ebp - 0x14] // File hash
				lea     ecx, [ebp - 0x20]  // Dir hash
				call	GetCachedArchiveForFile

				test	eax, eax
				jz		SEARCH

				jmp		uiReturnAddr

				SEARCH:
#ifdef  GAME
				push    0x11F8170
				call    dword ptr ds : [0xFDF05C]
#else
				push	0xF23448
				call    dword ptr ds : [0xD231CC]
#endif
				jmp		uiSearchAddr
			}
		}

		// GAME - 0xAF6287
		// GECK - 0x8A4C67
		SPEC_NAKED void Cache_GetCachedArchiveForFile_Asm() {
#ifdef GAME
			static constexpr uint32_t uiReturnAddr = 0xAF6290;
#else
			static constexpr uint32_t uiReturnAddr = 0x8A4C70;
#endif
			__asm {
				mov     ecx, [ebp - 0x2C]
				call	CacheArchive
				mov     ecx, [ebp - 0x2C]
				add     ecx, 0x158
				jmp		uiReturnAddr
			}
		}

#pragma endregion

#pragma region GetArchiveForFileEntry
		// GAME - 0xAF6910
		// GECK - 0x8A52F0
		Archive* __fastcall GetCachedArchiveForFileEntry(BSFileEntry* apFileEntry, ARCHIVE_TYPE aeArchiveType) {
			if (spLastArchive && (spLastArchive->IsType(aeArchiveType))) {
				if (spLastArchive->IsFileEntryInArchive(apFileEntry)) {
					return spLastArchive;
				}
			}
			return nullptr;
		}
#pragma warning(push)
#pragma warning(disable: 4733)
		// GAME - 0xAF692F
		// GECK - 0x8A530F
		SPEC_NAKED void GetCachedArchiveForFileEntry_Asm() {
#ifdef GAME
			static constexpr uint32_t uiReturnAddr = 0xAF6B8F;
			static constexpr uint32_t uiSearchAddr = 0xAF6935;
#else
			static constexpr uint32_t uiReturnAddr = 0x8A556F;
			static constexpr uint32_t uiSearchAddr = 0x8A5315;
#endif
			__asm {
				mov     dword ptr fs : [0], eax

				lea     edx, [ebp + 0xC] // Archive type
				lea     ecx, [ebp + 0x8]  // File entry
				call	GetCachedArchiveForFileEntry

				test	eax, eax
				jz		SEARCH

				jmp		uiReturnAddr

				SEARCH:
				jmp		uiSearchAddr
			}
		}
#pragma warning(pop)

		// GAME - 0xAF69E9
		// GECK - 0x8A53C9
		SPEC_NAKED void Cache_GetCachedArchiveForFileEntry1_Asm() {
#ifdef GAME
			static constexpr uint32_t uiReturnAddr = 0xAF69F2;
#else
			static constexpr uint32_t uiReturnAddr = 0x8A53D2;
#endif
			__asm {
				mov     ecx, [ebp - 0x14]
				call	CacheArchive
				mov     ecx, [ebp - 0x14]
				add     ecx, 0x158
				jmp		uiReturnAddr
			}
		}

		// GAME - 0xAF6B0F
		// GECK - 0x8A54EF
		SPEC_NAKED void Cache_GetCachedArchiveForFileEntry2_Asm() {
#ifdef  GAME
			static constexpr uint32_t uiReturnAddr = 0xAF6B18;
#else
			static constexpr uint32_t uiReturnAddr = 0x8A54FB;
#endif
			__asm {
				mov     ecx, [ebp - 0x18]
				call	CacheArchive
				mov     ecx, [ebp - 0x18]
				add     ecx, 0x158
				jmp		uiReturnAddr
			}
		}

#pragma endregion

#pragma region GetFile
		// GAME - 0xAF5FA0
		// GECK - 0x8A4980
		ArchiveFile* __fastcall GetFileFromCachedArchive(const BSHash& arDirHash, const BSHash& arFileHash, ARCHIVE_TYPE aeArchiveType, const char* apFileName, uint32_t auiBufferSize) {
			if (spLastArchive && spLastArchive->IsType(aeArchiveType)) {
				uint32_t uiDir = 0;
				uint32_t uiFile = 0;
				if (spLastArchive->FindFile(arDirHash, arFileHash, uiDir, uiFile, apFileName)) {
					ArchiveFile* pFile = spLastArchive->GetFile(uiDir, uiFile, auiBufferSize, apFileName);
					if (pFile) {
						return pFile;
					}
				}
			}
			return nullptr;
		}

		// GAME - 0xAF600E
		// GECK - 0x8A49EE
		SPEC_NAKED void GetFileFromCachedArchive_Asm() {
#ifdef GAME
			static constexpr uint32_t uiReturnAddr = 0xAF6143;
			static constexpr uint32_t uiSearchAddr = 0xAF6014;
#else
			static constexpr uint32_t uiReturnAddr = 0x8A4B23;
			static constexpr uint32_t uiSearchAddr = 0x8A49F4;
#endif
			__asm {
				push	[ebp + 0xC] // Buffer size
				push	[ebp + 0x8] // Filename
				push	[ebp + 0x10] // Archive type
				lea     edx, [ebp - 0x14] // File hash
				lea     ecx, [ebp - 0x20]  // Dir hash
				call	GetFileFromCachedArchive

				test	eax, eax
				jz		SEARCH

				jmp		uiReturnAddr

				SEARCH:
#ifdef GAME
				mov     edx, dword ptr ds : [0x11F8160]
#else
				mov     edx, dword ptr ds : [0xF23438]
#endif
				jmp		uiSearchAddr
			}
		}

		// GAME - 0xAF60CE
		// GECK - 0x8A4AAE
		SPEC_NAKED void Cache_GetFileFromCachedArchive_Asm() {
#ifdef GAME
			static constexpr uint32_t uiReturnAddr = 0xAF60D7;
#else
			static constexpr uint32_t uiReturnAddr = 0x8A4AB7;
#endif
			__asm {
				mov     ecx, [ebp - 0x2C]
				call	CacheArchive
				mov     edx, [ebp - 0x2C]
				add     edx, 0x158
				jmp		uiReturnAddr
			}
		}
#pragma endregion

#pragma region GetFileEntryForFileFromAllArchives
		// GAME - 0xAF6540
		// GECK - 0x8A4F20
		BSFileEntry* __fastcall GetFileEntryFromCachedArchive(const BSHash& arDirHash, const BSHash& arFileHash, ARCHIVE_TYPE_INDEX aeArchiveTypeIndex, const char* apFileName) {
			if (spLastArchive && spLastArchive->IsType(aeArchiveTypeIndex)) {
				BSFileEntry* pFileEntry = spLastArchive->GetFileEntryForFile(arDirHash, arFileHash, apFileName);
				if (pFileEntry) {
					return pFileEntry;
				}
			}
			return nullptr;
		}

		// GAME - 0xAF6565
		// GECK - 0x8A5095
		SPEC_NAKED void GetFileEntryForFileFromAllArchives_Asm() {
#ifdef GAME
			static constexpr uint32_t uiReturnAddr = 0xAF667C;
			static constexpr uint32_t uiSearchAddr = 0xAF656A;
#else
			static constexpr uint32_t uiReturnAddr = 0x8A519F;
			static constexpr uint32_t uiSearchAddr = 0x8A509A;
#endif
			__asm {
				push	[ebp + 0x14] // Filename
				push	[ebp + 0x8] // Archive type index
				mov     edx, [ebp + 0x10] // File hash
				mov     ecx, [ebp + 0xC]  // Dir hash
				call	GetFileEntryFromCachedArchive

				test	eax, eax
				jz		SEARCH

				jmp		uiReturnAddr

				SEARCH:
#ifdef GAME
				mov     eax, dword ptr ds : [0x11F8160]
#else
				mov     eax, dword ptr ds : [0xF23438]
#endif
				jmp		uiSearchAddr
			}
		}

		// GAME - 0xAF6607
		// GECK - 0x8A512A
		SPEC_NAKED void Cache_GetFileEntryForFileFromAllArchives_Asm() {
#ifdef GAME
			static constexpr uint32_t uiReturnAddr = 0xAF660F;
#define REGISTER eax
#else
			static constexpr uint32_t uiReturnAddr = 0x8A5133;
#define REGISTER edx
#endif

			__asm {
				mov     ecx, [ebp - 0x14]
				call	CacheArchive
				mov     REGISTER, [ebp - 0x14]
				add     REGISTER, 0x158
				jmp		uiReturnAddr
			}
#undef REGISTER
		}
#pragma endregion

		void InitHooks() {
#ifdef GAME
			HookUtils::WriteRelJump(0xAF61D0, GetCachedArchiveForFile_Asm);
			HookUtils::WriteRelJump(0xAF6287, Cache_GetCachedArchiveForFile_Asm);

			HookUtils::WriteRelJump(0xAF692F, GetCachedArchiveForFileEntry_Asm);
			HookUtils::WriteRelJump(0xAF69E9, Cache_GetCachedArchiveForFileEntry1_Asm);
			HookUtils::WriteRelJump(0xAF6B0F, Cache_GetCachedArchiveForFileEntry2_Asm);

			HookUtils::WriteRelJump(0xAF600E, GetFileFromCachedArchive_Asm);
			HookUtils::WriteRelJump(0xAF60CE, Cache_GetFileFromCachedArchive_Asm);

			HookUtils::WriteRelJump(0xAF6565, GetFileEntryForFileFromAllArchives_Asm);
			HookUtils::WriteRelJump(0xAF6607, Cache_GetFileEntryForFileFromAllArchives_Asm);
#else
			HookUtils::WriteRelJump(0x8A4BB0, GetCachedArchiveForFile_Asm);
			HookUtils::WriteRelJump(0x8A4C67, Cache_GetCachedArchiveForFile_Asm);

			HookUtils::WriteRelJump(0x8A530F, GetCachedArchiveForFileEntry_Asm);
			HookUtils::WriteRelJump(0x8A53C9, Cache_GetCachedArchiveForFileEntry1_Asm);
			HookUtils::WriteRelJump(0x8A54EF, Cache_GetCachedArchiveForFileEntry2_Asm);

			HookUtils::WriteRelJump(0x8A49EE, GetFileFromCachedArchive_Asm);
			HookUtils::WriteRelJump(0x8A4AAE, Cache_GetFileFromCachedArchive_Asm);

			HookUtils::WriteRelJump(0x8A5095, GetFileEntryForFileFromAllArchives_Asm);
			HookUtils::WriteRelJump(0x8A512A, Cache_GetFileEntryForFileFromAllArchives_Asm);
#endif
		}
	}

	namespace ArchiveInvalidation {

		constexpr char DATA_PATH[] = "Data\\";

		uint32_t __fastcall CheckArchiveFiles(Archive* apArchive) {
			if ((!apArchive->GetHasDirectoryStrings() || !apArchive->GetHasFileStrings())) [[unlikely]] {
				return 0;
			}

			char cPathBuffer[MAX_PATH];
			cPathBuffer[0] = 0;
			strcpy_s(cPathBuffer, DATA_PATH);

			constexpr uint32_t uiDataLen = sizeof(DATA_PATH);
			constexpr uint32_t uiBufferSize = MAX_PATH - uiDataLen;
			char* pBuffer = &cPathBuffer[uiDataLen - 1];

			apArchive->kArchiveCriticalSection.Lock();

			uint32_t uiInvalidedFiles = 0;
			const uint32_t uiDirCount = apArchive->uiDirectories;
			for (uint32_t i = 0; i < uiDirCount; ++i) {
				const BSDirectoryEntry* pDirectory = &apArchive->pDirectories[i];
				const uint32_t uiFileCount = pDirectory->uiFiles;
				if (!uiFileCount) [[unlikely]]
					continue;

				pBuffer[0] = 0;

				const char* pDirName = apArchive->GetDirectoryString(i);
				if (pDirName) [[likely]] {
					strcat_s(pBuffer, uiBufferSize, pDirName);

					const DWORD dwDirAttributes = GetFileAttributes(cPathBuffer);
					if (dwDirAttributes != INVALID_FILE_ATTRIBUTES && (dwDirAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
						const uint32_t uiFolderLength = strlen(cPathBuffer) + 1;
						const uint32_t uiFileBufferSize = MAX_PATH - uiFolderLength;
						cPathBuffer[uiFolderLength - 1] = '\\';
						cPathBuffer[uiFolderLength] = 0;
						char* pFileBuffer = &cPathBuffer[uiFolderLength];
						pFileBuffer[0] = 0;
						for (uint32_t j = 0; j < uiFileCount; ++j) {
							BSFileEntry* pFile = &pDirectory->pFiles[j];
							if (!pFile->IsChecked() && !pFile->IsInvalidated()) {
								const char* pFileName = apArchive->GetFileString(i, j);
								strcat_s(pFileBuffer, uiFileBufferSize, pFileName);

								const DWORD dwFileAttributes = GetFileAttributes(cPathBuffer);
								if (dwFileAttributes != INVALID_FILE_ATTRIBUTES && (dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) == 0) {
									pFile->SetOffset(0);
									++uiInvalidedFiles;
								}
								pFileBuffer[0] = 0;
							}
							pFile->SetChecked(true);
						}
						continue;
					}
				}

				for (uint32_t j = 0; j < uiFileCount; ++j) {
					pDirectory->pFiles[j].SetChecked(true);
				}
			}

			apArchive->kArchiveCriticalSection.Unlock();

			_MESSAGE("Invalidated %i files for \"%s\"", uiInvalidedFiles, apArchive->cFileName);
			return uiInvalidedFiles;
		}

		void InitHooks() {
#ifdef GAME
			HookUtils::WriteRelJump(0xAFAD00, CheckArchiveFiles);
			HookUtils::SafeWrite8(0xAFB17B, 0x74);
#else
			HookUtils::WriteRelJump(0x8A96E0, CheckArchiveFiles);
			HookUtils::SafeWrite8(0x8A9B5B, 0x74);
#endif
		}

	}

	void Install() {
		FullOffsetRange::InitHooks();
		ArchiveCaching::InitHooks();
		ArchiveInvalidation::InitHooks();
	}

}
