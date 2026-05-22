#pragma once

#include <actor/ActorBase.h>

class ActorSpawner : public ActorBase
{
public:
    ActorSpawner(const ActorCreateParam& param)
        : ActorBase(param)
        , mPos(param.position)
        , mTrigSwitchFlag(param.param_ex_0.course.switch_flag_1)
    {

        mChildSwitchFlag[0] = param.param_ex_0.course.switch_flag_0 & 0xF;
        mChildSwitchFlag[1] = (param.param_ex_0.course.switch_flag_0 >> 4) & 0xF;
    }

private:
    Result create_() override;
    bool execute_() override;

private:
    sead::Vector3f  mPos;
    u8              mTrigSwitchFlag;
    u8              mChildSwitchFlag[2];
    bool            mSpawned;
    u16             mSpawnProfileID;
};
