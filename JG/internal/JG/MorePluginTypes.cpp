#include "MorePluginTypes.hpp"
#include <GameAPI.h>
#include "Bethesda/TESDataHandler.hpp"
#include "Bethesda/BGSNumericIDIndex.hpp"
#include "Bethesda/BGSSaveLoadFormIDMap.hpp"
#include "Bethesda/BGSSaveLoadManager.hpp"
#include "Bethesda/BGSLoadGameBuffer.hpp"
#include "Bethesda/BGSSaveGameBuffer.hpp"
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

bool bSupportESLs = true;
bool bSupportOverlays = true;

namespace MorePluginTypes {

	namespace FileHooks {

		static constexpr AddressPtr<uint32_t, 0x11C3F24> iTotalForms;

		void __fastcall OpenCustomPlugins(TESDataHandler* apDataHandler) {
			if (bSupportESLs) {
				for (uint32_t i = 0; i < apDataHandler->GetSmallCompiledFileCount(); ++i) {
					TESFile* pFile = apDataHandler->GetSmallFile(i);
					if (pFile->OpenTES(0, false))
						iTotalForms += pFile->kHeader.uiRecordCount;
					else
						_MESSAGE("Failed to open small file \"%s\"", pFile->GetName());
				}
			}

			if (bSupportOverlays) {
				for (uint32_t i = 0; i < apDataHandler->GetOverlayFileCount(); ++i) {
					TESFile* pFile = apDataHandler->GetOverlayFile(i);
					if (!pFile->OpenTES(0, false))
						_MESSAGE("Failed to open overlay file \"%s\"", pFile->GetName());
				}
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
			if (bSupportOverlays && apFile->IsOverlay()) {
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
				apFile->SetSmallCompileIndex(pMaster->GetSmallCompileIndex());
#endif
				rCompiledFiles.kOverlayFiles.Add(apFile);
				_MESSAGE("[ TESDataHandler::AddCompiledFile ] Adding overlay file %s", apFile->GetName());
				return;
			}

			if (bSupportESLs && apFile->IsSmallFile()) {
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
			apFile->SetSmallCompileIndex(0);
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
			TESFile* pIndexFile = apIndexFile ? apIndexFile : apFile;
			pIndexFile->AdjustFormIDFileIndex(apFile->kCurrentForm.uiFormID);
		}

		SPEC_NAKED void AdjustFormIDFileIndex_Asm() {
			static constexpr uint32_t uiReturnAddr = 0x472CEC;
			__asm {
				mov     ecx, [ebp - 0xC]
				mov     edx, [ebp - 0x8]
				call	AdjustFormIDFileIndex
				jmp		uiReturnAddr
			}
		}

		void __fastcall AdjustFormIDFileIndex_CellSearch(TESFile* apFile, FORM* apCurrentForm) {
			FormID uiFormID = apCurrentForm->uiFormID;
			uint8_t ucIndex = FormID_View(uiFormID).GetCompileIndex();
			TESFile* pIndexFile = apFile->GetIndexFile(ucIndex + 1);
			if (!pIndexFile)
				pIndexFile = apFile;

			pIndexFile->AdjustFormIDFileIndex(uiFormID);
		}

		SPEC_NAKED void AdjustFormIDFileIndex_CellSearch_Asm() {
			static constexpr uint32_t uiReturnAddr = 0x461FB2;
			__asm {
				mov     ecx, [ebp - 0x2C]
				mov     edx, [ebp - 0x30]
				call	AdjustFormIDFileIndex_CellSearch
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
				if (bSupportESLs || bSupportOverlays) {
					ucDLCFlags.Set(HAS_SMALL_PLUGINS_FLAG, bSupportESLs);
					ucDLCFlags.Set(HAS_OVERLAY_PLUGINS_FLAG, bSupportOverlays);
					kCompiledFiles.Initialize();
				}
				return this;
			}

			TESFile* GetCompiledFile(uint32_t auiIndex) const {
				return kCompiledFiles.GetFile(auiIndex);
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
				if (bSupportESLs) {
					SetSmallCompileIndex(0);
					SetSmallFile(apParent->IsSmallFile());
					SetSmallCompileIndex(apParent->GetSmallCompileIndex());
				}

				if (bSupportOverlays) {
					SetOverlay(apParent->IsOverlay());
				}
				ThisCall(kSetThreadSafeParentDetour, this, apParent);
			}

			void SetFileFlags(uint32_t auiLanguage) {
				if (bSupportESLs) {
					SetSmallCompileIndex(0);
					SetSmallFile(kCurrentForm.uiFormFlags.Get(TESFile::FileFlags::SMALL));
				}

				if (bSupportOverlays) {
					SetOverlay(kCurrentForm.uiFormFlags.Get(TESFile::FileFlags::OVERLAY));

					if (IsOverlay() && !uiMasterCount) {
						_MESSAGE("Overlay file %s - no masters", GetName());
						DebugBreak();
					}
				}

				ThisCall(kSetFileLanguageDetour, this, auiLanguage);
			}
		};

		class TESFormEx : public TESForm {
		public:
			static void __cdecl AddCompileIndex(FormID& auiID, TESFile* apFile) {
				if (!TESForm::IsDefaultForm(auiID) && apFile) {
					const uint8_t ucIndex = FormID_View(auiID).GetCompileIndex();
					TESFile* pIndexFile = apFile->GetIndexFile(ucIndex + 1);
					if (pIndexFile)
						pIndexFile->AdjustFormIDFileIndex(auiID);
					else
						apFile->AdjustFormIDFileIndex(auiID);
				}
			}
		};

		const char cExtensionSearchQueryWildcard[] = "*.es*";
		const char cExtensionSearchQuery[] = "*.es";

		void InitHooks() {
			HookUtils::SafeWrite8(0x4625B7 + 6, 0x1);
			HookUtils::SafeWrite32(0x4625F8 + 1, uint32_t(&cExtensionSearchQueryWildcard));
			HookUtils::SafeWrite32(0xAF47C4 + 1, uint32_t(&cExtensionSearchQuery));

			kDataHandlerConstructorDetour.ReplaceCall(0x44FF95, &TESDataHandlerEx::InitializeDataHandler);

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

		HookUtils::CallDetour kSaveLoadGameConstructorDetour;
		class BGSSaveLoadGameEx : public BGSSaveLoadGame {
		public:
			void InitializeArrays() {
				new (&kFiles) BSSimpleArray<TESFile*>(0, 0);
				new (&kSmallFiles) BSSimpleArray<TESFile*>(0, 0);
				ucLoadOrderChanges = 0;
			}

			BGSSaveLoadGame* InitializeSaveLoadGame() {
				ThisCall(kSaveLoadGameConstructorDetour, this);
				InitializeArrays();
				return this;
			}

			FormID GetConvertedFormID(FormID auiFormID) const {
				const uint8_t ucIndex = FormID_View(auiFormID).GetCompileIndex();
				const uint8_t ucMaxIndex = SupportsSmallPlugins() ? 0xFE : 0xFF;

				TESFile* pFile = nullptr;
				if (ucIndex != ucMaxIndex) {
					if (ucIndex < kFiles.GetSize())
						pFile = kFiles.GetAt(ucIndex);
				}
				else if (bSupportESLs && ucIndex == 0xFE) {
					const uint8_t ucSmallIndex = FormID_View(auiFormID).GetSmallIndex();
					if (ucSmallIndex < kSmallFiles.GetSize())
						pFile = kSmallFiles.GetAt(ucSmallIndex);
				}

				if (pFile) {
					pFile->AdjustFormIDFileIndex(auiFormID);
					return auiFormID;
				}

				_MESSAGE("[ BGSSaveLoadGame::GetConvertedFormID ] Not found %08X", auiFormID);
				return 0;
			}

			bool LoadPluginList(BGSSaveLoadFile* apFile) {
				kFiles.Clear();
				kSmallFiles.Clear();
				_MESSAGE("Loading plugin list");
				TESDataHandler* pDataHandler = TESDataHandler::GetSingleton();
				StackObject<BGSLoadGameBuffer, 0x8646B0, 0x8646F0> kBuffer;
				kBuffer->Load(apFile);

				uint8_t ucModCount = 0;
				kBuffer->LoadData(&ucModCount);
				_MESSAGE("Mod count: %d", ucModCount);
				bool bResult = true;

				for (uint32_t i = 0; i < ucModCount; i++) {
					char cModName[MAX_PATH];
					kBuffer->LoadString(cModName);

					TESFile* pFile = pDataHandler->GetListFile(cModName);
					if (pFile && pFile->ucCompileIndex != 0xFF) {
						_MESSAGE("Mod %s", cModName);
						kFiles.Add(pFile);
					}
					else {
						bResult = false;
						pFile = nullptr;
						kFiles.Add(pFile);
						ucLoadOrderChanges.Set(1);
						_MESSAGE("Missing mod %s", cModName);
					}

					if (kFiles.GetSize() != pDataHandler->GetCompiledFileCount())
						ucLoadOrderChanges.Set(1);
				}

				if (SupportsSmallPlugins()) {
					uint16_t usSmallModCount = 0;
					kBuffer->LoadData(&usSmallModCount);
					_MESSAGE("Small mod count: %d", usSmallModCount);
					if (!usSmallModCount)
						return bResult;

					for (uint32_t i = 0; i < usSmallModCount; i++) {
						char cModName[MAX_PATH];
						kBuffer->LoadString(cModName);

						TESFile* pFile = pDataHandler->GetListFile(cModName);
						if (pFile && pFile->ucCompileIndex != 0xFF) {
							_MESSAGE("Small mod %s", cModName);
							kSmallFiles.Add(pFile);
						}
						else {
							bResult = false;
							pFile = nullptr;
							kSmallFiles.Add(pFile);
							_MESSAGE("Missing small mod %s", cModName);
							ucLoadOrderChanges.Set(2);
						}
					}
					if (kSmallFiles.GetSize() != pDataHandler->GetSmallCompiledFileCount())
						ucLoadOrderChanges.Set(2);
				}

				return bResult;
			}

			void SavePluginList(BGSSaveLoadFile* apFile) const {
				StackObject<BGSSaveGameBuffer, 0x865BD0, 0x865C10> kBuffer;
				const uint8_t ucModCount = TESDataHandler::GetSingleton()->GetCompiledFileCount();
				kBuffer->SaveData(ucModCount);
				for (uint32_t i = 0; i < ucModCount; i++) {
					TESFile* pFile = TESDataHandler::GetSingleton()->GetCompiledFile(i);
					if (pFile) {
						kBuffer->SaveString(pFile->GetName(), 0);
					}
				}

				if (BGSSaveLoadManager::GetSingleton()->GetMinorVersion() > 27) {
					const uint16_t usSmallModCount = TESDataHandler::GetSingleton()->GetSmallCompiledFileCount();
					kBuffer->SaveData(usSmallModCount);
					for (uint32_t i = 0; i < usSmallModCount; i++) {
						TESFile* pFile = TESDataHandler::GetSingleton()->GetSmallFile(i);
						if (pFile)
							kBuffer->SaveString(pFile->GetName(), 0);
					}
				}

				kBuffer->Save(apFile);
			}
		};


		constexpr int32_t VANILLA_MINOR_VERSION = 27;
		constexpr int32_t VANILLA_MAJOR_VERSION = 48;
		constexpr int32_t ESL_MINOR_VERSION = VANILLA_MINOR_VERSION + 1;
		constexpr int32_t ESL_MAJOR_VERSION = VANILLA_MAJOR_VERSION + 1;
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
				if (FormID_View(auiFormID).GetCompileIndex() == 0xFF)
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
				if (bSupportESLs && ucIndex == 0xFE) {
					uint16_t usSmallIndex = FormID_View(auiFormID).GetSmallIndex();
					if (usSmallIndex < pDataHandler->GetSmallCompiledFileCount())
						return pDataHandler->GetSmallFile(usSmallIndex);
				}
				else if (ucIndex < pDataHandler->GetCompiledFileCount()) {
					return pDataHandler->GetCompiledFile(ucIndex);
				}

				return nullptr;
			}
		};

		class BGSNumericIDIndexEx : public BGSNumericIDIndex {
		public:
			static constexpr uint32_t ID_EMPTY		= 0x400000;
			static constexpr uint32_t ID_PRESENT	= 0x800000;
			static constexpr uint32_t ID_FLAGS_MASK	= ID_EMPTY | ID_PRESENT;

			void SetNumericID(FormID auiFormID) {

				FormID uiFormID = 0;
#if 0

				if (BGSSaveLoadManager::GetSingleton()->GetMinorVersion() <= 27) {
					_MESSAGE("Saving Save ver 27, using old FormID resolve");
					uiFormID = BGSSaveLoadGame::GetSingleton()->pFormIDMap->AddFormID(auiFormID);
					if (FormID_View(auiFormID).GetIndex() == 0xFF)
						uiFormID = (uiFormID | ID_PRESENT);
				}
				else {
					const uint8_t ucIndex = FormID_View(auiFormID).GetIndex();
					_MESSAGE("Saving Save ver 28, using new FormID resolve");
					if (auiFormID && (!ucIndex || ucIndex == 0xFF)) {
						if ((auiFormID & ID_FLAGS_MASK) != 0)
							_MESSAGE("[ BGSNumericIDIndex::SetNumericID ] Flag already set on FormID %08X", auiFormID);

						const uint32_t uiMask = ucIndex ? ID_PRESENT : ID_EMPTY;
						uiFormID = auiFormID | uiMask;
					}
					else {
						uiFormID = BGSSaveLoadGame::GetSingleton()->pFormIDMap->AddFormID(auiFormID);
					}
				}
#else
				uiFormID = BGSSaveLoadGame::GetSingleton()->pFormIDMap->AddFormID(auiFormID);
				if (FormID_View(auiFormID).GetCompileIndex() == 0xFF)
					uiFormID = (uiFormID | ID_PRESENT);
#endif
				ucData1 = (uiFormID >> 16) & 0xFF;
				ucData2 = (uiFormID >> 8) & 0xFF;
				ucData3 = uiFormID & 0xFF;
			}

			uint32_t GetNumericID() const {
				const uint32_t uiID = uint32_t(ucData3) + (uint32_t(ucData2) << 8) + (uint32_t(ucData1) << 16);
				uint32_t uiMask = 0xFF000000;
#if 0
				if (!BGSSaveLoadGame::GetSingleton()->SupportsSmallPlugins()) {
					if ((uiID & ID_PRESENT) != 0)
						return uiID & 0x7FFFFF | uiMask;
					else
						return BGSSaveLoadGame::GetSingleton()->pFormIDMap->GetFormID(uiID);
				}
				if ((uiID & ID_FLAGS_MASK) == 0)
					return BGSSaveLoadGame::GetSingleton()->pFormIDMap->GetFormID(uiID);


				if ((uiID & ID_EMPTY) != 0)
					uiMask = 0;

				return uiID & ~ID_FLAGS_MASK | uiMask;
#else
				if ((uiID & ID_PRESENT) != 0)
					return uiID & 0x7FFFFF | uiMask;
				else
					return BGSSaveLoadGame::GetSingleton()->pFormIDMap->GetFormID(uiID);
#endif
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

			HookUtils::WriteRelJump(0x853570, &BGSNumericIDIndexEx::SetNumericID); // Tweaks' inlines conflict
			HookUtils::WriteRelJump(0x853500, &BGSNumericIDIndexEx::GetNumericID);
		}

	}

	namespace OtherHooks {

		FormID __fastcall GetRawFormID(const TESForm* apForm) {
			if (apForm->GetCompileIndex() == 0xFE)
				return FormID_View(apForm->GetFormID()).GetSmallID();
			else
				return FormID_View(apForm->GetFormID()).GetID();
		}

		HookUtils::CallDetour kScriptLoadDetour;
		void __fastcall LoadScriptForm(TESForm* apThis, void*, TESFile* apFile) {
			ThisCall(kScriptLoadDetour, apThis, apFile);
			TESFile* pOrgFile = apThis->GetFile(0);
			if (bSupportESLs && pOrgFile->IsSmallFile()) {
				char cMessage[MAX_PATH];
				our_snprintf(cMessage, sizeof(cMessage), "%s has Script %08X (%s), but is an ESL. Not allowed! Time to die.", pOrgFile->GetName(), apThis->GetFormID(), apThis->GetFormEditorID());
				MessageBox(nullptr, cMessage, "AAAAAAA", MB_ICONERROR);
				ExitProcess(0);
			}
		}

		void InitHooks() {
			if (bSupportESLs) {
				HookUtils::ReplaceCall(0x604384, GetRawFormID); // TESNPC::GetHeadPartModTextureFileName
				HookUtils::ReplaceCall(0x60439B, GetRawFormID);	// TESNPC::GetHeadPartModTextureFileName
				HookUtils::ReplaceCall(0x614863, GetRawFormID); // TESRace::GetBodyModTextureName
				HookUtils::ReplaceCall(0x614873, GetRawFormID); // TESRace::GetBodyModTextureName
				HookUtils::ReplaceCall(0x617460, GetRawFormID); // TESResponse::GetAudioFilename
				HookUtils::ReplaceCall(0x5441F1, GetRawFormID); // TESObjectCELL::GetGroupBlockKey
				HookUtils::ReplaceCall(0x544251, GetRawFormID); // TESObjectCELL::GetGroupSubBlockKey

				kScriptLoadDetour.ReplaceCall(0x5ABA3D, LoadScriptForm);
			}

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

namespace JazzAuxVars {

}

namespace MorePluginTypes {

	static TESFile* __fastcall JIP_LookupModByName(TESDataHandler* apThis, const char* apFileName) {
		return apThis->GetListFile(apFileName);
	}

	static bool __fastcall JIP_GetResolvedModIndex(uint8_t& arIndex) {
		if (arIndex >= 0xFE)
			return true;

		TESFile* pFile = BGSSaveLoadGame::GetSingleton()->GetSaveMod(arIndex);
		if (!pFile)
			return false;

		arIndex = pFile->GetCompileIndex();
		return true;
	}

	uint32_t uiRefToStringRet = 0;
	SPEC_NAKED void JIP_RefToString_Asm() {
		__asm {
			mov		ecx, edi
			push	0xFFFFFFFF
			call	TESForm::GetFile
			mov		esi, eax
			jmp		uiRefToStringRet
		}
	}

	uint32_t uiGetModNameRet = 0;
	SPEC_NAKED void JIP_GetModName_Asm() {
		__asm {
			push	ecx
			mov		ecx, dword ptr ds:[0x11C3F2C]
			call	TESDataHandler::GetCompiledFile
			mov		edx, eax
			jmp		uiGetModNameRet
		}
	}

	TESFile* __fastcall GetOverridingMod(TESForm* apForm) {
		return apForm->GetFile(-1);
	}

#if 0
	// I'm having more fun than you can imagine
	namespace JIPAuxVars {

		constexpr uint32_t AUX_VAR_SAVE_VERSION = 11;

		TESFile* __fastcall GetOverridingModOrID(TESForm* apForm) {
			TESFile* pFile = apForm->GetFile(-1);
			if (pFile)
				return pFile;
			return reinterpret_cast<TESFile*>(0xFF);
		}

		void __fastcall JIP_SaveAuxVarMod(TESFile* apFile) {
			assert(apFile);
			const char* pName = "RUNTIME";
			if (apFile != reinterpret_cast<TESFile*>(0xFF))
				pName = apFile->GetName();
			
			uint8_t ucLength = StrLen(pName);
			JohnnySerialization::_WriteRecordData(&ucLength, 1);
			JohnnySerialization::_WriteRecordData(pName, ucLength);
		}

		uint32_t uiSaveAuxVarModAddr = 0x100162C3;
		SPEC_NAKED void JIP_SaveAuxVarMod_Asm() {
			__asm {
				mov     ecx, [esi + 4]
				call	JIP_SaveAuxVarMod
				movzx   eax, word ptr[esi + 0x10]
				jmp		uiSaveAuxVarModAddr
			}
		}

		void __fastcall JIP_LoadAuxVarMod(TESFile* apFile) {
			assert(apFile);
			const char* pName = "RUNTIME";
			if (apFile != reinterpret_cast<TESFile*>(0xFF))
				pName = apFile->GetName();

			uint8_t ucLength = StrLen(pName);
			JohnnySerialization::_WriteRecordData(&ucLength, 1);
			JohnnySerialization::_WriteRecordData(pName, ucLength);
		}

		uint32_t uiLoadAuxVarModAddr = 0x100162C3;
		SPEC_NAKED void JIP_LoadAuxVarMod_Asm() {
			__asm {
				mov     ecx, [esi + 4]
				call	JIP_LoadAuxVarMod
				movzx   eax, word ptr[esi + 0x10]
				jmp		uiLoadAuxVarModAddr
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
			HookUtils::WriteRelJump(JIPUtils::GetAddress(0x100162B1) , JIP_SaveAuxVarMod_Asm);
			uiSaveAuxVarModAddr = JIPUtils::GetAddress(0x100162C3);

			// Load
			HookUtils::SafeWrite8(JIPUtils::GetAddress(0x100156EA) + 3, AUX_VAR_SAVE_VERSION); 
			// TODO
		}

	}
#endif

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

		// TESForm::RefToString
		HookUtils::SafeWrite8(JIPUtils::GetAddress(0x10057C1E) + 2, 0xFE);
		HookUtils::WriteRelJump(JIPUtils::GetAddress(0x10057C26), JIP_RefToString_Asm);
		uiRefToStringRet = JIPUtils::GetAddress(0x10057C32);

		// ModLogPrint
		// mov     edi, eax
		// test    edi, edi
		// jz      EXIT
		// jmp	   +3
		HookUtils::ReplaceCall(JIPUtils::GetAddress(0x1003CF00), GetOverridingMod);
		HookUtils::SafeWriteBuf(JIPUtils::GetAddress(0x1003CF05), "\x89\xC7\x85\xFF\x0F\x84\x3A\x01\x00\x00\xEB\x03");
		HookUtils::PatchMemoryNop(JIPUtils::GetAddress(0x1003CF53), 7);

		// GetModName
		HookUtils::SafeWrite8(JIPUtils::GetAddress(0x10043FAF) + 2, 0xFE);
		HookUtils::WriteRelJump(JIPUtils::GetAddress(0x10043FB7), JIP_GetModName_Asm);
		uiRefToStringRet = JIPUtils::GetAddress(0x10043FC3);

		// Auxvars
		//JIPAuxVars::InitHooks();
	}

}

namespace MorePluginTypes {

	bool JIP_GetModName(COMMAND_ARGS) {
		char cName[MAX_PATH] = {};
		uint32_t uiIndex = 0;
		BOOL bKeepExtension = false;
		const uint32_t uiMaxIndex = bSupportESLs ? 0xFE : 0xFF;
		if (ExtractArgsEx(EXTRACT_ARGS_EX, &uiIndex, &bKeepExtension) && uiIndex < uiMaxIndex) {
			TESFile* pFile = TESDataHandler::GetSingleton()->GetCompiledFile(uiIndex);
			const char* pName = "    ";
			if (pFile)
				pName = pFile->GetName();

			strcpy_s(cName, pName);
			if (cName[0] && !bKeepExtension) {
				char* pDot = strrchr(cName, '.');
				if (pDot)
					*pDot = 0;
			}
		}

		g_strInterface->Assign(PASS_COMMAND_ARGS, cName);
		return true;
	}

	bool JIP_IsFormOverridden(COMMAND_ARGS) {
		TESForm* pForm = nullptr;
		if (ExtractArgsEx(EXTRACT_ARGS_EX, &pForm) && pForm) {
			const FormID uiFormID = scriptObj->GetFormID();
			const uint8_t ucIndex = scriptObj->GetCompileIndex();

			TESFile* pFile = pForm->GetFile(-1);
			if (!pFile)
				return true;

			if (bSupportOverlays && pFile->IsOverlay()) {
				*result = 1;
				return true;
			}

			const uint8_t ucFileIndex = pFile->GetCompileIndex();
			if (ucFileIndex == 0xFF)
				return true;

			if (bSupportESLs && ucIndex == 0xFE && ucIndex == ucFileIndex) {
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
		*result = pSaveLoad->ucLoadOrderChanges;
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
			CommandInfo* pInfo = const_cast<CommandInfo*>(g_cmdTableInterface->GetByOpcode(CommandOpcodes::kGetModName));
			if (pInfo) {
				pInfo->execute = JIP_GetModName;
			}
		}
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