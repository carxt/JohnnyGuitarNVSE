#pragma once

#include "Gamebryo/NiColorA.hpp"
#include "Gamebryo/NiPoint3.hpp"
#include "Gamebryo/NiSmartPointer.hpp"

class BSMultiBoundShape;
class NiGeometry;
class NiLines;
class BSFadeNode;

class BGSPrimitive {
public:
	virtual ~BGSPrimitive();
	virtual void				Build();
	virtual void				SetColor(const NiColorA& arColor);
	virtual void				SetRadii(const NiPoint3& arRadii);
	virtual bool				IsInside(const NiPoint3& arPoint) const;
	virtual BSMultiBoundShape*  MakeMultiBoundShape(const NiPoint3& arAngle) const;

	struct _Type {
		enum Type : uint32_t {
			BOX		= 1,
			SPHERE	= 2,
			PLANE	= 3,
			LINE	= 4,
		};
	};
	using Type = _Type::Type;

	Type					eType;
	NiColorA				kColor;
	NiPoint3				kRadii;
	NiPointer<NiGeometry>	spGeometry;
	NiPointer<NiLines>		spFrame;
	NiPointer<BSFadeNode>	spNode;
	uint32_t				uiScaleHandlesEnabled;

	Type GetType() const;
};

ASSERT_SIZE(BGSPrimitive, 0x34);