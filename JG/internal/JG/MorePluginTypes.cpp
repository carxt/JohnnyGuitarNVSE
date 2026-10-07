#include "MorePluginTypes.hpp"
#include <GameAPI.h>
#include "Bethesda/TESDataHandler.hpp"
#include "Bethesda/BGSNumericIDIndex.hpp"
#include "Bethesda/BGSSaveLoadFormIDMap.hpp"
#include "Bethesda/BGSSaveLoadManager.hpp"
#include "Bethesda/BGSLoadGameBuffer.hpp"
#include "Bethesda/BGSSaveGameBuffer.hpp"
#include "Bethesda/BGSSaveLoadGame.hpp"
#include "Bethesda/BGSReconstructFormsInAllFilesMap.hpp"

#include "JG/JohnnySerialization.hpp"
#include "internal/CommandOpcodes.h"
#include <ScriptUtils.h>
#include <JIP/JIPUtils.hpp>

#include "Shared/Utils/DebugLog.hpp"
#include "Shared/SafeWrite/SafeWrite.hpp"
#include "Shared/Utils/StackObject.hpp"

extern NVSECommandTableInterface* g_cmdTableInterface;
extern NVSEStringVarInterface* g_strInterface;
extern NVSEScriptInterface* g_scriptInterface;
extern bool (*ExtractArgsEx)(COMMAND_ARGS_EX, ...);

namespace MorePluginTypes {

	class FormID_ViewEx : public FormID_View {
	public:
		constexpr uint32_t		GetProperID() const noexcept { if (IsMedium()) return GetMediumID(); if (IsSmall()) return GetSmallID(); return GetID(); }
		constexpr uint32_t		GetProperIndex() const noexcept { if (IsMedium()) return GetMediumIndex(); if (IsSmall()) return GetSmallIndex(); return GetCompileIndex(); }
	};

	namespace FileHooks {

		static constexpr AddressPtr<uint32_t, 0x11C3F24> iTotalForms;

		void __fastcall OpenCustomPlugins(TESDataHandler* apDataHandler) {
			for (uint32_t i = 0; i < apDataHandler->GetSmallCompiledFileCount(); ++i) {
				TESFile* pFile = apDataHandler->GetSmallFile(i);
				if (pFile->OpenTES(0, false))
					iTotalForms += pFile->kHeader.uiRecordCount;
				else
					_MESSAGE("Failed to open small file \"%s\"", pFile->GetName());
			}

			for (uint32_t i = 0; i < apDataHandler->GetMediumCompiledFileCount(); ++i) {
				TESFile* pFile = apDataHandler->GetMediumFile(i);
				if (pFile->OpenTES(0, false))
					iTotalForms += pFile->kHeader.uiRecordCount;
				else
					_MESSAGE("Failed to open medium file \"%s\"", pFile->GetName());
			}

			for (uint32_t i = 0; i < apDataHandler->GetOverlayFileCount(); ++i) {
				TESFile* pFile = apDataHandler->GetOverlayFile(i);
				if (!pFile->OpenTES(0, false))
					_MESSAGE("Failed to open overlay file \"%s\"", pFile->GetName());
			}
		}

		SPEC_NAKED void OpenCustomPlugins_Asm() {
			static constexpr uint32_t uiReturnAddr = 0x4636FD;
			__asm {
				mov     ecx, [ebp - 0x648]
				call	OpenCustomPlugins

				// Prepare iterator for archives
				mov     eax, [ebp - 0x648]
				add		eax, 0x210
				mov		dword ptr[ebp - 0x84], eax

				jmp		uiReturnAddr
			}
		}

		void __fastcall AddCompiledFile(TESDataHandler* apDataHandler, TESFile* apFile) {
			CompiledFiles& rCompiledFiles = apDataHandler->kCompiledFiles;
			if (apFile->IsOverlay()) {
				if (apFile->uiMasterCount == 0) {
					_MESSAGE("[ TESDataHandler::AddCompiledFile ] Overlay file has no masters!", apFile->GetName());
					return;
				}

				if (rCompiledFiles.kOverlayFiles.IsInArray(apFile)) {
					_MESSAGE("[ TESDataHandler::AddCompiledFile ] Overlay file already in array!", apFile->GetName());
					return;
				}

				// TEST TEST TEST! Should we? Or should we not
#if 1
				const TESFile* pMaster = apFile->GetIndexFile(1);
				apFile->SetCompileIndex(pMaster->GetCompileIndex());
				if (pMaster->IsSmallFile())
					apFile->SetSmallCompileIndex(pMaster->GetSmallCompileIndex());
				else if (pMaster->IsMediumFile())
					apFile->SetMediumCompileIndex(pMaster->GetMediumCompileIndex());
#endif
				rCompiledFiles.kOverlayFiles.Add(apFile);
				_MESSAGE("[ TESDataHandler::AddCompiledFile ] Adding overlay file %s", apFile->GetName());
				return;
			}

			if (apFile->IsMediumFile()) {
				if (rCompiledFiles.kMediumFiles.IsInArray(apFile))
					return;

				const uint32_t uiIndex = rCompiledFiles.kMediumFiles.Add(apFile);
				if (uiIndex > 0xFF) {
					_MESSAGE("[ TESDataHandler::AddCompiledFile ] Too many medium files");
					DebugBreak();
				}
				_MESSAGE("[ TESDataHandler::AddCompiledFile ] Adding medium file %s - FD%02X", apFile->GetName(), uiIndex);
				apFile->SetCompileIndex(0xFD);
				apFile->SetMediumCompileIndex(uiIndex);
				return;
			}

			if (apFile->IsSmallFile()) {
				if (rCompiledFiles.kSmallFiles.IsInArray(apFile))
					return;

				const uint32_t uiIndex = rCompiledFiles.kSmallFiles.Add(apFile);
				if (uiIndex > 0xFFF) {
					_MESSAGE("[ TESDataHandler::AddCompiledFile ] Too many small files");
					DebugBreak();
				}
				_MESSAGE("[ TESDataHandler::AddCompiledFile ] Adding small file %s - FE%03X", apFile->GetName(), uiIndex);
				apFile->SetCompileIndex(0xFE);
				apFile->SetSmallCompileIndex(uiIndex);
				return;
			}

			if (rCompiledFiles.kNormalFiles.IsInArray(apFile))
				return;

			uint32_t uiIndex = rCompiledFiles.kNormalFiles.Add(apFile);
			if (uiIndex >= 0xFE) {
				_MESSAGE("[ TESDataHandler::AddCompiledFile ] Too many files");
				DebugBreak();
			}
			_MESSAGE("[ TESDataHandler::AddCompiledFile ] Adding file %s - %02X", apFile->GetName(), uiIndex);
			apFile->SetCompileIndex(uiIndex);
			apFile->SetSecondCompileIndex(0);
		}

		SPEC_NAKED void AddCompileFile_Asm() {
			static constexpr uint32_t uiReturnAddr = 0x4634D3;
			__asm {
				mov     ecx, [ebp - 0x648]
				mov		edx, [ebp - 0xE8]
				call	AddCompiledFile
				jmp		uiReturnAddr
			}
		}

		SPEC_NAKED void AddActiveCompileFile_Asm() {
			static constexpr uint32_t uiReturnAddr = 0x463662;
			__asm {
				mov     ecx, [ebp - 0x648]
				mov		edx, [ecx + 0x20C]
				call	AddCompiledFile
				jmp		uiReturnAddr
			}
		}

		void __fastcall AdjustFormIDFileIndex(TESFile* apFile, TESFile* apIndexFile) {
			FormID_View uiDefaultFormIDCheck = apFile->kCurrentForm.uiFormID;
			if (!apFile->IsSpecialFile())
				uiDefaultFormIDCheck.SetCompileIndex(0);

			if (uiDefaultFormIDCheck.IsDefault()) {
				reinterpret_cast<FormID_View&>(apFile->kCurrentForm.uiFormID).SetCompileIndex(0);
			}
			else {
				const TESFile* pIndexFile = apIndexFile ? apIndexFile : apFile;
				pIndexFile->AdjustFormIDFileIndex(apFile->kCurrentForm.uiFormID);
			}
		}

		SPEC_NAKED void AdjustFormIDFileIndex_Asm() {
			static constexpr uint32_t uiReturnAddr = 0x472D23;
			__asm {
				mov     ecx, [ebp - 0xC]
				mov     edx, [ebp - 0x8]
				call	AdjustFormIDFileIndex
				jmp		uiReturnAddr
			}
		}

		FormID __fastcall AdjustFormIDFileIndex_CellSearch(TESFile* apFile, FORM* apCurrentForm) {
			FormID uiFormID = apCurrentForm->uiFormID;
			const uint8_t ucIndex = FormID_View(uiFormID).GetCompileIndex();
			const TESFile* pIndexFile = apFile->GetIndexFile(ucIndex + 1);
			if (!pIndexFile)
				pIndexFile = apFile;

			pIndexFile->AdjustFormIDFileIndex(uiFormID);
			return uiFormID;
		}

		SPEC_NAKED void AdjustFormIDFileIndex_CellSearch_Asm() {
			static constexpr uint32_t uiReturnAddr = 0x461FB2;
			__asm {
				mov     ecx, [ebp - 0x2C]
				mov     edx, [ebp - 0x30]
				call	AdjustFormIDFileIndex_CellSearch
				mov     [ebp - 0x3C], eax
				jmp		uiReturnAddr
			}
		}

		template<uint32_t uiReturnAddress>
		SPEC_NAKED void GetFile_Asm() {
			static constexpr uint32_t uiReturnAddr = uiReturnAddress;
			__asm {
				mov     ecx, [ebp - 0x84]	// Index
				mov     edx, [ebp - 0x648]	// TESDataHandler
				mov     edx, [edx + 0x21C]
				mov     ecx, [edx + ecx * 4]
				jmp		uiReturnAddr
			}
		}

		HookUtils::CallDetour kDataHandlerConstructorDetour;
		class TESDataHandlerEx : public TESDataHandler {
		public:
			TESDataHandler* InitializeDataHandler() {
				ThisCall(kDataHandlerConstructorDetour, this);
				ucDLCFlags.Set(HAS_NEW_FILE_TYPES, true);

				new (&kCompiledFiles.kNormalFiles)	BSSimpleArray<TESFile*>(0, 0);
				new (&kCompiledFiles.kSmallFiles)	BSSimpleArray<TESFile*>(0, 0);
				new (&kCompiledFiles.kOverlayFiles) BSSimpleArray<TESFile*>(0, 0);
				new (&kCompiledFiles.kMediumFiles) BSSimpleArray<TESFile*>(0, 0);
				memset(kCompiledFiles.padding, 0xCCCCCCCC, sizeof(kCompiledFiles.padding));
				return this;
			}

			TESFile* GetCompiledFile(uint32_t auiIndex) const {
				if (auiIndex == 0xFF)
					return nullptr;

				if (FormID_View(auiIndex).IsMedium() && SupportsNewFileTypes()) {
					const uint8_t usMediumIndex = FormID_View(auiIndex).GetMediumIndex();
					return kCompiledFiles.GetMediumFile(usMediumIndex);
				}
				else if (FormID_View(auiIndex).IsSmall() && SupportsNewFileTypes()) {
					const uint16_t usSmallIndex = FormID_View(auiIndex).GetSmallIndex();
					return kCompiledFiles.GetSmallFile(usSmallIndex);
				}
				else {
					return kCompiledFiles.GetFile(auiIndex);
				}
			}
		};

		HookUtils::CallDetour kSetTempIDOwnedByFileDetour;
		HookUtils::CallDetour kSetThreadSafeParentDetour;
		HookUtils::CallDetour kSetFileLanguageDetour;
		class TESFileEx : public TESFile {
		public:
			static void __cdecl LoadONAM(FormID auiFormID, TESFile* apFile) {
				const uint8_t ucIndex = FormID_View(auiFormID).GetCompileIndex();
				const TESFile* pIndexFile = apFile->GetIndexFile(ucIndex + 1);
				if (!pIndexFile)
					pIndexFile = apFile;

				pIndexFile->AdjustFormIDFileIndex(auiFormID);
				CdeclCall(kSetTempIDOwnedByFileDetour, auiFormID, apFile);
			}

			void SetThreadSafeParent(TESFile* apParent) {
				SetSecondCompileIndex(0);

				if (apParent->IsMediumFile()) {
					SetMediumFile(true);
					SetMediumCompileIndex(apParent->GetMediumCompileIndex());
				}

				if (apParent->IsSmallFile()) {
					SetSmallFile(true);
					SetSmallCompileIndex(apParent->GetSmallCompileIndex());
				}

				if (apParent->IsOverlay())
					SetOverlay(true);

				ThisCall(kSetThreadSafeParentDetour, this, apParent);
			}

			void SetFileFlags(uint32_t auiLanguage) {
				SetSecondCompileIndex(0);

				SetMediumFile(kCurrentForm.uiFormFlags.Get(TESFile::FileFlags::MEDIUM));

				SetSmallFile(kCurrentForm.uiFormFlags.Get(TESFile::FileFlags::SMALL));

				assert(IsMediumFile() + IsSmallFile() < 2);

				SetOverlay(kCurrentForm.uiFormFlags.Get(TESFile::FileFlags::OVERLAY));

				if (IsOverlay() && !uiMasterCount) {
					_MESSAGE("Overlay file %s - no masters", GetName());
					DebugBreak();
				}

				ThisCall(kSetFileLanguageDetour, this, auiLanguage);
			}
		};

		class TESFormEx : public TESForm {
		public:
			static void __cdecl AddCompileIndex(FormID& auiID, TESFile* apFile) {
				if (!IsDefaultForm(auiID) && apFile) {
					const uint8_t ucIndex = FormID_View(auiID).GetCompileIndex();
					const TESFile* pIndexFile = apFile->GetIndexFile(ucIndex + 1);
					if (!pIndexFile)
						pIndexFile = apFile;
					
					pIndexFile->AdjustFormIDFileIndex(auiID);
				}
			}
		};

		const char cExtensionSearchQueryWildcard[] = "*.es*";
		const char cExtensionSearchQuery[] = ".es";

		void InitHooks() {
			// Load all files with extensions that start with ".es"
			// Feel free to come up with your own weird extension names, I think only the mod managers and xEdit will complain
			HookUtils::SafeWrite8(0x4625B7 + 6, 0x1);
			HookUtils::SafeWrite32(0x4625F8 + 1, uint32_t(&cExtensionSearchQueryWildcard));
			HookUtils::SafeWrite32(0xAF47C4 + 1, uint32_t(&cExtensionSearchQuery));

			kDataHandlerConstructorDetour.ReplaceCall(0x44FF95, &TESDataHandlerEx::InitializeDataHandler);

			// Don't pre-create thread-specific files for AILinearTaskThreads
			// It's already wasteful in vanilla
			// Only dialogue, quest logs, descriptions and cells need them, and not all of that is actually done on those threads
			// Doing it with all overlays and ESLs is only worse
			// They'll get created on-demand instead
			HookUtils::PatchMemoryNopRange(0x8C70A5, 0x8C70B0);

			// TESDataHandler::ConstructObject
			{
				HookUtils::WriteRelJump(0x468102, 0x468169);
				kSetTempIDOwnedByFileDetour.ReplaceCall(0x468174, TESFileEx::LoadONAM);
			}

			// TESDataHandler::CompileFiles
			{
				// Skip file count reset
				HookUtils::SafeWrite8(0x4630D7, 0xEB);

				// Handle indices
				// List files
				HookUtils::WriteRelJump(0x463455, AddCompileFile_Asm);
				// Active file
				HookUtils::WriteRelJump(0x4635D8, AddActiveCompileFile_Asm);

				// Handle normal file iterator (for the OpenTES)
				HookUtils::SafeWrite16(0x463693 + 2, 0x0220);
				HookUtils::WriteRelJump(0x4636A5, GetFile_Asm<0x4636B2>);
				HookUtils::WriteRelJump(0x4636CD, GetFile_Asm<0x4636E0>);

				// Open small and overlay files right after
				// Also setups list iterator for the next step
				HookUtils::WriteRelJump(0x4636F2, OpenCustomPlugins_Asm);

				// Load archives
				HookUtils::SafeWriteBuf(0x4636FD, "\x89\x85\x7C\xFF\xFF\xFF\xEB\x0E\x8B\x85\x7C\xFF\xFF\xFF\x8B\x40\x04\xEB\xED"); // Loop start + increment
				HookUtils::SafeWriteBuf(0x463719, "\x83\xFA\x00\x0F\x84\x74\x01\x00\x00\xEB\x01"); // Iterator nullcheck, loop break
				HookUtils::SafeWriteBuf(0x463748, "\x8B\x08\x8A\x81\x0C\x04\x00\x00\x3C\xFF\x74\x22\x90"); // Get TESFile* from the iterator + check if index is valid
				HookUtils::SafeWriteBuf(0x463772, "\x8B\x08\xEB\x09\xE9\x07\x01\x00\x00"); // Get TESFile* from the iterator + add continue jmp for the failed index check
				HookUtils::WriteRelJump(0x463891, 0x463705); // Jump back to the top

				// Load forms
				HookUtils::SafeWriteBuf(0x4638CD, "\x8B\x85\xB8\xF9\xFF\xFF\x05\x10\x02\x00\x00\xC6\x85\x0B\xFA\xFF\xFF\x01\x89\x85\x7C\xFF\xFF\xFF\x83\xF8\x00\x0F\x84\xB1\x00\x00\x00\xEB\x12\xC6\x85\x0B\xFA\xFF\xFF\x00\x8B\x85\x7C\xFF\xFF\xFF\x8B\x40\x04\xEB\xDD\x8B\x08\x8A\x81\x0C\x04\x00\x00\x3C\xFF\x75\x09");
				// 0x46390E - could check for overlays, if their index remains 0xFF? TODO
				HookUtils::SafeWriteBuf(0x463925, "\x8B\x08\xEB\x09"); // Get TESFile* from the iterator
				HookUtils::SafeWriteBuf(0x463941, "\x8B\x0A\xEB\x09"); // Get TESFile* from the iterator
				HookUtils::WriteRelJump(0x46395A, 0x4638F0);
				HookUtils::SafeWriteBuf(0x46396D, "\x8B\x10\xEB\x09");
				HookUtils::WriteRelJump(0x46399A, 0x4638F0);
			}

			// TESForm::AddCompileIndex
			{
				HookUtils::WriteRelJump(0x485D50, TESFormEx::AddCompileIndex);
			}

			// TESFile::LoadTESInfo
			{
				kSetFileLanguageDetour.ReplaceCall(0x471778, &TESFileEx::SetFileFlags);
			}

			// TESFile::ReadFormHeader
			{
				HookUtils::WriteRelJump(0x472C97, AdjustFormIDFileIndex_Asm);
			}

			// TESDataHandler::GetExtCellDataFromFileByEditorID
			{
				HookUtils::WriteRelJump(0x461F56, AdjustFormIDFileIndex_CellSearch_Asm);
			}

			// TESDataHandler::GetCompiledFile
			{
				HookUtils::WriteRelJump(0x465010, &TESDataHandlerEx::GetCompiledFile);
			}

			// TESFile::GetThreadSafeFileForThread
			{
				kSetThreadSafeParentDetour.ReplaceCall(0x473BD2, &TESFileEx::SetThreadSafeParent);
			}
		}

	}

	namespace SaveLoadHooks {

		constexpr int32_t VANILLA_MINOR_VERSION = 27;
		constexpr int32_t VANILLA_MAJOR_VERSION = 48;
		constexpr int32_t ESL_MINOR_VERSION = VANILLA_MINOR_VERSION + 1;
		constexpr int32_t ESL_MAJOR_VERSION = VANILLA_MAJOR_VERSION + 1;

		HookUtils::CallDetour kSaveLoadGameConstructorDetour;
		class BGSSaveLoadGameEx : public BGSSaveLoadGame {
		public:
			BGSSaveLoadGame* InitializeSaveLoadGame() {
				ThisCall(kSaveLoadGameConstructorDetour, this);
				uiLoadOrderChanges = 0;
				new (&kFiles)		BSSimpleArray<TESFile*>(0, 0);
				new (&kSmallFiles)	BSSimpleArray<TESFile*>(0, 0);
				new (&kMediumFiles)	BSSimpleArray<TESFile*>(0, 0);
				memset(padding, 0xCCCCCCCC, sizeof(padding));
				return this;
			}

			FormID GetConvertedFormID(FormID auiFormID) const {
				const uint8_t ucIndex = FormID_View(auiFormID).GetCompileIndex();
				if (ucIndex == 0xFF)
					return 0;

				const TESFile* pFile = nullptr;
				if (SupportsNewFileTypes() && ucIndex >= 0xFD) {
					if (ucIndex == 0xFD) {
						const uint8_t ucMediumIndex = FormID_View(auiFormID).GetMediumIndex();
						if (ucMediumIndex < kMediumFiles.GetSize())
							pFile = kMediumFiles.GetAt(ucMediumIndex);
					}
					else if (ucIndex == 0xFE) {
						const uint16_t usSmallIndex = FormID_View(auiFormID).GetSmallIndex();
						if (usSmallIndex < kSmallFiles.GetSize())
							pFile = kSmallFiles.GetAt(usSmallIndex);
					}
				}
				else if (ucIndex < kFiles.GetSize()) {
					pFile = kFiles.GetAt(ucIndex);
				}

				if (pFile) {
					pFile->AdjustFormIDFileIndex(auiFormID);
					return auiFormID;
				}

				_MESSAGE("[ BGSSaveLoadGame::GetConvertedFormID ] Not found %08X", auiFormID);
				return 0;
			}

			bool LoadPluginList(BGSSaveLoadFile* apFile) {
				bool bResult = true;

				kFiles.Clear();
				kSmallFiles.Clear();
				kMediumFiles.Clear();
				_MESSAGE("Loading plugin list");
				const TESDataHandler* pDataHandler = TESDataHandler::GetSingleton();
				StackObject<BGSLoadGameBuffer, 0x8646B0, 0x8646F0> kBuffer;
				kBuffer->Load(apFile);
				
				uint8_t ucModCount = 0;
				kBuffer->LoadData(&ucModCount);
				if (ucModCount) {
					_MESSAGE("Mod count: %d", ucModCount);
					
					for (uint32_t i = 0; i < ucModCount; ++i) {
						char cModName[MAX_PATH];
						kBuffer->LoadString(cModName);

						TESFile* pFile = pDataHandler->GetListFile(cModName);
						if (pFile && !pFile->IsSpecialFile() && pFile->GetCompileIndex() != 0xFF) {
							_MESSAGE("Mod %s", cModName);
						}
						else {
							bResult = false;
							pFile = nullptr;
							uiLoadOrderChanges.SetBit<0>();
							_MESSAGE("Missing mod %s", cModName);
						}

						kFiles.Add(pFile);
					}

					if (kFiles.GetSize() != pDataHandler->GetCompiledFileCount())
						uiLoadOrderChanges.SetBit<0>();
				}

				if (SupportsNewFileTypes()) {
					uint16_t usSmallModCount = 0;
					kBuffer->LoadData(&usSmallModCount);
					_MESSAGE("Small mod count: %d", usSmallModCount);
					if (usSmallModCount) {
						for (uint32_t i = 0; i < usSmallModCount; ++i) {
							char cModName[MAX_PATH];
							kBuffer->LoadString(cModName);

							TESFile* pFile = pDataHandler->GetListFile(cModName);
							if (pFile && pFile->IsSmallFile() && pFile->GetCompileIndex() != 0xFF) {
								_MESSAGE("Small mod %s", cModName);
							}
							else {
								bResult = false;
								pFile = nullptr;
								_MESSAGE("Missing small mod %s", cModName);
								uiLoadOrderChanges.SetBit<1>();
							}

							kSmallFiles.Add(pFile);
						}

						if (kSmallFiles.GetSize() != pDataHandler->GetSmallCompiledFileCount())
							uiLoadOrderChanges.SetBit<1>();
					}

					uint32_t uiMediumModCount = 0;
					kBuffer->LoadData(&uiMediumModCount);
					_MESSAGE("Medium mod count: %d", uiMediumModCount);
					if (uiMediumModCount) {
						for (uint32_t i = 0; i < uiMediumModCount; ++i) {
							char cModName[MAX_PATH];
							kBuffer->LoadString(cModName);

							TESFile* pFile = pDataHandler->GetListFile(cModName);
							if (pFile && pFile->IsMediumFile() && pFile->GetCompileIndex() != 0xFF) {
								_MESSAGE("Medium mod %s", cModName);
							}
							else {
								bResult = false;
								pFile = nullptr;
								_MESSAGE("Missing medium mod %s", cModName);
								uiLoadOrderChanges.SetBit<2>();
							}

							kMediumFiles.Add(pFile);
						}

						if (kMediumFiles.GetSize() != pDataHandler->GetSmallCompiledFileCount())
							uiLoadOrderChanges.SetBit<2>();
					}
				}

				return bResult;
			}

			void SavePluginList(BGSSaveLoadFile* apFile) const {
				StackObject<BGSSaveGameBuffer, 0x865BD0, 0x865C10> kBuffer;
				const TESDataHandler* pDataHandler = TESDataHandler::GetSingleton();
				const uint8_t ucModCount = pDataHandler->GetCompiledFileCount();
				kBuffer->SaveData(ucModCount);
				for (uint32_t i = 0; i < ucModCount; ++i) {
					const TESFile* pFile = pDataHandler->GetCompiledFile(i);
					if (pFile)
						kBuffer->SaveString(pFile->GetName(), 0);
				}

				if (BGSSaveLoadManager::GetSingleton()->GetMinorVersion() >= ESL_MINOR_VERSION) {
					const uint16_t usSmallModCount = pDataHandler->GetSmallCompiledFileCount();
					kBuffer->SaveData(usSmallModCount);
					for (uint32_t i = 0; i < usSmallModCount; ++i) {
						const TESFile* pFile = pDataHandler->GetSmallFile(i);
						if (pFile)
							kBuffer->SaveString(pFile->GetName(), 0);
					}

					// Bethesda apparently uses uint32_t here, based on MO2's save read code
					const uint32_t uiMediumModCount = pDataHandler->GetMediumCompiledFileCount();
					kBuffer->SaveData(uiMediumModCount);
					for (uint32_t i = 0; i < uiMediumModCount; ++i) {
						const TESFile* pFile = pDataHandler->GetMediumFile(i);
						if (pFile)
							kBuffer->SaveString(pFile->GetName(), 0);
					}
				}

				kBuffer->Save(apFile);
			}
		};

		class BGSSaveLoadManagerEx : public BGSSaveLoadManager {
		public:
			int32_t GetMinorVersion() const {
				int32_t iVersion = VANILLA_MINOR_VERSION;
				if (TESDataHandler::GetSingleton()->GetSmallCompiledFileCount())
					iVersion = ESL_MINOR_VERSION;

				_MESSAGE("Using minor version %i", iVersion);
				return iVersion;
			}

			int32_t GetMajorVersion() const {
				int32_t iVersion = VANILLA_MAJOR_VERSION;
				if (TESDataHandler::GetSingleton()->GetSmallCompiledFileCount())
					iVersion = ESL_MAJOR_VERSION;

				_MESSAGE("Using major version %i", iVersion);
				return iVersion;
			}
		};

		class BGSSaveLoadFormIDMapEx : public BGSSaveLoadFormIDMap {
		public:
			FormID ConvertFormID(FormID auiFormID) const {
				if (FormID_View(auiFormID).IsCreated())
					return auiFormID;
				else
					return reinterpret_cast<BGSSaveLoadGameEx*>(BGSSaveLoadGame::GetSingleton())->GetConvertedFormID(auiFormID);
			}
		};

		class BGSReconstructFormsInAllFilesMapEx : public BGSReconstructFormsInAllFilesMap {
		public:
			TESFile* GetFileForFormID(BSSimpleList<TESFile*>* apWorldFiles, FormID auiFormID) {
				const TESForm* pForm = TESForm::GetFormByNumericID(auiFormID);
				if (pForm)
					return pForm->GetFile(-1);

				const uint8_t ucIndex = FormID_View(auiFormID).GetCompileIndex();
				TESFile* pFile = TESFile::GetFileForTempID(auiFormID);
				if (pFile)
					return pFile;

				const TESDataHandler* pDataHandler = TESDataHandler::GetSingleton();
				if (ucIndex == 0xFD) {
					const uint8_t ucMediumIndex = FormID_View(auiFormID).GetMediumIndex();
					if (ucMediumIndex < pDataHandler->GetMediumCompiledFileCount())
						return pDataHandler->GetMediumFile(ucMediumIndex);
				}
				else if (ucIndex == 0xFE) {
					const uint16_t usSmallIndex = FormID_View(auiFormID).GetSmallIndex();
					if (usSmallIndex < pDataHandler->GetSmallCompiledFileCount())
						return pDataHandler->GetSmallFile(usSmallIndex);
				}
				else if (ucIndex < pDataHandler->GetCompiledFileCount()) {
					return pDataHandler->GetCompiledFile(ucIndex);
				}

				return nullptr;
			}
		};

		class bhkCapsuleShapeEx {
		public:
			// COMDAT folding in action...
			// BGSSaveLoadManager::GetMajorVersion and this are the same function
			// So this one needs to be replaced to prevent issues...
			uint32_t GetCInfoSize() const {
				return 48;
			}
		};

		void InitHooks() {
			// Bump save versions
			HookUtils::WriteRelJump(0x851110, &BGSSaveLoadManagerEx::GetMinorVersion);
			HookUtils::WriteRelJump(0x66D730, &BGSSaveLoadManagerEx::GetMajorVersion);
			HookUtils::SafeWrite8(0x850EF8 + 3, ESL_MAJOR_VERSION);
			HookUtils::SafeWrite8(0x850F46 + 3, ESL_MAJOR_VERSION);
			HookUtils::SafeWrite8(0x850F6D + 1, ESL_MAJOR_VERSION);
			HookUtils::SafeWrite8(0x850F4C + 1, ESL_MAJOR_VERSION);
			// Fix conflict due to COMDAT folding...
			HookUtils::ReplaceVirtualFunc(0x1066ED4, &bhkCapsuleShapeEx::GetCInfoSize);

			kSaveLoadGameConstructorDetour.ReplaceCall(0x8474C5, &BGSSaveLoadGameEx::InitializeSaveLoadGame);
			HookUtils::WriteRelJump(0x847660, &BGSSaveLoadGameEx::LoadPluginList); // Conflict with Tweaks - PrintNewModsOnLoad
			HookUtils::WriteRelJump(0x847590, &BGSSaveLoadGameEx::SavePluginList);

			HookUtils::WriteRelJump(0x846D80, &BGSSaveLoadFormIDMapEx::ConvertFormID);

			HookUtils::WriteRelJump(0x843FE0, &BGSReconstructFormsInAllFilesMapEx::GetFileForFormID);
		}

	}

	namespace OtherHooks {

		FormID __fastcall GetRawFormID(const TESForm* apForm) {
			return FormID_ViewEx(apForm->GetFormID()).GetProperID();
		}

		void InitHooks() {
			HookUtils::ReplaceCall(0x604384, GetRawFormID); // TESNPC::GetHeadPartModTextureFileName
			HookUtils::ReplaceCall(0x60439B, GetRawFormID);	// TESNPC::GetHeadPartModTextureFileName
			HookUtils::ReplaceCall(0x614863, GetRawFormID); // TESRace::GetBodyModTextureName
			HookUtils::ReplaceCall(0x614873, GetRawFormID); // TESRace::GetBodyModTextureName
			HookUtils::ReplaceCall(0x617460, GetRawFormID); // TESResponse::GetAudioFilename
			HookUtils::ReplaceCall(0x5441F1, GetRawFormID); // TESObjectCELL::GetGroupBlockKey
			HookUtils::ReplaceCall(0x544251, GetRawFormID); // TESObjectCELL::GetGroupSubBlockKey

			// Handle TESDataHandler::GetExtCellDataFromFileByEditorID
			HookUtils::SafeWrite8(0x461D71 + 1, 0x50);
			HookUtils::SafeWrite16(0x461DD5, 0x5174);
			HookUtils::SafeWrite16(0x461DE4, 0x4275);
			HookUtils::SafeWriteBuf(0x461E28, "\x8B\x45\x9C\x05\x10\x02\x00\x00\x89\x45\xD8\xEB\x08\x8B\x45\xD8\x8B\x40\x04\xEB\xF3\x83\xF8\x00\x0F\x84\xA0\x03\x00\x00\x8B\x08\x85\xC9\x74\xE9\x8A\x91\x0C\x04\x00\x00\x80\xFA\xFF\x74\xDE\x89\x4D\xD4\xEB\x0A");
		
			// Just for an error message in FalloutAudio::ResolveSoundName...
			HookUtils::ReplaceCall(0x82D2FD, &TESDataHandler::GetCompiledFileCount);
		}

	}

	void InitHooks() {
		SaveLoadHooks::InitHooks();
		FileHooks::InitHooks();
		OtherHooks::InitHooks();
	}

}

namespace MorePluginTypes {

	static TESFile* __fastcall JIP_LookupModByName(TESDataHandler* apThis, const char* apFileName) {
		return apThis->GetListFile(apFileName);
	}

	static bool __fastcall JIP_GetResolvedModIndex(uint8_t& arIndex) {
		if (arIndex == 0xFF)
			return true;

		TESFile* pFile = BGSSaveLoadGame::GetSingleton()->GetSaveMod(arIndex);
		if (!pFile)
			return false;

		arIndex = pFile->GetCompileIndex();
		return true;
	}

	static FormID __fastcall JIP_GetResolvedFormID(FormID& arFormID) {
		if (arFormID == 0)
			return 0;

		if (FormID_View(arFormID).IsCreated())
			return arFormID;

		FormID uiFormID = 0;
		JohnnySerialization::_ResolveFormID(arFormID, &uiFormID);
		arFormID = uiFormID;
		return uiFormID;
	}

	TESFile* __fastcall GetOverridingMod(TESForm* apForm) {
		return apForm->GetFile(-1);
	}

	TESFile* __fastcall GetOverridingModOrID(TESForm* apForm) {
		TESFile* pFile = apForm->GetFile(-1);
		if (pFile)
			return pFile;
		return reinterpret_cast<TESFile*>(0xFF);
	}

	void __cdecl JIP_SaveMod(const TESFile* apFile) {
		bool bValidFile = apFile && apFile != reinterpret_cast<TESFile*>(0xFF);
		const uint8_t ucIndex = bValidFile ? apFile->GetCompileIndex() : 0xFF;
		const uint16_t usSecondIndex = bValidFile ? apFile->GetSecondCompileIndex() : 0;
		JohnnySerialization::_WriteRecord8(ucIndex);
		JohnnySerialization::_WriteRecord16(usSecondIndex);
	}

	TESFile* __fastcall JIP_LoadMod(uint8_t aucIndex, uint16_t ausSecondIndex, bool abSupportsSpecial) {
		FormID_View uiTempFormID(0);
		if (abSupportsSpecial) {
			if (aucIndex == 0xFD)
				uiTempFormID.SetMediumIndex(ausSecondIndex);
			else if (aucIndex == 0xFE)
				uiTempFormID.SetSmallIndex(ausSecondIndex);
		}
		else if (aucIndex == 0xFE)
			return nullptr;
		else if (aucIndex == 0xFD)
			return nullptr;

		uiTempFormID.SetCompileIndex(aucIndex);
		return TESDataHandler::GetSingleton()->GetCompiledFileForFormID(uiTempFormID.Get());
	}

	// I'm having more fun than you can imagine
	namespace JIPAuxVars {

		constexpr uint32_t AUX_VAR_SAVE_VERSION = 11;

		uint32_t uiSaveModAddr = 0x100162BC;
		SPEC_NAKED void JIP_SaveMod_Asm() {
			__asm {
				mov     eax, [esi + 4]
				push	eax
				call	JIP_SaveMod
				jmp		uiSaveModAddr
			}
		}

		uint32_t uiLoadModAddr = 0x10015722;
		SPEC_NAKED void JIP_LoadMod_Asm() {
			__asm {
				mov		cl, [esi]
				add		esi, 1

				mov		edx, dword ptr[ebp - 0x28]
				cmp		edx, AUX_VAR_SAVE_VERSION
				jl		SKIP_ESL

				push	1
				movzx	edx, word ptr[esi]
				add		esi, 2
				jmp		LOAD_VAR

				SKIP_ESL:
				mov		edx, 0
				push	0

				LOAD_VAR:
				call	JIP_LoadMod
				mov		[ebp - 0xC], eax
				movzx   ebx, word ptr[esi]
				add     esi, 2
				mov		[ebp - 0x1C], ebx
				jmp		uiLoadModAddr
			}
		}

		void InitHooks() {
			// AuxiliaryVariableGetSize
			HookUtils::ReplaceCall(JIPUtils::GetAddress(0x1001CD19), GetOverridingModOrID);
			HookUtils::PatchMemoryNop(JIPUtils::GetAddress(0x1001CD1E), 3);

			// AuxiliaryVariableGetType
			HookUtils::ReplaceCall(JIPUtils::GetAddress(0x1001CE04), GetOverridingModOrID);
			HookUtils::PatchMemoryNop(JIPUtils::GetAddress(0x1001CE09), 3);

			// AuxiliaryVariableGetFloat
			HookUtils::ReplaceCall(JIPUtils::GetAddress(0x1001CEF4), GetOverridingModOrID);
			HookUtils::PatchMemoryNop(JIPUtils::GetAddress(0x1001CEF9), 3);

			// AuxiliaryVariableGetRef
			HookUtils::ReplaceCall(JIPUtils::GetAddress(0x1001CFE4), GetOverridingModOrID);
			HookUtils::PatchMemoryNop(JIPUtils::GetAddress(0x1001CFE9), 3);

			// AuxiliaryVariableGetString
			HookUtils::ReplaceCall(JIPUtils::GetAddress(0x1001D0D4), GetOverridingModOrID);
			HookUtils::PatchMemoryNop(JIPUtils::GetAddress(0x1001D0D9), 3);

			// AuxiliaryVariableGetAsArray
			HookUtils::ReplaceCall(JIPUtils::GetAddress(0x1001D1F0), GetOverridingModOrID);
			HookUtils::PatchMemoryNop(JIPUtils::GetAddress(0x1001D1F5), 3);

			// AuxiliaryVariableGetAll
			HookUtils::ReplaceCall(JIPUtils::GetAddress(0x1001D36E), GetOverridingModOrID);
			HookUtils::SafeWriteBuf(JIPUtils::GetAddress(0x1001D373), "\x89\xC6\x90");

			// AuxiliaryVariableSetFloat
			HookUtils::ReplaceCall(JIPUtils::GetAddress(0x1001D696), GetOverridingModOrID);
			HookUtils::PatchMemoryNop(JIPUtils::GetAddress(0x1001D69B), 3);

			// AuxiliaryVariableSetRef
			HookUtils::ReplaceCall(JIPUtils::GetAddress(0x1001D7F5), GetOverridingModOrID);
			HookUtils::PatchMemoryNop(JIPUtils::GetAddress(0x1001D7FA), 3);

			// AuxiliaryVariableSetString
			HookUtils::ReplaceCall(JIPUtils::GetAddress(0x1001D95D), GetOverridingModOrID);
			HookUtils::PatchMemoryNop(JIPUtils::GetAddress(0x1001D962), 3);

			// AuxiliaryVariableSetFromArray
			HookUtils::ReplaceCall(JIPUtils::GetAddress(0x1001DB00), GetOverridingModOrID);
			HookUtils::PatchMemoryNop(JIPUtils::GetAddress(0x1001DB05), 3);

			// AuxiliaryVariableErase
			HookUtils::ReplaceCall(JIPUtils::GetAddress(0x1001DCE4), GetOverridingModOrID);
			HookUtils::SafeWriteBuf(JIPUtils::GetAddress(0x1001DCE9), "\x89\xC7\x90");

			// AuxiliaryVariableEraseAll
			HookUtils::ReplaceCall(JIPUtils::GetAddress(0x1001DF38), GetOverridingModOrID);
			HookUtils::SafeWriteBuf(JIPUtils::GetAddress(0x1001DF3D), "\x89\xC6\x90");

			// AuxVarGetFltCond
			HookUtils::ReplaceCall(JIPUtils::GetAddress(0x1001E0AF), GetOverridingModOrID);
			HookUtils::PatchMemoryNop(JIPUtils::GetAddress(0x1001E0B4), 3);

			// Save
			HookUtils::SafeWrite8(JIPUtils::GetAddress(0x10016261) + 1, AUX_VAR_SAVE_VERSION);
			HookUtils::WriteRelJump(JIPUtils::GetAddress(0x100162B1) , JIP_SaveMod_Asm);
			uiSaveModAddr = JIPUtils::GetAddress(0x100162BC);

			// Load
			HookUtils::SafeWrite8(JIPUtils::GetAddress(0x100156EA) + 3, AUX_VAR_SAVE_VERSION); 
			HookUtils::WriteRelJump(JIPUtils::GetAddress(0x10015713), JIP_LoadMod_Asm);
			uiLoadModAddr = JIPUtils::GetAddress(0x10015722);
			HookUtils::SafeWriteBuf(JIPUtils::GetAddress(0x10015722), "\x85\xC0\x0F\x84\xA1\x01\x00\x00\xEB\x0E");
			HookUtils::SafeWriteBuf(JIPUtils::GetAddress(0x1001578E), "\x8B\x4D\xF4\x90");
		}

	}

	namespace JIPScriptVars {

		constexpr uint32_t SCRIPT_VAR_SAVE_VERSION = 10;

		uint32_t uiSetVariableReturnAddr = 0x100024DB;
		SPEC_NAKED void SetScriptVar_Asm() {
			__asm {
				mov     eax, [ebp + 0x14]
				mov     edi, [ebp - 8]
				mov		[ecx], edi
				mov		[ecx + 4], eax
				jmp		uiSetVariableReturnAddr
			}
		}

		uint32_t uiSaveModAddr = 0x1001619B;
		SPEC_NAKED void JIP_SaveMod_Asm() {
			__asm {
				mov     eax, [edi + 0x10]
				push	eax
				call	JIP_SaveMod
				jmp		uiSaveModAddr
			}
		}

		uint32_t uiLoadModAddr = 0x10015662;
		SPEC_NAKED void JIP_LoadMod_Asm() {
			__asm {
				mov		cl, [esi]
				add		esi, 1

				mov		edx, dword ptr[ebp - 0x28]
				cmp		edx, SCRIPT_VAR_SAVE_VERSION
				jl		SKIP_ESL

				push	1
				movzx	edx, word ptr[esi]
				add		esi, 2
				jmp		LOAD_VAR

				SKIP_ESL:
				mov		edx, 0
				push	0

				LOAD_VAR:
				call	JIP_LoadMod
				mov		[ebp - 0xC], eax
				mov		ecx, eax

				dec     ebx
				lea     eax, [esi + 1]
				mov		[ebp - 0x38], eax
				movzx   eax, byte ptr[esi]
				add     esi, eax
				mov     al, [esi + 1]
				lea     edi, [esi + 1]
				mov     byte ptr[esi + 1], 0
				add     esi, 9
				jmp		uiLoadModAddr
			}
		}

		uint32_t uiSkipLoadModAddr = 0x100156C0;
		SPEC_NAKED void JIP_SkipLoadMod_Asm() {
			__asm {
				mov		edx, dword ptr[ebp - 0x28]
				cmp		edx, SCRIPT_VAR_SAVE_VERSION
				jl		SKIP_ESL

				movzx   eax, byte ptr[esi + 3]
				lea     esi, [esi + 12]
				jmp		EXIT

				SKIP_ESL:
				movzx   eax, byte ptr[esi + 1]
				lea     esi, [esi + 10]

				EXIT:
				lea     esi, [esi + eax]
				jmp		uiSkipLoadModAddr
			}
		}

		void InitHooks() {
			// Script::AddVariable
			HookUtils::WriteRelJump(JIPUtils::GetAddress(0x100024D0), SetScriptVar_Asm);
			uiSetVariableReturnAddr = JIPUtils::GetAddress(0x100024DB);

			// ScriptVariableAction_Execute
			HookUtils::ReplaceCall(JIPUtils::GetAddress(0x10034C8E), GetOverridingMod);

			// Cmd_RemoveAllAddedVariables_Execute
			HookUtils::ReplaceCall(JIPUtils::GetAddress(0x10034DF8), GetOverridingMod);
			HookUtils::SafeWriteBuf(JIPUtils::GetAddress(0x10034E01), "\x89\xC1\x89\x4D\xFC");
			HookUtils::SafeWrite8(JIPUtils::GetAddress(0x10034E31), 0x39);
			HookUtils::SafeWriteBuf(JIPUtils::GetAddress(0x10034E6E), "\x8B\x4D\xFC");
			HookUtils::SafeWriteBuf(JIPUtils::GetAddress(0x10034EA3), "\x8B\x4D\xFC");

			// Cmd_ClearJIPSavedData_Execute
			HookUtils::ReplaceCall(JIPUtils::GetAddress(0x1003CB3C), GetOverridingMod);
			HookUtils::SafeWriteBuf(JIPUtils::GetAddress(0x1003CB45), "\x89\xC1\x90");
			HookUtils::SafeWriteBuf(JIPUtils::GetAddress(0x1003CBC5), "\x8B\x4D\x10\x90");
			
			// SaveGameCallback
			HookUtils::SafeWrite8(JIPUtils::GetAddress(0x100160F3) + 1, SCRIPT_VAR_SAVE_VERSION);
			HookUtils::WriteRelJump(JIPUtils::GetAddress(0x10016190), JIP_SaveMod_Asm);
			uiSaveModAddr = JIPUtils::GetAddress(0x1001619B);

			// LoadGameCallback
			HookUtils::WriteRelJump(JIPUtils::GetAddress(0x10015640), JIP_LoadMod_Asm);
			uiLoadModAddr = JIPUtils::GetAddress(0x10015662);
			HookUtils::SafeWriteBuf(JIPUtils::GetAddress(0x10015665), "\x85\xC9\xEB\x03");

			HookUtils::WriteRelJump(JIPUtils::GetAddress(0x100156B6), JIP_SkipLoadMod_Asm);
			uiSkipLoadModAddr = JIPUtils::GetAddress(0x100156C0);
		}

	}

	namespace JIPRefMaps {

		constexpr uint32_t REF_MAP_SAVE_VERSION = 11;

		uint32_t uiSaveModAddr = 0x1001655F;
		SPEC_NAKED void JIP_SaveMod_Asm() {
			__asm {
				mov     eax, [edi + 0x4]
				push	eax
				call	JIP_SaveMod
				jmp		uiSaveModAddr
			}
		}

		uint32_t uiLoadModAddr = 0x10015993;
		SPEC_NAKED void JIP_LoadMod_Asm() {
			__asm {
				mov		cl, [esi]
				add		esi, 1

				mov		edx, dword ptr[ebp - 0x28]
				cmp		edx, REF_MAP_SAVE_VERSION
				jl		SKIP_ESL

				push	1
				movzx	edx, word ptr[esi]
				add		esi, 2
				jmp		LOAD_VAR

				SKIP_ESL:
				mov		edx, 0
				push	0

				LOAD_VAR:
				call	JIP_LoadMod
				mov		[ebp - 0xC], eax

				movzx   edi, word ptr[esi]
				add     esi, 2
				mov		[ebp - 0x1C], edi

				jmp		uiLoadModAddr
			}
		}

		void InitHooks() {
			// RMFind
			HookUtils::ReplaceCall(JIPUtils::GetAddress(0x100334AF), GetOverridingModOrID);
			HookUtils::SafeWriteBuf(JIPUtils::GetAddress(0x100334B4), "\x89\xC2\x90");

			// Cmd_RefMapArrayGetAll_Execute
			HookUtils::ReplaceCall(JIPUtils::GetAddress(0x10033E55), GetOverridingModOrID);
			HookUtils::SafeWriteBuf(JIPUtils::GetAddress(0x100334B4), "\x89\xC6\x90");

			// RefMapAddValue
			HookUtils::ReplaceCall(JIPUtils::GetAddress(0x100340CC), GetOverridingModOrID);
			HookUtils::PatchMemoryNop(JIPUtils::GetAddress(0x100340D1), 3);

			// Cmd_RefMapArrayErase_Execute
			HookUtils::ReplaceCall(JIPUtils::GetAddress(0x10034500), GetOverridingModOrID);
			HookUtils::SafeWriteBuf(JIPUtils::GetAddress(0x10034505), "\x89\xC7\x90");

			// Cmd_RefMapArrayValidate_Execute
			HookUtils::ReplaceCall(JIPUtils::GetAddress(0x10034754), GetOverridingModOrID);
			HookUtils::SafeWriteBuf(JIPUtils::GetAddress(0x10034759), "\x89\xC7\x90");

			// Cmd_RefMapArrayDestroy_Execute
			HookUtils::ReplaceCall(JIPUtils::GetAddress(0x100349C2), GetOverridingModOrID);
			HookUtils::SafeWriteBuf(JIPUtils::GetAddress(0x100349C7), "\x89\xC7\x90");

			// SaveGameCallback
			HookUtils::SafeWrite8(JIPUtils::GetAddress(0x10016504) + 1, REF_MAP_SAVE_VERSION);
			HookUtils::WriteRelJump(JIPUtils::GetAddress(0x10016554), JIP_SaveMod_Asm);
			uiSaveModAddr = JIPUtils::GetAddress(0x1001655F);

			// LoadGameCallback
			HookUtils::SafeWrite8(JIPUtils::GetAddress(0x10015941) + 3, REF_MAP_SAVE_VERSION);
			HookUtils::WriteRelJump(JIPUtils::GetAddress(0x1001596C), JIP_LoadMod_Asm);
			uiLoadModAddr = JIPUtils::GetAddress(0x1001597B);
			HookUtils::SafeWriteBuf(JIPUtils::GetAddress(0x1001597B), "\x85\xC0\x0F\x84\x5E\x01\x00\x00\xEB\x0E");
			HookUtils::SafeWriteBuf(JIPUtils::GetAddress(0x10015A1A), "\x8B\x4D\xF4\x90");
		}
	}

	namespace JIPExtraData {

		constexpr uint32_t EXTRA_DATA_SAVE_VERSION = 3;

		uint32_t uiRefHasExtraDataReturnAddr;
		SPEC_NAKED void RefHasExtraData_Asm() {
			__asm {
				mov     eax, [ebp - 0x4]
				test    eax, eax
				jnz		SELECT_FILE

				mov     ecx, [ebp + 0x18]
				call	GetOverridingMod
				jmp		EXIT

				SELECT_FILE:
				push	eax
				mov		ecx, dword ptr ds:[0x11C3F2C] // pDataHandler
				call	TESDataHandler::GetCompiledFile

				EXIT:
				mov		[ebp - 0x4], eax
				test	eax, eax
				jmp		uiRefHasExtraDataReturnAddr
			}
		}

		uint32_t uiGetRefExtraDataReturnAddr;
		SPEC_NAKED void GetRefExtraData_Asm() {
			__asm {
				test    ebx, ebx
				jnz		SELECT_FILE

				mov     ecx, [ebp + 0x18]
				call	GetOverridingMod
				mov		ebx, eax
				jmp		EXIT

				SELECT_FILE:
				push	ebx
				mov		ecx, dword ptr ds:[0x11C3F2C] // pDataHandler
				call	TESDataHandler::GetCompiledFile
				mov		ebx, eax

				EXIT:
				test	ebx, ebx
				jmp		uiGetRefExtraDataReturnAddr
			}
		}

		uint32_t uiSaveModAddr;
		SPEC_NAKED void JIP_SaveMod_Asm() {
			__asm {
				mov		eax, [esi]
				push	eax
				call	JIP_SaveMod
				jmp		uiSaveModAddr
			}
		}

		uint32_t uiLoadModAddr;
		SPEC_NAKED void JIP_LoadMod_Asm() {
			__asm {
				mov		[ebp - 0x30], eax

				mov		cl, [esi]
				add		esi, 1

				mov		edx, dword ptr[ebp - 0x28]
				cmp		edx, EXTRA_DATA_SAVE_VERSION
				jl		SKIP_ESL

				push	1
				movzx	edx, word ptr[esi]
				add		esi, 2
				jmp		LOAD_VAR

				SKIP_ESL:
				mov		edx, 0
				push	0

				LOAD_VAR:
				call	JIP_LoadMod
				mov		[ebp - 0xC], eax

				mov		edi, dword ptr[esi]
				mov		[ebp - 0x1C], edi
				add     esi, 4

				movzx   edi, word ptr[esi]
				mov		[ebp - 0x18], edi
				add		esi, 2

				movzx   edi, word ptr[esi]
				mov     [ebp - 0x38], edi
				add		esi, 2

				mov		[ebp - 0x34], esi

				jmp		uiLoadModAddr
			}
		}

		void InitHooks() {
			// Cmd_RefHasExtraData_Execute
			HookUtils::WriteRelJump(JIPUtils::GetAddress(0x1002E0DC), RefHasExtraData_Asm);
			uiRefHasExtraDataReturnAddr = JIPUtils::GetAddress(0x1002E0F6);
			HookUtils::SafeWrite8(JIPUtils::GetAddress(0x1002E0F6), 0x74);

			// Cmd_GetRefExtraData_Execute
			HookUtils::WriteRelJump(JIPUtils::GetAddress(0x1002E1B6), GetRefExtraData_Asm);
			uiGetRefExtraDataReturnAddr = JIPUtils::GetAddress(0x1002E1CB);
			HookUtils::SafeWrite8(JIPUtils::GetAddress(0x1002E1CB) + 1, 0x84);

			// Cmd_SetRefExtraData_Execute
			HookUtils::ReplaceCall(JIPUtils::GetAddress(0x1002E28C), GetOverridingModOrID);
			HookUtils::PatchMemoryNop(JIPUtils::GetAddress(0x1002E291), 3);

			// SaveGameCallback
			HookUtils::SafeWrite8(JIPUtils::GetAddress(0x10016761 + 1), EXTRA_DATA_SAVE_VERSION);
			HookUtils::WriteRelJump(JIPUtils::GetAddress(0x10016862), JIP_SaveMod_Asm);
			uiSaveModAddr = JIPUtils::GetAddress(0x1001686C);
			HookUtils::SafeWriteBuf(JIPUtils::GetAddress(0x100167EA), "\x6B\xD0\x0B");

			// LoadGameCallback
			HookUtils::SafeWrite8(JIPUtils::GetAddress(0x10015B33 + 3), EXTRA_DATA_SAVE_VERSION);
			HookUtils::WriteRelJump(JIPUtils::GetAddress(0x10015BB1), JIP_LoadMod_Asm);
			uiLoadModAddr = JIPUtils::GetAddress(0x10015BDB);
			HookUtils::SafeWrite8(JIPUtils::GetAddress(0x10015BDB), 0x85);
			HookUtils::SafeWriteBuf(JIPUtils::GetAddress(0x10015C1C), "\x8B\x45\xF4\x90");
		}

	}

	namespace JIPLinkedRefs {

		constexpr uint32_t LINKED_REF_SAVE_VERSION = 10;

		uint32_t uiSetRefReturnAddr = 0x100027C0;
		SPEC_NAKED void SetRef_Asm() {
			__asm {
				mov     eax, [ebp + 0x8]
				mov     eax, [eax + 0xC]
				mov		[ecx], eax
				mov     eax, [ebp + 0xC]
				mov		[ecx + 0x4], eax
				jmp		uiSetRefReturnAddr
			}
		}

		uint32_t uiSaveModAddr = 0x100169D4;
		SPEC_NAKED void JIP_SaveMod_Asm() {
			__asm {
				add     esp, 4
				mov		eax, [edi + 0xC]
				push	eax
				call	JIP_SaveMod
				jmp		uiSaveModAddr
			}
		}

		uint32_t uiLoadModAddr = 0x10015D2C;
		SPEC_NAKED void JIP_LoadMod_Asm() {
			__asm {
				mov		[ebp - 0x5C], eax

				mov		eax, dword ptr [esi]
				mov		[ebp - 0x8], eax // FormID
				add		esi, 4

				mov		eax, dword ptr [esi]
				mov     [ebp - 0x30], eax // Link FormID
				add		esi, 4

				mov		cl, [esi]
				add		esi, 1

				mov		edx, dword ptr[ebp - 0x28]
				cmp		edx, LINKED_REF_SAVE_VERSION
				jl		SKIP_ESL

				push	1
				movzx	edx, word ptr[esi]
				add		esi, 2
				jmp		LOAD_VAR

				SKIP_ESL:
				mov		edx, 0
				push	0

				LOAD_VAR:
				call	JIP_LoadMod
				mov		[ebp - 0xC], eax

				lea     ecx, [ebp - 0x8]

				jmp		uiLoadModAddr
			}
		}

		void InitHooks() {
			// TESObjectREFR::SetLinkedRef
			HookUtils::WriteRelJump(JIPUtils::GetAddress(0x100027B2), SetRef_Asm);
			uiSetRefReturnAddr = JIPUtils::GetAddress(0x100027C0);

			// Cmd_SetLinkedReference_Execute
			HookUtils::ReplaceCall(JIPUtils::GetAddress(0x10028DFF), GetOverridingModOrID);

			// Cmd_ClearJIPSavedData_Execute
			HookUtils::SafeWriteBuf(JIPUtils::GetAddress(0x1003CD25), "\x8B\x41\x0C\x90");

			// SaveGameCallback
			HookUtils::SafeWrite8(JIPUtils::GetAddress(0x10016966) + 1, LINKED_REF_SAVE_VERSION);
			HookUtils::WriteRelJump(JIPUtils::GetAddress(0x100169C6), JIP_SaveMod_Asm);
			uiSaveModAddr = JIPUtils::GetAddress(0x100169D4);

			// LoadGameCallback
			HookUtils::WriteRelJump(JIPUtils::GetAddress(0x10015D11), JIP_LoadMod_Asm);
			uiLoadModAddr = JIPUtils::GetAddress(0x10015D2C);
			HookUtils::SafeWriteBuf(JIPUtils::GetAddress(0x10015D45), "\x8B\x45\xF4\x85\xC0\x74\x6F\xEB\x06");
			HookUtils::SafeWrite8(JIPUtils::GetAddress(0x10015D5A), 0x89);
		}

	}

	namespace JIPCCC {

		// 0x1007673B
		static TESFile* pJIP_CCC = nullptr;
		static const char* pEDID_Version = "iJIPCCCVersion";
		static const char* pEDID_Startup = "iJIPCCCStartup";
		static const char* pEDID_CurrentTask = "JIPCCCCurrentTask";

		uint32_t uiCCCOnLoad_1_ReturnAddr = 0x1003F1F7;
		SPEC_NAKED void CCCOnLoad_1_Asm() {
			__asm {
				mov     ecx, [ebp + 0x18]
				push    0
				mov     eax, 0x484E60 // TESForm::GetFile
				call    eax

				mov		pJIP_CCC, eax

				push	pEDID_Version
				mov		eax, 0x483A00 // TESForm::GetFormByEditorID
				call	eax
				add     esp, 4

				push    esi
				jmp		uiCCCOnLoad_1_ReturnAddr
			}
		}

		uint32_t uiCCCOnLoad_2_ReturnAddr = 0x1003FDA6;
		SPEC_NAKED void CCCOnLoad_2_Asm() {
			__asm {
				push	pEDID_Version
				mov		eax, 0x483A00 // TESForm::GetFormByEditorID
				call	eax
				add     esp, 4

				jmp		uiCCCOnLoad_2_ReturnAddr
			}
		}

		uint32_t uiCCCOnLoad_3_ReturnAddr = 0x1003FDA6;
		SPEC_NAKED void CCCOnLoad_3_Asm() {
			__asm {
				push	pEDID_CurrentTask
				mov		eax, 0x483A00 // TESForm::GetFormByEditorID
				call	eax
				add     esp, 4

				jmp		uiCCCOnLoad_3_ReturnAddr
			}
		}

		void InitHooks() {
			// Oh Jazz...
			HookUtils::SafeWrite8(JIPUtils::GetAddress(0x1003F1C9), 0x83);
			HookUtils::SafeWrite32(JIPUtils::GetAddress(0x1003F1C9) + 2, uint32_t(&pJIP_CCC));

			HookUtils::WriteRelJump(JIPUtils::GetAddress(0x1003F1D8), CCCOnLoad_1_Asm);
			uiCCCOnLoad_1_ReturnAddr = JIPUtils::GetAddress(0x1003F1F7);

			HookUtils::WriteRelJump(JIPUtils::GetAddress(0x1003FD9A), CCCOnLoad_2_Asm);
			uiCCCOnLoad_2_ReturnAddr = JIPUtils::GetAddress(0x1003FDA6);

			HookUtils::WriteRelJump(JIPUtils::GetAddress(0x1003F3AE), CCCOnLoad_3_Asm);
			uiCCCOnLoad_3_ReturnAddr = JIPUtils::GetAddress(0x1003F3C3);

			// Cmd_CCCSMS_Execute
			HookUtils::SafeWrite8(JIPUtils::GetAddress(0x10041595), 0x8B);
			HookUtils::SafeWrite32(JIPUtils::GetAddress(0x10041595) + 2, uint32_t(&pJIP_CCC));
			HookUtils::SafeWrite8(JIPUtils::GetAddress(0x100415B6), 0x39);
			HookUtils::SafeWrite8(JIPUtils::GetAddress(0x100415B6) + 2, 0x10);
			
			// TODO: Mod FormIDs are still hardcoded; will work only if they are full plugins
		}

	}

	void InitJIPHooks() {
		if (!JIPUtils::IsValid())
			return;

		_MESSAGE("[ PluginExpansions ] Initializing JIP hooks (ESL)...");
		HookUtils::WriteRelJump(JIPUtils::GetAddress(0x10057480), JIP_LookupModByName);

		// Stupid cars DRM!!!!
		HookUtils::PatchMemoryNop(JIPUtils::GetAddress(0x10002FF7), 5);

		// RunBatchScript
		// test    eax, eax
		// jz      SKIP
		// jmp	   +17
		HookUtils::ReplaceCall(JIPUtils::GetAddress(0x100365FA), GetOverridingMod);
		HookUtils::SafeWriteBuf(JIPUtils::GetAddress(0x100365FF), "\x85\xC0\x74\x1D\xEB\x11");


		// GetINIPath
		// mov     ecx, edx
		// push    0xFFFFFFFF
		// mov     edx, 0x484E60 (TESForm::GetFile)
		// call    edx
		// jmp	   +3
		HookUtils::SafeWriteBuf(JIPUtils::GetAddress(0x1004AA56), "\x89\xD1\x6A\xFF\xBA\x60\x4E\x48\x00\xFF\xD2\xEB\x03");

		HookUtils::WriteRelJump(JIPUtils::GetAddress(0x100016A0), JIP_GetResolvedModIndex);

		HookUtils::WriteRelJump(JIPUtils::GetAddress(0x100016C0), JIP_GetResolvedFormID);

		// TESForm::RefToString
		// mov     ecx, edi
		// push    0xFFFFFFFF
		// mov     eax, 484E60h // TESForm::GetFile
		// call    eax
		// mov     esi, eax
		// jmp     +9
		HookUtils::SafeWriteBuf(JIPUtils::GetAddress(0x10057C1A), "\x89\xF9\x6A\xFF\xB8\x60\x4E\x48\x00\xFF\xD0\x89\xC6\xEB\x09");

		// ModLogPrint
		// mov     edi, eax
		// test    edi, edi
		// jz      EXIT
		// jmp	   +3
		HookUtils::ReplaceCall(JIPUtils::GetAddress(0x1003CF00), GetOverridingMod);
		HookUtils::SafeWriteBuf(JIPUtils::GetAddress(0x1003CF05), "\x89\xC7\x85\xFF\x0F\x84\x3A\x01\x00\x00\xEB\x03");
		HookUtils::PatchMemoryNop(JIPUtils::GetAddress(0x1003CF53), 7);

		// GetModName
		// push	   [ebp - 0x8]
		// mov     ecx, dword ptr ds:[0x11C3F2C] // pDataHandler
		// mov     eax, 0x465010 // TESDataHandler::GetCompiledFile
		// call    eax
		// mov     edx, eax
		// jmp     +3
		HookUtils::SafeWriteBuf(JIPUtils::GetAddress(0x10043FAC), "\xFF\x75\xF8\x8B\x0D\x2C\x3F\x1C\x01\xB8\x10\x50\x46\x00\xFF\xD0\x89\xC2\xEB\x03");

		{
			// Original GetResolvedRefID is in asm, and doesn't edit ECX
			// Thus... compiler reuses ECX after the call
			// This obviously doesn't work with me (us??) replacing GetResolvedRefID...
			
			// AuxVariableValue::ReadValData
			HookUtils::SafeWriteBuf(JIPUtils::GetAddress(0x1000798F), "\x8B\x45\x08\x83\xC0\x04\xEB\xE4");

			// LoadGameCallback
			HookUtils::SafeWrite16(JIPUtils::GetAddress(0x10015E59), 0x9050);
			HookUtils::SafeWrite16(JIPUtils::GetAddress(0x10015E96), 0x9050);
		}

		JIPAuxVars::InitHooks();

		JIPScriptVars::InitHooks();

		JIPRefMaps::InitHooks();

		JIPExtraData::InitHooks();

		JIPLinkedRefs::InitHooks();

		JIPCCC::InitHooks();
	}

}

namespace MorePluginTypes {

	bool JIP_IsFormOverridden(COMMAND_ARGS) {
		TESForm* pForm = nullptr;
		if (ExtractArgsEx(EXTRACT_ARGS_EX, &pForm) && pForm) {
			const FormID uiFormID = scriptObj->GetFormID();
			const uint8_t ucIndex = scriptObj->GetCompileIndex();

			const TESFile* pFile = pForm->GetFile(-1);
			if (!pFile) [[unlikely]]
				return true;

			if (pFile->IsOverlay()) {
				*result = 1;
				return true;
			}

			const uint8_t ucFileIndex = pFile->GetCompileIndex();
			if (ucFileIndex == 0xFF) [[unlikely]]
				return true;

			if (ucIndex == 0xFD && ucIndex == ucFileIndex) {
				const uint8_t ucMediumIndex = FormID_View(scriptObj->GetFormID()).GetMediumIndex();
				if (pFile->GetMediumCompileIndex() > ucMediumIndex) {
					*result = 1;
					return true;
				}
			}
			if (ucIndex == 0xFE && ucIndex == ucFileIndex) {
				const uint16_t usSmallIndex = FormID_View(scriptObj->GetFormID()).GetSmallIndex();
				if (pFile->GetSmallCompileIndex() > usSmallIndex) {
					*result = 1;
					return true;
				}
			}

			if (ucFileIndex > ucIndex) {
				*result = 1;
				return true;
			}
		}
		return true;
	}

	bool JIP_GetLoadOrderChanged(COMMAND_ARGS) {
		const BGSSaveLoadGame* pSaveLoad = BGSSaveLoadGame::GetSingleton();
		*result = pSaveLoad->uiLoadOrderChanges;
		return true;
	}

	uint32_t uiHexToUIntAddr = 0x10006660;
	uint32_t __fastcall HexToUInt(const char* apString) {
		return FastCall<uint32_t>(uiHexToUIntAddr, apString);
	}

	bool JIP_GetFormFromMod(COMMAND_ARGS) {
		char cModName[MAX_PATH] = {};
		char cFormID[16] = {};
		if (!ExtractArgsEx(EXTRACT_ARGS_EX, cModName, cFormID))
			return true;

		const uint8_t ucModIndex = 0xFF;
		TESFile* pFile = nullptr;
		if (_stricmp(cModName, "none")){
			pFile = TESDataHandler::GetSingleton()->GetListFile(cModName);
			if (!pFile)
				return true;
		}

		FormID uiFormID = HexToUInt(cFormID);
		if (pFile)
			pFile->AdjustFormIDFileIndex(uiFormID);
		else
			uiFormID = FormID_View(ucModIndex, uiFormID).Get();

		if (TESForm::GetFormByNumericID(uiFormID))
			*reinterpret_cast<uint32_t*>(result) = uiFormID;

		return true;
	}

	void InitCommandHooks() {
		if (!JIPUtils::IsValid())
			return;

		uiHexToUIntAddr = JIPUtils::GetAddress(0x10006660);

		{
			CommandInfo* pInfo = const_cast<CommandInfo*>(g_cmdTableInterface->GetByOpcode(CommandOpcodes::kIsFormOverridden));
			if (pInfo) {
				pInfo->execute = JIP_IsFormOverridden;
			}
		}
		{
			CommandInfo* pInfo = const_cast<CommandInfo*>(g_cmdTableInterface->GetByOpcode(CommandOpcodes::kGetFormFromMod));
			if (pInfo) {
				pInfo->execute = JIP_GetFormFromMod;
			}
		}
		{
			CommandInfo* pInfo = const_cast<CommandInfo*>(g_cmdTableInterface->GetByOpcode(CommandOpcodes::kGetLoadOrderChanged));
			if (pInfo) {
				pInfo->execute = JIP_GetLoadOrderChanged;
			}
		}
	}

}

namespace MorePluginTypes {

	// We must hook after all plugins finish loading to avoid being overwritten, especially by Stewie...

	HookUtils::CallDetour kDetour;
	void __cdecl InitDelayedHooks(const char* apFilename) {
		InitHooks();
		CdeclCall(kDetour, apFilename);
	}

	void Install() {
		kDetour.ReplaceCall(0x86A91A, InitDelayedHooks);
	}

}