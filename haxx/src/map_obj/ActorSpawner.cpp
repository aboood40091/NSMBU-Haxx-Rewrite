#include <actor/Actor.h>
#include <actor/ActorMgr.h>
#include <actor/MapActor_Haxx.h>
#include <actor/Profile_Haxx.h>
#include <map/PSwitchMgr.h>

class ActorSpawner : public Actor
{
public:
    ActorSpawner(const ActorCreateParam& param)
        : Actor(param)
    {
    }

private:
    s32 create_() override;
    s32 execute_() override;

private:
    u16     mSpawnProfileID;
    bool    mSpawned;
};

static const Profile ActorSpawner_Profile(&TActorFactory<ActorSpawner>, ProfileID::cActorSpawner, "ActorSpawner", nullptr, 0);

s32 ActorSpawner::create_()
{
    if (mEventID[1] == 0)
        return 2;

    u16 id = ((mParamEx.course.movement_id & 0xF) << 8) | mParamEx.course.link_id;
    if (mParamEx.course.movement_id >> 4 & 1)  // Map Actor ID
        mSpawnProfileID = MapActorHaxx::cProfileID[id];
    else
        mSpawnProfileID = id;

    mSpawned = false;

    execute_(); // Call execute_() to prevent the spawned actor to be missing for one frame if the event is already active.
    return 1;
}

s32 ActorSpawner::execute_()
{
    if (!PSwitchMgr::instance()->isActivated(mEventID[1] - 1))
        mSpawned = false;

    else if (!mSpawned)
    {
        ActorCreateParam param;
        {
            param.param_0                       = mParam0;
            param.param_1                       = mParam1;
            param.p_profile                     = Profile::get(mSpawnProfileID);
            param.position                      = mPos;
            param.param_ex_0.course.event_id_0  = mEventID[0] & 0xF;
            param.param_ex_0.course.event_id_1  = (mEventID[0] >> 4) & 0xF;
        }
        ActorMgr::instance()->createImmediately(param);

        mSpawned = true;
    }

    return 1;
}
