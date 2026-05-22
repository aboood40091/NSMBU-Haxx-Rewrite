#include <actor/Profile_Haxx.h>
#include <collision/ActorBgCollisionMgr.h>
#include <effect/EffectCreateUtil.h>
#include <effect/EffectID_Haxx.h>
#include <graphics/AnimModel.h>
#include <graphics/ModelG3d.h>
#include <graphics/Renderer.h>
#include <map_obj/FlipBlock.h>
#include <player/PlayerObject.h>
#include <player/PlayerMgr.h>

/*
    Notes:
    * Currently uses the Snake Block model.
    * The flip block does not check if there
      is an actor (other than the player)
      overlapping with it and can change from
      the "flipping" state to the "waiting"
      state while the actor is inside.
*/

static const ActorCreateInfo FlipBlock_ActorCreateInfo = { 8, -8, 0, 0, 0x100, 0x100, 0, 0, 0, 0, ActorCreateInfo::cFlag_MapObj };
static const Profile FlipBlock_Profile(&TActorFactory<FlipBlock>, ProfileInfo::cProfileID_FlipBlock, "FlipBlock", &FlipBlock_ActorCreateInfo, Profile::cFlag_DrawCullCheck | Profile::cFlag_Unk12);

CREATE_STATE_ID(FlipBlock, Flipping)
CREATE_STATE_VIRTUAL_ID_OVERRIDE(FlipBlock, BlockCoinBase, DownMove_DiffEnd)

const ActorCollisionCheck::CollisionData FlipBlock::cCcData = {
    { 0.0f, 0.0f },
    { 8.0f, 8.0f },
    ActorCollisionCheck::cShapeType_Box,
    ActorCollisionCheck::cKind_Enemy,
    ActorCollisionCheck::cAttack_None,
    ActorCollisionCheck::cTargetKind_None,
    ActorCollisionCheck::cDamageFrom_None,
    ActorCollisionCheck::cStatus_NoPassInfo,
    nullptr
};

static const s32 cWidth  = 1 * 16;  // 1 block
static const s32 cHeight = 1 * 16;  // 1 block

static const s32 cWidth_Half  = cWidth  / 2;
static const s32 cHeight_Half = cHeight / 2;

void FlipBlock::onUpMoveStart()
{
    mHeadSensor.p1 = -(cWidth_Half - 1);
    mHeadSensor.p2 = (cWidth_Half - 1);
    mHeadSensor.center_offset = cHeight_Half;
}

void FlipBlock::initializeFootSensor_()
{
    mFootSensor.p1 = -(cWidth_Half - 1);
    mFootSensor.p2 = (cWidth_Half - 1);
    mFootSensor.center_offset = -cHeight_Half;
}

void FlipBlock::setBoxBgCollisionOfs_()
{
    setBoxBgCollisionOfs(-cWidth_Half, cHeight_Half, cWidth_Half, -cHeight_Half);
}

ActorBase::Result FlipBlock::create_()
{
    _1c68 = 1;
    // _1cb4 = 0.0f;
    // _1cb8 = 0.0f;
    _1ab4 = 0;
    _1aec = 0;
    _1cc0 = 0;
    mCollisionMask.setDirect(0x01);

    mType = cType_Hatena;
    mBoxBgCollision.setType(BgCollision::cType_QuestionBlock);

    if (!init(true, true))
        return cResult_Failed;

    mBoxBgCollision.setFlag(0x00000018);
    mBoxBgCollision.setCallback(
        &BlockCoinBase::callbackFoot,
        &BlockCoinBase::callbackHead,
        &BlockCoinBase::callBackWall
    );
    mBoxBgCollision.setDrcTouchCallback(&mDrcTouchCallback);

    mContent = cContent_Empty;

    mItemCreateAddYPosUp1 = 0.0f;
    mVisibleAreaSize.x = 2048.0f;
    mVisibleAreaSize.y = 1024.0f;

    registerColliderActiveInfo();

    setBoxBgCollisionOfs_();

    mpAnimModel = AnimModel::create("block_snake", "block_snake", 0, 0, 0, 0, 0);

    mCollisionCheck.set(this, cCcData);
    reviveCollisionCheck();

    changeState(StateID_Wait);
    updateModel();

    // Remove this line if you'd like to remove the custom Fire effect
    EffectCreateUtil::createEffect(Sample_Fire_02, &mPos);

    return cResult_Success;
}

bool FlipBlock::execute_()
{
    if (!ActorBlockBase::execute_())
        return false;

    updateModel();
    return true;
}

bool FlipBlock::draw_()
{
    Renderer::instance()->drawModel(mpAnimModel);
    return true;
}

void FlipBlock::spawnItemUp()
{
    changeState(StateID_Flipping);
}

void FlipBlock::spawnItemDown()
{
    mBgCheckObj.setSensorFoot(nullptr);
    changeState(StateID_Flipping);
}

void FlipBlock::initializeState_DownMove_DiffEnd()
{
    // Delay in frames before switching to StateID_Wait
    _1a90 = 15;
}

void FlipBlock::executeState_DownMove_DiffEnd()
{
    BlockCoinBase::executeState_DownMove_DiffEnd();
}

void FlipBlock::finalizeState_DownMove_DiffEnd()
{
    mVSpawnType = cVSpawnType_None;

    // Undo our "fake" Used state
    mType = cType_Hatena;
    mBoxBgCollision.setType(BgCollision::cType_QuestionBlock);

    mBoxBgCollision.setFlag(0x00000018);
    mBoxBgCollision.setCallback(
        &BlockCoinBase::callbackFoot,
        &BlockCoinBase::callbackHead,
        &BlockCoinBase::callBackWall
    );
    mBoxBgCollision.setDrcTouchCallback(&mDrcTouchCallback);
}

bool FlipBlock::isBlockActive()
{
    return true;
}

void FlipBlock::destroy()
{
    mSpawnDirection = cDirType_Down;
    changeState(StateID_Flipping);
}

void FlipBlock::destroy2()
{
    mSpawnDirection = cDirType_Down;
    changeState(StateID_Flipping);
}

void FlipBlock::initializeState_Flipping()
{
    mFlipsRemaining = 7;
    ActorBgCollisionMgr::instance()->release(mBoxBgCollision);
}

void FlipBlock::executeState_Flipping()
{
    if (mSpawnDirection == cDirType_Down) // Down
        mAngle.x() += 0x8000000;

    else
        mAngle.x() -= 0x8000000;

    if (mAngle.x() == 0 && --mFlipsRemaining <= 0 && !playerOverlaps())
    {
        // Add the collider back and literally "reset" the actor
        init(true, true);
        changeState(StateID_Wait);
        mContent = cContent_Empty;
    }
}

void FlipBlock::finalizeState_Flipping()
{
    mVSpawnType = cVSpawnType_None;
    mAngle.x() = 0;

    setBoxBgCollisionOfs_();
}

void FlipBlock::updateModel()
{
    sead::Matrixf mtx;
    mtx.makeRTIdx(mAngle, mPos);

    mpAnimModel->getModel()->setMtxRT(mtx);
    mpAnimModel->getModel()->setScale(mScale);
    mpAnimModel->calcMdl();
}

bool FlipBlock::playerOverlaps()
{
    for (s32 i = 0; i < 4; i++)
    {
        if (PlayerMgr::instance()->isPlayerActive(i))
        {
            const PlayerObject* player = PlayerMgr::instance()->getPlayerObject(i);
            if (player != nullptr && mCollisionCheck.isOverlap(player->getCollisionCheck()))
                return true;
        }
    }
    return false;
}
