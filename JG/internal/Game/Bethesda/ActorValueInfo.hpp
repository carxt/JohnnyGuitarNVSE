#pragma once

#include "TESFullName.hpp"
#include "TESDescription.hpp"
#include "TESForm.hpp"
#include "TESIcon.hpp"
#include "ActorValue.hpp"

class ActorValueOwner;

class ActorValueInfo : public TESFormBase, public TESFullName, public TESDescription, public TESIcon {
public:
	ActorValueInfo();
	~ActorValueInfo();

	const char*					pInfoName;
	BSString					strAbbreviation;
	Bitfield32					uiAVFlags;
	ActorValue::Section			eType;
	float(__cdecl*				pDerivationFunction)(ActorValueOwner*, ActorValue::Index);
	ActorValue::Index(__cdecl*	pMappingFunction)(ActorValueOwner*, ActorValue::Index);
	void(__cdecl*				pModifiedCallback)(ActorValueOwner*, int32_t, float, float, ActorValueOwner*);
	uint32_t					uiNumDependentActorValues;
	ActorValue::Index			kDependentActorValues[15];
	uint32_t					uiEnumCount;
	const char*					pEnumNames[10];

	TESFORM_TYPE(ActorValueInfo);
};

#ifdef GAME
ASSERT_SIZE(ActorValueInfo, 0xC4);
#else
ASSERT_SIZE(ActorValueInfo, 0xF0);
#endif