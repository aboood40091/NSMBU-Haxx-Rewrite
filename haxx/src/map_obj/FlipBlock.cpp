#include <actor/Profile.h>
#include <collision/ActorBgCollisionMgr.h>
#include <graphics/BasicModel.h>
#include <graphics/ModelNW.h>
#include <graphics/Renderer.h>
#include <map_obj/ActorBlockBase.h>
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

class FlipBlock : public ActorBlockBase
{
    ACTOR_CLASS_INIT(FlipBlock)

public:
    FlipBlock(const ActorInitArg& arg);
    virtual ~FlipBlock() { }

private:
    s32 create_()  override;
    s32 execute_() override;
    s32 draw_()    override;

public:
    void spawnItemUp() override;
    void spawnItemDown() override;

    DECLARE_STATE_VIRTUAL_ID_OVERRIDE(FlipBlock, DownMove_DiffEnd)

    bool isActive() override;
    void destroy() override;
    void destroy2() override;

    void updateModel();
    bool playerOverlaps();

    DECLARE_STATE_ID(FlipBlock, Flipping)

private:
    BasicModel* mpBasicModel;
    s32 mFlipsRemaining;

    static const ActorCollisionCheck::Info cCcInfo;
};

CREATE_STATE_ID(FlipBlock, Flipping)
CREATE_STATE_VIRTUAL_ID_OVERRIDE(FlipBlock, BlockCoinBase, DownMove_DiffEnd)

static const ActorCreateInfo FlipBlock_ActorCreateInfo = { sead::Vector2i(8, -16), sead::Vector2i(8, -8), sead::Vector2i(0x100, 0x100), 0, 0, 0, 0, ActorCreateInfo::cFlag_MapObj };
static const Profile FlipBlock_Profile(&FlipBlock::classInit, ProfileID::cFlipBlock, "FlipBlock", &FlipBlock_ActorCreateInfo, 0x1002);

const ActorCollisionCheck::Info FlipBlock::cCcInfo = { sead::Vector2f(0.0f, 8.0f), sead::Vector2f(8.0f, 8.0f), ActorCollisionCheck::cShape_Square, 0, 0, 0, 0, 0, nullptr };

FlipBlock::FlipBlock(const ActorInitArg& arg)
    : ActorBlockBase(arg)
    , mFlipsRemaining(0)
{
}

s32 FlipBlock::create_()
{
    _1cb4 = 0.0f;
    _1cb8 = 0.0f;
    _1ab4 = 0;
    _1aec = 0;
    _1cc0 = 0;
    mCollisionMask.setDirect(0x01);

    mType = cType_Hatena;
    mSquareBgCollision.setType(BgCollision::cType_QuestionBlock);

    if (!init(true, true))
        return 2;

    mContent = cContent_Empty;

    _1cac = 0.0f;
    mVisibleArea.size.x = 2048.0f;
    mVisibleArea.size.y = 1024.0f;

    registerColliderActiveInfo();

    mpBasicModel = BasicModel::create("block_snake", "block_snake", 0, 1, 0, 0, 0);

    mCollisionCheck.set(this, cCcInfo);
    reviveCollisionCheck();

    changeState(StateID_Wait);
    updateModel();

    return 1;
}

s32 FlipBlock::execute_()
{
    s32 result = ActorBlockBase::execute_();
    if (result != 1)
        return result;

    updateModel();
    return 1;
}

s32 FlipBlock::draw_()
{
    Renderer::instance()->drawModel(mpBasicModel);
    return 1;
}

void FlipBlock::spawnItemUp()
{
    changeState(StateID_Flipping);
}

void FlipBlock::spawnItemDown()
{
    mBgCheck.setSensor(nullptr, 3);
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
    _1aae = 0;

    // Undo our "fake" Used state
    mType = cType_Hatena;
    mSquareBgCollision.setType(BgCollision::cType_QuestionBlock);

    mSquareBgCollision.setCallbackFlag(0x00000018);
    mSquareBgCollision.setCallback(
        &BlockCoinBase::callbackFoot,
        &BlockCoinBase::callbackHead,
        &BlockCoinBase::callBackWall
    );
    mSquareBgCollision.setCollisionCallback(&mCollisionCallback);
}

bool FlipBlock::isActive()
{
    return true;
}

void FlipBlock::destroy()
{
    mSpawnDirection = 3;
    changeState(StateID_Flipping);
}

void FlipBlock::destroy2()
{
    mSpawnDirection = 3;
    changeState(StateID_Flipping);
}

void FlipBlock::initializeState_Flipping()
{
    mFlipsRemaining = 7;
    ActorBgCollisionMgr::instance()->release(mSquareBgCollision);
}

void FlipBlock::executeState_Flipping()
{
    if (mSpawnDirection == 3) // Down
        mAngle.x += 0x8000000;

    else
        mAngle.x -= 0x8000000;

    if (mAngle.x == 0 && --mFlipsRemaining <= 0 && !playerOverlaps())
        changeState(StateID_Wait);
}

void FlipBlock::finalizeState_Flipping()
{
    // Add the collider back and literally "reset" the actor
    init(true, true);

    _1aae = 0;
    mAngle.x = 0;
}

void FlipBlock::updateModel()
{
    sead::Vector3f pos(mPos.x, mPos.y + 8.0f, mPos.z);
    sead::Matrixf mtx;
    mtx.makeRTIdx(mAngle, pos);

    mpBasicModel->getModel()->setMtxRT(mtx);
    mpBasicModel->updateModel();
}

bool FlipBlock::playerOverlaps()
{
    bool overlaps = false;

    PlayerObject* player;

    for (s32 i = 0; i < 4; i++)
    {
        if (PlayerMgr::instance()->isPlayerActive(i))
        {
            player = PlayerMgr::instance()->getPlayerObject(i);
            if (player != nullptr)
                overlaps = mCollisionCheck.isOverlap(player->getCollisionCheck());
        }

        if (overlaps)
            return true;
    }

    return false;
}
