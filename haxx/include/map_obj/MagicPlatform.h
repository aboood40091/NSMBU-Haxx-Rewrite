#pragma once

#include <actor/Actor.h>
#include <collision/ActorBoxBgCollision.h>
#include <collision/ActorLineBgCollision.h>
#include <map_obj/PairObjChild.h>
#include <map_obj/ParentMovementMgr.h>

// Callback table, useful for squishing the player
class MagicPlatformDrcTouchCB : public PairObjChildDrcTouchCB
{
public:
    bool bcSetTouchNormal(BgCollision* p_bg_collision, const sead::Vector2f& pos) override { return false; }
};
static_assert(sizeof(MagicPlatformDrcTouchCB) == sizeof(PairObjChildDrcTouchCB));

class MagicPlatform : public Actor
{
public:
    MagicPlatform(const ActorCreateParam& param)
        : Actor(param)
        , mTileData(nullptr)
    {
    }

    virtual ~MagicPlatform()
    {
    }

private:
    Result create_() override;
    bool execute_() override;
    bool draw_() override;
    Result doDelete_();

private:
    u16*                    mTileData;
    u32                     mTileW;
    u32                     mTileH;

    ParentMovementMgr       mParentMovementMgr;

    enum CollisionType
    {
        cCollisionType_Box,
        cCollisionType_Line,
        cCollisionType_None
    };
    CollisionType           mCollisionType;
    ActorBoxBgCollision     mBoxBgCollision;
    MagicPlatformDrcTouchCB mDrcTouchCallback;
    ActorLineBgCollision    mLineBgCollision;
};
