#include <actor/Profile_Haxx.h>
#include <collision/ActorBgCollisionMgr.h>
#include <game_info/CourseInfo.h>
#include <graphics/Renderer.h>
#include <map/Bg.h>
#include <map/CourseData.h>
#include <map/UnitID.h>
#include <map_obj/MagicPlatform.h>

/*
    TODO:
    * Add other solidity types.
*/

static const ActorCreateInfo MagicPlatform_ActorCreateInfo = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, ActorCreateInfo::cFlag_IgnoreSpawnRange | ActorCreateInfo::cFlag_MapObj };
static const Profile MagicPlatform_Profile(&TActorFactory<MagicPlatform>, ProfileInfo::cProfileID_MagicPlatform, "MagicPlatform", &MagicPlatform_ActorCreateInfo);

ActorBase::Result MagicPlatform::create_()
{
    CourseDataFile* file = CourseData::instance()->getFile(CourseInfo::instance()->getFileNo());
    const Location* location = file->getLocation(nullptr, mParam0 & 0xFF);
    if (location == nullptr)
        return cResult_Failed;

    u32 loc_x = location->offset.x & ~0xF;
    u32 loc_y = location->offset.y & ~0xF;
    mTileW = (location->size.x + (location->size.x & 0xF) + 0xF) / 16;
    mTileH = (location->size.y + (location->size.y & 0xF) + 0xF) / 16;

    if (!mTileW || !mTileH)
        return cResult_Failed;

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
        return cResult_Failed;

    const BgCollision::Type bg_collision_type = BgCollision::Type((mParam0 >> 16) & 0xFF);
    if (bg_collision_type > BgCollision::cType_InvisibleBlock)
        return cResult_Failed;

    BgUnitCode::Attr bg_collision_attr = BgUnitCode::Attr((mParam0 >> 12) & 0xF);
    if (bg_collision_attr > BgUnitCode::cCarpet)
        bg_collision_attr = BgUnitCode::cNone;

    mParentMovementMgr.link(
        mPos,
        mParentMovementMgr.getTypeMask(ParentMovementType(mParam1 & 0xF)),
        mParamEx.course.movement_id
    );

    switch (mCollisionType)
    {
    case cCollisionType_Box:
        {
            BgCollision::BoxInitArg arg = { sead::Vector2f(0.0f, 0.0f), sead::Vector2f(0.0f, 0.0f), sead::Vector2f(mTileW * -8.0f, mTileH * 8.0f), sead::Vector2f(mTileW * 8.0f, mTileH * -8.0f), 0 };
            mBoxBgCollision.set(this, arg);

            mBoxBgCollision.setDrcTouchCallback(&mDrcTouchCallback);
            // Callbacks for squishing the player
            mBoxBgCollision.setCheckRev(
                &PairObjChild::checkRevFoot,
                &PairObjChild::checkRevHead,
                &PairObjChild::checkRevWall
            );

            mBoxBgCollision.setType(bg_collision_type);
            if ((mParam0 >> 24) & 1)
                mBoxBgCollision.setAttr(bg_collision_attr);

            ActorBgCollisionMgr::instance()->entry(mBoxBgCollision);
        }
        break;
    case cCollisionType_Line:
        {
            mLineBgCollision.set(this, sead::Vector2f(mTileW * -8.0f, mTileH * 8.0f), sead::Vector2f(mTileW * 8.0f, mTileH * 8.0f));

            mLineBgCollision.setType(bg_collision_type);
            if ((mParam0 >> 24) & 1)
                mLineBgCollision.setAttr(bg_collision_attr);

            ActorBgCollisionMgr::instance()->entry(mLineBgCollision);
        }
        break;
    }

    if (!execute_())
        return cResult_Failed;

    return cResult_Success;
}

bool MagicPlatform::execute_()
{
    mParentMovementMgr.execute();
    mPos = mParentMovementMgr.getPosition();
    mAngle.z() = mParentMovementMgr.getAngle();

    switch (mCollisionType)
    {
    case cCollisionType_Box:
        mBoxBgCollision.setAngle(mAngle.z());
        mBoxBgCollision.execute();
        break;
    case cCollisionType_Line:
        mLineBgCollision.setAngle(mAngle.z());
        mLineBgCollision.execute();
        break;
    }

    return true;
}

bool MagicPlatform::draw_()
{
    f32 sin_v, cos_v;
    sead::Mathf::sinCosIdx(&sin_v, &cos_v, mAngle.z());

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

            Renderer::instance()->drawActorBgUnit(UnitID(mTileData[y * mTileW + x]), draw_pos, mAngle.z(), mScale);
        }
    }

    return true;
}

ActorBase::Result MagicPlatform::doDelete_()
{
    if (mTileData != nullptr)
    {
        delete[] mTileData;
        mTileData = nullptr;
    }

    return cResult_Success;
}
