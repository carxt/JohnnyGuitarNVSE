#pragma once

#include "NiObject.hpp"

class NiPoint3;
class NiColorA;
class NiQuatTransform;
class NiQuaternion;
class NiBoolInterpolator;
class NiObjectNET;

NiSmartPointer(NiInterpolator);

class NiInterpolator : public NiObject {
public:
	NiInterpolator();
	virtual ~NiInterpolator();

	virtual bool				UpdateTransform(float afTime, NiObjectNET* apTarget, NiQuatTransform& arValue);
	virtual bool				UpdateColorA(float afTime, NiObjectNET* apTarget, NiColorA& arValue);
	virtual bool				UpdatePoint3(float afTime, NiObjectNET* apTarget, NiPoint3& arValue);
	virtual bool				UpdateQuaternion(float afTime, NiObjectNET* apTarget, NiQuaternion& arValue);
	virtual bool				UpdateFloat(float afTime, NiObjectNET* apTarget, float& arValue);
	virtual bool				UpdateBool(float afTime, NiObjectNET* apTarget, bool& arValue);
	virtual bool				IsBoolValueSupported() const;
	virtual bool				IsFloatValueSupported() const;
	virtual bool				IsQuaternionValueSupported() const;
	virtual bool				IsPoint3ValueSupported() const;
	virtual bool				IsColorAValueSupported() const;
	virtual bool				IsTransformValueSupported() const;
	virtual void				Collapse();
	virtual void				GetActiveTimeRange(float& arBeginKeyTime, float& arEndKeyTime) const;
	virtual void				GuaranteeTimeRange(float afStartTime, float afEndTime);
	virtual NiInterpolator*		GetSequenceInterpolator(float afStartTime, float afEndTime);
	virtual bool				ResolveDependencies();
	virtual bool				SetUpDependencies();
	virtual bool				AlwaysUpdate() const;
	virtual NiBoolInterpolator* IsNiBoolInterpolator() const;

	float m_fLastTime;

	NIRTTI_ADDRESS(0x11F4200);

	void ForceNextUpdate();
};

ASSERT_SIZE(NiInterpolator, 0xC);