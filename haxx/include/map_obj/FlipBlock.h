#pragma once

#include <map_obj/ActorBlockBase.h>

class AnimModel;

class FlipBlock : public ActorBlockBase
{
public:
    FlipBlock(const ActorCreateParam& param)
        : ActorBlockBase(param)
        , mFlipsRemaining(0)
    {
    }

    virtual ~FlipBlock()
    {
    }

private:
    Result create_() override;
    bool execute_() override;
    bool draw_() override;

public:
    void spawnItemUp() override;
    void spawnItemDown() override;

    DECLARE_STATE_VIRTUAL_ID_OVERRIDE(FlipBlock, DownMove_DiffEnd)

    bool isBlockActive() override;
    void destroy() override;
    void destroy2() override;

    void onUpMoveStart() override;

    void onDownMove_DiffStart() override
    {
        initializeFootSensor_();
        ActorBlockBase::onDownMove_DiffStart();
    }

    void updateModel();
    bool playerOverlaps();

    DECLARE_STATE_ID(FlipBlock, Flipping)

private:
    void initializeFootSensor_();
    void setBoxBgCollisionOfs_();

private:
    AnimModel*  mpAnimModel;
    s32         mFlipsRemaining;

    static const ActorCollisionCheck::CollisionData cCcData;
};
