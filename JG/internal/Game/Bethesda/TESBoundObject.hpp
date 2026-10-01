#pragma once

#include "TESObject.hpp"
#ifdef EDITOR
#include "Bethesda/TESCellUseList.hpp"
class TESContainer;
class ContainerItemExtra;
#endif

class NiNode;

#ifdef GAME
class TESBoundObject : public TESObject {
#else
class TESBoundObject : public TESObject, public TESCellUseList {
#endif
public:
	TESBoundObject();
	~TESBoundObject();

	virtual NiNode* Clone3DAlt(TESObjectREFR* apRequester);
	virtual bool	ReplaceModelAlt(const char* apPath);
#ifdef EDITOR
	virtual void	Unk_112(TESContainer* apContainer, int, ContainerItemExtra* apExtra);
	virtual void	Unk_113(int);
#endif

	struct Bounds {
		Bounds() : x(0), y(0), z(0) {};
		Bounds(int16_t aX, int16_t aY, int16_t aZ) : x(aX), y(aY), z(aZ) {};
		int16_t x = 0;
		int16_t y = 0;
		int16_t z = 0;

		Bounds operator-(const Bounds& aOther) const;

		float Length() const;
	};

	struct BoundData {
		Bounds kMin;
		Bounds kMax;
	};

	BoundData			kBoundData;
#ifdef EDITOR
	uint32_t			uiReferenceCount;
#endif

	float GetBoundSize() const;
};

#ifdef GAME
ASSERT_SIZE(TESBoundObject, 0x30)
#else
ASSERT_SIZE(TESBoundObject, 0x54)
#endif