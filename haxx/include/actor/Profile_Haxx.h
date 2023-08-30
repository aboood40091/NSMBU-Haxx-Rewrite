#pragma once

#include <actor/Profile.h>
#include <actor/ProfileID_Haxx.h>

class ProfileHaxx : public Profile
{
public:
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

public:
    static u32 getProfileNumAll();

private:
    static sead::SafeArray<Profile*, cProfileID_MaxCustom>  sProfileCustom;

    static const s16                cDrawPriorityCustom[cProfileID_MaxCustom];
    static const s8                 cResTypeCustom[cProfileID_MaxCustom];
    static const u8                 cResNumCustom[cProfileID_MaxCustom];
    static const sead::SafeString*  cResListCustom[cProfileID_MaxCustom];

    friend class Profile;
};
static_assert(sizeof(ProfileHaxx) == sizeof(Profile));
