#include <actor/ActorBase.h>
#include <actor/Profile_Haxx.h>

sead::SafeArray<Profile*, ProfileInfo::cProfileID_MaxCustom> ProfileHaxx::sProfileListCustom;

Profile::Profile(ActorFactory factory, s32 id, const sead::SafeString& name, const ActorCreateInfo* p_create_info, Flag flag)
    : mFactory(factory)
    , mID(id)
    , mpActorCreateInfo(p_create_info != nullptr ? p_create_info : &ActorCreateInfo::cDefault)
    , mIsResLoaded(false)
    , mFlag(flag)
{
    if (static_cast<u32>(id) < ProfileInfo::cProfileID_Max)
        sProfileList[id] = this;

    else if (static_cast<u32>(id) < ProfileInfo::cProfileID_MaxAll)
        ProfileHaxx::sProfileListCustom[id - ProfileInfo::cProfileID_Max] = this;
}

Profile* Profile::get(s32 id)
{
    if (static_cast<u32>(id) >= ProfileInfo::cProfileID_MaxAll)
        return nullptr;

    return (static_cast<u32>(id) < ProfileInfo::cProfileID_Max)
        ? sProfileList[id]
        : ProfileHaxx::sProfileListCustom[id - ProfileInfo::cProfileID_Max];
}
