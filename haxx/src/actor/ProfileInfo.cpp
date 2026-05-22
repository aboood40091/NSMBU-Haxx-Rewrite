#include <actor/ActorBase.h>
#include <actor/Profile_Haxx.h>

u16 ProfileInfo::getExecutePriority(const ActorBase& actor)
{
    return getExecutePriority(actor.getProfileID());
}

u16 ProfileInfo::getExecutePriority(s32 id)
{
    if (static_cast<u32>(id) >= cProfileID_MaxAll)
        return 0xFFFF;

    return (static_cast<u32>(id) < cProfileID_Max)
        ? id
        : cExecutePriorityCustom[id - cProfileID_Max];
}

s16 ProfileInfo::getDrawPriority(s32 id)
{
    if (static_cast<u32>(id) >= cProfileID_MaxAll)
        return -1;

    return (static_cast<u32>(id) < cProfileID_Max)
        ? cDrawPriority[id]
        : cDrawPriorityCustom[id - cProfileID_Max];
}

ProfileInfo::ResType ProfileInfo::getResType(s32 id)
{
    if (static_cast<u32>(id) >= cProfileID_MaxAll)
        return cResType_Boot;

    return (static_cast<u32>(id) < cProfileID_Max)
        ? ResType(cResType[id])
        : ResType(cResTypeCustom[id - cProfileID_Max]);
}

u32 ProfileInfo::getResNum(s32 id)
{
    if (static_cast<u32>(id) >= cProfileID_MaxAll)
        return 0;

    return (static_cast<u32>(id) < cProfileID_Max)
        ? cResNum[id]
        : cResNumCustom[id - cProfileID_Max];
}

const sead::SafeString* ProfileInfo::getResList(s32 id)
{
    if (static_cast<u32>(id) >= cProfileID_MaxAll)
        return nullptr;

    return (static_cast<u32>(id) < cProfileID_Max)
        ? cResList[id]
        : cResListCustom[id - cProfileID_Max];
}

u32 ProfileInfo::getProfileNumAll()
{
    return cProfileID_MaxAll;
}

// -------------------------------------  ExecutePriority ------------------------------------- //

const u16 ProfileInfo::cExecutePriorityCustom[cProfileID_MaxCustom] = {
    ProfileInfo::cProfileID_ActorSpawner,   // ProfileInfo::cProfileID_ActorSpawner
    ProfileInfo::cProfileID_Block,          // ProfileInfo::cProfileID_FlipBlock
    ProfileInfo::cProfileID_PairObjChild,   // ProfileInfo::cProfileID_MagicPlatform
    ProfileInfo::cProfileID_EffectPlayer    // ProfileInfo::cProfileID_EffectPlayer
};

// --------------------------------------- DrawPriority --------------------------------------- //

const s16 ProfileInfo::cDrawPriorityCustom[cProfileID_MaxCustom] = {
    ProfileInfo::cDrawPriority_ActorSpawner,    // ProfileInfo::cProfileID_ActorSpawner
    ProfileInfo::cDrawPriority_FlipBlock,       // ProfileInfo::cProfileID_FlipBlock
    ProfileInfo::cDrawPriority_MagicPlatform,   // ProfileInfo::cProfileID_MagicPlatform
    ProfileInfo::cDrawPriority_EffectPlayer     // ProfileInfo::cProfileID_EffectPlayer
};

// -----------------------------------------  ResType ----------------------------------------- //

const s8 ProfileInfo::cResTypeCustom[cProfileID_MaxCustom] = {
    ProfileInfo::cResType_Course,   // ProfileInfo::cProfileID_ActorSpawner
    ProfileInfo::cResType_Course,   // ProfileInfo::cProfileID_FlipBlock
    ProfileInfo::cResType_Course,   // ProfileInfo::cProfileID_MagicPlatform
    ProfileInfo::cResType_Course    // ProfileInfo::cProfileID_EffectPlayer
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

const u8 ProfileInfo::cResNumCustom[cProfileID_MaxCustom] = {
    0,                              // ProfileInfo::cProfileID_ActorSpawner
    GetResNum(cRes_FlipBlock),      // ProfileInfo::cProfileID_FlipBlock
    0,                              // ProfileInfo::cProfileID_MagicPlatform
    GetResNum(cRes_EffectPlayer)    // ProfileInfo::cProfileID_EffectPlayer
};

// -----------------------------------------  ResList ----------------------------------------- //

const sead::SafeString* ProfileInfo::cResListCustom[cProfileID_MaxCustom] = {
    nullptr,            // ProfileInfo::cProfileID_ActorSpawner
    cRes_FlipBlock,     // ProfileInfo::cProfileID_FlipBlock
    nullptr,            // ProfileInfo::cProfileID_MagicPlatform
    cRes_EffectPlayer   // ProfileInfo::cProfileID_EffectPlayer
};

// ----------------------------------------- Replace ----------------------------------------- //

#define REPLACE_RES_LIST(PROFILE_NAME)                                          \
    static const ProfileInfo::ReplaceResList cReplaceResList_##PROFILE_NAME(    \
        ProfileInfo::cProfileID_##PROFILE_NAME,                                 \
        cRes_##PROFILE_NAME                                                     \
    );

REPLACE_RES_LIST(FloorHoleDokan)
