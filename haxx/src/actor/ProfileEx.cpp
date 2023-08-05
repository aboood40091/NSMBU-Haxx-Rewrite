#include <actor/Profile.h>

s16 Profile::getDrawPriority(u32 id)
{
    if (id < cNum)
        return cDrawPriority[id];

    return ProfileHaxx::cDrawPriorityCustom[id - cNum];
}

Profile::ResLoadAt Profile::getResLoadAt(u32 id)
{
    if (id < cNum)
        return ResLoadAt(cResLoadAt[id]);

    return ResLoadAt(ProfileHaxx::cResLoadAtCustom[id - cNum]);
}

u8 Profile::getResNum(u32 id)
{
    if (id < cNum)
        return cResNum[id];

    return ProfileHaxx::cResNumCustom[id - cNum];
}

const sead::SafeString* Profile::getResList(u32 id)
{
    if (id < cNum)
        return cResList[id];

    return ProfileHaxx::cResListCustom[id - cNum];
}

u32 ProfileHaxx::getProfileNumAll()
{
    return cNumAll;
}

// --------------------------------------- DrawPriority --------------------------------------- //

const s16 ProfileHaxx::cDrawPriorityCustom[] = {
    0,  // ProfileID::cActorSpawner
    0,  // ProfileID::cFlipBlock
    0,  // ProfileID::cMagicPlatform
    0   // ProfileID::cEffectPlayer
};

// ----------------------------------------  ResLoadAt ---------------------------------------- //

const u8 ProfileHaxx::cResLoadAtCustom[] = {
    Profile::cResLoadAt_Course, // ProfileID::cActorSpawner
    Profile::cResLoadAt_Course, // ProfileID::cFlipBlock
    Profile::cResLoadAt_Course, // ProfileID::cMagicPlatform
    Profile::cResLoadAt_Course  // ProfileID::cEffectPlayer
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

template <s32 N>
inline s32 GetResNum(const sead::SafeString (&)[N])
{
    return N;
}

const u8 ProfileHaxx::cResNumCustom[] = {
    0,                              // ProfileID::cActorSpawner
    GetResNum(cRes_FlipBlock),      // ProfileID::cFlipBlock
    0,                              // ProfileID::cMagicPlatform
    GetResNum(cRes_EffectPlayer)    // ProfileID::cEffectPlayer
};

// -----------------------------------------  ResList ----------------------------------------- //

const sead::SafeString* ProfileHaxx::cResListCustom[] = {
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
