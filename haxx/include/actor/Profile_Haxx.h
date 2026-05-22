#pragma once

#include <actor/Profile.h>
#include <actor/ProfileInfo_Haxx.h>

class ProfileHaxx : public Profile
{
private:
    static sead::SafeArray<
        Profile*,
        ProfileInfo::cProfileID_MaxCustom
    >   sProfileListCustom;

    friend class Profile;
};
static_assert(sizeof(ProfileHaxx) == sizeof(Profile));
