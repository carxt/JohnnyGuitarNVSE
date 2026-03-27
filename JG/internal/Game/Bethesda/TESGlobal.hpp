#pragma once

#include "TESForm.hpp"

class TESGlobal : public TESForm {
public:
	TESGlobal();
	~TESGlobal();

	enum DataType {
		DATA_SHORT	= 's',
		DATA_LONG	= 'l',
		DATA_FLOAT	= 'f'
	};

	BSString	strEditorID;
	uint8_t		ucType;
	union {
		int32_t		iValue;
		uint32_t	uiValue;
		int16_t		sValue;
		uint16_t	usValue;
		float		fValue;
	};

	TESFORM_TYPE(TESGlobal);

	uint8_t GetType() const;

	float GetValue() const;
	void SetValue(float afValue);
};

ASSERT_SIZE(TESGlobal, 0x28);