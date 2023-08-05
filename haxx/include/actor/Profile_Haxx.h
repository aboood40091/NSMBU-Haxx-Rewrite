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
            if (id < cNum)
                const_cast<s16*>(cDrawPriority)[id] = priority;
        }
    };

    struct ReplaceResLoadAt
    {
        ReplaceResLoadAt(const u32 id, const u8 res_load_at)
        {
            if (id < cNum)
                const_cast<u8*>(cResLoadAt)[id] = res_load_at;
        }
    };

    struct ReplaceResList
    {
        template <s32 N>
        ReplaceResList(const u32 id, const sead::SafeString (&res_list)[N])
        {
            if (id < cNum)
            {
                const_cast<u8*>(cResNum)[id] = N;
                cResList[id] = res_list;
            }
        }
    };

public:
    static const u32 cNumAll = ProfileID::cNumAll;
    static const u32 cNumCustom = cNumAll - cNum;

public:
    static u32 getProfileNumAll();

private:
    static sead::SafeArray<Profile*, cNumCustom>    sProfileCustom;

    static const s16                cDrawPriorityCustom[cNumCustom];
    static const u8                 cResLoadAtCustom[cNumCustom];
    static const u8                 cResNumCustom[cNumCustom];
    static const sead::SafeString*  cResListCustom[cNumCustom];

    friend class Profile;
};
static_assert(sizeof(ProfileHaxx) == sizeof(Profile));
