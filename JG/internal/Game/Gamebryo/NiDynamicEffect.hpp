#pragma once

#include "NiAVObject.hpp"
#include "NiTPointerList.hpp"

#define JIP_LIGHTS USE_MODDED_CHANGES

class NiNode;

class NiDynamicEffect : public NiAVObject {
public:
	NiDynamicEffect();
	virtual ~NiDynamicEffect();

	struct _EffectType {
		enum Type {
			LIGHT_AMBIENT	= 0,
			LIGHT_POINT		= 2,
			LIGHT_DIR		= 3,
			LIGHT_SPOT		= 4,
			TEXTURE_EFFECT	= 5,
		};
	};
	using EffectType = _EffectType::Type;

	bool					m_bOn;
	uint8_t					m_ucEffectType;
#if JIP_LIGHTS
	bool					bResetTraits;
	Bitfield8				ucExtraFlags;
#endif
	int32_t					m_iIndex;
	uint32_t				m_uiPushCount;
	uint32_t				m_uiRevID;
	NiTPointerList<NiNode*>	m_kAffectedNodeList;
	NiTPointerList<NiNode*>	m_kUnaffectedNodeList;

	bool IsOn() const;

	EffectType GetEffectType() const;

	bool IsLight() const;

	bool IsAmbientLight() const;

	bool IsPointLight() const;

	bool IsDirectionalLight() const;

	bool IsSpotLight() const;

	bool IsTextureEffect() const;

	void IncRevisionID();
};

ASSERT_SIZE(NiDynamicEffect, 0xC4)