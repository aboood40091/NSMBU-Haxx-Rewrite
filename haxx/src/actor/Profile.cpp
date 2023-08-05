#include <actor/ActorBase.h>
#include <actor/Profile_Haxx.h>

sead::SafeArray<Profile*, ProfileHaxx::cNumCustom> ProfileHaxx::sProfileCustom;

Profile::Profile(ClassInit p_class_init, u32 id, const sead::SafeString& name, const ActorCreateInfo* p_create_info, u32 flag)
    : mpClassInit(p_class_init)
    , mID(id)
    , mpActorCreateInfo(p_create_info != nullptr ? p_create_info : &ActorCreateInfo::cDefault)
    , mIsResLoaded(false)
    , mFlag(flag)
{
    if (id < cNum)
        sProfile[id] = this;

    else
        ProfileHaxx::sProfileCustom[id - cNum] = this;
}


Profile* Profile::get(u32 id)
{
    if (id < cNum)
        return sProfile[id];

    return ProfileHaxx::sProfileCustom[id - cNum];
}
