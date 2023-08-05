#include <actor/Actor.h>
#include <actor/ActorMgr.h>
#include <actor/MapActor.h>
#include <actor/Profile.h>
#include <map/PSwitchMgr.h>

class ActorSpawner : public Actor
{
    ACTOR_CLASS_INIT(ActorSpawner)

public:
    ActorSpawner(const ActorInitArg& arg)
        : Actor(arg)
    {
    }

private:
    s32 create_() override;
    s32 execute_() override;

private:
    u16     mSpawnProfileID;
    bool    mSpawned;
};

static const Profile ActorSpawner_Profile(&ActorSpawner::classInit, ProfileID::cActorSpawner, "ActorSpawner", nullptr, 0);

s32 ActorSpawner::create_()
{
    if (mEventID[1] == 0)
        return 2;

    u16 id = ((mMovementID & 0xF) << 8) | mLinkID;
    if (mMovementID >> 4 & 1)  // Map Actor ID
        mSpawnProfileID = MapActor::cProfileID[id];
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
        ActorInitArg arg;
        {
            arg.param_0     = mParam0;
            arg.param_1     = mParam1;
            arg.p_profile   = Profile::get(mSpawnProfileID);
            arg.position    = mPos;
            arg.event_id_0  = mEventID[0] & 0xF;
            arg.event_id_1  = (mEventID[0] >> 4) & 0xF;
        }
        ActorMgr::instance()->create(arg);

        mSpawned = true;
    }

    return 1;
}
