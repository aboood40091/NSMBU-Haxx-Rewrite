#pragma once

#ifndef PROFILE_INFO_AS_NAMESPACE
    #error "Must define PROFILE_INFO_AS_NAMESPACE"
#endif

#include <actor/ProfileInfo.h>

class ActorBase;

namespace ProfileInfo {

enum
{
    cProfileID_ActorSpawner = cProfileID_Max,
    cProfileID_FlipBlock,
    cProfileID_MagicPlatform,
    cProfileID_EffectPlayer,

    cProfileID_MaxAll,
    cProfileID_MaxCustom    = cProfileID_MaxAll - cProfileID_Max
};

struct ReplaceDrawPriority
{
    ReplaceDrawPriority(const u32 id, const s16 priority)
    {
        if (id < cProfileID_Max)
            const_cast<s16*>(cDrawPriority)[id] = priority;
    }
};

struct ReplaceResType
{
    ReplaceResType(const u32 id, const s8 res_type)
    {
        if (id < cProfileID_Max)
            const_cast<s8*>(cResType)[id] = res_type;
    }
};

struct ReplaceResList
{
    explicit ReplaceResList(const u32 id)
    {
        if (id < cProfileID_Max)
        {
            const_cast<u8*>(cResNum)[id] = 0;
            cResList[id] = nullptr;
        }
    }

    template <s32 N>
    ReplaceResList(const u32 id, const sead::SafeString (&res_list)[N])
    {
        if (id < cProfileID_Max)
        {
            const_cast<u8*>(cResNum)[id] = N;
            cResList[id] = res_list;
        }
    }
};

u16 getExecutePriority(const ActorBase& actor);
u16 getExecutePriority(s32 id);
u32 getProfileNumAll();

enum
{
    cDrawPriority_FlipBlock         = 796,
    cDrawPriority_MagicPlatform     = 797,
    cDrawPriority_EffectPlayer      = 798,

    // No Draw
    cDrawPriority_ActorSpawner      = 118 - 0x3ff
};

extern const u16                cExecutePriorityCustom[cProfileID_MaxCustom];
extern const s16                cDrawPriorityCustom[cProfileID_MaxCustom];
extern const s8                 cResTypeCustom[cProfileID_MaxCustom];
extern const u8                 cResNumCustom[cProfileID_MaxCustom];
extern const sead::SafeString*  cResListCustom[cProfileID_MaxCustom];

}
