#pragma once

#include "NiProperty.hpp"

NiSmartPointer(NiStencilProperty);

class NiStencilProperty : public NiProperty {
public:
	NiStencilProperty();
	virtual ~NiStencilProperty();

	struct ALIGN2 _Flags {
		enum Flags {
			ENABLE				= 0x1,
			FAIL_ACTION			= 0xE,
			FAIL_ACTION_POS		= 0x1,
			ZFAIL_ACTION		= 0x70,
			ZFAIL_ACTION_POS	= 0x4,
			PASS_ACTION			= 0x380,
			PASS_ACTION_POS		= 0x7,
			DRAW_MODE			= 0xC00,
			DRAW_MODE_POS		= 0xA,
			TEST_FUNC			= 0xF000,
			TEST_FUNC_POS		= 0xC,
		};

		bool	bEnabled		: 1;
		uint8_t ucFailAction	: 3;
		uint8_t ucZFailAction	: 3;
		uint8_t					: 1; // Pass action is split due to padding issues
		uint8_t					: 2;
		uint8_t ucDrawMode		: 2;
		uint8_t ucTestFunc		: 4;
	};
	using Flags = _Flags::Flags;

	struct _TestFunc {
		enum Func {
			NEVER,
			LESS,
			EQUAL,
			LESSEQUAL,
			GREATER,
			NOTEQUAL,
			GREATEREQUAL,
			ALWAYS,
			COUNT
		};
	};
	using TestFunc = _TestFunc::Func;

	struct _Action {
		enum Action {
			KEEP,
			ZERO,
			REPLACE,
			INCREMENT,
			DECREMENT,
			INVERT,
			COUNT
		};
	};
	using Action = _Action::Action;

	struct _DrawMode {
		enum Mode {
			CCW_OR_BOTH,
			CCW,
			CW,
			BOTH,
			COUNT,
		};
	};
	using DrawMode = _DrawMode::Mode;

	Bitfield<_Flags>	m_usFlags;
	uint32_t			m_uiRef;
	uint32_t			m_uiMask;

	CREATE_OBJECT(NiStencilProperty, 0xA6F410);
	NIRTTI_ADDRESS(0x11F4A0C);

	bool GetStencilOn() const;
	void SetStencilOn(bool abEnabled);

	uint32_t GetStencilReference() const;
	void SetStencilReference(uint32_t auiRef);

	uint32_t GetStencilMask() const;
	void SetStencilMask(uint32_t auiMask);

	Action GetStencilFailAction() const;
	void SetStencilFailAction(Action aeAction);

	Action GetStencilZFailAction() const;
	void SetStencilZFailAction(Action aeAction);

	Action GetStencilPassAction() const;
	void SetStencilPassAction(Action aeAction);

	DrawMode GetDrawMode() const;
	void SetDrawMode(DrawMode aeDraw);

	TestFunc GetStencilFunction() const;
	void SetStencilFunction(TestFunc aeFunc);
};

ASSERT_SIZE(NiStencilProperty, 0x24);