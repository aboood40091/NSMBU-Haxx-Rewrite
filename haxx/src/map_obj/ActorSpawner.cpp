#include <actor/ActorMgr.h>
#include <actor/MapActor.h>
#include <actor/Profile_Haxx.h>
#include <map/SwitchFlagMgr.h>
#include <map_obj/ActorSpawner.h>

static const Profile ActorSpawner_Profile(&TActorFactory<ActorSpawner>, ProfileInfo::cProfileID_ActorSpawner, "ActorSpawner");

ActorBase::Result ActorSpawner::create_()
{
    if (mTrigSwitchFlag == 0)
        return cResult_Failed;

    u16 id = ((mParamEx.course.movement_id & 0xF) << 8) | mParamEx.course.link_id;
    if (mParamEx.course.movement_id >> 4 & 1)  // Map Actor ID
        mSpawnProfileID = MapActor::cProfileID[id];
    else
        mSpawnProfileID = id;

    mSpawned = false;

    execute_(); // Call execute_() to prevent the spawned actor to be missing for one frame if the switch flag is already active.
    return cResult_Success;
}

bool ActorSpawner::execute_()
{
    if (!SwitchFlagMgr::instance()->isActivated(mTrigSwitchFlag - 1))
        mSpawned = false;

    else if (!mSpawned)
    {
        ActorCreateParam param;
        {
            param.param_0                           = mParam0;
            param.param_1                           = mParam1;
            param.p_profile                         = Profile::get(mSpawnProfileID);
            param.position                          = mPos;
            param.param_ex_0.course.switch_flag_0   = mChildSwitchFlag[0];
            param.param_ex_0.course.switch_flag_1   = mChildSwitchFlag[1];
        }
        ActorMgr::instance()->createImmediately(param);

        mSpawned = true;
    }

    return true;
}
