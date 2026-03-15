#pragma once

#include "BaseFormComponent.hpp"
#include "TESTextureList.hpp"
#include "BSStringT.hpp"

class TESFile;
class TESModelTextureSwap;

class TESModel : public BaseFormComponent {
public:
	TESModel();
	virtual							~TESModel();
	virtual const char*				GetModel() const;
	virtual void					SetModel(const char* apPath);
	virtual TESModelTextureSwap*	GetAsModelMaterialSwap() const;

	struct ALIGN1 _FacegenFlags {
		enum Flags : uint8_t {
			HEAD			= 1u << 0,
			TORSO			= 1u << 1,
			RIGHT_HAND		= 1u << 2,
			LEFT_HAND		= 1u << 3,
		};
	
		bool bHead		: 1;
		bool bTorso		: 1;
		bool bRightHand : 1;
		bool bLeftHand	: 1;
	};
	using FacegenFlags = _FacegenFlags::Flags;

	BSString				strModel;
	TESTextureList			kTextures;
	Bitfield<_FacegenFlags>	ucFaceGenFlags;
};

ASSERT_SIZE(TESModel, 0x18);