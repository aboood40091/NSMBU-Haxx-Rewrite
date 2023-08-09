#include <actor/Actor.h>
#include <actor/Profile_Haxx.h>
#include <collision/ActorBgCollisionMgr.h>
#include <collision/BasicRideLineBgCollision.h>
#include <collision/SquareBgCollision.h>
#include <game/Info.h>
#include <graphics/BasicModel.h>
#include <graphics/Renderer.h>
#include <map/Bg.h>
#include <map/CourseData.h>
#include <map/UnitID.h>
#include <map_obj/PairObjChild.h>
#include <map_obj/ParentMovementMgr.h>

/*
    TODO:
    * Add other solidity types.
*/

// Callback table, useful for squishing the player
class MagicPlatformCB : public PairObjChildBaseCB
{
public:
    bool bcCallback1(Actor*, BgCollision*, const sead::Vector2f&) override { return false; }
};
static_assert(sizeof(MagicPlatformCB) == sizeof(PairObjChildBaseCB));

class MagicPlatform : public Actor
{
public:
    MagicPlatform(const ActorCreateParam& param);
    virtual ~MagicPlatform() { }

private:
    s32 create_()   override;
    s32 execute_()  override;
    s32 draw_()     override;
    s32 doDelete_() override;

private:
    u16*                        mTileData;
    u32                         mTileW;
    u32                         mTileH;

    ParentMovementMgr           mParentMovementMgr;

    enum CollisionType
    {
        cCollisionType_Square,
        cCollisionType_Line,
        cCollisionType_None
    }                           mCollisionType;
    SquareBgCollision           mSquareBgCollision;
    MagicPlatformCB             mCollisionCallback;
    BasicRideLineBgCollision    mLineBgCollision;
};

static const ActorCreateInfo MagicPlatform_ActorCreateInfo = { sead::Vector2i(0, 0), sead::Vector2i(0, 0), sead::Vector2i(0, 0), 0, 0, 0, 0, ActorCreateInfo::cFlag_IgnoreSpawnRange | ActorCreateInfo::cFlag_MapObj };
static const Profile MagicPlatform_Profile(&TActorFactory<MagicPlatform>, ProfileID::cMagicPlatform, "MagicPlatform", &MagicPlatform_ActorCreateInfo, 0);

MagicPlatform::MagicPlatform(const ActorCreateParam& param)
    : Actor(param)
    , mTileData(nullptr)
    , mParentMovementMgr()
    , mSquareBgCollision()
    , mLineBgCollision()
{
}

s32 MagicPlatform::create_()
{
    CourseDataFile* file = CourseData::instance()->getFile(Info::instance()->getFileNo());
    const Location* location = file->getLocation(nullptr, mParam0 & 0xFF);
    if (location == nullptr)
        return 2;

    u32 loc_x = location->offset.x & ~0xF;
    u32 loc_y = location->offset.y & ~0xF;
    mTileW = (location->size.x + (location->size.x & 0xF) + 0xF) / 16;
    mTileH = (location->size.y + (location->size.y & 0xF) + 0xF) / 16;

    if (!mTileW || !mTileH)
        return 2;

    mTileData = new u16[mTileW * mTileH];

    for (u32 y = 0; y < mTileH; y++)
    {
        for (u32 x = 0; x < mTileW; x++)
        {
            u16* p_unit = Bg::getUnitCurrentCdFile(loc_x + x * 16, loc_y + y * 16, 0);
            mTileData[x + y * mTileW] = p_unit ? *p_unit : cUnitID_Null;
        }
    }

    mCollisionType = CollisionType((mParam0 >> 8) & 0xF);
    if (mCollisionType > cCollisionType_None)
        return 2;

    const BgCollision::Type bg_collision_type = BgCollision::Type((mParam0 >> 16) & 0xFF);
    if (bg_collision_type > BgCollision::cType_InvisibleBlock)
        return 2;

    BgCheckUnitInfo::SurfaceType bg_collision_surface_type = BgCheckUnitInfo::SurfaceType((mParam0 >> 12) & 0xF);
    if (bg_collision_surface_type > BgCheckUnitInfo::cSurfaceType_BeanstalkLeaf)
        bg_collision_surface_type = BgCheckUnitInfo::cSurfaceType_Normal;

    switch (mCollisionType)
    {
    case cCollisionType_Square:
        {
            BgCollision::SquareInitArg arg = { sead::Vector2f(0.0f, 0.0f), sead::Vector2f(0.0f, 0.0f), sead::Vector2f(mTileW * -8.0f, mTileH * 8.0f), sead::Vector2f(mTileW * 8.0f, mTileH * -8.0f), 0 };
            mSquareBgCollision.set(this, arg);

            // More Ugh
            // Callback table, useful for squishing the player
            mSquareBgCollision.setCollisionCallback(&mCollisionCallback);
            mSquareBgCollision.setCheckRev(
                &PairObjChild::checkRevFoot,
                &PairObjChild::checkRevHead,
                &PairObjChild::checkRevWall
            );

            mSquareBgCollision.setType(bg_collision_type);
            if ((mParam0 >> 24) & 1)
                mSquareBgCollision.setSurfaceType(bg_collision_surface_type);

            ActorBgCollisionMgr::instance()->entry(mSquareBgCollision);
        }
        break;
    case cCollisionType_Line:
        {
            const sead::Vector2f points[2] = { sead::Vector2f(mTileW * -8.0f, mTileH * 8.0f), sead::Vector2f(mTileW * 8.0f, mTileH * 8.0f) };
            BgCollision::InitArg arg = { sead::Vector2f(0.0f, 0.0f), sead::Vector2f(0.0f, 0.0f), points, 0 };
            mLineBgCollision.set(this, arg, 2);

            mLineBgCollision.setType(bg_collision_type);
            if ((mParam0 >> 24) & 1)
                mLineBgCollision.setSurfaceType(bg_collision_surface_type);

            ActorBgCollisionMgr::instance()->entry(mLineBgCollision);
        }
        break;
    }

    mParentMovementMgr.link(
        mPos,
        mParentMovementMgr.getTypeMask(ParentMovementType(mParam1 & 0xFF)),
        mMovementID
    );

    return execute_();
}

s32 MagicPlatform::execute_()
{
    mParentMovementMgr.execute();
    mPos = mParentMovementMgr.getPosition();
    mAngle.z = mParentMovementMgr.getAngle();

    switch (mCollisionType)
    {
    case cCollisionType_Square:
        mSquareBgCollision.setAngle(mAngle.z);
        mSquareBgCollision.execute();
        break;
    case cCollisionType_Line:
        mLineBgCollision.setAngle(mAngle.z);
        mLineBgCollision.execute();
        break;
    }

    return 1;
}

s32 MagicPlatform::draw_()
{
    f32 sin_v, cos_v;
    sead::Mathf::sinCosIdx(&sin_v, &cos_v, mAngle.z);

    for (s32 y = 0; y < mTileH; y++)
    {
        for (s32 x = 0; x < mTileW; x++)
        {
            s32 offset_x = x * 16 - mTileW * 8 + 8;
            s32 offset_y = y * 16 - mTileH * 8 + 8;

            // https://en.wikipedia.org/wiki/Rotation_matrix#In_two_dimensions
            f32 rotated_x =  offset_x * cos_v + offset_y * sin_v;
            f32 rotated_y = -offset_x * sin_v + offset_y * cos_v;
            sead::Vector3f draw_pos(mPos.x + rotated_x, mPos.y - rotated_y, mPos.z);

            Renderer::instance()->drawActorBgUnit(UnitID(mTileData[y * mTileW + x]), draw_pos, mAngle.z, mScale);
        }
    }

    return 1;
}

s32 MagicPlatform::doDelete_()
{
    if (mTileData != nullptr)
    {
        delete[] mTileData;
        mTileData = nullptr;
    }

    return 1;
}
