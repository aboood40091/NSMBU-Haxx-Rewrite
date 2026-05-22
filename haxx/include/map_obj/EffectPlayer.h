#pragma once

#include <actor/Actor.h>

#include <ptcl/seadPtclSystem.h>

class AnimModel;
class PlayerKey;

class EffectPlayer : public Actor
{
public:
    EffectPlayer(const ActorCreateParam& param);

private:
    Result create_() override;
    bool execute_() override;
    bool draw_() override;

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
            AnimModel*,
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
