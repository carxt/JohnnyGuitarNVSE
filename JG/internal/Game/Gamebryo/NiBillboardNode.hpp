#pragma once

#include "NiNode.hpp"

NiSmartPointer(NiBillboardNode);

class NiBillboardNode : public NiNode {
public:
	NiBillboardNode();
	virtual ~NiBillboardNode();

	struct _FaceMode {
		enum Mode {
			ALWAYS_FACE_CAMERA,
			ROTATE_ABOUT_UP,
			RIGID_FACE_CAMERA,
			ALWAYS_FACE_CENTER,
			RIGID_FACE_CENTER,
			BSROTATE_ABOUT_UP
		};
	};
	using FaceMode = _FaceMode::Mode;

	struct ALIGN2 _Flags {
		enum Flags {
			FACE_MODE_MASK		= 0x7,

			UPDATE_CONTROLLERS	= 1u << 3,
		};

		uint8_t	eFaceMode			: 3;
		bool	bUpdateControllers	: 1;
	};
	using Flags = _Flags::Flags;

	Bitfield<_Flags>	m_usFlags;
	float				m_fSavedTime;

	CREATE_OBJECT(NiBillboardNode, 0xA7E770);
	NIRTTI_ADDRESS(0x11F4AA0);

	FaceMode GetMode() const;
	void SetMode(FaceMode eMode);

	void RotateToCamera(NiCamera* apCamera);
};

ASSERT_SIZE(NiBillboardNode, 0xB4);