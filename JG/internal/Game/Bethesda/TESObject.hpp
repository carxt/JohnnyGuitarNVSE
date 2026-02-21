#pragma once

#include "TESForm.hpp"

class NiNode;
class NiAVObject;
class TESObjectREFR;
class TESBoundObject;
class TESWaterForm;
class TESObjectList;
class BipedAnim;

class TESObject : public TESForm {
public:
	TESObject();
	virtual ~TESObject();

	virtual NiAVObject*		Load3D();
	virtual bool			IsBoundAnimObject() const;
	virtual TESWaterForm*	GetWaterType() const;
	virtual bool			IsAutoCalc() const;
	virtual void			SetAutoCalc(bool abVal);
	virtual NiNode*			Clone3D(TESObjectREFR* apRequester, bool abDeepCopy);
	virtual void			UnClone3D(TESObjectREFR* apRequester);
	virtual bool			IsMarker() const;
	virtual bool			IsOcclusionMarker() const;
	virtual void			InitDefaultWorn();
	virtual bool			ReplaceModel();
	virtual bool			ReplaceModelBip(BipedAnim* apBiped);
	virtual void			Set3D(NiAVObject* apObject, bool abDebugPrint);
	virtual uint32_t		IncRef(); // GECK only
	virtual uint32_t		DecRef(); // GECK only
	virtual NiNode*			LoadGraphics(TESObjectREFR* apRef);

	TESObjectList*	pList;
	TESObject*		pPrev;
	TESObject*		pNext;

	TESObject* GetNext() const;
	TESObject* GetPrev() const;

	const char* GetModelFileName(const TESObjectREFR* apRef = nullptr) const;

	static uint32_t GetHealth(const TESObject* apObject);
};

ASSERT_SIZE(TESObject, 0x24)