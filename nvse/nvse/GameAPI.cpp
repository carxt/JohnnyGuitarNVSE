#include "GameAPI.h"

#if RUNTIME
ScriptVar* ScriptLocals::GetVariable(uint32_t id) {
	if (m_vars) {
		ListNode<ScriptVar>* varIter = m_vars->Head();
		ScriptVar* scriptVar;
		do {
			scriptVar = varIter->data;
			if (scriptVar && (scriptVar->id == id))
				return scriptVar;
		} while (varIter = varIter->next);
	}
	return NULL;
}
#endif