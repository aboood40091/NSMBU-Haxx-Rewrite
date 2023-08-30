#include <actor/ActorBase.h>
#include <actor/Profile_Haxx.h>

sead::SafeArray<Profile*, cProfileID_MaxCustom> ProfileHaxx::sProfileCustom;

Profile::Profile(ActorFactory factory, s32 id, const sead::SafeString& name, const ActorCreateInfo* p_create_info, u32 flag)
    : mFactory(factory)
    , mID(id)
    , mpActorCreateInfo(p_create_info != nullptr ? p_create_info : &ActorCreateInfo::cDefault)
    , mIsResLoaded(false)
    , mFlag(flag)
{
    if (id < cProfileID_Max)
        sProfile[id] = this;

    else
        ProfileHaxx::sProfileCustom[id - cProfileID_Max] = this;
}


Profile* Profile::get(s32 id)
{
    if (id < cProfileID_Max)
        return sProfile[id];

    return ProfileHaxx::sProfileCustom[id - cProfileID_Max];
}
