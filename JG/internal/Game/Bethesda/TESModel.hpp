#pragma once

#include "BaseFormComponent.hpp"
#include "TESTextureList.hpp"
#include "BSStringT.hpp"

class TESForm;
class TESModelTextureSwap;

class TESModel : public BaseFormComponent {
public:
	TESModel();
	virtual							~TESModel();
	virtual const char*				GetModel() const;
	virtual void					SetModel(const char* apPath);
	virtual TESModelTextureSwap*	GetAsModelMaterialSwap() const;

	struct ALIGN1 _Flags {
		enum Flags : uint8_t {
			HAS_FACEGEN			= 1u << 0,
			SKIN_TORSO			= 1u << 1,
			SKIN_RIGHT_HAND		= 1u << 2,
			SKIN_LEFT_HAND		= 1u << 3,

			SKIN_MASK			= SKIN_TORSO | SKIN_RIGHT_HAND | SKIN_LEFT_HAND
		};
	
		bool bHasFacegen	: 1;
		bool bSkinTorso		: 1;
		bool bSkinRightHand	: 1;
		bool bSkinLeftHand	: 1;
	};
	using Flags = _Flags::Flags;

	BSString			strModel;
	TESTextureList		kTextures;
	Bitfield<_Flags>	ucFlags;

	bool GetHasFacegenData() const;
	void SetHasFacegenData(bool abVal);

	uint32_t GetSkinFlags() const;

	static const char* GetModel(const TESForm* apForm);

	uint32_t GetModelLength() const;
	static uint32_t GetModelLength(const TESForm* apForm);
};

ASSERT_SIZE(TESModel, 0x18);