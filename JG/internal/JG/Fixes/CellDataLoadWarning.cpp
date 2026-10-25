#include "CellDataLoadWarning.hpp"
#include "Bethesda/TESObjectCELL.hpp"
#include "Bethesda/TESMain.hpp"

#include "Shared/SafeWrite/SafeWrite.hpp"

class Controls;

namespace CellDataLoadWarning {

	// """Fix""" lmao
	// Slightly above karut tier
	// At least makes debugging straightforward

	bool __fastcall PrintCellErrorMsg(const TESObjectCELL* apCell, const TESFile* apFile) {
		const char* pType = apCell->GetInterior() ? "interior" : "exterior";
		char cMessage[1024];
		our_snprintf(cMessage, sizeof(cMessage), 
					 "Failed to load %s cell %08X (\"%s\") from plugin \"%s\"\n\n"
					 "The plugin was probably saved incorrectly\n\n"
					 "Try resaving it in xEdit or GECK with latest Extender\n\n"
					 "Do you want to close the game ?\n"
					 "(Clicking \"No\" will continue loading, and may crash or lead to instabilities or mising data)", 
					 pType, apCell->GetFormID(), apCell->GetFormEditorID(), apFile->GetName());

		ShowCursor(TRUE);
		const int32_t iResult = MessageBox(nullptr, cMessage, "Cell Loading Error!", MB_YESNO | MB_ICONERROR | MB_SYSTEMMODAL | MB_SETFOREGROUND);
		ShowCursor(FALSE);

		if (iResult == IDYES)
			DebugBreak();

		return true;
	}

	template<uint32_t uiAddress>
	class Hook {
		static inline HookUtils::CallDetour kDetour;

		bool LoadTempDataFromFile(TESFile* apFile) {
			const bool bResult = ThisCall<bool>(kDetour, this, apFile);
			if (!bResult)
				return PrintCellErrorMsg(reinterpret_cast<TESObjectCELL*>(this), apFile);
			return bResult;
		}

	public:
		Hook() {
			kDetour.ReplaceCall(uiAddress, &Hook::LoadTempDataFromFile);
		}
	};

	void Install() {
		Hook<0x550438>();
		Hook<0x585D26>();
	}

}