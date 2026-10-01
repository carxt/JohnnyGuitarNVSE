#pragma once

#include "Bethesda/BSEnums.hpp"

class FalloutAudioMedia {
public:
	
    struct _MediaType {
    	enum Type {
            STANDBY             = 0,
            OBJECT              = 1,
            LOCATION            = 2,
            DUNGEON             = 3,
            BATTLE              = 4,
            LOCATION_BATTLE     = 5,
            SPECIAL             = 6,
            RADIO               = 7,
            MAIN_MENU           = 8,
            COUNT,
            NONE                = COUNT
    	};
    };
    using Type = _MediaType::Type;


	static void MediaOpen(Type aeMediaType, const char* apFileName, uint32_t auiFadeTime, bool abLoop, bool abForce, float afAttenuation, uint32_t auiSynchTime);

    static void MediaClose();
};