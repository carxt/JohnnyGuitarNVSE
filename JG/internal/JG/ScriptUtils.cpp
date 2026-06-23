#include "ScriptUtils.hpp"
#include "GameObjects.h"

namespace ScriptUtils {

	NiAVObject* __fastcall GetReferenceScene(TESObjectREFR* apRef, bool abFirstPerson) {
		if (apRef == PlayerCharacter::GetSingleton())
			return static_cast<PlayerCharacter*>(apRef)->Get3D(abFirstPerson);
		else
			return apRef->Get3D();
	}

}