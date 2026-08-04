#pragma once

#include "NiInterpolator.hpp"
#include "NiAnimationKey.hpp"

class NiKeyBasedInterpolator : public NiInterpolator {
public:
	NiKeyBasedInterpolator();
	virtual ~NiKeyBasedInterpolator();

    virtual uint16_t                    GetKeyChannelCount() const;
    virtual uint32_t                    GetKeyCount(uint16_t ausChannel) const;
    virtual NiAnimationKey::KeyType     GetKeyType(uint16_t ausChannel) const;
    virtual NiAnimationKey::KeyContent  GetKeyContent(uint16_t ausChannel) const;
    virtual NiAnimationKey*             GetKeyArray(uint16_t ausChannel) const;
    virtual uint8_t                     GetKeyStride(uint16_t ausChannel) const;
    virtual bool                        GetChannelPosed(uint16_t ausChannel) const;

	NIRTTI_ADDRESS(0x11F3740);
};