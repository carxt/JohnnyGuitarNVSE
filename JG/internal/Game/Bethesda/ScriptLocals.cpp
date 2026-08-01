#include "ScriptLocals.hpp"
#include "Script.hpp"

SCRIPT_LOCAL* ScriptLocals::GetVariable(uint32_t auiIndex) const {
	auto pIter = pVariables;
	while (pIter && !pIter->IsEmpty()) {
		SCRIPT_LOCAL* pLocal = pIter->GetItem();
		if (pLocal && pLocal->uiVarID == auiIndex)
			return pLocal;

		pIter = pIter->GetNext();
	}
	return nullptr;
}
