#include "JohnnyRadios.hpp"
#include <unordered_set>
#include <GameForms.h>

namespace JohnnyRadios {
	static ULONGLONG timer = GetTickCount64();
	std::unordered_set<DWORD> availableRadios;

	void Reset() {
		availableRadios.clear();
	}

	void Update() {
		if (((GetTickCount64() - timer) > 1000) || availableRadios.empty()) {
			timer = GetTickCount64();
			availableRadios.clear();
			availableRadios.insert(0);
			tList<TESObjectACTI>* discoveredRadios = CdeclCall<tList<TESObjectACTI>*>(0x79C080);
			for (auto radioIter = discoveredRadios->Begin(); !radioIter.End(); radioIter.Next()) {
				if (*radioIter) {
					availableRadios.insert((*radioIter)->GetFormID());
				}
			}
		}

	}
	bool IsAvailable(uint32_t formID)
	{
		return availableRadios.count(formID) > 0;
	}
}