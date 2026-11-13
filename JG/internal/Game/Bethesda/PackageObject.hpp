#pragma once

class TESForm;
class TESObjectREFR;

union PackageObject {
	TESForm*		pForm;
	TESObjectREFR*	pReference;
	uint32_t		uiObjectCode;
};