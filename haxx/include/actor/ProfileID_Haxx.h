#pragma once

#include <actor/ProfileID.h>

namespace ProfileID {

enum
{
    cActorSpawner = cProfileID_Max,
    cFlipBlock,
    cMagicPlatform,
    cEffectPlayer,

    _cNumAll
};

}

enum
{
    cProfileID_MaxAll       = ProfileID::_cNumAll,
    cProfileID_MaxCustom    = cProfileID_MaxAll - cProfileID_Max
};
