#include "AddonNodeMap.hpp"
#include "Bethesda/TESDataHandler.hpp"
#include "Bethesda/BGSAddonNode.hpp"

#include <shared/SafeWrite/SafeWrite.hpp>

namespace AddonNodeMap {

	// TLDR:
	// Bethesda uses an array to store addon nodes
	// While normally I'd applaud them using an array instead of a linked list...
	// unfortunately addon node indices are... well, literal indices
	// Thus, if someone creates an addon node with a big index...
	// It resizes the whole goddamn array to that value, which is slow af, but most importantly, memory hungry
	// Especially as modders have no idea about this, and are free to choose any index as they want 
	// (and due to not wanting to conflict with each other, they often choose high values)
	// Amazing
	// Beth fixed it in FO4

	STACK_FRAME_OPT_ENABLE

#ifdef GAME
	constexpr inline uint32_t uiAddrGetAt = 0x853130;
	constexpr inline uint32_t uiAddrSetAt = 0x844700;
	constexpr inline uint32_t uiAddrGetFirst = 0x4B9BA0;
	constexpr inline uint32_t uiAddrGetNext = 0x6B7F20;
#else
	constexpr inline uint32_t uiAddrGetAt = 0x922810;
	constexpr inline uint32_t uiAddrSetAt = 0x6DFC30;
	constexpr inline uint32_t uiAddrGetFirst = 0x626240;
	constexpr inline uint32_t uiAddrGetNext = 0x46A5A0;
#endif

	using AddonMap = NiTPointerMap<uint32_t, BGSAddonNode*>;

	int32_t __fastcall ShowConflictMessage(BGSAddonNode* apNode, BGSAddonNode* apFoundNode) {
		char cMessage[1024];
		const TESFile* pFile = apNode->GetFile(0);
		const TESFile* pFoundFile = apFoundNode->GetFile(0);
		const char* pFileName = pFile ? pFile->GetName() : "Unknown";
		const char* pFoundFileName = pFoundFile ? pFoundFile->GetName() : "Unknown";
		our_snprintf(cMessage, sizeof(cMessage),
			"Addon Node %08X (\"%s\") from \"%s\" is trying to use index %i, but Addon Node %08X (\"%s\") from \"%s\" already uses that index.",
			apNode->GetFormID(), apNode->GetFormEditorID(), pFileName, apNode->GetIndex(),
			apFoundNode->GetFormID(), apFoundNode->GetFormEditorID(), pFoundFileName);
		return MessageBox(nullptr, cMessage, "Addon Node Conflict!", MB_OK | MB_ICONERROR);
	}

	class TESDataHandlerEx : public TESDataHandler {
	public:
		BGSAddonNode* GetAddonNode(uint32_t auiIndex) const {
			BGSAddonNode* pNode = nullptr;
			ThisCall<bool>(uiAddrGetAt, &kAddons, auiIndex, &pNode);
			return pNode;
		}
		uint32_t GetAddonNodeCount() const {
			return kAddons.GetCount();
		}

		void AddAddonNode(BGSAddonNode* apNode) {
			if (!apNode)
				return;

			const uint32_t uiNodeIndex = apNode->GetIndex();
			BGSAddonNode* pFoundNode = GetAddonNode(uiNodeIndex);
			if (pFoundNode) [[unlikely]] {
				if (pFoundNode != apNode)
					ShowConflictMessage(apNode, pFoundNode);
			}
			else [[likely]] {
				ThisCall(uiAddrSetAt, &kAddons, uiNodeIndex, apNode);
			}
		}
	};

	class AddonMapIterator : public TESDataHandler {
	public:
		NiTMapIterator Start() {
			return ThisCall<NiTMapIterator>(uiAddrGetFirst, &kAddons);
		}

		BGSAddonNode* GetNext(NiTMapIterator& arIter) const {
			uint32_t uiIndex;
			BGSAddonNode* pNode = nullptr;
			ThisCall(uiAddrGetNext, &kAddons, &arIter, &uiIndex, &pNode);
			return pNode;
		}
	};

#ifdef GAME
	static void __fastcall InitAddonNodeMap(NiTPointerMap<uint32_t, BGSAddonNode*>* apMap, void*, uint16_t, uint16_t) {
		ThisCall(0x486930, apMap, 37); // NiTPointerMap<unsigned int,TESForm *>
	}
#else
	static SPEC_NAKED void InitAddonNodeMap_asm() {
		static constexpr uint32_t uiReturnAddr = 0x4DB458;
		__asm {
			push	37
			lea		ecx, [esi + 0x1EC]
			mov		eax, 0x4FB750
			call	eax
			xor		ecx, ecx
			xor		eax, eax
			xor		edx, edx
			jmp		uiReturnAddr
		}
	}
#endif

	void Install() {
#ifdef GAME
		HookUtils::ReplaceCall(0x45D6A5, InitAddonNodeMap);

		// TESDataHandler::ClearData
		HookUtils::ReplaceCall(0x45F1AB, 0x438AF0); // RemoveAll

		HookUtils::WriteRelJump(0x461820, &TESDataHandlerEx::AddAddonNode);
		HookUtils::ReplaceCall(0x461951, 0x405430); // RemoveAt (TESDataHandler::RemoveAddonNode)
		HookUtils::WriteRelJump(0x4617E0, &TESDataHandlerEx::GetAddonNode);

		// TES::PreloadAddonNodes
		// cmp     dword ptr [ebp-0x14], 0 ; Compare iter
		// jz      0x45A0F4 (Exit)
		// lea     ecx, [ebp-0x14] ; Load iter
		HookUtils::SafeWriteBuf(0x459FD5, "\x83\x7D\xEC\x00\x0F\x84\x15\x01\x00\x00\x8D\x4D\xEC\x90\x90");
		HookUtils::ReplaceCall(0x459FBB, &AddonMapIterator::Start);
		HookUtils::ReplaceCall(0x459FEB, &AddonMapIterator::GetNext);

		// BGSSceneInfo::CollectSceneDataFromAddonNodes
		// Disable because cba atm
		HookUtils::WriteRelJump(0x4A80D3, 0x4A821C);
#else
		HookUtils::WriteRelJump(0x4DB42C, InitAddonNodeMap_asm);

		HookUtils::WriteRelJump(0x4D8AA0, &TESDataHandlerEx::AddAddonNode);
		HookUtils::WriteRelJump(0x4CF0C8, 0xC30410); // RemoveAt (TESDataHandler::RemoveAddonNode)
		HookUtils::WriteRelJump(0x4CF090, &TESDataHandlerEx::GetAddonNode);

		// BGSSceneInfo::CollectSceneDataFromAddonNodes
		// Disable because cba atm
		HookUtils::WriteRelJump(0x51DB24, 0x51DC55);
#endif
	}

	STACK_FRAME_OPT_RESET

}