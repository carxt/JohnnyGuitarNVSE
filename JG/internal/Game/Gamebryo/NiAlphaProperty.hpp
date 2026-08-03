#pragma once

#include "NiProperty.hpp"

NiSmartPointer(NiAlphaProperty);

class NiAlphaProperty : public NiProperty {
public:
	NiAlphaProperty();
	virtual ~NiAlphaProperty();

	struct ALIGN2 _Flags {
		enum Flags {
			ALPHA_BLEND			= 0x0001,
			SRC_BLEND			= 0x001E,
			SRC_BLEND_POS		= 1,
			DEST_BLEND			= 0x01E0,
			DEST_BLEND_POS		= 5,

			TEST_ENABLE			= 0x0200,
			TEST_FUNC			= 0x1C00,
			TEST_FUNC_POS		= 10,
			ALPHA_NOSORTER		= 0x2000
		};

		bool	bAlphaBlending	: 1;
		uint8_t ucSrcBlend		: 4;
		uint8_t					: 3; // Dest blend is split due to padding issues
		uint8_t					: 1; 
		bool	bAlphaTesting	: 1;
		uint8_t ucTestFunc		: 3;
		bool	bNoSorter		: 1;
	};
	using Flags = _Flags::Flags;

	struct _AlphaFunc {
		enum Func {
			ONE,
			ZERO,
			SRC_COLOR,
			INV_SRC_COLOR,
			DEST_COLOR,
			INV_DEST_COLOR,
			SRC_ALPHA,
			INV_SRC_ALPHA,
			DEST_ALPHA,
			INV_DEST_ALPHA,
			SRC_ALPHA_SAT,
			COUNT
		};
	};
	using AlphaFunc = _AlphaFunc::Func;

	struct _TestFunc {
		enum Func {
			ALWAYS,
			LESS,
			EQUAL,
			LESS_EQUAL,
			GREATER,
			NOT_EQUAL,
			GREATER_EQUAL,
			NEVER,
			COUNT
		};
	};
	using TestFunc = _TestFunc::Func;

	Bitfield<_Flags>	m_usFlags;
	uint8_t				m_ucAlphaTestRef;

	CREATE_OBJECT(NiAlphaProperty, 0xA5CEB0);
	NIRTTI_ADDRESS(0x11F4408);

	bool GetAlphaBlending() const;
	void SetAlphaBlending(bool abBlend);

	bool GetAlphaTesting() const;
	void SetAlphaTesting(bool abTest);

	uint8_t GetTestRef() const;
	void SetTestRef(uint8_t aucRef);

	AlphaFunc GetSrcBlendMode() const;
	void SetSrcBlendMode(AlphaFunc aeSrcBlend);

	AlphaFunc GetDestBlendMode() const;
	void SetDestBlendMode(AlphaFunc aeDestBlend);

	TestFunc GetTestMode() const;
	void SetTestMode(TestFunc aeTestFunc);

	static AlphaFunc GetNiAlphaFunctionFromD3D(D3DBLEND aeBlend);
};

ASSERT_SIZE(NiAlphaProperty, 0x1C);