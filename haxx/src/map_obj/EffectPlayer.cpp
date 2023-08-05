#include <actor/Profile_Haxx.h>
#include <effect/PtclMgr.h>
#include <graphics/BasicModel.h>
#include <player/PlayerMgr.h>
#include <player/PlayerObject.h>

#include <log.h>

#include <ptcl/seadPtclSystem.h>

/*
    TODO:
    * Make it more customizable.
    * Better digits rendering (make sead::PrimitiveRenderer work).
    * Better handling of inputs (slightly).
    * Better centering of emitter set number.

    Controls (Player 1 only):
    * Down: Next effect (emitter set)
    * Up: Previous effect (emitter set)
*/

class EffectPlayer : public Actor
{
    ACTOR_CLASS_INIT(EffectPlayer)

public:
    EffectPlayer(const ActorInitArg& arg);

private:
    s32 create_()  override;
    s32 execute_() override;
    s32 draw_()    override;

private:
    bool nextEffect_(const PlayerKey& player1_input);
    bool prevEffect_(const PlayerKey& player1_input);
    void killEffect_();

private:
    nw::eft::Handle mEffectHandle;
    s32             mCurrentEmitterSetID;
    nw::math::MTX34 mMtx;
    bool            mIsDownHeld;
    bool            mIsUpHeld;
    s32             mDownHeldCnt;
    s32             mUpHeldCnt;

    static const s32 cDigitNumMax = 4;
    static const s32 cDigitLineNumMax = 7;

    sead::UnsafeArray<
        sead::UnsafeArray<
            BasicModel*,
            cDigitLineNumMax
        >,
        cDigitNumMax
    > mModel;

    static const sead::Vector2f s_p1;
    static const sead::Vector2f s_p2;
    static const sead::Vector2f s_p3;
    static const sead::Vector2f s_p4;
    static const sead::Vector2f s_p5;
    static const sead::Vector2f s_p6;

    static const s32 cHoldRegisterDuration = 15; // 0.25 sec
};

const sead::Vector2f EffectPlayer::s_p1(-8.0f,  16.0f);
const sead::Vector2f EffectPlayer::s_p2( 8.0f,  16.0f);
const sead::Vector2f EffectPlayer::s_p3( 8.0f,   0.0f);
const sead::Vector2f EffectPlayer::s_p4( 8.0f, -16.0f);
const sead::Vector2f EffectPlayer::s_p5(-8.0f, -16.0f);
const sead::Vector2f EffectPlayer::s_p6(-8.0f,   0.0f);

static const Profile EffectPlayer_Profile(&EffectPlayer::classInit, ProfileID::cEffectPlayer, "EffectPlayer", nullptr, 0);

EffectPlayer::EffectPlayer(const ActorInitArg& arg)
    : Actor(arg)
    , mEffectHandle()
    , mCurrentEmitterSetID(-1)
    , mMtx(nw::math::MTX34::Identity())
    , mIsDownHeld(false)
    , mIsUpHeld(false)
    , mDownHeldCnt(0)
    , mUpHeldCnt(0)
{
}

s32 EffectPlayer::create_()
{
    LOG("EffectPlayer: create start")

    mCurrentEmitterSetID    = -1;
    mIsDownHeld             = false;
    mIsUpHeld               = false;
    mDownHeldCnt            = 0;
    mUpHeldCnt              = 0;

    nw::math::VEC3 ef_scale(mScale.x, mScale.y, mScale.z);

    nw::math::VEC3 ef_rotat;
    if (mParam0 & 1)
    {
        ef_rotat.x = sead::Mathf::idx2rad(mAngle.x + 0x20000000);
        ef_rotat.y = sead::Mathf::idx2rad(mAngle.y + 0x20000000);
    }
    else
    {
        ef_rotat.x = sead::Mathf::idx2rad(mAngle.x);
        ef_rotat.y = sead::Mathf::idx2rad(mAngle.y);
    }
    ef_rotat.z = sead::Mathf::idx2rad(mAngle.z);

    nw::math::VEC3 ef_trans;
    ef_trans.x = (mPos.x += 8.0f);
    ef_trans.y = (mPos.y -= 8.0f);
    ef_trans.z = mPos.z;

    nw::math::MTX34MakeSRT(&mMtx, ef_scale,
                                  ef_rotat,
                                  ef_trans);

    for (u32 i = 0; i < cDigitNumMax; i++)
        for (u32 j = 0; j < cDigitLineNumMax; j++)
            mModel[i][j] = BasicModel::create("block_snake", "block_snake", 0, 0, 0, 0, 0);

    LOG("EffectPlayer: create end")

    return 1;
}

s32 EffectPlayer::execute_()
{
    s32 set_num = PtclMgr::instance()->getPtclSystem()->GetResource(0)->GetNumEmitterSet();
    if (set_num < 1 || mCurrentEmitterSetID >= set_num)
    {
failure:
        LOG("EffectPlayer: Failure")
        killEffect_();
        requestDelete();
        return 1;
    }

    const PlayerObject* player1 = nullptr;
    if (PlayerMgr::instance()->isPlayerActive(0))
        player1 = PlayerMgr::instance()->getPlayerObject(0);

    if (player1 != nullptr && nextEffect_(player1->getPlayerKey()))
    {
        mCurrentEmitterSetID = (mCurrentEmitterSetID + 1) % set_num;
        LOG("EffectPlayer: Proceeding to next: %d", mCurrentEmitterSetID)
    }
    else if (player1 != nullptr && prevEffect_(player1->getPlayerKey()))
    {
        mCurrentEmitterSetID = (mCurrentEmitterSetID - 1) % set_num;
        if (mCurrentEmitterSetID < 0)
            mCurrentEmitterSetID += set_num;
        LOG("EffectPlayer: Going to previous: %d", mCurrentEmitterSetID)
    }
    else
    {
        if (mCurrentEmitterSetID == -1)
            return 1;
        else
            goto update;
    }

    killEffect_();

    if (!PtclMgr::instance()->getPtclSystem()->CreateEmitterSetID(&mEffectHandle, nw::math::MTX34::Identity(), mCurrentEmitterSetID, 0, PtclMgr::instance()->getEmitterSetGroupID(mCurrentEmitterSetID)))
        goto failure;

    LOG("EffectPlayer: Create succeeded")

update:
    if (!mEffectHandle.IsValid())
        goto failure;

    mEffectHandle.GetEmitterSet()->SetMtx(mMtx);

    return 1;
}

s32 EffectPlayer::draw_()
{
    return 1;
}

bool EffectPlayer::nextEffect_(const PlayerKey& player1_input)
{
    if (!mIsDownHeld)
    {
        if (player1_input.isDownPressed())
        {
            mIsDownHeld = true;
            mDownHeldCnt = 0;
        }
    }
    else
    {
        if (player1_input.isDownHeld())
        {
            if (player1_input.isOnlyDownHeld() && ++mDownHeldCnt >= cHoldRegisterDuration)
            {
                mDownHeldCnt = 0;
                return true;
            }
        }
        else
        {
            mIsDownHeld = false;
            if (mDownHeldCnt > 0)
                return true;
        }
    }

    return false;
}

bool EffectPlayer::prevEffect_(const PlayerKey& player1_input)
{
    if (!mIsUpHeld)
    {
        if (player1_input.isUpPressed())
        {
            mIsUpHeld = true;
            mUpHeldCnt = 0;
        }
    }
    else
    {
        if (player1_input.isUpHeld())
        {
            if (player1_input.isOnlyUpHeld() && ++mUpHeldCnt >= cHoldRegisterDuration)
            {
                mUpHeldCnt = 0;
                return true;
            }
        }
        else
        {
            mIsUpHeld = false;
            if (mUpHeldCnt > 0)
                return true;
        }
    }

    return false;
}

void EffectPlayer::killEffect_()
{
    if (mEffectHandle.IsValid())
    {
        nw::eft::EmitterSet* set = mEffectHandle.GetEmitterSet();
        if (set->IsAlive())
            set->Fade();
    }

    mEffectHandle.Invalidate();
}
