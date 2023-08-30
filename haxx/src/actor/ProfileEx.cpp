#include <actor/Profile_Haxx.h>

s16 Profile::getDrawPriority(s32 id)
{
    if (static_cast<u32>(id) >= cProfileID_MaxAll)
        return -1;

    return (id < cProfileID_Max)
        ? cDrawPriority[id]
        : ProfileHaxx::cDrawPriorityCustom[id - cProfileID_Max];
}

Profile::ResType Profile::getResType(s32 id)
{
    if (static_cast<u32>(id) >= cProfileID_MaxAll)
        return cResType_Boot;

    return (id < cProfileID_Max)
        ? ResType(cResType[id])
        : ResType(ProfileHaxx::cResTypeCustom[id - cProfileID_Max]);
}

u32 Profile::getResNum(s32 id)
{
    if (static_cast<u32>(id) >= cProfileID_MaxAll)
        return 0;

    return (id < cProfileID_Max)
        ? cResNum[id]
        : ProfileHaxx::cResNumCustom[id - cProfileID_Max];
}

const sead::SafeString* Profile::getResList(s32 id)
{
    if (static_cast<u32>(id) >= cProfileID_MaxAll)
        return nullptr;

    return (id < cProfileID_Max)
        ? cResList[id]
        : ProfileHaxx::cResListCustom[id - cProfileID_Max];
}

u32 ProfileHaxx::getProfileNumAll()
{
    return cProfileID_MaxAll;
}

// --------------------------------------- DrawPriority --------------------------------------- //

const s16 ProfileHaxx::cDrawPriorityCustom[cProfileID_MaxCustom] = {
    118 - 0x3ff,    // ProfileID::cActorSpawner
    796,            // ProfileID::cFlipBlock
    797,            // ProfileID::cMagicPlatform
    798             // ProfileID::cEffectPlayer
};

// -----------------------------------------  ResType ----------------------------------------- //

const s8 ProfileHaxx::cResTypeCustom[cProfileID_MaxCustom] = {
    Profile::cResType_Course,   // ProfileID::cActorSpawner
    Profile::cResType_Course,   // ProfileID::cFlipBlock
    Profile::cResType_Course,   // ProfileID::cMagicPlatform
    Profile::cResType_Course    // ProfileID::cEffectPlayer
};

// -------------------------------------------  Res ------------------------------------------- //

static const sead::SafeString cRes_FloorHoleDokan[]  = {
    "circle_ground_holeD",
    "circle_ground_holeD_chika",
    "obj_dokan"
};

static const sead::SafeString cRes_FlipBlock[]  = {
    "block_snake"
};

static const sead::SafeString cRes_EffectPlayer[]  = {
    "block_snake"
};

// ------------------------------------------ ResNum ------------------------------------------ //

template <typename T, size_t N>
u8 (&_ResNumGetter(T(&)[N]))[N];
#define GetResNum(array) (sizeof(_ResNumGetter(array)))

const u8 ProfileHaxx::cResNumCustom[cProfileID_MaxCustom] = {
    0,                              // ProfileID::cActorSpawner
    GetResNum(cRes_FlipBlock),      // ProfileID::cFlipBlock
    0,                              // ProfileID::cMagicPlatform
    GetResNum(cRes_EffectPlayer)    // ProfileID::cEffectPlayer
};

// -----------------------------------------  ResList ----------------------------------------- //

const sead::SafeString* ProfileHaxx::cResListCustom[cProfileID_MaxCustom] = {
    nullptr,            // ProfileID::cActorSpawner
    cRes_FlipBlock,     // ProfileID::cFlipBlock
    nullptr,            // ProfileID::cMagicPlatform
    cRes_EffectPlayer   // ProfileID::cEffectPlayer
};

// ----------------------------------------- Replace ----------------------------------------- //

#define REPLACE_RES_LIST(PROFILE_NAME)                                          \
    static const ProfileHaxx::ReplaceResList cReplaceResList_##PROFILE_NAME(    \
        ProfileID::c##PROFILE_NAME,                                             \
        cRes_##PROFILE_NAME                                                     \
    );

REPLACE_RES_LIST(FloorHoleDokan)
